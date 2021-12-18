#include "Defs.h"

#ifdef __SAW__
//****************начало Motor_R************************************
#include <stdlib.h>
#include "Motors.h"
#include "Motor_R.h"
#include "VirtualPins.h"
#include "VPSaw.h"
#include "Timers.h"
#include "msg.h"


TIMER_CONTROL_STRUCT tcs_MotorR; 	// структура управления таймером движения радиальным двигателем 
TMC 	mc_R;
TMS 	ms_R;

__inline void  PositR(void) {
	// позиционирование по радиусу
	switch (*ms_R.StagePos) {
		case 0: // движение к датчику
			QSetPin(MOTOR_R_DIR);
			if (QGetPin(SENS_MOTOR_R)) {
				*ms_R.StagePos = 1;
				Msg("StagePosR 1 Sensor Found\r\n");
			} else {
				// движение с разгоном
				if (*(ms_R.FrCur) < *(mc_R.FrReq)) {
					// разгон до FrReq
					*(ms_R.FrCur) += *(mc_R.Accel) * (ms_R.Tcur);
					if (*(ms_R.FrCur) > *(mc_R.FrReq)) *(ms_R.FrCur) = *(mc_R.FrReq);
					ms_R.Tcur = Kb / (*(ms_R.FrCur));
					ms_R.LPOFF = (ms_R.Tcur) - ms_R.LPON;		
				} 
				// ON_PULSE
				ms_R.Level = 1;								
				QSetPin(MOTOR_R_STEP);						
				TCS_SetInterval(tcs_MotorR,ms_R.LPON);		
			}
		break;
		case 1: // торможение и смена направления
			if (*(ms_R.FrCur) <= *(mc_R.FrMin)) {
				// смена направления
				QClrPin(MOTOR_R_DIR);
				*ms_R.StagePos = 2;
				Msg("StagePosR 2 Break And Move Back\r\n");
			} else {
				// торможение
				*(ms_R.FrCur) -= *(mc_R.Accel) * (ms_R.Tcur);
				if (*(ms_R.FrCur) < *(mc_R.FrMin)) *(ms_R.FrCur) = *(mc_R.FrMin);
				ms_R.Tcur = Kb / (*(ms_R.FrCur));
				ms_R.LPOFF = (ms_R.Tcur) - ms_R.LPON;		
				// ON_PULSE
				ms_R.Level = 1;								
				QSetPin(MOTOR_R_STEP);						
				TCS_SetInterval(tcs_MotorR,ms_R.LPON);		
			}
		break;
		case 2:
			if (!QGetPin(SENS_MOTOR_R)) {
				QClrPin(MOTOR_R_DIR);
				*ms_R.StagePos = 3;
				*(ms_R.Pos) = R_MAX_POS;
				// сохранение в backup регистре
				BR_ms_R_Pos = *(ms_R.Pos);
				*ms_R.Dir = -1;
				*ms_R.Posit = 1;
				*mc_R.PositOn = 0;
				Msg("StagePosR Complete\r\n");
			} else {
				// выход из датчика на малой скорости
				// ON_PULSE
				ms_R.Level = 1;								
				QSetPin(MOTOR_R_STEP);						
				TCS_SetInterval(tcs_MotorR,ms_R.LPON);		
			}
		break;
	}
}

