#include "Defs.h"

//****************начало Motor_Y************************************
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
#define mulAY 1
// множтель ускорения при торможении во время позиционирования
#define mulAYP 1
// делитель скорости при позиционировании
#define divVYP 4
volatile TIMER_CONTROL_STRUCT tcs_MotorY; 	// структура управления таймером движения радиальным двигателем 
volatile TFMC 	mc_Y;
volatile TFMS 	ms_Y;
// флаг принудительного сброса сигнала step
u8 ClrSY = 0;

__inline void PositY(void){
	if (!((*ms_Z.Posit == 1)&&(*mc_Z.PositOn == 0))) return;
	// позиционирование по радиусу
	switch (*ms_Y.StagePos) {
		case 0: // движение к датчику
			QClrPin(MOTOR_Yl_DIR);
			QClrPin(MOTOR_Yr_DIR);
			if (QGetPin(SENS_MOTOR_Y)) {
				*ms_Y.StagePos = 1;
				Msg("StagePosY 1 Sensor Found\r\n");
			} else {
				*(mc_Y.FrReq)=*(mc_Y.FrMax);
				// движение с разгоном
				if (*(ms_Y.FrCur) < (*(mc_Y.FrReq)/divVYP)) {
//				if (*(ms_Y.FrCur) < (*(mc_Y.FrReq))) {
					// разгон до FrReq/2
					*(ms_Y.FrCur) += *(mc_Y.Accel) * (ms_Y.Tcur);
					if (*(ms_Y.FrCur) > (*(mc_Y.FrReq)/divVYP)) *(ms_Y.FrCur) = *(mc_Y.FrReq)/divVYP;
//					if (*(ms_Y.FrCur) > (*(mc_Y.FrReq))) *(ms_Y.FrCur) = *(mc_Y.FrReq);
					ms_Y.Tcur = Kb / (*(ms_Y.FrCur));
					ms_Y.LPOFF = CLPOFF(ms_Y.Tcur,ms_Y.LPON);		
				} 
				// ON_PULSE
				ms_Y.Level = 1;								
//				QSetPin(MOTOR_Yl_STEP);						
//				QSetPin(MOTOR_Yr_STEP);						
//				TCS_SetInterval(tcs_MotorY,ms_Y.LPON);		
			}
		break;
		case 1: // торможение и смена направления
			if (*(ms_Y.FrCur) <= *(mc_Y.FrMin)) {
				// смена направления
				QSetPin(MOTOR_Yl_DIR);
				QSetPin(MOTOR_Yr_DIR);
				*ms_Y.StagePos = 2;
				Msg("StagePosY 2 Break And Move Back\r\n");
			} else {
				// торможение
				if (*(ms_Y.FrCur) > *(mc_Y.Accel) * mulAYP * (ms_Y.Tcur))
					*(ms_Y.FrCur) -= *(mc_Y.Accel) * mulAYP * (ms_Y.Tcur);
				else *(ms_Y.FrCur) = 0;
				if (*(ms_Y.FrCur) < *(mc_Y.FrMin)) *(ms_Y.FrCur) = *(mc_Y.FrMin);
				ms_Y.Tcur = Kb / (*(ms_Y.FrCur));
				ms_Y.LPOFF = CLPOFF(ms_Y.Tcur,ms_Y.LPON);		
				// ON_PULSE
				ms_Y.Level = 1;								
//				QSetPin(MOTOR_Yl_STEP);						
//				QSetPin(MOTOR_Yr_STEP);						
//				TCS_SetInterval(tcs_MotorY,ms_Y.LPON);		
			}
		break;
		case 2:
			if (!QGetPin(SENS_MOTOR_Y)) {
				*ms_Y.StagePos = 3;
				*(ms_Y.Pos) = Y_MIN_POS;
				BR_ms_Y_Pos = *(ms_Y.Pos);

				*ms_Y.Posit = 1;
				*mc_Y.PositOn = 0;
				if ((*ms_X.Posit)&&(*ms_Z.Posit)) {
					*pCorrStop = 1;
					BR_pCorrStop = *pCorrStop;
				}
				Msg("StagePosY Complete %d\r\n",*pCorrStop);
			} else {
				// выход из датчика на малой скорости
				// ON_PULSE
				ms_Y.Level = 1;								
//				QSetPin(MOTOR_Yl_STEP);						
//				QSetPin(MOTOR_Yr_STEP);						
//				TCS_SetInterval(tcs_MotorY,ms_Y.LPON);		
			}
		break;
	}

}

