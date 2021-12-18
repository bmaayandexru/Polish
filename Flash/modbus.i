#line 1 "Main\\Modbus.c"

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



 

#line 3 "Main\\Modbus.c"
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










#line 4 "Main\\Modbus.c"
#line 1 "Main\\Modbus.h"



#line 5 "Main\\Modbus.h"










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

#line 5 "Main\\Modbus.c"
#line 1 ".\\UCNC\\ti.h"
#line 4 ".\\UCNC\\ti.h"
#line 1 ".\\UCNC\\Timers.h"



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

#line 6 "Main\\Modbus.c"
#line 1 ".\\UCNC\\UART.h"
#line 4 ".\\UCNC\\UART.h"
#line 1 ".\\Drivers\\include\\lpc17xx_uart.h"


 





















 

 



 




 
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



 

#line 38 ".\\Drivers\\include\\lpc17xx_uart.h"
#line 1 ".\\Drivers\\include\\lpc_types.h"


 























 

 



 




 
#line 40 ".\\Drivers\\include\\lpc_types.h"


 


 



 




 
typedef enum {RESET = 0, SET = !RESET} FlagStatus, IntStatus, SetState;




 
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;




 
typedef enum {ERROR = 0, SUCCESS = !ERROR} Status;




 
typedef enum
{
	NONE_BLOCKING = 0,		 
	BLOCKING				 
} TRANSFER_BLOCK_Type;


 
typedef void (*PFV)();

 
typedef int32_t(*PFI)();



 


 


 




 

 





 

 














 

 


 




 


 

 







 


 


 

 
typedef char CHAR;

 
typedef uint8_t UNS_8;

 
typedef int8_t INT_8;

 
typedef	uint16_t UNS_16;

 
typedef	int16_t INT_16;

 
typedef	uint32_t UNS_32;

 
typedef	int32_t INT_32;

 
typedef int64_t INT_64;

 
typedef uint64_t UNS_64;

 


 


 




 






 

 
#line 39 ".\\Drivers\\include\\lpc17xx_uart.h"







 


 



 




 

 


 

 



 
 

 


 

 


 

 



 

 



 

 
#line 104 ".\\Drivers\\include\\lpc17xx_uart.h"

 

 
#line 119 ".\\Drivers\\include\\lpc17xx_uart.h"

 

 
#line 133 ".\\Drivers\\include\\lpc17xx_uart.h"

 

 
#line 150 ".\\Drivers\\include\\lpc17xx_uart.h"

 

 
#line 160 ".\\Drivers\\include\\lpc17xx_uart.h"

 

 
#line 173 ".\\Drivers\\include\\lpc17xx_uart.h"

 

 
#line 186 ".\\Drivers\\include\\lpc17xx_uart.h"

 

 


 

 
#line 201 ".\\Drivers\\include\\lpc17xx_uart.h"

 

 






 

 




 

 



 

 
#line 238 ".\\Drivers\\include\\lpc17xx_uart.h"

 

 


 

 
 


 

 





 

 



 


 




 




 




 


 


 



 





 


 


 



 


 
#line 318 ".\\Drivers\\include\\lpc17xx_uart.h"

 


 




 


 


 



 
typedef enum {
	UART_DATABIT_5		= 0,     		 
	UART_DATABIT_6,		     			 
	UART_DATABIT_7,		     			 
	UART_DATABIT_8		     			 
} UART_DATABIT_Type;



 
typedef enum {
	UART_STOPBIT_1		= (0),   					 
	UART_STOPBIT_2		 							 
} UART_STOPBIT_Type;



 
typedef enum {
	UART_PARITY_NONE 	= 0,					 
	UART_PARITY_ODD,	 						 
	UART_PARITY_EVEN, 							 
	UART_PARITY_SP_1, 							 
	UART_PARITY_SP_0 							 
} UART_PARITY_Type;



 
typedef enum {
	UART_FIFO_TRGLEV0 = 0,	 
	UART_FIFO_TRGLEV1, 		 
	UART_FIFO_TRGLEV2,		 
	UART_FIFO_TRGLEV3		 
} UART_FITO_LEVEL_Type;

 

 
typedef enum {
	UART_INTCFG_RBR = 0,	 
	UART_INTCFG_THRE,		 
	UART_INTCFG_RLS,		 
	UART1_INTCFG_MS,		 
	UART1_INTCFG_CTS,		 
	UART_INTCFG_ABEO,		 
	UART_INTCFG_ABTO		 
} UART_INT_Type;



 
typedef enum {
	UART_LINESTAT_RDR	= ((uint8_t)(1<<0)),			 
	UART_LINESTAT_OE	= ((uint8_t)(1<<1)),			 
	UART_LINESTAT_PE	= ((uint8_t)(1<<2)),			 
	UART_LINESTAT_FE	= ((uint8_t)(1<<3)),			 
	UART_LINESTAT_BI	= ((uint8_t)(1<<4)),			 
	UART_LINESTAT_THRE	= ((uint8_t)(1<<5)),		 
	UART_LINESTAT_TEMT	= ((uint8_t)(1<<6)),		 
	UART_LINESTAT_RXFE	= ((uint8_t)(1<<7))			 
} UART_LS_Type;



 
typedef enum {
	UART_AUTOBAUD_MODE0				= 0,			 
	UART_AUTOBAUD_MODE1							 
} UART_AB_MODE_Type;



 
typedef struct {
	UART_AB_MODE_Type	ABMode;			 
	FunctionalState		AutoRestart;	 
} UART_AB_CFG_Type;



 
typedef enum {
	UART_AUTOBAUD_INTSTAT_ABEO		= ((uint32_t)(1<<8)),		 
	UART_AUTOBAUD_INTSTAT_ABTO		= ((uint32_t)(1<<9))			 
}UART_ABEO_Type;



 
typedef enum {
	UART_IrDA_PULSEDIV2		= 0,		
 
	UART_IrDA_PULSEDIV4,				
 
	UART_IrDA_PULSEDIV8,				
 
	UART_IrDA_PULSEDIV16,				
 
	UART_IrDA_PULSEDIV32,				
 
	UART_IrDA_PULSEDIV64,				
 
	UART_IrDA_PULSEDIV128,				
 
	UART_IrDA_PULSEDIV256				
 
} UART_IrDA_PULSE_Type;

 

 
typedef enum {
	INACTIVE = 0,			 
	ACTIVE = !INACTIVE 		 
}UART1_SignalState;



 
typedef enum {
	UART1_MODEM_STAT_DELTA_CTS	= ((uint8_t)(1<<0)),		 
	UART1_MODEM_STAT_DELTA_DSR	= ((uint8_t)(1<<1)),		 
	UART1_MODEM_STAT_LO2HI_RI	= ((uint8_t)(1<<2)),		 
	UART1_MODEM_STAT_DELTA_DCD	= ((uint8_t)(1<<3)),		 
	UART1_MODEM_STAT_CTS		= ((uint8_t)(1<<4)),			 
	UART1_MODEM_STAT_DSR		= ((uint8_t)(1<<5)),			 
	UART1_MODEM_STAT_RI			= ((uint8_t)(1<<6)),				 
	UART1_MODEM_STAT_DCD		= ((uint8_t)(1<<7))				 
} UART_MODEM_STAT_type;



 
typedef enum {
	UART1_MODEM_PIN_DTR			= 0,		 
	UART1_MODEM_PIN_RTS						 
} UART_MODEM_PIN_Type;



 
typedef enum {
	UART1_MODEM_MODE_LOOPBACK	= 0,		 
	UART1_MODEM_MODE_AUTO_RTS,				 
	UART1_MODEM_MODE_AUTO_CTS 				 
} UART_MODEM_MODE_Type;



 
typedef enum {
	UART1_RS485_DIRCTRL_RTS = 0,	 
	UART1_RS485_DIRCTRL_DTR			 
} UART_RS485_DIRCTRL_PIN_Type;

 

 
typedef struct {
  uint32_t Baud_rate;   		 
  UART_PARITY_Type Parity;    	





 
  UART_DATABIT_Type Databits;   




 
  UART_STOPBIT_Type Stopbits;   


 
} UART_CFG_Type;

 

 

