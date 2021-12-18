#line 1 "Main\\FS.c"








#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"
 
 
 





 






 







 




  
 








#line 47 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"


  



    typedef unsigned int size_t;    









 
 

 



    typedef struct __va_list __va_list;






   




 




typedef struct __fpos_t_struct {
    unsigned __int64 __pos;
    



 
    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
   


 


   

 

typedef struct __FILE FILE;
   






 

#line 136 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"


extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;

#line 166 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"
    

    

    





     



   


 


   


 

   



 

   


 




   


 





    


 






extern __declspec(__nothrow) int remove(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int rename(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) FILE *tmpfile(void);
   




 
extern __declspec(__nothrow) char *tmpnam(char *  );
   











 

extern __declspec(__nothrow) int fclose(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) int fflush(FILE *  );
   







 
extern __declspec(__nothrow) FILE *fopen(const char * __restrict  ,
                           const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   








































 
extern __declspec(__nothrow) FILE *freopen(const char * __restrict  ,
                    const char * __restrict  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(2,3)));
   








 
extern __declspec(__nothrow) void setbuf(FILE * __restrict  ,
                    char * __restrict  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) int setvbuf(FILE * __restrict  ,
                   char * __restrict  ,
                   int  , size_t  ) __attribute__((__nonnull__(1)));
   















 
#pragma __printf_args
extern __declspec(__nothrow) int fprintf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   


















 
#pragma __printf_args
extern __declspec(__nothrow) int _fprintf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   




 
#pragma __printf_args
extern __declspec(__nothrow) int _printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






 
#pragma __printf_args
extern __declspec(__nothrow) int _sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int __ARM_snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));


#pragma __printf_args
extern __declspec(__nothrow) int snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   















 

#pragma __printf_args
extern __declspec(__nothrow) int _snprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int fscanf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






























 
#pragma __scanf_args
extern __declspec(__nothrow) int _fscanf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   






 
#pragma __scanf_args
extern __declspec(__nothrow) int _scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int sscanf(const char * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   








 
#pragma __scanf_args
extern __declspec(__nothrow) int _sscanf(const char * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

 
extern __declspec(__nothrow) int vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int _vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int _vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int _vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int __ARM_vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int _vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int vfprintf(FILE * __restrict  ,
                    const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int vsprintf(char * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int __ARM_vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));

extern __declspec(__nothrow) int vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   







 

extern __declspec(__nothrow) int _vsprintf(char * __restrict  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vfprintf(FILE * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vsnprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int asprintf(char **  , const char * __restrict  , ...) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) int vasprintf(char **  , const char * __restrict  , __va_list  ) __attribute__((__nonnull__(2)));

#pragma __printf_args
extern __declspec(__nothrow) int __ARM_asprintf(char **  , const char * __restrict  , ...) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) int __ARM_vasprintf(char **  , const char * __restrict  , __va_list  ) __attribute__((__nonnull__(2)));
   








 

extern __declspec(__nothrow) int fgetc(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) char *fgets(char * __restrict  , int  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   










 
extern __declspec(__nothrow) int fputc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   







 
extern __declspec(__nothrow) int fputs(const char * __restrict  , FILE * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int getc(FILE *  ) __attribute__((__nonnull__(1)));
   







 




    extern __declspec(__nothrow) int (getchar)(void);

   





 
extern __declspec(__nothrow) char *gets(char *  ) __attribute__((__nonnull__(1)));
   









 
extern __declspec(__nothrow) int putc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   





 




    extern __declspec(__nothrow) int (putchar)(int  );

   



 
extern __declspec(__nothrow) int puts(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int ungetc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   






















 

extern __declspec(__nothrow) size_t fread(void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   











 

extern __declspec(__nothrow) size_t __fread_bytes_avail(void * __restrict  ,
                    size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   











 

extern __declspec(__nothrow) size_t fwrite(const void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   







 

extern __declspec(__nothrow) int fgetpos(FILE * __restrict  , fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) int fseek(FILE *  , long int  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) int fsetpos(FILE * __restrict  , const fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   










 
extern __declspec(__nothrow) long int ftell(FILE *  ) __attribute__((__nonnull__(1)));
   











 
extern __declspec(__nothrow) void rewind(FILE *  ) __attribute__((__nonnull__(1)));
   





 

extern __declspec(__nothrow) void clearerr(FILE *  ) __attribute__((__nonnull__(1)));
   




 

extern __declspec(__nothrow) int feof(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) int ferror(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) void perror(const char *  );
   









 

extern __declspec(__nothrow) int _fisatty(FILE *   ) __attribute__((__nonnull__(1)));
    
 

extern __declspec(__nothrow) void __use_no_semihosting_swi(void);
extern __declspec(__nothrow) void __use_no_semihosting(void);
    





 











#line 1021 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"



 

#line 10 "Main\\FS.c"

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



 

#line 12 "Main\\FS.c"

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










#line 14 "Main\\FS.c"
#line 1 ".\\UCNC\\Tools.h"








#line 12 ".\\UCNC\\Tools.h"




















u8 CRC8(u8 *ptr, u8 crc, u16 len);

float sqr(float x);
int Round(float f);
s32 abss32(s32 a);



#line 15 "Main\\FS.c"
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




#line 16 "Main\\FS.c"
#line 1 ".\\UCNC\\Flash.h"













#line 1 "C:\\Keil_v5\\ARM\\Inc\\NXP\\LPC17xx\\LPC17xx.h"
 






















 









 



 

 
typedef enum IRQn
{
 
  Reset_IRQn                    = -15,       
  NonMaskableInt_IRQn           = -14,       
  HardFault_IRQn                = -13,       
  MemoryManagement_IRQn         = -12,       
  BusFault_IRQn                 = -11,       
  UsageFault_IRQn               = -10,       
  SVCall_IRQn                   = -5,        
  DebugMonitor_IRQn             = -4,        
  PendSV_IRQn                   = -2,        
  SysTick_IRQn                  = -1,        

 
  WDT_IRQn                      = 0,         
  TIMER0_IRQn                   = 1,         
  TIMER1_IRQn                   = 2,         
  TIMER2_IRQn                   = 3,         
  TIMER3_IRQn                   = 4,         
  UART0_IRQn                    = 5,         
  UART1_IRQn                    = 6,         
  UART2_IRQn                    = 7,         
  UART3_IRQn                    = 8,         
  PWM1_IRQn                     = 9,         
  I2C0_IRQn                     = 10,        
  I2C1_IRQn                     = 11,        
  I2C2_IRQn                     = 12,        
  SPI_IRQn                      = 13,        
  SSP0_IRQn                     = 14,        
  SSP1_IRQn                     = 15,        
  PLL0_IRQn                     = 16,        
  RTC_IRQn                      = 17,        
  EINT0_IRQn                    = 18,        
  EINT1_IRQn                    = 19,        
  EINT2_IRQn                    = 20,        
  EINT3_IRQn                    = 21,        
  ADC_IRQn                      = 22,        
  BOD_IRQn                      = 23,        
  USB_IRQn                      = 24,        
  CAN_IRQn                      = 25,        
  DMA_IRQn                      = 26,        
  I2S_IRQn                      = 27,        
  ENET_IRQn                     = 28,        
  RIT_IRQn                      = 29,        
  MCPWM_IRQn                    = 30,        
  QEI_IRQn                      = 31,        
  PLL1_IRQn                     = 32,        
  USBActivity_IRQn              = 33,        
  CANActivity_IRQn              = 34,        
} IRQn_Type;






 

 





#line 1 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm3.h"
 







 

























 
























 




 


 

 













#line 110 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm3.h"


 







#line 145 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm3.h"

#line 147 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm3.h"
#line 1 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cmInstr.h"
 







 

























 






 



 


 









 







 







 






 








 







 







 









 









 

__attribute__((section(".rev16_text"))) static __inline __asm uint32_t __REV16(uint32_t value)
{
  rev16 r0, r0
  bx lr
}








 

__attribute__((section(".revsh_text"))) static __inline __asm int32_t __REVSH(int32_t value)
{
  revsh r0, r0
  bx lr
}










 










 











 









 









 









 











 











 











 







 










 










 









 





#line 684 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cmInstr.h"

   

#line 148 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm3.h"
#line 1 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cmFunc.h"
 







 

























 






 



 


 





 
 






 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}







 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}







 
static __inline uint32_t __get_IPSR(void)
{
  register uint32_t __regIPSR          __asm("ipsr");
  return(__regIPSR);
}







 
static __inline uint32_t __get_APSR(void)
{
  register uint32_t __regAPSR          __asm("apsr");
  return(__regAPSR);
}







 
static __inline uint32_t __get_xPSR(void)
{
  register uint32_t __regXPSR          __asm("xpsr");
  return(__regXPSR);
}







 
static __inline uint32_t __get_PSP(void)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  return(__regProcessStackPointer);
}







 
static __inline void __set_PSP(uint32_t topOfProcStack)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  __regProcessStackPointer = topOfProcStack;
}







 
static __inline uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  return(__regMainStackPointer);
}







 
static __inline void __set_MSP(uint32_t topOfMainStack)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  __regMainStackPointer = topOfMainStack;
}







 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}







 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}








 







 








 
static __inline uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __asm("basepri");
  return(__regBasePri);
}







 
static __inline void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __asm("basepri");
  __regBasePri = (basePri & 0xff);
}







 
static __inline uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  return(__regFaultMask);
}







 
static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & (uint32_t)1);
}




#line 307 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cmFunc.h"


#line 634 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cmFunc.h"

 

#line 149 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm3.h"








 
#line 179 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm3.h"

 






 
#line 195 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm3.h"

 












 


 





 


 
typedef union
{
  struct
  {

    uint32_t _reserved0:27;               





    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} APSR_Type;



 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:23;               
  } b;                                    
  uint32_t w;                             
} IPSR_Type;



 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       

    uint32_t _reserved0:15;               





    uint32_t T:1;                         
    uint32_t IT:2;                        
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} xPSR_Type;



 
typedef union
{
  struct
  {
    uint32_t nPRIV:1;                     
    uint32_t SPSEL:1;                     
    uint32_t FPCA:1;                      
    uint32_t _reserved0:29;               
  } b;                                    
  uint32_t w;                             
} CONTROL_Type;

 






 


 
typedef struct
{
  volatile uint32_t ISER[8];                  
       uint32_t RESERVED0[24];
  volatile uint32_t ICER[8];                  
       uint32_t RSERVED1[24];
  volatile uint32_t ISPR[8];                  
       uint32_t RESERVED2[24];
  volatile uint32_t ICPR[8];                  
       uint32_t RESERVED3[24];
  volatile uint32_t IABR[8];                  
       uint32_t RESERVED4[56];
  volatile uint8_t  IP[240];                  
       uint32_t RESERVED5[644];
  volatile  uint32_t STIR;                     
}  NVIC_Type;

 



 






 


 
typedef struct
{
  volatile const  uint32_t CPUID;                    
  volatile uint32_t ICSR;                     
  volatile uint32_t VTOR;                     
  volatile uint32_t AIRCR;                    
  volatile uint32_t SCR;                      
  volatile uint32_t CCR;                      
  volatile uint8_t  SHP[12];                  
  volatile uint32_t SHCSR;                    
  volatile uint32_t CFSR;                     
  volatile uint32_t HFSR;                     
  volatile uint32_t DFSR;                     
  volatile uint32_t MMFAR;                    
  volatile uint32_t BFAR;                     
  volatile uint32_t AFSR;                     
  volatile const  uint32_t PFR[2];                   
  volatile const  uint32_t DFR;                      
  volatile const  uint32_t ADR;                      
  volatile const  uint32_t MMFR[4];                  
  volatile const  uint32_t ISAR[5];                  
       uint32_t RESERVED0[5];
  volatile uint32_t CPACR;                    
} SCB_Type;

 















 






























 




