/*****************************************************************/
//
//  ��������� ���������� �������� �����
//
/*****************************************************************/

#include "LPC17xx.h"
// ������� ������ !!!
#include "lpc17xx_timer.h"

#include "Defs.h"
#include "regs.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Timers.h"

#include "UART.h"

#include "VirtualPins.h"

#include "Modbus.h"
#include "u0packets.h"
#include "u1packets.h"
#include "ti.h"
#include "Handlers.h"
#include "Motors.h"
#include "Flash.h"
#include "FS.h"
#include "queue.h"
#include "msg.h"
#include "FreqInvr.h"
#include "KeyPad.h"
#include "Tools.h"
#include "pwm.h"

#include "VPFrz.h"
#include "Motor_X.h"
#include "Motor_Y.h"
#include "Motor_Z.h"

#include "Nextion.h"

// UART0_SPEED MAX 400000
//#define UART0_SPEED 230400
#define UART0_SPEED 115200
// ��� Nextion
//#define UART0_SPEED 256000
//#define UART0_SPEED 460800
//#define UART0_SPEED 921600
#define UART1_SPEED 9600
u8 F = 1;

void PinsErrorHandler(TPinError * pe){
// ���������� ������ ������ � ������������ ������
}

void Test_Handler(void) {
//	static u8 f=0;
//	if (f)	SetPin(OUT20);
//	else ClrPin(OUT20);
//	f=1-f;
//	TCS_SetInterval(tcs_MotorR,tmMsToTick(500));
//	TCS_Start(tcs_MotorR);
}


void	OutNextTableLine(void){
	u32 ofs;
	char 	name[20];	// ���
	u8 i;

	if (CurVarIndex >= iva) {
		OutAllocTable=0;
	} else {
		// ������� ������� ������
		ofs = (u32)&regs[0];

		strcpy(name,va[CurVarIndex].name);

		for (i=0;i<strlen(name);i++)
		  if (name[i] == '.') name[i] = '_';

		// �������� ������
		Msg("o%s \t = %5d;// %5d, %1d, %8X",name,(u32)(va[CurVarIndex].p)-ofs,va[CurVarIndex].len,va[CurVarIndex].attr,va[CurVarIndex].handle);				

//		Msg("%d, o%s \t = ; ",CurVarIndex,name);				
//		Msg("1");	
		CurVarIndex++;
	}
}

// �������. ������ OUT20
void SysTick_Handler (void) {
//	
//static int f=0;
//static int cc=1000;
//static int c=1000;
//	
//	// SysTick_Handler ������� � ���������� 1000 ��� �� SysTick_Config � InitPlatform
//	// ��� ��������
//	// 1000 ������ ������
//	if (c--)return;
//	c=cc;
//	// ������� ������
//	if (f)	Q1SetPin(OUT20);
//	else Q1ClrPin(OUT20);
//	f=1-f; // f  ���� ����� ������ 0 ��� 1
}

void NMI_Handler(void) 				{} //; NMI Handler
void HardFault_Handler(void) 	{} //; Hard Fault Handler
void MemManage_Handler(void) 	{} //; MPU Fault Handler
void BusFault_Handler(void) 	{
//LPC_GPIO1->FIOSET = 1;
} //; Bus Fault Handler
void UsageFault_Handler(void) {} //; Usage Fault Handler
void SVC_Handler (void) 			{} //; SVCall Handler
void DebugMon_Handler (void) 	{} //; Debug Monitor Handler
void PendSV_Handler(void) 		{} //; PendSV Handler

__inline void	Nextion(void){
	// ������ � ������� Nextion
	if (0) {
  //  ^ ��� ������ ���� ������� ���������� 
		if (EndTI(tiNextSendme)) {
			neCmd("sendme");	// �������� ������ ������� ��������
			StartTI(tiNextSendme,tiMsToTick(5000));
		}
	}
}
	
__inline void FormQueue(void){
	if (*pUsesKP485) {
		if (quPackCount() < (quMaxItemCount-1)) {
			if (*pPrgRun) {
				TITimer(tiFQGetPult,tiMsToTick(*pIntKPCtrl), 
					{	// ��������� � ������� ����� ��������� ������
						KPQuery();
					},{}
				);	
			} else {
				TITimer(tiFQGetPult,tiMsToTick(*pIntKPCtrlStop), 
					{	// ��������� � ������� ����� ��������� ������
						KPQuery();
					},{}
				);	
			}
		}
	}
}

__inline void mbFrzUARTs(void){
	// ������������ UART0
	UART0_Thread();
	// ������ ��������� (������� ���)
	SMsg();

	// ������������ UART1
	UART1_Thread();
	// ������������ �������
	FormQueue();
	// ��������� ������� RS-485
	QueueProcessing();
	// ������ �������� 11.11.2016
	// �� RS-485 ���������� ������ �� ������
	// ������ ����� �� ��������� ��������� ������
	// 04 03 04 B0 00 0C 4D 45 FB
	// � ������ �� ���� �������� ���������
	// 04 20 10 03 0C 45 4D
	// ������������ � �������� 2000 ��. 
	// �������� ����� ��������� �������� ����� ���� �� 100 �� 6000 ��.
	// ������� ������� ������������� �� ���������� ���� ���������
}

__inline void	OutAllocateTable(void){
	// ����� ������� ����������
	if (OutAllocTable) {
		if (EndTI(tiOutAT)) {
			OutNextTableLine();
			StartTI(tiOutAT,tiMsToTick(200));
		}
	}
}

__inline void	ByPassFrz(void){
	// ����� �������
	static u8 f1=1;
	if (*pByPass) {
    if (*pBtn5==100) {	
			if (f1) { 
				// ����� ��������� ��������� ����� �� �������
				// �� ������������ ������� ������ �����
				StartMoveZLowSpeed();
				f1=0;
			}
		} else { if (!f1) f1=1;	}
	}
}

