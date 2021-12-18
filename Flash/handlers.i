#line 1 "Main\\Handlers.c"
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



 

#line 2 "Main\\Handlers.c"
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



 

#line 3 "Main\\Handlers.c"
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"




 





 












 






   









 






#line 61 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"

#line 75 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"







   




 















 
#line 112 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"











 





extern __attribute__((__pcs__("aapcs"))) unsigned __ARM_dcmp4(double  , double  );
extern __attribute__((__pcs__("aapcs"))) unsigned __ARM_fcmp4(float  , float  );
    




 

extern __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_fpclassifyf(float  );
extern __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_fpclassify(double  );
     
     

__inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isfinitef(float __x)
{
    return (((*(unsigned *)&(__x)) >> 23) & 0xff) != 0xff;
}
__inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isfinite(double __x)
{
    return (((*(1 + (unsigned *)&(__x))) >> 20) & 0x7ff) != 0x7ff;
}
     
     

__inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isinff(float __x)
{
    return ((*(unsigned *)&(__x)) << 1) == 0xff000000;
}
__inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isinf(double __x)
{
    return (((*(1 + (unsigned *)&(__x))) << 1) == 0xffe00000) && ((*(unsigned *)&(__x)) == 0);
}
     
     

__inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_islessgreaterf(float __x, float __y)
{
    unsigned __f = __ARM_fcmp4(__x, __y) >> 28;
    return (__f == 8) || (__f == 2);  
}
__inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_islessgreater(double __x, double __y)
{
    unsigned __f = __ARM_dcmp4(__x, __y) >> 28;
    return (__f == 8) || (__f == 2);  
}
    


 

__inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isnanf(float __x)
{
    return (0x7f800000 - ((*(unsigned *)&(__x)) & 0x7fffffff)) >> 31;
}
__inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isnan(double __x)
{
    unsigned __xf = (*(1 + (unsigned *)&(__x))) | (((*(unsigned *)&(__x)) == 0) ? 0 : 1);
    return (0x7ff00000 - (__xf & 0x7fffffff)) >> 31;
}
     
     

__inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isnormalf(float __x)
{
    unsigned __xe = ((*(unsigned *)&(__x)) >> 23) & 0xff;
    return (__xe != 0xff) && (__xe != 0);
}
__inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isnormal(double __x)
{
    unsigned __xe = ((*(1 + (unsigned *)&(__x))) >> 20) & 0x7ff;
    return (__xe != 0x7ff) && (__xe != 0);
}
     
     

__inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_signbitf(float __x)
{
    return (*(unsigned *)&(__x)) >> 31;
}
__inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_signbit(double __x)
{
    return (*(1 + (unsigned *)&(__x))) >> 31;
}
     
     








#line 230 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"







   
  typedef float float_t;
  typedef double double_t;
#line 251 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"



extern const int math_errhandling;
#line 261 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"

extern __declspec(__nothrow) double acos(double  );
    
    
    
extern __declspec(__nothrow) double asin(double  );
    
    
    
    

extern __declspec(__nothrow) __attribute__((const)) double atan(double  );
    
    

extern __declspec(__nothrow) double atan2(double  , double  );
    
    
    
    

extern __declspec(__nothrow) double cos(double  );
    
    
    
    
extern __declspec(__nothrow) double sin(double  );
    
    
    
    

extern void __use_accurate_range_reduction(void);
    
    

extern __declspec(__nothrow) double tan(double  );
    
    
    
    

extern __declspec(__nothrow) double cosh(double  );
    
    
    
    
extern __declspec(__nothrow) double sinh(double  );
    
    
    
    
    

extern __declspec(__nothrow) __attribute__((const)) double tanh(double  );
    
    

extern __declspec(__nothrow) double exp(double  );
    
    
    
    
    

extern __declspec(__nothrow) double frexp(double  , int *  ) __attribute__((__nonnull__(2)));
    
    
    
    
    
    

extern __declspec(__nothrow) double ldexp(double  , int  );
    
    
    
    
extern __declspec(__nothrow) double log(double  );
    
    
    
    
    
extern __declspec(__nothrow) double log10(double  );
    
    
    
extern __declspec(__nothrow) double modf(double  , double *  ) __attribute__((__nonnull__(2)));
    
    
    
    

extern __declspec(__nothrow) double pow(double  , double  );
    
    
    
    
    
    
extern __declspec(__nothrow) double sqrt(double  );
    
    
    




    __inline double _sqrt(double __x) { return sqrt(__x); }




    __inline float _sqrtf(float __x) { return (float)sqrt(__x); }

    



 

extern __declspec(__nothrow) __attribute__((const)) double ceil(double  );
    
    
extern __declspec(__nothrow) __attribute__((const)) double fabs(double  );
    
    

extern __declspec(__nothrow) __attribute__((const)) double floor(double  );
    
    

extern __declspec(__nothrow) double fmod(double  , double  );
    
    
    
    
    

    









 



extern __declspec(__nothrow) double acosh(double  );
    

 
extern __declspec(__nothrow) double asinh(double  );
    

 
extern __declspec(__nothrow) double atanh(double  );
    

 
extern __declspec(__nothrow) double cbrt(double  );
    

 
__inline __declspec(__nothrow) __attribute__((const)) double copysign(double __x, double __y)
    

 
{
    (*(1 + (unsigned *)&(__x))) = ((*(1 + (unsigned *)&(__x))) & 0x7fffffff) | ((*(1 + (unsigned *)&(__y))) & 0x80000000);
    return __x;
}
__inline __declspec(__nothrow) __attribute__((const)) float copysignf(float __x, float __y)
    

 
{
    (*(unsigned *)&(__x)) = ((*(unsigned *)&(__x)) & 0x7fffffff) | ((*(unsigned *)&(__y)) & 0x80000000);
    return __x;
}
extern __declspec(__nothrow) double erf(double  );
    

 
extern __declspec(__nothrow) double erfc(double  );
    

 
extern __declspec(__nothrow) double expm1(double  );
    

 



    

 






#line 479 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"


extern __declspec(__nothrow) double hypot(double  , double  );
    




 
extern __declspec(__nothrow) int ilogb(double  );
    

 
extern __declspec(__nothrow) int ilogbf(float  );
    

 
extern __declspec(__nothrow) int ilogbl(long double  );
    

 







    

 





    



 





    



 





    

 





    



 





    



 





    



 





    

 





    

 





    


 

extern __declspec(__nothrow) double lgamma (double  );
    


 
extern __declspec(__nothrow) double log1p(double  );
    

 
extern __declspec(__nothrow) double logb(double  );
    

 
extern __declspec(__nothrow) float logbf(float  );
    

 
extern __declspec(__nothrow) long double logbl(long double  );
    

 
extern __declspec(__nothrow) double nextafter(double  , double  );
    


 
extern __declspec(__nothrow) float nextafterf(float  , float  );
    


 
extern __declspec(__nothrow) long double nextafterl(long double  , long double  );
    


 
extern __declspec(__nothrow) double nexttoward(double  , long double  );
    


 
extern __declspec(__nothrow) float nexttowardf(float  , long double  );
    


 
extern __declspec(__nothrow) long double nexttowardl(long double  , long double  );
    


 
extern __declspec(__nothrow) double remainder(double  , double  );
    

 
extern __declspec(__nothrow) __attribute__((const)) double rint(double  );
    

 
extern __declspec(__nothrow) double scalbln(double  , long int  );
    

 
extern __declspec(__nothrow) float scalblnf(float  , long int  );
    

 
extern __declspec(__nothrow) long double scalblnl(long double  , long int  );
    

 
extern __declspec(__nothrow) double scalbn(double  , int  );
    

 
extern __declspec(__nothrow) float scalbnf(float  , int  );
    

 
extern __declspec(__nothrow) long double scalbnl(long double  , int  );
    

 




    

 



 
extern __declspec(__nothrow) __attribute__((const)) float _fabsf(float);  
__inline __declspec(__nothrow) __attribute__((const)) float fabsf(float __f) { return _fabsf(__f); }
extern __declspec(__nothrow) float sinf(float  );
extern __declspec(__nothrow) float cosf(float  );
extern __declspec(__nothrow) float tanf(float  );
extern __declspec(__nothrow) float acosf(float  );
extern __declspec(__nothrow) float asinf(float  );
extern __declspec(__nothrow) float atanf(float  );
extern __declspec(__nothrow) float atan2f(float  , float  );
extern __declspec(__nothrow) float sinhf(float  );
extern __declspec(__nothrow) float coshf(float  );
extern __declspec(__nothrow) float tanhf(float  );
extern __declspec(__nothrow) float expf(float  );
extern __declspec(__nothrow) float logf(float  );
extern __declspec(__nothrow) float log10f(float  );
extern __declspec(__nothrow) float powf(float  , float  );
extern __declspec(__nothrow) float sqrtf(float  );
extern __declspec(__nothrow) float ldexpf(float  , int  );
extern __declspec(__nothrow) float frexpf(float  , int *  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) __attribute__((const)) float ceilf(float  );
extern __declspec(__nothrow) __attribute__((const)) float floorf(float  );
extern __declspec(__nothrow) float fmodf(float  , float  );
extern __declspec(__nothrow) float modff(float  , float *  ) __attribute__((__nonnull__(2)));

 
 













 
__declspec(__nothrow) long double acosl(long double );
__declspec(__nothrow) long double asinl(long double );
__declspec(__nothrow) long double atanl(long double );
__declspec(__nothrow) long double atan2l(long double , long double );
__declspec(__nothrow) long double ceill(long double );
__declspec(__nothrow) long double cosl(long double );
__declspec(__nothrow) long double coshl(long double );
__declspec(__nothrow) long double expl(long double );
__declspec(__nothrow) long double fabsl(long double );
__declspec(__nothrow) long double floorl(long double );
__declspec(__nothrow) long double fmodl(long double , long double );
__declspec(__nothrow) long double frexpl(long double , int* ) __attribute__((__nonnull__(2)));
__declspec(__nothrow) long double ldexpl(long double , int );
__declspec(__nothrow) long double logl(long double );
__declspec(__nothrow) long double log10l(long double );
__declspec(__nothrow) long double modfl(long double  , long double *  ) __attribute__((__nonnull__(2)));
__declspec(__nothrow) long double powl(long double , long double );
__declspec(__nothrow) long double sinl(long double );
__declspec(__nothrow) long double sinhl(long double );
__declspec(__nothrow) long double sqrtl(long double );
__declspec(__nothrow) long double tanl(long double );
__declspec(__nothrow) long double tanhl(long double );





 
extern __declspec(__nothrow) float acoshf(float  );
__declspec(__nothrow) long double acoshl(long double );
extern __declspec(__nothrow) float asinhf(float  );
__declspec(__nothrow) long double asinhl(long double );
extern __declspec(__nothrow) float atanhf(float  );
__declspec(__nothrow) long double atanhl(long double );
__declspec(__nothrow) long double copysignl(long double , long double );
extern __declspec(__nothrow) float cbrtf(float  );
__declspec(__nothrow) long double cbrtl(long double );
extern __declspec(__nothrow) float erff(float  );
__declspec(__nothrow) long double erfl(long double );
extern __declspec(__nothrow) float erfcf(float  );
__declspec(__nothrow) long double erfcl(long double );
extern __declspec(__nothrow) float expm1f(float  );
__declspec(__nothrow) long double expm1l(long double );
extern __declspec(__nothrow) float log1pf(float  );
__declspec(__nothrow) long double log1pl(long double );
extern __declspec(__nothrow) float hypotf(float  , float  );
__declspec(__nothrow) long double hypotl(long double , long double );
extern __declspec(__nothrow) float lgammaf(float  );
__declspec(__nothrow) long double lgammal(long double );
extern __declspec(__nothrow) float remainderf(float  , float  );
__declspec(__nothrow) long double remainderl(long double , long double );
extern __declspec(__nothrow) float rintf(float  );
__declspec(__nothrow) long double rintl(long double );



