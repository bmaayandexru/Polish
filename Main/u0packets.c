#include <string.h>
//#include <RTL.h>

#include "UART.h"
#include "Defs.h"
#include "regs.h"
#include "VirtualPins.h"
#include "u0packets.h"
#include "modbus.h"
#include "Motors.h"
#include "Motor_Z.h"
#include "Handlers.h"
#include "ti.h"
#include "FS.h"
#include "bFS.h"
#include "Flash.h"
#include "sbl_iap.h"
#include "queue.h"
#include "msg.h"
#include "FreqInvr.h"

#include "VPFrz.h"

//volatile BOOL	fU1toU0=FALSE;
typedef 	char   	tline[20];
u8 wbuf[255],rbuf[255];

void	DataToU1(u8 * buffer,u16 len){
	// транзитная передача команд частотника
	mbBufferToPack(1,buffer+2,len-6);
	mbInsPackToQueue(quCmdTransit,1);
}

void 	RunBootLoader(void){
	//SaveRegs();
	NVIC_DisableIRQ(UART0_IRQn); 
 	NVIC_DisableIRQ(UART1_IRQn); 
	NVIC_DisableIRQ(TIMER0_IRQn);
	NVIC_DisableIRQ(TIMER1_IRQn);

	__disable_irq();
	SCB->VTOR = 0x00000000 & 0x1FFFFF80;
	boot_jump(0);
}

void ReadRegs(u8 * buffer,u16 len){
	u16 saddr;
	u8 count;
	// чтение выходных регистров
	memcpy(&saddr,buffer+2,2); // стартовый адрес регистров
	//saddr = swap(saddr);
	memcpy(&count,buffer+4,1);
//	Msg("RR A %X C %d \r\n",saddr,count);
	//count = swap(count);
	if (saddr > REGS_COUNT-1) {
		// ошибка
		mbByteToPack(0,*buffer);
		mbByteToPack(0,*(buffer+1)|0x80);
		mbByteToPack(0,MBE_ADDR_FAULT);
	} else {
		// всё в порядке
		mbByteToPack(0,*buffer);
		mbByteToPack(0,*(buffer+1));
		mbWordToPackNoSwap(0,saddr);
		mbByteToPack(0,(u8)(count));
		mbBufferToPack(0,(u8*)&(regs[saddr]),count);
//		Msg("D0 %x",regs[saddr]);
	}
	mbSendPack(0);
}

u8 EnableWrite(u8 * data,u16 saddr,u8 len){
// возвращает 0 если запись разрешена
// 1 если обнаружена попытка записи в регистр только для чтения
// 2 регистр пишется не полностью (не сначала)
// 3 не хватает данных для записи регистра
	u32 tp;
	u16 i;
	u8 Ecode;
	u8 tlen;
	int ofs;
	tp = (u32)&(regs[saddr]);
//	Msg("EnWr a %d l %d\r\n",saddr,len);
	// проверка правомерности записи
	// поиск адреса в массиве атрибутов и вызов обработчика
	Ecode = 0;
	for (i=0;i<iva;i++) {
		if (Cross(tp,len,(u32)va[i].p,va[i].len)){
		 	if (va[i].attr==ro) {
				// атрибут только чтение
				Ecode = 1;
			} else
			if (va[i].attr==rw) { 
				// атрибут чтение и запись
				if (va[i].handle != 0) {
					// есть обработчик
					// определить смещение данных для регистра и длину
					ofs = (int)((u32)va[i].p - tp);
					if (ofs >= 0) {
						tlen = len - ofs;
						if (tlen >= va[i].len) {
							// данных достаточно
							Ecode = (*(va[i].handle))(va[i].name,data+ofs,tlen);
						} else {
							// данных не достаточно
							Ecode = 3;
						}
					} else {
						// смещение отрицательно - регистр пишется не полностью
						Ecode = 2;
					}
				} else 
					// нет обработчика - запись разрешена	
					Ecode = 0;
			}
		}
		if (Ecode) break;
	}
	return Ecode;
}

void _memcpy(u8 * d,u8 * s,u16 count){
	u16 i;
	u8 * ps;
	u8 * pd;
	ps = s;
	pd = d;
	for (i=0;i<count;i++){
		*pd=*ps;
		pd++; ps++;
	}
}

