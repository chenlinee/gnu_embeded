.section .isr_vector
    .align 2
    .extern NmiSR
    .extern FaultISR
    .extern IntDefaultHandler
    .extern Uart1IntHandler
    .extern Timer0IntHandler
.word   _MSP
.word   Reset_Handler + 1
.word   NmiSR + 1                               // The NMI handler
.word   FaultISR + 1                            // The hard fault handler
.word   IntDefaultHandler + 1                   // The MPU fault handler
.word   IntDefaultHandler + 1                   // The bus fault handler
.word   IntDefaultHandler + 1                   // The usage fault handler
.word   0                                       // Reserved
.word   0                                       // Reserved
.word   0                                       // Reserved
.word   0                                       // Reserved
.word   IntDefaultHandler + 1                   // SVCall handler
.word   IntDefaultHandler + 1                   // Debug monitor handler
.word   0                                       // Reserved
.word   IntDefaultHandler + 1                      // The PendSV handler
.word   IntDefaultHandler + 1                      // The SysTick handler
.word   IntDefaultHandler + 1                      // GPIO Port A
.word   IntDefaultHandler + 1                      // GPIO Port B
.word   IntDefaultHandler + 1                      // GPIO Port C
.word   IntDefaultHandler + 1                      // GPIO Port D
.word   IntDefaultHandler + 1                      // GPIO Port E
.word   IntDefaultHandler + 1                      // UART0 Rx and Tx
.word   Uart1IntHandler + 1                        // UART1 Rx and Tx
.word   IntDefaultHandler + 1                      // SSI Rx and Tx
.word   IntDefaultHandler + 1                      // I2C Master and Slave
.word   IntDefaultHandler + 1                      // PWM Fault
.word   IntDefaultHandler + 1                      // PWM Generator 0
.word   IntDefaultHandler + 1                      // PWM Generator 1
.word   IntDefaultHandler + 1                      // PWM Generator 2
.word   IntDefaultHandler + 1                      // Quadrature Encoder
.word   IntDefaultHandler + 1                      // ADC Sequence 0
.word   IntDefaultHandler + 1                      // ADC Sequence 1
.word   IntDefaultHandler + 1                      // ADC Sequence 2
.word   IntDefaultHandler + 1                      // ADC Sequence 3
.word   IntDefaultHandler + 1                      // Watchdog timer
.word   Timer0IntHandler + 1                       // Timer 0 subtimer A
.word   IntDefaultHandler + 1                      // Timer 0 subtimer B
.word   IntDefaultHandler + 1                      // Timer 1 subtimer A
.word   IntDefaultHandler + 1                      // Timer 1 subtimer B
.word   IntDefaultHandler + 1                      // Timer 2 subtimer A
.word   IntDefaultHandler + 1                      // Timer 2 subtimer B
.word   IntDefaultHandler + 1                      // Analog Comparator 0
.word   IntDefaultHandler + 1                      // Analog Comparator 1
.word   IntDefaultHandler + 1                      // Analog Comparator 2
.word   IntDefaultHandler + 1                      // System Control (PLL + 1 OSC + 1 BO)
.word   IntDefaultHandler + 1                      // FLASH Control
.word   IntDefaultHandler + 1                      // GPIO Port F
.word   IntDefaultHandler + 1                      // GPIO Port G
.word   IntDefaultHandler + 1                      // GPIO Port H
.word   IntDefaultHandler + 1                      // UART2 Rx and Tx
.word   IntDefaultHandler + 1                      // SSI1 Rx and Tx
.word   IntDefaultHandler + 1                      // Timer 3 subtimer A
.word   IntDefaultHandler + 1                      // Timer 3 subtimer B
.word   IntDefaultHandler + 1                      // I2C1 Master and Slave
.word   IntDefaultHandler + 1                      // Quadrature Encoder 1
.word   IntDefaultHandler + 1                      // CAN0
.word   IntDefaultHandler + 1                      // CAN1
.word   0                                         // Reserved
.word   IntDefaultHandler + 1                      // Ethernet
.word   IntDefaultHandler + 1                      // Hibernate

.section .text
    .align 2
    .global Reset_Handler
    .extern _start
    .extern main
Reset_Handler:
    cpsid i     // mov r0, #1 && msr primask, r0
    bl _start
    cpsie i     // mov r0, #0 && msr primask, r0
    bl main
stop:
    b stop