__inline void	HTCorrFrz(void){
	// ����� �������
	static u8 f2=1;
	if (*pHTCorr) {
    if (*pBtn5==100) {	
			if (f2) { 
				StartMoveZLowSpeed();
				f2=0;
			}
		} else { if (!f2) f2=1;	}
	}
}

__inline void	ZZeroDatFrz(void){
	// ��������� ���������� Z �� �������
	static u8 f2=1;
	if (*pZZeroDat) {
    if (*pBtn5==100) {	
			if (f2) { 
				StartMoveZLowSpeed();
				f2=0;
			}
		} else { if (!f2) f2=1;	}
	}
}

__inline void	ZZeroDat(void){
		*dZPos = *(ms_Z.Pos) - ((*pHdat)*(*pZ_SPR)/(*pZ_PG_MM));
		Msg("ZZero Zpos %d dZpos %d\r\n",*(ms_Z.Pos),*dZPos);
		SaveRegs();
		// ����� ��������� ���������� Z �� �������
		*pZZeroDat=0;
}

__inline void	ZZCheckPointFrz(void){
	// ����� �������
	static u8 f5=1;
	static u8 f6=1;
	if (*pZZeroDat) {
     if (QGetPin(SENS_SET_POINT)) {	
			if (f5) { 
				// ������������
				*(mc_Z.MovePos)=0;
				// ������ ������� ���������� �����
				RecoveryZfreq();
				ZZeroDat();
				UpZ();
				f5=0;
			}
		} else { if (!f5) f5=1;	}
		// �������� ����� �� �� ���� ��� �������
		if ((*(ms_Z.Pos)==0)&&(!QGetPin(SENS_SET_POINT))) {
			if (f6) { 
				// ����� �� ���� ��� �������
				Msg("Error Set Point\r\n");
				RecoveryZfreq();
				UpZ();
				f6=0;
			}
		} else { if (!f6) f6=1;	}
	}
}


__inline void	RunHorizontalDatFrz(void){
	// ����� ������ ��������������� �������
	static u8 f2=1;
	if ((*pHorizontalDat)&&(*pHorizDatState!=2)) {
		if ((*pBtn5==100)&&(((*pXmove) != 0)||((*pYmove) != 0))) {	
			// ���������� ����������� �� ���������
			if (f2) { 
				if ((*pXmove) < 0) *pHorizDatDir = 1;
				else {
					if ((*pXmove) > 0) *pHorizDatDir = 3;
					else {
						if ((*pYmove) < 0) *pHorizDatDir = 2;
						else {
							if ((*pYmove) > 0) *pHorizDatDir = 4;
						}	
					}
				}
				*pHorizDatState = 1;
				Msg("HDS 1. X %d Y %d D %d\r\n",*pXmove,*pYmove,*pHorizDatDir);
				f2=0;
			}
		} else { if (!f2) f2=1;	}
	}
}

__inline void	StartHorizontalDatFrz(void){
	// ����� ������ ��������������� �������
	static u8 f2=1;
	if ((*pHorizontalDat)&&(*pHorizDatState==1)) {
		if ((*pBtn5==0)&&(((*pXmove) == 0)||((*pYmove) == 0))) {	
			if (f2) { 
				*pHorizDatState = 2;
				// ���������� � ��������� � ������
				StartMoveHorizontalLowSpeed();
				Msg("HDS 2\r\n");
				f2=0;
			}
		} else { if (!f2) f2=1;	}
	}
}

__inline void	StopHorizontalDatFrz(void){
	// ��������� ������ ��������������� ������� ������� 5
	static u8 f2=1;
	if ((*pHorizontalDat)&&(*pHorizDatState==2)) {
		if ((*pBtn5==100)&&((*pXmove == 0)&&(*pYmove == 0))) {	
			if (f2) { 
				StopMoveHorizontalLowSpeed();
				*pHorizDatState = 0;
				Msg("HDS 0\r\n");
				f2=0;
			}
		} else { if (!f2) f2=1;	}
	}
}


__inline void	HorizontalDat(void){
		// �������� �� �������� �������
		// ������������� ���������� ����� � ��������
		float msx,msy; // ������ �� X � Y
		// ������� ������ �� ���������!!!!
		msx = 0;
		msy = 0;
		switch (*pHorizDatDir) {
			case 1: // �����
				msy = *pHorizMeasError;
				break;
			case 2: // �����
				msx = *pHorizMeasError;
				break;
			case 3: // ����
				msy = -(*pHorizMeasError);
				break;
			case 4: // ������
				msx = -(*pHorizMeasError);
				break;
		}	
		Msg("HDS 3\r\n");
		Msg("msx %d msy %d\r\n",OUTF1H(msx),OUTF1H(msy));
		*pHorizX = msx+(*(ms_X.Pos) - *dXPos)*(*pX_PG_MM)/(*pX_SPR);
		*pHorizY = msy+(*(ms_Y.Pos) - *dYPos)*(*pY_PG_MM)/(*pY_SPR);
		Msg("Horiz Dat X %d Y %d Xpos %d Ypos %d\r\n",OUTF1(*pHorizX),OUTF1(*pHorizY),*(ms_X.Pos),*(ms_Y.Pos));
		*pHorizDatState = 3;
}

