/**********************************************************************************************************************
File: template.c                                                                

Description:
This is a template .c file new source code

API overview:
**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */
xTaskHandle pvTEMPLATETaskHandle;                      /* The task handle */
volatile u32 G_u32TEMPLATEFlags;                       /* Global state flags */

//xQueueHandle G_xTEMPLATEQueue;                       /* Queue to transmit data out of the SPI */

//xSemaphoreHandle G_xTEMPLATEMutex;                  /* Mutex to protect access to  */
//xSemaphoreHandle G_xTEMPLATESemaphore;              /* Binary semaphore used to  */

/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
//extern volatile                                    /* From where.c? */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "TEMPLATE_" and be declared as static.
***********************************************************************************************************************/

static u32 TEMPLATE_u32Timeout;                      /* Timeout counter used across states */


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
void vStartTEMPLATETask( unsigned portBASE_TYPE uxPriority )
{
  /* Spawn the task. */
  xTaskCreate( vTEMPLATETask, ( signed char * ) "TEMPLATE", TEMPLATE_STACK_SIZE, NULL, uxPriority, &pvTEMPLATETaskHandle );

  /* Create the message queues */
  //G_xTEMPLATEQueue = xQueueCreate(TEMPLATE_QUEUE_LENGTH, TEMPLATE_QUEUE_ITEM_SIZE);
  
  /* Uncomment the next line to be able to see the queues in the debugger: */  
  //vQueueAddToRegistry(G_xTEMPLATEQueue, "TEMPLATE_QUEUE");
  
  /* Create required semaphores and mutexes */
  //G_xTEMPALTEMutex = xSemaphoreCreateMutex();
  //vSemaphoreCreateBinary(G_xTEMPLATESemaphore);
  
} /* end vStartTEMPLATETask() */


/*-----------------------------------------------------------
Main task definition
What does this task do?
*/
static portTASK_FUNCTION( vTEMPLATETask, pvParameters )
{
  ( void ) pvParameters; /* The parameters are not used. */

  /* Add any initialization code here */
  
  /* The main task */
  for(;;)
  {


  } /* end of task functionality */
        
} /* end portTASK_FUNCTION */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
