#line 1 "Main\\bFS.c"
#line 1 ".\\UCNC\\Defs.h"
 



 




#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
 
 





 









     
#line 27 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
     











#line 46 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"





 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     




typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;


     
typedef   signed     long long intmax_t;
typedef unsigned     long long uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     






     






     






     

     


     


     


     

     
#line 216 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     



     






     
    
 



#line 241 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     







     










     











#line 305 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"






 
#line 11 ".\\UCNC\\Defs.h"







typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef u8 bool;










#line 2 "Main\\bFS.c"
#line 1 "Main\\msg.h"
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdarg.h"
 
 
 





 










#line 27 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdarg.h"








 

 
 
#line 57 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdarg.h"
    typedef struct __va_list { void *__ap; } va_list;

   






 


   










 


   















 




   

 


   




 



   





 







#line 138 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdarg.h"



#line 147 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdarg.h"

 

#line 4 "Main\\msg.h"
#line 5 "Main\\msg.h"



void  Msg (const  u8 *format, ...);
void Dump(u8 * buffer,u16 count);
void	SMsg(void);

#line 3 "Main\\bFS.c"
#line 1 "Main\\FS.h"













#line 15 "Main\\FS.h"

#line 39 "Main\\FS.h"


typedef s8 tFile;

extern u16 CATRecordsNumber;															
extern u32 FNTRecordsNumber;															


s8 FS_Init(void);


s8 FS_Assign(const u8 *file_name, tFile * f);







s8 FS_Rewrite(tFile f);








s8 FS_Append(tFile f);





s8 FS_Reset(tFile f);






s8 FS_WriteByte(tFile f, u8 data);







s8 FS_ReadByte(tFile f, u8 *data);






s32 FS_Write(tFile f, const u8 *buffer, u32 size);



s32 FS_Read(tFile f, u8 *buffer, u32 size);



s32 FS_WriteLn(tFile f, const u8 *string);


s8 FS_ReadLn(tFile f, u8 *string, u32 max_size);



s8 FS_ReadPrevLn(tFile f, u8 *string, u32 max_size);


s32 FS_RemainSize(tFile f);


s8 FS_Seek(tFile f, u32 position);






s8 FS_RSeek(tFile fcs_num, s32 disp);




s8 FS_Close(tFile *f);





s8 FS_Delete(const u8 *file_name);







s8 FS_GetFileInfo(u32 * start_fnt_num, u8 *name, u8 *type, u8 *attr, u32 *size, tFile *f);




s8 FS_Eof(tFile f);



s8 FS_Pos(tFile fcs_num,s32 * pos);





s32 FS_Size(tFile f);




s32 FS_FilesCount(void);




s8 FS_Rename(const u8 *old_file_name, const u8 *new_file_name);




s8 FS_SetAttr(const u8 *file_name, u8 attr);










s32 FS_RemainSize(tFile f);






u8 FS_GetFCSState( u8 fcs_num);


void FS_FCS_Show( u8 fcs_num, void page_buf_view(u8 *buffer, u32 addr) );


void FS_Params_Show(void);

u32 FS_FindFreeFNT(void);
u16 FS_FindFreeCluster(void);




#line 4 "Main\\bFS.c"
#line 1 "Main\\bFS.h"



#line 5 "Main\\bFS.h"
#line 6 "Main\\bFS.h"


typedef struct tagTFileStream{
	tFile 	f;	 
	s32 	Pos; 
} TFileStream;



s8 bFS_Read(tFile fcs_num, u8 *buffer, u32 size, u32 * rb);
s8 bFS_ReadLn(tFile fcs_num, u8 *str, u32 max_size);
s8 bFS_BReadLn(tFile fcs_num, u8 *str, u32 max_size);
s8 bFS_Write(tFile fcs_num, const u8 *buffer, u32 size, u32 * wbc);


