#ifndef __SYS_TICK_H__

#define SECOND_PER_MINUTE   60
#define MINUTE_PER_HOUR     60

extern void sys_tick_init(void);
extern void vTimer1Task(void * pvParameters);

#endif // !__SYS_TICK_H__