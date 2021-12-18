#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Defs.h"
#include "Tools.h"
#include "Motors.h"
#include "VirtualPins.h"
#include "u0packets.h"
#include "msg.h"
#include "Handlers.h"
#include "ti.h"

#include "VPFrz.h"
#include "Motor_X.h"
#include "Motor_Y.h"
#include "Motor_Z.h"

#include "FreqInvr.h"

TIMER_CONTROL_STRUCT tcs_FMove;		// структура управления таймером движения по прямой

TFMVC 	fmvc; 	
TFMVS 	fmvs;	
//
//u32 *pDirDelay;
// координаты 3-х точек для построения плоскости компенсации
float *pX1;
float *pY1;
float *pZ1;
float *pX2;
float *pY2;
float *pZ2;
float *pX3;
float *pY3;
float *pZ3;
u8 *pfZcomp;// = 0;

//float A,B,C,D;// коэффициенты компенсации
float *pA,*pB,*pC,*pD;// коэффициенты компенсации
// вычисляются в InitZComp()
float dz;
s32 SaveZPos,SaveXPos,SaveYPos;

float ZComp(float x, float y, float z){
	float Zo;
	if (*pfZcomp) {
		if (*pC) {
/*		
			dX = *dXPos * *pX_PG_MM / *pX_SPR;
			dY = *dYPos * *pY_PG_MM / *pY_SPR;
			dZ = *dZPos * *pZ_PG_MM / *pZ_SPR;
			// x+dX y+dY - абсолютные координаты точки G-кода
			Za_pl = ((*pD)-(*pA)*(x+dX)-(*pB)*(y+dY))/(*pC);
			// Za_pl - координата Z на плоскости коррекции
			Zo = (z-dZ+Za_pl);
			// Zo - относительная скоррретированная координата Z для точки (x,y,z)
*/			
			// ПОЧЕМУ СВЯЗЬ ЧЕРЕЗ ПЕРВУЮ ТОЧКУ???!!!!!!!!!!
			// так будет работать через любую точку поверхности
			// и чтобы не вычислять dX, dY, dZ 
			// используем уже вычисленные значения *pX1 *pY1 *pZ1
			// которые точно лежат на плоскости коррекции
			dz = ((*pD)-(*pA)*(x+*pX1)-(*pB)*(y+*pY1))/(*pC);
			Zo = (z-*pZ1+dz);
			return Zo;
		}
		// С == 0 
		else {
			dz = 0;
			return (z);
		}
	} 
	// компенсация не возможна
	else {
			dz = 0;
			return (z);
	}
}

void InitZComp(){
	float dx21,dx31,dy21,dy31,dz21,dz31,k,b;
	float tmpX,tmpY,tmpZ;
//	s32 xi,yi,zi;

	// настройка нуля
	//*dXPos=0; *dYPos=0; *dZPos=0;
	// сброс коэффициентов плоскости
	*pA=0; *pB=0; *pC=0; *pD=0;
//	XYZToXYZImp(*pX1,*pY1,*pZ1,&xi,&yi,&zi);
//	Msg("SZ x %d y %d z %d xi %d yi %d zi %d\r\n",OUTF1(*pX1),OUTF1(*pY1),OUTF1(*pZ1),xi,yi,zi);
//	*dXPos=xi; *dYPos=yi; *dZPos=zi;
	// инициализация компенсации
	if (((*pX1 == *pX2)&&(*pY1 == *pY2))||
	 	((*pX3 == *pX2)&&(*pY3 == *pY2))||
	 	((*pX3 == *pX1)&&(*pY3 == *pY1))
		)
	{
		// две точки точно совпадают
		// компенсация не возможна
		Msg("Err Zcomp. Points is EQU.\r\n");
		*pfZcomp = 0;
		 dz = 0;
	} else {
		// точки не совпадают
		// проверяем не лежат ли они на 1 прямой
		if ((*pX1==*pX2) && (*pX1==*pX3) && (*pX1==*pX2)) {
			// точки на вертикальной прямой
			Msg("Err Zcomp. Points by Line.\r\n");
			*pfZcomp = 0;
			dz = 0;
		} else {
			if ((*pY1==*pY2) && (*pY1==*pY3) && (*pY1==*pY2)) {
				// точки на горизонтальной прямой
				Msg("Err Zcomp. Points by Line.\r\n");
				*pfZcomp = 0;
    		 dz = 0;
			} else {
				if ((*pX1==*pX2)&&(*pX3!=*pX2)) {
					//решаем через пару pX3 pX2
					k = (*pY3 - *pY2)/(*pX3-*pX2);
					b = *pY3-k**pX3;
					if (*pY1 == (k**pX1+b)) {
						// точки на одной прямой
						Msg("Init Err Zcomp. Points by Line.\r\n");
						*pfZcomp = 0;
						dz = 0;
					} else {
						*pfZcomp = 1;
					}
				} else {
					//решаем через пару pX1 pX2
					k = (*pY2 - *pY1)/(*pX2-*pX1);
					b = *pY2-k**pX2;
					if (*pY3 == (k**pX3+b)) {
						// точки на одной прямой
						Msg("Init Err Zcomp. Points by Line.\r\n");
						*pfZcomp = 0;
						dz = 0;
					} else {
						*pfZcomp = 1;
					}
				}
				//
				if (!*pfZcomp) 
					// точки на одной прямой
					return;
				else {
					// точки не на одной прямой
//					Msg("x1 %d y1 %d z1 %d \r\n",OUTF1(*pX1),OUTF1(*pY1),OUTF1(*pZ1));
//					Msg("x2 %d y2 %d z2 %d \r\n",OUTF1(*pX2),OUTF1(*pY2),OUTF1(*pZ2));
//					Msg("x3 %d y3 %d z3 %d \r\n",OUTF1(*pX3),OUTF1(*pY3),OUTF1(*pZ3));
					dx21=*pX2-*pX1;
					dy21=*pY2-*pY1;
					dz21=*pZ2-*pZ1;
					dx31=*pX3-*pX1;
					dy31=*pY3-*pY1;
					dz31=*pZ3-*pZ1;
//					Msg("dx21 %d dy21 %d dz21 %d \r\n",OUTF1(dx21),OUTF1(dy21),OUTF1(dz21));
//					Msg("dx31 %d dy31 %d dz31 %d \r\n",OUTF1(dx31),OUTF1(dy31),OUTF1(dz31));
					*pA = dy21*dz31 - dy31*dz21;
					*pB = dx31*dz21 - dx21*dz31;
					*pC = dx21*dy31 - dy21*dx31;
					*pD = (*pA)*(*pX1) + (*pB)*(*pY1) + (*pC)*(*pZ1);
//					Msg("A %d B %d C %d D %d\r\n",OUTF1(A),OUTF1(B),OUTF1(C),OUTF1(D));
					if (!(*pC)) {
						// компенсация не возможна
						Msg("Init Err Zcomp. Koef C==0.\r\n");
						*pfZcomp = 0;
						dz = 0;
					} else {
						*pfZcomp = 1;
  					XYZImpToXYZ(*(ms_X.Pos),*(ms_Y.Pos),0,&tmpX,&tmpY,&tmpZ);	
						dz = (*pD-(*pA)*(tmpX+*pX1)-(*pB)*(tmpY+*pY1))/(*pC);
						// здесь по dXpos dYpos можно скорректировать dZpos чтобы точка была на поверхности
						dXYZImpTodXYZ(*dXPos,*dYPos,0,&tmpX,&tmpY,&tmpZ);	
						tmpZ = (*pD-(*pA)*(tmpX)-(*pB)*(tmpY))/(*pC);
						if (tmpZ < 0) *dZPos = 0;
						else *dZPos = (tmpZ*(*pZ_SPR)/(*pZ_PG_MM));
						Msg("dx %d dy %d x %d y %d z %d dz %d\r\n",*dXPos,*dYPos,OUTF1T(tmpX),OUTF1T(tmpY),OUTF1T(tmpZ),*dZPos);
					}
				}
			}
		}
	}
	if (*pfZcomp) Msg("Init Zcomp success. A %d B %d C %d D %d dz %d\r\n",OUTF1(*pA),OUTF1(*pB),OUTF1(*pC),OUTF1(*pD),OUTF1T(dz));
}


