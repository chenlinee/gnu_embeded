//*****************************************************************************
//
// uartstdlib.h - Prototypes for simple standard library functions.
//
// Copyright (c) 2007 Luminary Micro, Inc.  All rights reserved.
//
// Software License Agreement
//
// Luminary Micro, Inc. (LMI) is supplying this software for use solely and
// exclusively on LMI's microcontroller products.
//
// The software is owned by LMI and/or its suppliers, and is protected under
// applicable copyright laws.  All rights are reserved.  Any use in violation
// of the foregoing restrictions may subject the user to criminal sanctions
// under applicable laws, as well as to civil liability for the breach of the
// terms and conditions of this license.
//
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// LMI SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
// CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
//
//
//*****************************************************************************

#ifndef __UARTSTDLIB_H__
#define __UARTSTDLIB_H__

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern int usprintf(char *, const char *pcString, ...);
extern int usnprintf(char *pcBuf, unsigned long ulSize,
                     const char *pcString, ...);
void os_printf(void);

#define os_print_buf_len   0x100
extern char os_print_buf[os_print_buf_len];

#define uart_printf(format, args...)    do \
                                    { \
                                        usnprintf(os_print_buf, os_print_buf_len - 1, format, ##args); \
                                        os_printf(); \
                                    }  while(0)

#ifdef __cplusplus
}
#endif

#endif // __UARTSTDLIB_H__
