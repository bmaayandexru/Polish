#include "Defs.h"

//****************начало Motor_Z************************************
#include <stdlib.h>
#include "Motors.h"
#include "Motor_X.h"
#include "Motor_Y.h"
#include "Motor_Z.h"
#include "VirtualPins.h"
#include "VPFrz.h"
#include "Timers.h"
#include "msg.h"
#include "Tools.h"

#include "FreqInvr.h"

// множтель ускорения при торможении
#define mulAZ 1
// множтель ускорения при торможении во время позиционирования
#define mulAZP 2
// делитель скорости при позиционировании
#define divVZP 2
volatile TIMER_CONTROL_STRUCT tcs_MotorZ; 	// структура управления таймером движения радиальным двигателем 
volatile TFMC 	mc_Z;
volatile TFMS 	ms_Z;
// флаг принудительного сброса сигнала step
u8 ClrSZ = 0;

__inline void PositZ(void){
	// позиционирование по радиусу
	switch (*ms_Z.StagePos) {
		case 0: // движение к датчику
			QSetPin(MOTOR_Z_DIR);
			//Msg("0");
			if (QGetPin(SENS_MOTOR_Z)) {
				*ms_Z.StagePos = 1;
				Msg("StagePosZ 1 Sensor Found\r\n");
			} else {
				*(mc_Z.FrReq)=*(mc_Z.FrMax);
				// движение с разгоном
				if (*(ms_Z.FrCur) < (*(mc_Z.FrReq)/divVZP)) {
					// разгон до FrReq
					*(ms_Z.FrCur) += *(mc_Z.Accel) * (ms_Z.Tcur);
					if (*(ms_Z.FrCur) > (*(mc_Z.FrReq)/divVZP)) *(ms_Z.FrCur) = (*(mc_Z.FrReq)/divVZP);
					ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
					ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
				} 
				// ON_PULSE
				ms_Z.Level = 1;								
//				QSetPin(MOTOR_Z_STEP);						
//				TCS_SetInterval(tcs_MotorZ,ms_Z.LPON);		
			}
		break;
		case 1: // торможение и смена направления
			if (*(ms_Z.FrCur) <= *(mc_Z.FrMin)) {
				// смена направления
				QClrPin(MOTOR_Z_DIR);
				*ms_Z.StagePos = 2;
				Msg("StagePosZ 2 Break And Move Back\r\n");
			} else {
				// торможение
				if (*(ms_Z.FrCur) > *(mc_Z.Accel) * mulAZP * (ms_Z.Tcur))
					*(ms_Z.FrCur) -= *(mc_Z.Accel) * mulAZP * (ms_Z.Tcur);
				else *(ms_Z.FrCur) = 0; 
				if (*(ms_Z.FrCur) < *(mc_Z.FrMin)) *(ms_Z.FrCur) = *(mc_Z.FrMin);
				ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
				ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
				// ON_PULSE
				ms_Z.Level = 1;								
//				QSetPin(MOTOR_Z_STEP);						
//				TCS_SetInterval(tcs_MotorZ,ms_Z.LPON);		
			}
		break;
		case 2:
			if (!QGetPin(SENS_MOTOR_Z)) {
				*ms_Z.StagePos = 3;
				*(ms_Z.Pos) = Z_MAX_POS;
				BR_ms_Z_Pos = *(ms_Z.Pos);
				*ms_Z.Posit = 1;
				*mc_Z.PositOn = 0;
				if ((*ms_X.Posit)&&(*ms_Y.Posit)) {
					*pCorrStop = 1;
					BR_pCorrStop = *pCorrStop;
				}
				Msg("StagePosZ Complete %d\r\n",*pCorrStop);
			} else {
				// выход из датчика на малой скорости
				// ON_PULSE
				ms_Z.Level = 1;								
//				QSetPin(MOTOR_Z_STEP);						
//				TCS_SetInterval(tcs_MotorZ,ms_Z.LPON);		
			}
		break;
	}

}
__inline void MovePosZ(void){
	if ((*(mc_Z.ReqPos) == *(ms_Z.Pos))) {
		*(mc_Z.MovePos) = 0;
		if ((*(mc_X.MovePos) == 0) && (*(mc_Y.MovePos) == 0)) {
			*pCorrStop = 1;
			BR_pCorrStop = *pCorrStop;
		}
		return;
	}
	if (*(mc_Z.ReqPos) < Z_MIN_POS) *(mc_Z.ReqPos)=Z_MIN_POS;
	if (*(mc_Z.ReqPos) > Z_MAX_POS) *(mc_Z.ReqPos)=Z_MAX_POS;
	// определяем направление
//	Msg("aDir %d RD %d\r\n",*(ms_Z.Dir),*(mc_Z.ReqDir));
	if (*(mc_Z.MovePos) == 1) {
		if (((*(mc_Z.ReqPos) < *(ms_Z.Pos))&&(*(ms_Z.Dir)==1))||
		    ((*(mc_Z.ReqPos) > *(ms_Z.Pos))&&(*(ms_Z.Dir)==-1)))
		{
	//		Msg("a");
			// торможение и смена направления
			if (*(ms_Z.FrCur) > *(mc_Z.FrMin)) {
	//			Msg("b");
				// торможение
				if (*(ms_Z.FrCur) > *(mc_Z.Accel) * mulAZ * (ms_Z.Tcur))
					*(ms_Z.FrCur) -= *(mc_Z.Accel) * mulAZ * (ms_Z.Tcur);
				else *(ms_Z.FrCur) = 0; 
				if (*(ms_Z.FrCur) < *(mc_Z.FrMin)) {
					*(ms_Z.FrCur) = *(mc_Z.FrMin);
					ms_Z.Lacc = 0;
				}	
				if (ms_Z.Lacc >= mulAZ) ms_Z.Lacc -= mulAZ; else ms_Z.Lacc = 0;
				ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
				ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
			} else {
	//			Msg("c");
				//смена направления
				if (*(ms_Z.Dir)==1) *(ms_Z.Dir)=-1;
				else *(ms_Z.Dir)=1;
				if (*(ms_Z.Dir)==1) QSetPin(MOTOR_Z_DIR);
				else QClrPin(MOTOR_Z_DIR);
				// задержка на смену направления
//				Msg("DelayDirZ\r\n");
//				TCS_SetInterval(tcs_MotorZ,*pDirDelay);
//				return;
			}
		} else {
	//		Msg("d");
			// определяем зону
			if (abs(*(ms_Z.Pos)-*(mc_Z.ReqPos))<=(ms_Z.Lacc+10)) {
	//			Msg("e");
				// в зоне тормозим
				if (*(ms_Z.FrCur) > *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur))
					*(ms_Z.FrCur) -= *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur);
				else *(ms_Z.FrCur) = 0; 
				if (*(ms_Z.FrCur) < *(mc_Z.FrMin)) *(ms_Z.FrCur) = *(mc_Z.FrMin);
				if (ms_Z.Lacc >= mulAZ) ms_Z.Lacc -= mulAZ; else ms_Z.Lacc = 0;
				ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
				ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
			} else {
	//			Msg("f");
				// вне зоны едем с разгоном
				if (*(ms_Z.FrCur) < *(mc_Z.FrReq)) {
	//				Msg("g");
					*(ms_Z.FrCur) += *(mc_Z.Accel) * (ms_Z.Tcur);
					if (*(ms_Z.FrCur) > *(mc_Z.FrReq)) *(ms_Z.FrCur) = *(mc_Z.FrReq);
					ms_Z.Lacc++;
					ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
					ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);	
	///				Msg("Dir %d\r\n",*(ms_Z.Dir));
				}
			}
		}
	} else { // MovePos == 2
		// только торможение
		if (*(ms_Z.FrCur) > *(mc_Z.FrMin)) {
				if (*(ms_Z.FrCur) > *(mc_Z.Accel)*mulAZ * (ms_Z.Tcur))
					*(ms_Z.FrCur) -= *(mc_Z.Accel)*mulAZ * (ms_Z.Tcur);
				else *(ms_Z.FrCur) = 0; 
				if (*(ms_Z.FrCur) < *(mc_Z.FrMin)) *(ms_Z.FrCur) = *(mc_Z.FrMin);
				if (ms_Z.Lacc >= mulAZ) ms_Z.Lacc -= mulAZ; else ms_Z.Lacc = 0;
				ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
				ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
		} else {
			// и при доcтижении минимальной частоты MovePos = 0
			*(mc_Z.MovePos) = 0;
			if (!*pCorrStop) {
				// корректная остановка сброшена
				if ((!*(mc_Y.MovePos))&&(!*(mc_X.MovePos))) {
					Msg("CorrStop G0\r\n");
					*pCorrStop = 1;
					BR_pCorrStop = *pCorrStop;
					// поднять Z на максимум
					*(mc_Z.ReqPos) = Z_MAX_POS;
					*(mc_Z.MovePos) = 1;
					// остановить шпиндель и выключить охлаждение
					FIStop();		QClrPin(COOLER1); QClrPin(COOLER2); 
				}
			}
			return;
		}

	}