void WriteRegs(u8 * buffer,u16 len){
	// запись РОНов
	u16 saddr;
	u8 count;
	u8 data[255];
	u8 ECode;
	memcpy(&saddr,buffer+2,2); // стартовый адрес регистров
	memcpy(&count,buffer+4,1); // количество
	memcpy(data,buffer+5,count);
//	Msg("WA a %X с %d %d\r\n",saddr,count,data[0]);
//	Dump(data,count);
	ECode = EnableWrite(data,saddr,count);
//	Msg("WA a %X с %d ecode %d\r\n",saddr,count,ECode);
	if (ECode == 0) {
		// всё в порядке
//		memcpy(data,buffer+5,count);
//		memcpy(regs+saddr,data,count);
		_memcpy(&(regs[saddr]),data,count);
		mbByteToPack(0,*buffer);
		mbByteToPack(0,*(buffer+1));
		mbBufferToPack(0,buffer+2,2);
		mbBufferToPack(0,buffer+4,1);
		mbBufferToPack(0,buffer+5,count);
		//Msg("D0 %d",regs[saddr]);
	} else {
		// ошибка
		mbByteToPack(0,*buffer);
		mbByteToPack(0,*(buffer+1)|0x80);
		mbByteToPack(0,ECode);
	}
	mbSendPack(0);
}

void GoToPoint(u8* buffer,u16 len) {
	u8 en;
	float x,y;//,xs,ys;
	memcpy((u8*)&en,(buffer+2),1);
	memcpy((u8*)&x,(buffer+3),4);
	memcpy((u8*)&y,(buffer+7),4);
	Msg("GoTo en %d x %d y %d\r\n",en,(int)(x),(int)(y));
#ifdef __SAW__
	InitMove(en,x,y);
#endif
//	XYToARImp(xs,ys,&ms_A.Pos,&ms_R.Pos);
//	Msg(" xs %d ys %d Apos %d Rpos %d\r\n",(int)(xs*1000),(int)(ys*1000),ms_A.Pos,ms_R.Pos);
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbSendPack(0);
}

void LSSendProc(u8* buffer,u16 len) {
	u8 st,rev;
	u16 Freq,Speed;
	memcpy((u8*)&st,(buffer+2),1);
	memcpy((u8*)&rev,(buffer+3),1);
	memcpy((u8*)&Speed,(buffer+4),2);
	Freq = (int)(Speed  * (*pFnom)/ (*pFdbyFnom));
// частота вращения вала об/мин при номинальной частоте сети pFnom Гц
//	*pFdbyFnom = 18000;	
// номинальная частота сети Гц
//	*pFnom = 300;	
	Msg("FrConv St %d Rev %d Speed %d Fr %d\r\n",st,rev,Speed,Freq);
	if (st) {
		QSetPin(COOLER1);
		FIUnlock();
		FISetFreq(Freq);
		FISetDir(rev);
		FIStart();		
	} else {
		QClrPin(COOLER1);
		FIStop();
	}
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbSendPack(0);
}

void QAllocTable(u8* buffer,u16 len) {
	OutAllocTable = 1;
	CurVarIndex = 0;
	Msg("QAllocTable... %d %d %d\r\n",OutAllocTable,CurVarIndex,iva);
	StartTI(tiOutAT,tiMsToTick(200));
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbSendPack(0);
}
			
void pFS_FInfo(u8* buffer,u16 len) {
	// объявили структуру 
	FInfo vf;
	u32 index;
	u8 name[15];
	u8 ext[4];
	u8 attr;
	u32 size;
	tFile f;
	s8 res;

	memset(name,0,15);
	memset(ext,0,4);
	index=0;
	attr = 0;
	size = 0;
	f = 0;

	// очистили структуру
	memset((void*)&vf,0,sizeof vf);
	memcpy((u8*)&index,(buffer+2),sizeof index); 
//	Msg("FS_FInfo Num %d size vf %d\r\n",index,sizeof vf);
	// читаем с *(buffer+2) индекс файла
	// ищем его в файловой системе
	// предполагаем что он найден 
	res = FS_GetFileInfo(
				&index,
				name,
				ext,
				&attr,
				&size,
				&f
			 );
//	Msg("Info i:%d n:%s e:%s a:%2X s:%d f:%d res %d\r\n",index,name,ext,attr,size,f,res);
	if (res == FS_RESULT_OK) {
		vf.index = index;
		memcpy(vf.name,name,15);
		memcpy(vf.ext,ext,4);
		vf.attr = attr;
		vf.size = size;
		vf.f = f;
	}

	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,res);
	mbBufferToPack(0,(u8*)&vf,sizeof vf);
	mbSendPack(0);
}

