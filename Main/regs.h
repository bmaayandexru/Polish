#ifndef __REGS_H__
#define __REGS_H__

//#include <RTL.h>   
#include "Defs.h"
#include "LPC17xx.h"
#include "motors.h"

// общее количество регистров
#define REGS_COUNT		1000

// атрибуты переменных
// чтение и запись
#define rw 0
// только чтение
#define ro 1
// отсутсвие обработчика при резервировании памяти
#define NoHandle 0

// периметр ведущей радиальной шестерни в мм
// было определено ка (120) теперь это регистр общей памяти
// это регистр double
#define	R_PG_MM	(*pR_PG_MM)
// шагов на оборот ведущей шестерни по радиусу
#define R_SPR	(*pR_SPR)
// шагов на оборот по углу
//#define A_SPR	(72000)
#define A_SPR	(int)(*pA_SPR)
#define A_SPRH	(A_SPR/2)
#define A_MIN_POS (-(int)A_SPRH+1)
#define A_MAX_POS ((int)A_SPRH)

// шагов на оборот по векторам
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
// Backup-регистры
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
// оставшиеся регистры которые можно использовать
  __IO uint16_t ALDOY; // до 512 считает только
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

// Backup-регистры фрезера
#define BR_ms_X_Pos LPC_RTC->GPREG0
#define BR_ms_Y_Pos LPC_RTC->GPREG1
#define BR_ms_Z_Pos	LPC_RTC->GPREG2
#define BR_FilePos	LPC_RTC->GPREG3
//#define BR_fmvc_V	LPC_RTC->GPREG3
#define BR_pCurCadr	LPC_RTC->GPREG4
#define BR_pPrgRun	LPC_RTC->ALSEC
#define BR_pCorrStop	LPC_RTC->ALDOW 

/*
// оставшиеся регистры которые можно использовать
#define BR_pPrgPause	LPC_RTC->ALMIN
#define BR_OnTros	LPC_RTC->ALDOW 
#define BR_OnTable	LPC_RTC->ALMON
#define BR_pPrgDir	LPC_RTC->ALHOUR

  __IO uint16_t ALDOY; // до 512 считает только
  __IO uint8_t	LPC_RTC->ALDOM
#define BR_pPrgPause	LPC_RTC->ALMIN
*/

#endif
// Ошибки трансляции
// неизвестная команда
#define TRE_UNKNOWN_CMD	1
// ошибка преобразования параметра
#define TRE_PARAM_ERROR	2
// неизвестная G-команда
#define TRE_UNKNOWN_G	3
// неизвестная M-команда
#define TRE_UNKNOWN_M	4
// параметр F < 0
#define TRE_LESSZERO_F	5
// параметр S < 0
#define TRE_LESSZERO_S	6
// параметр P < 0
#define TRE_LESSZERO_P	7
// пустая строка (в начале ch == 13)
#define TRE_LINE_EMPTY 	8

// информаци о файле
typedef __packed struct tagFInfo{ 
	u32		index;     
    char 	name[14];
    char 	ext[4];
    u8	 	attr;
    u32 	size;
    u8	 	f;
} FInfo;

// тип обработчик правомерности записи переменных
typedef u8(*TWHandler)(char * name,u8 * buffer,u16 len);

// структура размещения переменных
typedef struct {
	char 	name[20];	// имя
	void 	*p;			// указатель
	u16		len;		// длина байт
	u32		attr;		// атрибуты
	TWHandler	handle; // обработчик записи
} TVarAttr;

typedef struct {
	float X,Y;
} TPoint;

typedef TPoint TPoints[100];

typedef struct {
	u32 Count;
	TPoints points;
} TContur;

// управляющая структура кадра пилы
typedef struct tagTBlock { 
	s32		NumLine;	// номер строки
	s32 	PosSSP;		// позиция указателя файла программы с которой начинается поиск точки останова
	u8 		Nonstop;	// 0 - блок с остановкой (выталкивается в main)
						// 1 - блок без остановки (выталкивается в прерывании)
	u8		cFeed;		// наличие команды скорости подачи
    float 	Feed;    	// скорость подачи мм/с
    float 	Speed;    	// скорость троса в м/с
    u8 		cSpindel;   // наличие команды управления шпинделем
    u8 		sSpindel;   // статус 0-выкл.
                        // 1-вращение по часовой
                        // 2-вращение против часовой
    u8 		cCold;      // наличие команды охлаждения
    u8 		sCold1;     // статус 0-охлаждение 1 выкл.
                        // 1-охлаждение 1 вкл.
    u8 		sCold2;     // статус 0-охлаждение 2 выкл.
                        // 1-охлаждение 2 вкл.
    u8 		cPause;     // наличие команды "Пауза"
    u32 	lPause;  	// длина паузы в мс

		u8 		cStop;      // наличие команды "стоп"
    u8 		sStop;      // cтатус команды стоп
                        // 0 - пауза до кнопки старт
                        // 1 - останов с подтверждением
                        // 2 - полное отключение
    u8 		sGo;      	// тип движения
                        // 0 - быстрое перемещение
                        // 1 - прямолинейное движение
    float 	Mul;    	// множитель текущий = 1 или 25.3 (мм дюймы)
    float 	rMul;    	// множитель считанный
    u8 		SetSizeReg; // режим указания размеров текущий
                        // 0 - абсолютные координаты
                        // 1 - приращения
    u8 		rSetSizeReg;// режим указания размеров считанный
    float 	Xs,Ys,Zs;  	// текущие координаты в мм
    u8 		comX,comY,comZ;  // наличие считанных значений по X и Y
    float 	Xr,Yr,Zr;    	// считанные значения X и Y
    float 	Xd,Yd,Zd;    	// точка назначения
	s32		Xi,Yi,Zi;		// текушеее положение в импульсах
	s32		Xsi,Ysi,Zsi;	// начальное положение в импульсах
	s32		Xdi,Ydi,Zdi;	// конечное положение в импульсах
	s32		dXi,dYi,dZi;	// приращения в импульсах
	s32		signX,signY,signZ;	//4+4// направления 
	s32		e1;				//4//ошибка в алгоритме Брозенхейма
	s32		e2;				//4//ошибка в алгоритме Брозенхейма
	u8 		Lax; 			// ведущая ось 0-x	1-y 2-z
	s32   Laxi;			// количество шагов по ведущей оси
	float Li;				// длина отрезка в импульсах (условно) sqrt(x*x+y*y+z*z);
	u8 		Nomove;			// если 1 блок без движение все приращения равны 0
	float 	dS;				// приражение пути для одной итерации брозенхейма
							// вычитаетя из Sr
	u32		Tb;				// величина используемая для рачета периода частоты движения T = Tb/Vc
	char s[50];
	s32 FilePos; // позиция в файле соответсвующая блоку
} TBlock;

