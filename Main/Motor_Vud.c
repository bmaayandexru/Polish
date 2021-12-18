#include "Defs.h"

#ifdef __SAW__
//****************������ Motor_Vud************************************
#include <stdlib.h>
#include "Motors.h"
#include "VirtualPins.h"
#include "Timers.h"
#include "msg.h"
#include "VPSaw.h"

TIMER_CONTROL_STRUCT tcs_MotorVu,tcs_MotorVd;
TMC 	mc_Vu,mc_Vd;
TMS 	ms_Vu,ms_Vd;

// ********************** Vu

__inline void  PositVu(void) {
	// ���������������� �� �������� �������
	switch (*ms_Vu.StagePos) {
		case 0: // �������� � �������
			QClrPin(MOTOR_Vu_DIR);
			if (QGetPin(SENS_MOTOR_Vu)) {
				*ms_Vu.StagePos = 1;
				Msg("StagePosVu 1 Sensor Found\r\n");

			} else {
				// �������� � ��������
				if (*(ms_Vu.FrCur) < *(mc_Vu.FrReq)) {
					// ������ �� FrReq
					*(ms_Vu.FrCur) += *(mc_Vu.Accel) * ms_Vu.Tcur; //!!!!!!!!
					if (*(ms_Vu.FrCur) > *(mc_Vu.FrReq)) *(ms_Vu.FrCur) = *(mc_Vu.FrReq);
					ms_Vu.Tcur = Kb / (*(ms_Vu.FrCur));
					ms_Vu.LPOFF = ms_Vu.Tcur - ms_Vu.LPON;		
				} 
				// ON_PULSE
				ms_Vu.Level = 1;								
				QSetPin(MOTOR_Vu_STEP);						
				TCS_SetInterval(tcs_MotorVu,ms_Vu.LPON);		
			}
		break;
		case 1: // ���������� � ����� �����������
			if (*(ms_Vu.FrCur) <= *(mc_Vu.FrMin)) {
				// ����� �����������
				QSetPin(MOTOR_Vu_DIR);
				*ms_Vu.StagePos = 2;
				Msg("StagePosVu 2 Break And Move Back\r\n");
			} else {
				// ����������
				*(ms_Vu.FrCur) -= *(mc_Vu.Accel) * ms_Vu.Tcur;
				if (*(ms_Vu.FrCur) < *(mc_Vu.FrMin)) *(ms_Vu.FrCur) = *(mc_Vu.FrMin);
				ms_Vu.Tcur = Kb / (*(ms_Vu.FrCur));
				ms_Vu.LPOFF = ms_Vu.Tcur - ms_Vu.LPON;		
				// ON_PULSE
				ms_Vu.Level = 1;								
				QSetPin(MOTOR_Vu_STEP);						
				TCS_SetInterval(tcs_MotorVu,ms_Vu.LPON);		
			}
		break;
		case 2:
			QSetPin(MOTOR_Vu_DIR);
			if (!QGetPin(SENS_MOTOR_Vu)) {
				QClrPin(MOTOR_Vu_DIR);
				*ms_Vu.StagePos = 3;
				*(ms_Vu.Pos) = *pVuStartPos;
				BR_ms_Vud_Pos = *(ms_Vu.Pos);
				*(ms_Vu.Dir)=-1;
				*ms_Vu.Posit = 1;
				*mc_Vu.PositOn = 0;
				Msg("StagePosVu Complete\r\n");
			} else {
				// ����� �� ������� �� ����� ��������
				// ON_PULSE
				ms_Vu.Level = 1;								
				QSetPin(MOTOR_Vu_STEP);						
				TCS_SetInterval(tcs_MotorVu,ms_Vu.LPON);		
			}
		break;
	}
}

int RecVu(int A){
	if (A > Vu_SPRH) A=-(Vu_SPR-A);
//	Msg("A %d\r\n",A);
	return A;
}

int DeltaVu(int A1,int A2){
	int L;
	L = abs(A1-A2);
	if (L > Vu_SPRH) L = Vu_SPR - L;
//	Msg("DA %d\r\n",L);
	return L;
}

