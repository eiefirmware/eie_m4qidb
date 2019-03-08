/**
  ******************************************************************************
  * @file    m4qidb-pcb-01.h
  *
  * @brief   This file contains definitions for Leds, buttons,
  *          and COM ports hardware resources.
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __M4QIDB_PCB_H
#define __M4QIDB_PCB_H


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"


/*******************************************************************************
* TYPEDEFS
*******************************************************************************/


/*******************************************************************************
* LED GPIO TYPEDEFS
*******************************************************************************/

 typedef enum
{
  LED_RED0   = 0,
  LED_GREEN0 = 1,
  LED_BLUE0  = 2,
  LED_RED1   = 3,
  LED_GREEN1 = 4,
  LED_BLUE1  = 5,
  TOTAL_LEDS = 6
} Led_TypeDef;

//#define TOTAL_LEDS		8



/*******************************************************************************
* BUTTON TYPEDEFS
*******************************************************************************/

typedef enum
{
  BUTTON_LEFT  = 0,
  BUTTON_RIGHT = 1,
} Button_TypeDef;


typedef enum
{
  IRQ_BUTTON_LEFT = 10,
  IRQ_BUTTON_RIGHT = 13,
} IRQButton_TypeDef;


typedef enum
{
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;



/*******************************************************************************
* SPI TYPEDEFS
*******************************************************************************/
/*typedef enum
{
  SPI1 = 1,
  SPI2 = 2,
  SPI3 = 3
} SPI_TypeDef;
*/


/*******************************************************************************
* COM TYPEDEFS
* EDITED BY
*******************************************************************************/
typedef enum
{
  COM3 = 0
} COM_TypeDef;


/*******************************************************************************
* DEFINITIONS
*******************************************************************************/

/*******************************************************************************
* LED DEFINITIONS
*******************************************************************************/

//REGULAR LEDs

#define LED_RED0_PIN                       GPIO_Pin_6
#define LED_RED0_GPIO_PORT                 GPIOA
#define LED_RED0_GPIO_CLK                  RCC_AHB1Periph_GPIOA

#define LED_GREEN0_PIN                     GPIO_Pin_7
#define LED_GREEN0_GPIO_PORT               GPIOA
#define LED_GREEN0_GPIO_CLK                RCC_AHB1Periph_GPIOA

#define LED_BLUE0_PIN                      GPIO_Pin_4
#define LED_BLUE0_GPIO_PORT                GPIOC
#define LED_BLUE0_GPIO_CLK                 RCC_AHB1Periph_GPIOC

#define LED_RED1_PIN                       GPIO_Pin_1
#define LED_RED1_GPIO_PORT                 GPIOE
#define LED_RED1_GPIO_CLK                  RCC_AHB1Periph_GPIOE

#define LED_GREEN1_PIN                     GPIO_Pin_0
#define LED_GREEN1_GPIO_PORT               GPIOE
#define LED_GREEN1_GPIO_CLK                RCC_AHB1Periph_GPIOE

#define LED_BLUE1_PIN                      GPIO_Pin_9
#define LED_BLUE1_GPIO_PORT                GPIOB
#define LED_BLUE1_GPIO_CLK                 RCC_AHB1Periph_GPIOB




/*******************************************************************************
* BUTTON DEFINITIONS
*******************************************************************************/

#define BUTTONn                    2 //NUMBER OF BUTTONS

/* BUTTON0 = LEFT */
#define BUTTON0_PIN                GPIO_Pin_10  /* Bit 10 */
#define BUTTON0_GPIO_PORT          GPIOD /* base address of GPIOD */
#define BUTTON0_GPIO_CLK           RCC_AHB1Periph_GPIOD
#define BUTTON0_EXTI_LINE          EXTI_Line10  /* Bit 10 */
#define BUTTON0_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOD  /* 0x03 */
#define BUTTON0_EXTI_PIN_SOURCE    EXTI_PinSource10 /* 10 */
#define BUTTON0_EXTI_IRQn          EXTI15_10_IRQn               //Interrupt number MODIFY

#define BUTTON1_PIN                GPIO_Pin_13
#define BUTTON1_GPIO_PORT          GPIOD
#define BUTTON1_GPIO_CLK           RCC_AHB1Periph_GPIOD
#define BUTTON1_EXTI_LINE          EXTI_Line13
#define BUTTON1_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOD
#define BUTTON1_EXTI_PIN_SOURCE    EXTI_PinSource13
#define BUTTON1_EXTI_IRQn          EXTI15_10_IRQn              //MODIFY


/**
 * DEMO CODE

#define WAKEUP_BUTTON_PIN                GPIO_Pin_0
#define WAKEUP_BUTTON_GPIO_PORT          GPIOA
#define WAKEUP_BUTTON_GPIO_CLK           RCC_AHB1Periph_GPIOA
#define WAKEUP_BUTTON_EXTI_LINE          EXTI_Line0
#define WAKEUP_BUTTON_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOA
#define WAKEUP_BUTTON_EXTI_PIN_SOURCE    EXTI_PinSource0
#define WAKEUP_BUTTON_EXTI_IRQn          EXTI0_IRQn

*/

/*******************************************************************************
* COM DEFINITIONS
*******************************************************************************/
/** @addtogroup IAR_STM32F407ZG_SK_LOW_LEVEL_COM
  * @{
  */
#define COMn                             1


/**
 * @brief Definition for COM port3, connected to USART3
 */
#define EVAL_COM3                        USART3
#define EVAL_COM3_CLK                    RCC_APB1Periph_USART3

#define EVAL_COM3_TX_PIN                 GPIO_Pin_8
#define EVAL_COM3_TX_GPIO_PORT           GPIOD
#define EVAL_COM3_TX_GPIO_CLK            RCC_AHB1Periph_GPIOD
#define EVAL_COM3_TX_SOURCE              GPIO_PinSource8
#define EVAL_COM3_TX_AF                  GPIO_AF_USART3

#define EVAL_COM3_RX_PIN                 GPIO_Pin_9
#define EVAL_COM3_RX_GPIO_PORT           GPIOD
#define EVAL_COM3_RX_GPIO_CLK            RCC_AHB1Periph_GPIOD
#define EVAL_COM3_RX_SOURCE              GPIO_PinSource9
#define EVAL_COM3_RX_AF                  GPIO_AF_USART3

#define EVAL_COM3_RTS_PIN                GPIO_Pin_12
#define EVAL_COM3_RTS_GPIO_PORT          GPIOD
#define EVAL_COM3_RTS_GPIO_CLK           RCC_AHB1Periph_GPIOD
#define EVAL_COM3_RTS_SOURCE             GPIO_PinSource12
#define EVAL_COM3_RTS_AF                 GPIO_AF_USART3

#define EVAL_COM3_CTS_PIN                GPIO_Pin_11
#define EVAL_COM3_CTS_GPIO_PORT          GPIOD
#define EVAL_COM3_CTS_GPIO_CLK           RCC_AHB1Periph_GPIOD
#define EVAL_COM3_CTS_SOURCE             GPIO_PinSource11
#define EVAL_COM3_CTS_AF                 GPIO_AF_USART3

#define EVAL_COM3_IRQn                   USART3_IRQn


/*******************************************************************************
* LCD PIN DEFINITIONS
*******************************************************************************/


/*******************************************************************************
* BUZZER DEFINITIONS
*******************************************************************************/
#define BUZZER_GPIO_PIN                  GPIO_Pin_14
#define BUZZER_GPIO_PORT                 GPIOB
#define BUZZER_GPIO_CLK                  RCC_AHB1Periph_GPIOB
#define BUZZER_PIN_SOURCE                GPIO_PinSource14
#define BUZZER_TIM                       TIM1
#define RCC_APB2PERIPH_BUZZER_TIM        RCC_APB2Periph_TIM1
#define BUZZER_PIN_AF                    GPIO_AF_TIM1



/*******************************************************************************
* DAC DEFINITIONS
*
*******************************************************************************/
#define DAC1_GPIO_PIN                  GPIO_Pin_4
#define DAC1_GPIO_PORT                 GPIOA
#define DAC1_GPIO_CLK                  RCC_AHB1Periph_GPIOA
#define DAC1_PIN_SOURCE                GPIO_PinSource4
//#define DAC1_TIM                       TIM1
//#define RCC_APB2PERIPH_DAC1_TIM        RCC_APB2Periph_TIM1
//#define DAC1_PIN_AF                    GPIO_AF_TIM1

#define DAC2_GPIO_PIN                  GPIO_Pin_5
#define DAC2_GPIO_PORT                 GPIOA
#define DAC2_GPIO_CLK                  RCC_AHB1Periph_GPIOA
#define DAC2_PIN_SOURCE                GPIO_PinSource5
//#define DAC2_TIM                       TIM1
//#define RCC_APB2PERIPH_DAC2_TIM        RCC_APB2Periph_TIM1
//#define DAC2_PIN_AF                    GPIO_AF_TIM1



/*******************************************************************************
* External IO pin defintions
*******************************************************************************/

#define EXT_IO1_PIN                       GPIO_Pin_13
#define EXT_IO1_GPIO_PORT                 GPIOE
#define EXT_IO1_GPIO_CLK                  RCC_AHB1Periph_GPIOE

#define EXT_IO2_PIN                       GPIO_Pin_9
#define EXT_IO2_GPIO_PORT                 GPIOE
#define EXT_IO2_GPIO_CLK                  RCC_AHB1Periph_GPIOE

// TODO ANALOGUE IN 1+2

/*******************************************************************************
* Miscellaneous pin defintions
*******************************************************************************/
#define MCO1_PIN                          GPIO_Pin_8
#define MCO1_PORT                         GPIOA
#define MCO1_GPIO_CLK                     RCC_AHB1Periph_GPIOA
#define MCO1_SOURCE                       GPIO_PinSource9
#define MCO1_PIN_AF                       GPIO_AF_MCO

#define TICK_PORT                         GPIOC
#define TICK_GPIO_CLK                     RCC_AHB1Periph_GPIOC
#define TICK_PIN                          GPIO_Pin_9
#define TICK_MODE                         GPIO_Mode_OUT
#define TICK_SPEED                        GPIO_Speed_2MHz
#define TICK_SOURCE                       GPIO_PinSource9
#define TICK_OTYPE                        GPIO_OType_PP
#define TICK_PIN_PUPD                     GPIO_PuPd_NOPULL

#if 0
/*******************************************************************************
* USB OTG DEFINITIONS
*******************************************************************************/
#define OTG_FS_VBUS_PIN                    GPIO_Pin_9
#define OTG_FS_VBUS_PORT                   GPIOA
#define OTG_FS_VBUS_CLK                    RCC_AHB1Periph_GPIOA
#define OTG_FS_VBUS_SOURCE                 GPIO_PinSource9

#define USB_FS_VBUSON_PIN                  GPIO_Pin_2
#define USB_FS_VBUSON_PORT                 GPIOC
#define USB_FS_VBUSON_CLK                  RCC_AHB1Periph_GPIOC
#define USB_FS_VBUSON_SOURCE               GPIO_PinSource2

#define USB_FS_FAULT_PIN                   GPIO_Pin_10
#define USB_FS_FAULT_PORT                  GPIOB
#define USB_FS_FAULT_CLK                   RCC_AHB1Periph_GPIOB
#define USB_FS_FAULT_SOURCE                GPIO_PinSource10


/*******************************************************************************
* USB HOST DEFINITIONS
*******************************************************************************/
#define OTG_HS_VBUS_PIN                    GPIO_Pin_13
#define OTG_HS_VBUS_PORT                   GPIOB
#define OTG_HS_VBUS_CLK                    RCC_AHB1Periph_GPIOB
#define OTG_HS_VBUS_SOURCE                 GPIO_PinSource13

#define USB_HS_VBUSON_PIN                  GPIO_Pin_3
#define USB_HS_VBUSON_PORT                 GPIOE
#define USB_HS_VBUSON_CLK                  RCC_AHB1Periph_GPIOE
#define USB_HS_VBUSON_SOURCE               GPIO_PinSource3

#define USB_HS_FAULT_PIN                   GPIO_Pin_13
#define USB_HS_FAULT_PORT                  GPIOD
#define USB_HS_FAULT_CLK                   RCC_AHB1Periph_GPIOD
#define USB_HS_FAULT_SOURCE                GPIO_PinSource13

#define OTG_HS_ID_PIN                      GPIO_Pin_12
#define OTG_HS_ID_PORT                     GPIOB
#define OTG_HS_ID_CLK                      RCC_AHB1Periph_GPIOB
#define OTG_HS_ID_SOURCE                   GPIO_PinSource12

#endif

/*****************************************************************
* @defgroup IAR_STM32F407ZG_SK_LOW_LEVEL_Exported_Functions
* from ST
*****************************************************************/

/*******************************************************************************
* LED FUNCTIONS
*******************************************************************************/
void EIE_LEDInit_All(void);
void EIE_LEDInit(Led_TypeDef Led);
void EIE_LEDOn(Led_TypeDef Led);
void EIE_LEDOff(Led_TypeDef Led);
void EIE_LEDToggle(Led_TypeDef Led);


/*******************************************************************************
* BUTTON FUNCTIONS
*******************************************************************************/
void EIE_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode, u8 u8PullUp);
uint32_t EIE_PBGetState(Button_TypeDef Button);


/*******************************************************************************
* SPI FUNCTIONS
*******************************************************************************/
//void SPI1_Definitions();
//void SPI_Definitions();
//void SPI_Init(void);


/*******************************************************************************
* COM FUNCTIONS
*******************************************************************************/
void EIE_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct);


/*******************************************************************************
* MISC FUNCTIONS
*******************************************************************************/
void Clock_Out_Init(void);
void EIE_ButtonInit_All (void);
void EIE_Misc_GPIO_Init(void);


/*******************************************************************************
* CLOSING DETAILS
*******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __M4QIDB_PCB_H */


/************************END OF FILE********************************************/