//	Msg("h");
	//ON_PULSE;
	*(ms_Z.Pos)+=(*(ms_Z.Dir));
	BR_ms_Z_Pos = *(ms_Z.Pos);
	ms_Z.Level = 1;								
//	QSetPin(MOTOR_Z_STEP);						
//	TCS_SetInterval(tcs_MotorZ,ms_Z.LPON);		
//	Msg("RP %d P %d D %d OFF %d ON %d T %d\r\n",*(mc_Z.ReqPos),*(ms_Z.Pos),*(ms_Z.Dir),ms_Z.LPON,ms_Z.LPOFF,ms_Z.Tcur);
}

__inline void MoveBtnZ(void){
	//Msg("BX");
	if 	(((!*(mc_Z.MoveBtn))&&(*(ms_Z.FrCur) <= *(mc_Z.FrMin))) || 
		(*(ms_Z.Pos) <= Z_MIN_POS)&&(*(mc_Z.ReqDir) == -1) ||
		(*(ms_Z.Pos) >= Z_MAX_POS)&&(*(mc_Z.ReqDir) == 1)) 
	{
		// условие окончания движения
		// переход в мониторинг
		ms_Z.Tcur = Kb / *(mc_Z.FrMin);
//		TCS_SetInterval(tcs_MotorZ,2500000);
//		Msg("BXM");
	} else {
		if (!*(mc_Z.MoveBtn)) {
			// торможение
			if (*(ms_Z.FrCur) > *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur))
				*(ms_Z.FrCur) -= *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur);
			else *(ms_Z.FrCur) = 0; 
			if (*(ms_Z.FrCur) < *(mc_Z.FrMin)) *(ms_Z.FrCur) = *(mc_Z.FrMin);
			if (ms_Z.Lacc >= mulAZ) ms_Z.Lacc -= mulAZ; else ms_Z.Lacc = 0;
			ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
			ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
		} else {
			// Движение разрешено
			// Проверить текущую позицию на предмет подхода к границе поля 
			// на расстояние необходимое для торможения
			// торможение, изменение направления движения на необходимое
			// разгон и движение с постоянной скоростью
			if (*(ms_Z.Dir)!=*(mc_Z.ReqDir)) {
				// торможение и смена направления
				if (*(ms_Z.FrCur) > *(mc_Z.FrMin)) {
				   	// торможение
					if (*(ms_Z.FrCur) > *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur))
						*(ms_Z.FrCur) -= *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur);
					else *(ms_Z.FrCur) = 0; 
					if (*(ms_Z.FrCur) < *(mc_Z.FrMin)) *(ms_Z.FrCur) = *(mc_Z.FrMin);
					if (ms_Z.Lacc >= mulAZ) ms_Z.Lacc -= mulAZ; else ms_Z.Lacc = 0;
					ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
					ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
				} else {
					// смена направления
					*(ms_Z.Dir)=*(mc_Z.ReqDir);
					if (*(ms_Z.Dir) == 1) QSetPin(MOTOR_Z_DIR);
					else QClrPin(MOTOR_Z_DIR);
//					// задержка на смену направления
//					Msg("DelayDirZ\r\n");
//					TCS_SetInterval(tcs_MotorZ,*pDirDelay);
//					return;
				}
			} else {
				// разгон и движение с постоянной скоростью
				if 	( 
						(((*(ms_Z.Pos)-(ms_Z.Lacc+10)) < Z_MIN_POS)&&(*(mc_Z.ReqDir) == -1)) ||
						(((*(ms_Z.Pos)+(ms_Z.Lacc+10)) > Z_MAX_POS)&&(*(mc_Z.ReqDir) == 1)) 
					)
				{
					// торможение
					if (*(ms_Z.FrCur) > *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur))
						*(ms_Z.FrCur) -= *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur);
					else *(ms_Z.FrCur) = 0; 
					if (*(ms_Z.FrCur) < *(mc_Z.FrMin)) *(ms_Z.FrCur) = *(mc_Z.FrMin);
					ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
					if (ms_Z.Lacc >= mulAZ) ms_Z.Lacc -= mulAZ; else ms_Z.Lacc = 0;
					ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
				} else
				if (*(mc_Z.FrReq) < *(mc_Z.FrMin)) {
					// требуемая частота меньше минимальной
					// торможение FrCur до FrMin и переход на FrReq
					if (*(ms_Z.FrCur) > *(mc_Z.FrMin)) {
						// торможение
						if (*(ms_Z.FrCur) > *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur))
							*(ms_Z.FrCur) -= *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur);
						else *(ms_Z.FrCur) = 0; 
						if (*(ms_Z.FrCur) < *(mc_Z.FrMin)) *(ms_Z.FrCur) = *(mc_Z.FrMin);
						if (ms_Z.Lacc >= mulAZ) ms_Z.Lacc -= mulAZ; else ms_Z.Lacc = 0;
						if (*(ms_Z.FrCur) > *(mc_Z.FrMin)) {
							ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
							ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
						} else {
							// переход на FrReq
							*(ms_Z.FrCur) = *(mc_Z.FrReq);
							ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
							ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
						}
					} 
				} else {
					// требуемая частота больше или равна минимальной
					// движение с FrReq
					if (*(ms_Z.FrCur) < *(mc_Z.FrReq)) {
						// разгон до FrReq
						*(ms_Z.FrCur) += *(mc_Z.Accel) * ms_Z.Tcur;
						ms_Z.Lacc++;
						if (*(ms_Z.FrCur) > *(mc_Z.FrReq)) *(ms_Z.FrCur) = *(mc_Z.FrReq);
						ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
						ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
					} else
					if (*(ms_Z.FrCur) > *(mc_Z.FrReq)) {
						// торможение до FrReq
						if (*(ms_Z.FrCur) > *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur))
							*(ms_Z.FrCur) -= *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur);
						else *(ms_Z.FrCur) = 0; 
						if (ms_Z.Lacc >= mulAZ) ms_Z.Lacc -= mulAZ; else ms_Z.Lacc = 0;
						if (*(ms_Z.FrCur) < *(mc_Z.FrReq)) *(ms_Z.FrCur) = *(mc_Z.FrReq);
						ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
						ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
					} 
				}
			}
		}
		ms_Z.Level = 1;								
		*(ms_Z.Pos)+=*(ms_Z.Dir);							
		BR_ms_Z_Pos = *(ms_Z.Pos);