__inline void	HorizontalCheckPointFrz(void){
	// ������ �������������� �������
	static u8 f5=1;
	static u8 f6=1;
	if ((*pHorizontalDat)&&(*pHorizDatState == 2)) {
     if (QGetPin(SENS_HORIZONTAL_POINT)) {	
			if (f5) { 
				// ������������
				*(mc_X.MovePos)=0;
				*(mc_Y.MovePos)=0;
				// ������ ������� ���������� �����
				HorizontalDat();
				BackHorizontal();// ���� UpZ();
				SaveRegs();
				f5=0;
			}
		} else { if (!f5) f5=1;	}
		
		// �������� ����� �� �� ����� �������� ���� ��� �������
		switch (*pHorizDatDir) {
				case 1:// Up 
					if ((*(ms_Y.Pos)==Y_MAX_POS)&&(!QGetPin(SENS_HORIZONTAL_POINT))) {
						if (f6) { 
							// ����� �� ���� ��� �������
							Msg("Error Set Y Point\r\n");
							*pHorizDatState = 4;
							RecoveryHorizfreq();
							BackHorizontal();// ���� UpZ();
							SaveRegs();
							f6=0;
						}
					} else { if (!f6) f6=1;	}
					break;
				case 3:// Down
					if ((*(ms_Y.Pos)==0)&&(!QGetPin(SENS_HORIZONTAL_POINT))) {
						if (f6) { 
							// ����� �� ���� ��� �������
							Msg("Error Set Y Point\r\n");
							*pHorizDatState = 4;
							RecoveryHorizfreq();
							BackHorizontal();// ���� UpZ();
							SaveRegs();
							f6=0;
						}
					} else { if (!f6) f6=1;	}
					break;
				case 2:// Left 
					if ((*(ms_X.Pos)==0)&&(!QGetPin(SENS_HORIZONTAL_POINT))) {
						if (f6) { 
							// ����� �� ����� ������� ��� �������
							Msg("Error Set X Point\r\n");
							*pHorizDatState = 4;
							RecoveryHorizfreq();
							BackHorizontal();// ���� UpZ();
							SaveRegs();
							f6=0;
						}
					} else { if (!f6) f6=1;	}
					break;
				case 4:// Right
					if ((*(ms_X.Pos)==X_MAX_POS)&&(!QGetPin(SENS_HORIZONTAL_POINT))) {
						if (f6) { 
							// ����� �� ������ ������� ��� �������
							Msg("Error Set X Point\r\n");
							*pHorizDatState = 4;
							RecoveryHorizfreq();
							BackHorizontal();// ���� UpZ();
							SaveRegs();
							f6=0;
						}
					} else { if (!f6) f6=1;	}
					break;
		}			
	}
}


__inline void	CheckPointFrz(void){
	// ����� �������
	static u8 f3=1;
	static u8 f4=1;
	if (*pByPass) {
    if (QGetPin(SENS_SET_POINT)) {	
			if (f3) { 
				// ������������
				*(mc_Z.MovePos)=0;
				// ������ ������� ���������� �����
				AddPointFrz();
				UpZ();
				f3=0;
			}
		} else { if (!f3) f3=1;	}
		// �������� ����� �� �� ���� ��� �������
		if ((*(ms_Z.Pos)==0)&&(!QGetPin(SENS_SET_POINT))) {
			if (f4) { 
				// ����� �� ���� ��� �������
				Msg("Error Set Point\r\n");
				RecoveryZfreq();
				UpZ();
				f4=0;
			}
		} else { if (!f4) f4=1;	}
	}
}

__inline void	HTCheckPointFrz(void){
	// ����� �������
	static u8 f5=1;
	static u8 f6=1;
	if (*pHTCorr) {
     if (QGetPin(SENS_SET_POINT)) {	
			if (f5) { 
				// ������������
				*(mc_Z.MovePos)=0;
				// ������ ������� ���������� �����
				HTCorr();
				SaveRegs();
				UpZ();
				f5=0;
			}
		} else { if (!f5) f5=1;	}
		// �������� ����� �� �� ���� ��� �������
		if ((*(ms_Z.Pos)==0)&&(!QGetPin(SENS_SET_POINT))) {
			if (f6) { 
				// ����� �� ���� ��� �������
				Msg("Error Set Point\r\n");
				RecoveryZfreq();
				UpZ();
				f6=0;
			}
		} else { if (!f6) f6=1;	}
	}
}

__inline void DebugFrzMoveHandler(void){
	// ������� Move_Handler(); 
	if (EndTI(tiTest)) { 
		FMove_HandlerQuick();
		StartTI(tiTest,tiMsToTick(20));
	}
}

__inline void StopPrg(void){
//	Msg("StopPrg %d",*pPrgRun);
	fStopPrg = 0;
	if (*(mc_X.MovePos)==1) *(mc_X.MovePos) = 2;
	if (*(mc_Y.MovePos)==1) *(mc_Y.MovePos) = 2;
	if (*(mc_Z.MovePos)==1) *(mc_Z.MovePos) = 2;
	if (fmvc.Enable==1) fmvc.Enable = 2;
	*(mc_X.FrReq)=*(mc_X.FrMax);
	*(mc_Y.FrReq)=*(mc_Y.FrMax);
	*(mc_Z.FrReq)=*(mc_Z.FrMax);
	// ����� �������� ���������� ���������
	*pCorrStop = 0;
	BR_pCorrStop = *pCorrStop;
	Msg("Xm %d Ym %d Zm %d fmcE %d\r\n",*(mc_X.MovePos),*(mc_Y.MovePos),*(mc_Z.MovePos),fmvc.Enable);
	// ���� �������� �� ���� �� ��������������� ���������� ���������
	if ((*(mc_X.MovePos)==0)&&
			(*(mc_Y.MovePos)==0)&&
			(*(mc_Z.MovePos)==0)&&
			(fmvc.Enable==0)) {
		*pCorrStop = 1;
		BR_pCorrStop = *pCorrStop;
				
	}			
}
__inline void StartPrg(void){
//	Msg("StartPrg %d",*pPrgRun);
	fStartPrg = 0;
	*(mc_X.FrReq)=*(mc_X.FrMax);
	*(mc_Y.FrReq)=*(mc_Y.FrMax);
	*(mc_Z.FrReq)=*(mc_Z.FrMax);
	if (*pCurCadr == 0) {
		InitQExBlks();// ������� �������
		InitPrgStreams();
	} else {
		*pRecoverBlock = 1;
	}
}