void ShowMC(TFMC * mc){
//	Msg("FMin %d FrR %d FrMax %d RP %d LAP %d Acc %d RD %d MBtn	%d MPos %d PositOn %d\r\n",
	Msg("FrMax %d\r\n",
/*
	*(mc->FrMin)/K1,
	*(mc->FrReq)/K1,
*/
	*(mc->FrMax));
/*
	Msg("RP %d LAP %d Acc %d RD %d MBtn %d MPos %d PositOn %d\r\n",

	*(mc->FrMin),
	*(mc->FrReq),
	*(mc->FrMax),

	*(mc->ReqPos),
	*(mc->LenActPulse),
    *(mc->Accel),
	*(mc->ReqDir),	
	*(mc->MoveBtn),	
	*(mc->MovePos),	
	*(mc->PositOn));	
*/
}

void ShowMS(TFMS * ms){
	Msg("Level %d Dir %d Pos %d Lacc %d FrCur %d Tcur %d LPON %d LPOFF %d Posit %d StagePos %d\r\n",
		ms->Level,
		*(ms->Dir),
		*(ms->Pos),
		ms->Lacc,
		*(ms->FrCur),
		ms->Tcur,			
		ms->LPON,			
		ms->LPOFF,				
		*(ms->Posit),
		*(ms->StagePos));
}


void InitMotorStructF(volatile TFMS* ms,volatile TFMC* mc ) {
	// параметры по умолчанию для управляющей структуры
	*(mc->LenOnPulse) = 5000;
	*(mc->Accel) = 5000;			// Гц/с
	*(mc->FrMin) = 100*K1;			// Гц / K1
	*(mc->FrReq) = 4300*K1;		// Гц / K1
	*(mc->FrMax) = 4300*K1;		// Гц / K1
	*(mc->ReqDir) = -1;			// требуемое направление сброшено
	*(mc->MoveBtn) = 0;				// движение запрещено
	// параметры по умолчанию
	ms->Level = 0;							// уровень сброшен
	// т.к. сигнал управления направления по умолчанию сброшен оба направления -1
	*(ms->Dir) = -1;							// направление положительное
   	*(ms->Pos) = 0;							// текущая позиция
	if (!(*(mc->FrMin))) *(mc->FrMin) = 1*K1;
	if (*(mc->FrMax) < *(mc->FrMin)) *(mc->FrMax) = *(mc->FrMin);
	if (*(mc->FrReq) == 0) *(mc->FrReq) = 1*K1;

	if (*(mc->FrReq) < *(mc->FrMin)) {
		*(ms->FrCur) = *(mc->FrReq);
	} else {
		*(ms->FrCur) = *(mc->FrMin);
	}
	ms->Tcur = Kb / (*(ms->FrCur));
	if (*(mc->LenOnPulse) == 0) *(mc->LenOnPulse) = 5000;
	ms->LPON =  *(mc->LenOnPulse);
	ms->LPOFF = ms->Tcur - ms->LPON;	
	*ms->Posit = 0;
	*mc->PositOn = 0;	
}

void InitMotorStructALF(volatile TFMS* ms,volatile TFMC* mc ) {
	// параметры по умолчанию для управляющей структуры
	*(mc->ReqDir) = -1;			// требуемое направление сброшено
	*(mc->MoveBtn) = 0;				// движение запрещено
	// параметры по умолчанию
	ms->Level = 0;							// уровень сброшен
	// т.к. сигнал управления направления по умолчанию сброшен оба направления -1
	*(ms->Dir) = -1;							
	if (!(*(mc->FrMin))) *(mc->FrMin) = 1*K1;
	if (*(mc->FrMax) < *(mc->FrMin)) *(mc->FrMax) = *(mc->FrMin);
	if (*(mc->FrReq) == 0) *(mc->FrReq) = 1*K1;

	if (*(mc->FrReq) < *(mc->FrMin)) {
		*(ms->FrCur) = *(mc->FrReq);
	} else {
		*(ms->FrCur) = *(mc->FrMin);
	}
	ms->Tcur = Kb / (*(ms->FrCur));
	if (*(mc->LenOnPulse) == 0) *(mc->LenOnPulse) = 5000;
	ms->LPON = *(mc->LenOnPulse); 
	ms->LPOFF = ms->Tcur - ms->LPON;	

	*(mc->PositOn) = 0;	
	*(mc->ReqPos) = 0;
	*(mc->MovePos) = 0;	
	*(ms->StagePos) = 0;	
}

u64 save_mc_Z_FrReq;
u64 save_mc_Z_FrMax;
u64 save_mc_X_FrReq;
u64 save_mc_X_FrMax;
u64 save_mc_Y_FrReq;
u64 save_mc_Y_FrMax;
u8 fStartMoveZLowSpeed = 0;
s32	Index = 1;
float px,py,pz;
u8 SendPointCount = 0;
// высота датчика в мм
float * pHdat;


void UpZ(void){
	*(mc_Z.FrReq) = save_mc_Z_FrMax;
	*(mc_Z.FrMax) = save_mc_Z_FrMax;
//	*(mc_Z.ReqPos) = Z_MAX_POS;
	*(mc_Z.ReqPos) = SaveZPos;
	*(mc_Z.MovePos) = 1;
	fStartMoveZLowSpeed = 0;
}

void BackHorizontal(void){
	switch (*pHorizDatDir) {
		case 2:// Up Down
		case 4:
			*(mc_Y.FrReq) = save_mc_Y_FrMax;
			*(mc_Y.FrMax) = save_mc_Y_FrMax;
			*(mc_Y.ReqPos) = SaveYPos;
			*(mc_Y.MovePos) = 1;
			break;
		case 1:
		case 3:// Left Right
			*(mc_X.FrReq) = save_mc_X_FrMax;
			*(mc_X.FrMax) = save_mc_X_FrMax;
			*(mc_X.ReqPos) = SaveXPos;
			*(mc_X.MovePos) = 1;
			break;
	}
}

void RecoveryZfreq(void){
	fStartMoveZLowSpeed = 0;
	Msg("StopMoveZLowSpeed\r\n");
	// восстановить максимальную и требуемую скорости по Z
	*(mc_Z.FrReq) = save_mc_Z_FrReq;
	*(mc_Z.FrMax) = save_mc_Z_FrMax;
	// остановиться
	*mc_Z.MovePos = 0;
}

void RecoveryHorizfreq(void){
	Msg("StopMoveHorizLowSpeed\r\n");
	switch (*pHorizDatDir) {
		case 1:// Up Down
		case 3:
			// восстановить максимальную и требуемую скорости по Y
			*(mc_Y.FrReq) = save_mc_Y_FrMax;
			*(mc_Y.FrMax) = save_mc_Y_FrMax;
			// остановиться
			*(mc_Y.MovePos) = 0;
			break;
		case 2:
		case 4:// Left Right
			// восстановить максимальную и требуемую скорости по X
			*(mc_X.FrReq) = save_mc_X_FrMax;
			*(mc_X.FrMax) = save_mc_X_FrMax;
			// остановиться
			*(mc_X.MovePos) = 0;
			break;
	}
}