#line 422 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm3.h"

 





















 









 


















 










































 









 









 















 






 


 
typedef struct
{
       uint32_t RESERVED0[1];
  volatile const  uint32_t ICTR;                     



       uint32_t RESERVED1[1];

} SCnSCB_Type;

 



 










 






 


 
typedef struct
{
  volatile uint32_t CTRL;                     
  volatile uint32_t LOAD;                     
  volatile uint32_t VAL;                      
  volatile const  uint32_t CALIB;                    
} SysTick_Type;

 












 



 



 









 






 


 
typedef struct
{
  volatile  union
  {
    volatile  uint8_t    u8;                   
    volatile  uint16_t   u16;                  
    volatile  uint32_t   u32;                  
  }  PORT [32];                           
       uint32_t RESERVED0[864];
  volatile uint32_t TER;                      
       uint32_t RESERVED1[15];
  volatile uint32_t TPR;                      
       uint32_t RESERVED2[15];
  volatile uint32_t TCR;                      
       uint32_t RESERVED3[29];
  volatile  uint32_t IWR;                      
  volatile const  uint32_t IRR;                      
  volatile uint32_t IMCR;                     
       uint32_t RESERVED4[43];
  volatile  uint32_t LAR;                      
  volatile const  uint32_t LSR;                      
       uint32_t RESERVED5[6];
  volatile const  uint32_t PID4;                     
  volatile const  uint32_t PID5;                     
  volatile const  uint32_t PID6;                     
  volatile const  uint32_t PID7;                     
  volatile const  uint32_t PID0;                     
  volatile const  uint32_t PID1;                     
  volatile const  uint32_t PID2;                     
  volatile const  uint32_t PID3;                     
  volatile const  uint32_t CID0;                     
  volatile const  uint32_t CID1;                     
  volatile const  uint32_t CID2;                     
  volatile const  uint32_t CID3;                     
} ITM_Type;

 



 



























 



 



 



 









   






 


 
typedef struct
{
  volatile uint32_t CTRL;                     
  volatile uint32_t CYCCNT;                   
  volatile uint32_t CPICNT;                   
  volatile uint32_t EXCCNT;                   
  volatile uint32_t SLEEPCNT;                 
  volatile uint32_t LSUCNT;                   
  volatile uint32_t FOLDCNT;                  
  volatile const  uint32_t PCSR;                     
  volatile uint32_t COMP0;                    
  volatile uint32_t MASK0;                    
  volatile uint32_t FUNCTION0;                
       uint32_t RESERVED0[1];
  volatile uint32_t COMP1;                    
  volatile uint32_t MASK1;                    
  volatile uint32_t FUNCTION1;                
       uint32_t RESERVED1[1];
  volatile uint32_t COMP2;                    
  volatile uint32_t MASK2;                    
  volatile uint32_t FUNCTION2;                
       uint32_t RESERVED2[1];
  volatile uint32_t COMP3;                    
  volatile uint32_t MASK3;                    
  volatile uint32_t FUNCTION3;                
} DWT_Type;

 






















































 



 



 



 



 



 



 



























   






 


 
typedef struct
{
  volatile uint32_t SSPSR;                    
  volatile uint32_t CSPSR;                    
       uint32_t RESERVED0[2];
  volatile uint32_t ACPR;                     
       uint32_t RESERVED1[55];
  volatile uint32_t SPPR;                     
       uint32_t RESERVED2[131];
  volatile const  uint32_t FFSR;                     
  volatile uint32_t FFCR;                     
  volatile const  uint32_t FSCR;                     
       uint32_t RESERVED3[759];
  volatile const  uint32_t TRIGGER;                  
  volatile const  uint32_t FIFO0;                    
  volatile const  uint32_t ITATBCTR2;                
       uint32_t RESERVED4[1];
  volatile const  uint32_t ITATBCTR0;                
  volatile const  uint32_t FIFO1;                    
  volatile uint32_t ITCTRL;                   
       uint32_t RESERVED5[39];
  volatile uint32_t CLAIMSET;                 
  volatile uint32_t CLAIMCLR;                 
       uint32_t RESERVED7[8];
  volatile const  uint32_t DEVID;                    
  volatile const  uint32_t DEVTYPE;                  
} TPI_Type;

 



 



 












 






 



 





















 



 





















 



 



 


















 






   







 


 
typedef struct
{
  volatile const  uint32_t TYPE;                     
  volatile uint32_t CTRL;                     
  volatile uint32_t RNR;                      
  volatile uint32_t RBAR;                     
  volatile uint32_t RASR;                     
  volatile uint32_t RBAR_A1;                  
  volatile uint32_t RASR_A1;                  
  volatile uint32_t RBAR_A2;                  
  volatile uint32_t RASR_A2;                  
  volatile uint32_t RBAR_A3;                  
  volatile uint32_t RASR_A3;                  
} MPU_Type;

 









 









 



 









 






























 







 


 
typedef struct
{
  volatile uint32_t DHCSR;                    
  volatile  uint32_t DCRSR;                    
  volatile uint32_t DCRDR;                    
  volatile uint32_t DEMCR;                    
} CoreDebug_Type;

 




































 






 







































 






 

 
#line 1253 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm3.h"

#line 1262 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm3.h"






 










 

 



 




 










 
static __inline void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07);                

  reg_value  =  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR;                                                    
  reg_value &= ~((0xFFFFUL << 16) | (7UL << 8));              
  reg_value  =  (reg_value                                 |
                ((uint32_t)0x5FA << 16) |
                (PriorityGroupTmp << 8));                                      
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR =  reg_value;
}







 
static __inline uint32_t NVIC_GetPriorityGrouping(void)
{
  return ((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8)) >> 8);    
}







 
static __inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}







 
static __inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}











 
static __inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}







 
static __inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}







 
static __inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}










 
static __inline uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
  return((uint32_t)((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IABR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}










 
static __inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[((uint32_t)(IRQn) & 0xF)-4] = ((priority << (8 - 5)) & 0xff); }  
  else {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[(uint32_t)(IRQn)] = ((priority << (8 - 5)) & 0xff);    }         
}












 
static __inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)(((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[((uint32_t)(IRQn) & 0xF)-4] >> (8 - 5)));  }  
  else {
    return((uint32_t)(((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[(uint32_t)(IRQn)]           >> (8 - 5)));  }  
}













 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 5) ? 5 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 5) < 7) ? 0 : PriorityGroupTmp - 7 + 5;

  return (
           ((PreemptPriority & ((1 << (PreemptPriorityBits)) - 1)) << SubPriorityBits) |
           ((SubPriority     & ((1 << (SubPriorityBits    )) - 1)))
         );
}













 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 5) ? 5 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 5) < 7) ? 0 : PriorityGroupTmp - 7 + 5;

  *pPreemptPriority = (Priority >> SubPriorityBits) & ((1 << (PreemptPriorityBits)) - 1);
  *pSubPriority     = (Priority                   ) & ((1 << (SubPriorityBits    )) - 1);
}





 
static __inline void NVIC_SystemReset(void)
{
  __dsb(0xF);                                                     
 
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR  = ((0x5FA << 16)      |
                 (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8)) |
                 (1UL << 2));                    
  __dsb(0xF);                                                      
  while(1);                                                     
}

 



 




 

















 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1) > (0xFFFFFFUL << 0))  return (1);       

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD  = ticks - 1;                                   
  NVIC_SetPriority (SysTick_IRQn, (1<<5) - 1);   
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL   = 0;                                           
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL  = (1UL << 2) |
                   (1UL << 1)   |
                   (1UL << 0);                     
  return (0);                                                   
}



 



 




 

extern volatile int32_t ITM_RxBuffer;                     












 
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if ((((ITM_Type *) (0xE0000000UL) )->TCR & (1UL << 0))                  &&       
      (((ITM_Type *) (0xE0000000UL) )->TER & (1UL << 0)        )                    )      
  {
    while (((ITM_Type *) (0xE0000000UL) )->PORT[0].u32 == 0);
    ((ITM_Type *) (0xE0000000UL) )->PORT[0].u8 = (uint8_t) ch;
  }
  return (ch);
}








 
static __inline int32_t ITM_ReceiveChar (void) {
  int32_t ch = -1;                            

  if (ITM_RxBuffer != 0x5AA55AA5) {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = 0x5AA55AA5;        
  }

  return (ch);
}








 
static __inline int32_t ITM_CheckChar (void) {

  if (ITM_RxBuffer == 0x5AA55AA5) {
    return (0);                                  
  } else {
    return (1);                                  
  }
}

 





#line 107 "C:\\Keil_v5\\ARM\\Inc\\NXP\\LPC17xx\\LPC17xx.h"
#line 1 "C:\\Keil_v5\\ARM\\Inc\\NXP\\LPC17xx\\system_LPC17xx.h"
 





















 









#line 34 "C:\\Keil_v5\\ARM\\Inc\\NXP\\LPC17xx\\system_LPC17xx.h"



 

extern uint32_t SystemCoreClock;      










 
extern void SystemInit (void);









 
extern void SystemCoreClockUpdate (void);







 

#line 108 "C:\\Keil_v5\\ARM\\Inc\\NXP\\LPC17xx\\LPC17xx.h"


 
 
 


#pragma anon_unions


 
 
typedef struct
{
  volatile uint32_t FLASHCFG;                
       uint32_t RESERVED0[31];
  volatile uint32_t PLL0CON;                 
  volatile uint32_t PLL0CFG;
  volatile const  uint32_t PLL0STAT;
  volatile  uint32_t PLL0FEED;
       uint32_t RESERVED1[4];
  volatile uint32_t PLL1CON;
  volatile uint32_t PLL1CFG;
  volatile const  uint32_t PLL1STAT;
  volatile  uint32_t PLL1FEED;
       uint32_t RESERVED2[4];
  volatile uint32_t PCON;
  volatile uint32_t PCONP;
       uint32_t RESERVED3[15];
  volatile uint32_t CCLKCFG;
  volatile uint32_t USBCLKCFG;
  volatile uint32_t CLKSRCSEL;
  volatile uint32_t	CANSLEEPCLR;
  volatile uint32_t	CANWAKEFLAGS;
       uint32_t RESERVED4[10];
  volatile uint32_t EXTINT;                  
       uint32_t RESERVED5;
  volatile uint32_t EXTMODE;
  volatile uint32_t EXTPOLAR;
       uint32_t RESERVED6[12];
  volatile uint32_t RSID;                    
       uint32_t RESERVED7[7];
  volatile uint32_t SCS;                     
  volatile uint32_t IRCTRIM;                 
  volatile uint32_t PCLKSEL0;
  volatile uint32_t PCLKSEL1;
       uint32_t RESERVED8[4];
  volatile uint32_t USBIntSt;                
  volatile uint32_t DMAREQSEL;
  volatile uint32_t CLKOUTCFG;               
 } LPC_SC_TypeDef;

 
 
typedef struct
{
  volatile uint32_t PINSEL0;
  volatile uint32_t PINSEL1;
  volatile uint32_t PINSEL2;
  volatile uint32_t PINSEL3;
  volatile uint32_t PINSEL4;
  volatile uint32_t PINSEL5;
  volatile uint32_t PINSEL6;
  volatile uint32_t PINSEL7;
  volatile uint32_t PINSEL8;
  volatile uint32_t PINSEL9;
  volatile uint32_t PINSEL10;
       uint32_t RESERVED0[5];
  volatile uint32_t PINMODE0;
  volatile uint32_t PINMODE1;
  volatile uint32_t PINMODE2;
  volatile uint32_t PINMODE3;
  volatile uint32_t PINMODE4;
  volatile uint32_t PINMODE5;
  volatile uint32_t PINMODE6;
  volatile uint32_t PINMODE7;
  volatile uint32_t PINMODE8;
  volatile uint32_t PINMODE9;
  volatile uint32_t PINMODE_OD0;
  volatile uint32_t PINMODE_OD1;
  volatile uint32_t PINMODE_OD2;
  volatile uint32_t PINMODE_OD3;
  volatile uint32_t PINMODE_OD4;
  volatile uint32_t I2CPADCFG;
} LPC_PINCON_TypeDef;

 
 
