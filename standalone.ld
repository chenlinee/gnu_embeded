ENTRY(Reset_Handler)

MEMORY
{
    M_ISR : ORIGIN = 0x00000000, LENGTH = 0x00000400
    M_ROM : ORIGIN = 0x00000400, LENGTH = 0x0003FC00
    M_RAM : ORIGIN = 0x20000000, LENGTH = 0x00010000
}

SECTIONS
{
    . = ALIGN(4);
    .isr_vector :
    {
        *startup.o(.isr_vector)
    } > M_ISR

    . = ALIGN(4);
    .text :
    {
        *startup.o(.text)
        *(.text)
        *(.rodata)
        _text_end = .;
    } > M_ROM

    . = ALIGN(4);
    _DATA_ROM_START = .;
    .data : AT ( _text_end )
    {
        *(.data)
    } > M_RAM
    _DATA_ROM_END = .;
    _DATA_LEN = _DATA_ROM_END - _DATA_ROM_START;
    _DATA_RAM_START = ORIGIN(M_RAM);

    . = ALIGN(4);
    _BSS_START = .;
    .bss :
    {
        *(.bss COMMON)
    } > M_RAM
    _BSS_END = .;
    _BSS_LEN = _BSS_END - _BSS_START;

    _BSS_RAM_START = _DATA_RAM_START + _DATA_LEN;
    _MSP = ORIGIN(M_RAM) + LENGTH(M_RAM);
}