void	StartMoveZLowSpeed(void){
	if (!fStartMoveZLowSpeed) {
		fStartMoveZLowSpeed = 1;
		Msg("StartMoveZLowSpeed Index %d\r\n",Index);
		// запомнить максимальную и требуемую скорости по Z
		save_mc_Z_FrReq = *(mc_Z.FrReq);
		save_mc_Z_FrMax = *(mc_Z.FrMax);
		// перебить их на минимальную
		*(mc_Z.FrReq) = *(mc_Z.FrMin);
		*(mc_Z.FrMax) = *(mc_Z.FrMin);
		// отправить Z координату вниз до срабатывания датчика или до 0
		// в нуле или в датчике восстановить скорости 
		SaveZPos = *(ms_Z.Pos);
		*mc_Z.ReqPos = 0;
		*mc_Z.MovePos = 1;
	} else {
		fStartMoveZLowSpeed = 0;
		Msg("StopMoveZLowSpeed\r\n");
		// восстановить максимальную и требуемую скорости по Z
		*(mc_Z.FrReq) = save_mc_Z_FrReq;
		*(mc_Z.FrMax) = save_mc_Z_FrMax;
		Msg("frmax frreq  %d %d\r\n",save_mc_Z_FrMax, save_mc_Z_FrReq);
		// остановиться
		*mc_Z.MovePos = 0;
	}
}


void	StartMoveHorizontalLowSpeed(void){
	Msg("StartMoveHorizontalLowSpeed Dir %d\r\n",*pHorizDatDir);
	switch (*pHorizDatDir) {
			case 2:// Up Down
			case 4:
				// запомнить максимальную и требуемую скорости по Y
				save_mc_Y_FrReq = *(mc_Y.FrReq);
				save_mc_Y_FrMax = *(mc_Y.FrMax);
				// перебить их на минимальную
				*(mc_Y.FrReq) = *(mc_Y.FrMin);
				*(mc_Y.FrMax) = *(mc_Y.FrMin);
				// отправить Y координату вверх до срабатывания датчика или до MaxPos
				// в нуле или в датчике восстановить скорости 
				SaveYPos = *(ms_Y.Pos);
				if (*pHorizDatDir == 2) *(mc_Y.ReqPos) = 0;
				else *(mc_Y.ReqPos) = Y_MAX_POS;
				*(mc_Y.MovePos) = 1;
				break;
			case 1:// Left Right
			case 3:
				// Save X
				// запомнить максимальную и требуемую скорости по Y
				save_mc_X_FrReq = *(mc_X.FrReq);
				save_mc_X_FrMax = *(mc_X.FrMax);
				// перебить их на минимальную
				*(mc_X.FrReq) = *(mc_X.FrMin);
				*(mc_X.FrMax) = *(mc_X.FrMin);
				// отправить X координату вверх до срабатывания датчика или до MaxPos
				// в нуле или в датчике восстановить скорости 
				SaveXPos = *(ms_X.Pos);
				if (*pHorizDatDir == 1) *(mc_X.ReqPos) = 0;
				else *(mc_X.ReqPos) = X_MAX_POS;
				*(mc_X.MovePos) = 1;
				break;
			default:
				Msg("Error Horizontal Dat!!! Set Dir 0 (1)\r\n");
			break;
	}
}

void	StopMoveHorizontalLowSpeed(void){
	Msg("StopMoveHorizontalDatLowSpeed\r\n");
	switch (*pHorizDatDir) {
			case 2:// Up Down
			case 4:
				// восстановить максимальную и требуемую скорости по Y
				*(mc_Y.FrReq) = save_mc_Y_FrMax;
				*(mc_Y.FrMax) = save_mc_Y_FrMax;
				// остановиться
				*mc_Y.MovePos = 0;
				break;
			case 1:// Left Right
			case 3:
				// восстановить максимальную и требуемую скорости по X
				*(mc_X.FrReq) = save_mc_X_FrMax;
				*(mc_X.FrMax) = save_mc_X_FrMax;
				// остановиться
				*mc_X.MovePos = 0;
				break;
			default:
				Msg("Error Horizontal Dat!!! Set Dir 0 (2)\r\n");
			break;
	}		
}


void	AddPointFrz(void){
	// выдача пакета добавления точки
	//float px,py,pz;
	Msg("AddPoint ");	
	// позицию по Z откорректировать на высоту датчика pHdat
	Msg("xp %d yp %d zp %d\r\n",*(ms_X.Pos),*(ms_Y.Pos),*(ms_Z.Pos));
	dXYZImpTodXYZ(*(ms_X.Pos),*(ms_Y.Pos),*(ms_Z.Pos),&px,&py,&pz);
	pz = pz - *pHdat;
	SendAddPointPackFrz(&Index,&px,&py,&pz);
	FixPointPackFrz(&Index,&px,&py,&pz);
	StartTI(tiRetrySendPoint,tiMsToTick(100));
	SendPointCount = 3;
	Msg("AP %d %d %d %d\r\n",Index,OUTF1T(px),OUTF1T(py),OUTF1T(pz));
	Index++;
	if (Index > 3) Index = 1;
}

void	HTCorr(void){
	// выдача пакета добавления точки
	float ptx,pty,ptz,pzc,dz;
	Msg("HTCorr ");
	// позицию по Z откорректировать на высоту датчика pHdat
	Msg("xp %d yp %d zp %d\r\n",*(ms_X.Pos),*(ms_Y.Pos),*(ms_Z.Pos));
	// измерить dZTool 
	// получаем px,py (pz не нужно) абсолютные
	dXYZImpTodXYZ(*(ms_X.Pos),*(ms_Y.Pos),*(ms_Z.Pos),&ptx,&pty,&ptz);
	Msg("ptx %d pty %d\r\n",OUTF1T(ptx),OUTF1T(pty));
	// вычисляем z на плоскости
	if (*pfZcomp) {
		if (*pC) {
//			ptz = (D-A*(ptx-*pX1)-B*(pty-*pY1))/C;
			ptz = ((*pD)-(*pA)*(ptx)-(*pB)*(pty))/(*pC);
			// прибавляем высоту датчика и pZ1
			// ptz = ptz + *pHdat + *pZ1;
			// вычисляем обсолютную координату z по позиции
			dXYZImpTodXYZ(0,0,*(ms_Z.Pos),&ptx,&pty,&pzc);
			// вычислить отклонение по z координате
			dz = pzc - ptz - *pHdat;
			Msg("pzc %d ptz %d dz %d\r\n",OUTF1T(pzc),OUTF1T(ptz),OUTF1T(dz));
			// прибавить к pZ1 pZ2 pZ3
			*pZ1 += dz;
			*pZ2 += dz;
			*pZ3 += dz;
			// вычислить новую плоскостную коррекцию
		} 
		// С == 0 
	} else {
		// корекция только первой точки для расчета dXPos dYPos dZPos
		// НЕ ПРОВЕРЕНО !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		dXYZImpTodXYZ(*(ms_X.Pos),*(ms_Y.Pos),*(ms_Z.Pos),&ptx,&pty,&ptz);
		//dz = pzc - ptz - *pHdat;
		dz = ptz - *pZ1 - *pHdat ;
		Msg("ptz %d Hd %d dz %d pZ1 %d\r\n",OUTF1T(ptz),OUTF1T(*pHdat),OUTF1T(dz),OUTF1T(*pZ1));
		*pZ1 += dz;
	}
	*pfZcomp = 0;
	InitZComp();
	*pHTCorr = 0; // конец коррекции
}

