  /*
  ******************************************************************************
  * @file    misc_io.h
  *
  * @brief   
  ******************************************************************************
  */

#include "configuration.h"

/* Includes ------------------------------------------------------------------*/
//#include "stm32f4xx.h"

/* Hardware and starter kit includes. */
//#include "scic-ehdw-01.h"

#define MISC_IO_TASK_PRIORITY (mainREGULAR_TASK_PRIORITY)

typedef enum
{
  LED0,
  LED1,
  BUZZER,
  NUM_FUNCTIONS // always last
} MiscIOFunctionEnum;

static uint32_t au32Timeouts[NUM_FUNCTIONS];

typedef enum
{
  LED_OFF      = 0,
  LED_RED      = 1,
  LED_GREEN    = 2,
  LED_BLUE     = 4,
  LED_YELLOW   = LED_RED + LED_GREEN,
  LED_PURPLE   = LED_RED + LED_BLUE,
  LED_CYAN     = LED_GREEN + LED_BLUE,
  LED_WHITE    = LED_RED + LED_BLUE + LED_GREEN
} LEDColourEnum;


#define MISC_IO_TASK_PERIOD (configTICK_RATE_HZ / 10) // 1000 / 10 = 100ms

#define DAC1_DEFAULT (0)
#define DAC2_DEFAULT (0)

typedef struct
{
  MiscIOFunctionEnum FunctionType;
  uint32_t  Param1;
  uint32_t  Param2;
} MiscIOCommandStruct;

#define MISCIO_QUEUE_LENGTH (5)

void vStartMiscIOTask( unsigned portBASE_TYPE uxPriority );
void vMiscIOtask(void* pvParameters);

void DACInit(void);
void BuzzerInit(uint32_t);

// Public
u8 MiscIOControl(MiscIOCommandStruct* MiscIOMessage);
