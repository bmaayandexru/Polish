#include "Defs.h"

#ifdef __SAW__
//****************������ Motor_A************************************
#include <stdlib.h>
#include "Motors.h"
#include "VirtualPins.h"
#include "Timers.h"
#include "msg.h"
#include "VPSaw.h"

TIMER_CONTROL_STRUCT tcs_MotorA; 	// ��������� ���������� �������� �������� ���������� ���������� 
TMC 	mc_A;
TMS 	ms_A;

u8 * pValueLuft; // �������� �����
u8 * pFLuft;
u8 * pBLuft;

void InitCompensation(void){
	// ����� ����������������
	*pFLuft = 0;
	*pBLuft = *pValueLuft;
}

u8 Compensation(void){
	if (*(ms_A.Dir)==1) {
		if (*pFLuft > 0) {
			(*pFLuft)--;
			(*pBLuft)++;
//			Msg("C %d %d ",*pFLuft,*pBLuft);
			return 1;
		} else {
			return 0;
		}
	} else { //(*(ms_A.Dir)==-1)
		if (*pBLuft > 0) {
			(*pBLuft)--;
			(*pFLuft)++;
//			Msg("C %d %d ",*pFLuft,*pBLuft);
			return 1;
		} else {
			return 0;
		}
	}
}

int RecA(int A){
	if (A > A_SPRH) A=-(A_SPR-A);
//	Msg("A %d\r\n",A);
	return A;
}

int DeltaA(int A1,int A2){
	int L;
	L = abs(A1-A2);
	if (L > A_SPRH) L = A_SPR - L;
//	Msg("DA %d\r\n",L);
	return L;
}


__inline void  PositA(void) {
	// ���������������� �� ����
	switch (*ms_A.StagePos) {
		case 0: 
			*ms_A.StagePos = 2;
		break;
		case 2:
			QSetPin(MOTOR_A_DIR);
			*ms_A.Dir = 1;
			*ms_A.StagePos = 3;
			*(ms_A.Pos) = 0;
			BR_ms_A_Pos = *(ms_A.Pos); 
			Msg("StagePosA Complete\r\n");
   			//  ��� �������� �� ��������� ����������������
			*ms_A.Posit = 1;
			*mc_A.PositOn = 0;
			InitCompensation();
		break;
	}
}

