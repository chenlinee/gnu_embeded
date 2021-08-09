#include "LM3Sxxxx.h"
#include "ustdlib.h"
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"

static void sys_init(void);


int main(void)
{
    sys_init();

    os_printf("system init success.\r\n");

    vTaskStartScheduler();

    while(1)
    {
        //
    }

    return 0;
}

void Timer0IntHandler(void)
{
    //UartFrameHandler();

    TimerIntClear( TIMER0_BASE, TIMER_TIMA_TIMEOUT );
}

void Timer1IntHandler(void)
{
    static uint32_t count = 1;

    int hour, minute, second;
    hour = count / 3600;
    minute = (count % 3600) / 60;
    second = count % 60;

    os_printf("[%02d:%02d:%02d]System Tick\r\n", hour, minute, second);
    count++;

    TimerIntClear( TIMER1_BASE, TIMER_TIMA_TIMEOUT );
}

static void sys_init(void)
{
    /* Set the clocking to run from the PLL at 50 MHz 
            400 MHz / 2 / 4 = 50 MHz                 */
    SysCtlClockSet( SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ );

    IntPriorityGroupingSet( NVIC_APINT_PRIGROUP_M );

    // uart0 for printf
    SysCtlPeripheralEnable( SYSCTL_PERIPH_UART0 );
	SysCtlPeripheralReset( SYSCTL_PERIPH_UART0 );
    /* 	Enable Port A for UART0
		U0Rx        Bit 0   Input
		U0Tx        Bit 1   Output  */
	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA );
	GPIODirModeSet( GPIO_PORTA_BASE, GPIO_PIN_0, GPIO_DIR_MODE_IN );
    GPIODirModeSet( GPIO_PORTA_BASE, GPIO_PIN_1, GPIO_DIR_MODE_OUT );
	GPIOPadConfigSet( GPIO_PORTA_BASE, (GPIO_PIN_0 | GPIO_PIN_1 ), GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD );
    UARTConfigSet( UART0_BASE, 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_ODD );
    //IntEnable( INT_UART0 );
    //UARTIntEnable(UART0_BASE, UART_INT_TX);
    UARTEnable( UART0_BASE );

    os_printf("os_printf init success.\r\n");

    return;
}


void vAssertCalled( const char *pcFile, unsigned long ulLine )
{
    volatile uint32_t ulSetTo1InDebuggerToExit = 0;

	taskENTER_CRITICAL();
	{
		while( ulSetTo1InDebuggerToExit == 0 )
		{
			/* Nothing to do here.  Set the loop variable to a non zero value in
			the debugger to step out of this function to the point that caused
			the assertion. */
			( void ) pcFile;
			( void ) ulLine;
		}
	}
	taskEXIT_CRITICAL();
}

void vApplicationTickHook( void )
{
    static uint32_t count = 0;
    static uint32_t time = 0;
    if(count == 1000)
    {
        count = 0;

        time++;
        int hour, minute, second;
        hour = time / 3600;
        minute = (time % 3600) / 60;
        second = time % 60;
        os_printf("[%02d:%02d:%02d]System Tick\r\n", hour, minute, second);
    }
    count++;
}

/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
/* If the buffers to be provided to the Idle task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
static StaticTask_t xIdleTaskTCB;
static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

	/* Pass out a pointer to the StaticTask_t structure in which the Idle task's
	state will be stored. */
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

	/* Pass out the array that will be used as the Idle task's stack. */
	*ppxIdleTaskStackBuffer = uxIdleTaskStack;

	/* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
	Note that, as the array is necessarily of type StackType_t,
	configMINIMAL_STACK_SIZE is specified in words, not bytes. */
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
static StaticTask_t xTimerTaskTCB;
static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

	/* Pass out a pointer to the StaticTask_t structure in which the Timer
	task's state will be stored. */
	*ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

	/* Pass out the array that will be used as the Timer task's stack. */
	*ppxTimerTaskStackBuffer = uxTimerTaskStack;

	/* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
	Note that, as the array is necessarily of type StackType_t,
	configMINIMAL_STACK_SIZE is specified in words, not bytes. */
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
/*-----------------------------------------------------------*/
