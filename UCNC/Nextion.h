#ifndef __NEXTION_H__
#define __NEXTION_H__

#include "Defs.h"

//--------------------- коды возврата nextion -----------------------------
// 0x00 не верная инструкция
#define NER_InstFault 0x00

// инструкция выполнена верно
#define NER_InstOk		0x01

// неверный идентификатор компонета
#define NER_IDFault		0x02

// не верный идентификатор страницы
#define NER_PagIDFault	0x03

// не верный индентификатор изображения
#define NER_PicIDFault	0x04

// не верный идетификатор шрифта
#define NER_FntIDFault	0x05

// Недопустимая Файловая операция
#define NER_FopFault 	0x06

// Неверная CRC
#define NER_CRCFault	0x09

// Неверная настройка скорости передачи 
#define NER_BaudFaul	0x11

// Неверный идентификатор waveform или номера канала
#define NER_WavIDFault	0x12

// Недопустимое имя переменной или атрибут
#define NER_NameFault	0x1A

// Недопустимая операция с переменной
#define NER_VOPFault	0x1B

// не удалось назначить назначение
#define NER_OPFault	0x1C

//Сбой операции EEPROM
#define NER_EEPROMFault 0x1D

// Недопустимое количество параметров
#define NER_PCFault	0x1E

// Сбой операции ввода-вывода
#define NER_IOFailt	0x1F

// Недопустимый Escape-символ
#define NER_EscFault	0x20

// Слишком длинное имя переменной
#define NER_LongName	0x23

// Переполнение последовательного буфера
#define NER_UARTFull	0x24

// Событие касания (отпускания)
#define NER_PushEvent	0x65

// Текущий номер страницы
#define NER_CurPage	0x66

// Координаты касания (пробуждение)
#define NER_PushKoodWake	0x67

// Координаты касания (спящий режим)
#define NER_PushKoodSleep	0x68

// получена строка
#define NER_GetString	0x70

// Числовые данные
#define NER_GetNum	0x71

// Переход В Спящий режим
#define NER_ToSleep	0x86

// Автоматическое пробуждение от сна
#define NER_AutoWake	0x87

// готовность
#define NER_Ready	0x88

// Запуск обновления с microSD
#define NER_StartUpdateMSD	0x89

// Передача данных завершена
#define NER_TramsDataEnd	0xFD

// Готовность к получению данных
#define NER_RecvDataReady	0xFE

extern u8 neEOLN[]; // Маркер конца FFFFFF
										// используется в Modbus
										// все пакеты модбас теперь могут иметь такой 
										// конец для удобства обработки ПО
										// необходимость такого конца регулируется регистрами
										// названия уточняются

//------------------- функции, обеспечивающие прием ------------------------

// тип обработчика приема пакета
typedef void(*TPackHandler)(u8 * buffer,u16 len);

// установка обработчика
void neSetHandler(u8 num,TPackHandler ph);

// прием буфера
void neRecvBuffer(u8 num, u8 * buffer,u16 len);

// передача строчной команды типа "sendme"
void neCmd(u8 * cmd);

// передача строчной команды с числовым параметром типа "n0.val" "=" 100
void neCmdVal(u8 * cmd,s32 val);

// передача запроса типа get с указание что ждем и сколько (уточняется)
void neCmdQwr(u8 * cmd,u8 WhatWait,u8 WaitCount);



#endif
