// модуль работы с регистрами
// формирование таблицы регистров
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

// общие переменные
u8 *pByPass; // режим обхода
u8 *pCrushWater;
//TContur * pscz;

u8 *pQURepCount;
u16 *pQUTimeout;
// логирование правильно полученных квитанций по RS-485
u8 *pACmdDump;
u8 *pAMsg;
u8 *pAAnswDump;
// логирование ошибочных квитанций по RS-485
u8 *pAECmdDump;
u8 *pAEMsg;
u8 *pAEAnswDump;
// логирование не полученных квитанций
u8 *pANCmdDump;
u8 *pANMsg;

// логирование ошибок контрольной суммы UART1
u8 *pErrCSU1;
// логирование пропуска команд на постановку в очередь
u8 *pDropCmd;
#ifdef __FREZER__
// группа по Х
float *pX_PG_MM;
u32 *pX_SPR;
float	*pX_MIN;
float	*pX_MAX;
s32 vX_MIN_POS; 
s32 vX_MAX_POS; 
// группа по Y
float *pY_PG_MM;
u32 *pY_SPR;
float	*pY_MIN;
float	*pY_MAX;
s32 vY_MIN_POS; 
s32 vY_MAX_POS; 
// группа по Z
float *pZ_PG_MM;
u32 *pZ_SPR;
float	*pZ_MIN;
float	*pZ_MAX;
s32 vZ_MIN_POS; 
s32 vZ_MAX_POS; 

// смещение центра начала координат
s32 * dXPos;
s32 * dYPos;
s32 * dZPos;

// интервалы опроса частотника пульта УУПС
u16 *pIntKPCtrl;
u16 *pIntKPCtrlStop;
// количество команд без квитанций для пульта
u8	*pKP_NA_Max;

// связь с ПУ 
u8 *pLinkKP;
// количество команд без квитанций для частотника
//u8	LS_NA_Count;
// количество команд без квитанций для пульта
u8	KP_NA_Count;
// признак корректной остановки
u8 *pCorrStop;
// признак восстановления сссотояния после паузв или после выключения питания
u8 *pRecoverBlock;
// режим коррекции высоты инструмента
u8 *pHTCorr; 
// режим обнуления координаты Z по датчику
u8 *pZZeroDat; 
// режим работы по горизонтальному датчику
u8 *pHorizontalDat;
// направление горизонального датчика 0 off 1 up 2 left 3 down 4 right
u8 *pHorizDatDir;
// состояние выполнения горизонального датчика 0 off 1 go 2 ok 3 fault
u8 *pHorizDatState;
	// диаметр шарика датчика
float *pHorizDiam;
	// погрешность измерения
float *pHorizMeasError;
// координата X после срабатывания датчика
float *pHorizX;
// координата Y после срабатывания датчика
float *pHorizY;

u8	fStopPrg;
u8	fStartPrg;
u8	fSaveRegs;
// коэффициент редукции двигатель->ведущий вал
//float *pKred;
// диаметр вала (м)
//float *pDval;
// частота вращения вала об/мин при номинальной частоте сети pFnom
u16 *pFdbyFnom;	
// номинальная частота сети
u16	*pFnom;

#endif



static u32 CurBase = 0,CurOffset;
TVarAttr 	va[200]; 	// массив атрибутов
u16			iva=0;		// текущий индекс

u8 OutAllocTable=0;
u32 CurVarIndex = 0;
u8	VChange = 0;

u8 regs[REGS_COUNT]; // registers

u8 ROHandler(char * name,u8 * buffer,u16 len){
	// пример обработчика,
	// используемого при записи данных из внешнего интерфейса
	// в общую память
	// Msg("ROH %s.",name);
	return 0; // запись разрешена
	//return не 0; // запись запрещена 
	// 1,2,3 - зарезервированы
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
// задержка анти дребезга
	s16 v;
	if (*pUsesKP485) {
		memcpy((u8*)&v,buffer,2);
		mbInsCmd485(*pAddrKPCtrl,6,1200,v,1); 
	}
	return 0;
}

