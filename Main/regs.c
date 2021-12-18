// ������ ������ � ����������
// ������������ ������� ���������
#include "Defs.h"
#include <string.h>
#include "regs.h"
#include "msg.h"
#include "motors.h"
#include "handlers.h"
#include "ti.h"
#include "bfs.h"
#include "VirtualPins.h"
#include "Modbus.h"
#include "FreqInvr.h"
#include "KeyPad.h"
#include "tools.h"

#include "VPFrz.h"
#include "Motor_X.h"
#include "Motor_Y.h"
#include "Motor_Z.h"

// ����� ����������
u8 *pByPass; // ����� ������
u8 *pCrushWater;
//TContur * pscz;

u8 *pQURepCount;
u16 *pQUTimeout;
// ����������� ��������� ���������� ��������� �� RS-485
u8 *pACmdDump;
u8 *pAMsg;
u8 *pAAnswDump;
// ����������� ��������� ��������� �� RS-485
u8 *pAECmdDump;
u8 *pAEMsg;
u8 *pAEAnswDump;
// ����������� �� ���������� ���������
u8 *pANCmdDump;
u8 *pANMsg;

// ����������� ������ ����������� ����� UART1
u8 *pErrCSU1;
// ����������� �������� ������ �� ���������� � �������
u8 *pDropCmd;
#ifdef __FREZER__
// ������ �� �
float *pX_PG_MM;
u32 *pX_SPR;
float	*pX_MIN;
float	*pX_MAX;
s32 vX_MIN_POS; 
s32 vX_MAX_POS; 
// ������ �� Y
float *pY_PG_MM;
u32 *pY_SPR;
float	*pY_MIN;
float	*pY_MAX;
s32 vY_MIN_POS; 
s32 vY_MAX_POS; 
// ������ �� Z
float *pZ_PG_MM;
u32 *pZ_SPR;
float	*pZ_MIN;
float	*pZ_MAX;
s32 vZ_MIN_POS; 
s32 vZ_MAX_POS; 

// �������� ������ ������ ���������
s32 * dXPos;
s32 * dYPos;
s32 * dZPos;

// ��������� ������ ���������� ������ ����
u16 *pIntKPCtrl;
u16 *pIntKPCtrlStop;
// ���������� ������ ��� ��������� ��� ������
u8	*pKP_NA_Max;

// ����� � �� 
u8 *pLinkKP;
// ���������� ������ ��� ��������� ��� ����������
//u8	LS_NA_Count;
// ���������� ������ ��� ��������� ��� ������
u8	KP_NA_Count;
// ������� ���������� ���������
u8 *pCorrStop;
// ������� �������������� ���������� ����� ����� ��� ����� ���������� �������
u8 *pRecoverBlock;
// ����� ��������� ������ �����������
u8 *pHTCorr; 
// ����� ��������� ���������� Z �� �������
u8 *pZZeroDat; 
// ����� ������ �� ��������������� �������
u8 *pHorizontalDat;
// ����������� �������������� ������� 0 off 1 up 2 left 3 down 4 right
u8 *pHorizDatDir;
// ��������� ���������� �������������� ������� 0 off 1 go 2 ok 3 fault
u8 *pHorizDatState;
	// ������� ������ �������
float *pHorizDiam;
	// ����������� ���������
float *pHorizMeasError;
// ���������� X ����� ������������ �������
float *pHorizX;
// ���������� Y ����� ������������ �������
float *pHorizY;

u8	fStopPrg;
u8	fStartPrg;
u8	fSaveRegs;
// ����������� �������� ���������->������� ���
//float *pKred;
// ������� ���� (�)
//float *pDval;
// ������� �������� ���� ��/��� ��� ����������� ������� ���� pFnom
u16 *pFdbyFnom;	
// ����������� ������� ����
u16	*pFnom;

#endif



static u32 CurBase = 0,CurOffset;
TVarAttr 	va[200]; 	// ������ ���������
u16			iva=0;		// ������� ������

u8 OutAllocTable=0;
u32 CurVarIndex = 0;
u8	VChange = 0;

u8 regs[REGS_COUNT]; // registers

u8 ROHandler(char * name,u8 * buffer,u16 len){
	// ������ �����������,
	// ������������� ��� ������ ������ �� �������� ����������
	// � ����� ������
	// Msg("ROH %s.",name);
	return 0; // ������ ���������
	//return �� 0; // ������ ��������� 
	// 1,2,3 - ���������������
}

u8 pCurCadrHandle(char * name,u8 * buffer,u16 len){
	memcpy((void*)&(BR_pCurCadr),(void*)buffer,4);
	//Msg("BR_pCurCadr %d\r\n",BR_pCurCadr);
	return 0;
}

u8 pCurCadrHandleFrz(char * name,u8 * buffer,u16 len){
	memcpy((void*)&(BR_pCurCadr),(void*)buffer,4);
	*pRCS = 0;
	if (BR_pCurCadr == 0) *pRecoverBlock = 0;
	else *pRecoverBlock = 1;
	//Msg("BR_pCurCadr %d\r\n",BR_pCurCadr);
	return 0;
}


u8 pDrDelayHandle(char * name,u8 * buffer,u16 len){
// �������� ���� ��������
	s16 v;
	if (*pUsesKP485) {
		memcpy((u8*)&v,buffer,2);
		mbInsCmd485(*pAddrKPCtrl,6,1200,v,1); 
	}
	return 0;
}

u8 pDCTimeHandle(char * name,u8 * buffer,u16 len){
// ����� DoubleClick
	s16 v;
	if (*pUsesKP485) {
		memcpy((u8*)&v,buffer,2);
		mbInsCmd485(*pAddrKPCtrl,6,1201,v,1);  
	}
	return 0;
}

