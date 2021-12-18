#include "Defs.h"
#include "msg.h"
#include "FS.h"
#include "bFS.h"

s8 bFS_Read(tFile fcs_num, u8 *buffer, u32 size, u32 * rbc) {
	u32 i;
	s8 res;
	if (size == 0) return FS_RESULT_OK;
	*rbc = 0;
	for (i=0;i < size;i++){
		res = FS_ReadByte(fcs_num,buffer+i);
		if (res < 0) {
			return res;
		} else {
			(*rbc)++;
		}
	}	
	return res;
}


s8 bFS_ReadLn(tFile fcs_num, u8 *str, u32 max_size) {
	u32 i;
	u8 s;
	u8 b;
	s8 res;

	s = 0; 
	i = 0;
	if (FS_Eof(fcs_num)==FS_EOF) return FS_EOF;
	do {
		res = FS_ReadByte(fcs_num,&b);
		if (res < 0) return res;
		else {
			switch (s) {
				case 0:
					// читаем все символы до 13
					*(str+i) = b;
					if (b == 13) s=1;
				break;
	
				case 1:
					if (b == 10) {
						// следующий симпол за 13 должен быть 10
						*(str+i) = b;
						// выходим
						return FS_RESULT_OK;
					} else {
						// следующий за 13 символ не 10
						FS_RSeek(fcs_num,-1);
						// сдвигаемся на предыдущий символ и выходим
						return FS_RESULT_OK;
					}
//				break;
			}
		}
		i++;
	} while	(i<max_size);
	// если переехали max_size тоже выходим
	return FS_RESULT_OK;
}

s8 FS_ReadPrevByte(tFile fcs_num,u8 * b){
	s32 pos;
	s8 res;
	res = FS_Pos(fcs_num,&pos);
	if (res) return res;
	// получили позицию в pos
	if (pos) {
		res = FS_RSeek(fcs_num,-1);
		if (res) return res;
		res = FS_ReadByte(fcs_num,b);
		if (res) return res;
		res = FS_RSeek(fcs_num,-1);
		return res;
	} else {
		*b = 0;
		return FS_BOF;
	}
}

s8 bFS_BReadLn(tFile fcs_num, u8 *str, u32 max_size) {
// прочитать строку в обратном направлении
	u8 s;
	u8 b;
	s8 res;
	s32 fixpos;
	s32 pos;

	s = 0; 

	// если стоим в начале то ничего вычитать не можем
	res = FS_Pos(fcs_num,&pos);
	if (res) return res;
	if (pos==0) return FS_BOF; // выходим

	// идем по файлу в обратном направлении
	// до начала или до 2-х вхождений символа 13
	while ((FS_ReadPrevByte(fcs_num,&b)==0)&&(s < 2)) {
		if (b == 13) s++;
	}
	res = FS_Pos(fcs_num,&pos);
	if (res) return res;
	if (pos) {
		// если не в начале файла
		// вычитываем три символа XX 13 10
		FS_ReadByte(fcs_num,&b);
		FS_ReadByte(fcs_num,&b);
		FS_ReadByte(fcs_num,&b);
	}	
	// здесь гарантированно стоим на первом символе пред строки
	// фиксирум позицию чтобы вернуться в нее
	res = FS_Pos(fcs_num,&fixpos);
	if (res) return res;
	// читаем строку
	res = bFS_ReadLn(fcs_num,str,max_size);
	if (res) return res;
	// возвращаемся в позицию
	res = FS_Seek(fcs_num,fixpos);
	return res;
}

s8 bFS_Write(tFile fcs_num, const u8 *buffer, u32 size, u32 * wbc) {
	u32 i;
	s8 res;
	*wbc = 0;
	if (size == 0) return FS_RESULT_OK;
	for (i=0;i<size;i++) {
		res = FS_WriteByte(fcs_num,*(buffer+i));
//		res = 0;
		if (res < 0) {
			return res;
		} else {
			(*wbc)++;
		}
	}
	return res;
}

s8 InitStream(TFileStream *s,tFile fs){
	// инициализация потока
	if (fs != 0) {
		(*s).Pos = 0;
		(*s).f = fs;
		return FS_Seek(fs,((*s).Pos));
	} 	
	else return -100;
}

s8 bsFS_ReadLn(TFileStream *s, u8 *str, u32 max_size){
	s8 res;	
   	res = FS_Seek((*s).f,(*s).Pos);
//	Msg("FS_Seek (%d,%d) = %d \r\n",(*s).f,(*s).Pos,res);
	if (res == FS_RESULT_OK) {
		// позиция есть можно читать
		res = bFS_ReadLn((*s).f,str,max_size);
//		Msg("Strm Line: %s\r\n",str);
		if (res == FS_RESULT_OK) {
//			res = FS_Pos((*s).f,&((*s).Pos));
			return FS_Pos((*s).f,&((*s).Pos));
//			Msg("FS_Pos( %d, %d) = %d \r\n",(*s).f,((*s).Pos),res);
//			return res;
		} else return res;
	}
	else return res;
}

s8 bsFS_BReadLn(TFileStream *s, u8 *str, u32 max_size){
	s8 res;	
   	res = FS_Seek((*s).f,(*s).Pos);
	if (res == FS_RESULT_OK) {
		// позиция есть можно читать
		res = bFS_BReadLn((*s).f,str,max_size);
		if (res == FS_RESULT_OK) {
			return FS_Pos((*s).f,&((*s).Pos));
		} else return res;
	}
	else return res;
}

s8 bsFS_Seek(TFileStream *s,u32 position){
	s8 res;
	res = FS_Seek((*s).f,position);
	if (res == FS_RESULT_OK) {
		(*s).Pos = position;
	}
	return res;
}

s8 bsFS_Pos(TFileStream * s,s32 * pos){
	*pos = (*s).Pos;
	return FS_RESULT_OK;
}
