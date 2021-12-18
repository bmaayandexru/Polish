#ifndef __REGS_H__
#define __REGS_H__

//#include <RTL.h>   
#include "Defs.h"
#include "LPC17xx.h"
#include "motors.h"

// ����� ���������� ���������
#define REGS_COUNT		1000

// �������� ����������
// ������ � ������
#define rw 0
// ������ ������
#define ro 1
// ��������� ����������� ��� �������������� ������
#define NoHandle 0

// �������� ������� ���������� �������� � ��
// ���� ���������� �� (120) ������ ��� ������� ����� ������
// ��� ������� double
#define	R_PG_MM	(*pR_PG_MM)
// ����� �� ������ ������� �������� �� �������
#define R_SPR	(*pR_SPR)
// ����� �� ������ �� ����
//#define A_SPR	(72000)
#define A_SPR	(int)(*pA_SPR)
#define A_SPRH	(A_SPR/2)
#define A_MIN_POS (-(int)A_SPRH+1)
#define A_MAX_POS ((int)A_SPRH)

// ����� �� ������ �� ��������
#define Vu_SPR	(int)(*pVu_SPR)
#define Vu_SPRH	(Vu_SPR/2)
#define Vu_MIN_POS (-(int)Vu_SPRH+1)
#define Vu_MAX_POS ((int)Vu_SPRH)

#define Vd_SPR	(int)(*pVd_SPR)
#define Vd_SPRH	(Vd_SPR/2)
#define Vd_MIN_POS (-(int)Vd_SPRH+1)
#define Vd_MAX_POS ((int)Vd_SPRH)

#define R_MIN_POS vR_MIN_POS
//#define R_MIN_POS 7466
#define R_MAX_POS vR_MAX_POS
//#define R_MAX_POS 35000

#ifdef __SAW__
// Backup-��������
#define BR_ms_A_Pos LPC_RTC->GPREG0
#define BR_ms_R_Pos LPC_RTC->GPREG1
#define BR_mvc_V	LPC_RTC->GPREG2
#define BR_ms_Vud_Pos	LPC_RTC->GPREG3
//#define BR_ms_Vd_Pos	LPC_RTC->GPREG4
#define BR_pCurCadr	LPC_RTC->GPREG4
#define BR_pPrgRun	LPC_RTC->ALSEC
#define BR_pPrgPause	LPC_RTC->ALMIN
#define BR_pPrgDir	LPC_RTC->ALHOUR

/*
// ���������� �������� ������� ����� ������������
  __IO uint16_t ALDOY; // �� 512 ������� ������
  __IO uint8_t	LPC_RTC->ALDOM
	__IO uint8_t	LPC_RTC->ALDOW
	__IO uint8_t	LPC_RTC->ALMON
*/
#endif


#ifdef __FREZER__
#define	X_PG_MM	(*pX_PG_MM)
#define X_SPR	(*pX_SPR)
#define X_MIN_POS vX_MIN_POS
#define X_MAX_POS vX_MAX_POS
#define	Y_PG_MM	(*pY_PG_MM)
#define Y_SPR	(*pY_SPR)
#define Y_MIN_POS vY_MIN_POS
#define Y_MAX_POS vY_MAX_POS
#define	Z_PG_MM	(*pZ_PG_MM)
#define Z_SPR	(*pZ_SPR)
#define Z_MIN_POS vZ_MIN_POS
#define Z_MAX_POS vZ_MAX_POS

// Backup-�������� �������
#define BR_ms_X_Pos LPC_RTC->GPREG0
#define BR_ms_Y_Pos LPC_RTC->GPREG1
#define BR_ms_Z_Pos	LPC_RTC->GPREG2
#define BR_FilePos	LPC_RTC->GPREG3
//#define BR_fmvc_V	LPC_RTC->GPREG3
#define BR_pCurCadr	LPC_RTC->GPREG4
#define BR_pPrgRun	LPC_RTC->ALSEC
#define BR_pCorrStop	LPC_RTC->ALDOW 

/*
// ���������� �������� ������� ����� ������������
#define BR_pPrgPause	LPC_RTC->ALMIN
#define BR_OnTros	LPC_RTC->ALDOW 
#define BR_OnTable	LPC_RTC->ALMON
#define BR_pPrgDir	LPC_RTC->ALHOUR

  __IO uint16_t ALDOY; // �� 512 ������� ������
  __IO uint8_t	LPC_RTC->ALDOM
#define BR_pPrgPause	LPC_RTC->ALMIN
*/