u8 pPercVminHandle(char * name,u8 * buffer,u16 len){
	s16 v;
	if (*pUsesKP485) {
		memcpy((u8*)&v,buffer,2);
		mbInsCmd485(*pAddrKPCtrl,6,1202,v,1);
	}
	return 0;
}

u8 PinInt(u32 point,u32 left,u32 right){
//	Msg("p %X l %X r %X\r\n",point,left,right);
	if ((point >= left) && (point <= right))
		return 1;
	else return 0;
}

u8 Cross(u32 sx,u16 slen,u32 dx,u16 dlen){
	u32 p1,p2,p3,p4;
	p1 = sx; p2 = sx+slen-1;
	p3 = dx; p4 = dx+dlen-1;
//	Msg("p1 %X p2 %X p3 %X p4 %X",p1,p2,p3,p4);

	if (slen < dlen) {
		if (PinInt(p1,p3,p4) || PinInt(p2,p3,p4))
		 	return 1;
		else return 0;
	} else {
		if (PinInt(p3,p1,p2) || PinInt(p4,p1,p2))
		 	return 1;
		else return 0;
	}
}

void SetBase(u32 addr){
	// ���������� ����� � �����������
	// if (addr < REGS_COUNT) CurBase = addr;
	// ���
	// �������� � ���������� regs
	//if (addr < REGS_COUNT)
	CurBase = addr;
//	Msg("cb %d \r\n",CurBase);
}

void SetNewGroup(void){
	u32 CurAddr;
	CurAddr = CurBase + CurOffset;
	// �������� �������� ������ �� ������� ��������� ������������� 4+8*n
	if (CurAddr) {
		if ((CurAddr-4)%8) CurBase = ((CurAddr-4)/8 +1)*8 +4;
		else CurBase = CurAddr;
	} // ������� ����� ���������
	CurOffset = 0; // ����� �������� ��������
	//Msg("NG %d\r\n",CurBase);
}


void SetAddr(void ** p,char * name,/*u32 offset,*/u16 len,u32 attr,TWHandler WHandler){
	u32 tp;
	u16	i;

//	tp = (u32)&(regs[CurBase]) + offset;
	tp = (u32)&(regs[CurBase]) + CurOffset;
	CurOffset += len;
	//Msg("cb %X tp %X\r\n",CurBase,tp);

 	if (iva > 0) {
		for (i=0;i<iva;i++) {
			// ������� ����������� ����������
			if (Cross(tp,len,(u32)va[i].p,va[i].len)){
				Msg("Error allocate memory. Address is busy.\r\n");				
				Msg("Set name %s,addr 0x%X,len %d\r\n",va[i].name,va[i].p,va[i].len);				
				Msg("Alloc name %s,addr 0x%X,len %d\r\n",name,tp,va[i].len);				
				return;
			}
		}
	}

	*p = (void*)tp;
	strcpy(va[iva].name,name);
	va[iva].p = *p;
	va[iva].len = len;
	va[iva].attr = attr;
	va[iva].handle = WHandler;
	iva++;
}

// �������� ����� ���������
void	LoadRegsFromFile(void){
	tFile f;
	u32 rbc;
	s8 res;
	// ������� ���� regs.bin
	res = FS_Assign("startup.cmd",&f);
	if (res == FS_RESULT_OK) {
		res = FS_Reset(f);
		if (res == FS_RESULT_OK) {
			FS_Close(&f);
			res = FS_Assign("regs.bin",&f);
			if (res == FS_RESULT_OK) {
				res = FS_Reset(f);
				if (res == FS_RESULT_OK) {
					// ��������� N ���� � ������ regs
					res = bFS_Read(f,regs,REGS_COUNT,&rbc);
					if (res < 0) {
						Msg("Error Read File regs.bin res %d\r\n",res);
					}
					// ������� �����
					FS_Close(&f);
					Msg("Read File regs.bin Ok!!! h %d\r\n",f);
				} else {
					FS_Close(&f);
					Msg("Error Reset File regs.bin %d h %d\r\n",res,f);
				}
			} else {
				Msg("Error Assign File regs.bin %d\r\n",f);
				//FS_Close(&f);
			}
		} else {
			FS_Close(&f);
			Msg("Not Load regs.bin (err reset starup.cmd res %d) h %d\r\n",res,f);
		}
	} else {
		Msg("Not Load regs.bin (err assign starup.cmd res %d)\r\n",res);
		//FS_Close(&f);
	}
}

void	CloseFilesHandles(void){
	u32 fnt_num;
	u8 name[20];
	u8 type;
	u8 attr;
	u32 size;
	tFile f;
	s8 res;
	// ���������������� pPrgFileHandle
	fnt_num = 0;
	do {
		memset(name,sizeof name,0);
		res = FS_GetFileInfo(&fnt_num,name,&type,&attr,&size,&f);
		if (res == FS_RESULT_OK) {
			// ���� ������
			FS_Close(&f); // ���������
			// ���� ������
			fnt_num++;
		}
	} while (res == FS_RESULT_OK);
}

void	SaveRegs(void){
	s32 res;
	tFile f;
	u32 rbc;

	Msg("Save Regs\r\n");

	// ���� �� ��������� Rewrite
	FS_Delete("regs.bin"); 
	res = FS_Assign("regs.bin",&f); 
	if (res < 0) {	
		Msg("Error Assign regs.bin: %d\r\n",res);
	} else {
		res = FS_Rewrite(f);
		if (res == FS_RESULT_OK) {
			res = bFS_Write(f,regs,REGS_COUNT,&rbc);
			if (res < 0)
				Msg("Error Write regs.bin: %d\r\n",res);
		} else {
			Msg("Error Rewrite regs.bin: %d\r\n",res);
		}
	}
	res = FS_Close(&f);
	if (res<0)  Msg("Error Close regs.bin res:%d\r\n",res);

}

