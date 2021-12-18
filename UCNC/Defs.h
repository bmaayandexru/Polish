/*****************************************************************/
//
//  МОДУЛЬ ОБЩИХ ОПРЕДЕЛЕНИЙ
//
/*****************************************************************/

#ifndef __DEFS_H_
#define __DEFS_H_

#include <stdint.h>

#define TRUE 	1
#define FALSE 	0

//--------------------------------------------------
// Короткие имена стандартных типов
//--------------------------------------------------
typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef u8 bool;
typedef u8 BOOL;

#define VERSION 0x01010101
#define build 05

//#define VERSION 0x01020124
// отладка функции Move_Handler
//#define MOVE_D
// пила
// отключение загрузки параметров с флэш
//#define __NOT_LOAD_PARAMS__
// пила
//#define __SAW__
// фрезер
#define __FREZER__
#endif // __DEFS_H_