__inline void MovePosA(void) {
	s32 dA, sA;
	if ((*(mc_A.ReqPos) == *(ms_A.Pos))) {
		*(mc_A.MovePos) = 0;
		return;
	}
	//Msg("RPos %d Pos %d\r\n",*(mc_A.ReqPos),*(ms_A.Pos));
	if (*(mc_A.ReqPos) < A_MIN_POS) *(mc_A.ReqPos)=A_MIN_POS;
	if (*(mc_A.ReqPos) > A_MAX_POS) *(mc_A.ReqPos)=A_MAX_POS;
	// ����������� �����������
	dA = *(mc_A.ReqPos) - *(ms_A.Pos);
	sA = (dA < 0 ? -1 : 1);
	if (abs(dA) > A_SPRH) sA = -sA;
	//Msg("dA %d sA %d DIR %d\r\n",dA,sA,*(ms_A.Dir));
	if (sA != *(ms_A.Dir)) {
		// ���������� � ����� �����������
		if (*(ms_A.FrCur) > *(mc_A.FrMin)) {
		   	// ����������
			*(ms_A.FrCur) -= *(mc_A.Accel) * ms_A.Tcur;
			if (ms_A.Lacc) ms_A.Lacc--;
			ms_A.Tcur = Kb / (*(ms_A.FrCur));
			ms_A.LPOFF = ms_A.Tcur - ms_A.LPON;	
		//	Msg("T");	
		} else {
			// ����� �����������
			// �������� �����������
			//Msg("CD %d %d\r\n",*(ms_A.Dir),sA);
			*(ms_A.Dir) = sA;
			if (*(ms_A.Dir)==1) QSetPin(MOTOR_A_DIR);
			else QClrPin(MOTOR_A_DIR);
		}
	} else {
		// ����������� ���������
		// ���������� ����
		//Msg("Lacc %d \r\n",ms_A.Lacc);
		if ((DeltaA(RecA(*(mc_A.ReqPos)-(ms_A.Lacc+10)),*(ms_A.Pos))+
			 DeltaA(RecA(*(mc_A.ReqPos)+(ms_A.Lacc+10)),*(ms_A.Pos))) > 2*(ms_A.Lacc+10))
		{
			// ��� ���� ����������
			if (*(ms_A.FrCur) < *(mc_A.FrReq)) {
			   	// ������
				*(ms_A.FrCur) += *(mc_A.Accel) * ms_A.Tcur;
				if (*(ms_A.FrCur) > *(mc_A.FrReq)) *(ms_A.FrCur) = *(mc_A.FrReq);
				ms_A.Lacc++;
				ms_A.Tcur = Kb / (*(ms_A.FrCur));
				ms_A.LPOFF = ms_A.Tcur - ms_A.LPON;		
			}
			// ��� �������� � ��������� ���������
		} else {
			// � ���� ����������
			if (*(ms_A.FrCur) > *(mc_A.FrMin)) {
			   	// ����������
				*(ms_A.FrCur) -= *(mc_A.Accel) * ms_A.Tcur;
				if (*(ms_A.FrCur) < *(mc_A.FrMin)) *(ms_A.FrCur) = *(mc_A.FrMin);
				if (ms_A.Lacc) ms_A.Lacc--;
				ms_A.Tcur = Kb / (*(ms_A.FrCur));
				ms_A.LPOFF = ms_A.Tcur - ms_A.LPON;		
			}
		}
	}
	//ON_PULSE;
	ms_A.Level = 1;								
	QSetPin(MOTOR_A_STEP);						
	if (!Compensation()) *(ms_A.Pos)+=*(ms_A.Dir);							
    if (*(ms_A.Pos) == (A_SPRH+1)) *(ms_A.Pos)=-(A_SPRH-1);// ������� �� pi � -pi
    if (*(ms_A.Pos) == -A_SPRH) *(ms_A.Pos)=A_SPRH;// ������� �� -pi � pi
	// ���������� � backup ��������
	BR_ms_A_Pos = *(ms_A.Pos);
	TCS_SetInterval(tcs_MotorA,ms_A.LPON);		
}
__inline void MoveBtnA(void) {
	if ((!*(mc_A.MoveBtn))&&(*(ms_A.FrCur) <= *(mc_A.FrMin))) {
		// ������� ��������� ��������
		// ������� � ����������
		ms_A.Tcur = Kb / *(mc_A.FrMin);
		TCS_SetInterval(tcs_MotorA,ms_A.Tcur);
//			Msg("Mon ");
	} else {
		if (!*(mc_A.MoveBtn)) {
			// ����������
			*(ms_A.FrCur) -= *(mc_A.Accel) * ms_A.Tcur;
			if (ms_A.Lacc) ms_A.Lacc--;
			ms_A.Tcur = Kb / *(ms_A.FrCur);
			ms_A.LPOFF = ms_A.Tcur - ms_A.LPON;		
		} else {
			// ����������, ��������� ����������� �������� �� �����������
			// ������ � �������� � ���������� ���������
			if (*(ms_A.Dir)!=*(mc_A.ReqDir)) {
				// ���������� � ����� �����������
				if (*(ms_A.FrCur) > *(mc_A.FrMin)) {
				   	// ����������
					*(ms_A.FrCur) -= *(mc_A.Accel) * ms_A.Tcur;
					if (ms_A.Lacc) ms_A.Lacc--;
					ms_A.Tcur = Kb / (*(ms_A.FrCur));
					ms_A.LPOFF = ms_A.Tcur - ms_A.LPON;		
				} else {
					// ����� �����������
					// ��������� ����������� ����� �����
					*(ms_A.Dir) = *(mc_A.ReqDir);
					if (*(ms_A.Dir) == 1) QSetPin(MOTOR_A_DIR);
					else QClrPin(MOTOR_A_DIR);
				}
			} else {
				// ������ � �������� � ���������� ���������
				if (*(mc_A.FrReq) < *(mc_A.FrMin)) {
					// ��������� ������� ������ �����������
					// ���������� FrCur �� FrMin � ������� �� FrReq
//					Msg("FrReq < FrMin ");
					if (*(ms_A.FrCur) > *(mc_A.FrMin)) {
						// ����������
						*(ms_A.FrCur) -= *(mc_A.Accel) * ms_A.Tcur;
						if (ms_A.Lacc) ms_A.Lacc--;
						if (*(ms_A.FrCur) > *(mc_A.FrMin)) {
							ms_A.Tcur = Kb / (*(ms_A.FrCur));
							ms_A.LPOFF = ms_A.Tcur - ms_A.LPON;		
						} else {
							// ������� �� FrReq
							*(ms_A.FrCur) = *(mc_A.FrReq);
							ms_A.Tcur = Kb / (*(ms_A.FrCur));
							ms_A.LPOFF = ms_A.Tcur - ms_A.LPON;		
						}
					} 
				} else {
					// ��������� ������� ������ ��� ����� �����������
//					Msg("FrReq >= FrMin ");
					// �������� � FrReq
					if (*(ms_A.FrCur) < *(mc_A.FrReq)) {
						// ������ �� FrReq
						*(ms_A.FrCur) += *(mc_A.Accel) * ms_A.Tcur;
						ms_A.Lacc++;
						if (*(ms_A.FrCur) > *(mc_A.FrReq)) *(ms_A.FrCur) = *(mc_A.FrReq);
						ms_A.Tcur = Kb / (*(ms_A.FrCur));
						ms_A.LPOFF = ms_A.Tcur - ms_A.LPON;		
//							Msg("Acc To FrReq ");
					} else
					if (*(ms_A.FrCur) > *(mc_A.FrReq)) {
						// ���������� �� FrReq
						*(ms_A.FrCur) -= *(mc_A.Accel) * ms_A.Tcur;
						if (ms_A.Lacc) ms_A.Lacc--;
						if (*(ms_A.FrCur) < *(mc_A.FrReq)) *(ms_A.FrCur) = *(mc_A.FrReq);
						ms_A.Tcur = Kb / (*(ms_A.FrCur));
						ms_A.LPOFF = ms_A.Tcur - ms_A.LPON;		
//							Msg("Dec To FrReq ");
					} 
				}
			}
		}
		//ON_PULSE;
		ms_A.Level = 1;								
		QSetPin(MOTOR_A_STEP);						
		if (!Compensation()) *(ms_A.Pos)+=*(ms_A.Dir);							
        if (*(ms_A.Pos) == (A_SPRH+1)) *(ms_A.Pos)=-(A_SPRH-1);// ������� �� pi � -pi
        if (*(ms_A.Pos) == -A_SPRH) *(ms_A.Pos)=A_SPRH;// ������� �� -pi � pi
		// ���������� � backup ��������
		BR_ms_A_Pos = *(ms_A.Pos);
		TCS_SetInterval(tcs_MotorA,ms_A.LPON);		
		//Msg("Pos %d Delta %d Nacc %d Tcurr %d ",ms_A.Pos, ms_A.Delta,ms_A.Nacc, ms_A.Tcur);
	}
}

void	MotorA_Handler(void){
	if (!ms_A.Level) {
		// ����� ���������� �������� ��� ������ ��������
		if (*mc_A.PositOn && (!(*ms_A.Posit))) {
			PositA();
		} else
		if (*(mc_A.MovePos)) {
			//Msg("pa");
			MovePosA();
		} else MoveBtnA();
	} else {
		// ����� ��������� ���������
		//OFF_PULSE;
		ms_A.Level = 0;								
		QClrPin(MOTOR_A_STEP);						
		TCS_SetInterval(tcs_MotorA,ms_A.LPOFF);		
	}
}

//****************����� Motor_A*************************************
#endif
// #ifdef __SAW__