void	SaveRegsNoMes(void){
	s8 res;
	tFile f;
	u32 wbc;

	// ���� �� ��������� Rewrite
	FS_Delete("regs.bin"); 
	res = FS_Assign("regs.bin",&f); 
	if (res == FS_RESULT_OK) {	
		res = FS_Rewrite(f);
		if (res == FS_RESULT_OK) {
			res = bFS_Write(f,regs,REGS_COUNT,&wbc);
		} 
	}
	FS_Close(&f);
}

//*******************************************************************
//* �����������, ���������� ��� ������ �������� � �������� **********
u8 XPositOnHandle(char * name,u8 * buffer,u16 len){
	if (*buffer == 1) { 
		*ms_X.Posit = 0; 
		*ms_X.StagePos = 0;
	}
	return 0; 
}
u8 YPositOnHandle(char * name,u8 * buffer,u16 len){
	if (*buffer == 1) { 
		*ms_Y.Posit = 0; 
		*ms_Y.StagePos = 0;
	}
	return 0; 
}
u8 ZPositOnHandle(char * name,u8 * buffer,u16 len){
	if (*buffer == 1) { 
//		Msg("Zposit\r\n");
		*ms_Z.Posit = 0; 
		*ms_Z.StagePos = 0;
	}
	return 0; 
}

u8 pByPassHandle (char * name,u8 * buffer,u16 len){
	Index = 1;
	fStartMoveZLowSpeed = 0;
	return 0;
}

u8 pHorizDatHandle (char * name,u8 * buffer,u16 len){
	if (*buffer) {
		*pHorizDatState = 0;
		*pHorizDatDir = 0;
	}	
	return 0;
}

u8 PrgRunHandleFrz(char * name,u8 * buffer,u16 len){
	if (*buffer) {
			if (!*pPrgRun){
				fStartPrg = 1;
			}	
	}	else {
			if (*pPrgRun) {
				fStopPrg = 1;
			}	
	}	
	return 0;
}

u8 mvcVHandleFrz(char * name,u8 * buffer,u16 len){
//	float v;
	// ���������� � backup - ��������
	VChange = 1; // ������������� ������� ��������� ������
//	memcpy((void*)&(BR_fmvc_V),(void*)buffer,4);
//	memcpy((void*)&v,(void*)buffer,4);
//	Msg("Handle SetFeed %d ",(int)(v*1000));
	return 0;
}