__inline void MovePosR(void) {
	if ((*(mc_R.ReqPos) == *(ms_R.Pos))) {
		*(mc_R.MovePos) = 0;
		//if (*(mc_A.MovePos) == 0) Busy = 0;
		return;
	}
	if (*(mc_R.ReqPos) < R_MIN_POS) *(mc_R.ReqPos)=R_MIN_POS;
	if (*(mc_R.ReqPos) > R_MAX_POS) *(mc_R.ReqPos)=R_MAX_POS;
	// определяем направление
	if (((*(mc_R.ReqPos) < *(ms_R.Pos))&&(*(ms_R.Dir)==1))||
	    ((*(mc_R.ReqPos) > *(ms_R.Pos))&&(*(ms_R.Dir)==-1)))
	{
		// торможение и смена направления
		if (*(ms_R.FrCur) > *(mc_R.FrMin)) {
			// торможение
			*(ms_R.FrCur) -= *(mc_R.Accel) * (ms_R.Tcur);
			if (*(ms_R.FrCur) < *(mc_R.FrMin)) *(ms_R.FrCur) = *(mc_R.FrMin);
			if (ms_R.Lacc) ms_R.Lacc--;
			ms_R.Tcur = Kb / (*(ms_R.FrCur));
			ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
		} else {
			//смена направления
			if (*(ms_R.Dir)==1) *(ms_R.Dir)=-1;
			else *(ms_R.Dir)=1;
			if (*(ms_R.Dir)==1) QSetPin(MOTOR_R_DIR);
			else QClrPin(MOTOR_R_DIR);
		}
	} else {
		// определяем зону
		if (abs(*(ms_R.Pos)-*(mc_R.ReqPos))<=(ms_R.Lacc+10)) {
			// в зоне тормозим
			*(ms_R.FrCur) -= *(mc_R.Accel) * (ms_R.Tcur);
			if (*(ms_R.FrCur) < *(mc_R.FrMin)) *(ms_R.FrCur) = *(mc_R.FrMin);
			if (ms_R.Lacc) ms_R.Lacc--;
			ms_R.Tcur = Kb / (*(ms_R.FrCur));
			ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
		} else {
			// вне зоны едем с разгоном
			if (*(ms_R.FrCur) < *(mc_R.FrReq)) {
				*(ms_R.FrCur) += *(mc_R.Accel) * (ms_R.Tcur);
				if (*(ms_R.FrCur) > *(mc_R.FrReq)) *(ms_R.FrCur) = *(mc_R.FrReq);
				ms_R.Lacc++;
				ms_R.Tcur = Kb / (*(ms_R.FrCur));
				ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
			}
		}
	}
	//ON_PULSE;
	ms_R.Level = 1;								
	QSetPin(MOTOR_R_STEP);						
	*(ms_R.Pos)+=(*(ms_R.Dir));
	// сохранение в backup-регистре
	BR_ms_R_Pos = *(ms_R.Pos);
	TCS_SetInterval(tcs_MotorR,ms_R.LPON);		
}