void XYZToXYZImp(float X,float Y,float Z,s32 * Xi,s32 * Yi,s32 * Zi){
	*Xi = *dXPos + (X * (*pX_SPR))/(*pX_PG_MM);
	*Yi = *dYPos + (Y * (*pY_SPR))/(*pY_PG_MM);
// Эта формула правильна если MIN_POS >=0	
//	*Zi = Z_MIN_POS + (Z * (*pZ_SPR))/(*pZ_PG_MM);
// Эта формула если MIN_POS < 0 
	*Zi = *dZPos + (Z * (*pZ_SPR))/(*pZ_PG_MM);
// компенсация по Z
//	*Zi = *dZPos + ( ZComp(X,Y,Z)) * (*pZ_SPR))/(*pZ_PG_MM);
	if ((*Zi) > Z_MAX_POS) (*Zi) = Z_MAX_POS;
	if ((*Zi) < 0) (*Zi) = 0;
	if ((*Xi) > X_MAX_POS) (*Zi) = X_MAX_POS;
	if ((*Xi) < 0) (*Xi) = 0;
	if ((*Yi) > Y_MAX_POS) (*Zi) = Y_MAX_POS;
	if ((*Yi) < 0) (*Yi) = 0;	
}

void XYZToXYZImpZcomp(float X,float Y,float Z,s32 * Xi,s32 * Yi,s32 * Zi){
	*Xi = *dXPos + (X * (*pX_SPR))/(*pX_PG_MM);
	*Yi = *dYPos + (Y * (*pY_SPR))/(*pY_PG_MM);
// Эта формула правильна если MIN_POS >=0	
//	*Zi = Z_MIN_POS + (Z * (*pZ_SPR))/(*pZ_PG_MM);
// Эта формула если MIN_POS < 0 
//	*Zi = *dZPos + (Z * (*pZ_SPR))/(*pZ_PG_MM);
// компенсация по Z
	*Zi = *dZPos + (ZComp(X,Y,Z) * (*pZ_SPR))/(*pZ_PG_MM);
	if ((*Zi) > Z_MAX_POS) (*Zi) = Z_MAX_POS;
	if ((*Zi) < 0) (*Zi) = 0;
	if ((*Xi) > X_MAX_POS) (*Zi) = X_MAX_POS;
	if ((*Xi) < 0) (*Xi) = 0;
	if ((*Yi) > Y_MAX_POS) (*Zi) = Y_MAX_POS;
	if ((*Yi) < 0) (*Yi) = 0;
	//Msg("mmtoimp\r\n");
}

void XYZImpToXYZ(s32 Xi,s32 Yi,s32 Zi,float *X,float *Y,float *Z){
	*X = (Xi- *dXPos)*(*pX_PG_MM)/(*pX_SPR);
	*Y = (Yi- *dYPos)*(*pY_PG_MM)/(*pY_SPR);
// см. выше
//	*Z = (Zi-Z_MIN_POS)*(*pZ_PG_MM)/(*pZ_SPR);
	*Z = (Zi- *dZPos)*(*pZ_PG_MM)/(*pZ_SPR);
}

void dXYZImpTodXYZ(s32 Xi,s32 Yi,s32 Zi,float *X,float *Y,float *Z){
	*X = (Xi)*(*pX_PG_MM)/(*pX_SPR);
	*Y = (Yi)*(*pY_PG_MM)/(*pY_SPR);
// см. выше
//	*Z = (Zi-Z_MIN_POS)*(*pZ_PG_MM)/(*pZ_SPR);
	*Z = (Zi)*(*pZ_PG_MM)/(*pZ_SPR);
}

void Brezenheim	(s32 * e1,s32 * e2,
				s32 *Xi,	s32 *Yi,	s32 *Zi,
				s32 dXi,	s32 dYi,	s32 dZi,
				s32 signX,	s32 signY,	s32 signZ,
				u8 *stepX,	u8 *stepY,	u8 *stepZ)
{
	s32 e12,e22;  
	*stepX=0;	
	*stepY=0;	
	*stepZ=0;	
    e12 = *e1 * 2;
    e22 = *e2 * 2;
    if ((e12 > -dYi)&&(e22 > -dZi))  {
    	*e1 = *e1 - dYi;
    	*e2 = *e2 - dZi;
      *Xi += signX;
			*stepX = 1;
    };
    if (e12 < dXi)  {
      *e1 = *e1 + dXi;
      *Yi += signY;
			*stepY = 1;
    };
    if (e22 < dXi)  {
      *e2 = *e2 + dXi;
      *Zi += signZ;
			*stepZ = 1;
    };
//	Msg("e1 %d e2 %d\r\n", *e1,*e2);
//	Msg("e12 %d e22 %d\r\n", e12,e22);
//	Msg("Xi	%d Yi %d Zi %d\r\n",*Xi,*Yi,*Zi);
//	Msg("dXi %d dYi %d dZi %d\r\n",dXi,dYi,dZi);
//	Msg("signX %d signY %d signZ %d\r\n",signX,signY,signZ);
//	Msg("stepX %d stepY %d stepZ %d\r\n",*stepX,*stepY,*stepZ);
}

// Алгоритм прямолинейного движения, предполагающий не ровные фронты сигналов
// step и dir из-за плохих оптопар
// dir выдается при пассивном фронте step.
// переменная level отражает инвертированный уровень сигнала step
// алгоритм с инвертированной логикой
// при level = 1 step сбрасывается а необходимые dir`ы устанавливаются
// при level = 0 step устанавливается
// при переходе алгоритма в состояние мониторинга обеспечивается 
// однократный сброс сигналов step

float dS; //приращение пути,
u8 stepX,stepY,stepZ;

// флаг принудительного сброса сигналов step в соответствии с изменениеми логики
// алгоритма прямолинейного движения
u8 ClrF = 0; 

float Vct,con,St1,Vin;
int itc,cm,cc,cd;
int	Tacc, Tdec; 
u32 Sti; // путь торможения в импульсах

int DecItCount(float Vc){
	itc = 1;
	Vct = Vc;
	con = *(fmvc.Vaccel)*(*eb).Tb/K1;
	while (Vct > *(fmvc.Vmin)){
		Vct = Vct - con/Vct;
		itc++;
	}	
	return itc;
}