void AllocFrzRegisters(void){
// ������ � ������
	memset(regs,0,REGS_COUNT);

	SetBase(0);
	SetAddr((void*)&pvPins,"pvPins",108,rw,NoHandle);

	// ������ ��������� ����������
	SetNewGroup();
	SetAddr((void*)&mc_X.LenOnPulse,"mc_X.LenOnPulse",4,rw,NoHandle);
	SetAddr((void*)&mc_Y.LenOnPulse,"mc_Y.LenOnPulse",4,rw,NoHandle);
	SetAddr((void*)&mc_Z.LenOnPulse,"mc_Z.LenOnPulse",4,rw,NoHandle);

	SetAddr((void*)&fmvc.LenOnPulse,"fmvc.LenOnPulse",4,rw,NoHandle);
//	SetAddr((void*)&pDirDelay,"pDirDelay",4,rw,NoHandle);
	
	SetNewGroup();
	SetAddr((void*)&pX_PG_MM,		"pX_PG_MM",			4,rw,NoHandle);
	SetAddr((void*)&pX_SPR,			"pX_SPR",			4,rw,NoHandle);
	SetAddr((void*)&pX_MIN,			"pX_MIN",			4,rw,NoHandle);
	SetAddr((void*)&pX_MAX,			"pX_MAX",			4,rw,NoHandle);

	SetAddr((void*)&pY_PG_MM,		"pY_PG_MM",			4,rw,NoHandle);
	SetAddr((void*)&pY_SPR,			"pY_SPR",			4,rw,NoHandle);
	SetAddr((void*)&pY_MIN,			"pY_MIN",			4,rw,NoHandle);
	SetAddr((void*)&pY_MAX,			"pY_MAX",			4,rw,NoHandle);

	SetAddr((void*)&pZ_PG_MM,		"pZ_PG_MM",			4,rw,NoHandle);
	SetAddr((void*)&pZ_SPR,			"pZ_SPR",			4,rw,NoHandle);
	SetAddr((void*)&pZ_MIN,			"pZ_MIN",			4,rw,NoHandle);
	SetAddr((void*)&pZ_MAX,			"pZ_MAX",			4,rw,NoHandle);
	
	SetNewGroup();
	// ������ ���������� �������� �� X
	SetAddr((void*)&mc_X.FrMin,		"mc_X.FrMin",		8,rw,NoHandle);
	SetAddr((void*)&mc_X.FrReq, 	"mc_X.FrReq",		8,rw,NoHandle);
	SetAddr((void*)&mc_X.FrMax,		"mc_X.FrMax",		8,rw,NoHandle);
	SetAddr((void*)&mc_X.Accel,		"mc_X.Accel",		4,rw,NoHandle);

	SetNewGroup();
	// ������ ���������� �������� �� Y
	SetAddr((void*)&mc_Y.FrMin,		"mc_Y.FrMin",		8,rw,NoHandle);
	SetAddr((void*)&mc_Y.FrReq, 	"mc_Y.FrReq",		8,rw,NoHandle);
	SetAddr((void*)&mc_Y.FrMax,		"mc_Y.FrMax",		8,rw,NoHandle);
	SetAddr((void*)&mc_Y.Accel,		"mc_Y.Accel",		4,rw,NoHandle);

	SetNewGroup();
	// ������ ���������� �������� �� Z
	SetAddr((void*)&mc_Z.FrMin,		"mc_Z.FrMin",		8,rw,NoHandle);
	SetAddr((void*)&mc_Z.FrReq, 	"mc_Z.FrReq",		8,rw,NoHandle);
	SetAddr((void*)&mc_Z.FrMax,		"mc_Z.FrMax",		8,rw,NoHandle);
	SetAddr((void*)&mc_Z.Accel,		"mc_Z.Accel",		4,rw,NoHandle);

	SetNewGroup();
	SetAddr((void*)&mc_X.ReqPos,	"mc_X.ReqPos",		4,rw,NoHandle);//*//4// ��������� �������
	SetAddr((void*)&mc_X.MovePos,	"mc_X.MovePos",		1,rw,NoHandle);//*//1// ��������� ������ �� �������
	SetAddr((void*)&mc_Y.ReqPos,	"mc_Y.ReqPos",		4,rw,NoHandle);//*//4// ��������� �������
	SetAddr((void*)&mc_Y.MovePos,	"mc_Y.MovePos",		1,rw,NoHandle);//*//1// ��������� ������ �� �������
	SetAddr((void*)&mc_Z.ReqPos,	"mc_Z.ReqPos",		4,rw,NoHandle);//*//4// ��������� �������
	SetAddr((void*)&mc_Z.MovePos,	"mc_Z.MovePos",		1,rw,NoHandle);//*//1// ��������� ������ �� �������


	SetNewGroup();
	// ������ ���������� �������� X
	SetAddr((void*)&mc_X.ReqDir,	"mc_X.ReqDir",		1,rw,NoHandle);
	SetAddr((void*)&mc_X.MoveBtn,	"mc_X.MoveBtn",		1,rw,NoHandle);

	SetNewGroup();
	// ������ ����������� �������� Y
	SetAddr((void*)&mc_Y.ReqDir,	"mc_Y.ReqDir",		1,rw,NoHandle);
	SetAddr((void*)&mc_Y.MoveBtn,	"mc_Y.MoveBtn",		1,rw,NoHandle);

	SetNewGroup();
	// ������ ���������� �������� Z
	SetAddr((void*)&mc_Z.ReqDir,	"mc_Z.ReqDir",		1,rw,NoHandle);
	SetAddr((void*)&mc_Z.MoveBtn,	"mc_Z.MoveBtn",		1,rw,NoHandle);

	SetNewGroup();
	// ��������� ���������������� �� �����������
	SetAddr((void*)&mc_X.PositOn,	"mc_X.PositOn",		1,rw,XPositOnHandle);
	SetAddr((void*)&mc_Y.PositOn,	"mc_Y.PositOn",		1,rw,YPositOnHandle);
	SetAddr((void*)&mc_Z.PositOn,	"mc_Z.PositOn",		1,rw,ZPositOnHandle);

	SetNewGroup();
	SetAddr((void*)&ms_X.FrCur,		"ms_X.FrCur",		8,ro,NoHandle);
	SetAddr((void*)&ms_Y.FrCur,		"ms_Y.FrCur",		8,ro,NoHandle);
	SetAddr((void*)&ms_Z.FrCur,		"ms_Z.FrCur",		8,ro,NoHandle);

	// ��. ������������� �� ��������
	SetAddr((void*)&ms_X.Dir,		"ms_X.Dir",			1,ro,NoHandle);
	SetAddr((void*)&ms_Y.Dir,		"ms_Y.Dir",			1,ro,NoHandle);
  	SetAddr((void*)&ms_Z.Dir,		"ms_Z.Dir",			1,ro,NoHandle);
	// Posit �� �������� ����� ��
/*	
	SetAddr((void*)&ms_X.Posit, 	"ms_X.Posit",		1,ro,NoHandle);
	SetAddr((void*)&ms_Y.Posit, 	"ms_Y.Posit",		1,ro,NoHandle);
	SetAddr((void*)&ms_Z.Posit, 	"ms_Z.Posit",		1,ro,NoHandle);
*/	
	SetAddr((void*)&ms_X.Posit, 	"ms_X.Posit",		1,rw,NoHandle);
	SetAddr((void*)&ms_Y.Posit, 	"ms_Y.Posit",		1,rw,NoHandle);
	SetAddr((void*)&ms_Z.Posit, 	"ms_Z.Posit",		1,rw,NoHandle);

	// StagePos ������� ����� ��
	SetAddr((void*)&ms_X.StagePos, 	"ms_X.StagePos",		1,ro,NoHandle);
	SetAddr((void*)&ms_Y.StagePos, 	"ms_Y.StagePos",		1,ro,NoHandle);
	SetAddr((void*)&ms_Z.StagePos, 	"ms_Z.StagePos",		1,ro,NoHandle);
	
	// ��������� �������� � ���
	SetNewGroup();
	SetAddr((void*)&pFdbyFnom,	"pFdbyFnom",	2,rw,NoHandle);	//*// 
	SetAddr((void*)&pFnom,			"pFnom",			2,rw,NoHandle);	//*// 
  SetNewGroup();
	// ��� �������� ���� ��� 2
	SetAddr((void*)&pFIPWM, "pFIPWM",			4,rw,NoHandle);
	// ������������ ������� ��� ��� �� ���� ��� 2
	SetAddr((void*)&pFIPWMFreq, "pFIPWMFreq",			4,rw,NoHandle);

	// ����� ������ ���������
	// ByPass ������� ����� ��
	SetNewGroup();
	SetAddr((void*)&pByPass, 	"pByPass",		1,rw,pByPassHandle);
	// ����� ��������� ������ �����������
	SetAddr((void*)&pHTCorr, 	"pHTCorr",		1,rw,pByPassHandle);
	// ����� ��������� ���������� Z �� �������
	SetAddr((void*)&pZZeroDat, 	"pZZeroDat",		1,rw,pByPassHandle);
	// ����� ������ �� ��������������� �������
	SetAddr((void*)&pHorizontalDat, 	"pHorizontalDat",		1,rw,pHorizDatHandle);
	// ����������� �������������� ������� 0 off 1 up 2 left 3 down 4 right
	SetAddr((void*)&pHorizDatDir, 	"pHorizDatDir",		1,rw,NoHandle);
	// ��������� ���������� �������������� ������� 0 off 1 go 2 ok 3 fault
	SetAddr((void*)&pHorizDatState, 	"pHorizDatState",		1,ro,NoHandle);
	
	SetNewGroup();
	// ������� ������ �������
	SetAddr((void*)&pHorizDiam, 	"pHorizDiam",		4,rw,NoHandle);
	// ����������� ���������
	SetAddr((void*)&pHorizMeasError, 	"pHorizMeasError",		4,rw,NoHandle);
	// ���������� X ����� ������������ �������
	SetAddr((void*)&pHorizX, 	"pHorizX",		4,rw,NoHandle);
	// ���������� Y ����� ������������ �������
	SetAddr((void*)&pHorizY, 	"pHorizY",		4,rw,NoHandle);
	

	// �������� ������� ����� � ���������
	SetNewGroup();
	SetAddr((void*)&dXPos,		"dXPos",			4,rw,NoHandle);
	SetAddr((void*)&dYPos,		"dYPos",			4,rw,NoHandle);
	SetAddr((void*)&dZPos,		"dZPos",			4,rw,NoHandle);
	
	// ����� ����������� ���������
	SetNewGroup();
	// ���������� X1
	SetAddr((void*)&pX1,			"pX1",			4,rw,NoHandle);	
	// ���������� Y1
	SetAddr((void*)&pY1,			"pY1",			4,rw,NoHandle);	
	// ���������� Z1
	SetAddr((void*)&pZ1,			"pZ1",			4,rw,NoHandle);	
	// ���������� X2
	SetAddr((void*)&pX2,			"pX2",			4,rw,NoHandle);	
	// ���������� Y2
	SetAddr((void*)&pY2,			"pY2",			4,rw,NoHandle);	
	// ���������� Z2
	SetAddr((void*)&pZ2,			"pZ2",			4,rw,NoHandle);	
	// ���������� X3
	SetAddr((void*)&pX3,			"pX3",			4,rw,NoHandle);	
	// ���������� Y3
	SetAddr((void*)&pY3,			"pY3",			4,rw,NoHandle);	
	// ���������� Z3
	SetAddr((void*)&pZ3,			"pZ3",			4,rw,NoHandle);	

	SetAddr((void*)&pA,			"pA",			4,rw,NoHandle);	
	SetAddr((void*)&pB,			"pB",			4,rw,NoHandle);	
	SetAddr((void*)&pC,			"pC",			4,rw,NoHandle);	
	SetAddr((void*)&pD,			"pD",			4,rw,NoHandle);	

	SetNewGroup();
	// ����������� �������� �������
	SetAddr((void*)&fmvc.Vmin,		"fmvc.Vmin",			4,rw,NoHandle);	
	// ���������
	SetAddr((void*)&fmvc.Vaccel,	"fmvc.Vaccel",		4,rw,NoHandle);	
	// ���������
	SetAddr((void*)&fmvc.Vmul,		"fmvc.Vmul",			4,rw,NoHandle);	
	// ������ ������� � ��
	SetAddr((void*)&pHdat,			"pHdat",			4,rw,NoHandle);	
	//����������� ����
	SetAddr((void*)&pTrAngle,"pTrAngle"	,sizeof (*pTrAngle),rw,NoHandle);
	// ����� ������� ��������
	SetAddr((void*)&pRunSpPause,	"pRunSpPause",			4,rw,NoHandle);	

	// ��������� ������ �� 485
	SetNewGroup();
	// ���������� �� ������������� ������ �� RS-485
	SetAddr((void*)&pUsesKP485, "pUsesKP485", 	1,rw,NoHandle);
	// ����� ������
	SetAddr((void*)&pAddrKPCtrl, "pAddrKPCtrl",			1,rw,NoHandle);// �� ���� ����� ���������� ����� �������� ���������� ������� 
	// ������������ ���������� ����� �� ������ �������������
	SetAddr((void*)&pKP_NA_Max, "pKP_NA_Max",			1,rw,NoHandle);
	
	SetNewGroup();
	// �������� ������ ������ � ������ ����
	SetAddr((void*)&pIntKPCtrl, "pIntKPCtrl",			2,rw,NoHandle);
	// �������� ������ ������ � ������ ����
	SetAddr((void*)&pIntKPCtrlStop, "pIntKPCtrlStop",			2,rw,NoHandle);
	// ������� �������� � �� 
	SetAddr((void*)&pQUTimeout, 	"pQUTimeout",			2,rw,NoHandle);
	// ���������� ��������
	SetAddr((void*)&pQURepCount, 	"pQURepCount",			1,rw,NoHandle);

	SetNewGroup();
	// Pos �������� ��� ��������� ����� ��������
	SetAddr((void*)&ms_X.Pos,		"ms_X.Pos",			4,ro,NoHandle);
	SetAddr((void*)&ms_Y.Pos,		"ms_Y.Pos",			4,ro,NoHandle);
	SetAddr((void*)&ms_Z.Pos,		"ms_Z.Pos",			4,ro,NoHandle);
	SetAddr((void*)&pPrgRun,	"pPrgRun",			 	1,rw,PrgRunHandleFrz);
	SetAddr((void*)&pCurCadr,		"pCurCadr",		 	4,rw,pCurCadrHandleFrz);
	SetAddr((void*)&pNumReadLine,		"pNumReadLine",		 	4,ro,NoHandle);
	// �������� ��� ��������� ����� ��
	SetAddr((void*)&pRCS,		"pRCS"					,1,rw,NoHandle);
	// �������� ����� � �� � ���
	SetAddr((void*)&fmvs.Vc,			"fmvs.Vc",			4,ro,NoHandle);	
	// �������� ����� � �� � ���
	SetAddr((void*)&fmvc.V,			"fmvc.V",			4,rw,mvcVHandleFrz);	
	// ��������� �����
	SetAddr((void*)&pCrushWater,"pCrushWater",			1,rw,NoHandle);	
	// ����� � ������������ ����� RS-485
	SetAddr((void*)&pLinkKP,"pLinkKP",			1,ro,NoHandle);	
//	SetAddr((void*)&pCorrStop,"pCorrStop",			1,ro,NoHandle);	
	SetAddr((void*)&pCorrStop,"pCorrStop",			1,rw,NoHandle);	
	SetAddr((void*)&pRecoverBlock,"pRecoverBlock",			1,ro,NoHandle);	
	SetAddr((void*)&pfZcomp,"pfZcomp",			1,ro,NoHandle);	
	
	SetNewGroup();
	SetAddr((void*)&pPrgFileName,"pPrgFileName"	,sizeof (*pPrgFileName),rw,NoHandle);
	SetAddr((void*)&pPrgFileHandle,"pPrgFileHandle"	,sizeof (*pPrgFileHandle),rw,NoHandle);
	SetAddr((void*)&pPrgLineCount,"pPrgLineCount"	,sizeof (*pPrgLineCount),rw,NoHandle);
	SetAddr((void*)&pWF_CRC,"pWF_CRC"	,2,rw,NoHandle);
	
	
	
	SetNewGroup();
	// �������� ���� ��������
	SetAddr((void*)&pDrDelay, 	"pDrDelay",			2,	rw,pDrDelayHandle);
	// ����� DoubleClick � 0,01 � 
	SetAddr((void*)&pDCTime, "pDCTime",		2,	rw,pDCTimeHandle);
	// ����������� �������� �������� � ���������
	SetAddr((void*)&pPercVmin, 	"pPercVmin",	2,	rw,pPercVminHandle);
	// �������� ���������� ��������� -100 +100
	SetAddr((void*)&pYmove, 		"pYmove"	, 	2,	rw,NoHandle);
	SetAddr((void*)&pZmove,		"pZmove"	, 	2,	rw,NoHandle);
	SetAddr((void*)&pXmove,			"pXmove"	, 	2,	rw,NoHandle);
	SetAddr((void*)&pUnusedmove,		"pUnusedmove"	, 	2,	rw,NoHandle);
	// 5 ������ 0 100
	SetAddr((void*)&pBtn5,			"pBtn5"		, 	2,	rw,NoHandle);
// ������������ ���� 0 ��� 100 �� ������ 6
	SetAddr((void*)&pAxisSwitch,	"pAxisSwitch", 	2,	rw,NoHandle);
// �������
	SetAddr((void*)&pBUZZ,			"pBUZZ", 	2,	rw,NoHandle);	

	SetNewGroup();
// ����������� ��������� ���������� ��������� �� RS-485
	SetAddr((void*)&pACmdDump, 		"pACmdDump",			1,rw,NoHandle);
	SetAddr((void*)&pAMsg,			"pAMsg",			1,rw,NoHandle);
	SetAddr((void*)&pAAnswDump, 	"pAAnswDump",			1,rw,NoHandle);
// ����������� ��������� ��������� �� RS-485
	SetAddr((void*)&pAECmdDump, 	"pAECmdDump",			1,rw,NoHandle);
	SetAddr((void*)&pAEMsg, 		"pAEMsg",			1,rw,NoHandle);
	SetAddr((void*)&pAEAnswDump, 	"pAEAnswDump",			1,rw,NoHandle);
// ����������� �� ���������� ���������
	SetAddr((void*)&pANCmdDump, 	"pANCmdDump",			1,rw,NoHandle);
	SetAddr((void*)&pANMsg, 		"pANMsg",			1,rw,NoHandle);
// ����������� ������ ����������� ����� UART1
	SetAddr((void*)&pErrCSU1, 		"pErrCSU1",			1,rw,NoHandle);
// ����������� �������� ������ �� ���������� � �������
	SetAddr((void*)&pDropCmd, 		"pDropCmd",			1,rw,NoHandle);

	SetNewGroup();
	// �������� ��� ��������� ����� ��
	SetAddr((void*)&pBlock,		"pBlock"				,sizeof (*pBlock),ro,NoHandle);
//	SetAddr((void*)&eb,		"pBlock"				,sizeof (*pBlock),ro,NoHandle);
	// ������ ���������
	// �������� ��� ��������� ����� ��
	SetNewGroup();
//	SetAddr((void*)&pBusy,		"pbusy",			1,rw,NoHandle);
//	SetAddr((void*)&psG0,		"psG0",			 	1,rw,NoHandle);
//	SetAddr((void*)&pscz,		"pscz",			 	804,rw,NoHandle);

}

