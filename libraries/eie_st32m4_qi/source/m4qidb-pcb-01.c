/******************************************************************************
 * @file    m4qidb-pcb-01.c
 *
 * @brief   This file contains definitions for Leds, Buttons
 *          and COM ports hardware resources.
 ******************************************************************************/

#include "configuration.h"

/*******************************************************************************
 * LED GPIO DEFINITION
 *******************************************************************************/

GPIO_TypeDef* GPIO_PORT[TOTAL_LEDS] =
    { LED_RED0_GPIO_PORT,
    LED_GREEN0_GPIO_PORT,
    LED_BLUE0_GPIO_PORT,
    LED_RED1_GPIO_PORT,
    LED_GREEN1_GPIO_PORT,
    LED_BLUE1_GPIO_PORT };

const uint16_t GPIO_PIN[TOTAL_LEDS] =
    { LED_RED0_PIN,
    LED_GREEN0_PIN,
    LED_BLUE0_PIN,
    LED_RED1_PIN,
    LED_GREEN1_PIN,
    LED_BLUE1_PIN };

const uint32_t GPIO_CLK[TOTAL_LEDS] =
    { LED_RED0_GPIO_CLK,
    LED_GREEN0_GPIO_CLK,
    LED_BLUE0_GPIO_CLK,
    LED_RED1_GPIO_CLK,
    LED_GREEN1_GPIO_CLK,
    LED_BLUE1_GPIO_CLK, };

/*******************************************************************************
 * BUTTONS
 *******************************************************************************/

GPIO_TypeDef* BUTTON_PORT[BUTTONn] =
    { BUTTON0_GPIO_PORT,
    BUTTON1_GPIO_PORT };

const uint16_t BUTTON_PIN[BUTTONn] =
    { BUTTON0_PIN,
    BUTTON1_PIN };

const uint32_t BUTTON_CLK[BUTTONn] =
    { BUTTON0_GPIO_CLK,
    BUTTON1_GPIO_CLK };

const uint16_t BUTTON_EXTI_LINE[BUTTONn] =
    { BUTTON0_EXTI_LINE,
    BUTTON1_EXTI_LINE };

const uint16_t BUTTON_PORT_SOURCE[BUTTONn] =
    { BUTTON0_EXTI_PORT_SOURCE,
    BUTTON1_EXTI_PORT_SOURCE };

const uint16_t BUTTON_PIN_SOURCE[BUTTONn] =
    { BUTTON0_EXTI_PIN_SOURCE,
    BUTTON1_EXTI_PIN_SOURCE };

const uint16_t BUTTON_IRQn[BUTTONn] =
    { BUTTON0_EXTI_IRQn,
    BUTTON1_EXTI_IRQn };

#if 0
/*******************************************************************************
 * LCD GPIO configuraiton
 ********************************************************************************/
const uint16_t LCD_GPIO_PIN[LCD_PINn ] =
    { LCD_CS2_PIN, LCD_SCK2_PIN, LCD_MOSI2_PIN,
    LCD_RS_PIN, LCD_RESET_PIN, LCD_HEAT_PIN,
    LCD_BL_RED_PIN, LCD_BL_GRN_PIN, LCD_BL_BLU_PIN };

GPIO_TypeDef* LCD_GPIO_PORT[LCD_PINn ] =
    { LCD_CS2_GPIO_PORT, LCD_SCK2_GPIO_PORT, LCD_MOSI2_GPIO_PORT,
    LCD_RS_GPIO_PORT, LCD_RESET_GPIO_PORT, LCD_HEAT_GPIO_PORT,
    LCD_BL_RED_GPIO_PORT, LCD_BL_GRN_GPIO_PORT, LCD_BL_BLU_GPIO_PORT };

const uint32_t LCD_GPIO_CLK[LCD_PINn ] =
    { LCD_CS2_GPIO_CLK, LCD_SCK2_GPIO_CLK, LCD_MOSI2_GPIO_CLK,
    LCD_RS_GPIO_CLK, LCD_RESET_GPIO_CLK, LCD_HEAT_GPIO_CLK,
    LCD_BL_RED_GPIO_CLK, LCD_BL_GRN_GPIO_CLK, LCD_BL_BLU_GPIO_CLK };

const uint8_t LCD_GPIO_SOURCE[LCD_PINn ] =
    { LCD_CS2_SOURCE, LCD_SCK2_SOURCE, LCD_MOSI2_SOURCE,
    LCD_RS_SOURCE, LCD_RESET_SOURCE, LCD_HEAT_SOURCE,
    LCD_BL_RED_SOURCE, LCD_BL_GRN_SOURCE, LCD_BL_BLU_SOURCE };

