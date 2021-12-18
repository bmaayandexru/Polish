#ifndef __MOTORS_H__
#define __MOTORS_H__

#include "Defs.h"
#include "regs.h"
#include "Timers.h"


//25000000*25000000
#define	Kb	((u64)625000000000000)
#define K1	((u64)25000000)

#define pi (3.14159265358979323846264338327950288419716939937510582097494459230781640628620899) 
// структура состояния двигателя
typedef struct tagMState {
	u8		Level;			//1// текуший уровень сигнала Step						
	s8		*Dir;			//*r//1// текущее направление 1 - прямое (-1) - обратное 	
   	s32		*Pos;			//*r//4// позиция в импульсах								
   	s32		Lacc;			//4// шагов разгона									
	u64		*FrCur;			//*r//8// частота текущая (Гц)							
	u64		Tcur;			//*r//4// период текущий = Kb / FrCur					
	u64 	LPON;			//4// длина активного импульса (c * k1)				
	u64		LPOFF;			//4// длина пассивного импульса (c * k1)				
	u8		*Posit;			//*r//1// позиционирование выполнено
	u8		*StagePos;		//*r//1// стадия позиционирования
							// 0 - движение к датчику
							// 1 - торможение в датчике и смена направления
							// 2 - выход из датчика на малой скорости и остановка
} TFMS;						// 32

//структура управления двигателем
typedef struct tagFMControl {
	u64		*FrMin;				//8// частота минимальная (Гц*k1)							  8
	u64		*FrReq; 			//8// частота требуемая (Гц*k1)							  8
	u64		*FrMax; 			//8// частота максимальная (Гц*k1)							  8
	s32		*ReqPos;			//4// требуемая позиция									  4 / 32
	u32		*LenOnPulse;	//4// длина активного импульса (в 1/k1 секундных интервалах) 2
  u32 	*Accel; 			//4// ускорение (Гц/с)										  2
	s8	 	*ReqDir;			//1// требуемое направление 1 - прямое направление (-1)-обратное направление	 1	  8
	u8		*MoveBtn;			//1// разрешение движения
	u8		*MovePos;			//1// включение выхода на позицию
	u8		*PositOn;			//1// включение позиционирования
} TFMC;								//40

typedef struct tagFMoveStatus {
	u32		LPON;			//4	 // длина активного импульса
	u32		LPOFF;			//4	 // длина пассивного импульса
	u8		Level;			//1// уровень сигнала по X и(или) Y и(или) Z
	float 	*Vc;			// текущая скорость
} TFMVS;  	// Frezer MoVe Status (состояние перемещения в декартовой СК) //88

typedef __packed struct tagFMoveControl {
	u32		*LenOnPulse;// длина активного импульса (в 1/k1 секундных интервалах) 2
	float	*V;					// скорость подачи в мм/с
	float	*Vmin;			//	скорость минимальная
	float *Vaccel;		// 	ускорение
	float *Vmul;			// 	множитель
	float	Vmax;				// максимальная скорость = V * Vmul
	u8		Enable;			// разрешение движения
} TFMVC;  	// Frezer MoVe Conrtrol (управление перемещением в декартовой СК)


extern TIMER_CONTROL_STRUCT tcs_FMove;

//extern TMC 	/*mc_X,*/mc_Y,mc_Z;
//extern TMS 	/*ms_X,*/ms_Y,ms_Z;
extern TFMVC 	fmvc; 	
extern TFMVS 	fmvs;	
//extern u32 *pDirDelay;

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
extern u8 *pfZcomp;// = 0;
extern u8 fStartMoveZLowSpeed;// = 0;
extern float *pA,*pB,*pC,*pD;// коэффициенты компенсации
extern u8 ClrF; 


void 	ShowMC(TFMC * mc);
void 	ShowMS(TFMS * ms);

void	AddPointFrz(void);
void	StartMoveZLowSpeed(void);
void	StartMoveHorizontalLowSpeed(void);
void	StopMoveHorizontalLowSpeed(void);

void InitMotorStructF(volatile TFMS* ms,volatile  TFMC* mc );
void InitMotorStructALF(volatile TFMS* ms,volatile TFMC* mc );
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
void RecoveryHorizfreq(void);

void UpZ(void);
void BackHorizontal(void);

void	HTCorr(void);
void RetrySendPoint(void);
void SendAddPointPackFrz(s32 * pIndex,float * px, float * py, float * pz);
void FixPointPackFrz(s32 * pIndex,float * px, float * py, float * pz);


void InitZcompMoveXY(float Z);
void ZcompMoveXY(void);

#endif