typedef struct
{
  union {
    volatile uint32_t FIODIR;
    struct {
      volatile uint16_t FIODIRL;
      volatile uint16_t FIODIRH;
    };
    struct {
      volatile uint8_t  FIODIR0;
      volatile uint8_t  FIODIR1;
      volatile uint8_t  FIODIR2;
      volatile uint8_t  FIODIR3;
    };
  };
  uint32_t RESERVED0[3];
  union {
    volatile uint32_t FIOMASK;
    struct {
      volatile uint16_t FIOMASKL;
      volatile uint16_t FIOMASKH;
    };
    struct {
      volatile uint8_t  FIOMASK0;
      volatile uint8_t  FIOMASK1;
      volatile uint8_t  FIOMASK2;
      volatile uint8_t  FIOMASK3;
    };
  };
  union {
    volatile uint32_t FIOPIN;
    struct {
      volatile uint16_t FIOPINL;
      volatile uint16_t FIOPINH;
    };
    struct {
      volatile uint8_t  FIOPIN0;
      volatile uint8_t  FIOPIN1;
      volatile uint8_t  FIOPIN2;
      volatile uint8_t  FIOPIN3;
    };
  };
  union {
    volatile uint32_t FIOSET;
    struct {
      volatile uint16_t FIOSETL;
      volatile uint16_t FIOSETH;
    };
    struct {
      volatile uint8_t  FIOSET0;
      volatile uint8_t  FIOSET1;
      volatile uint8_t  FIOSET2;
      volatile uint8_t  FIOSET3;
    };
  };
  union {
    volatile  uint32_t FIOCLR;
    struct {
      volatile  uint16_t FIOCLRL;
      volatile  uint16_t FIOCLRH;
    };
    struct {
      volatile  uint8_t  FIOCLR0;
      volatile  uint8_t  FIOCLR1;
      volatile  uint8_t  FIOCLR2;
      volatile  uint8_t  FIOCLR3;
    };
  };
} LPC_GPIO_TypeDef;

 
typedef struct
{
  volatile const  uint32_t IntStatus;
  volatile const  uint32_t IO0IntStatR;
  volatile const  uint32_t IO0IntStatF;
  volatile  uint32_t IO0IntClr;
  volatile uint32_t IO0IntEnR;
  volatile uint32_t IO0IntEnF;
       uint32_t RESERVED0[3];
  volatile const  uint32_t IO2IntStatR;
  volatile const  uint32_t IO2IntStatF;
  volatile  uint32_t IO2IntClr;
  volatile uint32_t IO2IntEnR;
  volatile uint32_t IO2IntEnF;
} LPC_GPIOINT_TypeDef;

 
 
typedef struct
{
  volatile uint32_t IR;
  volatile uint32_t TCR;
  volatile uint32_t TC;
  volatile uint32_t PR;
  volatile uint32_t PC;
  volatile uint32_t MCR;
  volatile uint32_t MR0;
  volatile uint32_t MR1;
  volatile uint32_t MR2;
  volatile uint32_t MR3;
  volatile uint32_t CCR;
  volatile const  uint32_t CR0;
  volatile const  uint32_t CR1;
       uint32_t RESERVED0[2];
  volatile uint32_t EMR;
       uint32_t RESERVED1[12];
  volatile uint32_t CTCR;
} LPC_TIM_TypeDef;

 
 
typedef struct
{
  volatile uint32_t IR;
  volatile uint32_t TCR;
  volatile uint32_t TC;
  volatile uint32_t PR;
  volatile uint32_t PC;
  volatile uint32_t MCR;
  volatile uint32_t MR0;
  volatile uint32_t MR1;
  volatile uint32_t MR2;
  volatile uint32_t MR3;
  volatile uint32_t CCR;
  volatile const  uint32_t CR0;
  volatile const  uint32_t CR1;
  volatile const  uint32_t CR2;
  volatile const  uint32_t CR3;
       uint32_t RESERVED0;
  volatile uint32_t MR4;
  volatile uint32_t MR5;
  volatile uint32_t MR6;
  volatile uint32_t PCR;
  volatile uint32_t LER;
       uint32_t RESERVED1[7];
  volatile uint32_t CTCR;
} LPC_PWM_TypeDef;

 
 
typedef struct
{
  union {
  volatile const  uint8_t  RBR;
  volatile  uint8_t  THR;
  volatile uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  volatile uint8_t  DLM;
  volatile uint32_t IER;
  };
  union {
  volatile const  uint32_t IIR;
  volatile  uint8_t  FCR;
  };
  volatile uint8_t  LCR;
       uint8_t  RESERVED1[7];
  volatile const  uint8_t  LSR;
       uint8_t  RESERVED2[7];
  volatile uint8_t  SCR;
       uint8_t  RESERVED3[3];
  volatile uint32_t ACR;
  volatile uint8_t  ICR;
       uint8_t  RESERVED4[3];
  volatile uint8_t  FDR;
       uint8_t  RESERVED5[7];
  volatile uint8_t  TER;
} LPC_UART_TypeDef;

 
typedef struct
{
  union {
  volatile const  uint8_t  RBR;
  volatile  uint8_t  THR;
  volatile uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  volatile uint8_t  DLM;
  volatile uint32_t IER;
  };
  union {
  volatile const  uint32_t IIR;
  volatile  uint8_t  FCR;
  };
  volatile uint8_t  LCR;
       uint8_t  RESERVED1[3];
  volatile uint8_t  MCR;
       uint8_t  RESERVED2[3];
  volatile const  uint8_t  LSR;
       uint8_t  RESERVED3[3];
  volatile const  uint8_t  MSR;
       uint8_t  RESERVED4[3];
  volatile uint8_t  SCR;
       uint8_t  RESERVED5[3];
  volatile uint32_t ACR;
       uint32_t RESERVED6;
  volatile uint32_t FDR;
       uint32_t RESERVED7;
  volatile uint8_t  TER;
       uint8_t  RESERVED8[27];
  volatile uint8_t  RS485CTRL;
       uint8_t  RESERVED9[3];
  volatile uint8_t  ADRMATCH;
       uint8_t  RESERVED10[3];
  volatile uint8_t  RS485DLY;
} LPC_UART1_TypeDef;

 
 
typedef struct
{
  volatile uint32_t SPCR;
  volatile const  uint32_t SPSR;
  volatile uint32_t SPDR;
  volatile uint32_t SPCCR;
       uint32_t RESERVED0[3];
  volatile uint32_t SPINT;
} LPC_SPI_TypeDef;

 
 
typedef struct
{
  volatile uint32_t CR0;
  volatile uint32_t CR1;
  volatile uint32_t DR;
  volatile const  uint32_t SR;
  volatile uint32_t CPSR;
  volatile uint32_t IMSC;
  volatile uint32_t RIS;
  volatile uint32_t MIS;
  volatile uint32_t ICR;
  volatile uint32_t DMACR;
} LPC_SSP_TypeDef;

 
 
typedef struct
{
  volatile uint32_t I2CONSET;
  volatile const  uint32_t I2STAT;
  volatile uint32_t I2DAT;
  volatile uint32_t I2ADR0;
  volatile uint32_t I2SCLH;
  volatile uint32_t I2SCLL;
  volatile  uint32_t I2CONCLR;
  volatile uint32_t MMCTRL;
  volatile uint32_t I2ADR1;
  volatile uint32_t I2ADR2;
  volatile uint32_t I2ADR3;
  volatile const  uint32_t I2DATA_BUFFER;
  volatile uint32_t I2MASK0;
  volatile uint32_t I2MASK1;
  volatile uint32_t I2MASK2;
  volatile uint32_t I2MASK3;
} LPC_I2C_TypeDef;

 
 
typedef struct
{
  volatile uint32_t I2SDAO;
  volatile uint32_t I2SDAI;
  volatile  uint32_t I2STXFIFO;
  volatile const  uint32_t I2SRXFIFO;
  volatile const  uint32_t I2SSTATE;
  volatile uint32_t I2SDMA1;
  volatile uint32_t I2SDMA2;
  volatile uint32_t I2SIRQ;
  volatile uint32_t I2STXRATE;
  volatile uint32_t I2SRXRATE;
  volatile uint32_t I2STXBITRATE;
  volatile uint32_t I2SRXBITRATE;
  volatile uint32_t I2STXMODE;
  volatile uint32_t I2SRXMODE;
} LPC_I2S_TypeDef;

 
 
typedef struct
{
  volatile uint32_t RICOMPVAL;
  volatile uint32_t RIMASK;
  volatile uint8_t  RICTRL;
       uint8_t  RESERVED0[3];
  volatile uint32_t RICOUNTER;
} LPC_RIT_TypeDef;

 
 
typedef struct
{
  volatile uint8_t  ILR;
       uint8_t  RESERVED0[7];
  volatile uint8_t  CCR;
       uint8_t  RESERVED1[3];
  volatile uint8_t  CIIR;
       uint8_t  RESERVED2[3];
  volatile uint8_t  AMR;
       uint8_t  RESERVED3[3];
  volatile const  uint32_t CTIME0;
  volatile const  uint32_t CTIME1;
  volatile const  uint32_t CTIME2;
  volatile uint8_t  SEC;
       uint8_t  RESERVED4[3];
  volatile uint8_t  MIN;
       uint8_t  RESERVED5[3];
  volatile uint8_t  HOUR;
       uint8_t  RESERVED6[3];
  volatile uint8_t  DOM;
       uint8_t  RESERVED7[3];
  volatile uint8_t  DOW;
       uint8_t  RESERVED8[3];
  volatile uint16_t DOY;
       uint16_t RESERVED9;
  volatile uint8_t  MONTH;
       uint8_t  RESERVED10[3];
  volatile uint16_t YEAR;
       uint16_t RESERVED11;
  volatile uint32_t CALIBRATION;
  volatile uint32_t GPREG0;
  volatile uint32_t GPREG1;
  volatile uint32_t GPREG2;
  volatile uint32_t GPREG3;
  volatile uint32_t GPREG4;
  volatile uint8_t  RTC_AUXEN;
       uint8_t  RESERVED12[3];
  volatile uint8_t  RTC_AUX;
       uint8_t  RESERVED13[3];
  volatile uint8_t  ALSEC;
       uint8_t  RESERVED14[3];
  volatile uint8_t  ALMIN;
       uint8_t  RESERVED15[3];
  volatile uint8_t  ALHOUR;
       uint8_t  RESERVED16[3];
  volatile uint8_t  ALDOM;
       uint8_t  RESERVED17[3];
  volatile uint8_t  ALDOW;
       uint8_t  RESERVED18[3];
  volatile uint16_t ALDOY;
       uint16_t RESERVED19;
  volatile uint8_t  ALMON;
       uint8_t  RESERVED20[3];
  volatile uint16_t ALYEAR;
       uint16_t RESERVED21;
} LPC_RTC_TypeDef;

 
 
typedef struct
{
  volatile uint8_t  WDMOD;
       uint8_t  RESERVED0[3];
  volatile uint32_t WDTC;
  volatile  uint8_t  WDFEED;
       uint8_t  RESERVED1[3];
  volatile const  uint32_t WDTV;
  volatile uint32_t WDCLKSEL;
} LPC_WDT_TypeDef;

 
 
typedef struct
{
  volatile uint32_t ADCR;
  volatile uint32_t ADGDR;
       uint32_t RESERVED0;
  volatile uint32_t ADINTEN;
  volatile const  uint32_t ADDR0;
  volatile const  uint32_t ADDR1;
  volatile const  uint32_t ADDR2;
  volatile const  uint32_t ADDR3;
  volatile const  uint32_t ADDR4;
  volatile const  uint32_t ADDR5;
  volatile const  uint32_t ADDR6;
  volatile const  uint32_t ADDR7;
  volatile const  uint32_t ADSTAT;
  volatile uint32_t ADTRM;
} LPC_ADC_TypeDef;

 
 
typedef struct
{
  volatile uint32_t DACR;
  volatile uint32_t DACCTRL;
  volatile uint16_t DACCNTVAL;
} LPC_DAC_TypeDef;

 
 
