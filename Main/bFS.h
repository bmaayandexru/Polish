#ifndef __bFS_H__
#define __bFS_H__

#include "Defs.h"
#include "fs.h"

// ������
typedef struct tagTFileStream{
	tFile 	f;	 // ����
	s32 	Pos; // ������� ������ � �����
} TFileStream;


// ������ ������� ����������
s8 bFS_Read(tFile fcs_num, u8 *buffer, u32 size, u32 * rb);
s8 bFS_ReadLn(tFile fcs_num, u8 *str, u32 max_size);
s8 bFS_BReadLn(tFile fcs_num, u8 *str, u32 max_size);
s8 bFS_Write(tFile fcs_num, const u8 *buffer, u32 size, u32 * wbc);

// ��������� ������ � ��������
s8 InitStream(TFileStream *s,tFile fs);
s8 bsFS_ReadLn(TFileStream *s, u8 *str, u32 max_size);
s8 bsFS_BReadLn(TFileStream *s, u8 *str, u32 max_size);
s8 bsFS_Seek(TFileStream *s,u32 position);
s8 bsFS_Pos(TFileStream *s,s32 * pos);

#endif
