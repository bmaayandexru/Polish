#include "Defs.h"
#include "ti.h"
#include "Timers.h"

// для пинов
//#include "VirtualPins.h"

#define ticount 30

volatile u32 	ti[ticount];
volatile u32 	time[ticount];	

TIMER_CONTROL_STRUCT tcs_TI;

void TI_Handler(void){
	u32 i;
	for (i=0;i<ticount;i++){
		if (ti[i]>1) ti[i]--;
		if (time[i]>0) time[i]++;
	}
}