#line 875 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"





#line 896 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"

#line 1087 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"











#line 1317 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"





 
#line 4 "Main\\Handlers.c"
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"
 
 
 




 
 



 






   














  


 








#line 54 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"


  



    typedef unsigned int size_t;    
#line 70 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"






    



    typedef unsigned short wchar_t;  
#line 91 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"

typedef struct div_t { int quot, rem; } div_t;
    
typedef struct ldiv_t { long int quot, rem; } ldiv_t;
    

typedef struct lldiv_t { long long quot, rem; } lldiv_t;
    


#line 112 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"
   



 

   




 
#line 131 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"
   


 
extern __declspec(__nothrow) int __aeabi_MB_CUR_MAX(void);

   




 

   




 




extern __declspec(__nothrow) double atof(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int atoi(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) long int atol(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) long long atoll(const char *  ) __attribute__((__nonnull__(1)));
   



 


extern __declspec(__nothrow) double strtod(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

















 

extern __declspec(__nothrow) float strtof(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) long double strtold(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

 

extern __declspec(__nothrow) long int strtol(const char * __restrict  ,
                        char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   



























 
extern __declspec(__nothrow) unsigned long int strtoul(const char * __restrict  ,
                                       char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   


























 

 
extern __declspec(__nothrow) long long strtoll(const char * __restrict  ,
                                  char ** __restrict  , int  )
                          __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) unsigned long long strtoull(const char * __restrict  ,
                                            char ** __restrict  , int  )
                                   __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) int rand(void);
   







 
extern __declspec(__nothrow) void srand(unsigned int  );
   






 

struct _rand_state { int __x[57]; };
extern __declspec(__nothrow) int _rand_r(struct _rand_state *);
extern __declspec(__nothrow) void _srand_r(struct _rand_state *, unsigned int);
struct _ANSI_rand_state { int __x[1]; };
extern __declspec(__nothrow) int _ANSI_rand_r(struct _ANSI_rand_state *);
extern __declspec(__nothrow) void _ANSI_srand_r(struct _ANSI_rand_state *, unsigned int);
   


 

extern __declspec(__nothrow) void *calloc(size_t  , size_t  );
   



 
extern __declspec(__nothrow) void free(void *  );
   





 
extern __declspec(__nothrow) void *malloc(size_t  );
   



 
extern __declspec(__nothrow) void *realloc(void *  , size_t  );
   













 

extern __declspec(__nothrow) int posix_memalign(void **  , size_t  , size_t  );
   









 

typedef int (*__heapprt)(void *, char const *, ...);
extern __declspec(__nothrow) void __heapstats(int (*  )(void *  ,
                                           char const *  , ...),
                        void *  ) __attribute__((__nonnull__(1)));
   










 
extern __declspec(__nothrow) int __heapvalid(int (*  )(void *  ,
                                           char const *  , ...),
                       void *  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) __declspec(__noreturn) void abort(void);
   







 

extern __declspec(__nothrow) int atexit(void (*  )(void)) __attribute__((__nonnull__(1)));
   




 
#line 436 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"


extern __declspec(__nothrow) __declspec(__noreturn) void exit(int  );
   












 

extern __declspec(__nothrow) __declspec(__noreturn) void _Exit(int  );
   







      

extern __declspec(__nothrow) char *getenv(const char *  ) __attribute__((__nonnull__(1)));
   









 

extern __declspec(__nothrow) int  system(const char *  );
   









 

extern  void *bsearch(const void *  , const void *  ,
              size_t  , size_t  ,
              int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,2,5)));
   












 
#line 524 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"


extern  void qsort(void *  , size_t  , size_t  ,
           int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,4)));
   









 

#line 553 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"

extern __declspec(__nothrow) __attribute__((const)) int abs(int  );
   



 

extern __declspec(__nothrow) __attribute__((const)) div_t div(int  , int  );
   









 
extern __declspec(__nothrow) __attribute__((const)) long int labs(long int  );
   



 




extern __declspec(__nothrow) __attribute__((const)) ldiv_t ldiv(long int  , long int  );
   











 







extern __declspec(__nothrow) __attribute__((const)) long long llabs(long long  );
   



 




extern __declspec(__nothrow) __attribute__((const)) lldiv_t lldiv(long long  , long long  );
   











 
#line 634 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"




 
typedef struct __sdiv32by16 { int quot, rem; } __sdiv32by16;
typedef struct __udiv32by16 { unsigned int quot, rem; } __udiv32by16;
    
typedef struct __sdiv64by32 { int rem, quot; } __sdiv64by32;

__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __sdiv32by16 __rt_sdiv32by16(
     int  ,
     short int  );
   

 
__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __udiv32by16 __rt_udiv32by16(
     unsigned int  ,
     unsigned short  );
   

 
__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __sdiv64by32 __rt_sdiv64by32(
     int  , unsigned int  ,
     int  );
   

 




 
extern __declspec(__nothrow) unsigned int __fp_status(unsigned int  , unsigned int  );
   







 























 
extern __declspec(__nothrow) int mblen(const char *  , size_t  );
   












 
extern __declspec(__nothrow) int mbtowc(wchar_t * __restrict  ,
                   const char * __restrict  , size_t  );
   















 
