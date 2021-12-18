#ifndef __HANDLERS_H__
#define __HANDLERS_H__

#include "Defs.h"
#include "regs.h"
/*
#define COOLER1		OUT13
#define COOLER2		OUT14
*/
//#define rcsReadLine			0
#define rcsGetBlock			0
#define rcsTranslate		1
#define rcsEnd				2
#define rcsExecute			3
#define rcsTranslateError	4
#define rcsSetFeed			5
#define rcsSetPump			6
#define rcsSetSpindle		7
#define rcsSetCold			8
#define rcsSetPause			9
#define rcsSetTrack			10
#define rcsWaitPause		11
#define rcsSetGo			12
#define rcsWaitGo			13
#define rcsSetStop			14
#define rcsWaitStop			15
#define rcsEndExecute		16

extern volatile u8 Busy;
extern u8 		sG0;
extern u8 		*pPrgRun;
//extern u8		*pPrgPause;
extern s32 		*pCurCadr;
extern s32		*pNumReadLine;
extern s32 		sCurCadr;
extern u8 		*pRecBlock;
extern	u8 		*pRCS;		// состояние выполнения кадра

extern u8 		sBusy;
extern TBlock *pBlock;


extern u8 sXMovePos,sYMovePos,sZMovePos,sFMVCEnable;
extern float * pTrAngle; //траекторный угол
extern TBlock * eb;
extern volatile float Sr; // разведанный путь
extern volatile u32 Sri; // разведанный путь в импульсах
extern u8 SPS;
//extern s32 NumReadLine;
//extern float *pZset;
extern u32 *pRunSpPause;


u8 ReadPrevLine(char * CadrLine);
u8 ReadNextLine(char * CadrLine);

void RunNextCadrFrz(void);
void RunNextCadrFrzMain(void);
void RecRunNextCadrFrz(void);
void CrushWaterHandlerFrz(void);
void TranslatePrg(void);
void TranslatePrgLine(const char * s);

void SearchStopPoint(void);
u8 		InitPrgStreams(void);
void	InitQExBlks(void);
u8 qbDelFirst(void);
TBlock * qbFirstBlock(void);
TBlock * qbLastBlock(void);
u8 qbCount(void);
u8 qbAddBlock(TBlock * b);

void qbIncIndex(u8* Index);
u8 qbFirstIndex(void);
u8 qbLastFreeIndex(void);
TBlock * qbGetBlockIndex(u8 Index);

extern u8 EndTranslate;
void SaveFilePos(void);

#endif