void pFS_SetFInfo(u8* buffer,u16 len) {
	Msg("FS_SetFInfo\r\n");
	// читаем с *(buffer+2) индекс файла
	// читаем с *(buffer+3) FInfo
	// применяем к файлу с индексом *(buffer+2) параметры FInfo
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	// тут добавить в пакет результат операции
	// 0 - всё хорошо
	// 1 - нет файла с таким индексом
	// 2 - файл открыт
	// 
	mbSendPack(0);
}
void pFS_Delete(u8* buffer,u16 len) {
	u8 name[20];
	s8 res;
	memset(name,0,20);
	memcpy(name,(buffer+3),*(buffer+2));
	res = FS_Delete(name);
	if (res < 0) Msg("FS_Delete %s r:%d\r\n",name,res);
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,res);
	mbSendPack(0);
}

void pFS_Create(u8* buffer,u16 len) {
	u8 name[20];
	tFile f;
	s8 res;
	// *(buffer+2)  - 14 байт имени
	memset(name,0,20);
	memcpy(name,(buffer+3),*(buffer+2));
//	Msg("FS_Create %s\r\n",name);
	res = FS_Delete(name); // пока не переделан Rewrite нужно удалить
	if (res < 0) Msg("FS_Cr Del %s r:%d\r\n",name,res);
	res = FS_Assign(name,&f);
	if (res == FS_RESULT_OK) { 
		res = FS_Rewrite(f);
		if (res < 0) {
			 Msg("FS_Cr Rewrite %s r:%d\r\n",name,res);
			 FS_Close(&f);
		}
		else Msg("FS_Create %s f:%d res:%d\r\n",name,f,res);
	} else Msg("FS_Cr Assign %s res:%d \r\n",name,res); 

	// *(buffer+16)	- 4 байта расширения
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,res);  	// результат создания
	mbByteToPack(0,(u8)f);  // индекс файла
	// добавить результат
	// 0 - всё хорошо
	// 1 - файл с таким именем существует
	mbSendPack(0);
}

void pFS_Rewrite(u8* buffer,u16 len) {
	u8 name[20];
	tFile f;
	s8 res;
	memset(name,0,20);
	memcpy(name,(buffer+3),*(buffer+2));
	res = FS_Assign(name,&f);
	if (res == FS_RESULT_OK) { 
		res = FS_Rewrite(f);
		if (res < 0) {
			FS_Close(&f);
			Msg("FS_Rewrite %s r:%d h %d\r\n",name,res,f);
		}
		else Msg("FS_Rewrite %s f:%d\r\n",name,f); 
	} else Msg("FS_Rewrite FS_Assign %s res:%d\r\n",name,res); 
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,res);  
	mbByteToPack(0,(u8)f);
	mbSendPack(0);
}

void pFS_RewriteHandle(u8* buffer,u16 len) {
	tFile f;
	s8 res;
	f = (tFile)*(buffer+2);
	Msg("FS_Rewrite in h %d\r\n",f);
	res = FS_Rewrite(f);
	if (res < 0) {
		FS_Close(&f);
		Msg("FS_Rewrite r:%d h %d\r\n",res,f);
	}
	else Msg("FS_Rewrite h:%d\r\n",f); 
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,res);  
	mbByteToPack(0,(u8)f);
	mbSendPack(0);
}

void pFS_Append(u8* buffer,u16 len) {
	u8 name[20];
	tFile f;
	s8 res;
	memset(name,0,20);
	memcpy(name,(buffer+3),*(buffer+2));
	res = FS_Assign(name,&f);
	if (res == FS_RESULT_OK) { 
		res = FS_Append(f);
		if (res < 0) Msg("FS_Append %s r:%d\r\n",name,res);
		else Msg("FS_Append %s f:%d\r\n",name,f);
	} else Msg("FS_Append FS_Assign %s r:%d\r\n",name,res); 
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,res);
	mbByteToPack(0,f);
	mbSendPack(0);
}