const GPIOMode_TypeDef LCD_GPIO_MODE[LCD_PINn ] =
    { LCD_CS2_MODE, LCD_SCK2_MODE, LCD_MOSI2_MODE,
    LCD_RS_MODE, LCD_RESET_MODE, LCD_HEAT_MODE,
    LCD_BL_RED_MODE, LCD_BL_GRN_MODE, LCD_BL_BLU_MODE };

const uint8_t LCD_GPIO_AF[LCD_PINn ] =
    { LCD_CS2_AF, LCD_SCK2_AF, LCD_MOSI2_AF,
    LCD_RS_AF, LCD_RESET_AF, LCD_HEAT_AF,
    LCD_BL_RED_AF, LCD_BL_GRN_AF, LCD_BL_BLU_AF };

const GPIOSpeed_TypeDef LCD_GPIO_SPEED[LCD_PINn ] =
    { LCD_CS2_SPEED, LCD_SCK2_SPEED, LCD_MOSI2_SPEED,
    LCD_RS_SPEED, LCD_RESET_SPEED, LCD_HEAT_SPEED,
    LCD_BL_RED_SPEED, LCD_BL_GRN_SPEED, LCD_BL_BLU_SPEED };

const GPIOOType_TypeDef LCD_GPIO_OTYPE[LCD_PINn ] =
    { LCD_CS2_OTYPE, LCD_SCK2_OTYPE, LCD_MOSI2_OTYPE,
    LCD_RS_OTYPE, LCD_RESET_OTYPE, LCD_HEAT_OTYPE,
    LCD_BL_RED_OTYPE, LCD_BL_GRN_OTYPE, LCD_BL_BLU_OTYPE };

const GPIOPuPd_TypeDef LCD_GPIO_PUPD[LCD_PINn ] =
    { LCD_CS2_PUPD, LCD_SCK2_PUPD, LCD_MOSI2_PUPD,
    LCD_RS_PUPD, LCD_RESET_PUPD, LCD_HEAT_PUPD,
    LCD_BL_RED_PUPD, LCD_BL_GRN_PUPD, LCD_BL_BLU_PUPD };



/*------------------------------------------------------------------------------
 Function: LCD_GPIO_Init

 Description: Configures the hardware pins for the LCD including the control lines,
 backlight LEDs, and SPI.

 Requires:
 - Pins used are exclusively for LCD operation and do not require alternate configurations
 *   This parameter can be one of following parameters:
 *     @arg LCD_CS1,
 *     @arg LCD_SCK1,
 *     @arg LCD_MOSI1,
 *     @arg LCD_RS,
 *     @arg LCD_RESET,
 *     @arg LCD_HEAT,
 *     @arg LCD_BL_RED,
 *     @arg LCD_BL_GRN,
 *     @arg LCD_BL_BLU

 Promises:
 - All GPIO pins required for LCD operation are configured.
 */
void
EIE_LCD_GPIO_Init (void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    for (u8 i = 0; i < LCD_PINn ; i++)
    {
        /* Enable the GPIO_LCD Clock */
        RCC_AHB1PeriphClockCmd (LCD_GPIO_CLK[i], ENABLE);

        /* Configure the GPIO pin */
        GPIO_InitStructure.GPIO_Pin = LCD_GPIO_PIN[i];
        GPIO_InitStructure.GPIO_Mode = LCD_GPIO_MODE[i];
        GPIO_InitStructure.GPIO_Speed = LCD_GPIO_SPEED[i];
        GPIO_InitStructure.GPIO_OType = LCD_GPIO_OTYPE[i];
        GPIO_InitStructure.GPIO_PuPd = LCD_GPIO_PUPD[i];

        GPIO_Init (LCD_GPIO_PORT[i], &GPIO_InitStructure);

        /* Select the alternate function for the pin if applicable */
        if (LCD_GPIO_MODE[i] == GPIO_Mode_AF)
        {
            GPIO_PinAFConfig (LCD_GPIO_PORT[i], LCD_GPIO_SOURCE[i],
                              LCD_GPIO_AF[i]);
        }
    }

    /* Set the startup state for all pins */
    LCD_RESET_ASSERT();
    LCD_CS_DEASSERT();
    LcdSetBacklight (LCD_LIGHT_OFF);
    LCD_HEATER_OFF();

} /* end EIE_LCD_GPIO_Init() */
#endif