#endif
// ������ ����������
// ����������� �������
#define TRE_UNKNOWN_CMD	1
// ������ �������������� ���������
#define TRE_PARAM_ERROR	2
// ����������� G-�������
#define TRE_UNKNOWN_G	3
// ����������� M-�������
#define TRE_UNKNOWN_M	4
// �������� F < 0
#define TRE_LESSZERO_F	5
// �������� S < 0
#define TRE_LESSZERO_S	6
// �������� P < 0
#define TRE_LESSZERO_P	7
// ������ ������ (� ������ ch == 13)
#define TRE_LINE_EMPTY 	8

// ��������� � �����
typedef __packed struct tagFInfo{ 
	u32		index;     
    char 	name[14];
    char 	ext[4];
    u8	 	attr;
    u32 	size;
    u8	 	f;
} FInfo;

// ��� ���������� ������������� ������ ����������
typedef u8(*TWHandler)(char * name,u8 * buffer,u16 len);

// ��������� ���������� ����������
typedef struct {
	char 	name[20];	// ���
	void 	*p;			// ���������
	u16		len;		// ����� ����
	u32		attr;		// ��������
	TWHandler	handle; // ���������� ������
} TVarAttr;

typedef struct {
	float X,Y;
} TPoint;

typedef TPoint TPoints[100];

typedef struct {
	u32 Count;
	TPoints points;
} TContur;

// ����������� ��������� ����� ����
typedef struct tagTBlock { 
	s32		NumLine;	// ����� ������
	s32 	PosSSP;		// ������� ��������� ����� ��������� � ������� ���������� ����� ����� ��������
	u8 		Nonstop;	// 0 - ���� � ���������� (������������� � main)
						// 1 - ���� ��� ��������� (������������� � ����������)
	u8		cFeed;		// ������� ������� �������� ������
    float 	Feed;    	// �������� ������ ��/�
    float 	Speed;    	// �������� ����� � �/�
    u8 		cSpindel;   // ������� ������� ���������� ���������
    u8 		sSpindel;   // ������ 0-����.
                        // 1-�������� �� �������
                        // 2-�������� ������ �������
    u8 		cCold;      // ������� ������� ����������
    u8 		sCold1;     // ������ 0-���������� 1 ����.
                        // 1-���������� 1 ���.
    u8 		sCold2;     // ������ 0-���������� 2 ����.
                        // 1-���������� 2 ���.
    u8 		cPause;     // ������� ������� "�����"
    u32 	lPause;  	// ����� ����� � ��

		u8 		cStop;      // ������� ������� "����"
    u8 		sStop;      // c����� ������� ����
                        // 0 - ����� �� ������ �����
                        // 1 - ������� � ��������������
                        // 2 - ������ ����������
    u8 		sGo;      	// ��� ��������
                        // 0 - ������� �����������
                        // 1 - ������������� ��������
    float 	Mul;    	// ��������� ������� = 1 ��� 25.3 (�� �����)
    float 	rMul;    	// ��������� ���������
    u8 		SetSizeReg; // ����� �������� �������� �������
                        // 0 - ���������� ����������
                        // 1 - ����������
    u8 		rSetSizeReg;// ����� �������� �������� ���������
    float 	Xs,Ys,Zs;  	// ������� ���������� � ��
    u8 		comX,comY,comZ;  // ������� ��������� �������� �� X � Y
    float 	Xr,Yr,Zr;    	// ��������� �������� X � Y
    float 	Xd,Yd,Zd;    	// ����� ����������
	s32		Xi,Yi,Zi;		// �������� ��������� � ���������
	s32		Xsi,Ysi,Zsi;	// ��������� ��������� � ���������
	s32		Xdi,Ydi,Zdi;	// �������� ��������� � ���������
	s32		dXi,dYi,dZi;	// ���������� � ���������
	s32		signX,signY,signZ;	//4+4// ����������� 
	s32		e1;				//4//������ � ��������� �����������
	s32		e2;				//4//������ � ��������� �����������
	u8 		Lax; 			// ������� ��� 0-x	1-y 2-z
	s32   Laxi;			// ���������� ����� �� ������� ���
	float Li;				// ����� ������� � ��������� (�������) sqrt(x*x+y*y+z*z);
	u8 		Nomove;			// ���� 1 ���� ��� �������� ��� ���������� ����� 0
	float 	dS;				// ���������� ���� ��� ����� �������� �����������
							// ��������� �� Sr
	u32		Tb;				// �������� ������������ ��� ������ ������� ������� �������� T = Tb/Vc
	char s[50];
	s32 FilePos; // ������� � ����� �������������� �����
} TBlock;

typedef u8 TFileName[20];

// ����� ����������
extern TFileName * pPrgFileName;
extern s8 * pPrgFileHandle;
extern u32 * pPrgLineCount;
extern u16 * pWF_CRC;

