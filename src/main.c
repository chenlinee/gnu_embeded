#include "hw_types.h"
#include "sysctl.h"
#include "gpio.h"
#include "hw_memmap.h"
#include "uart.h"
#include "ustdlib.h"
#include <stdlib.h>

#define ENTER_IN        0x0A
#define ENTER_OUT       0x0D
#define BACKSPACE_IN    0x7F
#define BACKSPACE_OUT   0x08
#define CTRL_C          0x03

int main(void)
{
    /* Set the clocking to run from the PLL at 50 MHz 
            400 MHz / 2 / 4 = 50 MHz                 */
    SysCtlClockSet( SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ );

    SysCtlPeripheralEnable( SYSCTL_PERIPH_UART0 );
	SysCtlPeripheralReset( SYSCTL_PERIPH_UART0 );

    /* 	Enable Port A for UART0
		U0Rx        Bit 0   Output
		U0Tx        Bit 1   Input  */
	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA );
	GPIODirModeSet( GPIO_PORTA_BASE, GPIO_PIN_0, GPIO_DIR_MODE_OUT );
    GPIODirModeSet( GPIO_PORTA_BASE, GPIO_PIN_1, GPIO_DIR_MODE_IN );
	GPIOPadConfigSet( GPIO_PORTA_BASE, (GPIO_PIN_2 | GPIO_PIN_3 ), GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD );

    UARTConfigSet( UART0_BASE, 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_ODD );
    UARTEnable( UART0_BASE );

    unsigned char hello[] = "hello world.\n";

    for(int i = 0; hello[i] != 0; ++i)
    {
        UARTCharPut(UART0_BASE, hello[i]);
    }

    unsigned char receive;
    while((receive = UARTCharGet( UART0_BASE )))
    {
        UARTCharPut(UART0_BASE, receive);
        switch(receive)
        {
            case CTRL_C:
                return 0;
            case ENTER_IN:
                UARTCharPut(UART0_BASE, ENTER_OUT);
                break;
            case BACKSPACE_IN:
                UARTCharPut(UART0_BASE, BACKSPACE_OUT);
                break;
            default:
                break;
        }
    }

    return 0;
}