typedef struct {
	FunctionalState FIFO_ResetRxBuf;	


 
	FunctionalState FIFO_ResetTxBuf;	


 
	FunctionalState FIFO_DMAMode;		


 
	UART_FITO_LEVEL_Type FIFO_Level;	




 
} UART_FIFO_CFG_Type;

 

 
typedef struct {
	FunctionalState NormalMultiDropMode_State; 

 
	FunctionalState Rx_State;					

 
	FunctionalState AutoAddrDetect_State;		

 
	FunctionalState AutoDirCtrl_State;			

 
	UART_RS485_DIRCTRL_PIN_Type DirCtrlPin;		



 
	 SetState DirCtrlPol_Level;					




 
	uint8_t MatchAddrValue;					 
	uint8_t DelayValue;						 
} UART1_RS485_CTRLCFG_Type;



 


 


 
 
void UART_Init(LPC_UART_TypeDef *UARTx, UART_CFG_Type *UART_ConfigStruct);
void UART_DeInit(LPC_UART_TypeDef* UARTx);
void UART_ConfigStructInit(UART_CFG_Type *UART_InitStruct);

 
void UART_SendByte(LPC_UART_TypeDef* UARTx, uint8_t Data);
uint8_t UART_ReceiveByte(LPC_UART_TypeDef* UARTx);
uint32_t UART_Send(LPC_UART_TypeDef *UARTx, uint8_t *txbuf,
		uint32_t buflen, TRANSFER_BLOCK_Type flag);