__inline void MovePosVu(void) {
	s32 dVu, sVu;
	if ((*(mc_Vu.ReqPos) == *(ms_Vu.Pos))) {
		*(mc_Vu.MovePos) = 0;
		return;
	}
	//Msg("VuPos %d Pos %d\r\n",*(mc_Vu.ReqPos),*(ms_Vu.Pos));
	if (*(mc_Vu.ReqPos) < Vu_MIN_POS) *(mc_Vu.ReqPos)=Vu_MIN_POS;
	if (*(mc_Vu.ReqPos) > Vu_MAX_POS) *(mc_Vu.ReqPos)=Vu_MAX_POS;
	// ����������� �����������
	dVu = *(mc_Vu.ReqPos) - *(ms_Vu.Pos);
	sVu = (dVu < 0 ? -1 : 1);
	if (abs(dVu) > Vu_SPRH) sVu = -sVu;
	//Msg("dVu %d sVu %d DIR %d\r\n",dVu,sVu,*(ms_Vu.Dir));
	if (sVu != *(ms_Vu.Dir)) {
		// ���������� � ����� �����������
		if (*(ms_Vu.FrCur) > *(mc_Vu.FrMin)) {
		   	// ����������
			*(ms_Vu.FrCur) -= *(mc_Vu.Accel) * ms_Vu.Tcur;
			if (ms_Vu.Lacc) ms_Vu.Lacc--;
			ms_Vu.Tcur = Kb / (*(ms_Vu.FrCur));
			ms_Vu.LPOFF = ms_Vu.Tcur - ms_Vu.LPON;	
		//	Msg("T");	
		} else {
			// ����� �����������
			// �������� �����������
			//Msg("CD %d %d\r\n",*(ms_Vu.Dir),sVu);
			*(ms_Vu.Dir) = sVu;
			if (*(ms_Vu.Dir)==1) QSetPin(MOTOR_Vu_DIR);
			else QClrPin(MOTOR_Vu_DIR);
		}
	} else {
		// ����������� ���������
		// ���������� ����
		//Msg("Lacc %d \r\n",ms_Vu.Lacc);
		if ((DeltaVu(RecVu(*(mc_Vu.ReqPos)-(ms_Vu.Lacc+10)),*(ms_Vu.Pos))+
			 DeltaVu(RecVu(*(mc_Vu.ReqPos)+(ms_Vu.Lacc+10)),*(ms_Vu.Pos))) > 2*(ms_Vu.Lacc+10))
		{
			// ��� ���� ����������
			if (*(ms_Vu.FrCur) < *(mc_Vu.FrReq)) {
			   	// ������
				*(ms_Vu.FrCur) += *(mc_Vu.Accel) * ms_Vu.Tcur;
				if (*(ms_Vu.FrCur) > *(mc_Vu.FrReq)) *(ms_Vu.FrCur) = *(mc_Vu.FrReq);
				ms_Vu.Lacc++;
				ms_Vu.Tcur = Kb / (*(ms_Vu.FrCur));
				ms_Vu.LPOFF = ms_Vu.Tcur - ms_Vu.LPON;		
			}
			// ��� �������� � ��������� ���������
		} else {
			// � ���� ����������
			if (*(ms_Vu.FrCur) > *(mc_Vu.FrMin)) {
			   	// ����������
				*(ms_Vu.FrCur) -= *(mc_Vu.Accel) * ms_Vu.Tcur;
				if (*(ms_Vu.FrCur) < *(mc_Vu.FrMin)) *(ms_Vu.FrCur) = *(mc_Vu.FrMin);
				if (ms_Vu.Lacc) ms_Vu.Lacc--;
				ms_Vu.Tcur = Kb / (*(ms_Vu.FrCur));
				ms_Vu.LPOFF = ms_Vu.Tcur - ms_Vu.LPON;		
			}
		}
	}
	//ON_PULSE;
	ms_Vu.Level = 1;								
	QSetPin(MOTOR_Vu_STEP);						
	*(ms_Vu.Pos)+=*(ms_Vu.Dir);							
    if (*(ms_Vu.Pos) == (Vu_SPRH+1)) *(ms_Vu.Pos)=-(Vu_SPRH-1);// ������� �� pi � -pi
    if (*(ms_Vu.Pos) == -Vu_SPRH) *(ms_Vu.Pos)=Vu_SPRH;// ������� �� -pi � pi
	BR_ms_Vud_Pos = *(ms_Vu.Pos);
	TCS_SetInterval(tcs_MotorVu,ms_Vu.LPON);		
}

