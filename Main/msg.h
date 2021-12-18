#ifndef __MSG_H__
#define __MSG_H__
#include <stdarg.h>
#include "Defs.h"

#define cmDbgMsg        	0x66

void  Msg (const  u8 *format, ...);
void Dump(u8 * buffer,u16 count);
void	SMsg(void);

#endif