u32	tmpCurCadr = 0;
TBlock sb,*fb,*pb;
u8 Index1,Index2;
u8 Save_sGo;
float Save_Feed,Save_Speed;
char si[50];

__inline void RecoverBlock(){
	switch (*pRecoverBlock) {
		case 1:
			// ������ ������ ��������������
			Msg("RB%d\r\n",*pRecoverBlock);
			Msg("Xp %d Yp %d Zp %d\r\n",(*ms_X.Pos),(*ms_Y.Pos),(*ms_Z.Pos));
			InitQExBlks();// ������� �������
			InitPrgStreams();
			*pNumReadLine = 0;
			*pRecoverBlock = 2;
		break;
		case 2:
			if (*pNumReadLine < (*pCurCadr-1)) {
				// ����������� �� ����������� �����
				// ����� ���������� �����������
				TranslatePrg();	//*pNumReadLine++
				//Msg("rn %d",NumReadLine);
				if (qbCount() > 3) qbDelFirst();
			} else {
				//Msg("RB%d\r\n",*pRecoverBlock);
				*pRecoverBlock = 3;
				// ����� ��������� ���� ��� �������
				// ������� ������� ����� ���������� ��������� ������
				fb = qbLastBlock();
				// ��������� ���������� � sb ������ ���� �������
				memcpy(&sb,fb,sizeof sb);
				InitQExBlks();
				// �������� �������� ����� ������!!!!
				Save_sGo=sb.sGo;
				Save_Feed=sb.Feed;
				Save_Speed=sb.Speed;
				//Msg("RB2 G%d Xs %d Ys %d Zs %d Xd %d Yd %d Zd %d F %d S%d\r\n",sb.sGo,OUTF1T(sb.Xs),OUTF1T(sb.Ys),OUTF1T(sb.Zs),OUTF1T(sb.Xd),OUTF1T(sb.Yd),OUTF1T(sb.Zd),OUTF1(sb.Feed),OUTF1(sb.Speed));
				Msg("RB2 N%d: %s \r\n",sb.NumLine,sb.s);
				Msg("RB2 G%d X %d %d Y %d %d Z %d %d\r\n",sb.sGo,sb.Xsi,sb.Xdi,sb.Ysi,sb.Ydi,sb.Zsi,sb.Zdi);
			}
		break;
		case 3:
			Msg("RB%d\r\n",*pRecoverBlock);
			memset(si,0,50);
			sprintf(si,"G0 Z160 S%.0f\r\n",sb.Speed);
			Msg("%s",si);
			TranslatePrgLine(si);
			*pRecoverBlock = 4; 
		break;
		case 4:
			Msg("RB%d\r\n",*pRecoverBlock);
			TranslatePrgLine("M3 M7\r\n");
			*pRecoverBlock = 5; 
		break;
		case 5:
			Msg("RB%d\r\n",*pRecoverBlock);
			memset(si,0,50);
			sprintf(si,"G0 X%6.3f Y%6.3f\r\n",sb.Xd,sb.Yd); 
			Msg("%s",si);
			TranslatePrgLine(si);
			*pRecoverBlock = 6; 
		break;
		case 6:
			Msg("RB%d\r\n",*pRecoverBlock);
			memset(si,0,50);
			sprintf(si,"G%d Z%6.3f F%.0f\r\n",sb.sGo,sb.Zd,sb.Feed); 
			TranslatePrgLine(si);
			Msg("%s",si);
			*pRecoverBlock = 7; 
		break;
		case 7:
			(*pRCS) = rcsGetBlock;			
			Msg("End RB%d\r\n",*pRecoverBlock);
//			Msg("h %d t %d\r\n",qbFirstIndex(),qbLastFreeIndex());
			// ������ ��������� �� ����� !!!
			//qbAddBlock(&sb); // �������� �������� ����
			*pRecoverBlock = 0; 
			//*pRecoverBlock = 8; 
		break;
		case 8:
			Msg("RB%d\r\n",*pRecoverBlock);
			Index1 = qbFirstIndex();
			Index2 = qbLastFreeIndex();
			*pRecoverBlock = 9; 
		break;
		case 9:
			Msg("RB%d\r\n",*pRecoverBlock);
		// ������� ��������� ��� �������
			if (Index1 != Index2) {
				pb = qbGetBlockIndex(Index1);
				Msg("%s\r\n",(*pb).s);
				qbIncIndex(&Index1);
			} else {
				*pRecoverBlock = 0; 
			}
			// ������ ����� ���������� ������� � ���������
			// ��������� 8 � 9
			//*pRecoverBlock = 0; 
		break;
		case 10:
		break;
	}
}

