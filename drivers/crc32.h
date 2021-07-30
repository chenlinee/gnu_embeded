#ifndef __CRC32_H__
#define __CRC32_H__

extern unsigned int crc32_tab[256];

#define CRC_POLY_32     0xEDB88320ul
#define CRC_START_32    0xFFFFFFFFul

void init_crc32_tab( void );
unsigned int crc_32( const unsigned char *input_str, unsigned int num_bytes );
unsigned int update_crc_32( unsigned int crc, unsigned char c );

#endif
