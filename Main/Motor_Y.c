#include "Defs.h"

//****************������ Motor_Y************************************
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

// �������� ��������� ��� ����������
#define mulAY 1
// �������� ��������� ��� ���������� �� ����� ����������������
#define mulAYP 1
// �������� �������� ��� ����������������
#define divVYP 4
volatile TIMER_CONTROL_STRUCT tcs_MotorY; 	// ��������� ���������� �������� �������� ���������� ���������� 
volatile TFMC 	mc_Y;
volatile TFMS 	ms_Y;
// ���� ��������������� ������ ������� step
u8 ClrSY = 0;

__inline void PositY(void){
	if (!((*ms_Z.Posit == 1)&&(*mc_Z.PositOn == 0))) return;
	// ���������������� �� �������
	switch (*ms_Y.StagePos) {
		case 0: // �������� � �������
			QClrPin(MOTOR_Yl_DIR);
			QClrPin(MOTOR_Yr_DIR);
			if (QGetPin(SENS_MOTOR_Y)) {
				*ms_Y.StagePos = 1;
				Msg("StagePosY 1 Sensor Found\r\n");
			} else {
				*(mc_Y.FrReq)=*(mc_Y.FrMax);
				// �������� � ��������
				if (*(ms_Y.FrCur) < (*(mc_Y.FrReq)/divVYP)) {
//				if (*(ms_Y.FrCur) < (*(mc_Y.FrReq))) {
					// ������ �� FrReq/2
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
		case 1: // ���������� � ����� �����������
			if (*(ms_Y.FrCur) <= *(mc_Y.FrMin)) {
				// ����� �����������
				QSetPin(MOTOR_Yl_DIR);
				QSetPin(MOTOR_Yr_DIR);
				*ms_Y.StagePos = 2;
				Msg("StagePosY 2 Break And Move Back\r\n");
			} else {
				// ����������
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
				// ����� �� ������� �� ����� ��������
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
	// ���������� �����������
	if (*(mc_Y.MovePos) == 1) {
		if (((*(mc_Y.ReqPos) < *(ms_Y.Pos))&&(*(ms_Y.Dir)==1))||
		    ((*(mc_Y.ReqPos) > *(ms_Y.Pos))&&(*(ms_Y.Dir)==-1)))
		{
			// ���������� � ����� �����������
			if (*(ms_Y.FrCur) > *(mc_Y.FrMin)) {
				// ����������
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
				//����� �����������
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
			// ���������� ����
			if (abs(*(ms_Y.Pos)-*(mc_Y.ReqPos))<=(ms_Y.Lacc+10)) {
				// � ���� ��������
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
				// ��� ���� ���� � ��������
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
		// ������ ����������
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
			// � ��� ��c������� ����������� ������� MovePos = 0
			*(mc_Y.MovePos) = 0;
			if (!*pCorrStop) {
				// ���������� ��������� ��������
				if ((!*(mc_X.MovePos))&&(!*(mc_Z.MovePos))) {
					*pCorrStop = 1;
					BR_pCorrStop = *pCorrStop;
					// ������� Z �� ��������
					*(mc_Z.ReqPos) = Z_MAX_POS;
					*(mc_Z.MovePos) = 1;
					// ���������� �������� � ��������� ����������
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
		// ������� ��������� ��������
		// ������� � ����������
		ms_Y.Tcur = Kb / *(mc_Y.FrMin);
//		TCS_SetInterval(tcs_MotorY,2500000);
//			Msg("Mon ");
	} else {
		if (!*(mc_Y.MoveBtn)) {
			// ����������
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
			// �������� ���������
			// ��������� ������� ������� �� ������� ������� � ������� ���� 
			// �� ���������� ����������� ��� ����������
			// ����������, ��������� ����������� �������� �� �����������
			// ������ � �������� � ���������� ���������
			if (*(ms_Y.Dir)!=*(mc_Y.ReqDir)) {
				// ���������� � ����� �����������
				if (*(ms_Y.FrCur) > *(mc_Y.FrMin)) {
				   	// ����������
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
					// ����� �����������
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
				// ������ � �������� � ���������� ���������
				if 	( 
						(((*(ms_Y.Pos)-(ms_Y.Lacc+10)) < Y_MIN_POS)&&(*(mc_Y.ReqDir) == -1)) ||
						(((*(ms_Y.Pos)+(ms_Y.Lacc+10)) > Y_MAX_POS)&&(*(mc_Y.ReqDir) == 1)) 
					)
				{
					// ����������
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
					// ��������� ������� ������ �����������
					// ���������� FrCur �� FrMin � ������� �� FrReq
//					Msg("FrReq < FrMin ");
					if (*(ms_Y.FrCur) > *(mc_Y.FrMin)) {
						// ����������
						if (*(ms_Y.FrCur) > *(mc_Y.Accel) * mulAY * (ms_Y.Tcur))
							*(ms_Y.FrCur) -= *(mc_Y.Accel) * mulAY * (ms_Y.Tcur);
						else *(ms_Y.FrCur) = 0;			
						if (*(ms_Y.FrCur) < *(mc_Y.FrMin)) *(ms_Y.FrCur) = *(mc_Y.FrMin);
						if (ms_Y.Lacc >= mulAY) ms_Y.Lacc-=mulAY; else ms_Y.Lacc = 0;
						if (*(ms_Y.FrCur) > *(mc_Y.FrMin)) {
							ms_Y.Tcur = Kb / (*(ms_Y.FrCur));
							ms_Y.LPOFF = CLPOFF(ms_Y.Tcur,ms_Y.LPON);		
						} else {
							// ������� �� FrReq
							*(ms_Y.FrCur) = *(mc_Y.FrReq);
							ms_Y.Tcur = Kb / (*(ms_Y.FrCur));
							ms_Y.LPOFF = CLPOFF(ms_Y.Tcur,ms_Y.LPON);		
						}
					} 
				} else {
					// ��������� ������� ������ ��� ����� �����������
//					Msg("FrReq >= FrMin ");
					// �������� � FrReq
					if (*(ms_Y.FrCur) < *(mc_Y.FrReq)) {
						// ������ �� FrReq
						*(ms_Y.FrCur) += *(mc_Y.Accel) * ms_Y.Tcur;
						ms_Y.Lacc++;
						if (*(ms_Y.FrCur) > *(mc_Y.FrReq)) *(ms_Y.FrCur) = *(mc_Y.FrReq);
						ms_Y.Tcur = Kb / (*(ms_Y.FrCur));
						ms_Y.LPOFF = CLPOFF(ms_Y.Tcur,ms_Y.LPON);		
//							Msg("Acc To FrReq ");
					} else
					if (*(ms_Y.FrCur) > *(mc_Y.FrReq)) {
						// ���������� �� FrReq
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
			// ������ �� �������� �����������
			if (*(ms_Y.Dir) == 0) {
				Msg("YD0\r\n");
				if (QGetPin(MOTOR_Yl_DIR)) *(ms_Y.Dir) = 1;
				else *(ms_Y.Dir)=-1;
			}
			ClrSY = 0;
			// ����� ���������� �������� ��� ������ ��������
			if (*mc_Y.PositOn && (!(*ms_Y.Posit))) {
				PositY();
			} else
			if (*(mc_Y.MovePos)) 
				MovePosY();
			else
				MoveBtnY();
			if (ms_Y.Level) {
				ClrSY = 1; 
				// ������� � ������ �������
				//QSetPin(MOTOR_Y_STEP);	
				//TCS_SetInterval(tcs_MotorY,ms_X.LPON);		
				// *** ������� � �������� �������
				QClrPin(MOTOR_Yl_STEP);	
				QClrPin(MOTOR_Yr_STEP);	
				TCS_SetInterval(tcs_MotorY,ms_Y.LPOFF);		
			} else {
				QClrPin(MOTOR_Yl_STEP);	
				QClrPin(MOTOR_Yr_STEP);	
				TCS_SetInterval(tcs_MotorY,ms_Y.LPOFF);		
			}	
		} else {
				// ����������
				if (ClrSY) {
					QClrPin(MOTOR_Yl_STEP);	
					QClrPin(MOTOR_Yr_STEP);	
					ClrSY = 0;
				}
				TCS_SetInterval(tcs_MotorY,2500000);		
		}	
	} else {
		// ����� ��������� ���������
		//OFF_PULSE;
		ms_Y.Level = 0;								
		QSetPin(MOTOR_Yl_STEP);						
		QSetPin(MOTOR_Yr_STEP);						
		TCS_SetInterval(tcs_MotorY,ms_Y.LPON);		
	}
}

//****************����� Motor_Y*************************************