__inline void RunPrgFrz(void){
	 // ���������� ��������� 
	 // ��� �������������� �� ��������� �� ������ ����������
#ifdef MOVE_D
	if (EndTI(tiPrgExe)) {
#endif
		if (fSaveRegs) { SaveRegs(); fSaveRegs=0;}
		if (fStopPrg) StopPrg();
		if (fStartPrg) StartPrg();
		if (*pPrgRun) {
			if (*pRecoverBlock) {
				// ������ � ������ ������ ����������� � ������������ ���������
//				if 	((*pRecoverBlock==1)||(*pRecoverBlock==2)) RecoverBlock();
				// ������ ������ ����������� � ������������ ���������
				if 	(*pRecoverBlock==2) RecoverBlock();
				// ���������� � ���������� � 300 ��
				else {
					if (EndTI(tiRecBlock)) {
						RecoverBlock();
						StartTI(tiRecBlock,tiMsToTick(300));
					}
				}
			}
			else {
				TranslatePrg();// ���������� ����� � ������� ������
				// ����� �������� ����������
//				if (qbCount() > 2) qbDelFirst();
//				if (EndTranslate) {
//					Msg("End TrTime Msk %d Nl %d\r\n",tiTickToMks(GetTime(timeTrCalc)),NumReadLine);
//					*pPrgRun = 0;
//					*pPrgPause = 0;
//				}
				// ������� !!!
//				if ((qbCount()>8)||EndTranslate)
				// ������ !!!
				if ((qbCount()>2)||EndTranslate)
				RunNextCadrFrzMain(); // ���������� �������� �����
				SearchStopPoint(); // ����� ����� �������� 
			}
		} else {
			// ���������� ��� ���������
			if 	((*(mc_X.MovePos) == 2) ||
					(*(mc_Y.MovePos) == 2) ||
					(*(mc_Z.MovePos) == 2) ||
					(fmvc.Enable == 2))
			{
				TranslatePrg();// ���������� ����� � ������� ������
				// ������ !!!
				if ((qbCount()>2)||EndTranslate)
				RunNextCadrFrzMain(); // ���������� �������� �����
				SearchStopPoint(); // ����� ����� �������� 
			}
		}	
#ifdef MOVE_D
		StartTI(tiPrgExe,tiMsToTick(300));
	}
#endif
}


// ����� ���������� ����������
__inline void	BtnAxisSwitchHandler(void){
	static u8 f=1;
	if (QGetPin(BTN_AXIS_SWITCH)) {	
		if (f) { 
			f=0;
			// ������������ ����
			*pAxisSwitch = 1 - *pAxisSwitch;
			// ������������� ��
			*pXmove = 0;
			*pYmove = 0;
			*pZmove = 0;
		}
	} else {
		if (!f) {f=1;}
	}
}

__inline void BtnsMotorYHandler(void){
// ����� �������
// ���������� �������� ������� ����������� ��������
	static u8 fD=1;
	static u8 fB=1;
	if ((QGetPin(BTN_MOTOR_Y_DIR))&&(QGetPin(BTN_MOTOR_Y_BACK))){
		// �������� 
		*pYmove = 0;
		fD = 1;
		fB = 1;
	} else {
		if (QGetPin(BTN_MOTOR_Y_DIR)) {
			// ������ ������ ������ ����� 
			if (fD) {
				fD = 0;
//				Msg("PressADir\r\n");
				if (GetTime(timeYdir) < tiMsToTick(*pDCTime*10)) {
					// Double Click
					*pYmove = 100;
				} else {
					// Single Click
					*pYmove = (*pPercVmin);
				}
			}
		} else {

			if (QGetPin(BTN_MOTOR_Y_BACK)) {
				// ������ ������ ������ ����� 
				if (fB) {
//					Msg("PressABack\r\n");
					fB = 0;
					if (GetTime(timeYback) < tiMsToTick(*pDCTime*10)) {
						// Double Click
						*pYmove = -100;
					} else {
						// Single Click
						*pYmove = -(*pPercVmin);
					}
				}
			} else {
				if (!fB) {
//					Msg("UpABack\r\n");
					fB = 1;
					*pYmove = 0;
					StartTime(timeYback);
				}
				if (!fD) {
					fD = 1;
//					Msg("UpADir\r\n");
					*pYmove = 0;
					StartTime(timeYdir);
				}
			}
		}
	}
}
//******************************************************
__inline void BtnsMotorZHandler(void){
// ����� �������
// ���������� �������� ������� ����������� ��������
	static u8 fD=1;
	static u8 fB=1;
	if ((QGetPin(BTN_MOTOR_Z_DIR))&&(QGetPin(BTN_MOTOR_Z_BACK))){
		// �������� 
		*pZmove = 0;
		fD = 1;
		fB = 1;
	} else {
		if (QGetPin(BTN_MOTOR_Z_DIR)) {
			// ������ ������ ������ ����� 
			if (fD) {
				fD = 0;
//				Msg("PressADir\r\n");
				if (GetTime(timeZdir) < tiMsToTick(*pDCTime*10)) {
					// Double Click
					*pZmove = 100;
				} else {
					// Single Click
					*pZmove = (*pPercVmin);
				}
			}
		} else {

			if (QGetPin(BTN_MOTOR_Z_BACK)) {
				// ������ ������ ������ ����� 
				if (fB) {
//					Msg("PressABack\r\n");
					fB = 0;
					if (GetTime(timeZback) < tiMsToTick(*pDCTime*10)) {
						// Double Click
						*pZmove = -100;
					} else {
						// Single Click
						*pZmove = -(*pPercVmin);
					}
				}
			} else {
				if (!fB) {
//					Msg("UpABack\r\n");
					fB = 1;
					*pZmove = 0;
					StartTime(timeZback);
				}
				if (!fD) {
					fD = 1;
//					Msg("UpADir\r\n");
					*pZmove = 0;
					StartTime(timeZdir);
				}
			}
		}
	}
}

//******************************************************

