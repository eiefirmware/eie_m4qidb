/**********************************************************************************************************************
File: configuration.h

Description:
Main header file for project.

***********************************************************************************************************************/

#ifndef __CONFIG_H
#define __CONFIG_H

#include <stdlib.h>
#include <string.h>
#include "typedefs.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "queue.h"

/* STM Libary header files */
//#include "stm32f4x7_eth.h"
//#include "stm32f4x7_eth_conf.h"
//#include "stm32f4xx_rcc.h"
//#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_adc.h"

/* EiE Proprietary header files */
#include "m4qidb-pcb-01.h"
#include "misc_io.h"
#include "utilities.h"

#include "debug_serial.h"
//#include "spi_agent.h"
#include "main_app.h"

#include "boardtest.h"



/**********************************************************************************************************************
Runtime switches
***********************************************************************************************************************/
#define DEBUG_MODE        1         /* Define to enable certain debugging code */

#define debugPrint(x)

#endif /* __CONFIG_H */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File */
/*--------------------------------------------------------------------------------------------------------------------*/