typedef struct
{
  volatile const  uint32_t MCCON;
  volatile  uint32_t MCCON_SET;
  volatile  uint32_t MCCON_CLR;
  volatile const  uint32_t MCCAPCON;
  volatile  uint32_t MCCAPCON_SET;
  volatile  uint32_t MCCAPCON_CLR;
  volatile uint32_t MCTIM0;
  volatile uint32_t MCTIM1;
  volatile uint32_t MCTIM2;
  volatile uint32_t MCPER0;
  volatile uint32_t MCPER1;
  volatile uint32_t MCPER2;
  volatile uint32_t MCPW0;
  volatile uint32_t MCPW1;
  volatile uint32_t MCPW2;
  volatile uint32_t MCDEADTIME;
  volatile uint32_t MCCCP;
  volatile uint32_t MCCR0;
  volatile uint32_t MCCR1;
  volatile uint32_t MCCR2;
  volatile const  uint32_t MCINTEN;
  volatile  uint32_t MCINTEN_SET;
  volatile  uint32_t MCINTEN_CLR;
  volatile const  uint32_t MCCNTCON;
  volatile  uint32_t MCCNTCON_SET;
  volatile  uint32_t MCCNTCON_CLR;
  volatile const  uint32_t MCINTFLAG;
  volatile  uint32_t MCINTFLAG_SET;
  volatile  uint32_t MCINTFLAG_CLR;
  volatile  uint32_t MCCAP_CLR;
} LPC_MCPWM_TypeDef;

 
 
typedef struct
{
  volatile  uint32_t QEICON;
  volatile const  uint32_t QEISTAT;
  volatile uint32_t QEICONF;
  volatile const  uint32_t QEIPOS;
  volatile uint32_t QEIMAXPOS;
  volatile uint32_t CMPOS0;
  volatile uint32_t CMPOS1;
  volatile uint32_t CMPOS2;
  volatile const  uint32_t INXCNT;
  volatile uint32_t INXCMP;
  volatile uint32_t QEILOAD;
  volatile const  uint32_t QEITIME;
  volatile const  uint32_t QEIVEL;
  volatile const  uint32_t QEICAP;
  volatile uint32_t VELCOMP;
  volatile uint32_t FILTER;
       uint32_t RESERVED0[998];
  volatile  uint32_t QEIIEC;
  volatile  uint32_t QEIIES;
  volatile const  uint32_t QEIINTSTAT;
  volatile const  uint32_t QEIIE;
  volatile  uint32_t QEICLR;
  volatile  uint32_t QEISET;
} LPC_QEI_TypeDef;

 
 
typedef struct
{
  volatile uint32_t mask[512];               
} LPC_CANAF_RAM_TypeDef;

 
typedef struct                           
{
  volatile uint32_t AFMR;
  volatile uint32_t SFF_sa;
  volatile uint32_t SFF_GRP_sa;
  volatile uint32_t EFF_sa;
  volatile uint32_t EFF_GRP_sa;
  volatile uint32_t ENDofTable;
  volatile const  uint32_t LUTerrAd;
  volatile const  uint32_t LUTerr;
  volatile uint32_t FCANIE;
  volatile uint32_t FCANIC0;
  volatile uint32_t FCANIC1;
} LPC_CANAF_TypeDef;

 
typedef struct                           
{
  volatile const  uint32_t CANTxSR;
  volatile const  uint32_t CANRxSR;
  volatile const  uint32_t CANMSR;
} LPC_CANCR_TypeDef;

 
typedef struct                           
{
  volatile uint32_t MOD;
  volatile  uint32_t CMR;
  volatile uint32_t GSR;
  volatile const  uint32_t ICR;
  volatile uint32_t IER;
  volatile uint32_t BTR;
  volatile uint32_t EWL;
  volatile const  uint32_t SR;
  volatile uint32_t RFS;
  volatile uint32_t RID;
  volatile uint32_t RDA;
  volatile uint32_t RDB;
  volatile uint32_t TFI1;
  volatile uint32_t TID1;
  volatile uint32_t TDA1;
  volatile uint32_t TDB1;
  volatile uint32_t TFI2;
  volatile uint32_t TID2;
  volatile uint32_t TDA2;
  volatile uint32_t TDB2;
  volatile uint32_t TFI3;
  volatile uint32_t TID3;
  volatile uint32_t TDA3;
  volatile uint32_t TDB3;
} LPC_CAN_TypeDef;

 
 
typedef struct                           
{
  volatile const  uint32_t DMACIntStat;
  volatile const  uint32_t DMACIntTCStat;
  volatile  uint32_t DMACIntTCClear;
  volatile const  uint32_t DMACIntErrStat;
  volatile  uint32_t DMACIntErrClr;
  volatile const  uint32_t DMACRawIntTCStat;
  volatile const  uint32_t DMACRawIntErrStat;
  volatile const  uint32_t DMACEnbldChns;
  volatile uint32_t DMACSoftBReq;
  volatile uint32_t DMACSoftSReq;
  volatile uint32_t DMACSoftLBReq;
  volatile uint32_t DMACSoftLSReq;
  volatile uint32_t DMACConfig;
  volatile uint32_t DMACSync;
} LPC_GPDMA_TypeDef;

 
typedef struct                           
{
  volatile uint32_t DMACCSrcAddr;
  volatile uint32_t DMACCDestAddr;
  volatile uint32_t DMACCLLI;
  volatile uint32_t DMACCControl;
  volatile uint32_t DMACCConfig;
} LPC_GPDMACH_TypeDef;

 
 
typedef struct
{
  volatile const  uint32_t HcRevision;              
  volatile uint32_t HcControl;
  volatile uint32_t HcCommandStatus;
  volatile uint32_t HcInterruptStatus;
  volatile uint32_t HcInterruptEnable;
  volatile uint32_t HcInterruptDisable;
  volatile uint32_t HcHCCA;
  volatile const  uint32_t HcPeriodCurrentED;
  volatile uint32_t HcControlHeadED;
  volatile uint32_t HcControlCurrentED;
  volatile uint32_t HcBulkHeadED;
  volatile uint32_t HcBulkCurrentED;
  volatile const  uint32_t HcDoneHead;
  volatile uint32_t HcFmInterval;
  volatile const  uint32_t HcFmRemaining;
  volatile const  uint32_t HcFmNumber;
  volatile uint32_t HcPeriodicStart;
  volatile uint32_t HcLSTreshold;
  volatile uint32_t HcRhDescriptorA;
  volatile uint32_t HcRhDescriptorB;
  volatile uint32_t HcRhStatus;
  volatile uint32_t HcRhPortStatus1;
  volatile uint32_t HcRhPortStatus2;
       uint32_t RESERVED0[40];
  volatile const  uint32_t Module_ID;

  volatile const  uint32_t OTGIntSt;                
  volatile uint32_t OTGIntEn;
  volatile  uint32_t OTGIntSet;
  volatile  uint32_t OTGIntClr;
  volatile uint32_t OTGStCtrl;
  volatile uint32_t OTGTmr;
       uint32_t RESERVED1[58];

  volatile const  uint32_t USBDevIntSt;             
  volatile uint32_t USBDevIntEn;
  volatile  uint32_t USBDevIntClr;
  volatile  uint32_t USBDevIntSet;

  volatile  uint32_t USBCmdCode;              
  volatile const  uint32_t USBCmdData;

  volatile const  uint32_t USBRxData;               
  volatile  uint32_t USBTxData;
  volatile const  uint32_t USBRxPLen;
  volatile  uint32_t USBTxPLen;
  volatile uint32_t USBCtrl;
  volatile  uint32_t USBDevIntPri;

  volatile const  uint32_t USBEpIntSt;              
  volatile uint32_t USBEpIntEn;
  volatile  uint32_t USBEpIntClr;
  volatile  uint32_t USBEpIntSet;
  volatile  uint32_t USBEpIntPri;

  volatile uint32_t USBReEp;                 
  volatile  uint32_t USBEpInd;
  volatile uint32_t USBMaxPSize;

  volatile const  uint32_t USBDMARSt;               
  volatile  uint32_t USBDMARClr;
  volatile  uint32_t USBDMARSet;
       uint32_t RESERVED2[9];
  volatile uint32_t USBUDCAH;
  volatile const  uint32_t USBEpDMASt;
  volatile  uint32_t USBEpDMAEn;
  volatile  uint32_t USBEpDMADis;
  volatile const  uint32_t USBDMAIntSt;
  volatile uint32_t USBDMAIntEn;
       uint32_t RESERVED3[2];
  volatile const  uint32_t USBEoTIntSt;
  volatile  uint32_t USBEoTIntClr;
  volatile  uint32_t USBEoTIntSet;
  volatile const  uint32_t USBNDDRIntSt;
  volatile  uint32_t USBNDDRIntClr;
  volatile  uint32_t USBNDDRIntSet;
  volatile const  uint32_t USBSysErrIntSt;
  volatile  uint32_t USBSysErrIntClr;
  volatile  uint32_t USBSysErrIntSet;
       uint32_t RESERVED4[15];

  union {
  volatile const  uint32_t I2C_RX;                  
  volatile  uint32_t I2C_TX;
  };
  volatile const  uint32_t I2C_STS;
  volatile uint32_t I2C_CTL;
  volatile uint32_t I2C_CLKHI;
  volatile  uint32_t I2C_CLKLO;
       uint32_t RESERVED5[824];

  union {
  volatile uint32_t USBClkCtrl;              
  volatile uint32_t OTGClkCtrl;
  };
  union {
  volatile const  uint32_t USBClkSt;
  volatile const  uint32_t OTGClkSt;
  };
} LPC_USB_TypeDef;

 
 
typedef struct
{
  volatile uint32_t MAC1;                    
  volatile uint32_t MAC2;
  volatile uint32_t IPGT;
  volatile uint32_t IPGR;
  volatile uint32_t CLRT;
  volatile uint32_t MAXF;
  volatile uint32_t SUPP;
  volatile uint32_t TEST;
  volatile uint32_t MCFG;
  volatile uint32_t MCMD;
  volatile uint32_t MADR;
  volatile  uint32_t MWTD;
  volatile const  uint32_t MRDD;
  volatile const  uint32_t MIND;
       uint32_t RESERVED0[2];
  volatile uint32_t SA0;
  volatile uint32_t SA1;
  volatile uint32_t SA2;
       uint32_t RESERVED1[45];
  volatile uint32_t Command;                 
  volatile const  uint32_t Status;
  volatile uint32_t RxDescriptor;
  volatile uint32_t RxStatus;
  volatile uint32_t RxDescriptorNumber;
  volatile const  uint32_t RxProduceIndex;
  volatile uint32_t RxConsumeIndex;
  volatile uint32_t TxDescriptor;
  volatile uint32_t TxStatus;
  volatile uint32_t TxDescriptorNumber;
  volatile uint32_t TxProduceIndex;
  volatile const  uint32_t TxConsumeIndex;
       uint32_t RESERVED2[10];
  volatile const  uint32_t TSV0;
  volatile const  uint32_t TSV1;
  volatile const  uint32_t RSV;
       uint32_t RESERVED3[3];
  volatile uint32_t FlowControlCounter;
  volatile const  uint32_t FlowControlStatus;
       uint32_t RESERVED4[34];
  volatile uint32_t RxFilterCtrl;            
  volatile uint32_t RxFilterWoLStatus;
  volatile uint32_t RxFilterWoLClear;
       uint32_t RESERVED5;
  volatile uint32_t HashFilterL;
  volatile uint32_t HashFilterH;
       uint32_t RESERVED6[882];
  volatile const  uint32_t IntStatus;               
  volatile uint32_t IntEnable;
  volatile  uint32_t IntClear;
  volatile  uint32_t IntSet;
       uint32_t RESERVED7;
  volatile uint32_t PowerDown;
       uint32_t RESERVED8;
  volatile uint32_t Module_ID;
} LPC_EMAC_TypeDef;



#pragma no_anon_unions



 
 
 
 