__inline void	BtnsMotorXHandler(void){
	static u8 fD=1;
	static u8 fB=1;
	if ((QGetPin(BTN_MOTOR_X_DIR))&&(QGetPin(BTN_MOTOR_X_BACK))){
		// �������� 
		*pXmove = 0;									
		fD = 1;
		fB = 1;
	} else {
		if (QGetPin(BTN_MOTOR_X_DIR)) {
			// ������ ������ ������ ����� 
			if (fD) {
				fD = 0;
				//Msg("PressXDir\r\n");
				if (GetTime(timeXdir) < tiMsToTick(*pDCTime*10)) {
					// Double Click
					*pXmove = 100;
				} else {
					// Single Click
					*pXmove = (*pPercVmin);
				}
			}
		} else {

			if (QGetPin(BTN_MOTOR_X_BACK)) {
				// ������ ������ ������ ����� 
				if (fB) {
					//Msg("PressXBack\r\n");
					fB = 0;
					if (GetTime(timeXback) < tiMsToTick(*pDCTime*10)) {
						// Double Click
						*pXmove = -100;
					} else {
						// Single Click
						*pXmove = -(*pPercVmin);
					}
				}
			} else {
				if (!fB) {
					//Msg("UpXBack\r\n");
					fB = 1;
					*pXmove = 0;
					StartTime(timeXback);
				}
				if (!fD) {
					fD = 1;
					//Msg("UpXDir\r\n");
					*pXmove = 0;
					StartTime(timeXdir);
				}
			}
		}
	}
}
//*****************************************
__inline void Btn5Handler(void){
	// ����� �������
	static u8 f=1;
    if (QGetPin(BTN_NUM_5)) {	
		if (f) { f=0; *pBtn5 = 100;	}
	}
    else { 
		if (!f) {f=1;	*pBtn5 = 0;}
	}
}

__inline void ButtonsToRegs(void){
 	// �������� ������ � ��������
	// ���������� ��������
	if (*pUsesKP485==0) {
		//Msg("b");
		Btn5Handler(); // ������ 5
		BtnAxisSwitchHandler(); // ������������ ���� ������ 6
		if (*pAxisSwitch){
			// ������ ���������� ����������� Z
			BtnsMotorZHandler();
		}
		else {
			// ������ ���������� ����������� �
			BtnsMotorXHandler();
			// ������ ���������� ����������� Y
			BtnsMotorYHandler();
		}
	}
}

__inline void MoveByRegs(void){
// ��������� ��������
	if (*pXmove) {
		*(mc_X.ReqDir) = ((*pXmove) > 0) ? 1 : -1 ;
//		*(mc_X.ReqDir) = ((*pXmove) > 0) ? -1 : 1 ;
		*(mc_X.FrReq) = (u64)(*(mc_X.FrMax)*1.0*abs(*pXmove)/100);
		*(mc_X.MoveBtn) = 1;
	} else {
		*(mc_X.MoveBtn) = 0;
		*(mc_X.FrReq) = *(mc_X.FrMax);
	}
// ��������� ��������
	if (*pYmove) {
		*(mc_Y.ReqDir) = *pYmove > 0 ? 1 : -1 ;
		*(mc_Y.FrReq) = (u64)(*(mc_Y.FrMax) * (abs(*pYmove)*1.0/100));
		*(mc_Y.MoveBtn) = 1;
	} else {
		*(mc_Y.MoveBtn) = 0;
		*(mc_Y.FrReq) = *(mc_Y.FrMax);
	}

	if (*pZmove) {
		*(mc_Z.ReqDir) = *pZmove > 0 ? 1 : -1 ;
		*(mc_Z.FrReq) = (u64)(*(mc_Z.FrMax) * (abs(*pZmove)*1.0/100));
		*(mc_Z.MoveBtn) = 1;
	} else {
		*(mc_Z.MoveBtn) = 0;
		*(mc_Z.FrReq) = *(mc_Z.FrMax);
	}

}

// ����� ������ ���������� ����������


__inline void	CrushWaterFrz(void){
	static u8 f=1;
    if (QGetPin(CRUSH_WATER)) {	
		if (f) { 
			// ������ ����
			CrushWaterHandlerFrz();
			f=0;
		}
	}
    else {	if (!f) {	f=1;	*pCrushWater = 0; }	}
}

// ����� ������� ��� �����������
#define tmove 0
// ����� ������� ��� ������ ����������
#define tint 1

__inline void InitPlatform(void){
	// ������������� ���������
	// ������� ����������� �������������
	SystemInit();		
	// ����������� ����������� ���������� �����???
	NVIC_SetPriorityGrouping(4);
	// ����� �� ������� TIMER0 ����� ��� ����� ������� ��������� � �� ����� ���� ������� ������ ��������
	// ��������� ������������� SysTickHandler() � �������� ??? 
	// 1000 mks �������� SysTick_Handler()
	SysTick_Config(SystemCoreClock/(990000/1000)); 
	// Msg("%d",SystemCoreClock);
	//	SetPinsErrHandler(PinsErrorHandler);

	UARTx_Init(0,FULL_DUPLEX,UART0_SPEED,UART_PARITY_NONE,UART_DATABIT_8,UART_STOPBIT_1);
	// �����
//	UARTx_Init(1,FULL_DUPLEX,9600,UART_PARITY_NONE,UART_DATABIT_8,UART_STOPBIT_1);
	// ��������� ����� ����
	UARTx_Init(1,HALF_DUPLEX,UART1_SPEED,UART_PARITY_NONE,UART_DATABIT_8,UART_STOPBIT_1);
	InitTimer(tmove);	// �������������
	// 2 � 3 �� �����
//	InitTimer(2);	// �������������
//	InitTimer(3);	// �������������
 
	InitTimer1(1); // 

	FLASH_Init();
	__enable_irq();
}