u8 f=1;
void	FMove_HandlerQuick(void){
// 	u8 stepX,stepY,stepZ,ChDir;
//	float Vct,Vc2,con;
//	int itc;
	s32 ex,ey,ez;
	//float St; // путь торможения
	float	dV,dVmax; // приращение скорости, максимальное приращение скорости
	u32		T;
	if (fmvs.Level==0)  {
		if (fmvc.Enable==0)  { 
			// движение запрещено мониторинг
			if (ClrF) {
				ClrF = 0;
				// принудительный сброс сигналов step
				Q1ClrPin(MOTOR_X_STEP);	QClrPin(MOTOR_Yl_STEP);	QClrPin(MOTOR_Yr_STEP);	QClrPin(MOTOR_Z_STEP);
				//Msg("B0\r\n");
			}	
			Busy = 0;
			cm=0; cc=0; cd = 0;
			Tacc = 0; Tdec = 0; 
			Sti = 0;
#ifdef 	MOVE_D
			if (f) {Msg("Sti0\r\n");f=0;}
#endif
//			TCS_SetInterval(tcs_FMove,2500000);		
			TCS_SetInterval(tcs_FMove,2500000);		
		} else 	{
			f=1;
			// движение разрешено
			// проверяем наличие исполняемого болка
			if (eb==NULL) {
				// ждем пока не Null
				Msg("eb=Null\r\n");
				fmvc.Enable = 0;// Busy = 0;
//				Msg("E1\r\n");
				TCS_SetInterval(tcs_FMove,2500000);
			} else 	{ //(eb==NULL) {
				// здесь блок есть и его можно попытаться выполнить
				if ((*eb).Nomove) {	
					// к сожалению блок не выпоним тк приращения по всем координатам равны 0 
					// и нужен следующий блок
					Msg("Nomove\r\n");
					*pRCS = rcsEndExecute; 	
					fmvc.Enable = 0;//	Busy = 0;
//					Msg("E2\r\n");
					TCS_SetInterval(tcs_FMove,25000);
				} else { //((*eb).Nomove) {	
					ClrF = 0; dV = 0; dVmax = 0;
					// проверка отктонения Xi ms_X.Pos ...
					ex=(*eb).Xi-(*ms_X.Pos);
					ey=(*eb).Yi-(*ms_Y.Pos);
					ez=(*eb).Zi-(*ms_Z.Pos);
					//ex=1;
					if (ex || ey || ez) { 
							Msg("e %d %d %d\r\n",ex,ey,ez);
							//Msg("Zsi %d Zdi %d\r\n",(*eb).Zsi,(*eb).Zdi);
					}
					// здесь блок достоверно можно выполнить. хотя бы одно приращение не =0
					// установка необходимых направлений
					*(ms_X.Dir) = (*eb).signX;	
					if (*(ms_X.Dir) == 1) QSetPin(MOTOR_X_DIR);	else QClrPin(MOTOR_X_DIR);
					*(ms_Y.Dir) = (*eb).signY;
					if (*(ms_Y.Dir) == 1) {	QSetPin(MOTOR_Yl_DIR); QSetPin(MOTOR_Yr_DIR);	} 
					else {QClrPin(MOTOR_Yl_DIR);QClrPin(MOTOR_Yr_DIR);}
					*(ms_Z.Dir) = (*eb).signZ;
					if (*(ms_Z.Dir) == 1) QSetPin(MOTOR_Z_DIR); else QClrPin(MOTOR_Z_DIR);
					// Это Брезенхейм
					switch ((*eb).Lax) {
       			case 0:	// XYZ
							Brezenheim(	&(*eb).e1,&(*eb).e2,
										&(*eb).Xi,&(*eb).Yi,&(*eb).Zi,
										(*eb).dXi,(*eb).dYi,(*eb).dZi,
								   	(*eb).signX,(*eb).signY,(*eb).signZ,
										&stepX,&stepY,&stepZ
									  );
						break;
						case 1:	// YXZ
							Brezenheim(	&(*eb).e1,&(*eb).e2,
										&(*eb).Yi,&(*eb).Xi,&(*eb).Zi,
										(*eb).dYi,(*eb).dXi,(*eb).dZi,
									   	(*eb).signY,(*eb).signX,(*eb).signZ,
										&stepY,&stepX,&stepZ
									  );
						break;
         		case 2: // ZXY
							Brezenheim(	&(*eb).e1,&(*eb).e2,
										&(*eb).Zi,&(*eb).Xi,&(*eb).Yi,
										(*eb).dZi,(*eb).dXi,(*eb).dYi,
								   	(*eb).signZ,(*eb).signX,(*eb).signY,
										&stepZ,&stepX,&stepY
									  );
						break;
					}//switch
					// выдача необходимых импульсов
/*					
					if (stepX) { *(ms_X.Pos) = (*eb).Xi; BR_ms_X_Pos = *(ms_X.Pos); QSetPin(MOTOR_X_STEP);}
					if (stepY) { *(ms_Y.Pos) = (*eb).Yi; BR_ms_Y_Pos = *(ms_Y.Pos); QSetPin(MOTOR_Yl_STEP); QSetPin(MOTOR_Yr_STEP);}
					if (stepZ) { *(ms_Z.Pos) = (*eb).Zi; BR_ms_Z_Pos = *(ms_Z.Pos); QSetPin(MOTOR_Z_STEP); }
*/				
					if (stepX) { *(ms_X.Pos) = (*eb).Xi; BR_ms_X_Pos = *(ms_X.Pos);}
					if (stepY) { *(ms_Y.Pos) = (*eb).Yi; BR_ms_Y_Pos = *(ms_Y.Pos);}
					if (stepZ) { *(ms_Z.Pos) = (*eb).Zi; BR_ms_Z_Pos = *(ms_Z.Pos);}
					// выдачу импульсов заменяем на сброс в связи с изменившейся логикой 
					Q1ClrPin(MOTOR_X_STEP);	QClrPin(MOTOR_Yl_STEP);	QClrPin(MOTOR_Yr_STEP);	QClrPin(MOTOR_Z_STEP);
//					(*eb).dS = 	stepX*(*pX_PG_MM)/(*pX_SPR) +\
//											stepY*(*pY_PG_MM)/(*pY_SPR)	+\
//											stepZ*(*pZ_PG_MM)/(*pZ_SPR);
#ifdef MOVE_D
					// исходные данные
//					Msg("Sr %d\t\t\tVc %d dS %d\r\n",\
//					OUTF1T(Sr),OUTF1T(*(fmvs.Vc)),OUTF1T((*eb).dS));
#endif
					// расчет периода частоты
					// расчет периода по предварительновычисленной величине Tb и текущей скорости
		   		T = (int)((*eb).Tb*1.0/(*(fmvs.Vc)));
					Vin = *(fmvs.Vc);
					// новый расчет периода
					// Vf = Fv(*(fmvs.Vc)); // частотная скорость из линейной
					// Af = Fa(*(fmvc.Vaccel)); // частотное ускорение из линейного 
					//T = (int)(1*(-Vf+ sqrt(sqr(Vf) + 2 * (Af))/(Af)));
					//Vnew = sqrt(V*V+2*A); // ускорение
					//Vnew = sqrt(V*V-2*A); // торможение
					// ОТЛАДКА !!!
	   			fmvs.LPOFF = CLPOFF(T,*(fmvc.LenOnPulse));
		  		fmvs.Level = 1;
					// расчет пути торможения от текущей скорости подачи
					//*************************************
					// вычисляем путь торможения по формуле sqrt(v)/2a
					// умножение на 1.1 для уменьшения погрешности определения
//					St = 1.0*(sqr(*(fmvs.Vc)))/(2* (*(fmvc.Vaccel)));
//					// оцениваем примерное количесво итераций для итерационного алгоритма
//					if ((St/(*eb).dS) < 90.0) {
//						// тут можно применить итерационный алгоритм расчета пути торможения
//						itc = 1; 
//						con = (*(fmvc.Vaccel)*(*eb).Tb/K1);
//						Vct = *(fmvs.Vc);
//						while ((Vct > *(fmvc.Vmin))){	Vct = Vct - con/Vct;	itc++;}	
//						St = (*eb).dS * itc;
//					}
					// если итерационный алгоритм применять нельзя то используем вычисленное значение
					//***********************************
					Sr = Sr - (*eb).dS; /// !!! уменьшить разведанный путь
					if (Sr < 0) Sr = 0;
					if (Sri) Sri--;
					// сравнение с текущим разведанным путем Sr
//					if ((St) < Sr) {
//					if ((Sti+11) < Sri) {
					if ((Sti) < Sri) {
						// разгон и движение с постоянной скоростью
						if (fmvc.Enable == 1) {
							// признак корректной остановки
							if (*(fmvs.Vc) > *(fmvc.Vmin)) {
								*pCorrStop = 0 ;
								BR_pCorrStop = 0;
							} else { // (*(fmvs.Vc) <= *(fmvc.Vmin))
								*pCorrStop = 1 ;
								BR_pCorrStop = 1;
							}
							if (*(fmvs.Vc) < (fmvc.Vmax)) {
								// вычисление скорости для следующей итерации при ускорении
								// по ускорению и времени
								dV = *(fmvc.Vaccel) * (T * 1.0 / K1); 
								// ограничение приращения по скорости в 100 Гц
								dVmax = 100*1.0*(*eb).Tb/K1; if (dV > dVmax) dV = dVmax;
								*(fmvs.Vc) = *(fmvs.Vc) + dV;
								Sti++;
								Tacc+=T;
								// новое ускорение
								//Vf = sqrt(sqr(Vf)+2*Af); 
								// *(fmvs.Vc) = Fc(Vf); // обратное получение линейной скорости из чатотной
								cc++; if (cm < cc) cm=cc;
								if (*(fmvs.Vc) > fmvc.Vmax) *(fmvs.Vc) = fmvc.Vmax; // ограничили сверху
							} else {
								// если скорость уменьшили в процессе движения
								if (*(fmvs.Vc) > (fmvc.Vmax)) {
									// вычисление скорости для следующей итерации при замедлении
									// по текущей и минимальной скорости и количеству итераци для торможения
									if (Sti>1) dV = (*(fmvs.Vc) - *(fmvc.Vmin))/(Sti-1); 
									else dV = (*(fmvs.Vc) - *(fmvc.Vmin))/1; 
									// ограничение приращения по скорости в 100 Гц
									dVmax = 100*1.0*(*eb).Tb/K1; if (dV > dVmax) dV = dVmax;
									
									// торможение до максимальной скорости
									*(fmvs.Vc) = *(fmvs.Vc) - dV; 
									if (Sti) Sti--;
									// новое торможение
//									if (sqr(Vf) > 2*Af)
//										Vf = sqrt(sqr(Vf)-2*Af); 
//									else Vf = 0;
								// *(fmvs.Vc) = Fc(Vf); // обратное получение линейной скорости из чатотной
									Tdec+=T; cd++;
									if (cc) cc--;
									if (*(fmvs.Vc) < fmvc.Vmax) *(fmvs.Vc) = fmvc.Vmax; // ограничили снизу
								}
							} 
						} else { //fmvc.Enable == 2
							// только торможение
							if (*(fmvs.Vc) > *(fmvc.Vmin)) {
								// вычисление скорости для следующей итерации при замедлении
								// по текущей и минимальной скорости и количеству итераци для торможения
								if (Sti>1) dV = (*(fmvs.Vc) - *(fmvc.Vmin))/(Sti-1); 
								else dV = (*(fmvs.Vc) - *(fmvc.Vmin))/1; 
								// ограничение приращения по скорости в 100 Гц
								dVmax = 100*1.0*(*eb).Tb/K1; if (dV > dVmax) dV = dVmax;
								*(fmvs.Vc) = *(fmvs.Vc) - dV; 
								if (Sti) Sti--;
								// новое торможение
//									if (sqr(Vf) > 2*Af)
//										Vf = sqrt(sqr(Vf)-2*Af); 
//									else Vf = 0;
								// *(fmvs.Vc) = Fc(Vf); // обратное получение линейной скорости из чатотной
								Tdec+=T; cd++;
								if (cc)cc--; 
								if (*(fmvs.Vc) < *(fmvc.Vmin)) *(fmvs.Vc) = *(fmvc.Vmin); // ограничили снизу
							} else {
								// корректная остановка
								Msg("CorrStop G1\r\n");
								*pCorrStop = 1;
								BR_pCorrStop = *pCorrStop;
								ClrF = 1;
								fmvc.Enable = 0;	//Busy = 0;
//								Msg("E3\r\n");
								// поднять Z на максимум
								*(mc_Z.ReqPos) = Z_MAX_POS;
								*(mc_Z.MovePos) = 1;
								// остановить шпиндель и выключить охлаждение
								FIStop();		QClrPin(COOLER1); QClrPin(COOLER2); 
							}
						}
					} else {
						// торможение до минимально скорости
						if (fmvc.Enable == 2) {
							if (*(fmvs.Vc) <= *(fmvc.Vmin)){
								Msg("CorrStop G1\r\n");
								*pCorrStop = 1 ;
								BR_pCorrStop = 1;
								ClrF = 1;
								fmvc.Enable = 0;//	Busy = 0;
								*(mc_Z.ReqPos) = Z_MAX_POS;
								*(mc_Z.MovePos) = 1;
								// остановить шпиндель и выключить охлаждение
								FIStop();		QClrPin(COOLER1); QClrPin(COOLER2); 
								
//								Msg("E4\r\n");
							}
						} 
						if (*(fmvs.Vc) > *(fmvc.Vmin)) {
							// вычисление скорости для следующей итерации при замедлении
							// по текущей и минимальной скорости и количеству итераци для торможения
							if (Sti>1) dV = (*(fmvs.Vc) - *(fmvc.Vmin))/(Sti-1); 
							else dV = (*(fmvs.Vc) - *(fmvc.Vmin))/1; 
							// ограничение приращения по скорости в 100 Гц
							dVmax = 100*1.0*(*eb).Tb/K1; if (dV > dVmax) dV = dVmax;
							*(fmvs.Vc) = *(fmvs.Vc) - dV; 
							if (Sti) Sti--;
							// новое торможение
//									if (sqr(Vf) > 2*Af)
//										Vf = sqrt(sqr(Vf)-2*Af); 
//									else Vf = 0;
								// *(fmvs.Vc) = Fc(Vf); // обратное получение линейной скорости из частотной
							Tdec+=T; cd++;
							if (cc)cc--;
							if (*(fmvs.Vc) < *(fmvc.Vmin)) *(fmvs.Vc) = *(fmvc.Vmin); // ограничили снизу
						} 
					}
					// работа со скоростью
					fmvc.Vmax = *(fmvc.V)*(*(fmvc.Vmul)/100);
#ifdef MOVE_D
//					Msg("Sr %d St %d Vc %d dV %d T %d F %d\r\n",\
//					OUTF1T(Sr),OUTF1T(St),OUTF1T(*(fmvs.Vc)),OUTF1T(dV),OUTF1(T*1.0/25),OUTF1T(1.0/(T*1.0/25000)));
					Msg("dVm %d dV %d Vs %d T %d F %d Sri %d Sti %d Sr %d",\
					OUTF1T(dVmax),OUTF1T(dV),OUTF1T(Vin),OUTF1(T*1.0/25),OUTF1T(1.0/(T*1.0/25000)),Sri,Sti,OUTF1T(Sr));
					

#endif
					// уход на следующую итерацию
					// запустить таймер на следующую итерацию
					TCS_SetInterval(tcs_FMove,fmvs.LPOFF);
				} //else ((*eb).Nomove) {	
			} // else (eb==NULL) {
		} //else (fmvc.Enable==0)  { 
	} else { // Level != 0
		// сброс всех импульсов
/*		
		QClrPin(MOTOR_X_STEP);
		QClrPin(MOTOR_Yl_STEP);
		QClrPin(MOTOR_Yr_STEP);
		QClrPin(MOTOR_Z_STEP);
*/
		// заменяем сброс импульсов на установку нужных
		if (stepX) { Q1SetPin(MOTOR_X_STEP);}
		if (stepY) { QSetPin(MOTOR_Yl_STEP); QSetPin(MOTOR_Yr_STEP);}
		if (stepZ) { QSetPin(MOTOR_Z_STEP); }
		fmvs.Level = 0;
//		TCS_SetInterval(tcs_FMove,*(fmvc.LenOffPulse));
		// условие окончания движения
		if (((*eb).Xi==(*eb).Xdi)&&((*eb).Yi==(*eb).Ydi)&&((*eb).Zi==(*eb).Zdi)){
			//Msg("Vout %d\r\n",OUTF(*(fmvs.Vc)));
			if ((*eb).Nonstop) {
				SaveFilePos();
				qbDelFirst();
				eb = NULL;
				eb = qbFirstBlock();
				if (eb==NULL) {
					Msg("ebNull\r\n");
					ClrF = 1;
					fmvc.Enable = 0;//	Busy = 0;
//					Msg("E5\r\n");
					//TCS_SetInterval(tcs_FMove,fmvs.LPON);
				} else {
					*pCurCadr = (*eb).NumLine;
#ifdef MOVE_D					
					Msg("RI%d:G%d Xd %d Yd %d Zd %d NS %d\r\n",(*eb).NumLine,(*eb).sGo,OUTF1T((*eb).Xd),OUTF1T((*eb).Yd),OUTF1T((*eb).Zd),(*eb).Nonstop);
#endif		
					//Msg("t%d: %s",(*eb).NumLine,(*eb).s);
					//Msg("X %d %d Y %d %d Z %d %d\r\n",(*eb).Xsi,(*eb).Xdi,(*eb).Ysi,(*eb).Ydi,(*eb).Zsi,(*eb).Zdi);
					//Msg("tb %d \r\n",(*eb).Tb);
					memcpy((void*)&(BR_pCurCadr),(void*)pCurCadr,4);
//					if ((*eb).Nonstop) {
//						//TCS_SetInterval(tcs_FMove,fmvs.LPON); //???
//					} else {
//						(*pRCS)=rcsGetBlock;
//						ClrF = 1;
//						fmvc.Enable = 0;//						Busy = 0;
////						Msg("E6\r\n");
//						//TCS_SetInterval(tcs_FMove,fmvs.LPON);
//					}
					//TCS_SetInterval(tcs_FMove,fmvs.LPON);
#ifdef MOVE_D					
//					Msg("NS %d En %d\r\n",(*eb).Nonstop,fmvc.Enable);
#endif		
				}
				//TCS_SetInterval(tcs_FMove,fmvs.LPON);
			} else {
				*pRCS = rcsEndExecute; 	
				ClrF = 1;
				fmvc.Enable = 0;//				Busy = 0;
//				Msg("E7\r\n"); StartTimeTC(T1);
				*pCorrStop = 1;
				BR_pCorrStop = *pCorrStop;
				//TCS_SetInterval(tcs_FMove,fmvs.LPON);
			}
			//TCS_SetInterval(tcs_FMove,fmvs.LPON);
		} else {
			// двигаемся дальше
			//TCS_SetInterval(tcs_FMove,fmvs.LPON); 
		}
		TCS_SetInterval(tcs_FMove,fmvs.LPON);
	} // Level == 0
}
/*
// Алгоритм прямолинейного движения, предполагающий ровные фронты сигналов
// step и dir. В одной ветке выдаются и step и dir.
void	FMove_HandlerQuick(void){
	u8 stepX,stepY,stepZ,ChDir;
	s32 ex,ey,ez;
	float St,dV; // путь торможения,  приращение скорости
	u32		T;
	if (fmvs.Level==0)  {
		if (fmvc.Enable==0)  { 
			// движение запрещено мониторинг
			Busy = 0;
			TCS_SetInterval(tcs_FMove,2500000);		
		} else 	{
			// движение разрешено
			// проверряем наличие исполняемого болка
			if (eb==NULL) {
				// ждем пока не Null
				Msg("eb=Null\r\n");
				fmvc.Enable = 0; Busy = 0;
				TCS_SetInterval(tcs_FMove,2500000);
			} else 	{ //(eb==NULL) {
				// здесь блок есть и его можно попытаться выполнить
				//Msg("Xpos %d Ypos %d Zpos %d\r\n",*(ms_X.Pos),*(ms_Y.Pos),*(ms_Z.Pos));
				//Msg("Xi %d Yi %d Zi %d\r\n",(*eb).Xi,(*eb).Yi,(*eb).Zi);
				if ((*eb).Nomove) {	
					// к сожалению блок не выпоним тк приращения по всем координатам равны 0 
					// и нужен следующий блок
					Msg("Nomove\r\n");
					*pRCS = rcsEndExecute; 	
					fmvc.Enable = 0;
					Busy = 0;
					TCS_SetInterval(tcs_FMove,2500000);
				} else { //((*eb).Nomove) {	
					// проверка отктонения Xi ms_X.Pos ...
					ex=(*eb).Xi-(*ms_X.Pos);
					ey=(*eb).Yi-(*ms_Y.Pos);
					ez=(*eb).Zi-(*ms_Z.Pos);
					//ex=1;
					if (ex || ey || ez) Msg("e %d %d %d\r\n",ex,ey,ez);
					// здесь блок достоверно можно выполнить. хотя бы одно приращение не =0
					// установка необходимых направлений
//					Msg("signX %d signY %d signZ %d\r\n",eb->signX,eb->signY,eb->signZ);
					// проверяем изменение направления хотябы по одной оси
					ChDir = 0;
					if (	(*(ms_X.Dir) != (*eb).signX)||
								(*(ms_Y.Dir) != (*eb).signY)||
								(*(ms_Z.Dir) != (*eb).signZ)
							) ChDir = 1;
					// теперь устанавливаем нужные направления
					*(ms_X.Dir) = (*eb).signX;	
					if (*(ms_X.Dir) == 1) QSetPin(MOTOR_X_DIR);	
					else QClrPin(MOTOR_X_DIR);

					*(ms_Y.Dir) = (*eb).signY;
					if (*(ms_Y.Dir) == 1) {
					  	QSetPin(MOTOR_Yl_DIR);
					  	QSetPin(MOTOR_Yr_DIR);
					} else {
						QClrPin(MOTOR_Yl_DIR);
						QClrPin(MOTOR_Yr_DIR);
					}
					*(ms_Z.Dir) = (*eb).signZ;
					if (*(ms_Z.Dir) == 1) QSetPin(MOTOR_Z_DIR);
					else QClrPin(MOTOR_Z_DIR);
					// уходим на задержку если была смена
					if (ChDir) {
						Msg("DelayDirM\r\n");
						TCS_SetInterval(tcs_FMove,*pDirDelay);
						return;
					}
					// Это Брезенхейм
					switch ((*eb).Lax) {
	        			case 0:	// XYZ
							Brezenheim(	&(*eb).e1,&(*eb).e2,
										&(*eb).Xi,&(*eb).Yi,&(*eb).Zi,
										(*eb).dXi,(*eb).dYi,(*eb).dZi,
									   	(*eb).signX,(*eb).signY,(*eb).signZ,
										&stepX,&stepY,&stepZ
									  );
	
						break;
						case 1:	// YXZ
							Brezenheim(	&(*eb).e1,&(*eb).e2,
										&(*eb).Yi,&(*eb).Xi,&(*eb).Zi,
										(*eb).dYi,(*eb).dXi,(*eb).dZi,
									   	(*eb).signY,(*eb).signX,(*eb).signZ,
										&stepY,&stepX,&stepZ
									  );
						break;
	
	            		case 2: // ZXY
							Brezenheim(	&(*eb).e1,&(*eb).e2,
										&(*eb).Zi,&(*eb).Xi,&(*eb).Yi,
										(*eb).dZi,(*eb).dXi,(*eb).dYi,
									   	(*eb).signZ,(*eb).signX,(*eb).signY,
										&stepZ,&stepX,&stepY
									  );
						break;
					}//switch

					// выдача неоходимых импульсов
					// выдача необходимых импульсов
					if (stepX) { *(ms_X.Pos) = (*eb).Xi; BR_ms_X_Pos = *(ms_X.Pos); QSetPin(MOTOR_X_STEP);}
					if (stepY) { *(ms_Y.Pos) = (*eb).Yi; BR_ms_Y_Pos = *(ms_Y.Pos); QSetPin(MOTOR_Yl_STEP); QSetPin(MOTOR_Yr_STEP);}
					if (stepZ) { *(ms_Z.Pos) = (*eb).Zi; BR_ms_Z_Pos = *(ms_Z.Pos); QSetPin(MOTOR_Z_STEP); }
					// расчет периода частоты
					// расчет периода по предварительновычисленной величине Tb и текущей скорости
		   		T = (int)((*eb).Tb*1.0/(*(fmvs.Vc)));
					// ОТЛАДКА !!!
					//if (!T) Msg("dv0");
	   			fmvs.LPOFF = CLPOFF(T,*(fmvc.LenOnPulse));
		  		fmvs.Level = 1;
					// вычисление скорости для следующей итерации
					Sr = Sr - (*eb).dS; /// !!! уменьшить разведанный путь
					if (Sr < 0) Sr = 0;
					// по ускорению и времени
					dV = *(fmvc.Vaccel) * (T*1.0 / K1); 
					// расчет пути торможения от текущей скорости подачи
					//St = (sqr(*(fmvs.Vc)))/(2* (*(fmvc.Vaccel)));
					St = (sqr(*(fmvs.Vc)))/((*(fmvc.Vaccel)));
					// сравнение с текущим разведанным путем Sr
					if ((St+(*eb).dS) < Sr) {
						// разгон и движение с постоянной скоростью
						if (fmvc.Enable == 1) {
							if (*(fmvs.Vc) > *(fmvc.Vmin)) {
								*pCorrStop = 0 ;
								BR_pCorrStop = 0;
							} else { // (*(fmvs.Vc) <= *(fmvc.Vmin))
								*pCorrStop = 1 ;
								BR_pCorrStop = 1;
							}
							if (*(fmvs.Vc) < (fmvc.Vmax)) {
								*(fmvs.Vc) = *(fmvs.Vc) + dV; 
								if (*(fmvs.Vc) > fmvc.Vmax) *(fmvs.Vc) = fmvc.Vmax; // ограничили сверху
							} else {
								// если скорость уменьшили в процессе движения
								if (*(fmvs.Vc) > (fmvc.Vmax)) {
									// торможение до максимальной скорости
									*(fmvs.Vc) = *(fmvs.Vc) - dV; 
									if (*(fmvs.Vc) < fmvc.Vmax) *(fmvs.Vc) = fmvc.Vmax; // ограничили снизу
								}
							} 
						} else { //fmvc.Enable == 2
							// только торможение
//							Msg("f%d",fmvc.Enable);
							if (*(fmvs.Vc) > *(fmvc.Vmin)) {
								*(fmvs.Vc) = *(fmvs.Vc) - dV; 
								if (*(fmvs.Vc) < *(fmvc.Vmin)) *(fmvs.Vc) = *(fmvc.Vmin); // ограничили снизу
							} else {
								// корректная остановка
								Msg("CorrStop G1\r\n");
								fmvc.Enable = 0;
								Busy = 0;
								*pCorrStop = 1;
								BR_pCorrStop = *pCorrStop;
							}
						}
					} else {
						//Msg("%d %d %d %d",(*eb).NumLine,OUTF1T(St),OUTF1T((*eb).dS),OUTF1T(Sr));
						// торможение до минимально скорости
						if (fmvc.Enable == 2) {
							if (*(fmvs.Vc) <= *(fmvc.Vmin)){
								Msg("CorrStop G1\r\n");
								fmvc.Enable = 0;
								Busy = 0;
								*pCorrStop = 1 ;
								BR_pCorrStop = 1;
							}
						} 
						if (*(fmvs.Vc) > *(fmvc.Vmin)) {
							*(fmvs.Vc) = *(fmvs.Vc) - dV; 
							if (*(fmvs.Vc) < *(fmvc.Vmin)) *(fmvs.Vc) = *(fmvc.Vmin); // ограничили снизу
						} 
					}
					// работа со скоростью
					fmvc.Vmax = *(fmvc.V)*(*(fmvc.Vmul)/100);
#ifdef MOVE_D
//					Msg("Sr %d Vc %d T %d Tb %d dV %d",OUTF1T(Sr),OUTF1T(*(fmvs.Vc)),T,(*eb).Tb,OUTF1T(dV));
					Msg("Sr %d Vc %d dV %d",OUTF1T(Sr),OUTF1T(*(fmvs.Vc)),OUTF1T(dV));
#endif

					// уход на следующую итерацию
					// запустить таймер на следующую итерацию
					TCS_SetInterval(tcs_FMove,fmvs.LPON);
				} //else ((*eb).Nomove) {	
			} // else (eb==NULL) {
		} //else (fmvc.Enable==0)  { 
	} else { // Level != 0
		// сброс всех импульсов
		QClrPin(MOTOR_X_STEP);
		QClrPin(MOTOR_Yl_STEP);
		QClrPin(MOTOR_Yr_STEP);
		QClrPin(MOTOR_Z_STEP);
		fmvs.Level = 0;
//		TCS_SetInterval(tcs_FMove,*(fmvc.LenOffPulse));
		// условие окончания движения
		if (((*eb).Xi==(*eb).Xdi)&&((*eb).Yi==(*eb).Ydi)&&((*eb).Zi==(*eb).Zdi)){
			//Msg("Vout %d\r\n",OUTF(*(fmvs.Vc)));
			if ((*eb).Nonstop) {
//							Msg("NS %d\r\n",(*eb).NumLine);
				eb = NULL;
				qbDelFirst();
				eb = qbFirstBlock();
				if (eb==NULL) {
					Msg("ebNull\r\n");
					fmvc.Enable = 0;
					Busy = 0;
					TCS_SetInterval(tcs_FMove,2500000);
				} else {
					*pCurCadr = (*eb).NumLine;
#ifdef MOVE_D					
					Msg("RI%d:G%d Xd %d Yd %d Zd %d NS %d\r\n",(*eb).NumLine,(*eb).sGo,OUTF1T((*eb).Xd),OUTF1T((*eb).Yd),OUTF1T((*eb).Zd),(*eb).Nonstop);
#endif		
					memcpy((void*)&(BR_pCurCadr),(void*)pCurCadr,4);
					if ((*eb).Nonstop) {
						TCS_SetInterval(tcs_FMove,fmvs.LPOFF); //???
					} else {
						(*pRCS)=rcsGetBlock;
						fmvc.Enable = 0;
						Busy = 0;
						TCS_SetInterval(tcs_FMove,2500000);
					}
				}
			} else {
//							Msg("ENS %d\r\n",(*eb).NumLine);
				*pRCS = rcsEndExecute; 	
				fmvc.Enable = 0;
				Busy = 0;
//							Msg("CorrStop G1_\r\n");
				*pCorrStop = 1;
				BR_pCorrStop = *pCorrStop;
				TCS_SetInterval(tcs_FMove,2500000);
			}
		} else {
			// двигаемся дальше
			TCS_SetInterval(tcs_FMove,fmvs.LPOFF); //???
		}
	} // Level == 0
}
*/