extern u8 *pCrushWater;
extern u8 *pByPass;

//extern volatile BOOL	fU1toU0;

extern u8 		regs[REGS_COUNT]; // registers
extern u16		iva;	// ���������� ����������� ����������
extern TVarAttr 	va[]; 	// ������ ���������

//extern TContur * pscz;

extern u8 OutAllocTable;
extern u32 CurVarIndex;
extern u8	VChange;
// ������� �������� ���� ��/��� ��� ����������� ������� ���� pFnom
extern u16 *pFdbyFnom;	
// ����������� ������� ����
extern u16	*pFnom;

// �������� ������������ �������
extern u8 *pQURepCount; // ���������� ��������
extern u16 *pQUTimeout; // �������
// ����������� ��������� ���������� ��������� �� RS-485
extern u8 *pACmdDump;
extern u8 *pAMsg;
extern u8 *pAAnswDump;
// ����������� ��������� ��������� �� RS-485
extern u8 *pAECmdDump;
extern u8 *pAEMsg;
extern u8 *pAEAnswDump;
// ����������� �� ���������� ���������
extern u8 *pANCmdDump;
extern u8 *pANMsg;
// ����������� ������ ����������� ����� UART1
extern u8 *pErrCSU1;
// ����������� �������� ������ �� ���������� � �������
extern u8 *pDropCmd;
// ���������� ������ ��� ��������� ��� ������
extern u8	*pKP_NA_Max;
// ���������� ������ ��� ��������� ��� ����
extern u8	*pPress_NA_Max;
// ���������� ������ ��� ��������� ��� ������
extern u8	KP_NA_Count;
// ����� � �� 
extern u8 *pLinkKP;

// ���������� �������

// ������ X
extern float 	*pX_PG_MM;
extern u32		*pX_SPR;
extern float	*pX_MIN;
extern float	*pX_MAX;
extern s32 		vX_MIN_POS; 
extern s32 		vX_MAX_POS; 
// ������ Y
extern float 	*pY_PG_MM;
extern u32		*pY_SPR;
extern float	*pY_MIN;
extern float	*pY_MAX;
extern s32 		vY_MIN_POS; 
extern s32 		vY_MAX_POS; 
// ������ Z
extern float 	*pZ_PG_MM;
extern u32		*pZ_SPR;
extern float	*pZ_MIN;
extern float	*pZ_MAX;
extern s32 		vZ_MIN_POS; 
extern s32 		vZ_MAX_POS; 

// �������� ������ ������ ���������
extern s32 * dXPos;
extern s32 * dYPos;
extern s32 * dZPos;

// ���������� �� ������������� ������ �� RS-485
//extern u8	*pUsesKP485;

// ��������� ������ ���������� ������ ����
extern u16 *pIntKPCtrl;
extern u16 *pIntKPCtrlStop;

// ���������� ������ ��� ��������� ��� ������
extern u8	*pKP_NA_Max;


// ����� � �� 
extern u8 *pLinkKP;
// ���������� ������ ��� ��������� ��� ������
extern u8	KP_NA_Count;
// ������� ���������� ��������� 
extern u8 *pCorrStop;
// ������� �������������� �������� �����
extern u8 *pRecoverBlock;
// ����� ��������� ������ �����������
extern u8 *pHTCorr; 
// ����� ��������� ���������� Z �� �������
extern u8 *pZZeroDat; 
// ����� ������ �� ��������������� �������
extern u8 *pHorizontalDat;
// ����������� �������������� ������� 0 off 1 up 2 left 3 down 4 right
extern u8 *pHorizDatDir;
// ��������� ���������� �������������� ������� 0 off 1 go 2 ok 3 fault
extern u8 *pHorizDatState;
	// ������� ������ �������
extern float *pHorizDiam;
	// ����������� ���������
extern float *pHorizMeasError;
// ���������� X ����� ������������ �������
extern float *pHorizX;
// ���������� Y ����� ������������ �������
extern float *pHorizY;



// ������� ��������� ��� ����� ���������� ���������
extern u8	fStopPrg;
// ������� ����� ���������
extern u8	fStartPrg;
// ���� ���������� ���������
extern u8	fSaveRegs;

// ������� �������� ���� ��/��� ��� ����������� ������� ���� pFnom
extern u16 *pFdbyFnom;	
// ����������� ������� ����
extern u16	*pFnom;

void AllocFrzRegisters(void);
void InitFrzRegisters(void);
void InitFrzRegsAfterLoad(void);
void LoadFrzBackupRegs(void);

void SaveRegs(void);
void SaveRegsNoMes(void);
void LoadRegsFromFile(void);

u8 Cross(u32 sx,u16 slens,u32 dx,u16 dlen);

#endif


