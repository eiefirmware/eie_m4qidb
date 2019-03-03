/*
 FreeRTOS V7.2.0 - Copyright (C) 2012 Real Time Engineers Ltd.
 No changes in V7.5.2, so this file was not updated.
 *
 * main() creates all the  application tasks and software timers, then starts
 * the scheduler. The LED flashing demo application is still present for now.
 */

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* Demo application includes. */
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

/* Priorities for the demo application tasks. */
#define mainFLASH_TASK_PRIORITY                   ( tskIDLE_PRIORITY + 1UL )

/* Priorities for the SCI application tasks */
#define mainREGULAR_TASK_PRIORITY       ( tskIDLE_PRIORITY + 1UL )  /* Tasks that should generally always run */
#define mainCOMMUNICATION_TASK_PRIORITY ( tskIDLE_PRIORITY + 2UL )  /* Tasks that read and write communication buffers */

/* The LED used by the check timer. */
#define mainCHECK_LED                         ( 3UL )

/* A block time of zero simply means "don't block". */
#define mainDONT_BLOCK                        ( 0UL )

/* The period after which the check timer will expire, in ms, provided no errors
 have been reported by any of the standard demo tasks.  ms are converted to the
 equivalent in ticks using the portTICK_RATE_MS constant. */
#define mainCHECK_TIMER_PERIOD_MS            ( 3000UL / portTICK_RATE_MS )

/* The period at which the check timer will expire, in ms, if an error has been
 reported in one of the standard demo tasks.  ms are converted to the equivalent
 in ticks using the portTICK_RATE_MS constant. */
#define mainERROR_CHECK_TIMER_PERIOD_MS     ( 200UL / portTICK_RATE_MS )

/*-----------------------------------------------------------*/
/* Main's function prototypes */
static void prvSetupHardware (void);

/*-----------------------------------------------------------*/

int main (void)
{
    /* Configure the hardware */
    prvSetupHardware ();


    /* Start all tasks */

    //vStartUARTtask(DEBUG_SERIAL_TASK_PRIORITY);
    //vStartSpiTask ( tskIDLE_PRIORITY + 1UL);

    vStartvBoardTestTask( BOARDTEST_TASK_PRIORITY );

    // LEDs, buzzer, valves, etc
    vStartMiscIOTask ( MISC_IO_TASK_PRIORITY);

    /* Start the scheduler. */
    vTaskStartScheduler ();

    /* If all is well, the scheduler will now be running, and the following line
     will never be reached.  If the following line does execute, then there was
     insufficient FreeRTOS heap memory available for  the idle and/or timer tasks
     to be created.  See the memory management section on the FreeRTOS web site
     for more details. */
    for (;;)
        vTaskDelay (1000);
}

/*-----------------------------------------------------------*/

static void prvSetupHardware (void)
{
    /* Setup STM32 system (clock, PLL, Flash configuration) */
    SystemInit ();

    /* Configure all GPIO */
    EIE_LEDInit_All ();
    EIE_Misc_GPIO_Init ();
    EIE_ButtonInit_All ();

    /* Ensure all priority bits are assigned as preemption priority bits. */
    NVIC_PriorityGroupConfig ( NVIC_PriorityGroup_4);

}

#if 0
/*-----------------------------------------------------------*/
#define CW  (0)
#define CCW (1)
void EXTI9_5_IRQHandler (void)
{
    long lHigherPriorityTaskWoken = pdFALSE;

    long lPortcheck;
    long lExtLine = EXTI_Line5;

    for (lPortcheck = 5; lPortcheck <= 9; lPortcheck++)
    {
        if (EXTI_GetFlagStatus (lExtLine) == SET)
        {
            EXTI_ClearITPendingBit (lExtLine);

            if (lExtLine == EXTI_Line6) // left encoder
            {
				if (EIE_PBGetState (BUTTON_LEFT_ENCODER_A) == EIE_PBGetState (BUTTON_LEFT_ENCODER_B))
				{
					NewButtonAction (IRQ_BUTTON_LEFT_ENCODER_CCW);
				}
				else
				{
					NewButtonAction (IRQ_BUTTON_LEFT_ENCODER_CW);
				}
            } // if test

            if (lExtLine == EXTI_Line5) // right encoder
            {
                if (EIE_PBGetState (BUTTON_RIGHT_ENCODER_A) == EIE_PBGetState (BUTTON_RIGHT_ENCODER_B))
                {
                    NewButtonAction (IRQ_BUTTON_RIGHT_ENCODER_CW);
                }
                else
                {
                    NewButtonAction (IRQ_BUTTON_RIGHT_ENCODER_CCW);
                }
            } // Right Encoder
        }

        lExtLine <<= 1;
    }

    /* Only line 6 is enabled, so there is no need to test which line generated
     the interrupt. */
    //EXTI_ClearITPendingBit( EXTI_Line6 );
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
    portEND_SWITCHING_ISR(lHigherPriorityTaskWoken);
}
#endif

void EXTI15_10_IRQHandler (void)
{
    long lHigherPriorityTaskWoken = pdFALSE;

    long lPortcheck;
    long lExtLine = EXTI_Line10;

    for (lPortcheck = 10; lPortcheck <= 15; lPortcheck++)
    {
        if (EXTI_GetFlagStatus (lExtLine) == SET)
        {
            EXTI_ClearITPendingBit (lExtLine);

            //NewButtonAction (lPortcheck);

        }

        lExtLine <<= 1;
    }

    /* Only line 6 is enabled, so there is no need to test which line generated
     the interrupt. */
    //EXTI_ClearITPendingBit( EXTI_Line6 );
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
    portEND_SWITCHING_ISR(lHigherPriorityTaskWoken);
}

