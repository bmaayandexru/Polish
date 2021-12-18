#ifndef __U0PACKETS_H__
#define __U0PACKETS_H__

#include "Defs.h"
#include "fs.h"

// адрес протокола по UATR0
#define ADDR_U0 0x9F

// команды протокола
#define cmReadRegs 			0x03
#define cmWriteRegs		 	0x06

// файловая система
#define cmFS_QFiles			0x20
#define cmFS_FInfo			0x21
#define cmFS_SetFInfo		0x22
#define cmFS_Delete			0x23

#define cmFS_Create			0x24
#define cmFS_Rewrite		0x25
#define cmFS_Append			0x26
#define cmFS_Reset			0x27
#define cmFS_RewriteHandle	0x28

#define cmFS_BReadLn		0x29
#define cmFS_Write			0x2A
#define cmFS_Read			0x2B
#define cmFS_Seek			0x2C
#define cmFS_Close			0x2D
#define cmFS_WriteLn		0x2E
#define cmFS_ReadLn			0x2F

// пользовательские команды
#define cmTest          	0x64
#define cmRunBootLoader 	0x65
//#define cmDbgMsg        	0x66
//#define cmDataToU1      	0x67
#define cmGoToPoint			0x68
#define cmShiftRotate		0x69
#define cmAddPoint			0x70
#define cmCreateRegsBin		0x71
#define cmApplyRegsBin		0x72
#define cmLSSend			0x73
#define cmQAllocTable   	0x74
#define cmReset				0x75

#define cmGetRegInfo		0x76
#define cmGetVersion		0x77

#define cmGetBusy			0x78
#define cmGetBlock			0x79
#define cmGetTimers			0x80

#define cmInitZCorr			0x81
#define cmSetPin			0x82
#define cmGetPin			0x83

#define cmFl_GetUsing   	0x30
#define cmFl_BulkErase	 	0x31
#define cmFS_Pos			0x32

extern u8	EAddr;
extern u8	ECmd;
extern u8	ECode;

#ifdef __SAW__
void 	mbSawPackHandler0(u8 * buffer,u16 len);
#endif

#ifdef __FREZER__
void 	mbFrzPackHandler0(u8 * buffer,u16 len);
#endif

// переехало в msg.h.c 
//void	Msg (const  u8 *format, ...);
//void 	Dump(u8 * buffer,u16 count);
//void	SMsg(void);

void	UART0_Thread(void);


void 	SendAddPointPack(s32 * pIndex,float * px, float * py);



//// поставлено тут чтобы не пересекаться с Жениным кодом
// переехало в bFS.h.c
//s8 bFS_Read(tFile fcs_num, u8 *buffer, u32 size, u32 * rb);
//s8 bFS_ReadLn(tFile fcs_num, u8 *str, u32 max_size);
//s8 bFS_BReadLn(tFile fcs_num, u8 *str, u32 max_size);
//s8 bFS_Write(tFile fcs_num, const u8 *buffer, u32 size, u32 * wbc);

#endif
