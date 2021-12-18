
//****************************************************************************
//
//            M25P64/M25P128 serial memory
//
//****************************************************************************


#ifndef __FLASH_H_
#define __FLASH_H_



#include "LPC17xx.h"

#include "Defs.h"
#include "LPC1768_define.h"			// there are my definitions for benefit


//-----------------------------------------
//
//              SPI FLASH
//
//-----------------------------------------

void FLASH_Init(void);
u8   FLASH_WriteByte(u32 addr, u8 b);
u8   FLASH_ReadByte(u32 addr);
u8   FLASH_Write(u32 addr, const u8 *buffer, u32 size);
void FLASH_Read(u8 *buffer, u32 addr, u32 size);
u8   FLASH_SectorErase(u32 addr);
u32  FLASH_BulkErase(void);


void FLASH_BankSelect(u8 bank_num);
void FLASH_BankDeselect(u8 bank_num);

u8 FLASH_GetBankID(u8 bank_num);


#endif // __FLASH_H_