uint32_t UART_Receive(LPC_UART_TypeDef *UARTx, uint8_t *rxbuf, 		uint32_t buflen, TRANSFER_BLOCK_Type flag);


 
void UART_FIFOConfig(LPC_UART_TypeDef *UARTx, UART_FIFO_CFG_Type *FIFOCfg);
void UART_FIFOConfigStructInit(UART_FIFO_CFG_Type *UART_FIFOInitStruct);

 
uint32_t UART_GetIntId(LPC_UART_TypeDef* UARTx);
uint8_t UART_GetLineStatus(LPC_UART_TypeDef* UARTx);

 
void UART_IntConfig(LPC_UART_TypeDef *UARTx, UART_INT_Type UARTIntCfg, 				FunctionalState NewState);

void UART_TxCmd(LPC_UART_TypeDef *UARTx, FunctionalState NewState);
FlagStatus UART_CheckBusy(LPC_UART_TypeDef *UARTx);
void UART_ForceBreak(LPC_UART_TypeDef* UARTx);

 
void UART_ABClearIntPending(LPC_UART_TypeDef *UARTx, UART_ABEO_Type ABIntType);
void UART_ABCmd(LPC_UART_TypeDef *UARTx, UART_AB_CFG_Type *ABConfigStruct, 				FunctionalState NewState);


 
void UART_FullModemForcePinState(LPC_UART1_TypeDef *UARTx, UART_MODEM_PIN_Type Pin, 							UART1_SignalState NewState);

void UART_FullModemConfigMode(LPC_UART1_TypeDef *UARTx, UART_MODEM_MODE_Type Mode, 							FunctionalState NewState);

uint8_t UART_FullModemGetStatus(LPC_UART1_TypeDef *UARTx);

 
void UART_RS485Config(LPC_UART1_TypeDef *UARTx, 		UART1_RS485_CTRLCFG_Type *RS485ConfigStruct);

void UART_RS485ReceiverCmd(LPC_UART1_TypeDef *UARTx, FunctionalState NewState);
void UART_RS485SendSlvAddr(LPC_UART1_TypeDef *UARTx, uint8_t SlvAddr);
uint32_t UART_RS485SendData(LPC_UART1_TypeDef *UARTx, uint8_t *pData, uint32_t size);

 
void UART_IrDAInvtInputCmd(LPC_UART_TypeDef* UARTx, FunctionalState NewState);
void UART_IrDACmd(LPC_UART_TypeDef* UARTx, FunctionalState NewState);
void UART_IrDAPulseDivConfig(LPC_UART_TypeDef *UARTx, UART_IrDA_PULSE_Type PulseDiv);


 











 

 
#line 5 ".\\UCNC\\UART.h"

typedef enum {FULL_DUPLEX = (0), HALF_DUPLEX} UART_DUPLEX_Type;

