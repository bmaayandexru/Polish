#include "Defs.h"

//****************начало Motor_X************************************
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
#define mulAX 1
// множитель ускорения при торможении во время позиционирования
#define mulAXP 1

// делитель скорости при позиционировании
#define divVXP 4

volatile TIMER_CONTROL_STRUCT tcs_MotorX; 	// структура управления таймером движения радиальным двигателем 
volatile TFMC 	mc_X;
volatile TFMS 	ms_X;
// флаг принудительного сброса сигнала step
u8 ClrSX = 0;

__inline void PositX(void){
	if (!((*ms_Z.Posit == 1)&&(*mc_Z.PositOn == 0))) return;
	// позиционирование по радиусу
	switch (*ms_X.StagePos) {
		case 0: // движение к датчику
			QSetPin(MOTOR_X_DIR);
			if (QGetPin(SENS_MOTOR_X)) {
				*ms_X.StagePos = 1;
				Msg("StagePosX 1 Sensor Found\r\n");
			} else {
				*(mc_X.FrReq)=*(mc_X.FrMax);
				// движение с разгоном
				if (*(ms_X.FrCur) < (*(mc_X.FrReq)/divVXP)) {
//				if (*(ms_X.FrCur) < (*(mc_X.FrReq))) {
					// разгон до FrReq / 2
					*(ms_X.FrCur) += *(mc_X.Accel) * (ms_X.Tcur);
					if (*(ms_X.FrCur) > (*(mc_X.FrReq)/divVXP)) *(ms_X.FrCur) = *(mc_X.FrReq)/divVXP;
//					if (*(ms_X.FrCur) > (*(mc_X.FrReq))) *(ms_X.FrCur) = *(mc_X.FrReq);
					ms_X.Tcur = Kb / (*(ms_X.FrCur));
					ms_X.LPOFF = CLPOFF(ms_X.Tcur,ms_X.LPON);		
				} 
				// ON_PULSE
				ms_X.Level = 1;								
//				QSetPin(MOTOR_X_STEP);						
//				TCS_SetInterval(tcs_MotorX,ms_X.LPON);		
			}
		break;
		case 1: // торможение и смена направления
			if (*(ms_X.FrCur) <= *(mc_X.FrMin)) {
				// смена направления
				QClrPin(MOTOR_X_DIR);
				*ms_X.StagePos = 2;
				Msg("StagePosX 2 Break And Move Back\r\n");
			} else {
				// торможение
				if (*(ms_X.FrCur) > *(mc_X.Accel) * mulAXP * (ms_X.Tcur))
					*(ms_X.FrCur) -= *(mc_X.Accel) * mulAXP * (ms_X.Tcur);
				else *(ms_X.FrCur) = 0; 
				if (*(ms_X.FrCur) < *(mc_X.FrMin)) *(ms_X.FrCur) = *(mc_X.FrMin);
				ms_X.Tcur = Kb / (*(ms_X.FrCur));
				ms_X.LPOFF = CLPOFF(ms_X.Tcur,ms_X.LPON);		
				// ON_PULSE
				ms_X.Level = 1;								
//				QSetPin(MOTOR_X_STEP);						
//				TCS_SetInterval(tcs_MotorX,ms_X.LPON);		
			}
		break;
		case 2:
			if (!QGetPin(SENS_MOTOR_X)) {
				*ms_X.StagePos = 3;
				*(ms_X.Pos) = X_MAX_POS;
				BR_ms_X_Pos = *(ms_X.Pos);
				*ms_X.Posit = 1;
				*mc_X.PositOn = 0;
				if ((*ms_Y.Posit)&&(*ms_Z.Posit)) {
					Msg("CorrStop G0\r\n");
					*pCorrStop = 1;
					BR_pCorrStop = *pCorrStop;
				}
				Msg("StagePosX Complete %d\r\n", *pCorrStop);
			} else {
				// выход из датчика на малой скорости
				// ON_PULSE
				ms_X.Level = 1;								
//				QSetPin(MOTOR_X_STEP);						
//				TCS_SetInterval(tcs_MotorX,ms_X.LPON);		
			}
		break;
	}
}

