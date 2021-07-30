#include "hw_types.h"
#include "sysctl.h"
#include "gpio.h"
#include "uart.h"
#include "hw_memmap.h"
#include "hw_ints.h"
#include "interrupt.h"
#include <string.h>
#include "uart_protocol.h"
#include "crc32.h"

struct uart_frame_list_t uart_frame;
struct uart_frame_handle_t uart_frame_handle[] = 
{
    {app_uninit, NULL, "id = 0, app_uninit."},
    {app_iap, NULL, "id = 1, iap."}
};

// uart Rx irq handler
void Uart1IntHandler(void)
{
    struct uart_frame_t* cur_frame = uart_frame.list + uart_frame.head;
    if(cur_frame->status == RECIEVE_HEAD)
    {
        if(cur_frame->head_recieved_len >= sizeof(struct uart_head_t))
        {
             //TBD
        }
        cur_frame->buf[cur_frame->head_recieved_len] = UARTCharNonBlockingGet(UART0_BASE);
        cur_frame->head_recieved_len++;
        if(cur_frame->head_recieved_len == sizeof(struct uart_head_t))
        {
            cur_frame->head = (struct uart_head_t*)(cur_frame->buf);
            cur_frame->status = RECIEVE_BODY;
            if(cur_frame->head->body_len == 0)
            {
                cur_frame->status = RECIEVED;
                uart_frame.head = (uart_frame.head + 1) % UART_FRAME_LIST;
            }
        }
    }
    else if(cur_frame->status == RECIEVE_BODY)
    {
        if(cur_frame->body_recieved_len >= UART_MAX_BODY_LEN)
        {
            //TBD
        }
        cur_frame->buf[sizeof(struct uart_head_t) + cur_frame->body_recieved_len] = UARTCharNonBlockingGet(UART0_BASE);
        cur_frame->body_recieved_len++;
        if(cur_frame->body_recieved_len >= UART_MAX_BODY_LEN || cur_frame->body_recieved_len >= cur_frame->head->body_len)
        {
            cur_frame->status = RECIEVED;
            uart_frame.head = (uart_frame.head + 1) % UART_FRAME_LIST;
        }
    }

    UARTIntClear(UART0_BASE, UART_INT_RX);
}

static int SearchAppid(uint32_t appid)
{
    uint32_t left = 0, right = sizeof(uart_frame_handle) / sizeof(uart_frame_handle[0]) - 1;
    uint32_t mid;
    while(left <= right)
    {
        mid = (left + right) / 2;
        if(uart_frame_handle[mid].appid == appid) return mid;
        if(uart_frame_handle[mid].appid > appid) right = mid - 1;
        if(uart_frame_handle[mid].appid < appid) left = mid + 1;
    }

    return -1;
}

// process recieved frame and calling app_uart_handler
void UartFrameHandler(void)
{
    while(uart_frame.tail != uart_frame.head)
    {
        struct uart_frame_t* cur_frame = uart_frame.list + uart_frame.tail;
        if(cur_frame->status < RECIEVED) return;
        if(cur_frame->status == RECIEVED)
        {
            uint32_t crc_result = crc_32(cur_frame->buf, sizeof(struct uart_head_t) + cur_frame->body_recieved_len);
            if(crc_result == 0)
            {
                cur_frame->status = CRC_CORRECT;
                uint32_t app_index = SearchAppid(cur_frame->head->appid);
                if(app_index >= 0)
                {
                    uint8_t result = uart_frame_handle[app_index].handle(uart_frame.tail);
                    if(result == SUCCESS)
                    {
                        //TBD
                    }
                }
                else
                {
                    cur_frame->status = INVALID_APPID;
                }
            }
            else { cur_frame->status = CRC_ERROR; }
        }
        if(cur_frame->status > RECIEVED)
        {
            uart_frame.tail = (uart_frame.tail + 1) % UART_FRAME_LIST;
            memset(cur_frame, 0, sizeof(struct uart_frame_t));
        }
    }
}

void uart_protocol_init(void)
{
    SysCtlPeripheralEnable( SYSCTL_PERIPH_UART1 );
	SysCtlPeripheralReset( SYSCTL_PERIPH_UART1 );
    /* 	Enable Port D for UART1
		U1Rx        Bit 2   Input
		U1Tx        Bit 3   Output  */
	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOD );
	GPIODirModeSet( GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_DIR_MODE_IN );
    GPIODirModeSet( GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_DIR_MODE_OUT );
	GPIOPadConfigSet( GPIO_PORTD_BASE, (GPIO_PIN_2 | GPIO_PIN_3 ), GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD );

    UARTConfigSet( UART1_BASE, 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_ODD );

    IntEnable( INT_UART1 );
    UARTIntEnable(UART1_BASE, UART_INT_RX);
    UARTEnable( UART1_BASE );

    memset(&uart_frame, 0, sizeof(struct uart_frame_list_t));
}