BOOL UARTx_Init(u8 num, 
				UART_DUPLEX_Type dup,
				u32 baud_rate,
 				UART_PARITY_Type par,
				UART_DATABIT_Type dbits,
				UART_STOPBIT_Type Stopbits);

u16 UARTx_PlaceForSend(u8 num);


u16 UARTx_SendBuffer(u8 num,u8 * buffer,u16 buflen);






u16 UARTx_ReadyRecvData(u8 num);


u16 UARTx_RecvBuffer(u8 num,u8 * buffer,u16 buflen);









void BusyUartLine(void);


void FreeUartLine(void);


void InitHalfDupControlSignal(void);


void InitHalfDupWaitInterval(u32 baud_rate);


 
void StartDelay(void);


void WaitAndFreeUartLine(void);


void InitFullDupControlSignal(void);



#line 7 "Main\\Modbus.c"
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


#line 8 "Main\\Modbus.c"
#line 1 "Main\\regs.h"



#line 5 "Main\\regs.h"
#line 6 "Main\\regs.h"
#line 7 "Main\\regs.h"
#line 1 "Main\\motors.h"



#line 5 "Main\\motors.h"
#line 1 "Main\\regs.h"
#line 344 "Main\\regs.h"


#line 6 "Main\\motors.h"
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




#line 9 "Main\\Modbus.c"
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

#line 10 "Main\\Modbus.c"


u8 mbRBuffer0[512];
u8 mbRBuffer1[256];


u16 mbRDataLen0 = 0;
u16 mbRDataLen1 = 0;


u8 mbSBuffer0[256];
u8 mbSBuffer1[256];

u8 mbSFBuf0[256];
u8 mbSFBuf1[256];

volatile u8 WaitFlag = 0;


u16 mbSDataLen0 = 0;
u16 mbSDataLen1 = 0;

u16 mbSFDLen0 = 0;
u16 mbSFDLen1 = 0;


TPackHandler pPackHandler0 = 0;
TPackHandler pPackHandler1 = 0;


u16 mbDelay0 = 305;


u16 mbDelay1 = 3646;

u16 CRC16 (const u8 *nData, u16 wLength);




void mbSetSpeed(u8 num,u32 sp){
	if (num == 0){
		mbDelay0 = (3.5*1000000/(sp/10));
	} else
	if (num == 1){
		mbDelay1 = (3.5*1000000/(sp/10));

	}
}

void mbSetHandler(u8 num,TPackHandler ph){
	if (num == 0){
		pPackHandler0 = ph;
	} else
	if (num == 1){
		pPackHandler1 = ph;
	}
}

u16 swap (u16 w){
	return ((w << 8) | (w >> 8));
}

BOOL mbCheckSum(u8 * buffer,u16 len){
	u16 rCRC;

	if (len < 4) return 0;
	else {
		memcpy((u8*)&rCRC,buffer+len-2,2);
		
		return (rCRC == CRC16(buffer,len-2));
	}
}

void mbRecvBuffer(u8 num, u8 * buffer,u16 len){
	if (num == 0) {
		memcpy(mbRBuffer0+mbRDataLen0,buffer,len);
		mbRDataLen0+=len;
		
		time[0] = 1;
	} else {
		memcpy(mbRBuffer1+mbRDataLen1,buffer,len);
		mbRDataLen1+=len;
		time[1] = 1;
	}
}

void mbIdle(u8 num) {

	if (num == 0) {
		if ((time[0]==0 ? 0:time[0]-1) > ((mbDelay0)/(2500/25))) {
			
			
			
			if (mbCheckSum(mbRBuffer0,mbRDataLen0)) {
				
				
				
				if (pPackHandler0) {
					(*pPackHandler0)(mbRBuffer0,mbRDataLen0);
				}
			}
			
			memset(mbRBuffer0,0,sizeof mbRBuffer0);
			mbRDataLen0 = 0;
			time[0] = 0;
		}
	} else {
		if ((time[1]==0 ? 0:time[1]-1) > ((mbDelay1)/(2500/25))) {
			
			if (mbCheckSum(mbRBuffer1,mbRDataLen1)) {

				
				
				if (pPackHandler1) {
					(*pPackHandler1)(mbRBuffer1,mbRDataLen1);
				}
			} else {
				
				if (*pErrCSU1) {
					Msg("Err CS U1 ");
					Dump(mbRBuffer1,mbRDataLen1);
					Msg("\r\n");
				}
			}
			
			memset(mbRBuffer1,0,sizeof mbRBuffer1);
			mbRDataLen1 = 0;
			time[1] = 0;
		}
	}
}

