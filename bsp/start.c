extern unsigned char _DATA_RAM_START[], _DATA_ROM_START[], _DATA_LEN[];
extern unsigned char _BSS_RAM_START[], _BSS_LEN[];

void _start(void)
{
    unsigned int i = 0;
    for(; i < (unsigned int)_DATA_LEN; i += 4)
    {
        *(unsigned int*)(_DATA_RAM_START + i) = *(unsigned int*)(_DATA_ROM_START + i);
    }

    unsigned int bss_len = (unsigned int)_BSS_LEN;
    i = 0;
    while(i < bss_len)
    {
        *(unsigned int*)(_BSS_RAM_START + i) = 0;
        i += 4;
    }
}