//		QSetPin(MOTOR_Z_STEP);	
//		TCS_SetInterval(tcs_MotorZ,ms_Z.LPON);		
	}

}

void	MotorZ_Handler(void){
	CHECKLPOFF(ms_Z.LPOFF);
	if (ms_Z.Level==0) {
		if ((fmvc.Enable==0)&&(ClrF==0))  { 
			// защита от нулевого направления !!!!
			if (*(ms_Z.Dir) == 0) {
				Msg("ZD0\r\n");
				if (QGetPin(MOTOR_Z_DIR)) *(ms_Z.Dir) = 1;
				else *(ms_Z.Dir)=-1;
			}
			ClrSZ = 0;
			// конец пассивного импульса или начало движение
			if (*mc_Z.PositOn && (!(*ms_Z.Posit))) {
				PositZ();
			} else 
			if (*(mc_Z.MovePos)) 
				MovePosZ();
			else
				MoveBtnZ();
			if (ms_Z.Level) {
				ClrSZ = 1; 
				// вариант с прямой логикой
				//QSetPin(MOTOR_Z_STEP);	
				//TCS_SetInterval(tcs_MotorZ,ms_Z.LPON);		
				// *** вариант с обратной логикой
				QClrPin(MOTOR_Z_STEP);	
				TCS_SetInterval(tcs_MotorZ,ms_Z.LPOFF);		
			} else {
				QClrPin(MOTOR_Z_STEP);	
				TCS_SetInterval(tcs_MotorZ,ms_Z.LPOFF);		
			}	
		} else {
				// мониторинг
				if (ClrSZ) {
					// вариант с обратной логикой
					QClrPin(MOTOR_Z_STEP);
					ClrSZ = 0;
				}
				TCS_SetInterval(tcs_MotorZ,2500000);		
		}	
	} else {
		// конец активного исмпульса
		//OFF_PULSE;
		ms_Z.Level = 0;		
		// вариант с прямой логикой
		//QClrPin(MOTOR_Z_STEP);	
		//TCS_SetInterval(tcs_MotorZ,ms_Z.LPOFF);	
		// *** вариант с обратной логикой
		QSetPin(MOTOR_Z_STEP);				
		TCS_SetInterval(tcs_MotorZ,ms_Z.LPON);		
		
	}
}


//****************конец Motor_Z*************************************


