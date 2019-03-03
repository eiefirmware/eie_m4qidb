/*
    FreeRTOS V7.2.0 - Copyright (C) 2012 Real Time Engineers Ltd.


 ******************************************************************************
 * >>>>>> NOTE 1: <<<<<<
 *
 * main() can be configured to create either a very simple LED flasher demo, or
 * a more comprehensive test/demo application.
 *
 * To create a very simple LED flasher example, set the
 * mainCREATE_SIMPLE_LED_FLASHER_DEMO_ONLY constant (defined below) to 1.  When
 * this is done, only the standard demo flash tasks are created.  The standard
 * demo flash example creates three tasks, each of which toggle an LED at a
 * fixed but different frequency.
 *
 * To create a more comprehensive test and demo application, set
 * mainCREATE_SIMPLE_LED_FLASHER_DEMO_ONLY to 0.
 *
 * >>>>>> NOTE 2: <<<<<<
 *
 * In addition to the normal set of standard demo tasks, the comprehensive test
 * makes heavy use of the floating point unit, and forces floating point
 * instructions to be used from interrupts that nest three deep.  The nesting
 * starts from the tick hook function, resulting is an abnormally long context
 * switch time.  This is done purely to stress test the FPU context switching
 * implementation, and that part of the test can be removed by setting
 * configUSE_TICK_HOOK to 0 in FreeRTOSConfig.h.
 ******************************************************************************
 *
 * main() creates all the demo application tasks and software timers, then starts
 * the scheduler.  The web documentation provides more details of the standard
 * demo application tasks, which provide no particular functionality, but do
 * provide a good example of how to use the FreeRTOS API.
 *
 * In addition to the standard demo tasks, the following tasks and tests are
 * defined and/or created within this file:
 *
 * "Reg test" tasks - These fill both the core and floating point registers with
 * known values, then check that each register maintains its expected value for
 * the lifetime of the task.  Each task uses a different set of values.  The reg
 * test tasks execute with a very low priority, so get preempted very
 * frequently.  A register containing an unexpected value is indicative of an
 * error in the context switching mechanism.
 *
 * "Check" timer - The check software timer period is initially set to three
 * seconds.  The callback function associated with the check software timer
 * checks that all the standard demo tasks, and the register check tasks, are
 * not only still executing, but are executing without reporting any errors.  If
 * the check software timer discovers that a task has either stalled, or
 * reported an error, then it changes its own execution period from the initial
 * three seconds, to just 200ms.  The check software timer callback function
 * also toggles an LED each time it is called.  This provides a visual
 * indication of the system status:  If the LED toggles every three seconds,
 * then no issues have been discovered.  If the LED toggles every 200ms, then
 * an issue has been discovered with at least one task.
 *
 * Tick hook - The application tick hook is called from the schedulers tick
 * interrupt service routine when configUSE_TICK_HOOK is set to 1 in
 * FreeRTOSConfig.h.  In this example, the tick hook is used to test the kernels
 * handling of the floating point units (FPU) context, both at the task level
 * and when nesting interrupts access the floating point unit registers.  The
 * tick hook function first fills the FPU registers with a known value, it
 * then triggers a medium priority interrupt.  The medium priority interrupt
 * fills the FPU registers with a different value, and triggers a high priority
 * interrupt.  The high priority interrupt once again fills the the FPU
 * registers with a known value before returning to the medium priority
 * interrupt.  The medium priority interrupt checks that the FPU registers
 * contain the values that it wrote to them, then returns to the tick hook
 * function.  Finally, the tick hook function checks that the FPU registers
 * contain the values that it wrote to them, before it too returns.
 *
 * Button interrupt - The button marked "USER" on the starter kit is used to
 * demonstrate how to write an interrupt service routine, and how to synchronise
 * a task with an interrupt.  A task is created that blocks on a test semaphore.
 * When the USER button is pressed, the button interrupt handler gives the
 * semaphore, causing the task to unblock.  When the task unblocks, it simply
 * increments an execution count variable, then returns to block on the
 * semaphore again.
 */

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* Demo application includes. */
#include "partest.h"
#include "flash.h"

/* Hardware includes. */
#include "arm_comm.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_xx" (where xx is the variable data type
***********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
/* New variables */

/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword)
and have a comment about their origin. */
extern xSemaphoreHandle G_xLcdTxBufferMutex;            /* From lcd_NHD-C12864A1Z.c */
extern xSemaphoreHandle G_xLcdRamMutex;                 /* From lcd_NHD-C12864A1Z.c */


/* Priorities for the demo application tasks. */
#define mainFLASH_TASK_PRIORITY				( tskIDLE_PRIORITY + 1UL )