void InitFrzRegisters (void) {
	
	// ������������� ����� �������� �� ���������
	memcpy(pvPins,&vPinsdef,sizeof vPinsdef);
	// ������������ ������� ������� �����
	FormQPinTable();
	// X
 	// �������� ������� ���������� ��������
	*pX_PG_MM = 120.0; // (��)
	// ����� �� ������ ������� ��������
	*pX_SPR = 4000;
	*pX_MIN = 0; 
	// ����������� ������� �� X � �����
	vX_MIN_POS = (s32)((*pX_MIN) * ((*pX_SPR)/(*pX_PG_MM))); 
	// ������������ ������� �� ������� � ��
	*pX_MAX = 1500;
	// ������������ ������� �� X � �����
	vX_MAX_POS = (s32)((*pX_MAX) * ((*pX_SPR)/(*pX_PG_MM))); 
	// Y
 	// �������� ������� ���������� ��������
	*pY_PG_MM = 120.0; // (��)
	*pY_SPR = 4000;
	*pY_MIN = 0; 
	vY_MIN_POS = (s32)((*pY_MIN) * ((*pY_SPR)/(*pY_PG_MM))); 
	*pY_MAX = 1500;
	// ������������ ������� �� X � �����
	vY_MAX_POS = (s32)((*pY_MAX) * ((*pY_SPR)/(*pY_PG_MM))); 
	// Z
	*pZ_PG_MM = 10.0; // (��)
	*pZ_SPR = 400;
	*pZ_MIN = 0; 
	vZ_MIN_POS = (s32)((*pZ_MIN) * ((*pZ_SPR)/(*pZ_PG_MM))); 
	*pZ_MAX = 165;
	vZ_MAX_POS = (s32)((*pZ_MAX) * ((*pZ_SPR)/(*pZ_PG_MM))); 
	
	InitMotorStructF(&ms_X,&mc_X);
	InitMotorStructF(&ms_Y,&mc_Y);
	InitMotorStructF(&ms_Z,&mc_Z);
	*(ms_X.Pos) = X_MIN_POS+(X_MAX_POS-X_MIN_POS)/2;
	*(ms_Y.Pos) = Y_MIN_POS+(Y_MAX_POS-Y_MIN_POS)/2;
	*(ms_Z.Pos) = Z_MIN_POS+(Z_MAX_POS-Z_MIN_POS)/2;
	
//	XCPos = X_MIN_POS+(X_MAX_POS-X_MIN_POS)/2;
//	YCPos = Y_MIN_POS+(Y_MAX_POS-Y_MIN_POS)/2;
//	ZCPos = Z_MIN_POS+(Z_MAX_POS-Z_MIN_POS)/2;
	
	*(mc_Z.FrReq) = 500*K1;
	*(mc_Z.FrMax) = 500*K1;
	*(fmvc.LenOnPulse)=5000;
	fmvc.Enable=0;
	
    *(fmvc.V)=0.5;
    *(fmvc.Vmin)=0.5;
    *(fmvc.Vaccel)=16.7;
    *(fmvc.Vmul)=100;
//    *(fmvc.Break)=0;
	fmvs.Level = 0;
	*(fmvs.Vc) = *(fmvc.Vmin);
	fmvs.LPON = *(fmvc.LenOnPulse);
	fmvs.LPOFF = 1000;
	// ����� ��������� ��������
	*pByPass = 0;
	*pHTCorr = 0; 
	*pZZeroDat = 0;
	// ����� ������� ���������
//	memset((void*)pscz,0,804);
	*pPrgRun = 0;
	// ������������� ��������� "������ ������" - ��� ������ ��������� ���������� �����
	*pCurCadr = 0; // ������� ����� �����
	
	*pRCS = rcsGetBlock; // ��������� ���������� ����� "������ ��������� ������" 
	
	*pRecoverBlock = 0; // ���� ������������	
	
	// ���������� ����� ���������
 	*pPrgFileHandle=-1;
	// ��� ����� ��������� � G-����
	memset((void*)pPrgFileName,0,20);
	*pCrushWater = 0;
	// ��������
 	*dXPos=0;
 	*dYPos=0;
 	*dZPos=0;

	// ���������� �� ������������� ������ �� RS-485
	*pUsesKP485 = 1; // ��������� 1-���������
	
	// �������� ���� �������� � 0,0001 �
	*pDrDelay = 50;
	// ����� DoubleClick � 0,01 � 
	*pDCTime = 50; // 0,5 ��� 
	// ������� ���������� �������� (� ����� ��������? %/� ?)
	*pPercVmin = 5; // %/c ???????
	// �������� ���������� ��������� -100 +100
	*pYmove = 0;
	*pZmove = 0;
	*pXmove = 0;
	*pUnusedmove = 0;
	// 5 ������ 0 100
	*pBtn5 = 0;
	// ������������ ���� 0 ��� 100 �� ������ 6
	*pAxisSwitch = 0; // ������� ��� R � A 
	// �������
	*pBUZZ = 0;
	*pQURepCount = 3; // 3 ������� �� ���������
 	*pQUTimeout = 100; // 100 �� �������� 

// ����������� ��������� ���������� ��������� �� RS-485
	*pACmdDump = 0;
	*pAMsg = 0;
	*pAAnswDump = 0;
// ����������� ��������� ��������� �� RS-485
	*pAECmdDump = 0;
	*pAEMsg = 0;
	*pAEAnswDump = 0;
// ����������� �� ���������� ���������
	*pANCmdDump = 0;
	*pANMsg = 0;
// ����������� ������ ����������� ����� UART1
	*pErrCSU1 = 0;
	// ����������� �������� ������ �� ���������� � �������
	*pDropCmd = 0;
// ��������� ���������� ������ ��� ��������� ��� ������
	*pKP_NA_Max = 1;

// ���������� ������ ��� ��������� ��� ������
	KP_NA_Count = 0;
// ����� � �� 
	*pLinkKP = 0;
// ������� ���������� ��������� 
	*pCorrStop = 0;

	// ����� ������
	*pAddrKPCtrl = 4;
	
	// ��������� ������ ��
	*pIntKPCtrl = 5000;
	*pIntKPCtrlStop = 100;
	*pTrAngle = 15.0;	

	*pFIPWM = 2000;
	*pFIPWMFreq = 3000;

	fStopPrg = 0;
	fStartPrg = 0;
	fSaveRegs = 0;

	*pX1=0;
	*pY1=0;
	*pZ1=0;
	*pX2=0;
	*pY2=0;
	*pZ2=0;
	*pX3=0;
	*pY3=0;
	*pZ3=0;
	*pHdat = 23.6;
	// ������ ���������� �����
	Index = 1;
	// ����������� �����������
	*pfZcomp = 0;
// ������� �������� ���� ��/��� ��� ����������� ������� ���� pFnom ��
	*pFdbyFnom = 18000;	
// ����������� ������� ���� ��
	*pFnom = 300;	
	
	*pRunSpPause = 5000;
	// ����������� ����� ���������� ����� ���������
	*pWF_CRC = 0;
	// �������� ��� ��������� ����������� 200 ��� 
//	*pDirDelay = 5000;
}

