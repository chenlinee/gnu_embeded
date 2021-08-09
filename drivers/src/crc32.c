#include "hw_types.h"
#include "crc32.h"

unsigned int crc32_tab[256];

/*
 * void init_crc32_tab( void );
 *
 * For optimal speed, the CRC32 calculation uses a table with pre-calculated
 * bit patterns which are used in the XOR operations in the program.
 */

void init_crc32_tab( void )
{
	unsigned int i;
	unsigned int j;
	unsigned int crc;

	for (i=0; i<256; i++)
    {
		crc = i;

		for (j=0; j<8; j++)
        {
			if ( crc & 0x00000001L ) 
            {
                crc = ( crc >> 1 ) ^ CRC_POLY_32;
            }
			else
            {
                crc =   crc >> 1;
            }
		}

		crc32_tab[i] = crc;
	}
}  /* init_crc32_tab */

/*
 * uint32_t crc_32( const unsigned char *input_str, size_t num_bytes );
 *
 * The function crc_32() calculates in one pass the common 32 bit CRC value for
 * a byte string that is passed to the function together with a parameter
 * indicating the length.
 */

unsigned int crc_32( const unsigned char *input_str, unsigned int num_bytes )
{
	unsigned int crc;
	const unsigned char *ptr;
	unsigned int a;

	crc = CRC_START_32;
	ptr = input_str;

	if ( ptr != NULL ) for (a=0; a<num_bytes; a++)
    {
		crc = (crc >> 8) ^ crc32_tab[ (crc ^ (unsigned int) *ptr++) & 0x000000FFul ];
	}

	return (crc ^ 0xFFFFFFFFul);
}  /* crc_32 */

/*
 * uint32_t update_crc_32( uint32_t crc, unsigned char c );
 *
 * The function update_crc_32() calculates a new CRC-32 value based on the
 * previous value of the CRC and the next byte of the data to be checked.
 */

unsigned int update_crc_32( unsigned int crc, unsigned char c )
{
	return (crc >> 8) ^ crc32_tab[ (crc ^ (unsigned int) c) & 0x000000FFul ];
}  /* update_crc_32 */
