#include <stdlib.h>
#include <limits.h>
#include "LM3Sxxxx.h"
#include "ustdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "sys_tick.h"
#include "user_config.h"

/* global variables */
TaskHandle_t xTimer1TaskHandler = NULL;

/* internal functions */
static void sys_init(void);

int main(void)
{
    sys_init();
    sys_tick_init();

    BaseType_t xHandle;
    xHandle = xTaskCreate(  vTimer1Task,
                            "Timer1Task",
                            TIMER1_TASK_STACK_DEPTH,
                            NULL,
                            TIMER1_TASK_PRIORITY,
                            &xTimer1TaskHandler );
    if(xHandle != pdPASS)
    {
        os_printf("create Timer1TaskHandler failed\r\n");
    }

    vTaskStartScheduler();

    while(1)
    {
        //
    }

    return 0;
}

void sys_init(void)
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