/*------------------------------------------------------------------------------
 Function: EIE_Misc_GPIO_Init

 Description: Configures hardware pins for various signals in the system that are not grouped elsewhere.

 Requires:
 -

 Promises:
 - The following GPIO pins are configured:
 - Tick output for heartbeat LED
 */
void
EIE_Misc_GPIO_Init (void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Tick pin configuration: */
    /* Enable the GPIO_LED Clock */
    RCC_AHB1PeriphClockCmd (TICK_GPIO_CLK, ENABLE);

    /* Configure the GPIO pin */
    GPIO_InitStructure.GPIO_Pin = TICK_PIN;
    GPIO_InitStructure.GPIO_Mode = TICK_MODE;
    GPIO_InitStructure.GPIO_Speed = TICK_SPEED;
    GPIO_InitStructure.GPIO_OType = TICK_OTYPE;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init (TICK_PORT, &GPIO_InitStructure);

} /* end EIE_LCD_GPIO_Init() */

#if 0
/*------------------------------------------------------------------------------
 Function: SPI2_Init

 Description: Sets up SPI2 for use with the Newhaven NHD-C128641Z LCD screen.


 Requires:
 - GPIO pins have been set up for SPI mode.

 Promises:
 - SPI2 peripheral is set up and ready for LCD communications
 */
void
SPI2_Init (void)
{
    SPI_InitTypeDef SPI2_InitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Set all the peripheral config values */
    SPI2_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI2_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI2_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI2_InitStruct.SPI_CPOL = SPI_CPOL_High;
    SPI2_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
    SPI2_InitStruct.SPI_NSS = SPI_NSS_Soft;
    SPI2_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI2_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI2_InitStruct.SPI_CRCPolynomial = 7;

    /* Activate peripheral clock and configure the SPI2 peripheral */
    RCC_APB1PeriphClockCmd (RCC_APB1Periph_SPI2, ENABLE);
    SPI_Init (SPI2, &SPI2_InitStruct);

    /* Configure and enable interrupts */
    NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =
            configLIBRARY_LOWEST_INTERRUPT_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init (&NVIC_InitStructure);

    SPI_I2S_ITConfig (SPI2, SPI_I2S_IT_TXE, ENABLE);
    //SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);

    /* All is ready - enable SPI2 */
    SPI_Cmd (SPI2, ENABLE);

} /* end SPI2_Init() */
#endif


/*******************************************************************************
 * COM
 *******************************************************************************/

USART_TypeDef* COM_USART[COMn] =
    { EVAL_COM3 };

GPIO_TypeDef* COM_TX_PORT[COMn] =
    { EVAL_COM3_TX_GPIO_PORT };

GPIO_TypeDef* COM_RX_PORT[COMn] =
    { EVAL_COM3_RX_GPIO_PORT };

const uint32_t COM_USART_CLK[COMn] =
    { EVAL_COM3_CLK };

const uint32_t COM_TX_PORT_CLK[COMn] =
    { EVAL_COM3_TX_GPIO_CLK };

const uint32_t COM_RX_PORT_CLK[COMn] =
    { EVAL_COM3_RX_GPIO_CLK };

const uint16_t COM_TX_PIN[COMn] =
    { EVAL_COM3_TX_PIN };

const uint16_t COM_RX_PIN[COMn] =
    { EVAL_COM3_RX_PIN };

const uint16_t COM_TX_PIN_SOURCE[COMn] =
    { EVAL_COM3_TX_SOURCE };

const uint16_t COM_RX_PIN_SOURCE[COMn] =
    { EVAL_COM3_RX_SOURCE };

const uint16_t COM_TX_AF[COMn] =
    { EVAL_COM3_TX_AF };

const uint16_t COM_RX_AF[COMn] =
    { EVAL_COM3_RX_AF };

NVIC_InitTypeDef NVIC_InitStructure;

/******************************************************************************
 * GPIO FUNCTIONS
 *******************************************************************************/

/******************************************************************************
 * @brief  RESETS GPIO
 * stm CODE
 *****************************************/
void
EIE_GPIOReset (void)
{
    GPIO_DeInit (GPIOA);
    GPIO_DeInit (GPIOB);
    GPIO_DeInit (GPIOC);
    GPIO_DeInit (GPIOD);
    GPIO_DeInit (GPIOE);
    GPIO_DeInit (GPIOF);
    GPIO_DeInit (GPIOG);
    GPIO_DeInit (GPIOH);
    GPIO_DeInit (GPIOI);
}

/******************************************************************************
 * LED FUNCTIONS
 *******************************************************************************/

