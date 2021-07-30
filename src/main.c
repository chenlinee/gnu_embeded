#include "hw_types.h"
#include "sysctl.h"
#include "gpio.h"
#include "_timer.h"
#include "hw_memmap.h"
#include "hw_ints.h"
#include "uart.h"
#include "ustdlib.h"
#include "interrupt.h"
#include <stdlib.h>
#include "iap.h"
#include "crc32.h"
#include "uart_protocol.h"

static void sys_init(void);

int main(void)
{
    sys_init();
    init_crc32_tab();
    uart_protocol_init();

    uart_printf("system init success.\r\n");

    while(1)
    {
        //
    }

    return 0;
}

uint32_t count = 0;
void Timer0IntHandler(void)
{
    UartFrameHandler();

    TimerIntClear( TIMER0_BASE, TIMER_TIMA_TIMEOUT );
}

static void sys_init(void)
{
    /* Set the clocking to run from the PLL at 50 MHz 
            400 MHz / 2 / 4 = 50 MHz                 */
    SysCtlClockSet( SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ );

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
    //UARTIntEnable(UART0_BASE, UART_INT_RX);
    UARTEnable( UART0_BASE );


    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_32_BIT_PER);
    TimerLoadSet(TIMER0_BASE, TIMER_A, 50000 * 10);  // 50000 -> 1ms

    IntEnable( INT_TIMER0A );
    TimerIntEnable( TIMER0_BASE, TIMER_TIMA_TIMEOUT );
    TimerEnable(TIMER0_BASE, TIMER_A);

    return;
}