void mbByteToPack(u8 num,u8 b){
	if (num == 0) {
		*(mbSFBuf0+mbSFDLen0)=b;
		mbSFDLen0++;
	} else 
	if (num == 1) {
		*(mbSFBuf1+mbSFDLen1)=b;
		mbSFDLen1++;
	}
}

void mbWordToPack(u8 num,u16 w){
	u16 tmpw;
	if (num == 0) {
		tmpw = swap(w);
		memcpy(mbSFBuf0+mbSFDLen0,&tmpw,2);
		mbSFDLen0 += 2;
	} else 
	if (num == 1) {
		tmpw = swap(w);
		memcpy(mbSFBuf1+mbSFDLen1,&tmpw,2);
		mbSFDLen1 += 2;
	}
}

void mbWordToPackNoSwap(u8 num,u16 w){
	u16 tmpw;
	if (num == 0) {
		tmpw = w;
		memcpy(mbSFBuf0+mbSFDLen0,&tmpw,2);
		mbSFDLen0 += 2;
	} else 
	if (num == 1) {
		tmpw = w;
		memcpy(mbSFBuf1+mbSFDLen1,&tmpw,2);
		mbSFDLen1 += 2;
	}
}

void mbBufferToPack (u8 num,u8 * buffer,u16 len){
	if (num == 0) {
		memcpy(mbSFBuf0+mbSFDLen0,buffer,len);
		mbSFDLen0 += len;
	} else 
	if (num == 1) {
		memcpy(mbSFBuf1+mbSFDLen1,buffer,len);
		mbSFDLen1 += len;
	}
}

void mbCmd485(u8 devaddr,u8 cmd,u16 regaddr,u16 count){
	mbByteToPack(1,devaddr);
	mbByteToPack(1,cmd);
	mbWordToPack(1,regaddr);
	mbWordToPack(1,count);
	mbPackToQueue(0);
}

void mbInsCmd485(u8 devaddr,u8 cmd,u16 regaddr,u16 count,u8 ofs){
	mbByteToPack(1,devaddr);
	mbByteToPack(1,cmd);
	mbWordToPack(1,regaddr);
	mbWordToPack(1,count);
	mbInsPackToQueue(0,ofs);
}

void mbSendPack(u8 num){
	u16 tmpw;
	if (num == 0) {
		tmpw = CRC16(mbSFBuf0,mbSFDLen0);
		mbWordToPackNoSwap(0,tmpw);
		memcpy(mbSBuffer0,mbSFBuf0,mbSFDLen0);
		mbSDataLen0 = mbSFDLen0;
		UARTx_SendBuffer(0,mbSBuffer0,mbSDataLen0);
		mbSDataLen0 = 0;
		mbSFDLen0 = 0;
	} else
	if (num == 1) {
		tmpw = CRC16(mbSFBuf1,mbSFDLen1);
		mbWordToPackNoSwap(1,tmpw);
		memcpy(mbSBuffer1,mbSFBuf1,mbSFDLen1);
		mbSDataLen1 = mbSFDLen1;
		UARTx_SendBuffer(1,mbSBuffer1,mbSDataLen1);
		



		mbSDataLen1 = 0;
		mbSFDLen1 = 0;
	} 
}

void mbPackToQueue(u8 transit){
	quAddPack(mbSFBuf1,mbSFDLen1,transit);
	mbSFDLen1 = 0;
}

void mbInsPackToQueue(u8 transit,u8 ofs){
	quInsPack(mbSFBuf1,mbSFDLen1,transit,ofs);
	mbSFDLen1 = 0;
}

u16 CRC16 (const u8 *nData, u16 wLength)
{
static const u16 wCRCTable[] = {
0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };

u8 nTemp;
u16 wCRCWord = 0xFFFF;

   while (wLength--)
   {
      nTemp = *nData++ ^ wCRCWord;
      wCRCWord >>= 8;
      wCRCWord ^= wCRCTable[nTemp];
   }
   return wCRCWord;
}