/******************************************************************************
 * @brief  Configures one LED GPIO.
 * @param  Led: Specifies the Led to be configured.
 *   This parameter can be one of following parameters:
 *     @arg LED_RED,
 *     @arg LED_GREEN,
 *     @arg LED_BLUE,
 *     @arg LED_YELLOW,
 *     @arg LED_HP0,
 *     @arg LED_HP1,
 *     @arg LED_HP2,
 *     @arg LED_HP3
 * @retval None
 *****************************************/
void EIE_LEDInit (Led_TypeDef Led)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable the GPIO_LED Clock */
    RCC_AHB1PeriphClockCmd (GPIO_CLK[Led], ENABLE);

    /* Configure the GPIO_LED pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Led];
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init (GPIO_PORT[Led], &GPIO_InitStructure);
}

/******************************************************************************
 * @brief  Configures ALL LED GPIO.
 * @param  Led: Specifies the Led to be configured.
 *   This parameter can be one of following parameters:
 *
 * @retval None
 *****************************************/
void EIE_LEDInit_All (void)
{
    EIE_LEDInit (LED_RED0);
    EIE_LEDInit (LED_GREEN0);
    EIE_LEDInit (LED_BLUE0);
    EIE_LEDInit (LED_RED1);
    EIE_LEDInit (LED_GREEN1);
    EIE_LEDInit (LED_BLUE1);

}

/******************************************************************************
 * @brief  Turns selected LED On.
 * @param  Led: Specifies the Led to be set on.
 *   This parameter can be one of following parameters:
 *     @arg LED_RED,
 *     @arg LED_GREEN,
 *     @arg LED_BLUE,
 *     @arg LED_YELLOW,
 *     @arg LED_HP0,
 *     @arg LED_HP1,
 *     @arg LED_HP2,
 *     @arg LED_HP3
 * @retval None
 *****************************************/
void EIE_LEDOn (Led_TypeDef Led)
{
    GPIO_PORT[Led]->BSRRL = GPIO_PIN[Led];
}

/******************************************************************************
 * @brief  Turns selected LED Off.
 * @param  Led: Specifies the Led to be set off.
 *   This parameter can be one of following parameters:
 *     @arg LED_RED,
 *     @arg LED_GREEN,
 *     @arg LED_BLUE,
 *     @arg LED_YELLOW,
 *     @arg LED_HP0,
 *     @arg LED_HP1,
 *     @arg LED_HP2,
 *     @arg LED_HP3
 * @retval None
 *****************************************/
void EIE_LEDOff (Led_TypeDef Led)
{
    GPIO_PORT[Led]->BSRRH = GPIO_PIN[Led];
}

/******************************************************************************
 * @brief  Toggles the selected LED.
 * @param  Led: Specifies the Led to be toggled.
 *   This parameter can be one of following parameters:
 *     @arg LED_RED,
 *     @arg LED_GREEN,
 *     @arg LED_BLUE,
 *     @arg LED_YELLOW,
 *     @arg LED_HP0,
 *     @arg LED_HP1,
 *     @arg LED_HP2,
 *     @arg LED_HP3
 * @retval None
 *****************************************/
void EIE_LEDToggle (Led_TypeDef Led)
{
    taskENTER_CRITICAL();
    GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led]; /* Read-modify-write cannot be interrupted */
    taskEXIT_CRITICAL();
}

/******************************************************************************
 * BUTTON FUNCTIONS
 *******************************************************************************/

/**
 * @brief  Configures Button GPIO and EXTI Line.
 * @param  Button: Specifies the Button to be configured.
 *   This parameter can be one of following parameters:
 *     @arg BUTTON_WAKEUP: Wakeup Push Button
 *     @arg BUTTON_TAMPER: Tamper Push Button
 *     @arg BUTTON_KEY: Key Push Button
 *     @arg BUTTON_RIGHT: Joystick Right Push Button
 *     @arg BUTTON_LEFT: Joystick Left Push Button
 *     @arg BUTTON_UP: Joystick Up Push Button
 *     @arg BUTTON_DOWN: Joystick Down Push Button
 *     @arg BUTTON_SEL: Joystick Sel Push Button
 * @param  Button_Mode: Specifies Button mode.
 *   This parameter can be one of following parameters:
 *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO
 *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
 *                     generation capability
 * @retval None
 */