void pFS_Reset(u8* buffer,u16 len) {
	u8 name[20];
	tFile f;
	s8 res;
	memset(name,0,20);
	memcpy(name,(buffer+3),*(buffer+2));
	res = FS_Assign(name,&f);  // 0 - всё хорошо
	if (res == FS_RESULT_OK) { 
		res = FS_Reset(f);   // 0 - всё хорошо
		if (res < 0) Msg("FS_Reset %s r:%d\r\n",name,res);
	} else Msg("FS_Reset FS_Assign %s f:%d\r\n",name,f); 
	Msg("FS_Reset %s h:%d r:%d\r\n",name,f,res); 
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,res);
	mbByteToPack(0,f);
	mbSendPack(0);
}

//u8 wbuffer[4096];

void pFS_Write(u8* buffer,u16 len) {
	tFile f;
	s8 res;
	u16 size;
	u32 wbc;
//	memset(wbuffer,0,255);
	f = (tFile)*(buffer+2); 	// - номер или описатель куда пишем
//	size = *(buffer+3);		// - количество байт данных
	memcpy(&size,(buffer+3),2);	// - количество байт данных
//	memcpy(wbuffer,(buffer+5),size);	// - данные 
//	Msg("FS_Write in f:%d size:%d\r\n",f,size);
//	res = bFS_Write(f,wbuffer,size,&wbc);
	res = bFS_Write(f,(buffer+5),size,&wbc);
//	res = 0;
	if (res < 0) Msg("FS_Write f:%d r:%d\r\n",f,res);
//	res = bFS_Write((tFile)*(buffer+2),(buffer+4),*(buffer+3));
	//Msg("FS_Write f:%d s:%d buf[0]:%X res:%d\r\n",f,size,buf[0],res);
//	Msg("%d",len);
//	if (len!=16) {
//		Dump(buffer,len);
//	}
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
//	mbByteToPack(0,*(buffer+2));
//	mbByteToPack(0,*(buffer+3));
//	mbBufferToPack(0,wbuf,size);
	mbBufferToPack(0,(u8*)&res,sizeof res); // код завершения операции
	mbSendPack(0);
}

s8 bFS_WriteLn(tFile fcs_num, const u8 *str) {
	s8 res;
	s32 i;
	i = 0;
	while (*(str+i)) {
		res = FS_WriteByte(fcs_num,*(str+i));
		//res = 0;
		if (res < 0) return res;
		i++;
	}
	return res; 
}

void pFS_WriteLn(u8* buffer,u16 len) {
	tFile f;
	s8 res;
	u8 size;
	u8 buf[255];
	memset(buf,0,255);
	f = (tFile)*(buffer+2); 	// - номер или описатель куда пишем
	size = *(buffer+3);		// - количество байт данных
	memcpy(buf,(buffer+4),size);	// - данные 
	res = bFS_WriteLn(f,buf);
	//res = 0;
	//if (res < 0) Msg("FS_Write f:%d buf:%s res:%d\r\n",f,buf,res);
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,res); // код завершения операции
	mbSendPack(0);
}

void pFS_Read(u8* buffer,u16 len) {
	tFile f;
	s8 res;
	u8 size;
	u32 rbc;
	memset(rbuf,0,255);
	f = (tFile)*(buffer+2); 		// - описатель откуда читаем
	size = *(buffer+3);				// - количество байт данных
	res = bFS_Read(f,rbuf,size,&rbc);
	if (res < 0) Msg("FS_Read f:%d s%d res:%d\r\n",f,size,res);
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,res);
	mbByteToPack(0,size);
	mbBufferToPack(0,rbuf,size);
	mbSendPack(0);
}

void pFS_ReadLn(u8* buffer,u16 len) {
	tFile f;
	s8 res;
	u8 buf[255];
	memset(buf,0,255);
	f = (tFile)*(buffer+2); 		// - описатель откуда читаем
	res = bFS_ReadLn(f,buf,50);
	if (res < 0) Msg("FS_ReadLn f:%d buf:%s res:%d\r\n",f,buf,res);
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,res);
	mbByteToPack(0,strlen((const char*)buf));
	mbBufferToPack(0,buf,strlen((const char*)buf));
	mbSendPack(0);
}

void pFS_BReadLn(u8* buffer,u16 len) {
	tFile f;
	s8 res;
	u8 buf[255];
	memset(buf,0,255);
	f = (tFile)*(buffer+2); 		// - описатель откуда читаем
	res = bFS_BReadLn(f,buf,50);
//	Dump(buf,strlen((const char*)buf));
	if (res < 0) Msg("FS_ReadLn f:%d buf:%s res:%d\r\n",f,buf,res);
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,res);
	mbByteToPack(0,strlen((const char*)buf));
	mbBufferToPack(0,buf,strlen((const char*)buf));
	mbSendPack(0);
}

