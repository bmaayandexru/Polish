#ifndef __RWM_H__
#define __PWM_H__
void PWM_Init( uint32_t cycle );
void PWM_Start(void);
void PWM_Stop(void);
void PWM_Set( uint32_t offset );
#endif