__inline void	InitFrzTimers(void){
	// ������ �������� ���������� � ������
	// ������ ������� ������� ����� ��������
	LPC_TIM1->MR0 = 5000;
	LPC_TIM1->TC = 10;
	// ������� ���
//	LPC_TIM1->TC = 0;

// � �������� ������� ��������� ���� ��� � �������
	Init_TCS(&tcs_MotorX, tmove,  0,MotorX_Handler); // ���������� ��������� � ��������
	TCS_Start(tcs_MotorX);
	Init_TCS(&tcs_MotorY, tmove,  1,MotorY_Handler); // ���������� ��������� � ��������
	TCS_Start(tcs_MotorY);
	Init_TCS(&tcs_MotorZ, tmove,  2,MotorZ_Handler); // ���������� ��������� � ��������
	TCS_Start(tcs_MotorZ);
#ifndef MOVE_D
	Init_TCS(&tcs_FMove, tmove, 3,FMove_HandlerQuick); // ���������� ��������� � ��������
	TCS_Start(tcs_FMove);
#endif

}

#define CHECK_DTFIX(tmr,t,mr) { if (tmr) { \
		if (tmr->dtfix) { \
					Msg("T%dMR%d %d %d\r\n",t,mr,tmr->dtfix,tmr->intfix); \
					tmr->dtfix=0; \
		}	} }

#define REGION_Enabled  (0x01)
#define REGION_32K      (14 << 1)      // 2**15 == 32k
		#define REGION_64K      (15 << 1)      // 2**15 == 32k
		#define REGION_16K      (13 << 1)      // 2**15 == 32k
#define REGION_512K      (18 << 1)      // 2**15 == 32k
#define REGION_1M      (19 << 1)      // 2**15 == 32k
#define REGION_2M      (20 << 1)      // 2**15 == 32k

#define REGION_Valid 0x10
#define NORMAL          (8 << 16)      // TEX:0b001 S:0b0 C:0b0 B:0b0
#define DEVICE_NON_SHAREABLE          (16 << 16)      // TEX:0b001 S:0b0 C:0b0 B:0b0
#define STRONGLY_ORDERED_SHAREABLE          (0 << 16)      // TEX:0b001 S:0b0 C:0b0 B:0b0

#define FULL_ACCESS     (0x03 << 24)   // Privileged Read Write, Unprivileged Read Write
#define RO     (0x06 << 24)   // Privileged Read Write, Unprivileged Read Write
#define NOT_EXEC        (0x01 << 28)   // All Instruction fetches abort		
		
// !!!!!!!!!!!!!������ ��� ��������� �� ������������!!!!!!!!!!!!!!!
// ����������� ����������� �� �� ������		
void lpc1768_mpu_config(void)
{
   /* Disable MPU */
   MPU->CTRL = 0;
   /* Configure region 0 to cover 512KB Flash (Normal, Non-Shared, Executable, Read-only) */
   MPU->RBAR = 0x00000000 | REGION_Valid | 0;
   MPU->RASR = REGION_Enabled |  REGION_512K | RO;
   /* Configure region 1 to cover CPU 32KB SRAM (Normal, Non-Shared, Executable, Full Access) */
   MPU->RBAR = 0x10000000 | REGION_Valid | 1;
   MPU->RASR = REGION_Enabled |  REGION_32K | FULL_ACCESS;
   /* Configure region 2 to cover AHB 32KB SRAM (Normal, Non-Shared, Executable, Full Access) */
   MPU->RBAR = 0x2007C000 | REGION_Valid | 2;
   MPU->RASR = REGION_Enabled | REGION_32K | FULL_ACCESS;
   /* Configure region 3 to cover 16KB GPIO (Device, Non-Shared, Full Access Device, Full Access) */
   MPU->RBAR = 0x2009C000 | REGION_Valid | 3;
   MPU->RASR = REGION_Enabled | REGION_16K | FULL_ACCESS;
   /* Configure region 4 to cover 512KB APB Peripherials (Device, Non-Shared, Full Access Device, Full Access) */
   MPU->RBAR = 0x40000000 | REGION_Valid | 4;
   MPU->RASR = REGION_Enabled |  REGION_1M | FULL_ACCESS;
   /* Configure region 5 to cover 2MB AHB Peripherials (Device, Non-Shared, Full Access Device, Full Access) */
   MPU->RBAR = 0x50000000 | REGION_Valid | 5;
   MPU->RASR = REGION_Enabled |  REGION_2M | FULL_ACCESS;
   /* Configure region 6 to cover the 1MB PPB (Privileged, XN, Read-Write) */
   MPU->RBAR = 0xE0000000 | REGION_Valid | 6;
   MPU->RASR = REGION_Enabled | REGION_1M | FULL_ACCESS;
   /* Enable MPU */

   MPU->CTRL = 1;
   __ISB();
  __DSB();
}		
		
