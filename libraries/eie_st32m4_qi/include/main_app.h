/**********************************************************************************************************************
File: main.h
**********************************************************************************************************************/

#ifndef __MAIN_APP_H
#define __MAIN_APP_H

/**********************************************************************************************************************
Type Definitions
**********************************************************************************************************************/

/**********************************************************************************************************************
Constants / Definitions
**********************************************************************************************************************/
#define BOARDTEST_STACK_SIZE                  configMINIMAL_STACK_SIZE        /* Size of the task stack */
#define BOARDTEST_TASK_PRIORITY               mainREGULAR_TASK_PRIORITY       /* Priority of the task */

/* GGu32LCDFlags */
//#define _BOARDTEST_        0x00000001      /*  */
/* end of GGu32LCDFlags */

#define MAIN_START_DELAY                (u32)3000                        /* Time in ms before board test starts running */
#define MAIN_UPDATE_PERIOD              (u32)1000                         /* Time in ms between updates on the board test screen */


// Global System Flags
#define SYSFLAG_NVM_RESTORED    (0x00000001)
#define SYSFLAG_TEMP_LOW        (0x00000100)
#define SYSFLAG_TEMP_HIGH       (0x00000200)
#define SYSFLAG_ALARM           (0x00000400)

typedef enum
{
  SCREEN_MAIN,
  SCREEN_CONFIG
} ScreenIDEnum;



#define ConfigDataStartDelim ('J')
#define ConfigDataEndDelim   ('r')

typedef enum
{
  OPTIONTYPE_INTEGER0, // *Must be 0 = integer
  OPTIONTYPE_INTEGER1, // *Must be 1 = float 1 decimal
  OPTIONTYPE_INTEGER2, // *Must be 2 = float 2 decimals
  OPTIONTYPE_STRING,
  OPTIONTYPE_FLOAT
} OptionTypeEnum;

#define MENU_OPTION_MAX_LENGTH   (10)



/**********************************************************************************************************************
Function Declarations
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/
static portTASK_FUNCTION( vMainAppTask, pvParameters );
void vStartMainAppTask( unsigned portBASE_TYPE uxPriority );


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


#endif /* __BOARDTEST_H */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