__inline void MoveBtnVu(void) {
	if ((!*(mc_Vu.MoveBtn))&&(*(ms_Vu.FrCur) <= *(mc_Vu.FrMin))) {
		// ������� ��������� ��������
		// ������� � ����������
		ms_Vu.Tcur = Kb / *(mc_Vu.FrMin);
		TCS_SetInterval(tcs_MotorVu,ms_Vu.Tcur);
//			Msg("Mon ");
	} else {
		if (!*(mc_Vu.MoveBtn)) {
			// ����������
			*(ms_Vu.FrCur) -= *(mc_Vu.Accel) * ms_Vu.Tcur;
			if (ms_Vu.Lacc) ms_Vu.Lacc--;
			ms_Vu.Tcur = Kb / *(ms_Vu.FrCur);
			ms_Vu.LPOFF = ms_Vu.Tcur - ms_Vu.LPON;		
		} else {
			// ����������, ��������� ����������� �������� �� �����������
			// ������ � �������� � ���������� ���������
			if (*(ms_Vu.Dir)!=*(mc_Vu.ReqDir)) {
				// ���������� � ����� �����������
				if (*(ms_Vu.FrCur) > *(mc_Vu.FrMin)) {
				   	// ����������
					*(ms_Vu.FrCur) -= *(mc_Vu.Accel) * ms_Vu.Tcur;
					if (ms_Vu.Lacc) ms_Vu.Lacc--;
					ms_Vu.Tcur = Kb / (*(ms_Vu.FrCur));
					ms_Vu.LPOFF = ms_Vu.Tcur - ms_Vu.LPON;		
				} else {
					// ����� �����������
					// ��������� ����������� ����� �����
					*(ms_Vu.Dir) = *(mc_Vu.ReqDir);
					if (*(ms_Vu.Dir) == 1) QSetPin(MOTOR_Vu_DIR);
					else QClrPin(MOTOR_Vu_DIR);
				}
			} else {
				// ������ � �������� � ���������� ���������
				if (*(mc_Vu.FrReq) < *(mc_Vu.FrMin)) {
					// ��������� ������� ������ �����������
					// ���������� FrCur �� FrMin � ������� �� FrReq
//					Msg("FrReq < FrMin ");
					if (*(ms_Vu.FrCur) > *(mc_Vu.FrMin)) {
						// ����������
						*(ms_Vu.FrCur) -= *(mc_Vu.Accel) * ms_Vu.Tcur;
						if (ms_Vu.Lacc) ms_Vu.Lacc--;
						if (*(ms_Vu.FrCur) > *(mc_Vu.FrMin)) {
							ms_Vu.Tcur = Kb / (*(ms_Vu.FrCur));
							ms_Vu.LPOFF = ms_Vu.Tcur - ms_Vu.LPON;		
						} else {
							// ������� �� FrReq
							*(ms_Vu.FrCur) = *(mc_Vu.FrReq);
							ms_Vu.Tcur = Kb / (*(ms_Vu.FrCur));
							ms_Vu.LPOFF = ms_Vu.Tcur - ms_Vu.LPON;		
						}
					} 
				} else {
					// ��������� ������� ������ ��� ����� �����������
//					Msg("FrReq >= FrMin ");
					// �������� � FrReq
					if (*(ms_Vu.FrCur) < *(mc_Vu.FrReq)) {
						// ������ �� FrReq
						*(ms_Vu.FrCur) += *(mc_Vu.Accel) * ms_Vu.Tcur;
						ms_Vu.Lacc++;
						if (*(ms_Vu.FrCur) > *(mc_Vu.FrReq)) *(ms_Vu.FrCur) = *(mc_Vu.FrReq);
						ms_Vu.Tcur = Kb / (*(ms_Vu.FrCur));
						ms_Vu.LPOFF = ms_Vu.Tcur - ms_Vu.LPON;		
//							Msg("Acc To FrReq ");
					} else
					if (*(ms_Vu.FrCur) > *(mc_Vu.FrReq)) {
						// ���������� �� FrReq
						*(ms_Vu.FrCur) -= *(mc_Vu.Accel) * ms_Vu.Tcur;
						if (ms_Vu.Lacc) ms_Vu.Lacc--;
						if (*(ms_Vu.FrCur) < *(mc_Vu.FrReq)) *(ms_Vu.FrCur) = *(mc_Vu.FrReq);
						ms_Vu.Tcur = Kb / (*(ms_Vu.FrCur));
						ms_Vu.LPOFF = ms_Vu.Tcur - ms_Vu.LPON;		
//							Msg("Dec To FrReq ");
					} 
				}
			}
		}
		//ON_PULSE;
		ms_Vu.Level = 1;								
		QSetPin(MOTOR_Vu_STEP);						
		*(ms_Vu.Pos)+=*(ms_Vu.Dir);							
        if (*(ms_Vu.Pos) == (Vu_SPRH+1)) *(ms_Vu.Pos)=-(Vu_SPRH-1);// ������� �� pi � -pi
        if (*(ms_Vu.Pos) == -Vu_SPRH) *(ms_Vu.Pos)=Vu_SPRH;// ������� �� -pi � pi
		BR_ms_Vud_Pos = *(ms_Vu.Pos);
		TCS_SetInterval(tcs_MotorVu,ms_Vu.LPON);		
		//Msg("Pos %d Delta %d Nacc %d Tcurr %d ",ms_Vu.Pos, ms_Vu.Delta,ms_Vu.Nacc, ms_Vu.Tcur);
	}
}

