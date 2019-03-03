/**********************************************************************************************************************
File: boardtest.h                                                                
**********************************************************************************************************************/

#ifndef __BOARDTEST_H
#define __BOARDTEST_H

/**********************************************************************************************************************
Type Definitions
**********************************************************************************************************************/

/**********************************************************************************************************************
Constants / Definitions
**********************************************************************************************************************/
#define BOARDTEST_STACK_SIZE                  configMINIMAL_STACK_SIZE        /* Size of the task stack */
#define BOARDTEST_TASK_PRIORITY               mainREGULAR_TASK_PRIORITY       /* Priority of the task */

/* GGu32BoardTestFlags */
//#define _BOARDTEST_        0x00000001      /*  */
/* end of GGu32BoardTestFlags */

#define BOARDTEST_START_DELAY                (u32)3000                        /* Time in ms before board test starts running */              
#define BOARDTEST_UPDATE_PERIOD              (u32)1000                        /* Time in ms between updates */              


/**********************************************************************************************************************
Function Declarations
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/
static portTASK_FUNCTION( vBoardTestTask, pvParameters );
void vStartvBoardTestTask( unsigned portBASE_TYPE uxPriority );


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/



#endif /* __BOARDTEST_H */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/