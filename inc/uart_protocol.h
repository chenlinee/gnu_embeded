#ifndef __UART_PROTOCOL_H__
#define __UART_PROTOCOL_H__

//*****************************************************************************
//
//  struct uart_frame_t --> status
//
//*****************************************************************************
enum uart_protocol_frame_status_e
{
    RECIEVE_HEAD = 0,
    RECIEVE_BODY,
    RECIEVED,
    INVALID_APPID,
    CRC_CORRECT,
    CRC_ERROR
};

//*****************************************************************************
//
//  struct uart_frame_handle_t --> appid
//
//*****************************************************************************
enum uart_protocol_appid_e
{
    app_uninit = 0,     // default status
    app_iap = 1,        // iap register
    app_max
};

//*****************************************************************************
//
//  struct uart_frame_handle_t --> handle return status
//
//*****************************************************************************
enum uart_handler_status_e
{
    SUCCESS = 0,     // default status
    INVALID
};

#define UART_MAX_BODY_LEN   500
#define UART_FRAME_LIST     10

struct uart_head_t
{
    unsigned int appid;
    unsigned int index;
    unsigned int body_len;
    unsigned int wait_index;
    unsigned int crc;
}__attribute__((aligned(4)));

struct uart_frame_t
{
    unsigned int status;
    struct uart_head_t* head;
    unsigned int head_recieved_len;
    unsigned int body_recieved_len;
    unsigned char buf[sizeof(struct uart_head_t) + sizeof(UART_MAX_BODY_LEN)];
}__attribute__((aligned(4)));

struct uart_frame_list_t
{
    unsigned int head;
    unsigned int tail;
    struct uart_frame_t list[UART_FRAME_LIST];
}__attribute__((aligned(4)));
extern struct uart_frame_list_t uart_frame;

struct uart_frame_handle_t
{
    unsigned int appid;
    unsigned char (*handle)(unsigned int index_in_list);
    char* name;
}__attribute__((aligned(4)));

void uart_protocol_init(void);
void UartFrameHandler(void);

#endif
