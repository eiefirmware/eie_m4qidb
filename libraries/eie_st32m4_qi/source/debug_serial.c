#include "configuration.h"

/* USART3 Baud Rate */
#define DEBUG_SERIAL_BAUD_RATE 115200

/* USART initialization structure */
USART_InitTypeDef USART_InitStructure;

/* Queue to manage TX and RX communication to the driver */
xQueueHandle xQueueDebugSerialTX;
xQueueHandle xQueueDebugSerialRX;

xSemaphoreHandle G_xUsart3PeripheralMutex; /* Mutex to protect access to the USART3 peripheral */

#if 0
/*
 * @brief  Wait for Enter on USART3
 */
void debugWaitOnEnter()
{
    char receiveChar;
    do
    {
        xQueueReceive( xQueueDebugSerialRX, &receiveChar, 10);
    }while(receiveChar != '\r');
}
#endif

/*
 * @brief  Starts the debugSerial driver task
 * @param  Task priority
 * @retval None
 */
void vStartUARTtask (unsigned portBASE_TYPE uxPriority)
{

    /* Spawn the task. */
    xTaskCreate(vUARTtask, (signed char * ) "UART3", configMINIMAL_STACK_SIZE,
                (void* ) NULL, uxPriority, (xTaskHandle * ) NULL);

    G_xUsart3PeripheralMutex = xSemaphoreCreateMutex();
}

/*
 * @brief  Macro for debugSerial driver task
 * @param  task name,
 * @retval None
 */
static portTASK_FUNCTION( vUARTtask, pvParameters )
{
    //Fill init structure for USART3 and call init
    USART_InitStructure.USART_BaudRate = DEBUG_SERIAL_BAUD_RATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl =
            USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    EIE_COMInit (COM3, &USART_InitStructure);

    //Enable interrupt flag
    USART_ITConfig (USART3, USART_IT_RXNE, ENABLE);

    //Enable interrupt priority
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =
            configLIBRARY_LOWEST_INTERRUPT_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init (&NVIC_InitStructure);

    //Char array to receieve the queue value into
    char recieveBuffer[U32_DEBUG_SERIAL_MAX_MESSAGE_SIZE];

    for (;;)
    {

      //Check that the tx queue exists
      if (xQueueDebugSerialTX != 0)
      {

        /* Receive a message on the tx queue.  Block task indefinitely while a
         message is not available on the tx queue. */
        if (xQueueReceive(xQueueDebugSerialTX, recieveBuffer,
                          portMAX_DELAY))
        {
          //Send the char array
          for (uint8_t i = 0; i < recieveBuffer[0]; i++)
          {
              while (USART_GetFlagStatus (USART3, USART_FLAG_TC) != 1)
              {
              }

              USART_SendData (USART3, recieveBuffer[i + 1]);

          }
        }
      }
    }
}

/* USART3 Interrupt Handler */
void USART3_IRQHandler (void)
{
  /* handle recieve buffer not empty interrupt */
  if ((uint8_t) USART_GetITStatus (USART3, USART_IT_RXNE))
  {
    char cIn = (uint8_t) (USART3->DR & (uint16_t) 0x01FF);
    xQueueSendToBackFromISR(xQueueDebugSerialRX, &cIn, pdFALSE);
    USART_ClearITPendingBit (USART3, USART_IT_RXNE);
  }
}


