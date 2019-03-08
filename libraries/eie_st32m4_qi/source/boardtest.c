/**********************************************************************************************************************
 File: boardtest.c

 Description:
 Board testing application.

**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
 Global variable definitions with scope across entire project.
 All Global variable names shall start with "G_"
 ***********************************************************************************************************************/
/* New variables */
xTaskHandle pvBoardTestTaskHandle; /* The task handle */
volatile u32 G_u32BoardTestFlags; /* Global state flags */

//xQueueHandle G_xBoardTestQueue;                       /* Queue to transmit data out of the SPI */

//xSemaphoreHandle G_xBoardTestMutex;                  /* Mutex to protect access to ? */
//xSemaphoreHandle G_xBoardTestSemaphore;              /* Binary semaphore used to ? */

/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */


/***********************************************************************************************************************
 Global variable definitions with scope limited to this local application.
 Variable names shall start with "BoardTest_" and be declared as static.
 ***********************************************************************************************************************/

//static u32 BoardTest_u32Timeout;                      /* Timeout counter used across states */

/**********************************************************************************************************************
 Function Definitions
 **********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Standard function to create a task */
void vStartvBoardTestTask (unsigned portBASE_TYPE uxPriority)
{
    /* Spawn the task. */
    xTaskCreate(vBoardTestTask, (signed char * ) "BoardTest",
                BOARDTEST_STACK_SIZE, NULL, uxPriority, &pvBoardTestTaskHandle);

    /* Create the message queues */
    //G_xBoardTestQueue = xQueueCreate(SPI_QUEUE_LENGTH, SPI_QUEUE_ITEM_SIZE);
    /* Uncomment the next line to be able to see the queues in the debugger: */
    //vQueueAddToRegistry(G_xBoardTestQueue, "BoardTest_QUEUE");
    /* Create required semaphores and mutexes */
    //G_xTEMPALTEMutex = xSemaphoreCreateMutex();
    //vSemaphoreCreateBinary(G_xBoardTestSemaphore);
} /* end vStartBoardTestTask() */

/*-----------------------------------------------------------
 Main task definition
 Board test continually checks and reports various system paramters.

 For now, board test:
 */
static portTASK_FUNCTION( vBoardTestTask, pvParameters )
{
    (void) pvParameters; /* The parameters are not used. */
    static bool bStartupDelay = true;

    for (;;)
    {
        /* Run only the first time */
        if (bStartupDelay == true)
        {
            /* Start with a delay */
            vTaskDelay (BOARDTEST_START_DELAY);

            bStartupDelay = false;
        }
        /* Regular execution */
        else
        {
          
            /* Block until next cycle */
            vTaskDelay ( BOARDTEST_UPDATE_PERIOD);
        }

    } /* end of task functionality */

} /* end portTASK_FUNCTION */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
