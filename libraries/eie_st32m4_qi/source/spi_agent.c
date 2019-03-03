/*******************************************************************************
 File: spi_agent.c

 Description:
 A SPI agent manages access to an SPI peripheral resource.  It is a fairly dumb application
 that does not care who is writing to it, or who is reading from it.  It only manages
 sending data that is coming in on the transmit queue and reports data received on the receive queue.
 This particular agent works for SPI2.

 All data transactions to the SPI perihperal are interrupt-triggered, and thus the ISR that handles
 those interrupts is provided within this file.  Functions from stm32f4xx_spi.c are called
 to make things happen.

 The agent task priority should be set above the regular task priorities to ensure it efficiently sends out
 data.  When transmit data is present, the task will block as soon as a databyte is loaded to the SPI
 transmit register and will unblock on the interrupt that fires when the databyte has been sent.
 Currently, this is going to cause quite a lot of context switching since the byte transmission time is only
 43us at 183kHz SPI clock. Need to rewrite this for DMA!

 Use of the peripheral is managed by a Mutex to ensure that resource conflicts are avoided even
 though it makes no sense to have multiple agents using the same SPI peripheral. Always
 good to protect against secret agents, though!

 CUSTOMIZATION FOR LCD INTERFACE (#define LCD_SPI_AGENT)
 The base spi_agent driver is modified to work for the LCD interface required in the SCI design.
 There are two main differences:
 1. No data is required to be received from the LCD, so no receive functionlity is offered.
 2. Control of the LCD's command/data line GPIO is required for each message, so the transmit queue
 will consist of LcdQueueMessageType objects instead of regular queue objects with just length and data.

 -----------------------------------------------------------------------------------

 Task details:
 Since this task interacts only with message queues, there is no API defined.  However,
 the mutex and queues required by an instance of this task are listed here:

 xSemaphoreHandle G_xSpi[X]PeripheralMutex;
 Mutex to protect access to the SPI peripheral

 xQueueHandle G_xSpi[X]TransmitQueue;
 Queue to provide data to the SPI task to send.  The queue elements are structures with at least
 two fields:
 u16 u16Length;
 u8* pu8Data;

 The SPI Agent will send u16Length bytes starting at the data pointed to by pu8Data.
 If additional fields are added in the queue element, a preprocessor switch should be added
 to the SPI agent code to enable functionality related to the other field(s).

 xQueueHandle G_xSpiXReceiveQueue;
 Queue where incoming data will be posted by the SPI Agent. The data will be considered one
 complete message for all bytes received between the initial assertion of CS until CS is deasserted.
 The queue elements are structures with


 *******************************************************************************/

#include "configuration.h"


/***********************************************************************************************************************
 Global variable definitions with scope across entire project.
 All Global variable names shall start with "G_xxSpi"
 ***********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
/* New variables */
xTaskHandle pvSpi2TaskHandle; /* The SPI agent task handle */

/* The default transmit queue is not needed for the LCD implementation of this agent. */
xQueueHandle G_xSpi2TransmitQueue; /* Queue to transmit data out of the SPI */
xQueueHandle G_xSpi2ReceiveQueue; /* Queue to receive data in from the SPI */

xSemaphoreHandle G_xSpi2PeripheralMutex; /* Mutex to protect access to the SPI2 peripheral */
xSemaphoreHandle G_xSpi2TransmittingSemaphore; /* Binary semaphore used to block the agent task while a message is transmitting */

u32 G_u32AgentCounter = 0; /* Debug counter */
u32 G_u32AgentIntTxCounter = 0; /* Debug counter */
u32 G_u32AgentIntRxCounter = 0; /* Debug counter */

/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */


/***********************************************************************************************************************
 Global variable definitions with scope limited to this task.
 Variable names shall start with "Spi_" and be declared as static.
 ***********************************************************************************************************************/
u8 Spi_au8RxBuffer[SPI_RX_BUFFER_SIZE ]; /* Receive buffer for characters read by the agent */
u8* Spi_pu8RxNextByte; /* Pointer to location of next byte to be received. */
u8 Spi_u8RxByteCount; /* Number of bytes received in current message. */

volatile u16 Spi_u16CurrentTxMessageBytesToSend; /* Counter to track how many bytes need to be sent in the current message */
volatile u8* Spi_u8CurrentTxMessage; /* Pointer to current transmitting message */

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public Functions */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected Functions */
/*--------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------*/
/* Standard function to create a task */
void
vStartSpi2Task (unsigned portBASE_TYPE uxPriority)
{
    /* Spawn the task. */
    xTaskCreate(vSpiTask, (signed char * ) "SPI2", SPI_STACK_SIZE, NULL,
                uxPriority, &pvSpi2TaskHandle);

    /* Create the message queues */
    G_xSpi2TransmitQueue = xQueueCreate(SPI_QUEUE_LENGTH, SPI_QUEUE_ITEM_SIZE);
    G_xSpi2ReceiveQueue = xQueueCreate(SPI_QUEUE_LENGTH, SPI_QUEUE_ITEM_SIZE);

    /* Uncomment the next two lines to be able to see the queues in the debugger: */
    vQueueAddToRegistry(G_xSpi2TransmitQueue, "SPI_TX_QUEUE");
    vQueueAddToRegistry(G_xSpi2ReceiveQueue, "SPI_RX_QUEUE");

    /* Create required semaphores and mutexes */
    G_xSpi2PeripheralMutex = xSemaphoreCreateMutex();
    vSemaphoreCreateBinary(G_xSpi2TransmittingSemaphore);
    xSemaphoreTake(G_xSpi2TransmittingSemaphore, portMAX_DELAY);

} /* end vStartSpi2Task() */