void pFS_Pos(u8* buffer,u16 len) {
	tFile f;
	s32 res;
	s32 pos;
	f = (tFile)*(buffer+2); 		// - описатель
	res = FS_Pos(f,&pos);
//	Dump(buf,strlen((const char*)buf));
//	Msg("FS_Pos f:%d res:%d\r\n",f,res);
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,res);
	mbBufferToPack(0,(u8*)&pos,sizeof pos);
	mbSendPack(0);
}

void pFS_Seek(u8* buffer,u16 len) {
	tFile f;
	u32 pos;
	s8 res;
	f = (tFile)*(buffer+2); 
	memcpy((u8*)&pos,(buffer+3),sizeof pos);
	res = FS_Seek(f,pos);	
	if (res < 0) Msg("FS_Seek f:%d pos:%d res:%d\r\n",f,pos,res);
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,res);
	mbSendPack(0);
}

void pFS_Close(u8* buffer,u16 len) {
	tFile f;
	s8 res;
	f = (tFile)*(buffer+2); 
	res = FS_Close(&f);
	if (res<0)	Msg("FS_Close f:%d res:%d\r\n",f,res);
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,res);
	mbSendPack(0);
}

void pCreateRegsBin(u8* buffer,u16 len) {
	SaveRegs();
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbSendPack(0);
}

void pApplyRegsBin(u8* buffer,u16 len) {
	LoadRegsFromFile();
#ifdef __SAW__
	InitSawRegsAfterLoad();
	LoadSawBackupRegs();	
#endif 
#ifdef __FREZER__
	InitFrzRegsAfterLoad();
	LoadFrzBackupRegs();	
#endif 
	InitVirtualPins();
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbSendPack(0);
}

void pReset(u8* buffer,u16 len) {
	// пока не переделан Rewrite
	NVIC_DisableIRQ(UART0_IRQn); 
 	NVIC_DisableIRQ(UART1_IRQn); 
	NVIC_DisableIRQ(TIMER0_IRQn);
	NVIC_DisableIRQ(TIMER1_IRQn);

	__disable_irq();
	SCB->VTOR = 0x00000000 & 0x1FFFFF80;
	boot_jump(0x2000);
}

void pFl_GetUsing(u8 *buffer,u16 len) {
	u8 FNTU,CATU;

	FNTU=(u8)(FS_FindFreeFNT()*100/FNTRecordsNumber);	
	CATU=(u8)(FS_FindFreeCluster()*100/CATRecordsNumber);

//	Msg("Fl_GetUsing %d %d\r\n",FNTU,CATU);
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,FNTU);
	mbByteToPack(0,CATU);
	mbSendPack(0);
}

void pFl_BulkErase(u8 *buffer,u16 len) {
	u8 res;
	Msg("Fl_BulkErase\r\n");
	FLASH_BulkErase();
	res = FS_Init();
	if (res==FS_RESULT_OK) {
		Msg("FS Init Ok.\r\n");
	}
	else Msg("FS Init Fault. Err %d\r\n",res);
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,res);
	mbSendPack(0);
}

void pFl_GetTimeouts(u8 *buffer,u16 len) {
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbSendPack(0);
}

void pFl_SetTimeouts(u8 *buffer,u16 len) {
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbSendPack(0);
}

void pFl_EraseSector(u8 *buffer,u16 len) {
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbSendPack(0);
}

void pGetRegInfo(u8 *buffer,u16 len) {
	u8 Index;
	u16 Ofs,Size;
	char name[20];
	Index = *(buffer+2);
	if (Index >= iva) {
		Ofs = 0xFFFF; Size = 0; memset(name,0,20);
	} else {
		memcpy(name,va[Index].name,20);	// имя
		Ofs = (u32)va[Index].p - (u32)&regs[0];			// указатель
		Size = va[Index].len;
	}
	//Msg("Index %d Ofs %d Size %d name %s\r\n",Index,Ofs,Size,name);
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,Index);
	mbBufferToPack(0,(u8*)&Ofs,sizeof Ofs);
	mbBufferToPack(0,(u8*)&Size,sizeof Size);
	mbBufferToPack(0,(u8*)name,sizeof name);
	mbSendPack(0);
}