s8 InitStream(TFileStream *s,tFile fs);
s8 bsFS_ReadLn(TFileStream *s, u8 *str, u32 max_size);
s8 bsFS_BReadLn(TFileStream *s, u8 *str, u32 max_size);
s8 bsFS_Seek(TFileStream *s,u32 position);
s8 bsFS_Pos(TFileStream *s,s32 * pos);

#line 5 "Main\\bFS.c"

s8 bFS_Read(tFile fcs_num, u8 *buffer, u32 size, u32 * rbc) {
	u32 i;
	s8 res;
	if (size == 0) return 0;
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
	if (FS_Eof(fcs_num)== -21) return -21;
	do {
		res = FS_ReadByte(fcs_num,&b);
		if (res < 0) return res;
		else {
			switch (s) {
				case 0:
					
					*(str+i) = b;
					if (b == 13) s=1;
				break;
	
				case 1:
					if (b == 10) {
						
						*(str+i) = b;
						
						return 0;
					} else {
						
						FS_RSeek(fcs_num,-1);
						
						return 0;
					}

			}
		}
		i++;
	} while	(i<max_size);
	
	return 0;
}

s8 FS_ReadPrevByte(tFile fcs_num,u8 * b){
	s32 pos;
	s8 res;
	res = FS_Pos(fcs_num,&pos);
	if (res) return res;
	
	if (pos) {
		res = FS_RSeek(fcs_num,-1);
		if (res) return res;
		res = FS_ReadByte(fcs_num,b);
		if (res) return res;
		res = FS_RSeek(fcs_num,-1);
		return res;
	} else {
		*b = 0;
		return -22;
	}
}

s8 bFS_BReadLn(tFile fcs_num, u8 *str, u32 max_size) {

	u8 s;
	u8 b;
	s8 res;
	s32 fixpos;
	s32 pos;

	s = 0; 

	
	res = FS_Pos(fcs_num,&pos);
	if (res) return res;
	if (pos==0) return -22; 

	
	
	while ((FS_ReadPrevByte(fcs_num,&b)==0)&&(s < 2)) {
		if (b == 13) s++;
	}
	res = FS_Pos(fcs_num,&pos);
	if (res) return res;
	if (pos) {
		
		
		FS_ReadByte(fcs_num,&b);
		FS_ReadByte(fcs_num,&b);
		FS_ReadByte(fcs_num,&b);
	}	
	
	
	res = FS_Pos(fcs_num,&fixpos);
	if (res) return res;
	
	res = bFS_ReadLn(fcs_num,str,max_size);
	if (res) return res;
	
	res = FS_Seek(fcs_num,fixpos);
	return res;
}

s8 bFS_Write(tFile fcs_num, const u8 *buffer, u32 size, u32 * wbc) {
	u32 i;
	s8 res;
	*wbc = 0;
	if (size == 0) return 0;
	for (i=0;i<size;i++) {
		res = FS_WriteByte(fcs_num,*(buffer+i));

		if (res < 0) {
			return res;
		} else {
			(*wbc)++;
		}
	}
	return res;
}

s8 InitStream(TFileStream *s,tFile fs){
	
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

	if (res == 0) {
		
		res = bFS_ReadLn((*s).f,str,max_size);

		if (res == 0) {

			return FS_Pos((*s).f,&((*s).Pos));


		} else return res;
	}
	else return res;
}

s8 bsFS_BReadLn(TFileStream *s, u8 *str, u32 max_size){
	s8 res;	
   	res = FS_Seek((*s).f,(*s).Pos);
	if (res == 0) {
		
		res = bFS_BReadLn((*s).f,str,max_size);
		if (res == 0) {
			return FS_Pos((*s).f,&((*s).Pos));
		} else return res;
	}
	else return res;
}

s8 bsFS_Seek(TFileStream *s,u32 position){
	s8 res;
	res = FS_Seek((*s).f,position);
	if (res == 0) {
		(*s).Pos = position;
	}
	return res;
}

s8 bsFS_Pos(TFileStream * s,s32 * pos){
	*pos = (*s).Pos;
	return 0;
}
