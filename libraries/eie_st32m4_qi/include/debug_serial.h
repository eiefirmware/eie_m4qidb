  /*
  ******************************************************************************
  * @file    debugSerial.h
  *
  * @brief   This file contains definitions for the debug serial driver  on
  *          USART1 and test tasks.
  ******************************************************************************
  */

#include "configuration.h"

/* Includes ------------------------------------------------------------------*/
//#include "stm32f4xx.h"

/* Hardware and starter kit includes. */
//#include "scic-ehdw-01.h"

#define DEBUG_SERIAL_TASK_PRIORITY           mainREGULAR_TASK_PRIORITY

#define U32_DEBUG_SERIAL_MAX_MESSAGE_SIZE    (u32)128
    
/* Debug Serial TX Functions **************************************************/
//void debugPrint(char* stringToPrint);

/* Debug Serial Task Functions ************************************************/
void vStartUARTtask( unsigned portBASE_TYPE uxPriority );
static portTASK_FUNCTION_PROTO( vUARTtask, pvParameters );

//void debugWaitOnEnter(void);

//void ConverttoHex(uint8_t modbusMessage[8], uint8_t message[24]);

//void convertNumtoChar(uint8_t input, uint8_t message[3]);