void pGetVersion(u8 *buffer,u16 len) {
	u32 ver;
	ver = VERSION;
//	Msg("GetVersion %08X \r\n",ver);
	Msg("Polish (%08X) build %d\r\n",VERSION,build);
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbBufferToPack(0,(u8*)&ver,sizeof ver);
	mbSendPack(0);
}

void pGetBusy(u8 *buffer,u16 len) {
	Msg("Busy %d En %d mr3 %d tc %d\r\n",Busy,fmvc.Enable,LPC_TIM1->MR3,LPC_TIM1->TC);
	 
//	Msg("Z L %d MP %d T %d LPOFF %d LPON%d\r\n",ms_Z.Level,*(mc_Z.MovePos),ms_Z.Tcur,ms_Z.LPOFF,ms_Z.LPON);
//	QSetPin(MOTOR_X_STEP);
	//QSetPin(MOTOR_Yl_STEP);
	//QSetPin(MOTOR_Yr_STEP);
	//QSetPin(MOTOR_Z_STEP);
//	Msg("GetPin sZ %d \r\n",QGetPin(SENS_MOTOR_Z));
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbSendPack(0);
}

void pGetBlock(u8 *buffer,u16 len) {
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbBufferToPack(0,(u8*)eb,sizeof (*eb));
	mbSendPack(0);
}

void pGetTimers(u8 *buffer,u16 len) {
	u8 Tnum, MR;
	LPC_TIM_TypeDef       * pT;
	u32*	pMR;
//	QClrPin(MOTOR_X_STEP);
	//QClrPin(MOTOR_Yl_STEP);
	//QClrPin(MOTOR_Yr_STEP);
	//QClrPin(MOTOR_Z_STEP);
	Tnum = *(buffer+2); // таймер
	MR = *(buffer+3);	// MR
	switch (Tnum) {	
		case 0:pT=LPC_TIM0; break;
		case 1:pT=LPC_TIM1; break;		
		case 2:pT=LPC_TIM2; break;
		case 3:pT=LPC_TIM3; break;
	}

 	switch (MR){
		case 0:	pMR=(u32*)&(pT->MR0); break;
		case 1: pMR=(u32*)&(pT->MR1); break;
		case 2:	pMR=(u32*)&(pT->MR2); break;
		case 3: pMR=(u32*)&(pT->MR3); break;
	}

	Msg("T%d TC %u MR%d %u\r\n",Tnum,pT->TC,MR,*pMR);
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbSendPack(0);
}

void pInitZCorr(u8 *buffer,u16 len) {
	InitZComp();
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbSendPack(0);
}
void pSetPin(u8 *buffer,u16 len) {
	if (*(buffer+3)) QSetPin(*(buffer+2));
	else QClrPin(*(buffer+2));
//	Msg("SetPin n %d s %d\r\n",*(buffer+2),*(buffer+3));
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbSendPack(0);
}

void pGetPin(u8 *buffer,u16 len) {
	u8 b;
	b=QGetPin(*(buffer+2));
	Msg("GetPin n %d s %d\r\n",*(buffer+2),b);
	mbByteToPack(0,*buffer);
	mbByteToPack(0,*(buffer+1));
	mbByteToPack(0,*(buffer+2));
	mbByteToPack(0,b);
	mbSendPack(0);
}

void SendAddPointPack(s32 * pIndex,float * px, float * py) {
	mbByteToPack(0,ADDR_U0);
	mbByteToPack(0,cmAddPoint);
	mbBufferToPack(0,(u8*)pIndex,4);
	mbBufferToPack(0,(u8*)px,4);
	mbBufferToPack(0,(u8*)py,4);
	mbSendPack(0);
}

void SendAddPointPackFrz(s32 * pIndex,float * px, float * py, float * pz) {
	mbByteToPack(0,ADDR_U0);
	mbByteToPack(0,cmAddPoint);
	mbBufferToPack(0,(u8*)pIndex,4);
	mbBufferToPack(0,(u8*)px,4);
	mbBufferToPack(0,(u8*)py,4);
	mbBufferToPack(0,(u8*)pz,4);
	mbSendPack(0);
}

void FixPointPackFrz(s32 * pIndex,float * px, float * py, float * pz) {
	switch (*pIndex){
		case 1:
			*pX1 = *px; *pY1 = *py; *pZ1 = *pz;
			break;
		case 2:
			*pX2 = *px; *pY2 = *py; *pZ2 = *pz;
			break;
		case 3:
			*pX3 = *px; *pY3 = *py; *pZ3 = *pz;
			break;
	}
}

