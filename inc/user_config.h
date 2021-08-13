#ifndef __USER_CONFIG_H__

#ifndef __HW_TYPES_H__
    #error "include hw_types.h must appear in source files before include user_config.h"
#endif // !__HW_TYPES_H__

/*************************** global define ***************************/
/* interupt priority */
#define INT_PRIORITY_SET( n )       ( ( unsigned char )( (n) | 0x1f ) )
#define TIMER1_INT_PRIORITY         INT_PRIORITY_SET( 6 )

/* task priority */
#define TIMER1_TASK_PRIORITY        ( 1 )

/* task stack depth / 4B */
#define TIMER1_TASK_STACK_DEPTH     ( 0x100 )

/************************** global variables **************************/
extern TaskHandle_t xTimer1TaskHandler;

#endif // !__USER_CONFIG_H__