/******************************************************************************

 *****************************************************************************/

#include "configuration.h"

// Uncomment the following line to disable the buzzer during development
//#define NOSOUND


xQueueHandle xMiscIOIncomingQueue;

u8 MiscIOControl (MiscIOCommandStruct* MiscIOMessage)
{
    xQueueSendToBack(xMiscIOIncomingQueue, (void* )MiscIOMessage,
                     portMAX_DELAY);
    return (0);
}

/*
 * @brief  Starts the debugSerial driver task
 * @param  Task priority
 * @retval None
 */
void vStartMiscIOTask (unsigned portBASE_TYPE uxPriority)
{

    /* Spawn the task. */
    xTaskCreate(vMiscIOtask, (signed char * ) "MiscIO",
                configMINIMAL_STACK_SIZE, (void* ) NULL, uxPriority,
                (xTaskHandle * ) NULL);

    // G_xUsart1PeripheralMutex = xSemaphoreCreateMutex();
}

/*
 * @brief  Macro for debugSerial driver task
 * @param  task name,
 * @retval None
 */
static portTASK_FUNCTION( vMiscIOtask, pvParameters )
{
    xMiscIOIncomingQueue = xQueueCreate(MISCIO_QUEUE_LENGTH, sizeof(MiscIOCommandStruct));

    MiscIOCommandStruct stIncomingCommand;

    uint32_t param1, param2;

    //static uint32_t tickCounter;
    uint32_t ticksNow;

    DACInit ();

    memset (au32Timeouts, 0x00, sizeof(au32Timeouts));

    while (1)
    {

        if (xQueueReceive(xMiscIOIncomingQueue, &stIncomingCommand, 1)) /// 1000hz
        {
            param1 = stIncomingCommand.Param1; // function
            param2 = stIncomingCommand.Param2; // timeout ms

            switch (stIncomingCommand.FunctionType)
            {
                case LED0:
                    if (param1 & LED_RED)
                        EIE_LEDOn (LED_RED0);
                    else
                        EIE_LEDOff (LED_RED0);

                    if (param1 & LED_BLUE)
                        EIE_LEDOn (LED_BLUE0);
                    else
                        EIE_LEDOff (LED_BLUE0);

                    if (param1 & LED_GREEN)
                        EIE_LEDOn (LED_GREEN0);
                    else
                        EIE_LEDOff (LED_GREEN0);
                    break;

                case LED1:
                    if (param1 & LED_RED)
                        EIE_LEDOn (LED_RED1);
                    else
                        EIE_LEDOff (LED_RED1);

                    if (param1 & LED_BLUE)
                        EIE_LEDOn (LED_BLUE1);
                    else
                        EIE_LEDOff (LED_BLUE1);

                    if (param1 & LED_GREEN)
                        EIE_LEDOn (LED_GREEN1);
                    else
                        EIE_LEDOff (LED_GREEN1);
                    break;

                case BUZZER:
#ifdef NOSOUND                  
                    if (param1 > 0)
                        BuzzerInit (param1);
                    else
#endif                  
                        TIM_Cmd (TIM12, DISABLE);
                    break;

                default:
                    return;
            } // switch

            // If a timeout was supplied, set it
            if (param2 > 0)
                au32Timeouts[stIncomingCommand.FunctionType] = param2 + xTaskGetTickCount ();
        } // if Qreceive

        // see if it's time to do something
        ticksNow = xTaskGetTickCount ();

        // if there's a timeout value, set an event to disable the function
        for (uint8_t i = 0; i < NUM_FUNCTIONS; i++)
        {
            if ((au32Timeouts[i] > 0) && (ticksNow >= au32Timeouts[i]))
            {
                MiscIOCommandStruct stStop;

                au32Timeouts[i] = 0; // disable timeout
                stStop.FunctionType = (MiscIOFunctionEnum)i;
                stStop.Param1 = 0;
                stStop.Param2 = 0;

                MiscIOControl (&stStop);
            }
        }

    } // while(1)
}


void DACInit (void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitStructure;

    /* GPIOA clock enable (to be used with DAC) */
    RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA, ENABLE);

    /* DAC Periph clock enable */
    RCC_APB1PeriphClockCmd (RCC_APB1Periph_DAC, ENABLE);

    /* DAC channel 1 (DAC_OUT1 = PA.4) configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init (GPIOA, &GPIO_InitStructure);

    // DAC channel 2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init (GPIOA, &GPIO_InitStructure);

    /* DAC channel1 Configuration */
    DAC_StructInit (&DAC_InitStructure);
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_None; //DAC does not make use of a trigger
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None; //DAC does not generate any of the built-in waveforms
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable; //enables an extra output buffer to reduce output impedance
    DAC_Init (DAC_Channel_1, &DAC_InitStructure);              //initialize DAC1
    DAC_Init (DAC_Channel_2, &DAC_InitStructure);              //initialize DAC2

    /* Enable DAC Channel 1+2 with default settigs */
    DAC_SetChannel1Data (DAC_Align_12b_R, DAC1_DEFAULT);
    DAC_Cmd (DAC_Channel_1, ENABLE);
    DAC_SetChannel2Data (DAC_Align_12b_R, DAC2_DEFAULT);
    DAC_Cmd (DAC_Channel_2, ENABLE);

}

void BuzzerInit (uint32_t freq)
{

    RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOB, ENABLE);

    // init pin
    GPIO_InitTypeDef gpioStructure;
    gpioStructure.GPIO_Pin = GPIO_Pin_14;
    gpioStructure.GPIO_Mode = GPIO_Mode_AF;
    gpioStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init (GPIOB, &gpioStructure);

    // init Timer
    RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM12, ENABLE);

    TIM_TimeBaseInitTypeDef timerInitStructure;
    timerInitStructure.TIM_Prescaler = 4200 - 1; // 42MHz -> 10kHz
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = freq;  // 10kHz -> 500Hz
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit (TIM12, &timerInitStructure);
    TIM_Cmd (TIM12, ENABLE);

    // init PWMChannel
    TIM_OCInitTypeDef outputChannelInit = { 0, };
    outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
    outputChannelInit.TIM_Pulse = 8;
    outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
    outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init (TIM12, &outputChannelInit);
    TIM_OC1PreloadConfig (TIM12, TIM_OCPreload_Enable);

    GPIO_PinAFConfig (GPIOB, GPIO_PinSource14, GPIO_AF_TIM12);
}