void	MotorVu_Handler(void){
	//Msg("Vu");
	if (!ms_Vu.Level) {
		// ����� ���������� �������� ��� ������ ��������
		if (*mc_Vu.PositOn && (!(*ms_Vu.Posit))) {
			PositVu();
		} else
		if (*(mc_Vu.MovePos)) {
			MovePosVu();
		} else MoveBtnVu();
	} else {
		// ����� ��������� ���������
		//OFF_PULSE;
		ms_Vu.Level = 0;								
		QClrPin(MOTOR_Vu_STEP);						
		TCS_SetInterval(tcs_MotorVu,ms_Vu.LPOFF);		
	}
}


// *************************** Vd
__inline void  PositVd(void) {
	// ���������������� �� �������� �������
	switch (*ms_Vd.StagePos) {
		case 0: // �������� � �������
			QClrPin(MOTOR_Vd_DIR);
			if (QGetPin(SENS_MOTOR_Vd)) {
				*ms_Vd.StagePos = 1;
				Msg("StagePosVd 1 Sensor Found\r\n");
			} else {
				// �������� � ��������
				if (*(ms_Vd.FrCur) < *(mc_Vd.FrReq)) {
					// ������ �� FrReq
					*(ms_Vd.FrCur) += *(mc_Vd.Accel) * ms_Vd.Tcur; //!!!!!!!!
					if (*(ms_Vd.FrCur) > *(mc_Vd.FrReq)) *(ms_Vd.FrCur) = *(mc_Vd.FrReq);
					ms_Vd.Tcur = Kb / (*(ms_Vd.FrCur));
					ms_Vd.LPOFF = ms_Vd.Tcur - ms_Vd.LPON;		
				} 
				// ON_PULSE
				ms_Vd.Level = 1;								
				QSetPin(MOTOR_Vd_STEP);						
				TCS_SetInterval(tcs_MotorVd,ms_Vd.LPON);		
			}
		break;
		case 1: // ���������� � ����� �����������
			if (*(ms_Vd.FrCur) <= *(mc_Vd.FrMin)) {
				// ����� �����������
				QSetPin(MOTOR_Vd_DIR);
				*ms_Vd.StagePos = 2;
				Msg("StagePosVd 2 Break And Move Back\r\n");
			} else {
				// ����������
				*(ms_Vd.FrCur) -= *(mc_Vd.Accel) * ms_Vd.Tcur;
				if (*(ms_Vd.FrCur) < *(mc_Vd.FrMin)) *(ms_Vd.FrCur) = *(mc_Vd.FrMin);
				ms_Vd.Tcur = Kb / (*(ms_Vd.FrCur));
				ms_Vd.LPOFF = ms_Vd.Tcur - ms_Vd.LPON;		
				// ON_PULSE
				ms_Vd.Level = 1;								
				QSetPin(MOTOR_Vd_STEP);						
				TCS_SetInterval(tcs_MotorVd,ms_Vd.LPON);		
			}
		break;
		case 2:
			QSetPin(MOTOR_Vd_DIR);
			if (!QGetPin(SENS_MOTOR_Vd)) {
				QClrPin(MOTOR_Vd_DIR);
				*ms_Vd.StagePos = 3;
				// ������ ����		// ������� �� ������ �����
	
				//*(ms_Vd.Pos) = 75;	//+Vd_SPR/3;


				*(ms_Vd.Pos) = *pVdStartPos;
				BR_ms_Vud_Pos = *(ms_Vd.Pos);
				*(ms_Vd.Dir)=-1;
				*ms_Vd.Posit = 1;
				*mc_Vd.PositOn = 0;
				Msg("StagePosVd Complete\r\n");
			} else {
				// ����� �� ������� �� ����� ��������
				// ON_PULSE
				ms_Vd.Level = 1;								
				QSetPin(MOTOR_Vd_STEP);						
				TCS_SetInterval(tcs_MotorVd,ms_Vd.LPON);		
			}
		break;
	}
}
__inline void MoveBtnVd(void) {
	if ((!*(mc_Vd.MoveBtn))&&(*(ms_Vd.FrCur) <= *(mc_Vd.FrMin))) {
		// ������� ��������� ��������
		// ������� � ����������
		ms_Vd.Tcur = Kb / *(mc_Vd.FrMin);
		TCS_SetInterval(tcs_MotorVd,ms_Vd.Tcur);
//			Msg("Mon ");
	} else {
		if (!*(mc_Vd.MoveBtn)) {
			// ����������
			*(ms_Vd.FrCur) -= *(mc_Vd.Accel) * ms_Vd.Tcur;
			if (ms_Vd.Lacc) ms_Vd.Lacc--;
			ms_Vd.Tcur = Kb / *(ms_Vd.FrCur);
			ms_Vd.LPOFF = ms_Vd.Tcur - ms_Vd.LPON;		
		} else {
			// ����������, ��������� ����������� �������� �� �����������
			// ������ � �������� � ���������� ���������
			if (*(ms_Vd.Dir)!=*(mc_Vd.ReqDir)) {
				// ���������� � ����� �����������
				if (*(ms_Vd.FrCur) > *(mc_Vd.FrMin)) {
				   	// ����������
					*(ms_Vd.FrCur) -= *(mc_Vd.Accel) * ms_Vd.Tcur;
					if (ms_Vd.Lacc) ms_Vd.Lacc--;
					ms_Vd.Tcur = Kb / (*(ms_Vd.FrCur));
					ms_Vd.LPOFF = ms_Vd.Tcur - ms_Vd.LPON;		
				} else {
					// ����� �����������
					// ��������� ����������� ����� �����
					*(ms_Vd.Dir) = *(mc_Vd.ReqDir);
					if (*(ms_Vd.Dir) == 1) QSetPin(MOTOR_Vd_DIR);
					else QClrPin(MOTOR_Vd_DIR);
				}
			} else {
				// ������ � �������� � ���������� ���������
				if (*(mc_Vd.FrReq) < *(mc_Vd.FrMin)) {
					// ��������� ������� ������ �����������
					// ���������� FrCur �� FrMin � ������� �� FrReq
//					Msg("FrReq < FrMin ");
					if (*(ms_Vd.FrCur) > *(mc_Vd.FrMin)) {
						// ����������
						*(ms_Vd.FrCur) -= *(mc_Vd.Accel) * ms_Vd.Tcur;
						if (ms_Vd.Lacc) ms_Vd.Lacc--;
						if (*(ms_Vd.FrCur) > *(mc_Vd.FrMin)) {
							ms_Vd.Tcur = Kb / (*(ms_Vd.FrCur));
							ms_Vd.LPOFF = ms_Vd.Tcur - ms_Vd.LPON;		
						} else {
							// ������� �� FrReq
							*(ms_Vd.FrCur) = *(mc_Vd.FrReq);
							ms_Vd.Tcur = Kb / (*(ms_Vd.FrCur));
							ms_Vd.LPOFF = ms_Vd.Tcur - ms_Vd.LPON;		
						}
					} 
				} else {
					// ��������� ������� ������ ��� ����� �����������
//					Msg("FrReq >= FrMin ");
					// �������� � FrReq
					if (*(ms_Vd.FrCur) < *(mc_Vd.FrReq)) {
						// ������ �� FrReq
						*(ms_Vd.FrCur) += *(mc_Vd.Accel) * ms_Vd.Tcur;
						ms_Vd.Lacc++;
						if (*(ms_Vd.FrCur) > *(mc_Vd.FrReq)) *(ms_Vd.FrCur) = *(mc_Vd.FrReq);
						ms_Vd.Tcur = Kb / (*(ms_Vd.FrCur));
						ms_Vd.LPOFF = ms_Vd.Tcur - ms_Vd.LPON;		
//							Msg("Acc To FrReq ");
					} else
					if (*(ms_Vd.FrCur) > *(mc_Vd.FrReq)) {
						// ���������� �� FrReq
						*(ms_Vd.FrCur) -= *(mc_Vd.Accel) * ms_Vd.Tcur;
						if (ms_Vd.Lacc) ms_Vd.Lacc--;
						if (*(ms_Vd.FrCur) < *(mc_Vd.FrReq)) *(ms_Vd.FrCur) = *(mc_Vd.FrReq);
						ms_Vd.Tcur = Kb / (*(ms_Vd.FrCur));
						ms_Vd.LPOFF = ms_Vd.Tcur - ms_Vd.LPON;		
//							Msg("Dec To FrReq ");
					} 
				}
			}
		}
		//ON_PULSE;
		ms_Vd.Level = 1;								
		QSetPin(MOTOR_Vd_STEP);						
		*(ms_Vd.Pos)+=*(ms_Vd.Dir);							
        if (*(ms_Vd.Pos) == (Vd_SPRH+1)) *(ms_Vd.Pos)=-(Vd_SPRH-1);// ������� �� pi � -pi
        if (*(ms_Vd.Pos) == -Vd_SPRH) *(ms_Vd.Pos)=Vd_SPRH;// ������� �� -pi � pi
		BR_ms_Vud_Pos = *(ms_Vd.Pos);
		TCS_SetInterval(tcs_MotorVd,ms_Vd.LPON);		
		//Msg("Pos %d Delta %d Nacc %d Tcurr %d ",ms_Vd.Pos, ms_Vd.Delta,ms_Vd.Nacc, ms_Vd.Tcur);
	}
}