void InitFrzRegsAfterLoad(void){
	// ������������� ��������� ���������� ���������� 
	InitMotorStructALF(&ms_X,&mc_X);
	InitMotorStructALF(&ms_Y,&mc_Y);
	InitMotorStructALF(&ms_Z,&mc_Z);
	*pByPass = 0;
	*pHTCorr = 0; 
	*pZZeroDat = 0;
	
	if (*pPrgRun) {
		*pPrgRun = 0;
		BR_pPrgRun = *pPrgRun;
	}		
	vX_MIN_POS = (s32)((*pX_MIN) * (X_SPR/(*pX_PG_MM))); 
	vX_MAX_POS = (s32)((*pX_MAX) * (X_SPR/(*pX_PG_MM))); 
	vY_MIN_POS = (s32)((*pY_MIN) * (Y_SPR/(*pY_PG_MM))); 
	vY_MAX_POS = (s32)((*pY_MAX) * (Y_SPR/(*pY_PG_MM))); 
	vZ_MIN_POS = (s32)((*pZ_MIN) * (Z_SPR/(*pZ_PG_MM))); 
	vZ_MAX_POS = (s32)((*pZ_MAX) * (Z_SPR/(*pZ_PG_MM))); 
	// CloseFilesHandles();
	// ���������������� pPrgFileHandle
	*pPrgFileHandle = -1;
//	Msg("%d\r\n",OUTF1(1.0*ms_Y.LPON));
	fmvs.LPON = *(fmvc.LenOnPulse);
	
}