#line 933 "C:\\Keil_v5\\ARM\\Inc\\NXP\\LPC17xx\\LPC17xx.h"

 
#line 954 "C:\\Keil_v5\\ARM\\Inc\\NXP\\LPC17xx\\LPC17xx.h"

 
#line 968 "C:\\Keil_v5\\ARM\\Inc\\NXP\\LPC17xx\\LPC17xx.h"

 
#line 981 "C:\\Keil_v5\\ARM\\Inc\\NXP\\LPC17xx\\LPC17xx.h"

 






 
 
 
#line 1039 "C:\\Keil_v5\\ARM\\Inc\\NXP\\LPC17xx\\LPC17xx.h"



 

#line 15 ".\\UCNC\\Flash.h"

#line 17 ".\\UCNC\\Flash.h"
#line 1 ".\\Drivers\\LPC1768_define.h"





 
 
 










 
 
 






#line 36 ".\\Drivers\\LPC1768_define.h"

#line 53 ".\\Drivers\\LPC1768_define.h"

#line 310 ".\\Drivers\\LPC1768_define.h"


 
 
 
#line 347 ".\\Drivers\\LPC1768_define.h"


 
 
 




#line 367 ".\\Drivers\\LPC1768_define.h"




#line 378 ".\\Drivers\\LPC1768_define.h"











 
 
 




#line 428 ".\\Drivers\\LPC1768_define.h"





#line 445 ".\\Drivers\\LPC1768_define.h"



#line 464 ".\\Drivers\\LPC1768_define.h"






#line 482 ".\\Drivers\\LPC1768_define.h"











#line 499 ".\\Drivers\\LPC1768_define.h"












#line 519 ".\\Drivers\\LPC1768_define.h"



#line 534 ".\\Drivers\\LPC1768_define.h"
























#line 574 ".\\Drivers\\LPC1768_define.h"

























#line 606 ".\\Drivers\\LPC1768_define.h"

#line 613 ".\\Drivers\\LPC1768_define.h"























#line 650 ".\\Drivers\\LPC1768_define.h"





#line 669 ".\\Drivers\\LPC1768_define.h"























#line 703 ".\\Drivers\\LPC1768_define.h"




































































































































































































































































































#line 1027 ".\\Drivers\\LPC1768_define.h"





#line 1064 ".\\Drivers\\LPC1768_define.h"





#line 1101 ".\\Drivers\\LPC1768_define.h"





#line 1138 ".\\Drivers\\LPC1768_define.h"





#line 1175 ".\\Drivers\\LPC1768_define.h"


 
 
 








#line 1220 ".\\Drivers\\LPC1768_define.h"

#line 1253 ".\\Drivers\\LPC1768_define.h"


 
 
 








 
 
 
























#line 1300 ".\\Drivers\\LPC1768_define.h"

#line 1308 ".\\Drivers\\LPC1768_define.h"









#line 18 ".\\UCNC\\Flash.h"








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


#line 17 "Main\\FS.c"

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

#line 19 "Main\\FS.c"

























u8 FLASH_BANKS_NUM=0;






enum constFSState {
	FS_STATE_FLASH_CLEAR	= 0xFF,											

	FS_STATE_READY			= 0xFC,											






};








 


enum constFCSState {
	FCS_STATE_CLOSED,														
	FCS_STATE_OPENED,														
	FCS_STATE_OPENED_READ,													
	FCS_STATE_OPENED_WRITE													
};



enum constFileAttr {
	FILE_ATTR_NOATTR   = 0xFF,												
	FILE_ATTR_READONLY = 0xFE,												
	FILE_ATTR_HIDDEN   = 0xFD,												
	FILE_ATTR_SYSTEM   = 0xFB,												

};



typedef __packed struct {
	u8  FullName[1 + 14 + 3 + 1];				
	u8  Attribute;															
	u16 FirstCluster;														
	u32 Size;																
	
} tFNT;



typedef __packed struct {
	u8  Flag;
	u16 NextCluster;
} tCAT;



typedef __packed struct {
	u8  State;																
	u8  Name[14 + 1];											
	u8  Type[3 + 1];											
	u32 FNT_num;															
	u16 CurrCluster;														
	u8  CurrPage;															
	u16 PageBufPtr;															
	u8  PageBuffer[256];												
	u32 RemainSize;															
	u32 MinFilePosition;													
	u32 MaxFilePosition;													
	tFNT FNT;																
} tFCS;



tFCS  *pFCSArray[8];


tFCS  FCSArray[8];



enum constFS_PARAM {
   FS_PARAM_FS_STATE = (0),									
};







u8  FS_IS_INITED;														

u8  FS_STATE;																	



u16 SECTORS_NUMBER;																
u32 SECTOR_SIZE;																

u16 CLUSTERS_PER_SECTOR;														
u16 CLUSTERS_NUMBER;															
u16 ClusterMAX;																	
u16 CLUSTER_SIZE;																

u32 CAT_Size;																	
u16 CATRecordsNumber;															
u16 CATRecordMAX;																

u32 FNTRecordsNumber;															
u32 FNTRecordMAX;																

u32 CAT_BASE_ADDRESS;															
u32 CLUSTERS_BASE_ADDRESS;														









s8 FS_Init(void) {
	u8 i;

	u8 bank_num;
	u8 ID;

	FLASH_BANKS_NUM = 0;
	FS_IS_INITED = 0;															

	
	for (bank_num = 0; bank_num < 4; bank_num++) {
		
		ID = FLASH_GetBankID(bank_num);

		if (ID == 0x18) {							
			FLASH_BANKS_NUM++;													
		}



		else {
			break;															
		}
	}

	if (! FLASH_BANKS_NUM) {														
		return -1;														
	}





	
	FS_STATE = FLASH_ReadByte(FS_PARAM_FS_STATE);

	
	if (FS_STATE == FS_STATE_FLASH_CLEAR) {

		
		
		FS_STATE = FS_STATE_READY;
		FLASH_WriteByte(FS_PARAM_FS_STATE, FS_STATE);
	}
	
	else if (FS_STATE == FS_STATE_READY) {

	}

	
	
	SECTORS_NUMBER = FLASH_BANKS_NUM * 64;						
	SECTOR_SIZE = 1024 * 256;								

	CLUSTERS_PER_SECTOR = 1024 / 64;				
	CLUSTERS_NUMBER = (SECTORS_NUMBER - 3) * CLUSTERS_PER_SECTOR;					
	CLUSTER_SIZE = 64 * 256;									

	
	CAT_Size = CLUSTERS_NUMBER * 3 / 32 * 32;
	if ( (CLUSTERS_NUMBER * 3) % 32 ) {
		CAT_Size += 32;												
	}
	CATRecordsNumber = CLUSTERS_NUMBER;												

	FNTRecordsNumber = ( (SECTOR_SIZE - CAT_Size) / 32 ) - 1;			

	CAT_BASE_ADDRESS = 32 +
					   FNTRecordsNumber * 32;							
	CLUSTERS_BASE_ADDRESS = SECTOR_SIZE * 3;										

	ClusterMAX   = CLUSTERS_NUMBER  - 1;											
	CATRecordMAX = CATRecordsNumber - 1;											
	FNTRecordMAX = FNTRecordsNumber - 1;											

	
	for (i=0; i<8; i++) {
		pFCSArray[i] = FCSArray + i;
	}

	
	for (i=0; i<8; i++) {
		pFCSArray[i]->State = FCS_STATE_CLOSED ;
	}



	FS_IS_INITED = 1;															

	return 0;
}





bool FS_StrSymbolsValid(const u8 *str) {
	u8 s;
	u8 i;
	u8 len;

	len = strlen((char *)str);
	for (i = 0; i < len; i++) {
		s = str[i];
		if ( s <= ' ' ||
			 s == ':' ||
			 s == ';' ||
			 s == '.' ||
			 s == '*' ||
			 s == '?' ||
			 s == '/' ||
			 s == '|' ||
			 s == '\\' ) {
			return 0;
		}
	}

	return 1;
}






bool FS_GetNameAndType(const u8 *file_name, u8 *name, u8 *type) {
	u8 i, k;
	u8 s;

	
	for (i = 0, k = 0; k <= 14; i++, k++) {
		s = file_name[i];
		if (s && s != '.') {
			name[k] = s;
		}
		else {
			name[k] = 0;
			break;
		}
	}
	if (k == 0 || k > 14) {									
		name[0] = 0;
		type[0] = 0;
		return 0;														
	}

	
	if (s == '.') {
		for (i++, k = 0; k <= 3; i++, k++) {
			s = file_name[i];
			type[k] = s;
			if (!s) {
				break;
			}
		}
		if (k == 0 || k > 3) {								
			name[0] = 0;
			type[0] = 0;
			return 0;													
		}
	}
	else {
		type[0] = 0;
	}

	
	if ( ! FS_StrSymbolsValid(name) ) {										
		name[0] = 0;
		type[0] = 0;
		return 0;														
	}
	if ( ! FS_StrSymbolsValid(type) ) {										
		name[0] = 0;
		type[0] = 0;
		return 0;														
	}

	return 1;															
}





void FS_GetFullName(const u8 *name, const u8 *type, u8 *full_name) {
	u8 len;
	u8 i, j;
	u8 crc;

	
	i = 1;
	j = 0;
	len = strlen((char *)name);
	while (i <= len) {
		full_name[i++] = name[j++];
	}

	
	len = 14;
	while (i <= len) {
		full_name[i++] = 0;
	}

	
	len += strlen((char *)type);
	j = 0;
	while (i <= len) {
		full_name[i++] = type[j++];
	}

	
	len = 14 + 3;
	while (i <= len) {
		full_name[i++] = 0;
	}

	
	crc = CRC8(full_name + len, 0xFF, 3);
	full_name[i] = crc;

	
	crc = CRC8(full_name + len - 3, crc, 14);
	if ( crc == 0x00 || crc == 0xFF ) {
		crc = 0x01;
	}
	full_name[0] = crc;
}







tFile FS_FileUseFCS(const u8 *name, const u8 *type) {
	u8 fcs_num;																
	tFCS *p_fcs;
	u8 state;

	for (fcs_num = 0; fcs_num < 8; fcs_num++) {						
		p_fcs = pFCSArray[fcs_num];											

		state = p_fcs->State;
		if (state == FCS_STATE_CLOSED) {									
			continue;														
		}

		
		if ( ! strcmp( (char *)name, (char *)p_fcs->Name ) &&				
		     ! strcmp( (char *)type, (char *)p_fcs->Type ) ) {				
			return fcs_num;													
		};
	}

	return -1;																
}






u32 FS_FindFreeFNT(void) {
	u32 fnt_num1;															
	u32 fnt_num2;															
	u32 fnt_num;															
	u32 addr;

	fnt_num1 = 0;															
	fnt_num2 = FNTRecordMAX;												

	
	addr = 32;
	if (FLASH_ReadByte(addr) == 0xFF) {										
		return 0;															
	}
	addr += FNTRecordMAX * 32;
	if (FLASH_ReadByte(addr) != 0xFF) {										
		return 0xFFFFFFFF;													
	}

	
	while ( (fnt_num2 - fnt_num1) > 1 ) {									
		fnt_num = (fnt_num1 + fnt_num2) >> 1;
		addr = 32 + fnt_num * 32;
		if (FLASH_ReadByte(addr) == 0xFF) {
			fnt_num2 = fnt_num;
		}
		else {
			fnt_num1 = fnt_num;
		}
	}
	return fnt_num2;														
}








u32 FS_FindFileByName(const u8 *full_name) {
	u32 fnt_num;
	u32 fnt_addr;
	u32 addr;
	u8 len;
	u8 i;
	u8 b;

	len = 1 + 14 + 3;							
	fnt_addr = 32;											
	for (fnt_num = 0; fnt_num < FNTRecordsNumber; fnt_num++) {				
		addr = fnt_addr;													
		for (i=0; i<len; i++) {												
			b = FLASH_ReadByte(addr++);										
			if (b != full_name[i]) {										
				break;														
			}
		}
		if (i == len) {														
			return fnt_num;													
		}
		fnt_addr += 32;										
	}
	return 0xFFFFFFFF;														
}






u16 FS_FindFreeCluster(void) {
	u16 cat_num;
	u32 cat_addr;

	cat_addr = CAT_BASE_ADDRESS;											
	for (cat_num = 0; cat_num < CATRecordsNumber; cat_num++) {				
		if (FLASH_ReadByte(cat_addr) == 0xFF) {								
			return cat_num;													
		}
		cat_addr += 3;										
	}
	return 0xFFFF;															
}






