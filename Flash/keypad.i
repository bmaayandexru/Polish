#line 1 "Main\\KeyPad.c"
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
 
 
 
 




 








 












#line 38 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"


  



    typedef unsigned int size_t;    
#line 54 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"




extern __declspec(__nothrow) void *memcpy(void * __restrict  ,
                    const void * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) void *memmove(void *  ,
                    const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   







 
extern __declspec(__nothrow) char *strcpy(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncpy(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 

extern __declspec(__nothrow) char *strcat(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncat(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 






 

extern __declspec(__nothrow) int memcmp(const void *  , const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strcmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int strncmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcasecmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strncasecmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcoll(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   







 

extern __declspec(__nothrow) size_t strxfrm(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   













 


#line 193 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) void *memchr(const void *  , int  , size_t  ) __attribute__((__nonnull__(1)));

   





 

#line 209 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   




 

extern __declspec(__nothrow) size_t strcspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 

#line 232 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strpbrk(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   




 

#line 247 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strrchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   





 

extern __declspec(__nothrow) size_t strspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   



 

#line 270 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strstr(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   





 

extern __declspec(__nothrow) char *strtok(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) char *_strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

extern __declspec(__nothrow) char *strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

   

































 

extern __declspec(__nothrow) void *memset(void *  , int  , size_t  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) char *strerror(int  );
   





 
extern __declspec(__nothrow) size_t strlen(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) size_t strlcpy(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   
















 

extern __declspec(__nothrow) size_t strlcat(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






















 

extern __declspec(__nothrow) void _membitcpybl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpybb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
    














































 







#line 502 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"



 

#line 2 "Main\\KeyPad.c"
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










#line 3 "Main\\KeyPad.c"
#line 1 "Main\\KeyPad.h"



#line 5 "Main\\KeyPad.h"

extern u8	*pUsesKP485;

extern u8	*pAddrKPCtrl;



extern s16 *pDrDelay;

extern s16 *pDCTime;

extern s16 *pPercVmin;

#line 25 "Main\\KeyPad.h"
extern s16	*pYmove; 
extern s16	*pZmove;
extern s16	*pXmove;
extern s16	*pUnusedmove;



extern s16 *pBtn5;

extern s16 *pAxisSwitch;

extern s16 *pBUZZ;



void KPInit(void);
void KPQuery(void);
void KPAnswer(u8 * buffer,u16 len);




#line 4 "Main\\KeyPad.c"
#line 1 "Main\\modbus.h"



#line 5 "Main\\modbus.h"










typedef void(*TPackHandler)(u8 * buffer,u16 len);

extern u8 mbFixBuf1[256];

extern volatile u8 WaitFlag;


void mbSetHandler(u8 num,TPackHandler ph);


void mbSetSpeed(u8 num,u32 sp);


void mbRecvBuffer(u8 num, u8 * buffer,u16 len);


void mbIdle(u8 num);



void mbByteToPack(u8 num,u8 b);


void mbWordToPack(u8 num,u16 w);


void mbWordToPackNoSwap(u8 num,u16 w);


void mbBufferToPack (u8 num,u8 * buffer,u16 len);


void mbSendPack(u8 num);


void mbPackToQueue(u8 transit); 


void mbInsPackToQueue(u8 transit,u8 ofs);


void mbCmd485(u8 devaddr,u8 cmd,u16 regaddr,u16 count);


void mbInsCmd485(u8 devaddr,u8 cmd,u16 regaddr,u16 count,u8 ofs);


u16 swap (u16 w);

#line 5 "Main\\KeyPad.c"
#line 1 "Main\\queue.h"



#line 5 "Main\\queue.h"













typedef struct tagTQUItem {
	u8 buf[50]; 		
	u16 len;					
	u8 qbuf[50];		
	u16 qlen;					
	u8 repcount;				
	u16 timeout;				
	u8 transit;					
} TQUItem;


typedef TQUItem TAQueue[30];

typedef struct tagTQueue {
	TAQueue aqu; 	
	u16 head; 		
	u16 tail;		
	u8 stage;		
} TQueue;

extern TQueue qu; 


void InitQueue(void);


void QueueProcessing(void);


s8	quAddPack(u8 * buffer,u16 len,u8 transit);


s8	quInsPack(u8 * buffer,u16 len,u8 transit,u8 ofs);


void quFixAnswer(u8 * buffer,u16 len);


u8 quPackCount(void);


#line 6 "Main\\KeyPad.c"


u8	*pUsesKP485; 

u8	*pAddrKPCtrl; 



s16 *pDrDelay;

s16 *pDCTime;

s16 *pPercVmin;

#line 27 "Main\\KeyPad.c"
s16	*pYmove; 
s16	*pZmove;
s16	*pXmove;
s16	*pUnusedmove;


s16 *pBtn5;

s16 *pAxisSwitch;

s16 *pBUZZ;


void KPInit(void){
	if (*pUsesKP485) {
		
	
		
		mbCmd485(*pAddrKPCtrl,5,1111,0xFF00);
		
		mbCmd485(*pAddrKPCtrl,6,1200,*pDrDelay); 
		mbCmd485(*pAddrKPCtrl,6,1201,*pDCTime);  
		
		mbCmd485(*pAddrKPCtrl,6,1202,*pPercVmin);
	}
}

void KPQuery(void){
	
	mbCmd485(*pAddrKPCtrl,3,1200,12);
}

void KPAnswer(u8 * buffer,u16 len){
	u16 Addr;
	u8 i;
	s16 wbuf[10];


	if ((*(buffer+1)==3)&&(*(buffer+2)>=20)){
		
		
		memcpy(&Addr,&(qu.aqu[qu.head].buf[2]),2);
		Addr = swap(Addr);
		
		if (Addr == 1200) {
			
			
			memcpy((u8*)wbuf,(buffer+3),20);
			for (i=0;i<10;i++) {wbuf[i]=swap(wbuf[i]);}
			
			if (*pUsesKP485) {
				
				wbuf[3] = - wbuf[3];
				wbuf[4] = - wbuf[4];
				
				memcpy((u8*)pDrDelay,(u8*)wbuf,20);
			}
		}
	}
}