/*-----------------------------------------------------------
 Initialize and run the SPI Agent.
 */
static portTASK_FUNCTION( vSpiTask, pvParameters )
{
    portBASE_TYPE xStatus;

    (void) pvParameters; /* The parameters are not used. */

    /* Initialize task parameters */
    Spi_pu8RxNextByte = &Spi_au8RxBuffer[0];
    Spi_u8RxByteCount = 0;

    /* Configure the SPI2 peripheral and enable interrupts */
    //SPI2_Init();

    for (;;)
    {
        /* When the transmit queue is not empty, the task is actively keeping the SPI transmit buffer full of data
         so that it never starves.  The SPI clock should be running continuously during the transfer of a message. */
        xStatus = xQueueReceive( G_xSpi2ReceiveQueue, &sCurrentMessageDetails, portMAX_DELAY);

        /* While there is data to transmit, the task reads from the message queue to fill up the buffer */
        if (xStatus == pdPASS)
        {
            /* Initialize the local global variables that the SPI ISR needs for data transmission */
            Spi_u16CurrentTxMessageBytesToSend =
                    sCurrentMessageDetails.u16Length;
            Spi_u8CurrentTxMessage = sCurrentMessageDetails.pu8Data;


            /* Enable interrupts and queue the first byte */
            Spi_u16CurrentTxMessageBytesToSend--;
            SPI_I2S_SendData (SPI2, *Spi_u8CurrentTxMessage++);
            SPI_I2S_ITConfig (SPI2, SPI_I2S_IT_TXE, ENABLE);

            G_u32AgentCounter++;

            /* Try to take the transmitting semaphore to block the task.  The ISR will give it back when the entire message has been sent. */
            xSemaphoreTake(G_xSpi2TransmittingSemaphore, portMAX_DELAY);

            /* Deassert chip select after a short delay */
            vTaskDelay (1);
        }

    } /* end of task functionality */

} /* end portTASK_FUNCTION */

/*------------------------------------------------------------------------------
 ISR: SPI2_IRQHandler

 Description:
 Interrupt handler for enabled SPI2 interrupts:
 - TXE (Tx buffer empty) to trigger load of another byte (if available)
 - RXNE (Rx buffer not empty) to trigger reading a received byte

 Note: SPI bytes are received based on sending transmit bytes (usually dummies) for every Rx byte expected.
 Therefore we use the transmit count and semaphore to control the end of receive (must wait for the last byte
 to be received before quitting the current message).

 Requires:
 - eBacklightColor_ is the constant for the color of choice
 - The LED GPIOs have been configured

 Promises:
 - New outgoing data is queued to the transmit buffer; new incoming data is placed in the receive buffer
 */
void
SPI2_IRQHandler (void)
{
    static signed portBASE_TYPE xHigherPriorityTaskWoken;

    /* The receive interrupt indicates when a byte has been received and should be placed into the receive register.*/
    if (SPI_I2S_GetITStatus (SPI2, SPI_I2S_IT_RXNE) == SET)
    {
        G_u32AgentIntRxCounter++;

        /* A byte has been received - place it into the receive buffer and advance. */
        *Spi_pu8RxNextByte = (u8) (SPI_I2S_ReceiveData (SPI2));
        Spi_pu8RxNextByte++;
        Spi_u8RxByteCount++;

        /* The maximum allowed message size is SPI_RX_BUFFER_SIZE, so if we've received that then we can't receive anything else. */
        if (Spi_pu8RxNextByte == &Spi_au8RxBuffer[SPI_RX_BUFFER_SIZE ])
        {
            Spi_u16CurrentTxMessageBytesToSend = 0;
        }

        /* Check if this was the last byte to be received.  If so, post the message to the Rx queue and
         unblock the SPI agent task by giving the transmit semaphore. */
        if (Spi_u16CurrentTxMessageBytesToSend == 0)
        {
            /* Update the struct that will be queued and queue it*/
            sRxMessage.u16Length = Spi_u8RxByteCount;
            sRxMessage.pu8Data = &Spi_au8RxBuffer[0];
            xQueueSendFromISR(G_xSpi2ReceiveQueue, &sRxMessage, &xHigherPriorityTaskWoken);

            /* Give the transmit semaphore here, because there is always a receive byte after the last tx bit */
            xSemaphoreGiveFromISR(G_xSpi2TransmittingSemaphore, &xHigherPriorityTaskWoken);

            /* Reset parameters */
            Spi_u8RxByteCount = 0;
            Spi_pu8RxNextByte = &Spi_au8RxBuffer[0];
        }
    }

    /* The transmit interrupt indicates when a byte has been sent and the register is ready for the next byte.*/
    if (SPI_I2S_GetITStatus (SPI2, SPI_I2S_IT_TXE) == SET)
    {
        G_u32AgentIntTxCounter++;

        /* Tx of the current byte is complete.  If there is another byte to send, queue it up now! */
        if (Spi_u16CurrentTxMessageBytesToSend != 0)
        {
            Spi_u16CurrentTxMessageBytesToSend--;
            SPI_I2S_SendData (SPI2, *Spi_u8CurrentTxMessage++);
        }
        /* Otherwise we're done, so disable the interrupt */
        else
        {
            SPI_I2S_ITConfig (SPI2, SPI_I2S_IT_TXE, DISABLE);
        }
    }

} /* end SPI2_IRQHandler() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private Functions */
/*--------------------------------------------------------------------------------------------------------------------*/