__inline void MovePosX(void){
	if ((*(mc_X.ReqPos) == *(ms_X.Pos))) {
		*(mc_X.MovePos) = 0;
		if ((*(mc_Y.MovePos) == 0) && (*(mc_Z.MovePos) == 0)) {
			*pCorrStop = 1;
			BR_pCorrStop = *pCorrStop;
		}
		return;
	}
	if (*(mc_X.ReqPos) < X_MIN_POS) *(mc_X.ReqPos)=X_MIN_POS;
	if (*(mc_X.ReqPos) > X_MAX_POS) *(mc_X.ReqPos)=X_MAX_POS;
	if (*(mc_X.MovePos) == 1) {
		// определяем направление
		if (((*(mc_X.ReqPos) < *(ms_X.Pos))&&(*(ms_X.Dir)==1))||
		    ((*(mc_X.ReqPos) > *(ms_X.Pos))&&(*(ms_X.Dir)==-1)))
		{
			// торможение и смена направления
			if (*(ms_X.FrCur) > *(mc_X.FrMin)) {
				// торможение
				if (*(ms_X.FrCur) > *(mc_X.Accel) * mulAX * (ms_X.Tcur))
					*(ms_X.FrCur) -= *(mc_X.Accel) * mulAX * (ms_X.Tcur);
				else *(ms_X.FrCur) = 0; 
				if (*(ms_X.FrCur) < *(mc_X.FrMin)) {
					*(ms_X.FrCur) = *(mc_X.FrMin);
					ms_X.Lacc = 0;
				}
				if (ms_X.Lacc >= mulAX) ms_X.Lacc -= mulAX; else ms_X.Lacc = 0;
//				if (ms_X.Lacc) ms_X.Lacc--;
				ms_X.Tcur = Kb / (*(ms_X.FrCur));
				ms_X.LPOFF = CLPOFF(ms_X.Tcur,ms_X.LPON);		
			} else {
				//смена направления
				if (*(ms_X.Dir)==1) *(ms_X.Dir)=-1;
				else *(ms_X.Dir)=1;
				if (*(ms_X.Dir)==1) QSetPin(MOTOR_X_DIR);
				else QClrPin(MOTOR_X_DIR);
				// задержка на смену направления для прямой логики
//				Msg("DelayDirX\r\n");
//				TCS_SetInterval(tcs_MotorX,*pDirDelay);
//				return;
			}
		} else {
			// определяем зону
			if (abs(*(ms_X.Pos)-*(mc_X.ReqPos))<=(ms_X.Lacc+10)) {
				// в зоне тормозим
				if (*(ms_X.FrCur) > *(mc_X.Accel) * mulAX * (ms_X.Tcur))
					*(ms_X.FrCur) -= *(mc_X.Accel) * mulAX * (ms_X.Tcur);
				else *(ms_X.FrCur) = 0; 
				if (*(ms_X.FrCur) < *(mc_X.FrMin)) {
					*(ms_X.FrCur) = *(mc_X.FrMin);
					ms_X.Lacc = 0;
				}
				if (ms_X.Lacc >= mulAX) ms_X.Lacc -= mulAX; else ms_X.Lacc = 0;
				ms_X.Tcur = Kb / (*(ms_X.FrCur));
				ms_X.LPOFF = CLPOFF(ms_X.Tcur,ms_X.LPON);		
			} else {
				// вне зоны едем с разгоном
				if (*(ms_X.FrCur) < *(mc_X.FrReq)) {
					*(ms_X.FrCur) += *(mc_X.Accel) * (ms_X.Tcur);
					if (*(ms_X.FrCur) > *(mc_X.FrReq)) *(ms_X.FrCur) = *(mc_X.FrReq);
					ms_X.Lacc++;
					ms_X.Tcur = Kb / (*(ms_X.FrCur));
					ms_X.LPOFF = CLPOFF(ms_X.Tcur,ms_X.LPON);		
				}
			}
		}
	} else { // MovePos == 2
		// только торможение
		if (*(ms_X.FrCur) > *(mc_X.FrMin)) {
			// торможение
			if (*(ms_X.FrCur) > *(mc_X.Accel) * mulAX * (ms_X.Tcur))
				*(ms_X.FrCur) -= *(mc_X.Accel) * mulAX * (ms_X.Tcur);
			else *(ms_X.FrCur) = 0; 
			if (*(ms_X.FrCur) < *(mc_X.FrMin)) {
				*(ms_X.FrCur) = *(mc_X.FrMin);
				ms_X.Lacc = 0;
			}
			if (ms_X.Lacc >= mulAX) ms_X.Lacc -= mulAX; else ms_X.Lacc = 0;
			ms_X.Tcur = Kb / (*(ms_X.FrCur));
			ms_X.LPOFF = CLPOFF(ms_X.Tcur,ms_X.LPON);		
		} else {
			// и при доcтижении минимальной частоты MovePos = 0
			*(mc_X.MovePos) = 0;
			if (!*pCorrStop) {
				// корректная остановка сброшена
				if ((!*(mc_Y.MovePos))&&(!*(mc_Z.MovePos))) {
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
	//ON_PULSE;
	*(ms_X.Pos)+=(*(ms_X.Dir));
	BR_ms_X_Pos = *(ms_X.Pos);
	ms_X.Level = 1;								
//	QSetPin(MOTOR_X_STEP);						
//	TCS_SetInterval(tcs_MotorX,ms_X.LPON);		
}

__inline void MoveBtnX(void){
	//Msg("BX");
	if 	(((!*(mc_X.MoveBtn))&&(*(ms_X.FrCur) <= *(mc_X.FrMin))) || 
		(*(ms_X.Pos) <= X_MIN_POS)&&(*(mc_X.ReqDir) == -1) ||
		(*(ms_X.Pos) >= X_MAX_POS)&&(*(mc_X.ReqDir) == 1)) 

	{
		// условие окончания движения
		// переход в мониторинг
		ms_X.Tcur = Kb / *(mc_X.FrMin);
//		TCS_SetInterval(tcs_MotorX,2500000);
//		Msg("BXM");
	} else {
		if (!*(mc_X.MoveBtn)) {
			// торможение
			if (*(ms_X.FrCur) > *(mc_X.Accel) * mulAX * (ms_X.Tcur))
				*(ms_X.FrCur) -= *(mc_X.Accel) * mulAX * (ms_X.Tcur);
			else *(ms_X.FrCur) = 0; 
			if (*(ms_X.FrCur) < *(mc_X.FrMin)) {
				*(ms_X.FrCur) = *(mc_X.FrMin);
				ms_X.Lacc = 0;
			}
			if (ms_X.Lacc >= mulAX) ms_X.Lacc -= mulAX; else ms_X.Lacc = 0;
			ms_X.Tcur = Kb / (*(ms_X.FrCur));
			ms_X.LPOFF = CLPOFF(ms_X.Tcur,ms_X.LPON);		
		} else {
			// Движение разрешено
			// Проверить текущую позицию на предмет подхода к границе поля 
			// на расстояние необходимое для торможения
			// торможение, изменение направления движения на необходимое
			// разгон и движение с постоянной скоростью
			if (*(ms_X.Dir)!=*(mc_X.ReqDir)) {
				// торможение и смена направления
				if (*(ms_X.FrCur) > *(mc_X.FrMin)) {
				   	// торможение
					if (*(ms_X.FrCur) > *(mc_X.Accel) * mulAX * (ms_X.Tcur))
						*(ms_X.FrCur) -= *(mc_X.Accel) * mulAX * (ms_X.Tcur);
					else *(ms_X.FrCur) = 0; 
					if (*(ms_X.FrCur) < *(mc_X.FrMin)) {
						*(ms_X.FrCur) = *(mc_X.FrMin);
						ms_X.Lacc = 0;
					}
					if (ms_X.Lacc >= mulAX) ms_X.Lacc -= mulAX; else ms_X.Lacc = 0;
					ms_X.Tcur = Kb / (*(ms_X.FrCur));
					ms_X.LPOFF = CLPOFF(ms_X.Tcur,ms_X.LPON);		
				} else {
					// смена направления
					*(ms_X.Dir)=*(mc_X.ReqDir);
					if (*(ms_X.Dir) == 1) QSetPin(MOTOR_X_DIR);
					else QClrPin(MOTOR_X_DIR);
					// для прямой логики
//					Msg("DelayDirX\r\n");
//					TCS_SetInterval(tcs_MotorX,*pDirDelay);
//					return;
				}
			} else {
				// разгон и движение с постоянной скоростью
				if 	( 
						(((*(ms_X.Pos)-(ms_X.Lacc+10)) < X_MIN_POS)&&(*(mc_X.ReqDir) == -1)) ||
						(((*(ms_X.Pos)+(ms_X.Lacc+10)) > X_MAX_POS)&&(*(mc_X.ReqDir) == 1)) 
					)
				{
					// торможение
					if (*(ms_X.FrCur) > *(mc_X.Accel) * mulAX * (ms_X.Tcur))
						*(ms_X.FrCur) -= *(mc_X.Accel) * mulAX * (ms_X.Tcur);
					else *(ms_X.FrCur) = 0; 

					if (*(ms_X.FrCur) < *(mc_X.FrMin)) {
						*(ms_X.FrCur) = *(mc_X.FrMin);
						ms_X.Lacc = 0;
					}
					if (ms_X.Lacc >= mulAX) ms_X.Lacc -= mulAX; else ms_X.Lacc = 0;
					ms_X.Tcur = Kb / (*(ms_X.FrCur));
					ms_X.LPOFF = CLPOFF(ms_X.Tcur,ms_X.LPON);		
				} else
				if (*(mc_X.FrReq) < *(mc_X.FrMin)) {
					// требуемая частота меньше минимальной
					// торможение FrCur до FrMin и переход на FrReq
//					Msg("FrReq < FrMin ");
					if (*(ms_X.FrCur) > *(mc_X.FrMin)) {
						// торможение
						if (*(ms_X.FrCur) > *(mc_X.Accel) * mulAX * (ms_X.Tcur))
							*(ms_X.FrCur) -= *(mc_X.Accel) * mulAX * (ms_X.Tcur);
						else *(ms_X.FrCur) = 0; 
						if (*(ms_X.FrCur) < *(mc_X.FrMin)) *(ms_X.FrCur) = *(mc_X.FrMin);
						if (ms_X.Lacc >= mulAX) ms_X.Lacc -= mulAX; else ms_X.Lacc = 0;
						if (*(ms_X.FrCur) > *(mc_X.FrMin)) {
							ms_X.Tcur = Kb / (*(ms_X.FrCur));
							ms_X.LPOFF = CLPOFF(ms_X.Tcur,ms_X.LPON);		
						} else {
							// переход на FrReq
							*(ms_X.FrCur) = *(mc_X.FrReq);
							ms_X.Tcur = Kb / (*(ms_X.FrCur));
							ms_X.LPOFF = CLPOFF(ms_X.Tcur,ms_X.LPON);		
						}
					} 
				} else {
					// требуемая частота больше или равна минимальной
//					Msg("FrReq >= FrMin ");
					// движение с FrReq
					if (*(ms_X.FrCur) < *(mc_X.FrReq)) {
						// разгон до FrReq
						*(ms_X.FrCur) += *(mc_X.Accel) * ms_X.Tcur;
						ms_X.Lacc++;
						if (*(ms_X.FrCur) > *(mc_X.FrReq)) *(ms_X.FrCur) = *(mc_X.FrReq);
						ms_X.Tcur = Kb / (*(ms_X.FrCur));
						ms_X.LPOFF = CLPOFF(ms_X.Tcur,ms_X.LPON);		
//							Msg("Acc To FrReq ");
					} else
					if (*(ms_X.FrCur) > *(mc_X.FrReq)) {
						// торможение до FrReq
						if (*(ms_X.FrCur) > *(mc_X.Accel) * mulAX * (ms_X.Tcur))
							*(ms_X.FrCur) -= *(mc_X.Accel) * mulAX * (ms_X.Tcur);
						else *(ms_X.FrCur) = 0; 
						if (ms_X.Lacc >= mulAX) ms_X.Lacc -= mulAX; else ms_X.Lacc = 0;
						if (*(ms_X.FrCur) < *(mc_X.FrReq)) *(ms_X.FrCur) = *(mc_X.FrReq);
						ms_X.Tcur = Kb / (*(ms_X.FrCur));
						ms_X.LPOFF = CLPOFF(ms_X.Tcur,ms_X.LPON);		
//							Msg("Dec To FrReq ");
					} 
				}
			}
		}
		//ON_PULSE;
		//Msg("XON");
		*(ms_X.Pos)+=*(ms_X.Dir);							
		BR_ms_X_Pos = *(ms_X.Pos);
		ms_X.Level = 1;								
//		QSetPin(MOTOR_X_STEP);	
//		TCS_SetInterval(tcs_MotorX,ms_X.LPON);		
//		Msg("Pos %d Lacc %d ",*(ms_X.Pos), ms_X.Lacc);
	}
}
// тест
//void	MotorX_Handler(void){
//static u8 f=0;
//static u32 c=0;
////	TCS_SetInterval(tcs_MotorX,5000);		
//	// 5000 - 1 сек
//	// 
//	if (c<3000000) {
//		if (f) QSetPin(MOTOR_X_STEP);
//		else QClrPin(MOTOR_X_STEP);		
//		f=1-f;
//		c++;
//	}	
//}

void	MotorX_Handler(void){
	CHECKLPOFF(ms_X.LPOFF);
	if (ms_X.Level == 0) {
		if ((fmvc.Enable == 0)&&(ClrF==0))  { 
			// защита от нулевого направления
			if (*(ms_X.Dir) == 0) {
				Msg("XD0\r\n");
				if (QGetPin(MOTOR_X_DIR)) *(ms_X.Dir) = 1;
				else *(ms_X.Dir)=-1;
			}
			// если будем менять логику
			ClrSX = 0;
			// конец пассивного импульса или начало движение
			if (*mc_X.PositOn && (!(*ms_X.Posit))) {
				PositX();
			} else
			if (*(mc_X.MovePos)) 
				MovePosX();
			else {
				MoveBtnX();
			}
			if (ms_X.Level) {
				ClrSX = 1; 
				// вариант с прямой логикой
				//QSetPin(MOTOR_X_STEP);	
				//TCS_SetInterval(tcs_MotorX,ms_X.LPON);		
				// *** вариант с обратной логикой
				Q1ClrPin(MOTOR_X_STEP);	
				TCS_SetInterval(tcs_MotorX,ms_X.LPOFF);		
			} else {
				Q1ClrPin(MOTOR_X_STEP);	
				TCS_SetInterval(tcs_MotorX,ms_X.LPOFF);		
			}	
		} else {
				// мониторинг
				if (ClrSX) {
					// вариант с обратной логикой
					Q1ClrPin(MOTOR_X_STEP);
					ClrSX = 0;
				}
				TCS_SetInterval(tcs_MotorX,2500000);		
		}	
	} else {
		// конец активного исмпульса
		//OFF_PULSE;
		//Msg("XOFF");
		ms_X.Level = 0;
		// вариант с прямой логикой
		//QClrPin(MOTOR_X_STEP);				
		//TCS_SetInterval(tcs_MotorX,ms_X.LPOFF);		
		// *** вариант с обратной логикой
		Q1SetPin(MOTOR_X_STEP);				
		TCS_SetInterval(tcs_MotorX,ms_X.LPON);		
	}
}

/*
// НЕ СТИРАТЬ !!!! РАБОЧИЙ ВАРИАНТ!!!!
void	MotorX_Handler(void){
	//Msg("X");
	if (fmvc.Enable==0)  { 
		CHECKLPOFF(ms_X.LPOFF);
		if (!ms_X.Level) {
			// защита от нулевого направления
			if (*(ms_X.Dir) == 0) {
				Msg("XD0\r\n");
				if (QGetPin(MOTOR_X_DIR)) *(ms_X.Dir) = 1;
				else *(ms_X.Dir)=-1;
			}
			// конец пассивного импульса или начало движение
			if (*mc_X.PositOn && (!(*ms_X.Posit))) {
				PositX();
			} else
			if (*(mc_X.MovePos)) 
				MovePosX();
			else {
				MoveBtnX();
			}
		} else {
			// конец активного исмпульса
			//OFF_PULSE;
			//Msg("XOFF");
			ms_X.Level = 0;								
			QClrPin(MOTOR_X_STEP);						
			TCS_SetInterval(tcs_MotorX,ms_X.LPOFF);		
		}
	} else {
			// мониторинг
			TCS_SetInterval(tcs_MotorX,250000);		
	}	
}
*/
//****************конец Motor_X*************************************


