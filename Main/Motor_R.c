#include "Defs.h"

#ifdef __SAW__
//****************������ Motor_R************************************
#include <stdlib.h>
#include "Motors.h"
#include "Motor_R.h"
#include "VirtualPins.h"
#include "VPSaw.h"
#include "Timers.h"
#include "msg.h"


TIMER_CONTROL_STRUCT tcs_MotorR; 	// ��������� ���������� �������� �������� ���������� ���������� 
TMC 	mc_R;
TMS 	ms_R;

__inline void  PositR(void) {
	// ���������������� �� �������
	switch (*ms_R.StagePos) {
		case 0: // �������� � �������
			QSetPin(MOTOR_R_DIR);
			if (QGetPin(SENS_MOTOR_R)) {
				*ms_R.StagePos = 1;
				Msg("StagePosR 1 Sensor Found\r\n");
			} else {
				// �������� � ��������
				if (*(ms_R.FrCur) < *(mc_R.FrReq)) {
					// ������ �� FrReq
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
		case 1: // ���������� � ����� �����������
			if (*(ms_R.FrCur) <= *(mc_R.FrMin)) {
				// ����� �����������
				QClrPin(MOTOR_R_DIR);
				*ms_R.StagePos = 2;
				Msg("StagePosR 2 Break And Move Back\r\n");
			} else {
				// ����������
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
				// ���������� � backup ��������
				BR_ms_R_Pos = *(ms_R.Pos);
				*ms_R.Dir = -1;
				*ms_R.Posit = 1;
				*mc_R.PositOn = 0;
				Msg("StagePosR Complete\r\n");
			} else {
				// ����� �� ������� �� ����� ��������
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
	// ���������� �����������
	if (((*(mc_R.ReqPos) < *(ms_R.Pos))&&(*(ms_R.Dir)==1))||
	    ((*(mc_R.ReqPos) > *(ms_R.Pos))&&(*(ms_R.Dir)==-1)))
	{
		// ���������� � ����� �����������
		if (*(ms_R.FrCur) > *(mc_R.FrMin)) {
			// ����������
			*(ms_R.FrCur) -= *(mc_R.Accel) * (ms_R.Tcur);
			if (*(ms_R.FrCur) < *(mc_R.FrMin)) *(ms_R.FrCur) = *(mc_R.FrMin);
			if (ms_R.Lacc) ms_R.Lacc--;
			ms_R.Tcur = Kb / (*(ms_R.FrCur));
			ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
		} else {
			//����� �����������
			if (*(ms_R.Dir)==1) *(ms_R.Dir)=-1;
			else *(ms_R.Dir)=1;
			if (*(ms_R.Dir)==1) QSetPin(MOTOR_R_DIR);
			else QClrPin(MOTOR_R_DIR);
		}
	} else {
		// ���������� ����
		if (abs(*(ms_R.Pos)-*(mc_R.ReqPos))<=(ms_R.Lacc+10)) {
			// � ���� ��������
			*(ms_R.FrCur) -= *(mc_R.Accel) * (ms_R.Tcur);
			if (*(ms_R.FrCur) < *(mc_R.FrMin)) *(ms_R.FrCur) = *(mc_R.FrMin);
			if (ms_R.Lacc) ms_R.Lacc--;
			ms_R.Tcur = Kb / (*(ms_R.FrCur));
			ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
		} else {
			// ��� ���� ���� � ��������
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
	// ���������� � backup-��������
	BR_ms_R_Pos = *(ms_R.Pos);
	TCS_SetInterval(tcs_MotorR,ms_R.LPON);		
}

__inline void MoveBtnR(void) {
	if 	(((!*(mc_R.MoveBtn))&&(*(ms_R.FrCur) <= *(mc_R.FrMin))) || 
		(*(ms_R.Pos) <= R_MIN_POS)&&(*(mc_R.ReqDir) == -1) ||
		(*(ms_R.Pos) >= R_MAX_POS)&&(*(mc_R.ReqDir) == 1)) 

	{
		// ������� ��������� ��������
		// ������� � ����������
		ms_R.Tcur = Kb / *(mc_R.FrMin);
		TCS_SetInterval(tcs_MotorR,ms_R.Tcur);
//			Msg("Mon ");
	} else {
		if (!*(mc_R.MoveBtn)) {
			// ����������
			*(ms_R.FrCur) -= *(mc_R.Accel) * (ms_R.Tcur);
			if (ms_R.Lacc) ms_R.Lacc--;
			ms_R.Tcur = Kb / (*(ms_R.FrCur));
			ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
		} else {
			// �������� ���������
			// ��������� ������� ������� �� ������� ������� � ������� ���� 
			// �� ���������� ����������� ��� ����������
			// ����������, ��������� ����������� �������� �� �����������
			// ������ � �������� � ���������� ���������
			if (*(ms_R.Dir)!=*(mc_R.ReqDir)) {
				// ���������� � ����� �����������
				if (*(ms_R.FrCur) > *(mc_R.FrMin)) {
				   	// ����������
					*(ms_R.FrCur) -= *(mc_R.Accel) * ms_R.Tcur;
					if (ms_R.Lacc) ms_R.Lacc--;
					ms_R.Tcur = Kb / (*(ms_R.FrCur));
					ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
				} else {
					// ����� �����������
					*(ms_R.Dir)=*(mc_R.ReqDir);
					if (*(ms_R.Dir) == 1) QSetPin(MOTOR_R_DIR);
					else QClrPin(MOTOR_R_DIR);
				}
			} else {
				// ������ � �������� � ���������� ���������
				if 	( 
						(((*(ms_R.Pos)-(ms_R.Lacc+10)) < R_MIN_POS)&&(*(mc_R.ReqDir) == -1)) ||
						(((*(ms_R.Pos)+(ms_R.Lacc+10)) > R_MAX_POS)&&(*(mc_R.ReqDir) == 1)) 
					)
				{
					// ����������
					*(ms_R.FrCur) -= *(mc_R.Accel) * ms_R.Tcur;
					if (*(ms_R.FrCur) < *(mc_R.FrMin)) *(ms_R.FrCur) = *(mc_R.FrMin);
					ms_R.Tcur = Kb / (*(ms_R.FrCur));
					if (ms_R.Lacc) ms_R.Lacc--;
					ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
				} else
				if (*(mc_R.FrReq) < *(mc_R.FrMin)) {
					// ��������� ������� ������ �����������
					// ���������� FrCur �� FrMin � ������� �� FrReq
//					Msg("FrReq < FrMin ");
					if (*(ms_R.FrCur) > *(mc_R.FrMin)) {
						// ����������
						*(ms_R.FrCur) -= *(mc_R.Accel) * ms_R.Tcur;
						if (ms_R.Lacc) ms_R.Lacc--;
						if (*(ms_R.FrCur) > *(mc_R.FrMin)) {
							ms_R.Tcur = Kb / (*(ms_R.FrCur));
							ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
						} else {
							// ������� �� FrReq
							*(ms_R.FrCur) = *(mc_R.FrReq);
							ms_R.Tcur = Kb / (*(ms_R.FrCur));
							ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
						}
					} 
				} else {
					// ��������� ������� ������ ��� ����� �����������
//					Msg("FrReq >= FrMin ");
					// �������� � FrReq
					if (*(ms_R.FrCur) < *(mc_R.FrReq)) {
						// ������ �� FrReq
						*(ms_R.FrCur) += *(mc_R.Accel) * ms_R.Tcur;
						ms_R.Lacc++;
						if (*(ms_R.FrCur) > *(mc_R.FrReq)) *(ms_R.FrCur) = *(mc_R.FrReq);
						ms_R.Tcur = Kb / (*(ms_R.FrCur));
						ms_R.LPOFF = ms_R.Tcur - ms_R.LPON;		
//							Msg("Acc To FrReq ");
					} else
					if (*(ms_R.FrCur) > *(mc_R.FrReq)) {
						// ���������� �� FrReq
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
		// ���������� � backup-��������
		BR_ms_R_Pos = *(ms_R.Pos);
		TCS_SetInterval(tcs_MotorR,ms_R.LPON);		
		//Msg("Pos %d Lacc %d ",ms_R.Pos, ms_R.Lacc);
	}
}

void	MotorR_Handler(void){
	if (!ms_R.Level) {
		// ����� ���������� �������� ��� ������ ��������
		if (*mc_R.PositOn && (!(*ms_R.Posit))) {
			PositR();
		} else
		if (*(mc_R.MovePos)) 
			MovePosR();
		else
			MoveBtnR();
	} else {
		// ����� ��������� ���������
		//OFF_PULSE;
		ms_R.Level = 0;								
		QClrPin(MOTOR_R_STEP);						
		TCS_SetInterval(tcs_MotorR,ms_R.LPOFF);		
	}
}
//****************����� Motor_R*************************************
#endif
// #ifdef __SAW__