__inline void MovePosY(void){
	if ((*(mc_Y.ReqPos) == *(ms_Y.Pos))) {
		*(mc_Y.MovePos) = 0;
		if ((*(mc_X.MovePos) == 0) && (*(mc_Z.MovePos) == 0)) {
			*pCorrStop = 1;
			BR_pCorrStop = *pCorrStop;
		}
		return;
	}
	if (*(mc_Y.ReqPos) < Y_MIN_POS) *(mc_Y.ReqPos)=Y_MIN_POS;
	if (*(mc_Y.ReqPos) > Y_MAX_POS) *(mc_Y.ReqPos)=Y_MAX_POS;
	// определяем направление
	if (*(mc_Y.MovePos) == 1) {
		if (((*(mc_Y.ReqPos) < *(ms_Y.Pos))&&(*(ms_Y.Dir)==1))||
		    ((*(mc_Y.ReqPos) > *(ms_Y.Pos))&&(*(ms_Y.Dir)==-1)))
		{
			// торможение и смена направления
			if (*(ms_Y.FrCur) > *(mc_Y.FrMin)) {
				// торможение
				if (*(ms_Y.FrCur) > *(mc_Y.Accel) * mulAY *(ms_Y.Tcur))
					*(ms_Y.FrCur) -= *(mc_Y.Accel) * mulAY * (ms_Y.Tcur);
				else *(ms_Y.FrCur) = 0;
				if (*(ms_Y.FrCur) < *(mc_Y.FrMin)) {
					*(ms_Y.FrCur) = *(mc_Y.FrMin);
					ms_Y.Lacc = 0;
				}	
				if (ms_Y.Lacc >= mulAY) ms_Y.Lacc-=mulAY; else ms_Y.Lacc = 0;
				ms_Y.Tcur = Kb / (*(ms_Y.FrCur));
				ms_Y.LPOFF = CLPOFF(ms_Y.Tcur,ms_Y.LPON);		
			} else {
				//смена направления
				if (*(ms_Y.Dir)==1) *(ms_Y.Dir)=-1;
				else *(ms_Y.Dir)=1;
				if (*(ms_Y.Dir)==1) {
				 	QSetPin(MOTOR_Yl_DIR);
				 	QSetPin(MOTOR_Yr_DIR);
				} else {
					QClrPin(MOTOR_Yl_DIR);
					QClrPin(MOTOR_Yr_DIR);
				}
//				Msg("DelayDirY\r\n");
//				TCS_SetInterval(tcs_MotorY,*pDirDelay);
//				return;
			}
		} else {
			// определяем зону
			if (abs(*(ms_Y.Pos)-*(mc_Y.ReqPos))<=(ms_Y.Lacc+10)) {
				// в зоне тормозим
				if (*(ms_Y.FrCur) > *(mc_Y.Accel) * mulAY * (ms_Y.Tcur)) 
					*(ms_Y.FrCur) -= *(mc_Y.Accel) * mulAY * (ms_Y.Tcur);
				else 	*(ms_Y.FrCur) = 0;
		
				if (*(ms_Y.FrCur) < *(mc_Y.FrMin)) {
					*(ms_Y.FrCur) = *(mc_Y.FrMin);
					ms_Y.Lacc = 0;
				}	
				if (ms_Y.Lacc >= mulAY) ms_Y.Lacc-=mulAY; else ms_Y.Lacc = 0;
				ms_Y.Tcur = Kb / (*(ms_Y.FrCur));
				ms_Y.LPOFF = CLPOFF(ms_Y.Tcur,ms_Y.LPON);		
			} else {
				// вне зоны едем с разгоном
				if (*(ms_Y.FrCur) < *(mc_Y.FrReq)) {
					*(ms_Y.FrCur) += *(mc_Y.Accel) * (ms_Y.Tcur);
					if (*(ms_Y.FrCur) > *(mc_Y.FrReq)) *(ms_Y.FrCur) = *(mc_Y.FrReq);
					ms_Y.Lacc++;
					ms_Y.Tcur = Kb / (*(ms_Y.FrCur));
					ms_Y.LPOFF = CLPOFF(ms_Y.Tcur,ms_Y.LPON);		
				}
			}
		}
	} else { // MovePos == 2
		// только торможение
		if (*(ms_Y.FrCur) > *(mc_Y.FrMin)) {
			if (*(ms_Y.FrCur) > *(mc_Y.Accel) * mulAY * (ms_Y.Tcur)) 
				*(ms_Y.FrCur) -= *(mc_Y.Accel) * mulAY * (ms_Y.Tcur);
			else 	*(ms_Y.FrCur) = 0;
	
			if (*(ms_Y.FrCur) < *(mc_Y.FrMin)) {
				*(ms_Y.FrCur) = *(mc_Y.FrMin);
				ms_Y.Lacc = 0;
			}	
			if (ms_Y.Lacc >= mulAY) ms_Y.Lacc-=mulAY; else ms_Y.Lacc = 0;
			ms_Y.Tcur = Kb / (*(ms_Y.FrCur));
			ms_Y.LPOFF = CLPOFF(ms_Y.Tcur,ms_Y.LPON);		
		} else {
			// и при доcтижении минимальной частоты MovePos = 0
			*(mc_Y.MovePos) = 0;
			if (!*pCorrStop) {
				// корректная остановка сброшена
				if ((!*(mc_X.MovePos))&&(!*(mc_Z.MovePos))) {
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
	ms_Y.Level = 1;								
	*(ms_Y.Pos)+=(*(ms_Y.Dir));
	BR_ms_Y_Pos = *(ms_Y.Pos);
//	QSetPin(MOTOR_Yl_STEP);						
//	QSetPin(MOTOR_Yr_STEP);						
//	TCS_SetInterval(tcs_MotorY,ms_Y.LPON);		
}

__inline void MoveBtnY(void){
	if 	(((!*(mc_Y.MoveBtn))&&(*(ms_Y.FrCur) <= *(mc_Y.FrMin))) || 
		(*(ms_Y.Pos) <= Y_MIN_POS)&&(*(mc_Y.ReqDir) == -1) ||
		(*(ms_Y.Pos) >= Y_MAX_POS)&&(*(mc_Y.ReqDir) == 1)) 

	{
		// условие окончания движения
		// переход в мониторинг
		ms_Y.Tcur = Kb / *(mc_Y.FrMin);
//		TCS_SetInterval(tcs_MotorY,2500000);
//			Msg("Mon ");
	} else {
		if (!*(mc_Y.MoveBtn)) {
			// торможение
			if (*(ms_Y.FrCur) > *(mc_Y.Accel) * mulAY * (ms_Y.Tcur))
				*(ms_Y.FrCur) -= *(mc_Y.Accel) * mulAY * (ms_Y.Tcur);
			else *(ms_Y.FrCur) = 0;			
			if (*(ms_Y.FrCur) < *(mc_Y.FrMin)) {
				*(ms_Y.FrCur) = *(mc_Y.FrMin);
				ms_Y.Lacc = 0;
			}	
			if (ms_Y.Lacc >= mulAY) ms_Y.Lacc-=mulAY; else ms_Y.Lacc = 0;
			ms_Y.Tcur = Kb / (*(ms_Y.FrCur));
			ms_Y.LPOFF = CLPOFF(ms_Y.Tcur,ms_Y.LPON);		
		} else {
			// Движение разрешено
			// Проверить текущую позицию на предмет подхода к границе поля 
			// на расстояние необходимое для торможения
			// торможение, изменение направления движения на необходимое
			// разгон и движение с постоянной скоростью
			if (*(ms_Y.Dir)!=*(mc_Y.ReqDir)) {
				// торможение и смена направления
				if (*(ms_Y.FrCur) > *(mc_Y.FrMin)) {
				   	// торможение
					if (*(ms_Y.FrCur) > *(mc_Y.Accel) * mulAY * (ms_Y.Tcur))
						*(ms_Y.FrCur) -= *(mc_Y.Accel) * mulAY * (ms_Y.Tcur);
					else *(ms_Y.FrCur) = 0;			
					if (*(ms_Y.FrCur) < *(mc_Y.FrMin)) {
						*(ms_Y.FrCur) = *(mc_Y.FrMin);
						ms_Y.Lacc = 0;
					}	
					if (ms_Y.Lacc >= mulAY) ms_Y.Lacc-=mulAY; else ms_Y.Lacc = 0;
					ms_Y.Tcur = Kb / (*(ms_Y.FrCur));
					ms_Y.LPOFF = CLPOFF(ms_Y.Tcur,ms_Y.LPON);		
				} else {
					// смена направления
					*(ms_Y.Dir)=*(mc_Y.ReqDir);
					if (*(ms_Y.Dir) == 1) {
						QSetPin(MOTOR_Yl_DIR);
						QSetPin(MOTOR_Yr_DIR);
					} else {
					 	QClrPin(MOTOR_Yl_DIR);
					 	QClrPin(MOTOR_Yr_DIR);
					}
//					Msg("DelayDirY\r\n");
//					TCS_SetInterval(tcs_MotorY,*pDirDelay);
//					return;
				}
			} else {
				// разгон и движение с постоянной скоростью
				if 	( 
						(((*(ms_Y.Pos)-(ms_Y.Lacc+10)) < Y_MIN_POS)&&(*(mc_Y.ReqDir) == -1)) ||
						(((*(ms_Y.Pos)+(ms_Y.Lacc+10)) > Y_MAX_POS)&&(*(mc_Y.ReqDir) == 1)) 
					)
				{
					// торможение
					if (*(ms_Y.FrCur) > *(mc_Y.Accel) * mulAY * (ms_Y.Tcur))
						*(ms_Y.FrCur) -= *(mc_Y.Accel) * mulAY * (ms_Y.Tcur);
					else *(ms_Y.FrCur) = 0;			
					if (*(ms_Y.FrCur) < *(mc_Y.FrMin)) {
						*(ms_Y.FrCur) = *(mc_Y.FrMin);
						ms_Y.Lacc = 0;
					}	
					if (ms_Y.Lacc >= mulAY) ms_Y.Lacc-=mulAY; else ms_Y.Lacc = 0;
					ms_Y.Tcur = Kb / (*(ms_Y.FrCur));
					ms_Y.LPOFF = CLPOFF(ms_Y.Tcur,ms_Y.LPON);		
				} else
				if (*(mc_Y.FrReq) < *(mc_Y.FrMin)) {
					// требуемая частота меньше минимальной
					// торможение FrCur до FrMin и переход на FrReq
//					Msg("FrReq < FrMin ");
					if (*(ms_Y.FrCur) > *(mc_Y.FrMin)) {
						// торможение
						if (*(ms_Y.FrCur) > *(mc_Y.Accel) * mulAY * (ms_Y.Tcur))
							*(ms_Y.FrCur) -= *(mc_Y.Accel) * mulAY * (ms_Y.Tcur);
						else *(ms_Y.FrCur) = 0;			
						if (*(ms_Y.FrCur) < *(mc_Y.FrMin)) *(ms_Y.FrCur) = *(mc_Y.FrMin);
						if (ms_Y.Lacc >= mulAY) ms_Y.Lacc-=mulAY; else ms_Y.Lacc = 0;
						if (*(ms_Y.FrCur) > *(mc_Y.FrMin)) {
							ms_Y.Tcur = Kb / (*(ms_Y.FrCur));
							ms_Y.LPOFF = CLPOFF(ms_Y.Tcur,ms_Y.LPON);		
						} else {
							// переход на FrReq
							*(ms_Y.FrCur) = *(mc_Y.FrReq);
							ms_Y.Tcur = Kb / (*(ms_Y.FrCur));
							ms_Y.LPOFF = CLPOFF(ms_Y.Tcur,ms_Y.LPON);		
						}
					} 
				} else {
					// требуемая частота больше или равна минимальной
//					Msg("FrReq >= FrMin ");
					// движение с FrReq
					if (*(ms_Y.FrCur) < *(mc_Y.FrReq)) {
						// разгон до FrReq
						*(ms_Y.FrCur) += *(mc_Y.Accel) * ms_Y.Tcur;
						ms_Y.Lacc++;
						if (*(ms_Y.FrCur) > *(mc_Y.FrReq)) *(ms_Y.FrCur) = *(mc_Y.FrReq);
						ms_Y.Tcur = Kb / (*(ms_Y.FrCur));
						ms_Y.LPOFF = CLPOFF(ms_Y.Tcur,ms_Y.LPON);		
//							Msg("Acc To FrReq ");
					} else
					if (*(ms_Y.FrCur) > *(mc_Y.FrReq)) {
						// торможение до FrReq
						if (*(ms_Y.FrCur) > *(mc_Y.Accel) * mulAY * (ms_Y.Tcur))
							*(ms_Y.FrCur) -= *(mc_Y.Accel) * mulAY * (ms_Y.Tcur);
						else *(ms_Y.FrCur) = 0;			
						if (ms_Y.Lacc >= mulAY) ms_Y.Lacc-=mulAY; else ms_Y.Lacc = 0;
						if (*(ms_Y.FrCur) < *(mc_Y.FrReq)) *(ms_Y.FrCur) = *(mc_Y.FrReq);
						ms_Y.Tcur = Kb / (*(ms_Y.FrCur));
						ms_Y.LPOFF = CLPOFF(ms_Y.Tcur,ms_Y.LPON);		
//							Msg("Dec To FrReq ");
					} 
				}
			}
		}
		//ON_PULSE;
		*(ms_Y.Pos)+=*(ms_Y.Dir);							
		BR_ms_Y_Pos = *(ms_Y.Pos);
		ms_Y.Level = 1;								
//		QSetPin(MOTOR_Yl_STEP);						
//		QSetPin(MOTOR_Yr_STEP);	
//		TCS_SetInterval(tcs_MotorY,ms_Y.LPON);		
		//Msg("Pos %d Lacc %d ",ms_Y.Pos, ms_Y.Lacc);
	}

}

void	MotorY_Handler(void){
	CHECKLPOFF(ms_Y.LPOFF);	
	if (ms_Y.Level==0) {
		if ((fmvc.Enable==0)&&(ClrF==0))  { 
			// защита от нулевого направления
			if (*(ms_Y.Dir) == 0) {
				Msg("YD0\r\n");
				if (QGetPin(MOTOR_Yl_DIR)) *(ms_Y.Dir) = 1;
				else *(ms_Y.Dir)=-1;
			}
			ClrSY = 0;
			// конец пассивного импульса или начало движение
			if (*mc_Y.PositOn && (!(*ms_Y.Posit))) {
				PositY();
			} else
			if (*(mc_Y.MovePos)) 
				MovePosY();
			else
				MoveBtnY();
			if (ms_Y.Level) {
				ClrSY = 1; 
				// вариант с прямой логикой
				//QSetPin(MOTOR_Y_STEP);	
				//TCS_SetInterval(tcs_MotorY,ms_X.LPON);		
				// *** вариант с обратной логикой
				QClrPin(MOTOR_Yl_STEP);	
				QClrPin(MOTOR_Yr_STEP);	
				TCS_SetInterval(tcs_MotorY,ms_Y.LPOFF);		
			} else {
				QClrPin(MOTOR_Yl_STEP);	
				QClrPin(MOTOR_Yr_STEP);	
				TCS_SetInterval(tcs_MotorY,ms_Y.LPOFF);		
			}	
		} else {
				// мониторинг
				if (ClrSY) {
					QClrPin(MOTOR_Yl_STEP);	
					QClrPin(MOTOR_Yr_STEP);	
					ClrSY = 0;
				}
				TCS_SetInterval(tcs_MotorY,2500000);		
		}	
	} else {
		// конец активного исмпульса
		//OFF_PULSE;
		ms_Y.Level = 0;								
		QSetPin(MOTOR_Yl_STEP);						
		QSetPin(MOTOR_Yr_STEP);						
		TCS_SetInterval(tcs_MotorY,ms_Y.LPON);		
	}
}

//****************конец Motor_Y*************************************