u16 FS_GetFreeClustersNum(void) {
	u16 cat_num;
	u32 cat_addr;
	u16 n = 0;

	cat_addr = CAT_BASE_ADDRESS;											
	for (cat_num = 0; cat_num < CATRecordsNumber; cat_num++) {				
		if (FLASH_ReadByte(cat_addr) == 0xFF) {								
			n++;															
		}
		cat_addr += 3;										
	}
	return n;																
}





void FS_FNTWriteFullName(u32 fnt_num, const u8 *full_name) {
	u8 len;

	len = 1 + 14 + 3 + 1;
	FLASH_Write( 32 + fnt_num * 32, full_name, len );
}





void FS_FNTSetSignature1(u32 fnt_num, u8 signature) {
	FLASH_WriteByte( 32 + fnt_num * 32, signature );
}





void FS_ClusterSetFlag(u16 clust_num, u8 flag) {
	FLASH_WriteByte( CAT_BASE_ADDRESS + clust_num * 3, flag );
}





void FS_SetNextCluster(u16 clust_num_curr, u16 clust_num_next) {
	FLASH_Write( CAT_BASE_ADDRESS + clust_num_curr * 3 + 1, (u8 *)&clust_num_next, 2 );
}





u16 FS_GetNextCluster(u16 clust_num_curr) {
	u16 clust_num_next;

	FLASH_Read( (u8 *)&clust_num_next, CAT_BASE_ADDRESS + clust_num_curr * 3 + 1, 2 );
	return clust_num_next;
}





void FS_FlushPageBuffer(const tFCS *p_fcs, u16 size) {
	u32 addr;

	addr = CLUSTERS_BASE_ADDRESS +											
	       p_fcs->CurrCluster * CLUSTER_SIZE +
		   p_fcs->CurrPage * 256;
 	FLASH_Write(addr, p_fcs->PageBuffer, size);								
}





s8 FS_GetFreeFCS() {
	u8 i;

	for (i=0; i<8; i++) {											
		if (pFCSArray[i]->State == FCS_STATE_CLOSED) {						
			return i;														
		}
	}
	return -1;																
}












s8 FS_Assign(const u8 *file_name,tFile * f) {
	s8 fcs_num;
	u8 name[14 + 1];
	u8 type[3 + 1];

	
	if (! FS_IS_INITED) {													
		return -2;															
	}

	if (! FS_GetNameAndType(file_name, name, type)) {						
		return -3;															
	}

	
	if (FS_FileUseFCS(name, type) > -1) {									
		return -4;															
	};

	
	fcs_num = FS_GetFreeFCS();
	if (fcs_num < 0) {														
		return -5;											
	}

	
	pFCSArray[fcs_num]->State = FCS_STATE_OPENED;							
	strcpy((char *)pFCSArray[fcs_num]->Name, (char *)name);					
	strcpy((char *)pFCSArray[fcs_num]->Type, (char *)type);					
	*f = fcs_num;
	return 0;															
}





s8 FS_Rewrite(tFile fcs_num) {
	tFCS *p_fcs;															
	u32 fnt_num;															
	u16 clust_num;
	u8 *full_name;															
	u16 k;

	
	if (fcs_num < 0 || fcs_num >= 8) {								
		return -6;															
	}

	p_fcs = pFCSArray[fcs_num];												

	
	if (p_fcs->State != FCS_STATE_OPENED) {									
		return -7;															
	}

	
	full_name = p_fcs->FNT.FullName;										
	FS_GetFullName(p_fcs->Name, p_fcs->Type, full_name);

	
	fnt_num = FS_FindFileByName(full_name);									
	if (fnt_num != 0xFFFFFFFF) {											
		return -8;															
	}

	
	fnt_num = FS_FindFreeFNT();
	if (fnt_num == 0xFFFFFFFF) {											
		return -9;															
	}

	
	clust_num = FS_FindFreeCluster();										
	if (clust_num == 0xFFFF) {												
		return -10;															
	}

	

	
	FS_FNTWriteFullName(fnt_num, full_name);								
	FS_ClusterSetFlag(clust_num, 0xFE);										

	
	
	p_fcs->FNT.Attribute = FILE_ATTR_NOATTR;								
	p_fcs->FNT.FirstCluster = clust_num;									
	p_fcs->FNT.Size = 0;													

	
	p_fcs->State = FCS_STATE_OPENED_WRITE;									
	p_fcs->FNT_num = fnt_num;												
	p_fcs->CurrCluster = clust_num;											
	p_fcs->CurrPage = 0;													
	p_fcs->PageBufPtr = 0;													
	




for (k = 0; k < 256; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}


	return 0;																
}





s8 FS_Append(tFile fcs_num) {
	tFCS *p_fcs;															
	u8 *full_name;															
	u32 fnt_num_old, fnt_num_new;											
	u32 addr;																
	u8 len;
	u32 file_size;															
	u16 clust_num;															
	u8 page_num;															
	u32 n_bytes;															
	u16 i;
	u16 k;

	
	if (fcs_num < 0 || fcs_num >= 8) {								
		return -6;															
	}

	p_fcs = pFCSArray[fcs_num];												

	

	
	if (p_fcs->State != FCS_STATE_OPENED) {									
		return -7;															
	}

	
	full_name = p_fcs->FNT.FullName;										
	FS_GetFullName(p_fcs->Name, p_fcs->Type, full_name);

	
	fnt_num_old = FS_FindFileByName(full_name);								
	if (fnt_num_old == 0xFFFFFFFF) {										
		return -11;															
	}

	
	fnt_num_new = FS_FindFreeFNT();
	if (fnt_num_new == 0xFFFFFFFF) {										
		return -9;															
	}

	

	

	

	
	addr = 32 + fnt_num_old * 32;				
	len = 1 + 14 + 3 + 1;						
	addr += len;															
	FLASH_Read(full_name + len, addr, 32 - len);				

	
	if (p_fcs->FNT.Attribute == FILE_ATTR_READONLY) {						
		return -12;															
	}

	file_size = p_fcs->FNT.Size;											
	page_num = ( (file_size / 256) % 64 );				
	n_bytes = file_size % 256;										

	
	i = (file_size / CLUSTER_SIZE);											
	clust_num = p_fcs->FNT.FirstCluster;									
	while (i--) {															
		clust_num = FS_GetNextCluster(clust_num);
	}

	
	FS_FNTSetSignature1(fnt_num_old, 0x00);									
	FS_FNTWriteFullName(fnt_num_new, full_name);							

	
	p_fcs->State = FCS_STATE_OPENED_WRITE;									
	p_fcs->FNT_num = fnt_num_new;											
	p_fcs->CurrCluster = clust_num;											
	p_fcs->CurrPage = page_num;												
	p_fcs->PageBufPtr = n_bytes;											

	
	if (n_bytes) {															
		addr = CLUSTERS_BASE_ADDRESS +										
		       clust_num * CLUSTER_SIZE +
		       page_num * 256;
		FLASH_Read(p_fcs->PageBuffer, addr, n_bytes);						
	}




for (k = n_bytes; k < 256; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}


	return 0;																
}





s8 FS_Reset(tFile fcs_num) {
	tFCS *p_fcs;															
	u8 *full_name;															
	u32 fnt_num;															
	u8 len;
	u32 addr;																
	u32 size;
	u16 k;

	
	if (fcs_num < 0 || fcs_num >= 8) {								
		return -6;															
	}

	p_fcs = pFCSArray[fcs_num];												

	

	
	if (p_fcs->State != FCS_STATE_OPENED) {									
		return -7;															
	}

	
	full_name = p_fcs->FNT.FullName;										
	FS_GetFullName(p_fcs->Name, p_fcs->Type, full_name);

	
	fnt_num = FS_FindFileByName(full_name);									
	if (fnt_num == 0xFFFFFFFF) {											
		return -11;															
	}

	

	
	

	
	addr = 32 + fnt_num * 32;					

	len = 1 + 14 + 3 + 1;						
	addr += len;															
	FLASH_Read(full_name + len, addr, 32 - len);				

	
	p_fcs->State = FCS_STATE_OPENED_READ;									
	p_fcs->FNT_num = fnt_num;												
	p_fcs->CurrCluster = p_fcs->FNT.FirstCluster;							
	p_fcs->CurrPage = 0;													
	p_fcs->PageBufPtr = 0;													

	size = p_fcs->FNT.Size;													
	p_fcs->RemainSize = size;												

	if (size > 256) {													
		size = 256;
	}

	
	if (size) {																
		addr = CLUSTERS_BASE_ADDRESS +										
		       p_fcs->CurrCluster * CLUSTER_SIZE;							
		FLASH_Read(p_fcs->PageBuffer, addr, size);							
	}




for (k = size; k < 256; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}


	p_fcs->MinFilePosition = 0;												
	if (size == 256) {												
		p_fcs->MaxFilePosition = 256-1;
	}
	else {
		
		p_fcs->MaxFilePosition = size;
	}

	return 0;																
}





s8 FS_WriteByte(tFile fcs_num, u8 data) {
	tFCS *p_fcs;															
	u16 page_buf_ptr;														
	u8 curr_page;															
	u16 clust_num_next;
	s8 result;																
	u16 k;

	
	if (fcs_num < 0 || fcs_num >= 8) {								
		return -6;															
	}

	p_fcs = pFCSArray[fcs_num];												

	

	
	if (p_fcs->State != FCS_STATE_OPENED_WRITE) {							
		return -13;															
	}

	

	p_fcs->FNT.Size++;														
	page_buf_ptr = p_fcs->PageBufPtr;										
	p_fcs->PageBuffer[page_buf_ptr++] = data;								

	result = 0;																
	if (page_buf_ptr == 256) {										
		page_buf_ptr = 0;													
		FS_FlushPageBuffer(p_fcs, 256);								




for (k = 0; k < 256; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}

		curr_page = p_fcs->CurrPage + 1;									
		if (curr_page == 64) {								
			curr_page = 0;													

			
			clust_num_next = FS_FindFreeCluster();							
			if (clust_num_next == 0xFFFF) {									
				result = -10;												
			}
			else {
				FS_SetNextCluster(p_fcs->CurrCluster, clust_num_next);		
				FS_ClusterSetFlag(clust_num_next, 0xFE);					
				p_fcs->CurrCluster = clust_num_next;						
			}
		}
		p_fcs->CurrPage = curr_page;										
	}
	p_fcs->PageBufPtr = page_buf_ptr;										


	return result;															
}





s8 FS_ReadByte(tFile fcs_num, u8 *data) {
	tFCS *p_fcs;															
	u16 page_buf_ptr;														
	u8 *page_buffer;
	u16 page_size;															
	u32 remain_size;														
	u8  curr_page;															
	u16 clust_num;
	u32 addr;
	u16 k;

	
	if (fcs_num < 0 || fcs_num >= 8) {								
		return -6;															
	}

	p_fcs = pFCSArray[fcs_num];												

	
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							
		return -14;															
	}

	remain_size = p_fcs->RemainSize;

	
	if (! remain_size) {													
		return -15;															
	}

	

	p_fcs->RemainSize = --remain_size;										

	page_buf_ptr = p_fcs->PageBufPtr;										
	page_buffer = p_fcs->PageBuffer;										

	
	
	*data = page_buffer[page_buf_ptr++];

	if (page_buf_ptr == 256) {										
		page_buf_ptr = 0;													
		clust_num = p_fcs->CurrCluster;										
		curr_page = p_fcs->CurrPage + 1;									
		if (curr_page == 64) {								
			curr_page = 0;													
			clust_num = FS_GetNextCluster(clust_num);						
			p_fcs->CurrCluster = clust_num;									
		}
		p_fcs->CurrPage = curr_page;										

		
		if (remain_size > 256) {
			page_size = 256;
		}
		else {
			page_size = remain_size;
		}

		
		if (page_size) {
			addr = CLUSTERS_BASE_ADDRESS +									
			       clust_num * CLUSTER_SIZE +
				   curr_page * 256;
			FLASH_Read(page_buffer, addr, page_size);						
		}




for (k = page_size; k < 256; k++) {
	page_buffer[k] = 0xFF;
}


		
		p_fcs->MinFilePosition += 256;								
		if (page_size == 256) {										
			p_fcs->MaxFilePosition += 256;
		}
		else {
			
			p_fcs->MaxFilePosition += page_size + 1;
		}
	}
	p_fcs->PageBufPtr = page_buf_ptr;										

	return 0;																
}