void mbFrzPackHandler0(u8 * buffer,u16 len){
	// проверка адреса
	// if ((*buffer) != Addr) return;
	//Dump(buffer,len);
	//return;

	switch (*(buffer+1)) {
		case cmReadRegs: ReadRegs(buffer,len); break;
		case cmWriteRegs: WriteRegs(buffer,len); break;
		case cmGoToPoint:GoToPoint(buffer,len); break;
		case cmTest :
			// тест  - петля
			mbBufferToPack(0,buffer,len-2);
			mbSendPack(0);
			break;
		case cmRunBootLoader: RunBootLoader(); 		break;
		case cmDbgMsg 		:						break;
		case cmDataToU1		: DataToU1(buffer,len);	break;
		// во фрезере нет поворота и смещения
		//case cmShiftRotate	: ShiftRotate(buffer,len);	break;
		case cmLSSend		: LSSendProc(buffer,len);	break;
		case cmQAllocTable  : QAllocTable(buffer,len);	break;

 		case cmFS_FInfo 	: pFS_FInfo(buffer,len); break;
 		case cmFS_SetFInfo 	: pFS_SetFInfo(buffer,len); break;
 		case cmFS_Delete 	: pFS_Delete(buffer,len); break;
							  
 		case cmFS_Create 	: pFS_Create(buffer,len); break;
 		case cmFS_Rewrite 	: pFS_Rewrite(buffer,len); break;
 		case cmFS_RewriteHandle : pFS_RewriteHandle(buffer,len); break;
 		case cmFS_Append 	: pFS_Append(buffer,len); break;
 		case cmFS_Reset 	: pFS_Reset(buffer,len); break;

 		case cmFS_Write 	: pFS_Write(buffer,len); break;
 		case cmFS_Read 		: pFS_Read(buffer,len); break;
 		case cmFS_Seek 		: pFS_Seek(buffer,len); break;
 		case cmFS_Close 	: pFS_Close(buffer,len); break;
 		case cmFS_WriteLn 	: pFS_WriteLn(buffer,len); break;
 		case cmFS_ReadLn	: pFS_ReadLn(buffer,len); break;
 		case cmFS_BReadLn	: pFS_BReadLn(buffer,len); break;
 		case cmFS_Pos		: pFS_Pos(buffer,len); break;
 		case cmCreateRegsBin: pCreateRegsBin(buffer,len); break;
 		case cmApplyRegsBin	: pApplyRegsBin(buffer,len); break;
 		case cmReset		: pReset(buffer,len); break;

 		case cmFl_GetUsing  : pFl_GetUsing(buffer,len); break;
 		case cmFl_BulkErase : pFl_BulkErase(buffer,len); break;
		case cmGetRegInfo : pGetRegInfo(buffer,len); break;
		case cmGetVersion : pGetVersion(buffer,len); break;
		case cmGetBusy : pGetBusy(buffer,len); break;
		case cmGetBlock : pGetBlock(buffer,len); break;
		case cmGetTimers : pGetTimers(buffer,len); break;
		case cmInitZCorr : pInitZCorr(buffer,len); break;
		case cmSetPin : pSetPin(buffer,len); break;
		case cmGetPin : pGetPin(buffer,len); break;

/*
 		case cmFl_GetTimeouts : pFl_GetTimeouts(buffer,len); break;
 		case cmFl_SetTimeouts : pFl_SetTimeouts(buffer,len); break;
 		case cmFl_EraseSector : pFl_EraseSector(buffer,len); break;
*/

		default :
			// неизвестная команда
			break;
	}
}

//u8 buffer0[255];
u8 buffer0[10];
void	UART0_Thread(void){
	u16 Count;
	Count=0;
//	buffer[0]=0x55;
	Count=UARTx_ReadyRecvData(0);
//	TITimer(tiTest2,tiMsToTick(1000), Msg("u"));
	if (Count) {
		// данные есть
//			if (EndTI(tiTestTime)){
//				Msg("#\r\n");
//				StartTI(tiTestTime,tiMsToTick(100));
//			}
//		if (UARTx_RecvBuffer(0,buffer0,Count)){
		if (UART0_RecvBuffer(buffer0,Count)){
			mbRecvBuffer(0,buffer0,Count);
		} 
	} else {
		mbIdle(0);
	}
}