/* Priorities for the SCI application tasks */
#define mainREGULAR_TASK_PRIORITY     (tskIDLE_PRIORITY + 1UL)  /* Tasks that should generally always run */
#define mainCOMMUNICATION_TASK_PRIORITY (tskIDLE_PRIORITY + 2UL)  /* Tasks that read and write communication buffers */


#define mainQUEUE_POLL_PRIORITY				( tskIDLE_PRIORITY + 2UL )
#define mainSEM_TEST_PRIORITY				( tskIDLE_PRIORITY + 1UL )
#define mainBLOCK_Q_PRIORITY				( tskIDLE_PRIORITY + 2UL )
#define mainCREATOR_TASK_PRIORITY			( tskIDLE_PRIORITY + 3UL )
#define mainFLOP_TASK_PRIORITY				( tskIDLE_PRIORITY )

/* The LED used by the check timer. */
#define mainCHECK_LED 						( 3UL )

/* A block time of zero simply means "don't block". */
#define mainDONT_BLOCK						( 0UL )

/* The period after which the check timer will expire, in ms, provided no errors
have been reported by any of the standard demo tasks.  ms are converted to the
equivalent in ticks using the portTICK_RATE_MS constant. */
#define mainCHECK_TIMER_PERIOD_MS			( 3000UL / portTICK_RATE_MS )

/* The period at which the check timer will expire, in ms, if an error has been
reported in one of the standard demo tasks.  ms are converted to the equivalent
in ticks using the portTICK_RATE_MS constant. */
#define mainERROR_CHECK_TIMER_PERIOD_MS 	( 200UL / portTICK_RATE_MS )

/*-----------------------------------------------------------*/

/*
 * Set up the hardware ready to run this demo.
 */
static void prvSetupHardware( void );

/*
 * The check timer callback function, as described at the top of this file.
 */

/*-----------------------------------------------------------*/

int main(void)
{
	/* Configure the hardware ready to run the test. */
	prvSetupHardware();

  /* Start all tasks */
  vStartLEDFlashTasks( mainFLASH_TASK_PRIORITY );
  vStartUARTtask(DEBUG_SERIAL_TASK_PRIORITY);
  vStartSpi2Task( SPI_TASK_PRIORITY );
  vStartLcdTask( LCD_TASK_PRIORITY );
  vStartModbusTask(MODBUS_DRIVER_TASK_PRIORITY);
  vStartModbusStateMachine(MODBUS_STATE_MACHINE_TASK_PRIORITY);
  vStartEthPeriphTask( ETH_PERIPH_TASK_PRIORITY );
  vStartEthSwitchTask( ETH_SWITCH_TASK_PRIORITY );
  vStartEthernetHandlerTask( ETHERNET_HANDLER_TASK_PRIORITY );

	/* Start the scheduler. */
	vTaskStartScheduler();

	/* If all is well, the scheduler will now be running, and the following line
	will never be reached.  If the following line does execute, then there was
	insufficient FreeRTOS heap memory available for  the idle and/or timer tasks
	to be created.  See the memory management section on the FreeRTOS web site
	for more details. */
	for( ;; )
      vTaskDelay(1000);
}


/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{
	/* Setup STM32 system (clock, PLL, Flash configuration) */
	SystemInit();

  /* Configure all GPIO */
  SCI_LEDInit_All();
  SCI_LCD_GPIO_Init();
  SCI_ETH_GPIO_Init();
  SCI_Misc_GPIO_Init();

	/* Ensure all priority bits are assigned as preemption priority bits. */
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

  /* Peripheral setup */


	/* Configure the button input.  This configures the interrupt to use the
	lowest interrupt priority, so it is ok to use the ISR safe FreeRTOS API
	from the button interrupt handler. */

  //!!!!!!!!!!!!STM_EVAL_PBInit( BUTTON_USER, BUTTON_MODE_EXTI );
}
/*-----------------------------------------------------------*/

void EXTI9_5_IRQHandler(void)
{
long lHigherPriorityTaskWoken = pdFALSE;

	/* Only line 6 is enabled, so there is no need to test which line generated
	the interrupt. */
	EXTI_ClearITPendingBit( EXTI_Line6 );

	/* This interrupt does nothing more than demonstrate how to synchronise a
	task with an interrupt.  First the handler releases a semaphore.
	lHigherPriorityTaskWoken has been initialised to zero. */
	//xSemaphoreGiveFromISR( xTestSemaphore, &lHigherPriorityTaskWoken );

	/* If there was a task that was blocked on the semaphore, and giving the
	semaphore caused the task to unblock, and the unblocked task has a priority
	higher than the currently executing task (the task that this interrupt
	interrupted), then lHigherPriorityTaskWoken will have been set to pdTRUE.
	Passing pdTRUE into the following macro call will cause this interrupt to
	return directly to the unblocked, higher priority, task. */
	portEND_SWITCHING_ISR( lHigherPriorityTaskWoken );
}

/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/



