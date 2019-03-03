/**
  ******************************************************************************
  * @file    system_stm32f4xx.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    30-September-2011
  * @brief   CMSIS Cortex-M4 Device System Source File for STM32F4xx devices.
  ******************************************************************************/

#ifndef __SYSTEM_STM32F4XX_H
#define __SYSTEM_STM32F4XX_H


/*******************************************************************************
Function prototypes
********************************************************************************/

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

extern void Clock_Out_Init(void);          /* From scic-ehdw-01.c */



#endif /*__SYSTEM_STM32F4XX_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