int main(void)
{
//	u32 ver;//,test;
	s8 res;
//	static u32 f,xx;
	// ������������� ���������
	// ������������ ��� ���� �������� !!!!
	// ��� ������������� ���������� �������� � UART-�� ��� �������� � ������������
	InitPlatform();	
		
	// ������ ������
	AllocFrzRegisters();		// ���������� ��������� � ������� regs
													// ��������� � ������ ��������� �������� ����������-������
													// ������� ��������� �� ������������ ����� ������� regs
													// ��� ������ ������� ����� ������
													// ������ regs �������� �������� ������
													// ���� ����������� ���������� � �������� ������� regs �� ������
	InitFrzRegisters();			// ������������� regs
	InitFrzTimers();				// �������� ����������� � �������� ����������
	InitQExBlks();
	
	mbSetHandler(0,mbFrzPackHandler0);
	mbSetSpeed(0,UART0_SPEED);
	mbSetHandler(1,mbFrzPackHandler1);
	mbSetSpeed(1,UART1_SPEED);
	Msg("Polish (%08X) build %d\r\n",VERSION,build);
	Msg("PG %d\r\n",NVIC_GetPriorityGrouping());
	res = FS_Init();
	if (res==FS_RESULT_OK) {
		Msg("FS Init Ok.\r\n");
	   	// �������� ����� ���������
#ifndef __NOT_LOAD_PARAMS__		
		LoadRegsFromFile();
		InitFrzRegsAfterLoad();
		// ������������ ������� ������� �����
		FormQPinTable();
		// �������������� �� backup-���������
		LoadFrzBackupRegs();
#endif		
		// ��������� ��������� ��� ������ ����� ��������
	}
	else Msg("FS Init Fault. Err\r\n",res);
	//Msg("sizeof block %d\r\n",sizeof (*eb));
	InitPrgStreams();

	InitVirtualPins(); // ���

	FIInit();
	KPInit();
// � ����� ������� ����� ������ ���� �����
	InitZComp();
	StartTI(tiTest,tiMsToTick(200));  // DebugFrzMoveHandler
	StartTI(tiOutAT,tiMsToTick(200)); // ���
	StartTI(tiPrgExe,tiMsToTick(200)); // ���
	StartTI(tiTest2,tiMsToTick(1000)); // ���
	StartTI(tiQTest,tiMsToTick(100));
	StartTI(tiFQTest,tiMsToTick(100));
	StartTI(tiFQGetPult,tiMsToTick(500));
	StartTI(tiFQGetPress,tiMsToTick(2000));
	StartTI(tiRecBlock,tiMsToTick(200));

	StartTI(tiTestTime,tiMsToTick(100));
	StartTI(tiPrgExeNonStop,tiMsToTick(10));
	
	StartTI(tiNextSendme,tiMsToTick(5000));

	StartTime(timeXdir);
	StartTime(timeXback);
	StartTime(timeYdir);
	StartTime(timeYback);
	StartTime(timeZdir);
	StartTime(timeZback);
	
//	ver = VERSION;
	Msg("Init Ok.\r\n");
//#pragma push
//#pragma O0
//	Msg("sfp %d\r\n",BR_FilePos);	
//#pragma pop	
#ifdef __NOT_LOAD_PARAMS__
	Msg("Firmware Not Load regs.bin\r\n");
#endif	
//LPC_TIM1->MR0 = 5000;
//LPC_TIM1->TC = 10;
 //  while (1) {
	// ver = 3000000;
	//	ver = sqrt(ver+10);
	//	 ver = 4000000;
	//	ver = sqrt(ver * ver ); 
	//	 if (F == 1) {
		 
	//			QClrPin(MOTOR_X_DIR);
	//		} else {
	//			QSetPin(MOTOR_X_DIR);
	//		}
	//	F = 1-F;	
	// }
	
	while (1) {
			Nextion();
		
			mbFrzUARTs();	  		// ���
			
			OutAllocateTable();	// ���
			
			RunPrgFrz();			// ���
#ifdef MOVE_D
			DebugFrzMoveHandler();	 // ���
#endif
			ButtonsToRegs(); // �������� ������ � ��������
	
			if (*pPrgRun) {
				// ����� �������� ����� �������� ���������
				// ��������� ����� ��������
				// �������� �� ���������� ����
				CrushWaterFrz();
			} else {
				if (!fmvc.Enable) {
					if (!((*pHorizontalDat)&&(*pHorizDatState==2)))
					MoveByRegs();
				}
				// ������������ ���������
				ByPassFrz();
				CheckPointFrz();
				// ��������� �����������
				HTCorrFrz();
				HTCheckPointFrz();
				// ��������� �� �������
				ZZeroDatFrz();
				ZZCheckPointFrz();
				// ����� ������
				RunHorizontalDatFrz();
				StartHorizontalDatFrz();
				StopHorizontalDatFrz();
				HorizontalCheckPointFrz();
				// ����� ��������
				QGetPin(SENS_SET_POINT);
				QGetPin(SENS_HORIZONTAL_POINT);
			}
			// �������� ������ ��������
//			if (EndTI(tiTestTime)){
////				if (T0MR0->dtfix) {
////					Msg("T0MR0 %d %d\r\n",T0MR0->dtfix,T0MR0->intfix);
////					T0MR0->dtfix=0;
////				}	
//				CHECK_DTFIX(T0MR0,0,0);
//				CHECK_DTFIX(T0MR1,0,1);
//				CHECK_DTFIX(T0MR2,0,2);
//				CHECK_DTFIX(T0MR3,0,3);
//				CHECK_DTFIX(T1MR0,1,0);
//				CHECK_DTFIX(T1MR1,1,1);
//				CHECK_DTFIX(T1MR2,1,2);
//				CHECK_DTFIX(T1MR3,1,3);
//				CHECK_DTFIX(T2MR0,2,0);
//				CHECK_DTFIX(T2MR1,2,1);
//				CHECK_DTFIX(T2MR2,2,2);
//				CHECK_DTFIX(T2MR3,2,3);
//				CHECK_DTFIX(T3MR0,3,0);
//				CHECK_DTFIX(T3MR1,3,1);
//				CHECK_DTFIX(T3MR2,3,2);
//				CHECK_DTFIX(T3MR3,3,3);
////				if (T1T0p) {Msg("T1T0p");T1T0p=0;}
////				if (U1T0p) {Msg("U1T0p");U1T0p=0;}
////				if (U0T0p) {Msg("U0T0p");U0T0p=0;}
//				Msg("M\r\n");
//				StartTI(tiTestTime,tiMsToTick(1000));
//			}
    }// while (1)

}

/*
		// �������� ������� main
		frc++;
		if (EndTI(tiTest)) { 
			if (QGetPin(TEST_FREQ_MAIN)) {
				QClrPin(TEST_FREQ_MAIN);
			} else {
				QSetPin(TEST_FREQ_MAIN);
			}
			StartTI(tiTest,tiMsToTick(10));
			Msg("%d\r\n",frc);
			frc=0;
		}		
*/		


