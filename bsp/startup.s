.section .isr_vector
    .align 2
.word   _MSP
.word   Reset_Handler + 1

.section .text
    .align 2
    .global Reset_Handler
    .extern _start
    .extern main
Reset_Handler:
    mov r0, #1
    msr PRIMASK, r0 @ 关闭中断
    bl _start
    bl main
stop:
    b stop