extern __declspec(__nothrow) int wctomb(char *  , wchar_t  );
   













 





 
extern __declspec(__nothrow) size_t mbstowcs(wchar_t * __restrict  ,
                      const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 
extern __declspec(__nothrow) size_t wcstombs(char * __restrict  ,
                      const wchar_t * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 

extern __declspec(__nothrow) void __use_realtime_heap(void);
extern __declspec(__nothrow) void __use_realtime_division(void);
extern __declspec(__nothrow) void __use_two_region_memory(void);
extern __declspec(__nothrow) void __use_no_heap(void);
extern __declspec(__nothrow) void __use_no_heap_region(void);

extern __declspec(__nothrow) char const *__C_library_version_string(void);
extern __declspec(__nothrow) int __C_library_version_number(void);











#line 892 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"





 
#line 5 "Main\\Handlers.c"

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










#line 7 "Main\\Handlers.c"
#line 1 ".\\UCNC\\Tools.h"








#line 12 ".\\UCNC\\Tools.h"




















u8 CRC8(u8 *ptr, u8 crc, u16 len);

float sqr(float x);
int Round(float f);
s32 abss32(s32 a);



#line 8 "Main\\Handlers.c"
#line 1 "Main\\Handlers.h"



#line 5 "Main\\Handlers.h"
#line 1 "Main\\regs.h"



#line 1 "C:\\Keil_v5\\ARM\\RV31\\INC\\RTL.h"









 




 

 



#line 28 "C:\\Keil_v5\\ARM\\RV31\\INC\\RTL.h"







 typedef unsigned int   size_t;


typedef signed char     S8;
typedef unsigned char   U8;
typedef short           S16;
typedef unsigned short  U16;
typedef int             S32;
typedef unsigned int    U32;
typedef long long       S64;
typedef unsigned long long U64;
typedef unsigned char   BIT;
typedef unsigned int    BOOL;

#line 55 "C:\\Keil_v5\\ARM\\RV31\\INC\\RTL.h"

#line 71 "C:\\Keil_v5\\ARM\\RV31\\INC\\RTL.h"



 





 
typedef U32 OS_SEM[2];

 

typedef U32 OS_MBX[];

 
typedef U32 OS_MUT[4];

 
typedef U32 OS_TID;

 
typedef void *OS_ID;

 
typedef U32 OS_RESULT;

 












 




#line 202 "C:\\Keil_v5\\ARM\\RV31\\INC\\RTL.h"



 



 
extern void      os_set_env    (void);
extern void      rt_sys_init   (void (*task)(void), U8 priority, void *stk);
extern void      rt_tsk_pass   (void);
extern OS_TID    rt_tsk_self   (void);
extern OS_RESULT rt_tsk_prio   (OS_TID task_id, U8 new_prio);
extern OS_TID    rt_tsk_create (void (*task)(void), U8 priority, void *stk, void *argv);
extern OS_RESULT rt_tsk_delete (OS_TID task_id);

#line 238 "C:\\Keil_v5\\ARM\\RV31\\INC\\RTL.h"

extern void      _os_sys_init(U32 p, void (*task)(void), U32 prio_stksz,
                                     void *stk)                        __svc_indirect(0);
extern OS_TID    _os_tsk_create (U32 p, void (*task)(void), U32 prio_stksz,
                                        void *stk, void *argv)         __svc_indirect(0);
extern OS_TID    _os_tsk_create_ex (U32 p, void (*task)(void *), U32 prio_stksz,
                                           void *stk, void *argv)      __svc_indirect(0);
extern OS_TID    _os_tsk_self (U32 p)                                  __svc_indirect(0);
extern void      _os_tsk_pass (U32 p)                                  __svc_indirect(0);
extern OS_RESULT _os_tsk_prio (U32 p, OS_TID task_id, U8 new_prio)     __svc_indirect(0);
extern OS_RESULT _os_tsk_delete (U32 p, OS_TID task_id)                __svc_indirect(0);

 
extern OS_RESULT rt_evt_wait (U16 wait_flags,  U16 timeout, BOOL and_wait);
extern void      rt_evt_set  (U16 event_flags, OS_TID task_id);
extern void      rt_evt_clr  (U16 clear_flags, OS_TID task_id);
extern U16       rt_evt_get  (void);







extern OS_RESULT _os_evt_wait(U32 p, U16 wait_flags, U16 timeout,
                                     BOOL and_wait)                    __svc_indirect(0);
extern void      _os_evt_set (U32 p, U16 event_flags, OS_TID task_id)  __svc_indirect(0);
extern void      _os_evt_clr (U32 p, U16 clear_flags, OS_TID task_id)  __svc_indirect(0);
extern U16       _os_evt_get (U32 p)                                   __svc_indirect(0);
extern void      isr_evt_set (U16 event_flags, OS_TID task_id);

 
extern void      rt_sem_init (OS_ID semaphore, U16 token_count);
extern OS_RESULT rt_sem_send (OS_ID semaphore);
extern OS_RESULT rt_sem_wait (OS_ID semaphore, U16 timeout);





extern void      _os_sem_init (U32 p, OS_ID semaphore, 
                                      U16 token_count)                 __svc_indirect(0);
extern OS_RESULT _os_sem_send (U32 p, OS_ID semaphore)                 __svc_indirect(0);
extern OS_RESULT _os_sem_wait (U32 p, OS_ID semaphore, U16 timeout)    __svc_indirect(0);
extern void      isr_sem_send (OS_ID semaphore);

 
extern void      rt_mbx_init  (OS_ID mailbox, U16 mbx_size);
extern OS_RESULT rt_mbx_send  (OS_ID mailbox, void *p_msg,    U16 timeout);
extern OS_RESULT rt_mbx_wait  (OS_ID mailbox, void **message, U16 timeout);
extern OS_RESULT rt_mbx_check (OS_ID mailbox);







extern void      _os_mbx_init (U32 p, OS_ID mailbox, U16 mbx_size)     __svc_indirect(0);
extern OS_RESULT _os_mbx_send (U32 p, OS_ID mailbox, void *message_ptr,
                                      U16 timeout)                     __svc_indirect(0);
extern OS_RESULT _os_mbx_wait (U32 p, OS_ID mailbox, void  **message,
                                      U16 timeout)                     __svc_indirect(0);
extern OS_RESULT _os_mbx_check (U32 p, OS_ID mailbox)                  __svc_indirect(0);
extern void      isr_mbx_send (OS_ID mailbox, void *message_ptr);
extern OS_RESULT isr_mbx_receive (OS_ID mailbox, void **message);

 
extern void      rt_mut_init    (OS_ID mutex);
extern OS_RESULT rt_mut_release (OS_ID mutex);
extern OS_RESULT rt_mut_wait    (OS_ID mutex, U16 timeout);





extern void      _os_mut_init (U32 p, OS_ID mutex)                     __svc_indirect(0);
extern OS_RESULT _os_mut_release (U32 p, OS_ID mutex)                  __svc_indirect(0);
extern OS_RESULT _os_mut_wait (U32 p, OS_ID mutex, U16 timeout)        __svc_indirect(0);

 
extern U32       rt_time_get (void);
extern void      rt_dly_wait (U16 delay_time);
extern void      rt_itv_set  (U16 interval_time);
extern void      rt_itv_wait (void);






extern U32       _os_time_get (U32 p)                                  __svc_indirect(0);
extern void      _os_dly_wait (U32 p, U16 delay_time)                  __svc_indirect(0);
extern void      _os_itv_set (U32 p, U16 interval_time)                __svc_indirect(0);
extern void      _os_itv_wait (U32 p)                                  __svc_indirect(0);

 
extern OS_ID     rt_tmr_create (U16 tcnt, U16 info);
extern OS_ID     rt_tmr_kill   (OS_ID timer);




extern OS_ID     _os_tmr_create (U32 p, U16 tcnt, U16 info)            __svc_indirect(0);
extern OS_ID     _os_tmr_kill (U32 p, OS_ID timer)                     __svc_indirect(0);

 
extern U32       rt_suspend    (void);
extern void      rt_resume     (U32 sleep_time);
extern void      rt_tsk_lock   (void);
extern void      rt_tsk_unlock (void);






extern U32       _os_suspend (U32 p)                                   __svc_indirect(0);
extern void      _os_resume (U32 p, U32 sleep_time)                    __svc_indirect(0);
extern void      _os_tsk_lock (U32 p)                                  __svc_indirect(0);
extern void      _os_tsk_unlock (U32 p)                                __svc_indirect(0);

 
extern int       _init_box (void *box_mem, U32 box_size, U32 blk_size);
extern void     *_alloc_box (void *box_mem);
extern void     *_calloc_box (void *box_mem);
extern int       _free_box (void *box_mem, void *box);








 




 

 
typedef enum _FS_TYPE {
  FS_TYPE_NONE = 0,                      
  FS_TYPE_UNKNOWN,                       
  FS_TYPE_FAT12,                         
  FS_TYPE_FAT16,                         
  FS_TYPE_FAT32,                         
  FS_TYPE_EFS                            
} FS_TYPE;

typedef struct {                         
  U8  hr;                                
  U8  min;                               
  U8  sec;                               
  U8  day;                               
  U8  mon;                               
  U16 year;                              
} RL_TIME;

typedef struct {                         
  S8  name[256];                         
  U32 size;                              
  U16 fileID;                            
  U8  attrib;                            
  RL_TIME time;                          
} FINFO;

 
typedef struct {
  FS_TYPE fs_type;                       
  U64     capacity;                      
} Drive_INFO;

extern int finit (const char *drive);
extern int funinit (const char *drive);
extern int fdelete (const char *filename);
extern int frename (const char *oldname, const char *newname);
extern int ffind (const char *pattern, FINFO *info);
extern U64 ffree (const char *drive);
extern int fformat (const char *drive);
extern int fanalyse (const char *drive);
extern int fcheck (const char *drive);
extern int fdefrag (const char *drive);
extern int fattrib (const char *par, const char *path);
extern int fvol    (const char *drive, char *buf);
extern int finfo   (const char *drive, Drive_INFO *info);

 




 

 



 
#line 445 "C:\\Keil_v5\\ARM\\RV31\\INC\\RTL.h"

 
#line 453 "C:\\Keil_v5\\ARM\\RV31\\INC\\RTL.h"

 
#line 466 "C:\\Keil_v5\\ARM\\RV31\\INC\\RTL.h"

 




 




 



 



 



 
#line 501 "C:\\Keil_v5\\ARM\\RV31\\INC\\RTL.h"

 



 





 



 





 
#line 529 "C:\\Keil_v5\\ARM\\RV31\\INC\\RTL.h"

 




 
#line 545 "C:\\Keil_v5\\ARM\\RV31\\INC\\RTL.h"

 
#line 555 "C:\\Keil_v5\\ARM\\RV31\\INC\\RTL.h"

 
#line 563 "C:\\Keil_v5\\ARM\\RV31\\INC\\RTL.h"

 
#line 577 "C:\\Keil_v5\\ARM\\RV31\\INC\\RTL.h"

 



 
typedef struct sockaddr {          
  U16  sa_family;                  
  char sa_data[14];                
} SOCKADDR;

#pragma push
#pragma anon_unions

typedef struct in_addr {           
  union {
    struct {
      U8 s_b1,s_b2,s_b3,s_b4;      
    };
    struct {
      U16 s_w1,s_w2;               
    };
    U32 s_addr;                    
  };
} IN_ADDR;
#pragma pop

typedef struct sockaddr_in {       
  S16 sin_family;                  
  U16 sin_port;                    
  IN_ADDR sin_addr;                
  S8  sin_zero[8];                 
} SOCKADDR_IN;

typedef struct hostent {           
  char *h_name;                    
  char **h_aliases;                
  S16  h_addrtype;                 
  S16  h_length;                   
  char **h_addr_list;              
} HOSTENT;

extern void init_TcpNet (void);
extern BOOL main_TcpNet (void);
extern void timer_tick (void);
extern U8   udp_get_socket (U8 tos, U8 opt, 
                            U16 (*listener)(U8 socket, U8 *remip, U16 port, U8 *buf, U16 len));
extern BOOL udp_release_socket (U8 socket);
extern BOOL udp_open (U8 socket, U16 locport);
extern BOOL udp_close (U8 socket);
extern BOOL udp_mcast_ttl (U8 socket, U8 ttl);
extern U8  *udp_get_buf (U16 size);
extern BOOL udp_send (U8 socket, U8 *remip, U16 remport, U8 *buf, U16 dlen);
extern U8   tcp_get_socket (U8 type, U8 tos, U16 tout,
                            U16 (*listener)(U8 socket, U8 event, U8 *buf, U16 len));
extern BOOL tcp_release_socket (U8 socket);
extern BOOL tcp_listen (U8 socket, U16 locport);
extern BOOL tcp_connect (U8 socket, U8 *remip, U16 remport, U16 locport);
extern U8  *tcp_get_buf (U16 size);
extern U16  tcp_max_dsize (U8 socket);
extern BOOL tcp_check_send (U8 socket);
extern U8   tcp_get_state (U8 socket);
extern BOOL tcp_send (U8 socket, U8 *buf, U16 dlen);
extern BOOL tcp_close (U8 socket);
extern BOOL tcp_abort (U8 socket);
extern void tcp_reset_window (U8 socket);
extern BOOL arp_cache_ip (U8 *ipadr, U8 type);
extern BOOL arp_cache_mac (U8 *hwadr);
extern void ppp_listen (const char *user, const char *passw);
extern void ppp_connect (const char *dialnum, const char *user, const char *passw);
extern void ppp_close (void);
extern BOOL ppp_is_up (void);
extern void slip_listen (void);
extern void slip_connect (const char *dialnum);
extern void slip_close (void);
extern BOOL slip_is_up (void);
extern U8   get_host_by_name (U8 *hostn, void (*cbfunc)(U8 event, U8 *host_ip));
extern BOOL smtp_connect (U8 *ipadr, U16 port, void (*cbfunc)(U8 event));
extern void dhcp_disable (void);
extern BOOL igmp_join (U8 *group_ip);
extern BOOL igmp_leave (U8 *group_ip);
extern BOOL snmp_trap (U8 *manager_ip, U8 gen_trap, U8 spec_trap, U16 *obj_list);
extern BOOL snmp_set_community (const char *community);
extern BOOL icmp_ping (U8 *remip, void (*cbfunc)(U8 event));
extern BOOL ftpc_connect (U8 *ipadr, U16 port, U8 command, void (*cbfunc)(U8 event));
extern BOOL tftpc_put (U8 *ipadr, U16 port,
                       const char *src, const char *dst, void (*cbfunc)(U8 event));
extern BOOL tftpc_get (U8 *ipadr, U16 port, 
                       const char *src, const char *dst, void (*cbfunc)(U8 event));
extern BOOL sntp_get_time (U8 *ipadr, void (*cbfunc)(U32 utc_time));
extern void ftp_evt_notify (U8 evt);

 
extern int  socket (int family, int type, int protocol);
extern int  bind (int sock, const SOCKADDR *addr, int addrlen);
extern int  listen (int sock, int backlog);
extern int  accept (int sock, SOCKADDR *addr, int *addrlen);
extern int  connect (int sock, SOCKADDR *addr, int addrlen);
extern int  send (int sock, const char *buf, int len, int flags);
extern int  sendto (int sock, const char *buf, int len, int flags, SOCKADDR *to, int tolen);
extern int  recv (int sock, char *buf, int len, int flags);
extern int  recvfrom (int sock, char *buf, int len, int flags, SOCKADDR *from, int *fromlen);
extern int  closesocket (int sock);
extern int  getpeername (int sock, SOCKADDR *name, int *namelen);
extern int  getsockname (int sock, SOCKADDR *name, int *namelen);
extern int  ioctlsocket (int sock, long cmd, unsigned long *argp);
extern HOSTENT *gethostbyname (const char *name, int *err);







 


 
#line 5 "Main\\regs.h"
#line 6 "Main\\regs.h"
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



 

#line 7 "Main\\regs.h"
#line 1 "Main\\motors.h"



#line 5 "Main\\motors.h"
#line 1 "Main\\regs.h"
#line 344 "Main\\regs.h"


#line 6 "Main\\motors.h"
#line 1 ".\\UCNC\\Timers.h"



#line 5 ".\\UCNC\\Timers.h"
#line 6 ".\\UCNC\\Timers.h"


















typedef void(*TTimerHandler)(void);

typedef struct
{
  volatile 	BOOL 	enabled; 
  volatile 	u32 	interval;   	
	volatile	u32*	pMR;
	volatile 	u32*	pTC;	
	TTimerHandler 	handler;		
} TIMER_CONTROL_STRUCT;


extern volatile u32 dtfix;

void Init_TCS(TIMER_CONTROL_STRUCT* CTS,u8 t,u8 mr,TTimerHandler h);


void InitTimer(u8 num);



#line 7 "Main\\motors.h"








typedef struct tagMState {
	u8		Level;			
	s8		*Dir;			
   	s32		*Pos;			
   	s32		Lacc;			
	u64		*FrCur;			
	u64		Tcur;			
	u64 	LPON;			
	u64		LPOFF;			
	u8		*Posit;			
	u8		*StagePos;		
							
							
							
} TFMS;						


typedef struct tagFMControl {
	u64		*FrMin;			
	u64		*FrReq; 			
	u64		*FrMax; 			
	s32		*ReqPos;			
	u32		*LenOnPulse;	
  u16 	*Accel; 			
	s8	 	*ReqDir;			
	u8		*MoveBtn;		
	u8		*MovePos;		
	u8		*PositOn;		
} TFMC;						

typedef struct tagFMoveStatus {
	u32		LPON;			
	u32		LPOFF;			
	u8		Level;			
	float 	*Vc;			
	float 	*Vmin;			
} TFMVS;  	

typedef __packed struct tagFMoveControl {
	u32		*LenOnPulse;	
	float	*V;				
	float	*Vmin;			
	float 	*Vaccel;			
	float 	*Vmul;			
	float	Vmax;			
	u8		Enable;			

} TFMVC;  	


extern TIMER_CONTROL_STRUCT tcs_FMove;



extern TFMVC 	fmvc; 	
extern TFMVS 	fmvs;	


extern float *pX1;
extern float *pY1;
extern float *pZ1;
extern float *pX2;
extern float *pY2; 
extern float *pZ2;
extern float *pX3;
extern float *pY3;
extern float *pZ3;
extern u8 *pNumOpPoint;
extern float * pHdat;
extern s32	Index;
extern float *pdz;
extern u8 *pfZcomp;
extern u8 fStartMoveZLowSpeed;
extern float *pA,*pB,*pC,*pD;

void 	ShowMC(TFMC * mc);
void 	ShowMS(TFMS * ms);

void	AddPointFrz(void);
void	StartMoveZLowSpeed(void);
void InitMotorStructF(TFMS* ms, TFMC* mc );
void InitMotorStructALF(TFMS* ms, TFMC* mc );
void	FMove_Handler(void);
void	FMove_HandlerVconst(void);
void	FMove_HandlerDebugQueue(void);
void FMove_HandlerQuick(void);

void XYZToXYZImp(float X,float Y,float Z,s32 * Xi,s32 * Yi,s32 * Zi);
void XYZToXYZImpZcomp(float X,float Y,float Z,s32 * Xi,s32 * Yi,s32 * Zi);
void XYZImpToXYZ(s32 Xi,s32 Yi,s32 Zi,float *X,float *Y,float *Z);
void dXYZImpTodXYZ(s32 Xi,s32 Yi,s32 Zi,float *X,float *Y,float *Z);

void InitZComp(void);
float ZComp(float x, float y, float z);
void RecoveryZfreq(void);
void UpZ(void);
void	HTCorr(void);
void RetrySendPoint(void);
void SendAddPointPackFrz(s32 * pIndex,float * px, float * py, float * pz);
void FixPointPackFrz(s32 * pIndex,float * px, float * py, float * pz);


void InitZcompMoveXY(float Z);
void ZcompMoveXY(void);



#line 8 "Main\\regs.h"









































#line 69 "Main\\regs.h"


#line 84 "Main\\regs.h"


#line 93 "Main\\regs.h"











 





















typedef __packed struct tagFInfo{ 
	u32		index;     
    char 	name[14];
    char 	ext[4];
    u8	 	attr;
    u32 	size;
    u8	 	f;
} FInfo;


typedef u8(*TWHandler)(char * name,u8 * buffer,u16 len);


typedef struct {
	char 	name[20];	
	void 	*p;			
	u16		len;		
	u32		attr;		
	TWHandler	handle; 
} TVarAttr;

typedef struct {
	float X,Y;
} TPoint;

typedef TPoint TPoints[100];

typedef struct {
	u32 Count;
	TPoints points;
} TContur;


typedef struct tagTBlock { 
	s32		NumLine;	
	s32 	PosSSP;		
	u8 		Nonstop;	
						
	u8		cFeed;		
    float 	Feed;    	
    float 	Speed;    	
    u8 		cSpindel;   
    u8 		sSpindel;   
                        
                        
    u8 		cCold;      
    u8 		sCold1;     
                        
    u8 		sCold2;     
                        
    u8 		cPause;     
    u32 	lPause;  	

		u8 		cStop;      
    u8 		sStop;      
                        
                        
                        
    u8 		sGo;      	
                        
                        
    float 	Mul;    	
    float 	rMul;    	
    u8 		SetSizeReg; 
                        
                        
    u8 		rSetSizeReg;
    float 	Xs,Ys,Zs;  	
    u8 		comX,comY,comZ;  
    float 	Xr,Yr,Zr;    	
    float 	Xd,Yd,Zd;    	
	s32		Xi,Yi,Zi;		
	s32		Xsi,Ysi,Zsi;	
	s32		Xdi,Ydi,Zdi;	
	s32		dXi,dYi,dZi;	
	s32		signX,signY,signZ;	
	s32		e1;				
	s32		e2;				
	u8 		Lax; 			
	u8 		Nomove;			
	float 	dS;				
							
	u32		Tb;				
	char s[50];
} TBlock;

typedef u8 TFileName[20];


extern TFileName * pPrgFileName;
extern s8 * pPrgFileHandle;
extern u32 * pPrgLineCount;
extern u16 * pWF_CRC;

extern u8 *pCrushWater;
extern u8 *pByPass;



extern u8 		regs[1000]; 
extern u16		iva;	
extern TVarAttr 	va[]; 	



extern u8 OutAllocTable;
extern u32 CurVarIndex;
extern u8	VChange;

extern u16 *pFdbyFnom;	

extern u16	*pFnom;


extern u8 *pQURepCount; 
extern u16 *pQUTimeout; 

extern u8 *pACmdDump;
extern u8 *pAMsg;
extern u8 *pAAnswDump;

extern u8 *pAECmdDump;
extern u8 *pAEMsg;
extern u8 *pAEAnswDump;

extern u8 *pANCmdDump;
extern u8 *pANMsg;

extern u8 *pErrCSU1;

extern u8 *pDropCmd;

extern u8	*pKP_NA_Max;

extern u8	*pPress_NA_Max;

extern u8	KP_NA_Count;

extern u8 *pLinkKP;




extern float 	*pX_PG_MM;
extern u32		*pX_SPR;
extern float	*pX_MIN;
extern float	*pX_MAX;
extern s32 		vX_MIN_POS; 
extern s32 		vX_MAX_POS; 

extern float 	*pY_PG_MM;
extern u32		*pY_SPR;
extern float	*pY_MIN;
extern float	*pY_MAX;
extern s32 		vY_MIN_POS; 
extern s32 		vY_MAX_POS; 

extern float 	*pZ_PG_MM;
extern u32		*pZ_SPR;
extern float	*pZ_MIN;
extern float	*pZ_MAX;
extern s32 		vZ_MIN_POS; 
extern s32 		vZ_MAX_POS; 


extern s32 * dXPos;
extern s32 * dYPos;
extern s32 * dZPos;





extern u16 *pIntKPCtrl;
extern u16 *pIntKPCtrlStop;


extern u8	*pKP_NA_Max;



extern u8 *pLinkKP;

extern u8	KP_NA_Count;

extern u8 *pCorrStop;

extern u8 *pRecoverBlock;

extern u8 *pHTCorr; 

extern u8 *pZZeroDat; 



extern u8	fStopPrg;

extern u8	fStartPrg;

extern u8	fSaveRegs;


extern u16 *pFdbyFnom;	

extern u16	*pFnom;

void AllocFrzRegisters(void);
void InitFrzRegisters(void);
void InitFrzRegsAfterLoad(void);
void LoadFrzBackupRegs(void);

void SaveRegs(void);
void SaveRegsNoMes(void);
void LoadRegsFromFile(void);

u8 Cross(u32 sx,u16 slens,u32 dx,u16 dlen);




#line 6 "Main\\Handlers.h"



 

#line 28 "Main\\Handlers.h"

extern volatile u8 Busy;
extern u8 		sG0;
extern u8 		*pPrgRun;

extern s32 		*pCurCadr;
extern s32		*pNumReadLine;
extern s32 		sCurCadr;
extern u8 		*pRecBlock;
extern	u8 		*pRCS;		

extern u8 		sBusy;
extern TBlock *pBlock;


extern u8 sXMovePos,sYMovePos,sZMovePos,sFMVCEnable;
extern float * pTrAngle; 
extern TBlock * eb;
extern volatile float Sr; 
extern u8 SPS;


extern u32 *pRunSpPause;


u8 ReadPrevLine(char * CadrLine);
u8 ReadNextLine(char * CadrLine);

void RunNextCadrFrz(void);
void RunNextCadrFrzMain(void);
void RecRunNextCadrFrz(void);
void CrushWaterHandlerFrz(void);
void TranslatePrg(void);
void TranslatePrgLine(const char * s);

void SearchStopPoint(void);
u8 		InitPrgStreams(void);
void	InitQExBlks(void);
u8 qbDelFirst(void);
TBlock * qbFirstBlock(void);
TBlock * qbLastBlock(void);
u8 qbCount(void);
u8 qbAddBlock(TBlock * b);

void qbIncIndex(u8* Index);
u8 qbFirstIndex(void);
u8 qbLastFreeIndex(void);
TBlock * qbGetBlockIndex(u8 Index);

extern u8 EndTranslate;

#line 9 "Main\\Handlers.c"
#line 1 ".\\UCNC\\VirtualPins.h"



#line 5 ".\\UCNC\\VirtualPins.h"
#line 6 ".\\UCNC\\VirtualPins.h"





#line 31 ".\\UCNC\\VirtualPins.h"

#line 48 ".\\UCNC\\VirtualPins.h"





typedef struct{
	u16 ErrorCode; 	
	u8 vNum;		
	u8 sNum;		
	u8 sPort;		
	u32 sPin;		
	u8 Dir;			
	u8 Inv;			
} TPinError;

























typedef void(*TErrHandler)(TPinError * pe);


typedef struct tagVPIN {
	u8		nPin; 		
	u8		Inv;		
	u8		State;		
} TVPIN;

typedef TVPIN TaVPIN[36];

extern TaVPIN *pvPins;



void SetPinsErrHandler(TErrHandler eh);

BOOL InitPin(u8 n);






BOOL SetPin(u8 n);






void QSetPin(u8 n);


BOOL ClrPin(u8 n);






void QClrPin(u8 n);


u32 GetPin(u8 n);






u32 QGetPin(u8 n);



u8 		GetPinDir(u8 n);


u8 		GetPinInv(u8 n);


void 	SetPinInv(u8 n,u8 i);

void InitVirtualPins (void);

void ClrGetPin(u8 n);


#line 10 "Main\\Handlers.c"
#line 1 ".\\UCNC\\ti.h"
#line 4 ".\\UCNC\\ti.h"
#line 5 ".\\UCNC\\ti.h"




























#line 41 ".\\UCNC\\ti.h"




void DecTIs(void); 
void IncTimes(void); 

extern 	u32 	ti[];	
extern 	u32 	time[];	
extern TIMER_CONTROL_STRUCT tcs_TI;

void TI_Handler(void);



#line 67 ".\\UCNC\\ti.h"

#line 74 ".\\UCNC\\ti.h"





#line 89 ".\\UCNC\\ti.h"

#line 98 ".\\UCNC\\ti.h"

#line 117 ".\\UCNC\\ti.h"

#line 11 "Main\\Handlers.c"
#line 12 "Main\\Handlers.c"
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

#line 13 "Main\\Handlers.c"
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

#line 14 "Main\\Handlers.c"
#line 1 "Main\\bfs.h"



#line 5 "Main\\bfs.h"
#line 1 "Main\\fs.h"













#line 15 "Main\\fs.h"

#line 39 "Main\\fs.h"


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




#line 6 "Main\\bfs.h"


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

#line 15 "Main\\Handlers.c"
#line 1 "Main\\FreqInvr.h"



#line 5 "Main\\FreqInvr.h"

extern u32 * pFIPWM;

extern u32 * pFIPWMFreq;

void FILoadConf(void);
void FIInit(void);
void FIUnlock(void);
void FISetFreq(u16 Freq);
void FISetDir(u8 rev);
void FIStart(void);
void FIStop(void);
void FIQuery(void);
void FIAnswer(u8 * buffer,u16 len);


#line 16 "Main\\Handlers.c"

#line 1 "Main\\VPFrz.h"



#line 5 "Main\\VPFrz.h"



#line 9 "Main\\VPFrz.h"


#line 23 "Main\\VPFrz.h"








#line 38 "Main\\VPFrz.h"














extern TaVPIN vPinsdef;





#line 18 "Main\\Handlers.c"
#line 1 "Main\\Motor_X.h"



#line 5 "Main\\Motor_X.h"

#line 7 "Main\\Motor_X.h"
#line 8 "Main\\Motor_X.h"

extern TIMER_CONTROL_STRUCT tcs_MotorX; 	
extern TFMC 	mc_X;
extern TFMS 	ms_X;

void	MotorX_Handler(void);






#line 19 "Main\\Handlers.c"
#line 1 "Main\\Motor_Y.h"



#line 5 "Main\\Motor_Y.h"

#line 7 "Main\\Motor_Y.h"
#line 8 "Main\\Motor_Y.h"

extern TIMER_CONTROL_STRUCT tcs_MotorY; 	
extern TFMC 	mc_Y;
extern TFMS 	ms_Y;

void	MotorY_Handler(void);






#line 20 "Main\\Handlers.c"
#line 1 "Main\\Motor_Z.h"



#line 5 "Main\\Motor_Z.h"

#line 7 "Main\\Motor_Z.h"
#line 8 "Main\\Motor_Z.h"

extern TIMER_CONTROL_STRUCT tcs_MotorZ; 	
extern TFMC 	mc_Z;
extern TFMS 	ms_Z;

void	MotorZ_Handler(void);






#line 21 "Main\\Handlers.c"

float X,Y,Z; 



TFileName * pPrgFileName;
s8 * pPrgFileHandle;
u32 * pPrgLineCount;
u16 * pWF_CRC;

u8	*pPrgRun;		

u8 		*pRecBlock;
u8 	*pRCS;		
s32 *pCurCadr;			
s32 *pNumReadLine;
s32 sCurCadr;			


volatile u8 	Busy = 0;

u8 sG0 = 0; 
			
			
			
			
TBlock *pBlock;



TFileStream ts,rs;



float * pTrAngle; 
volatile float Sr; 
u32 *pRunSpPause;

u8 CheckPrgFile(void) {
	s8 	res;
	u32	i;
	u8 tmps[50];

	if (*pPrgFileHandle >= 0) {
		
		return 1;
	} else {
		
		res = FS_Assign((u8*)pPrgFileName,pPrgFileHandle);
		if (res == 0) {
			res = FS_Reset(*pPrgFileHandle);
			if (res == 0) {
				
				i=0;
				while (i < *pCurCadr) {
					res = bFS_ReadLn(*pPrgFileHandle,tmps,50);
					if (res) {
						Msg("Err ReadLn PrgFile %s : %d\r\n",pPrgFileName,res);
						
						return 0;
					}
					i++;
				}
				return 1;
			} else {
				Msg("Err Reset PrgFile %s : %d\r\n",pPrgFileName,res);
				FS_Close(pPrgFileHandle);
				return 0;
			}
		} else {
			Msg("Err Assing PrgFile %s : %d\r\n",pPrgFileName,*pPrgFileHandle);
			return 0;
		}
	}
}

u8 InitPrgStreams(void){
	
	
	s8 	res;

	ts.Pos = 0;
	rs.Pos = 0;
	if (*pPrgFileHandle >= 0) {
		
		InitStream(&ts,*pPrgFileHandle);
		InitStream(&rs,*pPrgFileHandle);
		Msg("Open Prg Streams 1\r\n");
		*pNumReadLine=0;
		return 1;
	} else {
		
		res = FS_Assign((u8*)pPrgFileName,pPrgFileHandle);
		if (res == 0) {
			res = FS_Reset(*pPrgFileHandle);
			if (res == 0) {
				InitStream(&ts,*pPrgFileHandle);
				InitStream(&rs,*pPrgFileHandle);
				Msg("Open Prg Streams 2\r\n");
				*pNumReadLine=0;
				return 1;
			} else {
				FS_Close(pPrgFileHandle);
				Msg("Err Reset PrgFile %s : %d h %d\r\n",pPrgFileName,res,*pPrgFileHandle);
				
				return 0;
			}
		} else {
			Msg("Err Assing PrgFile %s : %d\r\n",pPrgFileName,*pPrgFileHandle);
			return 0;
		}
	}
}

u8 ReadNextLine(char * CadrLine){

	if (*pCurCadr < *pPrgLineCount) {
		if (CheckPrgFile()) {
			if (bFS_ReadLn(*pPrgFileHandle,(u8*)CadrLine,50)==0) return 1;
			else return 0;
			
			
			
		} else return 0;
	} 
	
	return 0;
}

u8 ReadPrevLine(char * CadrLine){
	if (*pCurCadr > -1) {
		if (CheckPrgFile()) {
			if (bFS_BReadLn(*pPrgFileHandle,(u8*)CadrLine,50)==0) return 1;
			else return 0;
			
			
			
		} else return 0;
		
		
		
		
	} 
	
	return 0;
}

u8 TryStrToFloat(char * Param,float * f){
  int i;
  u8 minus;
  u8 frac;
  float c; 
  float d; 
  u8 curd; 
  char ch;
  u8 cdd;

  minus = 0; 
  frac = 0;  
  c = 0; 
  d = 0; 
  cdd = 0; 
  for (i=0;i < strlen(Param);i++) {
	ch = *(Param+i);
	switch (ch) {
      case '-':
        if (i > 1) return 0; 
        else minus = 1; 
      break;
      case '+':
        if (i > 1) return 0; 
        else minus = 0; 
      break;
			case '.':
      case ',':
        if (frac == 1) return 0; 
        else frac=1; 
      break;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
	  case '9':
        curd=ch-48;
        if (frac == 0) 
			
          	c = 10*c+curd;
        else {
          	
         	 d = 10*d+curd;
			 cdd++;
		}
      break;
	  default: return 0; 
    }
  }
  
  while (cdd) { d/=10; cdd--;}
  *f=c+d;
  if (minus == 1) *f=-*f;
  return 1;
}

u8 IsCmd(char ch){
   if (
   		(ch == 'G') ||
   		(ch == 'g') ||
   		(ch == 'M') ||
   		(ch == 'm') ||
   		(ch == 'X') ||
   		(ch == 'x') ||
   		(ch == 'Y') ||
   		(ch == 'y') ||
   		(ch == 'P') ||
   		(ch == 'p') ||
   		(ch == 'S') ||
   		(ch == 's') ||
   		(ch == 'F') ||
   		(ch == 'f')	||
   		(ch == 'Z') ||
   		(ch == 'z')
	  ) return 1;
   else return 0;
}

u8 IsDigits(char ch){
   if (
   		(ch == '0') ||
   		(ch == '1') ||
   		(ch == '2') ||
   		(ch == '3') ||
   		(ch == '4') ||
   		(ch == '5') ||
   		(ch == '6') ||
   		(ch == '7') ||
   		(ch == '8') ||
   		(ch == '9') ||
   		(ch == '-') ||
   		(ch == '+') ||
		(ch == '.') ||
   		(ch == ',')
	  ) return 1;
   else return 0;
}

u8	ApplyCmd(char cmd,char * Param, TBlock * pBlock){
	float fParam;
	u16 iParam;
	u8 res;




	if (!TryStrToFloat(Param,&fParam)) {
	    
		return 2;
	}


	res = 0; 
  	
	if ((cmd == 'g') || (cmd == 'G')) {
		
		
	    iParam=(u16)ceil(fParam);
	    res=0; 
		switch (iParam) {
	    	case	0:
			case	1: 
		        
	    	    (*pBlock).sGo = iParam;
				

	      	break;
	      	case 4:
	        	
	        	(*pBlock).cPause = 1;
	      	break;
			case 20:
			case 21:
	        
	        	if (iParam == 20) (*pBlock).rMul = 25.3;  
	          	else (*pBlock).rMul = 1;    
	      	break;
	      	case 90:
			case 91:
	        	
	        	(*pBlock).rSetSizeReg = iParam-90;
	      	break;
	      	default: res = 3; 
		}
	} else {
		if ((cmd == 'x') || (cmd == 'X')) {
			
			
		    (*pBlock).Xr = fParam;
		    (*pBlock).comX = 1;
		} else {
			if ((cmd == 'y') || (cmd == 'Y')) {
				
			    
			    (*pBlock).Yr=fParam;
			    (*pBlock).comY=1;
			} else {
				if ((cmd == 'z') || (cmd == 'Z')) {
				    (*pBlock).Zr=fParam;
				    (*pBlock).comZ=1;
				} else {
					if ((cmd == 'm') || (cmd == 'M')) {
						
					    
					    iParam=(u16)ceil(fParam);
					    res=0; 
						switch (iParam) {
					      case 0:
								case 2:
					        (*pBlock).cStop = 1;
					        (*pBlock).sStop = iParam;
					      break;
					      case 3:
								case 4:
					        
					        (*pBlock).cSpindel = 1;
					        (*pBlock).sSpindel = iParam-2;
									
									(*pBlock).cPause = 1;
									(*pBlock).lPause = *pRunSpPause; 
								break;
								case 5:
					        (*pBlock).cSpindel = 1;
					        (*pBlock).sSpindel = 0;
					      break;
								case 7:
					        (*pBlock).cCold = 1;
					        (*pBlock).sCold1 = 1;
					      break;
					      case 8:
					        (*pBlock).cCold = 1;
					        (*pBlock).sCold2 = 1;
					      break;
					      case 9:
					        (*pBlock).cCold = 1;
					        (*pBlock).sCold1 = 0;
					        (*pBlock).sCold2 = 0;
					      break;
					      default: res=4; 
					    }
					} else {
						if ((cmd == 'f') || (cmd == 'F')) {
							
						    
						    (*pBlock).cFeed = 1;
							if (fParam < 0) res = 5; 
						    (*pBlock).Feed = fParam;
						} else {
							if ((cmd == 's') || (cmd == 'S')) {
							
							    
							    if (fParam < 0) res = 6; 
							    (*pBlock).cSpindel = 1;  
							    (*pBlock).Speed = fParam;
							} else {
								if ((cmd == 'p') || (cmd == 'P')) {
									
								    
								    if (fParam < 0) res = 7; 
								    (*pBlock).lPause = (u16)ceil(fParam);
								} else { 
								   	
									
								   	res = 1;
								}
							} 
						} 
					} 
				} 
			}
		}
	}
	return res;
}

void InitFirstBlockFrz(TBlock * ib){
	

  	memset((u8*)ib,0,sizeof (*ib));
	
	(*ib).Mul = 1;
	(*ib).rMul = 1;
  	XYZImpToXYZ(	*(ms_X.Pos),		*(ms_Y.Pos),		*(ms_Z.Pos),
   					&((*ib).Xs),	&((*ib).Ys),	&((*ib).Zs));
	(*ib).Xsi = *(ms_X.Pos);
	(*ib).Ysi = *(ms_Y.Pos);
	(*ib).Zsi = *(ms_Z.Pos);
	(*ib).Xi = *(ms_X.Pos);
	(*ib).Yi = *(ms_Y.Pos);
	(*ib).Zi = *(ms_Z.Pos);




}

void InitNextBlock(TBlock * pBlock){
	
	
  	(*pBlock).Xs = (*pBlock).Xd;
  	(*pBlock).Ys = (*pBlock).Yd;
  	(*pBlock).Zs = (*pBlock).Zd;
	
}

void InitBlockByPrev(TBlock * ib,TBlock * prevb){
	
	if (prevb!=0) {
	  	memset((u8*)ib,0,sizeof (*pBlock));
  		(*ib).Xs = (*prevb).Xd;
  		(*ib).Ys = (*prevb).Yd;
  		(*ib).Zs = (*prevb).Zd;
  		(*ib).Xsi = (*prevb).Xdi;			   
  		(*ib).Ysi = (*prevb).Ydi;
  		(*ib).Zsi = (*prevb).Zdi;
  		(*ib).sGo = (*prevb).sGo;
  		(*ib).SetSizeReg = (*prevb).SetSizeReg;
  		(*ib).Mul = (*prevb).Mul;
  		(*ib).rSetSizeReg = (*prevb).rSetSizeReg;
  		(*ib).rMul = (*prevb).rMul;
  		(*ib).Speed = (*prevb).Speed;
  		(*ib).Feed = (*prevb).Feed;
	
	
	} else InitFirstBlockFrz(ib);

}



void CalcBlockFrz(TBlock * pB,u8 exe){
	float L;
	
	

  (*pB).SetSizeReg = (*pB).rSetSizeReg;
  (*pB).Mul = (*pB).rMul;
  if ((*pB).SetSizeReg == 0) {
    
    if ((*pB).comX == 1) {
      
      (*pB).Xd = (*pB).Xr*(*pB).Mul;
    } else {
      
      (*pB).Xd = (*pB).Xs;
    }
    if ((*pB).comY == 1) {
      
      (*pB).Yd = (*pB).Yr*(*pB).Mul;
    } else {
      
      (*pB).Yd = (*pB).Ys;
    }
    if ((*pB).comZ == 1) {
      
      (*pB).Zd = (*pB).Zr*(*pB).Mul;
    } else {
      
      (*pB).Zd = (*pB).Zs;
    }
  } else {
    
    if ((*pB).comX == 1) {
      
      (*pB).Xd = (*pB).Xs+(*pB).Xr*(*pB).Mul;
    } else {
      
      (*pB).Xd = (*pB).Xs;
    }
    if ((*pB).comY == 1) {
      
      (*pB).Yd = (*pB).Ys + (*pB).Yr*(*pB).Mul;
    } else {
      
      (*pB).Yd = (*pB).Ys;
    }
    if ((*pB).comZ == 1) {
      
      (*pB).Zd = (*pB).Zs + (*pB).Zr*(*pB).Mul;
    } else {
      
      (*pB).Zd = (*pB).Zs;
    }
  }





  


  if (exe) {
  	
	XYZToXYZImpZcomp((*pB).Xd,(*pB).Yd,(*pB).Zd,
  				  &(*pB).Xdi,&(*pB).Ydi,&(*pB).Zdi);


  	(*pB).Xi = (*pB).Xsi;
  	(*pB).Yi = (*pB).Ysi;
	(*pB).Zi = (*pB).Zsi;
  	(*pB).dXi = abss32((*pB).Xdi - (*pB).Xsi);
  	(*pB).dYi = abss32((*pB).Ydi - (*pB).Ysi);
	(*pB).dZi = abss32((*pB).Zdi - (*pB).Zsi);
	if (((*pB).dXi==0)&&((*pB).dYi==0)&&((*pB).dZi==0)) {
		
		
		(*pB).Nomove = (1&& (!(*pB).cFeed)  && (!(*pB).cSpindel) && (!(*pB).cCold) && 				 			(!(*pB).cPause) && (!(*pB).cStop)    && ((*pB).sGo==1));



	} else {
		
	 	(*pB).Nomove = 0; 
		
		(*pB).signX = (*pB).Xsi < (*pB).Xdi ? 1 : -1;
        (*pB).signY = (*pB).Ysi < (*pB).Ydi ? 1 : -1;
		(*pB).signZ = (*pB).Zsi < (*pB).Zdi ? 1 : -1;

		(*pB).dS=sqrt(sqr((*pB).Xd-(*pB).Xs)+sqr((*pB).Yd-(*pB).Ys)+sqr((*pB).Zd-(*pB).Zs));
        L = sqrt((*pB).dXi*(*pB).dXi+(*pB).dYi*(*pB).dYi+(*pB).dZi*(*pB).dZi);
		if (((*pB).dXi >= (*pB).dYi)&&((*pB).dXi >= (*pB).dZi))  {
			
			(*pB).Lax = 0;
   			(*pB).e1 = (*pB).dXi - (*pB).dYi;
  			(*pB).e2 = (*pB).dXi - (*pB).dZi;
			(*pB).dS = (*pB).dS/(*pB).dXi;
		} else {
  			if (((*pB).dYi >= (*pB).dXi)&&((*pB).dYi >= (*pB).dZi))  {
    			
				(*pB).Lax = 1;
				
       			(*pB).e1 = (*pB).dYi - (*pB).dXi;
	  			(*pB).e2 = (*pB).dYi - (*pB).dZi;
				(*pB).dS = (*pB).dS/(*pB).dYi;
  			} else 
  			if (((*pB).dZi >= (*pB).dXi)&&((*pB).dZi >= (*pB).dYi))  {
    			
				(*pB).Lax = 2;
				
       			(*pB).e1 = (*pB).dZi - (*pB).dXi;
	  			(*pB).e2 = (*pB).dZi - (*pB).dYi;
				(*pB).dS = (*pB).dS/(*pB).dZi;
  			};
		}
		
		
		switch ((*pB).Lax) {
			case 0:	(*pB).Tb = (int)((*pX_PG_MM)*L*((u64)25000000)/((*pX_SPR)*  (*pB).dXi)); break;
			case 1:	(*pB).Tb = (int)((*pY_PG_MM)*L*((u64)25000000)/((*pY_SPR)*  (*pB).dYi)); break;
    		case 2: (*pB).Tb = (int)((*pZ_PG_MM)*L*((u64)25000000)/((*pZ_SPR)*  (*pB).dZi)); break;
		}		






	};
  }				


}

void CalcBlock(TBlock * pBlock){


  (*pBlock).SetSizeReg = (*pBlock).rSetSizeReg;
  (*pBlock).Mul = (*pBlock).rMul;
  if ((*pBlock).SetSizeReg == 0) {
    
    if ((*pBlock).comX == 1) {
      
      (*pBlock).Xd = (*pBlock).Xr*(*pBlock).Mul;
    } else {
      
      (*pBlock).Xd = (*pBlock).Xs;
    }
    if ((*pBlock).comY == 1) {
      
      (*pBlock).Yd = (*pBlock).Yr*(*pBlock).Mul;
    } else {
      
      (*pBlock).Yd = (*pBlock).Ys;
    }
    if ((*pBlock).comZ == 1) {
      
      (*pBlock).Zd = (*pBlock).Zr*(*pBlock).Mul;
    } else {
      
      (*pBlock).Zd = (*pBlock).Zs;
    }
  } else {
    
    if ((*pBlock).comX == 1) {
      
      (*pBlock).Xd = (*pBlock).Xs+(*pBlock).Xr*(*pBlock).Mul;
    } else {
      
      (*pBlock).Xd = (*pBlock).Xs;
    }
    if ((*pBlock).comY == 1) {
      
      (*pBlock).Yd = (*pBlock).Ys + (*pBlock).Yr*(*pBlock).Mul;
    } else {
      
      (*pBlock).Yd = (*pBlock).Ys;
    }
    if ((*pBlock).comZ == 1) {
      
      (*pBlock).Zd = (*pBlock).Zs + (*pBlock).Zr*(*pBlock).Mul;
    } else {
      
      (*pBlock).Zd = (*pBlock).Zs;
    }
  }





 
}

void BackCalcBlock(TBlock * pBlock){


  if ((*pBlock).SetSizeReg == 0) {
    
    if ((*pBlock).comX == 1) {
      
      (*pBlock).Xd = (*pBlock).Xr*(*pBlock).Mul;
    } else {
      
      (*pBlock).Xd = (*pBlock).Xs;
    }
    if ((*pBlock).comY == 1) {
      
      (*pBlock).Yd = (*pBlock).Yr*(*pBlock).Mul;
    } else {
      
      (*pBlock).Yd = (*pBlock).Ys;
    }
  } else {
    
    if ((*pBlock).comX == 1) {
      
      (*pBlock).Xd = (*pBlock).Xs - (*pBlock).Xr*(*pBlock).Mul;
    } else {
      
      (*pBlock).Xd = (*pBlock).Xs;
    }
    if ((*pBlock).comY == 1) {
      
      (*pBlock).Yd = (*pBlock).Ys - (*pBlock).Yr*(*pBlock).Mul;
    } else {
      
      (*pBlock).Yd = (*pBlock).Ys;
    }
  }
  (*pBlock).SetSizeReg = (*pBlock).rSetSizeReg;
  (*pBlock).Mul = (*pBlock).rMul;
}

void G0Handler(void){
	s32 Xi,Yi,Zi;

	Busy = 1;
	XYZToXYZImpZcomp(X,Y,Z,&Xi,&Yi,&Zi);
	*(mc_X.ReqPos) = Xi;
	*(mc_Y.ReqPos) = Yi;
	*(mc_Z.ReqPos) = Zi;

	*pCorrStop = 0;

	((LPC_RTC_TypeDef *) ((0x40000000UL) + 0x24000) )->ALDOW = 0;
	
	*pRecoverBlock = 0;
	if (Zi < *(ms_Z.Pos)) {
		
		*(mc_X.MovePos) = 1;
		*(mc_Y.MovePos) = 1;
		sG0 = 1;
	} else {
		
		*(mc_Z.MovePos) = 1;
		sG0 = 3;
	}	

}

__inline void G1Handler(void){
	
	*(fmvs.Vc) = *(fmvc.Vmin);
	Busy = 1;
	
  fmvc.Enable=1;
}

void SetFeed(TBlock * pBlock){
	
	if ((*pBlock).cFeed) {
		(*pBlock).cFeed = 0;
		*(fmvc.V) = (*pBlock).Feed / 60;
		fmvc.Vmax = *(fmvc.V)*(*(fmvc.Vmul)/100);

		if (*(fmvs.Vc) > fmvc.Vmax) *(fmvs.Vc) = fmvc.Vmax;
		
		memcpy((void*)&(((LPC_RTC_TypeDef *) ((0x40000000UL) + 0x24000) )->GPREG3),(void*)fmvc.V,4);    


	}
}

void SetSpindle(TBlock * pBlock){
	u16 Freq;
	Freq = (int)((*pBlock).Speed)*(*pFnom)/(*pFdbyFnom);
	



	
    if ((*pBlock).cSpindel == 1) { 
      
	  	switch ((*pBlock).sSpindel) {
       	case 0:
				
					FIStop();

				break;
        case 1:
					FISetFreq(Freq);
					FISetDir(0);
					FIStart();

				break;
        case 2:
					FISetFreq(Freq);
					FISetDir(1);
					FIStart();

				break;
	  }
      
      (*pBlock).cSpindel=0;
    }
}

void SetCold(TBlock * pBlock){
   	
    if ((*pBlock).cCold == 1) {
      if ((*pBlock).sCold1 == 1) {
        
				Msg("Cool1 On\r\n");
				QSetPin(12); 
			} else {
				
				Msg("Cool1 Off\r\n");
				QClrPin(12); 
			}
      if ((*pBlock).sCold2 == 1) {
        

				QSetPin(13); 
			} else {
				

				QClrPin(13); 
			}
      (*pBlock).cCold = 0;
    }
}

void SetPause(TBlock * pBlock){
	
    if ((*pBlock).cPause == 1) {
			ti[6]=(((*pBlock). lPause)*(1000/(2500/25)))+1;

      (*pBlock).cPause = 0;
			*(fmvs.Vc) = *(fmvc.Vmin);
    } else 	ti[6]=1;
}

void RecSetPause(TBlock * pBlock){
	
    if ((*pBlock).cPause == 1) {
      	(*pBlock).cPause = 0;
    }
}

u8 EndPause(void) {
	return (ti[6]==1);
}

void SetGoFrz(TBlock * pBlock){
	if (((*pBlock).comX)||((*pBlock).comY)||((*pBlock).comZ)) {
		(*pBlock).comX = 0;
		(*pBlock).comY = 0;
		(*pBlock).comZ = 0;
		if ((*pBlock).sGo == 0) {
			

			X = (*pBlock).Xd;
			Y = (*pBlock).Yd;
			Z = (*pBlock).Zd;
			G0Handler();
		} else {
			G1Handler();
		}
	}
}

void RecSetGo(TBlock * pBlock){
	if (((*pBlock).comX)||((*pBlock).comY)||((*pBlock).comZ)) {
		(*pBlock).comX = 0;
		(*pBlock).comY = 0;
		(*pBlock).comZ = 0;
		if ((*pBlock).sGo == 0) {
			

		} else {
			

		}
	}
}

u8 EndGo(void){
  	
	
	return 1;
}

void SetStop(TBlock * pBlock) {
    if ((*pBlock).cStop == 1) {
      
			switch ((*pBlock).sStop) {
				case 0:
					(*pPrgRun) = 0;
					((LPC_RTC_TypeDef *) ((0x40000000UL) + 0x24000) )->ALSEC = *pPrgRun;
					FIStop();
				break;
				case 2:
					
					(*pPrgRun) = 0;
					((LPC_RTC_TypeDef *) ((0x40000000UL) + 0x24000) )->ALSEC = *pPrgRun;
					QClrPin(12); 
					QClrPin(13); 
					FIStop();
					Msg("Full Off\r\n");
				break;
			}
    }
}

void RecSetStop(TBlock * pBlock) {
    if ((*pBlock).cStop == 1) {
      
	  switch ((*pBlock).sStop) {
	      case 0:
					
					Msg("Pause To Start\r\n");
				break;
	      case 2:
					
					
					QClrPin(12); 
					QClrPin(13); 
					FIStop();
					Msg("Full Off\r\n");
				break;
	  }
    }
}

u8 EndStop(void) {
	
	return 1;
}

void ErrToMessage(u8 err,char * mess){
 	switch (err) {
		case 1: strcpy("unknown command",mess); break;
		case 2: strcpy("parametr error",mess); break;
		case 3: strcpy("unknown G-command",mess); break;
		case 4: strcpy("unknown M-command",mess); break;
		case 5: strcpy("parametr F less zero",mess); break;
		case 6: strcpy("parametr S less zero",mess); break;
		case 7: strcpy("parametr P less zero",mess); break;
		case 8: strcpy("empty line",mess); break;
		default: sprintf(mess,"unknown error %d",err);
	}
}



u8	BackApplyCmd(char cmd,char * Param){
	float fParam;
	u16 iParam;
	u8 res;



	if (!TryStrToFloat(Param,&fParam)) {
	    
		return 2;
	}
	res = 0; 
  	
	if ((cmd == 'g') || (cmd == 'G')) {
		
		
	    iParam=(u16)ceil(fParam);
	    res=0; 
		switch (iParam) {
	    	case	0:
			case	1: 
		        
	    	    (*pBlock).sGo = iParam;
	      	break;
	      	case 4:
	        	
	        	(*pBlock).cPause = 1;
	      	break;
			case 20:
			case 21:
		       	
	          	
	        	if (iParam == 20) (*pBlock).rMul = 1;  
	          	else (*pBlock).rMul = 25.3;    
	      	break;
	      	case 90:
			case 91:
	        	
	        	(*pBlock).rSetSizeReg = iParam-90;
		        
        		if ((*pBlock).rSetSizeReg == 1)  
					(*pBlock).rSetSizeReg=0; 
				else (*pBlock).rSetSizeReg=1;
	      	break;
	      	default: res = 3; 
		}
	} else {
		if ((cmd == 'x') || (cmd == 'X')) {
			
			
		    (*pBlock).Xr = fParam;
		    (*pBlock).comX = 1;
		} else {
			if ((cmd == 'y') || (cmd == 'Y')) {
				
			    
			    (*pBlock).Yr=fParam;
			    (*pBlock).comY=1;
			} else {
				if ((cmd == 'm') || (cmd == 'M')) {
					
				    
				    iParam=(u16)ceil(fParam);
				    res=0; 
					switch (iParam) {
				      case 0:
					  case 2:
				        (*pBlock).cStop = 1;
				        (*pBlock).sStop = iParam;
				      break;
				      case 3:
					  case 4:
				        
				        (*pBlock).cSpindel = 1;
				        (*pBlock).sSpindel = iParam-2;
				      break;
				      case 5:
				        (*pBlock).cSpindel = 1;
				        (*pBlock).sSpindel = 0;
				      break;
				      case 7:
				        (*pBlock).cCold = 1;
				        (*pBlock).sCold1 = 1;
				      break;
				      case 8:
				        (*pBlock).cCold = 1;
				        (*pBlock).sCold2 = 1;
				      break;
				      case 9:
				        (*pBlock).cCold = 1;
				        (*pBlock).sCold1 = 0;
				        (*pBlock).sCold2 = 0;
				      break;
					  case 100:
					  case 101:
						
					 	
					  break;
					  case 103: 
					  case 104: 
					  break;
					  case 110: 
					  break;
				      default: res=4; 
				    }
				} else {
					if ((cmd == 'f') || (cmd == 'F')) {
						
					    
					    (*pBlock).cFeed = 1;
						if (fParam < 0) res = 5; 
					    (*pBlock).Feed = fParam;
					} else {
						if ((cmd == 's') || (cmd == 'S')) {
						
						    
						    if (fParam < 0) res = 6; 
						    (*pBlock).cSpindel = 6;  
						    (*pBlock).Speed = fParam;
						} else {
							if ((cmd == 'p') || (cmd == 'P')) {
								
							    
							    if (fParam < 0) res = 7; 
							    (*pBlock).lPause = (u16)ceil(fParam);
							} else { 
							   	
								
							   	res = 1;
							}
						} 
					} 
				} 
			}
		}
	}
	return res;
}

u8 LineToBlock(const char * CadrLine,u8 * errindex, TBlock * b){
	
	u8 i,reg,ParamIndex,res;
	char Param[20];
	char ch,cmd;
	

	memset(Param,0,20);
	cmd=0;
	res=0;
	reg=0; 
	ParamIndex=0; 
	i=0;
	while (((*(CadrLine+i)) != 13)){
		ch = *(CadrLine+i); 
		
		
		
		if (!((ch == 32) || (ch == 8))) {
			

			if (reg==0) {
				
		        if (IsCmd(ch)) {
		          cmd=ch;
		          reg=1;
		          i++;
				  
		        } else {
		          
		          *errindex = i;
		          return 1;
		        }
			} else {
				
		        
		        if (IsDigits(ch)) {
					
					
		          	Param[ParamIndex]=ch;
					ParamIndex++;
		          	i++;
		        } else { 
		          	
		          	
								
		          	res = ApplyCmd(cmd,Param,b);
								
		          	if (res == 0) {
						
						reg=0;
		            	cmd=0;
						ParamIndex = 0;
						memset(Param,0,20);
		          	} else {
		            	
		            	
		            	
						
						Msg("Apply Cmd %c %s Error %d\r\n",cmd,Param,res);
		            	
		            	
						
						
						reg=0;
		            	cmd=0;
						ParamIndex = 0;
						memset(Param,0,20);
		          	}
		        }
  
			} 
		} else i++;
	}
	if (i==0) {
		res = 8; 
	} else {
		if ((cmd != 0) && (ParamIndex > 0)) {
		    res = ApplyCmd(cmd,Param,b);
			if (res) Msg("Apply Cmd %s %s Error %d\r\n",cmd,Param,res);
				
		}
	}
	return res;
}


u8 TranslateLineToBlock(const char * CadrLine,TBlock * b,TBlock * prevb,u8 exe){

	u8 Res;
	u8 errindex;
	InitBlockByPrev(b,prevb);
  	Res = LineToBlock(CadrLine,&errindex,b);

	if (Res == 0) CalcBlockFrz(b,exe);
	return Res;


}





typedef struct tagTQExBlks{
	TBlock blks[10];
	s8 head; 
	s8 tail; 
			 
			 
	s8 count;
} TQExBlks;

volatile u8 qbLock = 0;

TQExBlks qb; 

void InitQExBlks(void){
	
	memset((u8*)&qb,0,sizeof qb);	
}

u8 qbCount(void){
 	return qb.count;
}

u8 qbIsPlace(void){
	
	if (qb.count < 10) return 1;
	else return 0;
}


u8 qbAddBlock(TBlock * b){
	
	
	
	if (qbIsPlace()) {
		memcpy((u8*)&(qb.blks[qb.tail]),(u8*)b,sizeof (*b));
		
		qb.tail++;
		qb.tail %= 10; 
		qb.count++;
		return 1;
	} else return 0; 
}

u8 qbExtrBlock(TBlock * b){
	
	
	
	if (qb.count > 0) {
		memcpy((u8*)b,(u8*)&(qb.blks[qb.head]),sizeof (*b));
		qb.head++;
		qb.head %= 10; 
		qb.count--;
		return 1;
	} else return 0; 
}

u8 qbFirstIndex(void){
	return qb.head;
}

void qbIncIndex(u8* Index){
	(*Index)++;
	(*Index) %= 10; 
}

u8 qbLastFreeIndex(void){
	return qb.tail;
}

TBlock * qbGetBlockIndex(u8 Index){
	return &(qb.blks[Index]);
}

u8 qbDelFirst(void){
	
	
	
	if (qb.count > 0) {
		qb.head++;
		qb.head %= 10; 
		qb.count--;
		return 1;
	} else return 0; 
}

TBlock * qbFirstBlock(void){
	
	
	if (qb.count > 0) {
		
		
		return &(qb.blks[qb.head]);
	} else return 0;
}

TBlock * qbLastBlock(void){
	u8 i;
	
	
	if (qb.count > 0) {
		
		
		i = qb.tail;
		i--;
		if (i==255) i = 10-1;
		return &(qb.blks[i]);
	} else return 0;
}

TBlock * qbSecondBlock(void){
	
	
	u8 tmph;
	if (qb.count > 1) {
		
		
		tmph = (qb.head + 1)%10;
		return &(qb.blks[tmph]);
	} else return 0;
}

TBlock * qbPrevPrgBlock(void){
	s8 tmpTail;
	
	
	if (qb.count > 0) {
		
		
		tmpTail = qb.tail - 1;
		if (tmpTail < 0) tmpTail += 10; 
		return &(qb.blks[tmpTail]);
	} else return 0;
} 

u8 CheckG1Only(TBlock * b){
	

	if 	(	(b->cFeed) ||
			(b->cSpindel) ||
			(b->cCold) ||
			(b->cPause) ||
			(b->cStop) 
		)
	{

		return 0;
	} else {
		
		if 	(
				(	(b->comX) ||
					(b->comY) ||
					(b->comZ)
				) && 
				(b->sGo == 1)
			) {


			return 1;	
		}
		else {

		 	return 0; 
		}
	}
}

u8 CheckG1FOnly(TBlock * b){

	if 	(	(b->cSpindel) ||
			(b->cCold) ||
			(b->cPause) ||
			(b->cStop) 
		)
	{

		return 0;
	} else {
		
		if 	(
				(	(b->comX) ||
					(b->comY) ||
					(b->comZ)
				) && 
				(b->sGo == 1)
			) {

			return 1;	
		}
		else {

			return 0; 
		}
	}
}

u8 CheckAngle(float x0,float y0,float z0,float x1,float y1,float z1,float x2,float y2,float z2) {
	
	float xv1,yv1,zv1,xv2,yv2,zv2,sm,m1,m2,a;












 	
	
	xv1 = x1 - x0;
	yv1 = y1 - y0;
	zv1 = z1 - z0;
	xv2 = x2 - x1;
	yv2 = y2 - y1;
	zv2 = z2 - z1;
	




	sm = xv1*xv2 + yv1*yv2 + zv1*zv2;
	m1 = sqrt(xv1*xv1+yv1*yv1+zv1*zv1);
	m2 = sqrt(xv2*xv2+yv2*yv2+zv2*zv2);
	
	
	if ((m1*m2)!=0) {
		a = acos(sm/(m1*m2))*180/(3.14159265358979323846264338327950288419716939937510582097494459230781640628620899);

		if (a < *pTrAngle) {

			return 1;
		} else {

			return 0;
		}
	} {

		return 0; 
	}
}




	char st[50];
	TBlock ctb; 

u8 CheckNextLine(float pX,float pY,float pZ,TBlock * b,TFileStream * strm){
	
	u8 errt; 
	u8 res; 
	s32 sPos; 



	memset((void*)&ctb,0,sizeof ctb);
	memset((void*)&st[0],0,50);

	bsFS_Pos(strm,&sPos); 
	res = bsFS_ReadLn(&ts,(u8*)st,50);
	
		
	

	if (res == 0) {
		

		errt=TranslateLineToBlock(st,&ctb,b,0);
		
		
		bsFS_Seek(strm,sPos);
		

		if (errt==0) {
			
			
			if (CheckG1Only(&ctb)) {
	 			if (CheckAngle(pX,pY,pZ,b->Xd,b->Yd,b->Zd,ctb.Xd,ctb.Yd,ctb.Zd)) {

					return 1; 
				}
				else {

					return 0;
				}
			} else {

				return 0; 
			}
		} else {

			return 0; 
		}

	} else {

	 	return 0; 
	}
}

TBlock rbs,rbc;
u8 SPS;


TBlock * ppb; 
TBlock tb; 
char s[50];
u8 EndTranslate = 0;

void TranslatePrgLine(const char * s){
	u8 errt; 
	u8 len;

	
	
	memset((void*)&tb,0,sizeof tb);
	if (qbIsPlace()) {
		
		
		if (strlen(s) > 0) {
			
			
			





			
			
			ppb = qbPrevPrgBlock(); 

			
			
			errt=TranslateLineToBlock(s,&tb,ppb,1);
			if (errt==0) {
				tb.NumLine = *pCurCadr; 
				len = strlen(s);
				memset((void*)&(tb.s[0]),0,50);
				memcpy((void*)&(tb.s[0]),(void*)&(s[0]),len);
				if (!tb.Nomove) {
					if (!qbAddBlock(&tb)) {
						Msg("Error Add Block To Prg Queue\r\n");
					}
				} else {
					



				}
				
			} 
			
			else Msg("Err Tr Line(%s). Ec %d\r\n",s,errt);
		} else {
			Msg("Error ReadNextPrgLine\r\n");
		}
	}
	

}

void TranslatePrg(void){
	u8 errt; 
	s8 res;
	float pX,pY,pZ;
	if (EndTranslate) return;
	
	
	memset((void*)&tb,0,sizeof tb);
	memset((void*)&(s[0]),0,50);
	if (qbIsPlace()) {
		
		
		res=bsFS_ReadLn(&ts,(u8*)s,50);
		if (res==0) {
			(*pNumReadLine)++;
			




			memcpy((void*)&(tb.s[0]),(void*)&(s[0]),50);
			
			
			ppb = qbPrevPrgBlock(); 





			
			
			errt=TranslateLineToBlock(s,&tb,ppb,1);
			if (errt==0) {
				tb.NumLine = *pNumReadLine;
				memcpy((void*)&tb.s,(void*)&(s[0]),50);
				FS_Pos(ts.f,&tb.PosSSP);
				
				
				if (ppb != 0) {
					

					if ((*ppb).Nonstop) {
						
						
						if (CheckG1Only(&tb)) {
							
							


							if (CheckNextLine((*ppb).Xd,(*ppb).Yd,(*ppb).Zd,&tb,&ts)) {
								tb.Nonstop = 1; 
								

							}

						} 
					} else {
						
						
						if (CheckG1FOnly(&tb)) {


							if (CheckNextLine((*ppb).Xd,(*ppb).Yd,(*ppb).Zd,&tb,&ts)) {
								tb.Nonstop = 1; 


							}

						} 
					}
				} else {
					
					

					if (CheckG1FOnly(&tb)) {
						XYZImpToXYZ(*(ms_X.Pos),*(ms_Y.Pos),*(ms_Z.Pos),&pX,&pY,&pZ);
						if (CheckNextLine(pX,pY,pZ,&tb,&ts)) {
							tb.Nonstop = 1; 


						}
					} 
				}
				
				if (!tb.Nomove) {
					if (!qbAddBlock(&tb)) {
						Msg("Error Add Block To Prg Queue\r\n");
					}



				} else {
					



				}
				
			} 
			
			else Msg("Error Traslate Line(%s). Ecode %d \r\n",s,errt);
		} else {
			Msg("Error ReadNextPrgLine %d\r\n",res);
			if (FS_Eof(ts.f)== -21) {
				EndTranslate = 1;
			}
		}
	}
	


}

void SearchStopPoint(void){
	u8 errt; 
	char s[50];
	float dS;

	if (SPS) {
		
		
		
		memset((void*)&rbc,0,sizeof rbc);
		memset((void*)&(s[0]),0,50);
		dS = 0;
		
		if (bsFS_ReadLn(&rs,(u8*)s,50)==0) {
			



			
			errt=TranslateLineToBlock(s,&rbc,&rbs,1);
			if (errt==0) {
				




					
					if (CheckG1Only(&rbc)) {
						
						
						if (CheckAngle(	rbs.Xs,rbs.Ys,rbs.Zs,
										rbc.Xs,rbc.Ys,rbc.Zs,
										rbc.Xd,rbc.Yd,rbc.Zd
										)
							) {
							
							
							
							
							dS = sqrt(sqr(rbc.Xd-rbc.Xs)+sqr(rbc.Yd-rbc.Ys)+sqr(rbc.Zd-rbc.Zs));
							
							Sr = Sr + dS; 



								memcpy(&rbs,&rbc,sizeof rbs);
							SPS = 1; 
						} else {
							
							



							SPS = 0; 
						}
					} else {
						
						



						SPS = 0;
					}
				}
				

			} else {
				



				SPS = 0;
			}
		} else {

			
			SPS = 0;	
		}

		


}

void CrushWaterHandlerFrz(void){
	Msg("Crush Water.\r\n");
	if (*pPrgRun) {
		fStopPrg = 1;	
	}
	FIStop();
	*pCrushWater = 1;
}

void sG0HandlerFrz(void){
    
	switch (sG0) {
		case 1:
			if ((!*(mc_X.MovePos))&&(!*(mc_Y.MovePos))&&(ms_X.Level==0)&&(ms_Y.Level==0)) {
				*(mc_Z.MovePos)=1;		
				sG0 = 2;

			}
			break;
		case 2:
			if ((!*(mc_Z.MovePos))&&(ms_Z.Level==0)) {
				sG0 = 0;
				Busy = 0;
			}
			break;
		case 3:
			if ((!*(mc_Z.MovePos))&&(ms_Z.Level==0)) {
				*(mc_X.MovePos)=1;
				*(mc_Y.MovePos)=1;
				sG0 = 4;

			}
			break;
		case 4:
			if ((!*(mc_X.MovePos))&&(!*(mc_Y.MovePos))&&(ms_X.Level==0)&&(ms_Y.Level==0)) {
				sG0 = 0;
				Busy = 0;
			}
			break;			
	}
}


TBlock * eb = 0;
TBlock * nb;


void RunNextCadrFrzMain(void){





	if (sG0 != 0) { 
		
		sG0HandlerFrz();
		return;
	}
	if (Busy) {
		
		return;
	}
	
	switch (*pRCS) {
		
		case 0:
			eb = qbFirstBlock();
			if (eb!=0) {
				
				
				
				if (((*eb).sGo ==1)) {
					if ((*eb).Nonstop == 0) {
						
						Sr = sqrt(sqr((*eb).Xd-(*eb).Xs)+sqr((*eb).Yd-(*eb).Ys)+sqr((*eb).Zd-(*eb).Zs));



						SPS = 0;
					} else {
						
						Sr = sqrt(sqr((*eb).Xd-(*eb).Xs)+sqr((*eb).Yd-(*eb).Ys)+sqr((*eb).Zd-(*eb).Zs));
						
						nb = qbSecondBlock();
						if (nb == 0) {
							



							SPS = 0;
						} else {
							
							
							Sr = Sr + sqrt(sqr((*nb).Xd-(*nb).Xs)+sqr((*nb).Yd-(*nb).Ys)+sqr((*nb).Zd-(*nb).Zs));
							
							
							
							if ((*nb).Nonstop) {
								
								memcpy(&rbs,nb,sizeof rbs);
								
								rs.Pos = (*nb).PosSSP;
								rs.f = ts.f;



								SPS=1;
							} else {
								SPS = 0;
							}
						}
					}
				}






				(*pCurCadr) = (*eb).NumLine;


				memcpy((void*)&(((LPC_RTC_TypeDef *) ((0x40000000UL) + 0x24000) )->GPREG4),(void*)pCurCadr,4);
				SetFeed(eb);  
				SetSpindle(eb);	 
				SetCold(eb);	 
				SetPause(eb);
				*pRCS = 11; 
				
			} else {
				
				Msg("Queue is Empty\r\n");
				*pRCS = 2; 
			}
		break;
		case 11:
			
			if (EndPause()) {
				*pRCS = 12; 
				
			}
		break;

		case 12:
			SetGoFrz(eb);
			*pRCS = 13; 
		break;
		case 13:
			if (EndGo()) {





















				
				*pRCS = 14; 
			}
		break;

		case 14:
			SetStop(eb);
			*pRCS = 15; 
		break;
		case 15:
			if (EndStop()) {
				*pRCS = 16; 
			}
		break;
		
		case 16:
			
			
		    if ((*eb).cStop==1) {
				(*eb).cStop=0;
				if ((*eb).sStop == 2) {
		 			*pRCS = 2; 
					break;
				}
			}
			eb = 0;
			qbDelFirst();
 			*pRCS = 0; 
		break;
		
		case 2:
			Msg("EndPrg");
			eb = 0;
			*pPrgRun = 0;
			((LPC_RTC_TypeDef *) ((0x40000000UL) + 0x24000) )->ALSEC = *pPrgRun;
			*pCurCadr = 0; 
			memcpy((void*)&(((LPC_RTC_TypeDef *) ((0x40000000UL) + 0x24000) )->GPREG4),(void*)pCurCadr,4);
			*pRCS = 0; 
			FS_Close(pPrgFileHandle);
			*pPrgFileHandle = -1;
			EndTranslate = 0;
		break;
	}
}


