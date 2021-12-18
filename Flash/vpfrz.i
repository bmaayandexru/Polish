#line 1 "Main\\VPFrz.c"
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










#line 2 "Main\\VPFrz.c"



#line 1 ".\\UCNC\\VirtualPins.h"



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


#line 6 "Main\\VPFrz.c"
#line 1 "Main\\VPFrz.h"



#line 5 "Main\\VPFrz.h"



#line 9 "Main\\VPFrz.h"


#line 23 "Main\\VPFrz.h"








#line 38 "Main\\VPFrz.h"














extern TaVPIN vPinsdef;





#line 7 "Main\\VPFrz.c"



TaVPIN vPinsdef = {

	{0,	1,		0},	
	{1,	1,		0}, 
	{2,	1,		0}, 
	{3,	1,		0}, 
	{4,	1,		0}, 
	{5,	1,		0}, 
	{6,	1,		0}, 
	{7,	0,		0},	
	{8,	1,		0},	
	{9,	1,		0},	
	{10,	0,		0},	
	{11,	1,		0},	
	{12,	1,		0},	
	{13,	0,		0},	
	{14,	0,		0},	
	{15,	1,		0},	
	{16,	1,		0},
	{17,	1,		0},
	{18,	1,		0},
	{19,	1,		0},

	{20,	1,		0},	 
	{21,	1,		0},	 
	{22,	1,		0},	 
	{23,	1,		0},	 
	{24,	1,		0},	 
	{25,	1,		0},  
	{26,	1,		0},
	{27,	1,		0},
	{28,	1,		0},		 
	{29,	1,		0},	 
	{30,	1,		0},	 
	{31,	1,		0},	 
	{32,	1,		0},	 
	{33,	1,		0},	 
	{34,	1,		0},	 
	{35,	1,		0}	 

	};



