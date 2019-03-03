/*
    FreeRTOS V7.2.0 - Copyright (C) 2012 Real Time Engineers Ltd.
*/

/**
 * This version of flash .c is for use on systems that have limited stack space
 * and no display facilities.  The complete version can be found in the
 * Demo/Common/Full directory.
 *
 * Three tasks are created, each of which flash an LED at a different rate.  The first
 * LED flashes every 200ms, the second every 400ms, the third every 600ms.
 *
 * The LED flash tasks provide instant visual feedback.  They show that the scheduler
 * is still operational.
 *
 */


#include "configuration.h"

/* Demo program include files. */
//#include "partest.h"
#include "flash.h"

#define ledSTACK_SIZE		configMINIMAL_STACK_SIZE
#define ledFLASH_RATE_BASE	( ( portTickType ) 2000 )

/* Variable used by the created tasks to calculate the LED number to use, and
the rate at which they should flash the LED. */
static volatile unsigned portBASE_TYPE uxFlashTaskNumber = 0;

/* The task that is created three times. */
static portTASK_FUNCTION_PROTO( vLEDFlashTask, pvParameters );

/*-----------------------------------------------------------*/

void vStartLEDFlashTasks( unsigned portBASE_TYPE uxPriority )
{
signed portBASE_TYPE xLEDTask;

	/* Create the tasks. */
	for( xLEDTask = 0; xLEDTask < 6; ++xLEDTask )
	{
		/* Spawn the task. */
		xTaskCreate( vLEDFlashTask, ( signed char * ) "LEDx", ledSTACK_SIZE, NULL, uxPriority, ( xTaskHandle * ) NULL );
	}
}
/*-----------------------------------------------------------*/

static portTASK_FUNCTION( vLEDFlashTask, pvParameters )
{
portTickType xFlashRate, xLastFlashTime;
unsigned portBASE_TYPE uxLED;

	/* The parameters are not used. */
	( void ) pvParameters;

	/* Calculate the LED and flash rate. */
	taskENTER_CRITICAL();
	{
		/* See which of the LED's we should use. */
		uxLED = uxFlashTaskNumber;

		/* Update so the next task uses the next LED. */
		uxFlashTaskNumber++;
	}
	taskEXIT_CRITICAL();

	xFlashRate = ledFLASH_RATE_BASE + ( ledFLASH_RATE_BASE * ( portTickType ) uxLED );
	xFlashRate /= portTICK_RATE_MS;

	/* We will turn the LED on and off again in the delay period, so each
	delay is only half the total period. */
	xFlashRate /= ( portTickType ) 2;

	/* We need to initialise xLastFlashTime prior to the first call to
	vTaskDelayUntil(). */
	xLastFlashTime = xTaskGetTickCount();

	for(;;)
	{
		/* Delay for half the flash period then turn the LED on. */
		vTaskDelayUntil( &xLastFlashTime, xFlashRate );
		EIE_LEDToggle( (Led_TypeDef)uxLED );

		/* Delay for half the flash period then turn the LED off. */
		vTaskDelayUntil( &xLastFlashTime, xFlashRate );
		EIE_LEDToggle( (Led_TypeDef)uxLED );
	}
} /*lint !e715 !e818 !e830 Function definition must be standard for task creation. */

