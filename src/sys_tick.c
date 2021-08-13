#include <stdlib.h>
#include <limits.h>
#include "LM3Sxxxx.h"
#include "ustdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "sys_tick.h"
#include "user_config.h"

void Timer0IntHandler(void)
{
    TimerIntClear( TIMER1_BASE, TIMER_TIMA_TIMEOUT );
}

void Timer1IntHandler(void)
{
    TimerIntClear( TIMER1_BASE, TIMER_TIMA_TIMEOUT );
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveIndexedFromISR( xTimer1TaskHandler, 0, &xHigherPriorityTaskWoken );
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void sys_tick_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_32_BIT_PER);
    TimerLoadSet(TIMER1_BASE, TIMER_A, configCPU_CLOCK_HZ);

    IntEnable(INT_TIMER1A);
    TimerIntEnable( TIMER1_BASE, TIMER_TIMA_TIMEOUT );
    IntPrioritySet(INT_TIMER1A, TIMER1_INT_PRIORITY);
    TimerEnable(TIMER1_BASE, TIMER_A);

    os_printf("Timer1 init success, priority = %d.\r\n", IntPriorityGet(INT_TIMER1A));
    return;
}

void vTimer1Task(void * pvParameters)
{
    uint32_t ulNotifiedValue;
    uint8_t hour = 0, minute = 0, second = 0;

    for( ;; )
    {
        ulNotifiedValue = ulTaskNotifyTakeIndexed( 0, pdTRUE, portMAX_DELAY ); /* Block indefinitely. */

        second++;
        if(second == SECOND_PER_MINUTE)
        {
            second = 0; 
            minute++;
        }
        if(minute == MINUTE_PER_HOUR)
        {
            minute = 0; 
            hour++;
        }

        os_printf("[%02d:%02d:%02d]Timer1 Tick.\r\n", hour, minute, second);
    }
    (void)ulNotifiedValue;
}