void LoadFrzBackupRegs(void){
/*
#define BR_ms_X_Pos LPC_RTC->GPREG0
#define BR_ms_Y_Pos LPC_RTC->GPREG1
#define BR_ms_Z_Pos	LPC_RTC->GPREG2
#define BR_fmvc_V	LPC_RTC->GPREG3
#define BR_pCurCadr	LPC_RTC->GPREG4
#define BR_pPrgRun	LPC_RTC->ALSEC
#define BR_pPrgPause	LPC_RTC->ALMIN
#define BR_pCorrStop	LPC_RTC->ALDOW 

*/
	tFile f;
	s8 res;
	// ������� ���� regs.bin
	res = FS_Assign("startup.cmd",&f);
	if (res == FS_RESULT_OK) {
		res = FS_Reset(f);
		if (res == FS_RESULT_OK) {
			FS_Close(&f);
			//	���� ���� - �������� ���������

			*(ms_X.Pos) = BR_ms_X_Pos;
			*(ms_Y.Pos) = BR_ms_Y_Pos;
			*(ms_Z.Pos) = BR_ms_Z_Pos;
			//memcpy((void*)mvc.V,(void*)&(BR_mvc_V),4);
			//*(fmvc.V) = BR_fmvc_V;
			//memcpy((void*)pCurCadr,(void*)&(BR_pCurCadr),2);	
			//*pCurCadr = BR_pCurCadr;
			
//			memcpy((void*)fmvc.V,(void*)&(BR_fmvc_V),4);
			memcpy((void*)pCurCadr,(void*)&(BR_pCurCadr),4);
			if (*pCurCadr) *pRecoverBlock = 1;
			else *pRecoverBlock = 0;
//			Msg("pCurCadr %d RecBlock %d\r\n",*pCurCadr,*pRecoverBlock);
			*pPrgRun = BR_pPrgRun;
			*pCorrStop = BR_pCorrStop;
			if (*pPrgRun) {
				*pPrgRun = 0;
				BR_pPrgRun = *pPrgRun;
			}	
			Msg("Load Backup Regs Ok.\r\n");
			
		} else {
			// ����� ��� - ������ ���������

			BR_ms_X_Pos = *(ms_X.Pos);
			BR_ms_Y_Pos = *(ms_Y.Pos);
			BR_ms_Z_Pos = *(ms_Z.Pos);

//			memcpy((void*)&(BR_fmvc_V),(void*)fmvc.V,4);
			memcpy((void*)&(BR_pCurCadr),(void*)pCurCadr,4);
//			Msg("BR_pCurCadr %d\r\n",BR_pCurCadr);
			BR_pPrgRun = *pPrgRun;
			BR_pCorrStop = *pCorrStop;
			FS_Close(&f);
			Msg("Not Load Backup Regs. (err reset startup.cmd %d) h %d\r\n",res,f);
		}
	} else {
		Msg("Not Load Backup Regs. (err assign startup.cmd %d)\r\n",res);
		//FS_Close(&f);
	}
}

