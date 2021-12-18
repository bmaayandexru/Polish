#include "Defs.h"

//****************������ Motor_Z************************************
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
#define mulAZ 1
// �������� ��������� ��� ���������� �� ����� ����������������
#define mulAZP 2
// �������� �������� ��� ����������������
#define divVZP 2
volatile TIMER_CONTROL_STRUCT tcs_MotorZ; 	// ��������� ���������� �������� �������� ���������� ���������� 
volatile TFMC 	mc_Z;
volatile TFMS 	ms_Z;
// ���� ��������������� ������ ������� step
u8 ClrSZ = 0;

__inline void PositZ(void){
	// ���������������� �� �������
	switch (*ms_Z.StagePos) {
		case 0: // �������� � �������
			QSetPin(MOTOR_Z_DIR);
			//Msg("0");
			if (QGetPin(SENS_MOTOR_Z)) {
				*ms_Z.StagePos = 1;
				Msg("StagePosZ 1 Sensor Found\r\n");
			} else {
				*(mc_Z.FrReq)=*(mc_Z.FrMax);
				// �������� � ��������
				if (*(ms_Z.FrCur) < (*(mc_Z.FrReq)/divVZP)) {
					// ������ �� FrReq
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
		case 1: // ���������� � ����� �����������
			if (*(ms_Z.FrCur) <= *(mc_Z.FrMin)) {
				// ����� �����������
				QClrPin(MOTOR_Z_DIR);
				*ms_Z.StagePos = 2;
				Msg("StagePosZ 2 Break And Move Back\r\n");
			} else {
				// ����������
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
				// ����� �� ������� �� ����� ��������
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
	// ���������� �����������
//	Msg("aDir %d RD %d\r\n",*(ms_Z.Dir),*(mc_Z.ReqDir));
	if (*(mc_Z.MovePos) == 1) {
		if (((*(mc_Z.ReqPos) < *(ms_Z.Pos))&&(*(ms_Z.Dir)==1))||
		    ((*(mc_Z.ReqPos) > *(ms_Z.Pos))&&(*(ms_Z.Dir)==-1)))
		{
	//		Msg("a");
			// ���������� � ����� �����������
			if (*(ms_Z.FrCur) > *(mc_Z.FrMin)) {
	//			Msg("b");
				// ����������
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
				//����� �����������
				if (*(ms_Z.Dir)==1) *(ms_Z.Dir)=-1;
				else *(ms_Z.Dir)=1;
				if (*(ms_Z.Dir)==1) QSetPin(MOTOR_Z_DIR);
				else QClrPin(MOTOR_Z_DIR);
				// �������� �� ����� �����������
//				Msg("DelayDirZ\r\n");
//				TCS_SetInterval(tcs_MotorZ,*pDirDelay);
//				return;
			}
		} else {
	//		Msg("d");
			// ���������� ����
			if (abs(*(ms_Z.Pos)-*(mc_Z.ReqPos))<=(ms_Z.Lacc+10)) {
	//			Msg("e");
				// � ���� ��������
				if (*(ms_Z.FrCur) > *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur))
					*(ms_Z.FrCur) -= *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur);
				else *(ms_Z.FrCur) = 0; 
				if (*(ms_Z.FrCur) < *(mc_Z.FrMin)) *(ms_Z.FrCur) = *(mc_Z.FrMin);
				if (ms_Z.Lacc >= mulAZ) ms_Z.Lacc -= mulAZ; else ms_Z.Lacc = 0;
				ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
				ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
			} else {
	//			Msg("f");
				// ��� ���� ���� � ��������
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
		// ������ ����������
		if (*(ms_Z.FrCur) > *(mc_Z.FrMin)) {
				if (*(ms_Z.FrCur) > *(mc_Z.Accel)*mulAZ * (ms_Z.Tcur))
					*(ms_Z.FrCur) -= *(mc_Z.Accel)*mulAZ * (ms_Z.Tcur);
				else *(ms_Z.FrCur) = 0; 
				if (*(ms_Z.FrCur) < *(mc_Z.FrMin)) *(ms_Z.FrCur) = *(mc_Z.FrMin);
				if (ms_Z.Lacc >= mulAZ) ms_Z.Lacc -= mulAZ; else ms_Z.Lacc = 0;
				ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
				ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
		} else {
			// � ��� ��c������� ����������� ������� MovePos = 0
			*(mc_Z.MovePos) = 0;
			if (!*pCorrStop) {
				// ���������� ��������� ��������
				if ((!*(mc_Y.MovePos))&&(!*(mc_X.MovePos))) {
					Msg("CorrStop G0\r\n");
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
		// ������� ��������� ��������
		// ������� � ����������
		ms_Z.Tcur = Kb / *(mc_Z.FrMin);
//		TCS_SetInterval(tcs_MotorZ,2500000);
//		Msg("BXM");
	} else {
		if (!*(mc_Z.MoveBtn)) {
			// ����������
			if (*(ms_Z.FrCur) > *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur))
				*(ms_Z.FrCur) -= *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur);
			else *(ms_Z.FrCur) = 0; 
			if (*(ms_Z.FrCur) < *(mc_Z.FrMin)) *(ms_Z.FrCur) = *(mc_Z.FrMin);
			if (ms_Z.Lacc >= mulAZ) ms_Z.Lacc -= mulAZ; else ms_Z.Lacc = 0;
			ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
			ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
		} else {
			// �������� ���������
			// ��������� ������� ������� �� ������� ������� � ������� ���� 
			// �� ���������� ����������� ��� ����������
			// ����������, ��������� ����������� �������� �� �����������
			// ������ � �������� � ���������� ���������
			if (*(ms_Z.Dir)!=*(mc_Z.ReqDir)) {
				// ���������� � ����� �����������
				if (*(ms_Z.FrCur) > *(mc_Z.FrMin)) {
				   	// ����������
					if (*(ms_Z.FrCur) > *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur))
						*(ms_Z.FrCur) -= *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur);
					else *(ms_Z.FrCur) = 0; 
					if (*(ms_Z.FrCur) < *(mc_Z.FrMin)) *(ms_Z.FrCur) = *(mc_Z.FrMin);
					if (ms_Z.Lacc >= mulAZ) ms_Z.Lacc -= mulAZ; else ms_Z.Lacc = 0;
					ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
					ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
				} else {
					// ����� �����������
					*(ms_Z.Dir)=*(mc_Z.ReqDir);
					if (*(ms_Z.Dir) == 1) QSetPin(MOTOR_Z_DIR);
					else QClrPin(MOTOR_Z_DIR);
//					// �������� �� ����� �����������
//					Msg("DelayDirZ\r\n");
//					TCS_SetInterval(tcs_MotorZ,*pDirDelay);
//					return;
				}
			} else {
				// ������ � �������� � ���������� ���������
				if 	( 
						(((*(ms_Z.Pos)-(ms_Z.Lacc+10)) < Z_MIN_POS)&&(*(mc_Z.ReqDir) == -1)) ||
						(((*(ms_Z.Pos)+(ms_Z.Lacc+10)) > Z_MAX_POS)&&(*(mc_Z.ReqDir) == 1)) 
					)
				{
					// ����������
					if (*(ms_Z.FrCur) > *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur))
						*(ms_Z.FrCur) -= *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur);
					else *(ms_Z.FrCur) = 0; 
					if (*(ms_Z.FrCur) < *(mc_Z.FrMin)) *(ms_Z.FrCur) = *(mc_Z.FrMin);
					ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
					if (ms_Z.Lacc >= mulAZ) ms_Z.Lacc -= mulAZ; else ms_Z.Lacc = 0;
					ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
				} else
				if (*(mc_Z.FrReq) < *(mc_Z.FrMin)) {
					// ��������� ������� ������ �����������
					// ���������� FrCur �� FrMin � ������� �� FrReq
					if (*(ms_Z.FrCur) > *(mc_Z.FrMin)) {
						// ����������
						if (*(ms_Z.FrCur) > *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur))
							*(ms_Z.FrCur) -= *(mc_Z.Accel)* mulAZ * (ms_Z.Tcur);
						else *(ms_Z.FrCur) = 0; 
						if (*(ms_Z.FrCur) < *(mc_Z.FrMin)) *(ms_Z.FrCur) = *(mc_Z.FrMin);
						if (ms_Z.Lacc >= mulAZ) ms_Z.Lacc -= mulAZ; else ms_Z.Lacc = 0;
						if (*(ms_Z.FrCur) > *(mc_Z.FrMin)) {
							ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
							ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
						} else {
							// ������� �� FrReq
							*(ms_Z.FrCur) = *(mc_Z.FrReq);
							ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
							ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
						}
					} 
				} else {
					// ��������� ������� ������ ��� ����� �����������
					// �������� � FrReq
					if (*(ms_Z.FrCur) < *(mc_Z.FrReq)) {
						// ������ �� FrReq
						*(ms_Z.FrCur) += *(mc_Z.Accel) * ms_Z.Tcur;
						ms_Z.Lacc++;
						if (*(ms_Z.FrCur) > *(mc_Z.FrReq)) *(ms_Z.FrCur) = *(mc_Z.FrReq);
						ms_Z.Tcur = Kb / (*(ms_Z.FrCur));
						ms_Z.LPOFF = CLPOFF((ms_Z.Tcur),ms_Z.LPON);		
					} else
					if (*(ms_Z.FrCur) > *(mc_Z.FrReq)) {
						// ���������� �� FrReq
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
			// ������ �� �������� ����������� !!!!
			if (*(ms_Z.Dir) == 0) {
				Msg("ZD0\r\n");
				if (QGetPin(MOTOR_Z_DIR)) *(ms_Z.Dir) = 1;
				else *(ms_Z.Dir)=-1;
			}
			ClrSZ = 0;
			// ����� ���������� �������� ��� ������ ��������
			if (*mc_Z.PositOn && (!(*ms_Z.Posit))) {
				PositZ();
			} else 
			if (*(mc_Z.MovePos)) 
				MovePosZ();
			else
				MoveBtnZ();
			if (ms_Z.Level) {
				ClrSZ = 1; 
				// ������� � ������ �������
				//QSetPin(MOTOR_Z_STEP);	
				//TCS_SetInterval(tcs_MotorZ,ms_Z.LPON);		
				// *** ������� � �������� �������
				QClrPin(MOTOR_Z_STEP);	
				TCS_SetInterval(tcs_MotorZ,ms_Z.LPOFF);		
			} else {
				QClrPin(MOTOR_Z_STEP);	
				TCS_SetInterval(tcs_MotorZ,ms_Z.LPOFF);		
			}	
		} else {
				// ����������
				if (ClrSZ) {
					// ������� � �������� �������
					QClrPin(MOTOR_Z_STEP);
					ClrSZ = 0;
				}
				TCS_SetInterval(tcs_MotorZ,2500000);		
		}	
	} else {
		// ����� ��������� ���������
		//OFF_PULSE;
		ms_Z.Level = 0;		
		// ������� � ������ �������
		//QClrPin(MOTOR_Z_STEP);	
		//TCS_SetInterval(tcs_MotorZ,ms_Z.LPOFF);	
		// *** ������� � �������� �������
		QSetPin(MOTOR_Z_STEP);				
		TCS_SetInterval(tcs_MotorZ,ms_Z.LPON);		
		
	}
}


//****************����� Motor_Z*************************************