typedef u8 TFileName[20];

// общие переменные
extern TFileName * pPrgFileName;
extern s8 * pPrgFileHandle;
extern u32 * pPrgLineCount;
extern u16 * pWF_CRC;

extern u8 *pCrushWater;
extern u8 *pByPass;

//extern volatile BOOL	fU1toU0;

extern u8 		regs[REGS_COUNT]; // registers
extern u16		iva;	// количество размещенных переменных
extern TVarAttr 	va[]; 	// массив атрибутов

//extern TContur * pscz;

extern u8 OutAllocTable;
extern u32 CurVarIndex;
extern u8	VChange;
// частота вращения вала об/мин при номинальной частоте сети pFnom
extern u16 *pFdbyFnom;	
// номинальная частота сети
extern u16	*pFnom;

// регистры обслуживания очереди
extern u8 *pQURepCount; // количество повторов
extern u16 *pQUTimeout; // таймаут
// логирование правильно полученных квитанций по RS-485
extern u8 *pACmdDump;
extern u8 *pAMsg;
extern u8 *pAAnswDump;
// логирование ошибочных квитанций по RS-485
extern u8 *pAECmdDump;
extern u8 *pAEMsg;
extern u8 *pAEAnswDump;
// логирование не полученных квитанций
extern u8 *pANCmdDump;
extern u8 *pANMsg;
// логирование ошибок контрольной суммы UART1
extern u8 *pErrCSU1;
// логирование пропуска команд на постановку в очередь
extern u8 *pDropCmd;
// количество команд без квитанций для пульта
extern u8	*pKP_NA_Max;
// количество команд без квитанций для УУПС
extern u8	*pPress_NA_Max;
// количество команд без квитанций для пульта
extern u8	KP_NA_Count;
// связь с ПУ 
extern u8 *pLinkKP;

// переменные фрезера

// группа X
extern float 	*pX_PG_MM;
extern u32		*pX_SPR;
extern float	*pX_MIN;
extern float	*pX_MAX;
extern s32 		vX_MIN_POS; 
extern s32 		vX_MAX_POS; 
// группа Y
extern float 	*pY_PG_MM;
extern u32		*pY_SPR;
extern float	*pY_MIN;
extern float	*pY_MAX;
extern s32 		vY_MIN_POS; 
extern s32 		vY_MAX_POS; 
// группа Z
extern float 	*pZ_PG_MM;
extern u32		*pZ_SPR;
extern float	*pZ_MIN;
extern float	*pZ_MAX;
extern s32 		vZ_MIN_POS; 
extern s32 		vZ_MAX_POS; 

// смещение центра начала координат
extern s32 * dXPos;
extern s32 * dYPos;
extern s32 * dZPos;

// разрешение на использование пульта по RS-485
//extern u8	*pUsesKP485;

// интервалы опроса частотника пульта УУПС
extern u16 *pIntKPCtrl;
extern u16 *pIntKPCtrlStop;

// количество команд без квитанций для пульта
extern u8	*pKP_NA_Max;


// связь с ПУ 
extern u8 *pLinkKP;
// количество команд без квитанций для пульта
extern u8	KP_NA_Count;
// признак корректной остановки 
extern u8 *pCorrStop;
// признак восстановления текущего блока
extern u8 *pRecoverBlock;
// режим коррекции высоты инструмента
extern u8 *pHTCorr; 
// режим обнуления координаты Z по датчику
extern u8 *pZZeroDat; 
// режим работы по горизонтальному датчику
extern u8 *pHorizontalDat;
// направление горизонального датчика 0 off 1 up 2 left 3 down 4 right
extern u8 *pHorizDatDir;
// состояние выполнения горизонального датчика 0 off 1 go 2 ok 3 fault
extern u8 *pHorizDatState;
	// диаметр шарика датчика
extern float *pHorizDiam;
	// погрешность измерения
extern float *pHorizMeasError;
// координата X после срабатывания датчика
extern float *pHorizX;
// координата Y после срабатывания датчика
extern float *pHorizY;



// признак остановки или паузы выполнения программы
extern u8	fStopPrg;
// признак пуска программы
extern u8	fStartPrg;
// флаг сохранения регистров
extern u8	fSaveRegs;

// частота вращения вала об/мин при номинальной частоте сети pFnom
extern u16 *pFdbyFnom;	
// номинальная частота сети
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