u8 pDCTimeHandle(char * name,u8 * buffer,u16 len){
// время DoubleClick
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
	// абсолютный адрес в контроллере
	// if (addr < REGS_COUNT) CurBase = addr;
	// или
	// смещение в переменной regs
	//if (addr < REGS_COUNT)
	CurBase = addr;
//	Msg("cb %d \r\n",CurBase);
}

void SetNewGroup(void){
	u32 CurAddr;
	CurAddr = CurBase + CurOffset;
	// проверка текущего адреса на правило кратности распределения 4+8*n
	if (CurAddr) {
		if ((CurAddr-4)%8) CurBase = ((CurAddr-4)/8 +1)*8 +4;
		else CurBase = CurAddr;
	} // нулевой адрес корректен
	CurOffset = 0; // сброс текущего смещения
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
			// условие пересечения интервалов
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

// загрузка файла регистров
void	LoadRegsFromFile(void){
	tFile f;
	u32 rbc;
	s8 res;
	// открыть файл regs.bin
	res = FS_Assign("startup.cmd",&f);
	if (res == FS_RESULT_OK) {
		res = FS_Reset(f);
		if (res == FS_RESULT_OK) {
			FS_Close(&f);
			res = FS_Assign("regs.bin",&f);
			if (res == FS_RESULT_OK) {
				res = FS_Reset(f);
				if (res == FS_RESULT_OK) {
					// загрузить N байт в массив regs
					res = bFS_Read(f,regs,REGS_COUNT,&rbc);
					if (res < 0) {
						Msg("Error Read File regs.bin res %d\r\n",res);
					}
					// закрыть файла
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
	// инициализировать pPrgFileHandle
	fnt_num = 0;
	do {
		memset(name,sizeof name,0);
		res = FS_GetFileInfo(&fnt_num,name,&type,&attr,&size,&f);
		if (res == FS_RESULT_OK) {
			// файл найден
			FS_Close(&f); // закрываем
			// едем дальше
			fnt_num++;
		}
	} while (res == FS_RESULT_OK);
}

void	SaveRegs(void){
	s32 res;
	tFile f;
	u32 rbc;

	Msg("Save Regs\r\n");

	// пока не переделан Rewrite
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

	// пока не переделан Rewrite
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
//* ОБРАБОТЧИКИ, ВЫЗЫВАЕМЫЕ ПРИ ЗАПИСИ ЗНАЧЕНИЙ В РЕГИСТРЫ **********
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
	// сохранение в backup - регистре
	VChange = 1; // устанавливаем признак изменения подачи
//	memcpy((void*)&(BR_fmvc_V),(void*)buffer,4);
//	memcpy((void*)&v,(void*)buffer,4);
//	Msg("Handle SetFeed %d ",(int)(v*1000));
	return 0;
}


void AllocFrzRegisters(void){
// Чтение и запись
	memset(regs,0,REGS_COUNT);

	SetBase(0);
	SetAddr((void*)&pvPins,"pvPins",108,rw,NoHandle);

	// Группа одиночных параметром
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
	// группа параметров движения по X
	SetAddr((void*)&mc_X.FrMin,		"mc_X.FrMin",		8,rw,NoHandle);
	SetAddr((void*)&mc_X.FrReq, 	"mc_X.FrReq",		8,rw,NoHandle);
	SetAddr((void*)&mc_X.FrMax,		"mc_X.FrMax",		8,rw,NoHandle);
	SetAddr((void*)&mc_X.Accel,		"mc_X.Accel",		4,rw,NoHandle);

	SetNewGroup();
	// группа параметров движения по Y
	SetAddr((void*)&mc_Y.FrMin,		"mc_Y.FrMin",		8,rw,NoHandle);
	SetAddr((void*)&mc_Y.FrReq, 	"mc_Y.FrReq",		8,rw,NoHandle);
	SetAddr((void*)&mc_Y.FrMax,		"mc_Y.FrMax",		8,rw,NoHandle);
	SetAddr((void*)&mc_Y.Accel,		"mc_Y.Accel",		4,rw,NoHandle);

	SetNewGroup();
	// группа параметров движения по Z
	SetAddr((void*)&mc_Z.FrMin,		"mc_Z.FrMin",		8,rw,NoHandle);
	SetAddr((void*)&mc_Z.FrReq, 	"mc_Z.FrReq",		8,rw,NoHandle);
	SetAddr((void*)&mc_Z.FrMax,		"mc_Z.FrMax",		8,rw,NoHandle);
	SetAddr((void*)&mc_Z.Accel,		"mc_Z.Accel",		4,rw,NoHandle);

	SetNewGroup();
	SetAddr((void*)&mc_X.ReqPos,	"mc_X.ReqPos",		4,rw,NoHandle);//*//4// требуемая позиция
	SetAddr((void*)&mc_X.MovePos,	"mc_X.MovePos",		1,rw,NoHandle);//*//1// включение выхода на позицию
	SetAddr((void*)&mc_Y.ReqPos,	"mc_Y.ReqPos",		4,rw,NoHandle);//*//4// требуемая позиция
	SetAddr((void*)&mc_Y.MovePos,	"mc_Y.MovePos",		1,rw,NoHandle);//*//1// включение выхода на позицию
	SetAddr((void*)&mc_Z.ReqPos,	"mc_Z.ReqPos",		4,rw,NoHandle);//*//4// требуемая позиция
	SetAddr((void*)&mc_Z.MovePos,	"mc_Z.MovePos",		1,rw,NoHandle);//*//1// включение выхода на позицию


	SetNewGroup();
	// группа управления кнопками X
	SetAddr((void*)&mc_X.ReqDir,	"mc_X.ReqDir",		1,rw,NoHandle);
	SetAddr((void*)&mc_X.MoveBtn,	"mc_X.MoveBtn",		1,rw,NoHandle);

	SetNewGroup();
	// группа управленияя кнопками Y
	SetAddr((void*)&mc_Y.ReqDir,	"mc_Y.ReqDir",		1,rw,NoHandle);
	SetAddr((void*)&mc_Y.MoveBtn,	"mc_Y.MoveBtn",		1,rw,NoHandle);

	SetNewGroup();
	// группа управления кнопками Z
	SetAddr((void*)&mc_Z.ReqDir,	"mc_Z.ReqDir",		1,rw,NoHandle);
	SetAddr((void*)&mc_Z.MoveBtn,	"mc_Z.MoveBtn",		1,rw,NoHandle);

	SetNewGroup();
	// включение позиционирования по координатам
	SetAddr((void*)&mc_X.PositOn,	"mc_X.PositOn",		1,rw,XPositOnHandle);
	SetAddr((void*)&mc_Y.PositOn,	"mc_Y.PositOn",		1,rw,YPositOnHandle);
	SetAddr((void*)&mc_Z.PositOn,	"mc_Z.PositOn",		1,rw,ZPositOnHandle);

	SetNewGroup();
	SetAddr((void*)&ms_X.FrCur,		"ms_X.FrCur",		8,ro,NoHandle);
	SetAddr((void*)&ms_Y.FrCur,		"ms_Y.FrCur",		8,ro,NoHandle);
	SetAddr((void*)&ms_Z.FrCur,		"ms_Z.FrCur",		8,ro,NoHandle);

	// см. инициализацию до загрузки
	SetAddr((void*)&ms_X.Dir,		"ms_X.Dir",			1,ro,NoHandle);
	SetAddr((void*)&ms_Y.Dir,		"ms_Y.Dir",			1,ro,NoHandle);
  	SetAddr((void*)&ms_Z.Dir,		"ms_Z.Dir",			1,ro,NoHandle);
	// Posit не меняется после ЗП
/*	
	SetAddr((void*)&ms_X.Posit, 	"ms_X.Posit",		1,ro,NoHandle);
	SetAddr((void*)&ms_Y.Posit, 	"ms_Y.Posit",		1,ro,NoHandle);
	SetAddr((void*)&ms_Z.Posit, 	"ms_Z.Posit",		1,ro,NoHandle);
*/	
	SetAddr((void*)&ms_X.Posit, 	"ms_X.Posit",		1,rw,NoHandle);
	SetAddr((void*)&ms_Y.Posit, 	"ms_Y.Posit",		1,rw,NoHandle);
	SetAddr((void*)&ms_Z.Posit, 	"ms_Z.Posit",		1,rw,NoHandle);

	// StagePos сброшен после ЗП
	SetAddr((void*)&ms_X.StagePos, 	"ms_X.StagePos",		1,ro,NoHandle);
	SetAddr((void*)&ms_Y.StagePos, 	"ms_Y.StagePos",		1,ro,NoHandle);
	SetAddr((void*)&ms_Z.StagePos, 	"ms_Z.StagePos",		1,ro,NoHandle);
	
	// настройки шпинделя и ШИМ
	SetNewGroup();
	SetAddr((void*)&pFdbyFnom,	"pFdbyFnom",	2,rw,NoHandle);	//*// 
	SetAddr((void*)&pFnom,			"pFnom",			2,rw,NoHandle);	//*// 
  SetNewGroup();
	// ШИМ частника если тип 2
	SetAddr((void*)&pFIPWM, "pFIPWM",			4,rw,NoHandle);
	// максимальная частота для ШИМ ЧП если тип 2
	SetAddr((void*)&pFIPWMFreq, "pFIPWMFreq",			4,rw,NoHandle);

	// режим обхода заготовки
	// ByPass сброшен после ЗП
	SetNewGroup();
	SetAddr((void*)&pByPass, 	"pByPass",		1,rw,pByPassHandle);
	// режим коррекции высоты инструмента
	SetAddr((void*)&pHTCorr, 	"pHTCorr",		1,rw,pByPassHandle);
	// режим обнуления координаты Z по датчику
	SetAddr((void*)&pZZeroDat, 	"pZZeroDat",		1,rw,pByPassHandle);
	// режим работы по горизонтальному датчику
	SetAddr((void*)&pHorizontalDat, 	"pHorizontalDat",		1,rw,pHorizDatHandle);
	// направление горизонального датчика 0 off 1 up 2 left 3 down 4 right
	SetAddr((void*)&pHorizDatDir, 	"pHorizDatDir",		1,rw,NoHandle);
	// состояние выполнения горизонального датчика 0 off 1 go 2 ok 3 fault
	SetAddr((void*)&pHorizDatState, 	"pHorizDatState",		1,ro,NoHandle);
	
	SetNewGroup();
	// диаметр шарика датчика
	SetAddr((void*)&pHorizDiam, 	"pHorizDiam",		4,rw,NoHandle);
	// погрешность измерения
	SetAddr((void*)&pHorizMeasError, 	"pHorizMeasError",		4,rw,NoHandle);
	// координата X после срабатывания датчика
	SetAddr((void*)&pHorizX, 	"pHorizX",		4,rw,NoHandle);
	// координата Y после срабатывания датчика
	SetAddr((void*)&pHorizY, 	"pHorizY",		4,rw,NoHandle);
	

	// смещения нулевой точки в импульсах
	SetNewGroup();
	SetAddr((void*)&dXPos,		"dXPos",			4,rw,NoHandle);
	SetAddr((void*)&dYPos,		"dYPos",			4,rw,NoHandle);
	SetAddr((void*)&dZPos,		"dZPos",			4,rw,NoHandle);
	
	// точки плоскостной коррекции
	SetNewGroup();
	// координата X1
	SetAddr((void*)&pX1,			"pX1",			4,rw,NoHandle);	
	// координата Y1
	SetAddr((void*)&pY1,			"pY1",			4,rw,NoHandle);	
	// координата Z1
	SetAddr((void*)&pZ1,			"pZ1",			4,rw,NoHandle);	
	// координата X2
	SetAddr((void*)&pX2,			"pX2",			4,rw,NoHandle);	
	// координата Y2
	SetAddr((void*)&pY2,			"pY2",			4,rw,NoHandle);	
	// координата Z2
	SetAddr((void*)&pZ2,			"pZ2",			4,rw,NoHandle);	
	// координата X3
	SetAddr((void*)&pX3,			"pX3",			4,rw,NoHandle);	
	// координата Y3
	SetAddr((void*)&pY3,			"pY3",			4,rw,NoHandle);	
	// координата Z3
	SetAddr((void*)&pZ3,			"pZ3",			4,rw,NoHandle);	

	SetAddr((void*)&pA,			"pA",			4,rw,NoHandle);	
	SetAddr((void*)&pB,			"pB",			4,rw,NoHandle);	
	SetAddr((void*)&pC,			"pC",			4,rw,NoHandle);	
	SetAddr((void*)&pD,			"pD",			4,rw,NoHandle);	

	SetNewGroup();
	// минимальная скорость пиления
	SetAddr((void*)&fmvc.Vmin,		"fmvc.Vmin",			4,rw,NoHandle);	
	// ускорение
	SetAddr((void*)&fmvc.Vaccel,	"fmvc.Vaccel",		4,rw,NoHandle);	
	// множитель
	SetAddr((void*)&fmvc.Vmul,		"fmvc.Vmul",			4,rw,NoHandle);	
	// высота датчика в мм
	SetAddr((void*)&pHdat,			"pHdat",			4,rw,NoHandle);	
	//траекторный угол
	SetAddr((void*)&pTrAngle,"pTrAngle"	,sizeof (*pTrAngle),rw,NoHandle);
	// время разгона шпинделя
	SetAddr((void*)&pRunSpPause,	"pRunSpPause",			4,rw,NoHandle);	

	// настройка обмена по 485
	SetNewGroup();
	// разрешение на использование пульта по RS-485
	SetAddr((void*)&pUsesKP485, "pUsesKP485", 	1,rw,NoHandle);
	// адрес пульта
	SetAddr((void*)&pAddrKPCtrl, "pAddrKPCtrl",			1,rw,NoHandle);// по идее нужен обработчик чтобы избежать конфликтов адресов 
	// максимальное количество сбоев до выдачи неисправности
	SetAddr((void*)&pKP_NA_Max, "pKP_NA_Max",			1,rw,NoHandle);
	
	SetNewGroup();
	// интервал опроса пульта в режиме стоп
	SetAddr((void*)&pIntKPCtrl, "pIntKPCtrl",			2,rw,NoHandle);
	// интервал опроса пульта в режиме пуск
	SetAddr((void*)&pIntKPCtrlStop, "pIntKPCtrlStop",			2,rw,NoHandle);
	// таймаут ожидания в мс 
	SetAddr((void*)&pQUTimeout, 	"pQUTimeout",			2,rw,NoHandle);
	// количество повторов
	SetAddr((void*)&pQURepCount, 	"pQURepCount",			1,rw,NoHandle);

	SetNewGroup();
	// Pos остается без изменений после загрузки
	SetAddr((void*)&ms_X.Pos,		"ms_X.Pos",			4,ro,NoHandle);
	SetAddr((void*)&ms_Y.Pos,		"ms_Y.Pos",			4,ro,NoHandle);
	SetAddr((void*)&ms_Z.Pos,		"ms_Z.Pos",			4,ro,NoHandle);
	SetAddr((void*)&pPrgRun,	"pPrgRun",			 	1,rw,PrgRunHandleFrz);
	SetAddr((void*)&pCurCadr,		"pCurCadr",		 	4,rw,pCurCadrHandleFrz);
	SetAddr((void*)&pNumReadLine,		"pNumReadLine",		 	4,ro,NoHandle);
	// остается без изменений после ЗП
	SetAddr((void*)&pRCS,		"pRCS"					,1,rw,NoHandle);
	// скорость резки в мм в сек
	SetAddr((void*)&fmvs.Vc,			"fmvs.Vc",			4,ro,NoHandle);	
	// скорость резки в мм в сек
	SetAddr((void*)&fmvc.V,			"fmvc.V",			4,rw,mvcVHandleFrz);	
	// аварийные флаги
	SetAddr((void*)&pCrushWater,"pCrushWater",			1,rw,NoHandle);	
	// связь с устройствами линии RS-485
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
	// задержка анти дребезга
	SetAddr((void*)&pDrDelay, 	"pDrDelay",			2,	rw,pDrDelayHandle);
	// время DoubleClick в 0,01 с 
	SetAddr((void*)&pDCTime, "pDCTime",		2,	rw,pDCTimeHandle);
	// минимальное значение скорости в процентах
	SetAddr((void*)&pPercVmin, 	"pPercVmin",	2,	rw,pPercVminHandle);
	// регистры управления движением -100 +100
	SetAddr((void*)&pYmove, 		"pYmove"	, 	2,	rw,NoHandle);
	SetAddr((void*)&pZmove,		"pZmove"	, 	2,	rw,NoHandle);
	SetAddr((void*)&pXmove,			"pXmove"	, 	2,	rw,NoHandle);
	SetAddr((void*)&pUnusedmove,		"pUnusedmove"	, 	2,	rw,NoHandle);
	// 5 кнопка 0 100
	SetAddr((void*)&pBtn5,			"pBtn5"		, 	2,	rw,NoHandle);
// переключение осей 0 или 100 по кнопке 6
	SetAddr((void*)&pAxisSwitch,	"pAxisSwitch", 	2,	rw,NoHandle);
// пищалка
	SetAddr((void*)&pBUZZ,			"pBUZZ", 	2,	rw,NoHandle);	

	SetNewGroup();
// логирование правильно полученных квитанций по RS-485
	SetAddr((void*)&pACmdDump, 		"pACmdDump",			1,rw,NoHandle);
	SetAddr((void*)&pAMsg,			"pAMsg",			1,rw,NoHandle);
	SetAddr((void*)&pAAnswDump, 	"pAAnswDump",			1,rw,NoHandle);
// логирование ошибочных квитанций по RS-485
	SetAddr((void*)&pAECmdDump, 	"pAECmdDump",			1,rw,NoHandle);
	SetAddr((void*)&pAEMsg, 		"pAEMsg",			1,rw,NoHandle);
	SetAddr((void*)&pAEAnswDump, 	"pAEAnswDump",			1,rw,NoHandle);
// логирование не полученных квитанций
	SetAddr((void*)&pANCmdDump, 	"pANCmdDump",			1,rw,NoHandle);
	SetAddr((void*)&pANMsg, 		"pANMsg",			1,rw,NoHandle);
// логирование ошибок контрольной суммы UART1
	SetAddr((void*)&pErrCSU1, 		"pErrCSU1",			1,rw,NoHandle);
// логирование пропуска команд на постановку в очередь
	SetAddr((void*)&pDropCmd, 		"pDropCmd",			1,rw,NoHandle);

	SetNewGroup();
	// остается без изменений после ЗП
	SetAddr((void*)&pBlock,		"pBlock"				,sizeof (*pBlock),ro,NoHandle);
//	SetAddr((void*)&eb,		"pBlock"				,sizeof (*pBlock),ro,NoHandle);
	// контур заготовки
	// остается без изменений после ЗП
	SetNewGroup();
//	SetAddr((void*)&pBusy,		"pbusy",			1,rw,NoHandle);
//	SetAddr((void*)&psG0,		"psG0",			 	1,rw,NoHandle);
//	SetAddr((void*)&pscz,		"pscz",			 	804,rw,NoHandle);

}

void InitFrzRegisters (void) {
	
	// инициализация пинов таблицей по умолчанию
	memcpy(pvPins,&vPinsdef,sizeof vPinsdef);
	// формирование таблицы быстрых пинов
	FormQPinTable();
	// X
 	// значение ведущей радиальной шестерни
	*pX_PG_MM = 120.0; // (мм)
	// шагов на оборот ведущей шестерни
	*pX_SPR = 4000;
	*pX_MIN = 0; 
	// минимальная позиция по X в шагах
	vX_MIN_POS = (s32)((*pX_MIN) * ((*pX_SPR)/(*pX_PG_MM))); 
	// максимальная позиция по радиусу в мм
	*pX_MAX = 1500;
	// максимальная позиция по X в шагах
	vX_MAX_POS = (s32)((*pX_MAX) * ((*pX_SPR)/(*pX_PG_MM))); 
	// Y
 	// значение ведущей радиальной шестерни
	*pY_PG_MM = 120.0; // (мм)
	*pY_SPR = 4000;
	*pY_MIN = 0; 
	vY_MIN_POS = (s32)((*pY_MIN) * ((*pY_SPR)/(*pY_PG_MM))); 
	*pY_MAX = 1500;
	// максимальная позиция по X в шагах
	vY_MAX_POS = (s32)((*pY_MAX) * ((*pY_SPR)/(*pY_PG_MM))); 
	// Z
	*pZ_PG_MM = 10.0; // (мм)
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
	// обход заготовки выключен
	*pByPass = 0;
	*pHTCorr = 0; 
	*pZZeroDat = 0;
	// сброс контура заготовки
//	memset((void*)pscz,0,804);
	*pPrgRun = 0;
	// зафиксировать состояние "чтение строки" - это превое состояние выполнения кадра
	*pCurCadr = 0; // текущий номер кадра
	
	*pRCS = rcsGetBlock; // состояние выполнения кадра "чтение следующей строки" 
	
	*pRecoverBlock = 0; // блок восстановлен	
	
	// дескриптор файла программы
 	*pPrgFileHandle=-1;
	// имя файла программы в G-коде
	memset((void*)pPrgFileName,0,20);
	*pCrushWater = 0;
	// смещения
 	*dXPos=0;
 	*dYPos=0;
 	*dZPos=0;

	// разрешение на использование пульта по RS-485
	*pUsesKP485 = 1; // запрещено 1-разрешено
	
	// задержка анти дребезга в 0,0001 с
	*pDrDelay = 50;
	// время DoubleClick в 0,01 с 
	*pDCTime = 50; // 0,5 сек 
	// процент увеличения скорости (в каких единицах? %/с ?)
	*pPercVmin = 5; // %/c ???????
	// регистры управления движением -100 +100
	*pYmove = 0;
	*pZmove = 0;
	*pXmove = 0;
	*pUnusedmove = 0;
	// 5 кнопка 0 100
	*pBtn5 = 0;
	// переключение осей 0 или 100 по кнопке 6
	*pAxisSwitch = 0; // выбраны оси R и A 
	// пищалка
	*pBUZZ = 0;
	*pQURepCount = 3; // 3 повтора по умолчанию
 	*pQUTimeout = 100; // 100 мс ожидание 

// логирование правильно полученных квитанций по RS-485
	*pACmdDump = 0;
	*pAMsg = 0;
	*pAAnswDump = 0;
// логирование ошибочных квитанций по RS-485
	*pAECmdDump = 0;
	*pAEMsg = 0;
	*pAEAnswDump = 0;
// логирование не полученных квитанций
	*pANCmdDump = 0;
	*pANMsg = 0;
// логирование ошибок контрольной суммы UART1
	*pErrCSU1 = 0;
	// логирование пропуска команд на постановку в очередь
	*pDropCmd = 0;
// пороговое количество команд без квитанций для пульта
	*pKP_NA_Max = 1;

// количество команд без квитанций для пульта
	KP_NA_Count = 0;
// связь с ПУ 
	*pLinkKP = 0;
// признак корректной остановки 
	*pCorrStop = 0;

	// адрес пульта
	*pAddrKPCtrl = 4;
	
	// интервалы опроса мс
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
	// индекс выдаваемой точки
	Index = 1;
	// плоскостная компенсация
	*pfZcomp = 0;
// частота вращения вала об/мин при номинальной частоте сети pFnom Гц
	*pFdbyFnom = 18000;	
// номинальная частота сети Гц
	*pFnom = 300;	
	
	*pRunSpPause = 5000;
	// контрольная сумма записаного файла программы
	*pWF_CRC = 0;
	// задержка при изменении направления 200 мкс 
//	*pDirDelay = 5000;
}

void InitFrzRegsAfterLoad(void){
	// инициализация структуры управления двигателем 
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
	// инициализировать pPrgFileHandle
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
	// открыть файл regs.bin
	res = FS_Assign("startup.cmd",&f);
	if (res == FS_RESULT_OK) {
		res = FS_Reset(f);
		if (res == FS_RESULT_OK) {
			FS_Close(&f);
			//	файл есть - загрузка регистров

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
			// файла нет - очитка регистров

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