int RecVd(int A){
	if (A > Vd_SPRH) A=-(Vd_SPR-A);
//	Msg("A %d\r\n",A);
	return A;
}

int DeltaVd(int A1,int A2){
	int L;
	L = abs(A1-A2);
	if (L > Vd_SPRH) L = Vd_SPR - L;
//	Msg("DA %d\r\n",L);
	return L;
}

__inline void MovePosVd(void) {
	s32 dVd, sVd;
	if ((*(mc_Vd.ReqPos) == *(ms_Vd.Pos))) {
		*(mc_Vd.MovePos) = 0;
		return;
	}
	//Msg("VdPos %d Pos %d\r\n",*(mc_Vd.ReqPos),*(ms_Vd.Pos));
	if (*(mc_Vd.ReqPos) < Vd_MIN_POS) *(mc_Vd.ReqPos)=Vd_MIN_POS;
	if (*(mc_Vd.ReqPos) > Vd_MAX_POS) *(mc_Vd.ReqPos)=Vd_MAX_POS;
	// ����������� �����������
	dVd = *(mc_Vd.ReqPos) - *(ms_Vd.Pos);
	sVd = (dVd < 0 ? -1 : 1);
	if (abs(dVd) > Vd_SPRH) sVd = -sVd;
	//Msg("dVd %d sVd %d DIR %d\r\n",dVd,sVd,*(ms_Vd.Dir));
	if (sVd != *(ms_Vd.Dir)) {
		// ���������� � ����� �����������
		if (*(ms_Vd.FrCur) > *(mc_Vd.FrMin)) {
		   	// ����������
			*(ms_Vd.FrCur) -= *(mc_Vd.Accel) * ms_Vd.Tcur;
			if (ms_Vd.Lacc) ms_Vd.Lacc--;
			ms_Vd.Tcur = Kb / (*(ms_Vd.FrCur));
			ms_Vd.LPOFF = ms_Vd.Tcur - ms_Vd.LPON;	
		//	Msg("T");	
		} else {
			// ����� �����������
			// �������� �����������
			//Msg("CD %d %d\r\n",*(ms_Vd.Dir),sVd);
			*(ms_Vd.Dir) = sVd;
			if (*(ms_Vd.Dir)==1) QSetPin(MOTOR_Vd_DIR);
			else QClrPin(MOTOR_Vd_DIR);
		}
	} else {
		// ����������� ���������
		// ���������� ����
		//Msg("Lacc %d \r\n",ms_Vd.Lacc);
		if ((DeltaVd(RecVd(*(mc_Vd.ReqPos)-(ms_Vd.Lacc+10)),*(ms_Vd.Pos))+
			 DeltaVd(RecVd(*(mc_Vd.ReqPos)+(ms_Vd.Lacc+10)),*(ms_Vd.Pos))) > 2*(ms_Vd.Lacc+10))
		{
			// ��� ���� ����������
			if (*(ms_Vd.FrCur) < *(mc_Vd.FrReq)) {
			   	// ������
				*(ms_Vd.FrCur) += *(mc_Vd.Accel) * ms_Vd.Tcur;
				if (*(ms_Vd.FrCur) > *(mc_Vd.FrReq)) *(ms_Vd.FrCur) = *(mc_Vd.FrReq);
				ms_Vd.Lacc++;
				ms_Vd.Tcur = Kb / (*(ms_Vd.FrCur));
				ms_Vd.LPOFF = ms_Vd.Tcur - ms_Vd.LPON;		
			}
			// ��� �������� � ��������� ���������
		} else {
			// � ���� ����������
			if (*(ms_Vd.FrCur) > *(mc_Vd.FrMin)) {
			   	// ����������
				*(ms_Vd.FrCur) -= *(mc_Vd.Accel) * ms_Vd.Tcur;
				if (*(ms_Vd.FrCur) < *(mc_Vd.FrMin)) *(ms_Vd.FrCur) = *(mc_Vd.FrMin);
				if (ms_Vd.Lacc) ms_Vd.Lacc--;
				ms_Vd.Tcur = Kb / (*(ms_Vd.FrCur));
				ms_Vd.LPOFF = ms_Vd.Tcur - ms_Vd.LPON;		
			}
		}
	}
	//ON_PULSE;
	ms_Vd.Level = 1;								
	QSetPin(MOTOR_Vd_STEP);						
	*(ms_Vd.Pos)+=*(ms_Vd.Dir);							
    if (*(ms_Vd.Pos) == (Vd_SPRH+1)) *(ms_Vd.Pos)=-(Vd_SPRH-1);// ������� �� pi � -pi
    if (*(ms_Vd.Pos) == -Vd_SPRH) *(ms_Vd.Pos)=Vd_SPRH;// ������� �� -pi � pi
	BR_ms_Vud_Pos = *(ms_Vd.Pos);
	TCS_SetInterval(tcs_MotorVd,ms_Vd.LPON);		
}

void	MotorVd_Handler(void){
	//Msg("Vd");
	if (!ms_Vd.Level) {
		// ����� ���������� �������� ��� ������ ��������
		if (*mc_Vd.PositOn && (!(*ms_Vd.Posit))) {
			PositVd();
		} else
		if (*(mc_Vd.MovePos)) {
			MovePosVd();
		} else MoveBtnVd();
	} else {
		// ����� ��������� ���������
		//OFF_PULSE;
		ms_Vd.Level = 0;								
		QClrPin(MOTOR_Vd_STEP);						
		TCS_SetInterval(tcs_MotorVd,ms_Vd.LPOFF);		
	}
}

//****************����� Motor_Vud*************************************
#endif
// #ifdef __SAW__