__inline void MoveBtnR(void) {
	if 	(((!*(mc_R.MoveBtn))&&(*(ms_R.FrCur) <= *(mc_R.FrMin))) || 
		(*(ms_R.Pos) <= R_MIN_POS)&&(*(mc_R.ReqDir) == -1) ||
		(*(ms_R.Pos) >= R_MAX_POS)&&(*(mc_R.ReqDir) == 1)) 

	{
		// условие окончания движения
		// переход в мониторинг
		ms_R.Tcur = Kb / *(mc_R.FrMin);
		TCS_SetInterval(tcs_MotorR,ms_R.Tcur);
//			Msg("Mon ");
	} else {
		if (!*(mc_R.MoveBtn)) {
			// торможение
			*(ms_R.FrCur) -= *(mc_R.Accel) * (ms_R.Tcur);
			if (ms_R.Lacc) ms_R.Lacc--;
			ms_R.Tcur = Kb / (*(ms_R.FrCur));
			ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
		} else {
			// Движение разрешено
			// Проверить текущую позицию на предмет подхода к границе поля 
			// на расстояние необходимое для торможения
			// торможение, изменение направления движения на необходимое
			// разгон и движение с постоянной скоростью
			if (*(ms_R.Dir)!=*(mc_R.ReqDir)) {
				// торможение и смена направления
				if (*(ms_R.FrCur) > *(mc_R.FrMin)) {
				   	// торможение
					*(ms_R.FrCur) -= *(mc_R.Accel) * ms_R.Tcur;
					if (ms_R.Lacc) ms_R.Lacc--;
					ms_R.Tcur = Kb / (*(ms_R.FrCur));
					ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
				} else {
					// смена направления
					*(ms_R.Dir)=*(mc_R.ReqDir);
					if (*(ms_R.Dir) == 1) QSetPin(MOTOR_R_DIR);
					else QClrPin(MOTOR_R_DIR);
				}
			} else {
				// разгон и движение с постоянной скоростью
				if 	( 
						(((*(ms_R.Pos)-(ms_R.Lacc+10)) < R_MIN_POS)&&(*(mc_R.ReqDir) == -1)) ||
						(((*(ms_R.Pos)+(ms_R.Lacc+10)) > R_MAX_POS)&&(*(mc_R.ReqDir) == 1)) 
					)
				{
					// торможение
					*(ms_R.FrCur) -= *(mc_R.Accel) * ms_R.Tcur;
					if (*(ms_R.FrCur) < *(mc_R.FrMin)) *(ms_R.FrCur) = *(mc_R.FrMin);
					ms_R.Tcur = Kb / (*(ms_R.FrCur));
					if (ms_R.Lacc) ms_R.Lacc--;
					ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
				} else
				if (*(mc_R.FrReq) < *(mc_R.FrMin)) {
					// требуемая частота меньше минимальной
					// торможение FrCur до FrMin и переход на FrReq
//					Msg("FrReq < FrMin ");
					if (*(ms_R.FrCur) > *(mc_R.FrMin)) {
						// торможение
						*(ms_R.FrCur) -= *(mc_R.Accel) * ms_R.Tcur;
						if (ms_R.Lacc) ms_R.Lacc--;
						if (*(ms_R.FrCur) > *(mc_R.FrMin)) {
							ms_R.Tcur = Kb / (*(ms_R.FrCur));
							ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
						} else {
							// переход на FrReq
							*(ms_R.FrCur) = *(mc_R.FrReq);
							ms_R.Tcur = Kb / (*(ms_R.FrCur));
							ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
						}
					} 
				} else {
					// требуемая частота больше или равна минимальной
//					Msg("FrReq >= FrMin ");
					// движение с FrReq
					if (*(ms_R.FrCur) < *(mc_R.FrReq)) {
						// разгон до FrReq
						*(ms_R.FrCur) += *(mc_R.Accel) * ms_R.Tcur;
						ms_R.Lacc++;
						if (*(ms_R.FrCur) > *(mc_R.FrReq)) *(ms_R.FrCur) = *(mc_R.FrReq);
						ms_R.Tcur = Kb / (*(ms_R.FrCur));
						ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
//							Msg("Acc To FrReq ");
					} else
					if (*(ms_R.FrCur) > *(mc_R.FrReq)) {
						// торможение до FrReq
						*(ms_R.FrCur) -= *(mc_R.Accel) * ms_R.Tcur;
						if (ms_R.Lacc) ms_R.Lacc--;
						if (*(ms_R.FrCur) < *(mc_R.FrReq)) *(ms_R.FrCur) = *(mc_R.FrReq);
						ms_R.Tcur = Kb / (*(ms_R.FrCur));
						ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
//							Msg("Dec To FrReq ");
					} 
				}
			}
		}
		//ON_PULSE;
		ms_R.Level = 1;								
		QSetPin(MOTOR_R_STEP);						
		*(ms_R.Pos)+=*(ms_R.Dir);
		// сохранение в backup-регистре
		BR_ms_R_Pos = *(ms_R.Pos);
		TCS_SetInterval(tcs_MotorR,ms_R.LPON);		
		//Msg("Pos %d Lacc %d ",ms_R.Pos, ms_R.Lacc);
	}
}

void	MotorR_Handler(void){
	if (!ms_R.Level) {
		// конец пассивного импульса или начало движение
		if (*mc_R.PositOn && (!(*ms_R.Posit))) {
			PositR();
		} else
		if (*(mc_R.MovePos)) 
			MovePosR();
		else
			MoveBtnR();
	} else {
		// конец активного исмпульса
		//OFF_PULSE;
		ms_R.Level = 0;								
		QClrPin(MOTOR_R_STEP);						
		TCS_SetInterval(tcs_MotorR,ms_R.LPOFF);		
	}
}
//****************конец Motor_R*************************************
#endif
// #ifdef __SAW__