s32 FS_Write(tFile fcs_num, const u8 *buffer, u32 size) {
	tFCS *p_fcs;															
	u8 *page_buffer;
	u16 page_buf_ptr;														
	u16 remain_page;														
	u16 first_size;															
	u16 last_size;															
	u32 full_page_count;													
	u8  curr_page;															
	u16 clust_num_next;															

	u16 k;

	
	if (fcs_num < 0 || fcs_num >= 8) {								
		return -9;															
	}

	p_fcs = pFCSArray[fcs_num];												

	

	
	if (p_fcs->State != FCS_STATE_OPENED_WRITE) {							
		return -1;															
	}

	

	page_buffer = p_fcs->PageBuffer;										
	page_buf_ptr = p_fcs->PageBufPtr;										

	
	remain_page = 256 - page_buf_ptr;									
	if (size < remain_page) {
		first_size = size;													
		full_page_count = 0;												
	}
	if (size == remain_page) {
		first_size = remain_page;											
		full_page_count = 1;												
		last_size = 0;														
	}
	if (size > remain_page) {
		first_size = remain_page;											
		full_page_count = (size - remain_page) / 256 + 1;				
		last_size = (size - remain_page) % 256;						
	}

	
	if (first_size) {														
		memcpy(page_buffer + page_buf_ptr, buffer, first_size);				
	}
	else {
		return 0;															
	}

	
	if (! full_page_count) {												
		p_fcs->PageBufPtr += first_size;									
		return size;														
	}
	

	
	FS_FlushPageBuffer(p_fcs, 256);									
	full_page_count--;



	if (last_size) {
	}




		if (page_buf_ptr == 256) {										
			page_buf_ptr = 0;													
			FS_FlushPageBuffer(p_fcs, 256);								
	
	
	
	
	for (k = 0; k < 256; k++) {
		p_fcs->PageBuffer[k] = 0xFF;
	}
	
			curr_page = p_fcs->CurrPage + 1;									
			if (curr_page == 64) {								
				curr_page = 0;													
	
				
				clust_num_next = FS_FindFreeCluster();							
				if (clust_num_next == 0xFFFF) {									

				}
				else {
					FS_SetNextCluster(p_fcs->CurrCluster, clust_num_next);		
					FS_ClusterSetFlag(clust_num_next, 0xFE);					
					p_fcs->CurrCluster = clust_num_next;						
				}
			}
			p_fcs->CurrPage = curr_page;										
		}
		p_fcs->PageBufPtr = page_buf_ptr;										








	return 0; 
}






s32 FS_Read(tFile fcs_num, u8 *buffer, u32 size) {
	tFCS *p_fcs;															
	u8 *page_buffer;
	u16 page_buf_ptr;														
	u16 first_size;															
	u16 last_size;															
	u32 full_page_count;													
	u32 remain_size;														
	u8  curr_page;															
	u16 clust_num;
	u32 addr;

	
	if (fcs_num < 0 || fcs_num >= 8) {								
		return -9;															
	}

	p_fcs = pFCSArray[fcs_num];												

	
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							
		return -1;															
	}

	

	remain_size = p_fcs->RemainSize;										

	
	if (! remain_size) {													
		return 0;															
	}

	if (! size) {															
		return 0;															
	}

	
	
	if (size > remain_size) {
		size = remain_size;
	}

	page_buffer = p_fcs->PageBuffer;										
	page_buf_ptr = p_fcs->PageBufPtr;										

	
	first_size = 256 - page_buf_ptr;									
	if (first_size >= size) {
		first_size = size;													
		full_page_count = 0;												
		last_size = 0;														
	}
	else {
		full_page_count = (size - first_size) / 256;					
		last_size = (size - first_size) % 256;						
	}

	
	
	memcpy(buffer, page_buffer + page_buf_ptr, first_size);					
	page_buf_ptr += first_size;												
	remain_size -= first_size;												

	clust_num = p_fcs->CurrCluster;											
	curr_page = p_fcs->CurrPage;											

	
	if (full_page_count) {
		buffer += first_size;												
	}
	while (full_page_count--) {
		
		curr_page++;														
		if (curr_page == 64) {								
			curr_page = 0;													
			clust_num = FS_GetNextCluster(clust_num);						

		}



		
		addr = CLUSTERS_BASE_ADDRESS +										
		       clust_num * CLUSTER_SIZE +
			   curr_page * 256;
		FLASH_Read(buffer, addr, 256);								

		remain_size -= 256;											
		buffer += 256;												
	}

	
	if (last_size) {
		clust_num = p_fcs->CurrCluster;										
		curr_page = p_fcs->CurrPage;										
	}








	p_fcs->CurrCluster = clust_num;											
	p_fcs->CurrPage = curr_page;											




	
	p_fcs->MinFilePosition += 256;									
	p_fcs->MaxFilePosition += 256;									


	return 0; 
}






s32 FS_WriteLn(tFile fcs_num, const u8 *str) {

	
	if (fcs_num < 0 || fcs_num >= 8) {								
		return -9;															
	}

	return 0; 
}





s8 FS_ReadLn(tFile fcs_num, u8 *str, u32 max_size) {
	tFCS *p_fcs;															
	u8 *page_buffer;
	u16 page_buf_ptr;														
	u16 page_size;															
	u32 remain_size;														
	u8  curr_page;															
	u16 clust_num;
	u32 addr;
	u8 s;																	
	u32 i;																	
	u16 k;
	s8 result;

	
	if (fcs_num < 0 || fcs_num >= 8) {								
		return -9;															
	}

	p_fcs = pFCSArray[fcs_num];												

	
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							
		return -1;															
	}

	

	remain_size = p_fcs->RemainSize;										

	
	if (! remain_size) {													
		str[0] = 0;															
		return -2;															
	}

	page_buffer = p_fcs->PageBuffer;										
	page_buf_ptr = p_fcs->PageBufPtr;										

	page_size = 256 - page_buf_ptr;									
	if (page_size > remain_size) {
		page_size = remain_size;
	}

	
	i = 0;																	
	do {
		
		while (page_size) {
			s = page_buffer[page_buf_ptr++];								
			remain_size--;													
			if (s == 10) {													
				page_size--;												
				continue;
			}
			if (s == 13) {													
				str[i] = 0;													
				result = 0;													
				break;														
			}
			if (s == 0) {													
				str[i] = 0;													
				result = -3;												
				break;														
			}
			
			if (i < max_size) {
				str[i++] = s;												
			}
			else {
				str[i] = 0;													
				
				page_buf_ptr--;												
				remain_size++;												
				result = -4;												
				break;														
			}
			
			page_size--;													
		}
		
		if (page_size) {													
			p_fcs->RemainSize = remain_size;								
			p_fcs->PageBufPtr = page_buf_ptr;								
			return result;													
		}
		

		
		if (! remain_size) {												
			str[i] = 0;														
			p_fcs->RemainSize = 0;											
			p_fcs->PageBufPtr = page_buf_ptr;								
			return 0;														
		}

		
		clust_num = p_fcs->CurrCluster;										
		curr_page = p_fcs->CurrPage + 1;									
		if (curr_page == 64) {								
			curr_page = 0;													
			clust_num = FS_GetNextCluster(clust_num);						
			p_fcs->CurrCluster = clust_num;									
		}
		p_fcs->CurrPage = curr_page;										
		page_buf_ptr = 0;													

		
		if (remain_size < 256) {
			page_size = remain_size;
		}
		else {
			page_size = 256;
		}

		
		addr = CLUSTERS_BASE_ADDRESS +										
		       clust_num * CLUSTER_SIZE +
			   curr_page * 256;
		FLASH_Read(page_buffer, addr, page_size);							




for (k = page_size; k < 256; k++) {
	page_buffer[k] = 0xFF;
}


		
		p_fcs->MinFilePosition += 256;								
		p_fcs->MaxFilePosition += page_size;								

	} while (1);
	
}






s8 FS_ReadPrevLn(tFile fcs_num, u8 *str, u32 max_size) {

	
	if (fcs_num < 0 || fcs_num >= 8) {								
		return -9;															
	}

	return 0; 
}





s32 FS_RemainSize(tFile fcs_num) {
	tFCS *p_fcs;															

	
	if (fcs_num < 0 || fcs_num >= 8) {								
		return -9;															
	}

	p_fcs = pFCSArray[fcs_num];												

	
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							
		return -1;															
	}

	return p_fcs->RemainSize;												
}






s8 FS_Seek(tFile fcs_num, u32 position) {
	tFCS *p_fcs;															
	u16 clusters_num;
	u16 clust_num;
	u8  page_num;
	u8  old_page_ptr, new_page_ptr;
	u32 size;
	u32 addr;
	u16 i;
	u16 k;

	
	if (fcs_num < 0 || fcs_num >= 8) {								
		return -6;															
	}

	p_fcs = pFCSArray[fcs_num];												

	
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							
		return -14;															
	}

	
	if (position > p_fcs->FNT.Size) {										
		return -16;															
	}

	

	page_num = position % CLUSTER_SIZE / 256;							
	new_page_ptr = position % 256;									

	
	if (position >= p_fcs->MinFilePosition && position <= p_fcs->MaxFilePosition) {
		
		old_page_ptr = p_fcs->PageBufPtr;
		p_fcs->PageBufPtr = new_page_ptr;
		p_fcs->RemainSize -= new_page_ptr - old_page_ptr;
		return 0;														
	}

	

	
	clusters_num = position / CLUSTER_SIZE;									
	clust_num = p_fcs->FNT.FirstCluster;									
	for (i = 0; i < clusters_num; i++) {									
		clust_num = FS_GetNextCluster(clust_num);
	}

	
	p_fcs->CurrCluster = clust_num;											
	p_fcs->CurrPage = page_num;												
	p_fcs->PageBufPtr = new_page_ptr;										

	size = p_fcs->FNT.Size - position;										
	p_fcs->RemainSize = size;

	
	size += new_page_ptr;													
	if (size >= 256) {												
		size = 256;													
	}

	
	addr = CLUSTERS_BASE_ADDRESS +											
	       clust_num * CLUSTER_SIZE +
		   page_num * 256;
	FLASH_Read(p_fcs->PageBuffer, addr, size);								




for (k = size; k < 256; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}


	p_fcs->MinFilePosition = (position / 256) * 256;			
	p_fcs->MaxFilePosition = p_fcs->MinFilePosition + size-1;				

	return 0;																
}








s8 FS_RSeek(tFile fcs_num, s32 disp) {
	tFCS *p_fcs;															
	s32 position;
	u16 clusters_num;
	u16 clust_num;
	u8  page_num;
	u8  old_page_ptr, new_page_ptr;
	u32 size;
	u32 addr;
	u16 i;
	u16 k;

	
	if (fcs_num < 0 || fcs_num >= 8) {								
		return -6;															
	}

	p_fcs = pFCSArray[fcs_num];												

	
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							
		return -14;															
	}

	size = p_fcs->FNT.Size;													

	position = size - p_fcs->RemainSize + disp;								
	

	
	if (position < 0) {
		position = 0;
	}
	if (position > size) {
		position = size;
	}

	

	page_num = position % CLUSTER_SIZE / 256;							
	new_page_ptr = position % 256;									

	
	if (position >= p_fcs->MinFilePosition && position <= p_fcs->MaxFilePosition) {
		
		old_page_ptr = p_fcs->PageBufPtr;
		p_fcs->PageBufPtr = new_page_ptr;
		p_fcs->RemainSize -= new_page_ptr - old_page_ptr;
		return 0;														
	}

	

	
	clusters_num = position / CLUSTER_SIZE;									
	clust_num = p_fcs->FNT.FirstCluster;									
	for (i = 0; i < clusters_num; i++) {									
		clust_num = FS_GetNextCluster(clust_num);
	}

	
	p_fcs->CurrCluster = clust_num;											
	p_fcs->CurrPage = page_num;												
	p_fcs->PageBufPtr = new_page_ptr;										

	size = p_fcs->FNT.Size - position;										
	p_fcs->RemainSize = size;

	
	size += new_page_ptr;													
	if (size >= 256) {												
		size = 256;													
	}

	
	addr = CLUSTERS_BASE_ADDRESS +											
	       clust_num * CLUSTER_SIZE +
		   page_num * 256;
	FLASH_Read(p_fcs->PageBuffer, addr, size);								