void EIE_PBInit (Button_TypeDef Button, ButtonMode_TypeDef Button_Mode, u8 u8PullUp)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable the BUTTON Clock */
    RCC_AHB1PeriphClockCmd (BUTTON_CLK[Button], ENABLE);
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_SYSCFG, ENABLE);

    /* Configure Button pin as input */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;

    if (u8PullUp)
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    else
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_InitStructure.GPIO_Pin = BUTTON_PIN[Button];
    GPIO_Init (BUTTON_PORT[Button], &GPIO_InitStructure);

    if (Button_Mode == BUTTON_MODE_EXTI)
    {
        /* Connect Button EXTI Line to Button GPIO Pin */
        SYSCFG_EXTILineConfig (BUTTON_PORT_SOURCE[Button],
                               BUTTON_PIN_SOURCE[Button]);

        /* Configure Button EXTI line */
        EXTI_InitStructure.EXTI_Line = BUTTON_EXTI_LINE[Button];
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;

        if (1)  //Button != BUTTON_WAKEUP)
        {
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
        }
        else
        {
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
        }
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_Init (&EXTI_InitStructure);

        /* Enable and set Button EXTI Interrupt to the lowest priority */
        NVIC_InitStructure.NVIC_IRQChannel = BUTTON_IRQn[Button];
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

        NVIC_Init (&NVIC_InitStructure);
    }
}

/******************************************************************************
 * @brief  Configures ALL LED GPIO.
 * @param  Led: Specifies the Led to be configured.
 *   This parameter can be one of following parameters:
 *
 * @retval None
 *****************************************/
void EIE_ButtonInit_All (void)
{
    EIE_PBInit (BUTTON_LEFT, BUTTON_MODE_EXTI, false);                // EXTI 10
    EIE_PBInit (BUTTON_RIGHT, BUTTON_MODE_EXTI, false);               // EXTI 13
}

/**
 * @brief  Returns the selected Button state.
 * @param  Button: Specifies the Button to be checked.
 *   This parameter can be one of following parameters:
 *     @arg BUTTON_WAKEUP: Wakeup Push Button
 *     @arg BUTTON_TAMPER: Tamper Push Button
 *     @arg BUTTON_KEY: Key Push Button
 *     @arg BUTTON_RIGHT: Joystick Right Push Button
 *     @arg BUTTON_LEFT: Joystick Left Push Button
 *     @arg BUTTON_UP: Joystick Up Push Button
 *     @arg BUTTON_DOWN: Joystick Down Push Button
 *     @arg BUTTON_SEL: Joystick Sel Push Button
 * @retval The Button GPIO pin value.
 */
uint32_t
EIE_PBGetState (Button_TypeDef Button)
{
    return GPIO_ReadInputDataBit (BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/******************************************************************************
 * COM FUNCTIONS
 *******************************************************************************/

/**
 * @brief  Configures COM port.
 * @param  COM: Specifies the COM port to be configured.
 *   This parameter can be one of following parameters:
 *     @arg COM1
 *     @arg COM2
 * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure that
 *   contains the configuration information for the specified USART peripheral.
 * @retval None
 */
void
EIE_COMInit (COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd (COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM],
                            ENABLE);

    if (COM == COM3)
    {
        /* Enable UART clock */
        RCC_APB1PeriphClockCmd (COM_USART_CLK[COM], ENABLE);
    }

    /* Connect PXx to USARTx_Tx*/
    GPIO_PinAFConfig (COM_TX_PORT[COM], COM_TX_PIN_SOURCE[COM], COM_TX_AF[COM]);

    /* Connect PXx to USARTx_Rx*/
    GPIO_PinAFConfig (COM_RX_PORT[COM], COM_RX_PIN_SOURCE[COM], COM_RX_AF[COM]);

    /* Configure USART Tx as alternate function  */
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

    GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init (COM_TX_PORT[COM], &GPIO_InitStructure);

    /* Configure USART Rx as alternate function  */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
    GPIO_Init (COM_RX_PORT[COM], &GPIO_InitStructure);

    /* USART configuration */
    USART_Init (COM_USART[COM], USART_InitStruct);

    /* Enable USART */
    USART_Cmd (COM_USART[COM], ENABLE);
}

/******************************************************************************
 * @brief  Configures Clock out pin.
 * @param  None

 * @retval None
 *****************************************/
void
Clock_Out_Init (void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable the GPIO_LED Clock */
    RCC_AHB1PeriphClockCmd (MCO1_GPIO_CLK, ENABLE);

    /* Select the alternate function for the pin */
    GPIO_PinAFConfig (MCO1_PORT, MCO1_PIN, MCO1_PIN_AF);

    /* Configure the GPIO pin */
    GPIO_InitStructure.GPIO_Pin = MCO1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

    GPIO_Init (MCO1_PORT, &GPIO_InitStructure);
}

/*****END OF FILE****/