for (k = size; k < 256; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}


	p_fcs->MinFilePosition = (position / 256) * 256;			
	p_fcs->MaxFilePosition = p_fcs->MinFilePosition + size-1;				

	return 0;																
}





s8 FS_Close(tFile *fcs_num) {
	tFCS *p_fcs;															
	u8 state;
	u32 flash_addr;
	u8 *addr;
	u8 size;

	
	if (*fcs_num < 0 || *fcs_num >= 8) {							
		return -6;															
	}

	p_fcs = pFCSArray[*fcs_num];											

	

	state = p_fcs->State;													

	
	if (state == FCS_STATE_CLOSED) {										
		return -17;															
	}

	
	if (state == FCS_STATE_OPENED || state == FCS_STATE_OPENED_READ) {
		p_fcs->State = FCS_STATE_CLOSED;									
		*fcs_num = -1;														
		return 0;															
	}

	
	if (state == FCS_STATE_OPENED_WRITE) {
		if (p_fcs->PageBufPtr) {											
			FS_FlushPageBuffer(p_fcs, p_fcs->PageBufPtr);					
		}
		
		flash_addr = 32 +										
		       p_fcs->FNT_num * 32 +							
			   1 + 14 + 3 + 1;
		addr = p_fcs->FNT.FullName +										
			   1 + 14 + 3 + 1;					
		size = sizeof(tFNT) -
		       1 - 14 - 3 - 1;
		FLASH_Write(flash_addr, addr, size);								

		p_fcs->State = FCS_STATE_CLOSED;									
		*fcs_num = -1;														
		return 0;															
	}
	else {
		return -18;															
	}
}





s8 FS_Delete(const u8 *file_name) {
	u8 name[14 + 1];
	u8 type[3 + 1];
	u8 full_name[1 + 14 + 3 + 1];
	u32 fnt_num;
	u32 fnt_addr;
	u32 addr;
	u16 clust_num;

	
	if (! FS_IS_INITED) {													
		return -2;															
	}

	if (! FS_GetNameAndType(file_name, name, type)) {						
		return -3;															
	}

	
	if (FS_FileUseFCS(name, type) > -1) {									
		return -4;															
	};

	
	FS_GetFullName(name, type, full_name);

	
	fnt_num = FS_FindFileByName(full_name);									
	if (fnt_num == 0xFFFFFFFF) {											
		return -11;															
	}

	

	fnt_addr = 32 + fnt_num * 32;				

	addr = fnt_addr + 1 + 14 + 3 + 1 + 1;		
	FLASH_Read((u8 *)&clust_num, addr, 2);									

	
	
	while (clust_num != 0xFFFF) {
		FS_ClusterSetFlag(clust_num, 0x00);									
		clust_num = FS_GetNextCluster(clust_num);							
	}

	
	FLASH_WriteByte(fnt_addr, 0x00);										

	return 0;																
}






s8 FS_GetFileInfo(u32 * fnt_num, u8 *name, u8 *type, u8 *attr, u32 *size, tFile *f) {
	tFCS *p_fcs;															
	u32 addr;
	__packed union {
		u8 array[32];											
		tFNT strc;															
	} fnt;
	u8 b;
	u8 i,k;

	
	addr = 32 + *fnt_num * 32;					
	while (*fnt_num < FNTRecordsNumber) {
		b = FLASH_ReadByte(addr);											
		if (b == 0xFF) {													
			name[0] = 0;													
			type[0] = 0;													
			*attr = 0xFF;
			*size = 0;
			*f = -1;
			*fnt_num = 0xFFFFFFFF;
			return -19;									
		}
		if (b > 0x00) {														
			break;															
		}
		addr += 32;											
		(*fnt_num)++;															
	}

	if ((*fnt_num) >= FNTRecordsNumber) {										
			name[0] = 0;													
			type[0] = 0;
			*attr = 0xFF;
			*size = 0;
			*f = -1;
			(*fnt_num) = 0xFFFFFFFF;
			return -19;									
	}

	
	
	
	FLASH_Read(fnt.array, addr, sizeof(tFNT));								

	
	for (i = 0, k = 1; i < 14; i++, k++) {
		b = fnt.strc.FullName[k];
		name[i] = b;
		if (! b) {
			break;
		}
	}
	if (i == 14) {
		name[14] = 0;
	}

	
	for (i = 0, k = 1 + 14; i < 3; i++, k++) {
		b = fnt.strc.FullName[k];
		type[i] = b;
		if (! b) {
			break;
		}
	}
	if (i == 3) {
		type[3] = 0;
	}

	*f = FS_FileUseFCS(name, type);											

	
	if (*f > -1) {															
		
		p_fcs = pFCSArray[*f];												
		*attr = p_fcs->FNT.Attribute;
		*size = p_fcs->FNT.Size;
	}
	
	else {
		
		*attr = fnt.strc.Attribute;
		*size = fnt.strc.Size;
	}

	return 0;															
}





s8 FS_Eof(tFile fcs_num) {
	tFCS *p_fcs;															

	
	if (fcs_num < 0 || fcs_num >= 8) {								
		return -6;															
	}

	p_fcs = pFCSArray[fcs_num];												

	
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							
		return -14;															
	}

	
	if (p_fcs->RemainSize) {
		return -20;
	}
	else {
		return -21;
	}
}





s8 FS_Pos(tFile fcs_num,s32 * pos) {
	tFCS *p_fcs;															

	
	if (fcs_num < 0 || fcs_num >= 8) {								
		return -6;															
	}

	p_fcs = pFCSArray[fcs_num];												

	
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							
		return -14;															
	}

	
	*pos = (p_fcs->FNT.Size - p_fcs->RemainSize);
	return 0;
}


















u8 FS_GetFCSState(u8 fcs_num) {

	return pFCSArray[fcs_num]->State;
}



void FS_FCS_Show( u8 fcs_num, void page_buf_view(u8 *buffer, u32 addr) ) {
	tFCS *p_fcs;															
	u8 *name_buf;
	char ch;
	u8 i;

	p_fcs = pFCSArray[fcs_num];												

	Msg(" - FCS %d:\r\n", fcs_num);
	Msg("   -------------------------\r\n", fcs_num);
	SMsg();
	Msg("   State: %d", p_fcs->State);
	SMsg();
	switch (p_fcs->State) {
		case FCS_STATE_CLOSED: {
			Msg(" (FCS_STATE_CLOSED)\r\n");
			SMsg();
			break;
		}
		case FCS_STATE_OPENED: {
			Msg(" (FCS_STATE_OPENED)\r\n");
			SMsg();
			break;
		}
		case FCS_STATE_OPENED_READ: {
			Msg(" (FCS_STATE_OPENED_READ)\r\n");
			SMsg();
			break;
		}
		case FCS_STATE_OPENED_WRITE: {
			Msg(" (FCS_STATE_OPENED_WRITE)\r\n");
			SMsg();
			break;
		}
	}
	Msg("   Name: \"%s\"\r\n", p_fcs->Name);
	SMsg();
	Msg("   Type: \"%s\"\r\n", p_fcs->Type);
	SMsg();
	Msg("   FNT_num: %d\r\n", p_fcs->FNT_num);
	SMsg();
	Msg("   CurrCluster: %d\r\n", p_fcs->CurrCluster);
	Msg("   CurrPage: %d\r\n", p_fcs->CurrPage);
	SMsg();
	Msg("   PageBufPtr: %d\r\n", p_fcs->PageBufPtr);
	Msg("   RemainSize: %d\r\n", p_fcs->RemainSize);
	SMsg();
	Msg("   MinFilePosition: %d\r\n", p_fcs->MinFilePosition);
	SMsg();
	Msg("   MaxFilePosition: %d\r\n", p_fcs->MaxFilePosition);
	SMsg();
	Msg("   PAGE_BUFFER:\r\n");
	page_buf_view(p_fcs->PageBuffer, 0);
	SMsg();
	Msg("   FNT:\r\n");
	Msg("   FNT.FullName: ");
	name_buf = p_fcs->FNT.FullName;
	for (i=0; i < 1 + 14 + 3 + 1; i++) {
		Msg(" %02X", name_buf[i]);
	}
	SMsg();
	Msg(" | ");
	for (i=0; i < 1 + 14 + 3 + 1; i++) {
		ch = name_buf[i];
		if (ch < 32) ch = '.';
		Msg("%c", ch);
	}
	Msg("\r\n");
	SMsg();
	Msg("   FNT.Attribute: 0x%02X\r\n", p_fcs->FNT.Attribute);
	SMsg();
	Msg("   FNT.FirstCluster: %d (0x%04X)\r\n", p_fcs->FNT.FirstCluster, p_fcs->FNT.FirstCluster);
	SMsg();
	Msg("   FNT.Size: %d\r\n", p_fcs->FNT.Size);
	Msg("   -------------------------\r\n", fcs_num);
	SMsg();
}



void FS_Params_Show(void) {
	Msg("MAX_FILES = %d\r\n", 8);
	SMsg();
	Msg("BANKS_NUM = %d\r\n", FLASH_BANKS_NUM);
	SMsg();
	Msg("SECTORS_PER_BANK = %d\r\n", 64);
	SMsg();
	Msg("PAGES_PER_SECTOR = %d\r\n", 1024);
	SMsg();
	Msg("PAGE_SIZE = %d\r\n", 256);
	SMsg();
	Msg("PAGES_PER_CLUSTER = %d\r\n", 64);
	SMsg();
	Msg("FILE_NAME_LENGTH = %d\r\n", 14);
	SMsg();
	Msg("FILE_TYPE_LENGTH = %d\r\n", 3);
	SMsg();
	Msg("FNT_RECORD_SIZE = %d\r\n", 32);
	SMsg();
	Msg("CAT_RECORD_SIZE = %d\r\n", 3);
	Msg("\r\n");
	SMsg();
	Msg("SECTORS_NUMBER = %d\r\n", SECTORS_NUMBER);
	SMsg();
	Msg("SECTOR_SIZE = %d\r\n", SECTOR_SIZE);
	SMsg();
	Msg("CLUSTERS_PER_SECTOR = %d\r\n", CLUSTERS_PER_SECTOR);
	SMsg();
	Msg("CLUSTERS_NUMBER = %d\r\n", CLUSTERS_NUMBER);
	SMsg();
	Msg("ClusterMAX = %d\r\n", ClusterMAX);
	SMsg();
	Msg("CLUSTER_SIZE = %d\r\n", CLUSTER_SIZE);
	SMsg();
	Msg("CAT_Size = %d\r\n", CAT_Size);
	SMsg();
	Msg("CATRecordsNumber = %d\r\n", CATRecordsNumber);
	SMsg();
	Msg("CATRecordMAX = %d\r\n", CATRecordMAX);
	SMsg();
	Msg("FNTRecordsNumber = %d\r\n", FNTRecordsNumber);
	SMsg();
	Msg("FNTRecordMAX = %d\r\n", FNTRecordMAX);
	Msg("\r\n");
	SMsg();
	Msg("FNT_BASE_ADDRESS = %d\r\n", 32);
	SMsg();
	Msg("CAT_BASE_ADDRESS = %d\r\n", CAT_BASE_ADDRESS);
	SMsg();
	Msg("CLUSTERS_BASE_ADDRESS = %d\r\n", CLUSTERS_BASE_ADDRESS);
	SMsg();
}















