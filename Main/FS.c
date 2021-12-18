//=============================================================================
//
//                            Файловая система
//
//=============================================================================

#include <stdio.h>
//#include <stdlib.h>
#include <string.h>

#include "Defs.h"
#include "Tools.h"
#include "FS.h"
#include "Flash.h"

#include "msg.h"

// Адрес FLASH-памяти
#define FLASH_ADDRESS(a) (a)


#define MAX_FILES  8														// Макс. кол-во открытых файлов

//#define FLASH_BANKS_NUM  1													// Кол-во банков FLASH-памяти

// Параметры FLASH-памяти
#define FLASH_SECTORS_PER_BANK  64											// Кол-во секторов в банке FLASH
#define FLASH_PAGES_PER_SECTOR  1024										// Кол-во страниц в секторе
#define PAGE_SIZE  256														// Размер страницы (байт)

// Параметры Файловой Системы
#define PAGES_PER_CLUSTER  64												// Кол-во страниц в кластере
#define FNT_BASE_ADDRESS  32												// Базовый адрес таблицы FNT

#define FNT_RECORD_SIZE  32													// Размер записи таблицы FNT
#define CAT_RECORD_SIZE  3													// Размер записи таблицы CAT

#define FILE_NAME_LENGTH  14												// Длина имени файла
#define FILE_TYPE_LENGTH  3													// Длина типа файла

u8 FLASH_BANKS_NUM=0;

//=============================================================================
//                              ОПРЕДЕЛЕНИЯ
//=============================================================================

// Состояние файловой системы
enum constFSState {
	FS_STATE_FLASH_CLEAR	= 0xFF,											// Чистая FLASH (ФС отсутствует)
//	резерв					= 0xFE,											//
	FS_STATE_READY			= 0xFC,											// ФС готова к работе
//	резерв					= 0xF8,											//
//	резерв					= 0xF0,											//
//	резерв					= 0xE0,											//
//	резерв					= 0xC0,											//
//	резерв					= 0x80,											//
//	резерв					= 0x00,											//
};

/*
// Тип открытия файла
enum constAssignType {
	ASSIGN_TYPE_REWRITE,													// Открыть файл для записи
	ASSIGN_TYPE_APPEND,														// Открыть файл для добавления
	ASSIGN_TYPE_RESET														// Открыть файл для чтения
};
*/

// Состояние структуры FCS
enum constFCSState {
	FCS_STATE_CLOSED,														// Структура FCS закрыта
	FCS_STATE_OPENED,														// Структура FCS открыта
	FCS_STATE_OPENED_READ,													// Структура FCS открыта для чтения файла
	FCS_STATE_OPENED_WRITE													// Структура FCS открыта для записи файла
};


// Атрибуты файла
enum constFileAttr {
	FILE_ATTR_NOATTR   = 0xFF,												// Файл не имеет атрибутов
	FILE_ATTR_READONLY = 0xFE,												// Файл "Только для чтения"
	FILE_ATTR_HIDDEN   = 0xFD,												// Файл "Скрытый"
	FILE_ATTR_SYSTEM   = 0xFB,												// Файл "Системный"
//	FILE_ATTR_reserved   = 0xF7,												// (зарезервировано)
};


// Структура записи таблицы FNT (File Name Table)
typedef __packed struct {
	u8  FullName[1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1];				// Сигнатура1 + Имя + Тип + Сигнатура2
	u8  Attribute;															// Атрибуты файла
	u16 FirstCluster;														// Индекс (в таблице CAT) первого кластера файла
	u32 Size;																// Размер файла (кол-во байт)
	// reserved
} tFNT;


// Структура записи таблицы CAT (Cluster Allocation Table)
typedef __packed struct {
	u8  Flag;
	u16 NextCluster;
} tCAT;


// FCS (File Control Structure) - Структура управления файлом
typedef __packed struct {
	u8  State;																// Состояние файла
	u8  Name[FILE_NAME_LENGTH + 1];											// Имя файла
	u8  Type[FILE_TYPE_LENGTH + 1];											// Тип файла
	u32 FNT_num;															// Номер записи таблицы FNT
	u16 CurrCluster;														// Индекс (в таблице CAT) текущего кластера
	u8  CurrPage;															// Номер текущей страницы в текущем кластере
	u16 PageBufPtr;															// Текущий указатель в буфере PageBuffer[]
	u8  PageBuffer[PAGE_SIZE];												// Буфер текущей страницы
	u32 RemainSize;															// Оставшийся (непрочитанный) размер
	u32 MinFilePosition;													// Мин. позиция файла в текущей странице
	u32 MaxFilePosition;													// Макс. позиция файла в текущей странице
	tFNT FNT;																// Копия записи таблицы FNT открытого файла
} tFCS;


// Массив указателей на структуры FCS
tFCS  *pFCSArray[MAX_FILES];

// Массив структур FCS
tFCS  FCSArray[MAX_FILES];


// Служебная область Файловой Системы (адреса FLASH в служебной области ФС)
enum constFS_PARAM {
/*u8*/  FS_PARAM_FS_STATE = FLASH_ADDRESS(0),									// Состояние ФС
};


//=============================================================================
//                          ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ
//=============================================================================

//u8  FS_IS_INITED = FALSE;														// Флаг инициализации файловой системы
u8  FS_IS_INITED;														// Флаг инициализации файловой системы

u8  FS_STATE;																	// Состояние ФС

//Рабочие параметры Файловой Системы
//(вычисляются в начале работы)
u16 SECTORS_NUMBER;																// Кол-во секторов
u32 SECTOR_SIZE;																// Размер сектора

u16 CLUSTERS_PER_SECTOR;														// Кол-во кластеров в секторе
u16 CLUSTERS_NUMBER;															// Кол-во кластеров
u16 ClusterMAX;																	// Номер максимального кластера
u16 CLUSTER_SIZE;																// Размер кластера (байт)

u32 CAT_Size;																	// Размер отводимый для размещения таблицы CAT
u16 CATRecordsNumber;															// Кол-во записей в таблице CAT
u16 CATRecordMAX;																// Номер максимальной записи в таблице CAT

u32 FNTRecordsNumber;															// Кол-во записей в таблице FNT
u32 FNTRecordMAX;																// Номер максимальной записи в таблице FNT

u32 CAT_BASE_ADDRESS;															// Базовый адрес таблицы CAT
u32 CLUSTERS_BASE_ADDRESS;														// Базовый адрес таблицы кластеров


//=============================================================================
//                   СЛУЖЕБНЫЕ ФУНКЦИИ ФАЙЛОВОЙ СИСТЕМЫ
//=============================================================================

//-----------------------------------------------------------------------------
//              FS Init
//-----------------------------------------------------------------------------
s8 FS_Init(void) {
	u8 i;
//-	отставляем пока------------------------------------
	u8 bank_num;
	u8 ID;

	FLASH_BANKS_NUM = 0;
	FS_IS_INITED = 0;															// Обнулить кол-во банков FLASH-памяти

	// Опросить наличие банков
	for (bank_num = 0; bank_num < 4; bank_num++) {
		//	где функция FLASH_GetBankID ?????????? 
		ID = FLASH_GetBankID(bank_num);
//		Msg("B %d ID %X\r\n",bank_num,ID);
		if (ID == 0x18) {							// Если ID = 18h (тип флэш-памяти M25P128)
			FLASH_BANKS_NUM++;													// ДА - Увеличить кол-во банков
		}
//		if (FLASH_GetBankID(bank_num) == 0x18) {							// Если ID = 18h (тип флэш-памяти M25P128)
//			FLASH_BANKS_NUM++;													// ДА - Увеличить кол-во банков
//		}
		else {
			break;															// НЕТ - Завершить опрос банков
		}
	}
//	Msg("FBN %d\r\n",FLASH_BANKS_NUM);
	if (! FLASH_BANKS_NUM) {														// Обнаружены банки Флэш-памяти?
		return EFS_FLASH_NOT_INITED;														// НЕТ - Вернуть результат: "Флэш-память не инициализирована"
	}
//----Будет так--------------------------------------
// 	res = FLASH_Init();
//	if (res < 0) {
//  	// в res код ошибки
//	}	 
	// Проверить состояние ФС
	FS_STATE = FLASH_ReadByte(FS_PARAM_FS_STATE);

	// Если "Чистая FLASH"
	if (FS_STATE == FS_STATE_FLASH_CLEAR) {

		// Установить состояние ФС = "ФС готова к работе"
		//---------------------------------------------------------------
		FS_STATE = FS_STATE_READY;
		FLASH_WriteByte(FS_PARAM_FS_STATE, FS_STATE);
	}
	// Если "ФС готова к работе"
	else if (FS_STATE == FS_STATE_READY) {

	}

	// Вычислить рабочие параметры ФС
	//---------------------------------------------------------------
	SECTORS_NUMBER = FLASH_BANKS_NUM * FLASH_SECTORS_PER_BANK;						// Кол-во секторов
	SECTOR_SIZE = FLASH_PAGES_PER_SECTOR * PAGE_SIZE;								// Размер сектора

	CLUSTERS_PER_SECTOR = FLASH_PAGES_PER_SECTOR / PAGES_PER_CLUSTER;				// Кол-во кластеров в секторе
	CLUSTERS_NUMBER = (SECTORS_NUMBER - 3) * CLUSTERS_PER_SECTOR;					// Кол-во кластеров
	CLUSTER_SIZE = PAGES_PER_CLUSTER * PAGE_SIZE;									// Размер кластера

	// Размер отводимый для размещения таблицы CAT
	CAT_Size = CLUSTERS_NUMBER * CAT_RECORD_SIZE / FNT_RECORD_SIZE * FNT_RECORD_SIZE;
	if ( (CLUSTERS_NUMBER * CAT_RECORD_SIZE) % FNT_RECORD_SIZE ) {
		CAT_Size += FNT_RECORD_SIZE;												// (округлить в бо'льшую сторону)
	}
	CATRecordsNumber = CLUSTERS_NUMBER;												// Кол-во записей в таблице CAT

	FNTRecordsNumber = ( (SECTOR_SIZE - CAT_Size) / FNT_RECORD_SIZE ) - 1;			// Кол-во записей в таблице FNT

	CAT_BASE_ADDRESS = FNT_BASE_ADDRESS +
					   FNTRecordsNumber * FNT_RECORD_SIZE;							// Базовый адрес таблицы CAT
	CLUSTERS_BASE_ADDRESS = SECTOR_SIZE * 3;										// Базовый адрес таблицы кластеров

	ClusterMAX   = CLUSTERS_NUMBER  - 1;											// Номер максимального кластера
	CATRecordMAX = CATRecordsNumber - 1;											// Номер максимальной записи в таблице CAT
	FNTRecordMAX = FNTRecordsNumber - 1;											// Номер максимальной записи в таблице FNT

	// Заполнить массив указателей на стркутуры FCS
	for (i=0; i<MAX_FILES; i++) {
		pFCSArray[i] = FCSArray + i;
	}

	// Состояние всех структур FCS = "Закрыто"
	for (i=0; i<MAX_FILES; i++) {
		pFCSArray[i]->State = FCS_STATE_CLOSED ;
	}
// отладка потом убрать
//	return 0;

	FS_IS_INITED = 1;															// Файловая система инициализирована

	return FS_RESULT_OK;// 0
}


//-----------------------------------------------------------------------------
// Проверить строку на допустимые символы
//-----------------------------------------------------------------------------
bool FS_StrSymbolsValid(const u8 *str) {
	u8 s;
	u8 i;
	u8 len;

	len = strlen((char *)str);
	for (i = 0; i < len; i++) {
		s = str[i];
		if ( s <= ' ' ||
			 s == ':' ||
			 s == ';' ||
			 s == '.' ||
			 s == '*' ||
			 s == '?' ||
			 s == '/' ||
			 s == '|' ||
			 s == '\\' ) {
			return FALSE;
		}
	}

	return TRUE;
}


//-----------------------------------------------------------------------------
// Выделить из имени файла отдельно имя и тип
//-----------------------------------------------------------------------------
// В случае ошибки - возвращаются пустые строки
bool FS_GetNameAndType(const u8 *file_name, u8 *name, u8 *type) {
	u8 i, k;
	u8 s;

	// Выделить имя
	for (i = 0, k = 0; k <= FILE_NAME_LENGTH; i++, k++) {
		s = file_name[i];
		if (s && s != '.') {
			name[k] = s;
		}
		else {
			name[k] = 0;
			break;
		}
	}
	if (k == 0 || k > FILE_NAME_LENGTH) {									// Имя отсутствует или слишком длинное?
		name[0] = 0;
		type[0] = 0;
		return FALSE;														// ДА - Завершить с ошибкой "Неверный формат имени файла"
	}

	// Выделить тип
	if (s == '.') {
		for (i++, k = 0; k <= FILE_TYPE_LENGTH; i++, k++) {
			s = file_name[i];
			type[k] = s;
			if (!s) {
				break;
			}
		}
		if (k == 0 || k > FILE_TYPE_LENGTH) {								// Тип отсутствует после точки или слишком длинный?
			name[0] = 0;
			type[0] = 0;
			return FALSE;													// ДА - Завершить с ошибкой "Неверный формат имени файла"
		}
	}
	else {
		type[0] = 0;
	}

	// Проверить имя и тип на допустимые символы
	if ( ! FS_StrSymbolsValid(name) ) {										// Символы имени допустимы?
		name[0] = 0;
		type[0] = 0;
		return FALSE;														// НЕТ - Завершить с ошибкой "Неверный формат имени файла"
	}
	if ( ! FS_StrSymbolsValid(type) ) {										// Символы типа допустимы?
		name[0] = 0;
		type[0] = 0;
		return FALSE;														// НЕТ - Завершить с ошибкой "Неверный формат имени файла"
	}

	return TRUE;															// Завершить с результатом "ОК"
}


//-----------------------------------------------------------------------------
// Получить полное имя файла ( Signature1 + имя + тип + Signature2 )
//-----------------------------------------------------------------------------
void FS_GetFullName(const u8 *name, const u8 *type, u8 *full_name) {
	u8 len;
	u8 i, j;
	u8 crc;

	// Взять имя файла
	i = 1;
	j = 0;
	len = strlen((char *)name);
	while (i <= len) {
		full_name[i++] = name[j++];
	}

	// Имя файла дополнить нулями
	len = FILE_NAME_LENGTH;
	while (i <= len) {
		full_name[i++] = 0;
	}

	// Добавить тип файла
	len += strlen((char *)type);
	j = 0;
	while (i <= len) {
		full_name[i++] = type[j++];
	}

	// Тип файла дополнить нулями
	len = FILE_NAME_LENGTH + FILE_TYPE_LENGTH;
	while (i <= len) {
		full_name[i++] = 0;
	}

	// Получить CRC для типа файла
	crc = CRC8(full_name + len, 0xFF, FILE_TYPE_LENGTH);
	full_name[i] = crc;

	// Получить CRC для полного имени (имя + тип)
	crc = CRC8(full_name + len - FILE_TYPE_LENGTH, crc, FILE_NAME_LENGTH);
	if ( crc == 0x00 || crc == 0xFF ) {
		crc = 0x01;
	}
	full_name[0] = crc;
}


//-----------------------------------------------------------------------------
//             Проверить использование файла с заданным именем
//-----------------------------------------------------------------------------
// Если файл используется (открыт) - возвращается номер FCS назначенной на данный файл
// иначе - возвращается -1 
tFile FS_FileUseFCS(const u8 *name, const u8 *type) {
	u8 fcs_num;																// Указатель на FCS
	tFCS *p_fcs;
	u8 state;

	for (fcs_num = 0; fcs_num < MAX_FILES; fcs_num++) {						// Проверять все структуры FCS
		p_fcs = pFCSArray[fcs_num];											// Получить указатель на FCS

		state = p_fcs->State;
		if (state == FCS_STATE_CLOSED) {									// Структура FCS закрыта?
			continue;														// ДА - Перейти к следующеей структуре FCS
		}

		// Здесь структура FCS не закрыта
		if ( ! strcmp( (char *)name, (char *)p_fcs->Name ) &&				// Имена совпадают?
		     ! strcmp( (char *)type, (char *)p_fcs->Type ) ) {				// И типы совпадают?
			return fcs_num;													// Вернуть номер структуры FCS
		};
	}

	return -1;																// Вернуть результат "Файл не используется"
}


//-----------------------------------------------------------------------------
// Получить номер первой свободной записи в таблице FNT
//-----------------------------------------------------------------------------
// если свободных записей нет - возвращается 0xFFFFFFFF
u32 FS_FindFreeFNT(void) {
	u32 fnt_num1;															// Левый элемент при поиске = первая запись
	u32 fnt_num2;															// Правый элемент при поиске = последняя запись
	u32 fnt_num;															// Промежуточный элемент при поиске
	u32 addr;

	fnt_num1 = 0;															// Левый элемент при поиске = первая запись
	fnt_num2 = FNTRecordMAX;												// Правый элемент при поиске = последняя запись

	// Предельные случаи
	addr = FNT_BASE_ADDRESS;
	if (FLASH_ReadByte(addr) == 0xFF) {										// Первая запись свободна?
		return 0;															// ДА - Свободная запись FNT = 0
	}
	addr += FNTRecordMAX * FNT_RECORD_SIZE;
	if (FLASH_ReadByte(addr) != 0xFF) {										// Последняя запись занята?
		return 0xFFFFFFFF;													// ДА - Свободных записей FNT нет
	}

	// Дихотомический поиск по таблице FNT
	while ( (fnt_num2 - fnt_num1) > 1 ) {									// Повторять чтобы левый и правый элемент оказались рядом
		fnt_num = (fnt_num1 + fnt_num2) >> 1;
		addr = FNT_BASE_ADDRESS + fnt_num * FNT_RECORD_SIZE;
		if (FLASH_ReadByte(addr) == 0xFF) {
			fnt_num2 = fnt_num;
		}
		else {
			fnt_num1 = fnt_num;
		}
	}
	return fnt_num2;														// Свободная запись FNT = правый элемент
}


//-----------------------------------------------------------------------------
// Получить номер записи файла с заданным именем в таблице FNT
//-----------------------------------------------------------------------------
// Искать по всем записям от начала до конца таблицы FNT
// Поиск выполняется по полному имени (имя + тип)
// если файл не найден - возвращается 0xFFFFFFFF
u32 FS_FindFileByName(const u8 *full_name) {
	u32 fnt_num;
	u32 fnt_addr;
	u32 addr;
	u8 len;
	u8 i;
	u8 b;

	len = 1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH;							// Длина поиска
	fnt_addr = FNT_BASE_ADDRESS;											// Адрес первой записи FNT
	for (fnt_num = 0; fnt_num < FNTRecordsNumber; fnt_num++) {				// Проверять все записи в таблице FNT
		addr = fnt_addr;													// Адрес символа строки
		for (i=0; i<len; i++) {												// Сравнивать все байты в заданной строке
			b = FLASH_ReadByte(addr++);										// Прочитать байт из строки
			if (b != full_name[i]) {										// Символы равны?
				break;														// НЕТ - прервать сравнение строк
			}
		}
		if (i == len) {														// Имя файла найдено?
			return fnt_num;													// ДА - Вернуть номер записи FNT
		}
		fnt_addr += FNT_RECORD_SIZE;										// Адрес следующей записи FNT
	}
	return 0xFFFFFFFF;														// Результат = "Файл не найден"
}

//-----------------------------------------------------------------------------
// Найти cвободный кластер в таблице CAT
//-----------------------------------------------------------------------------
// Искать по всем записям от начала до конца таблицы CAT
// если свободных кластеров нет - возвращается 0xFFFF
u16 FS_FindFreeCluster(void) {
	u16 cat_num;
	u32 cat_addr;

	cat_addr = CAT_BASE_ADDRESS;											// Адрес первой записи CAT
	for (cat_num = 0; cat_num < CATRecordsNumber; cat_num++) {				// Проверять все записи в таблице CAT
		if (FLASH_ReadByte(cat_addr) == 0xFF) {								// Запись свободна?
			return cat_num;													// ДА - Вернуть номер записи CAT
		}
		cat_addr += CAT_RECORD_SIZE;										// Адрес следующей записи CAT
	}
	return 0xFFFF;															// Результат = "Свободная запись CAT не найдена"
}


//-----------------------------------------------------------------------------
// Получить кол-во cвободных кластеров в таблице CAT
//-----------------------------------------------------------------------------
// Искать по всем записям от начала до конца таблицы CAT
u16 FS_GetFreeClustersNum(void) {
	u16 cat_num;
	u32 cat_addr;
	u16 n = 0;

	cat_addr = CAT_BASE_ADDRESS;											// Адрес первой записи CAT
	for (cat_num = 0; cat_num < CATRecordsNumber; cat_num++) {				// Проверять все записи в таблице CAT
		if (FLASH_ReadByte(cat_addr) == 0xFF) {								// Запись свободна?
			n++;															// ДА - Считать кол-во свободных кластеров
		}
		cat_addr += CAT_RECORD_SIZE;										// Адрес следующей записи CAT
	}
	return n;																// Результат = Кол-во свободных кластеров
}


//-----------------------------------------------------------------------------
// Записать полное имя файла в запись FNT
//-----------------------------------------------------------------------------
void FS_FNTWriteFullName(u32 fnt_num, const u8 *full_name) {
	u8 len;

	len = 1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1;
	FLASH_Write( FNT_BASE_ADDRESS + fnt_num * FNT_RECORD_SIZE, full_name, len );
}


//-----------------------------------------------------------------------------
// Записать Сигнатуру1 в запись FNT
//-----------------------------------------------------------------------------
void FS_FNTSetSignature1(u32 fnt_num, u8 signature) {
	FLASH_WriteByte( FNT_BASE_ADDRESS + fnt_num * FNT_RECORD_SIZE, signature );
}


//-----------------------------------------------------------------------------
// Записать флаг кластера в таблице CAT
//-----------------------------------------------------------------------------
void FS_ClusterSetFlag(u16 clust_num, u8 flag) {
	FLASH_WriteByte( CAT_BASE_ADDRESS + clust_num * CAT_RECORD_SIZE, flag );
}


//-----------------------------------------------------------------------------
// Записать номер следующего кластера в таблице CAT
//-----------------------------------------------------------------------------
void FS_SetNextCluster(u16 clust_num_curr, u16 clust_num_next) {
	FLASH_Write( CAT_BASE_ADDRESS + clust_num_curr * CAT_RECORD_SIZE + 1, (u8 *)&clust_num_next, 2 );
}


//-----------------------------------------------------------------------------
// Прочитать номер следующего кластера в таблице CAT
//-----------------------------------------------------------------------------
u16 FS_GetNextCluster(u16 clust_num_curr) {
	u16 clust_num_next;

	FLASH_Read( (u8 *)&clust_num_next, CAT_BASE_ADDRESS + clust_num_curr * CAT_RECORD_SIZE + 1, 2 );
	return clust_num_next;
}


//-----------------------------------------------------------------------------
// Записать буфер страницы в файл
//-----------------------------------------------------------------------------
void FS_FlushPageBuffer(const tFCS *p_fcs, u16 size) {
	u32 addr;

	addr = CLUSTERS_BASE_ADDRESS +											// Адрес страницы в флэш-памяти
	       p_fcs->CurrCluster * CLUSTER_SIZE +
		   p_fcs->CurrPage * PAGE_SIZE;
 	FLASH_Write(addr, p_fcs->PageBuffer, size);								// Записать страницу флэш-памяти
}


//-----------------------------------------------------------------------------
// Получить номер свободной структуры FCS
//-----------------------------------------------------------------------------
s8 FS_GetFreeFCS() {
	u8 i;

	for (i=0; i<MAX_FILES; i++) {											// Проверить все структуры FCS
		if (pFCSArray[i]->State == FCS_STATE_CLOSED) {						// Найдена свободная (закрытая) структура FCS?
			return i;														// ДА - Вернуть номер найденной структуры FCS
		}
	}
	return -1;																// НЕТ - Вернуть ошибку "Нет свободной структуры FCS" (ошибка -1)
}




//					*	*	*	*	*	*	*	*	*




//-----------------------------------------------------------------------------
//               НАЗНАЧИТЬ ФАЙЛОВУЮ ПЕРЕМЕННУЮ ФАЙЛУ
//-----------------------------------------------------------------------------
s8 FS_Assign(const u8 *file_name,tFile * f) {
	s8 fcs_num;
	u8 name[FILE_NAME_LENGTH + 1];
	u8 type[FILE_TYPE_LENGTH + 1];

	// Проверить инициализацию файловой системы (ошибка -1)
	if (! FS_IS_INITED) {													// Файловая система инициализирована?
		return EFS_FS_NOT_INITED;															// НЕТ - Вернуть ошибку "Файловая система не инициализирована" (ошибка -1)
	}

	if (! FS_GetNameAndType(file_name, name, type)) {						// Выделение имени и типа выполнилось успешно?
		return EFS_INVALID_FILE_NAME;															// НЕТ - Вернуть ошибку "Неверный формат имени файла" (ошибка -3)
	}

	// Проверить использование файла с заданным именем
	if (FS_FileUseFCS(name, type) > -1) {									// Файл с заданным именем используется?
		return EFS_FILE_IS_USED;															// ДА - Вернуть ошибку "Файл с заданным именем используется" (ошибка -4)
	};

	// Получить номер свободной структуры FCS
	fcs_num = FS_GetFreeFCS();
	if (fcs_num < 0) {														// Свободная структура FCS найдена?
		return EFS_NO_FREE_FCS;											// НЕТ - Вернуть ошибку "Нет свободной структуры FCS" (ошибка -2)
	}

	// Заполнить занятую структуру FCS
	pFCSArray[fcs_num]->State = FCS_STATE_OPENED;							// Структура FCS = Открыта
	strcpy((char *)pFCSArray[fcs_num]->Name, (char *)name);					// Записать имя файла
	strcpy((char *)pFCSArray[fcs_num]->Type, (char *)type);					// Записать тип файла
	*f = fcs_num;
	return FS_RESULT_OK;															// Вернуть номер открытой структуры FCS
}


//-----------------------------------------------------------------------------
//                 СОЗДАТЬ НОВЫЙ ФАЙЛ ДЛЯ ЗАПИСИ
//-----------------------------------------------------------------------------
s8 FS_Rewrite(tFile fcs_num) {
	tFCS *p_fcs;															// Указатель на FCS
	u32 fnt_num;															// Номер записи в таблице FNT
	u16 clust_num;
	u8 *full_name;															// Указатель на полное имя файла
	u16 k;

	// Проверить файловую переменную (ошибка -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// Файловая переменная назначена файлу?
		return EFS_INVALID_FSC;															// НЕТ - Вернуть ошибку "Файловая переменная не назначена файлу" (ошибка -9)
	}

	p_fcs = pFCSArray[fcs_num];												// Получить указатель на FCS

	// Проверить состояние структуры FCS (ошибка -1)
	if (p_fcs->State != FCS_STATE_OPENED) {									// Структура FCS открыта?
		return EFS_FCS_NOT_OPENED;															// НЕТ - Вернуть ошибку "Структура FCS не открыта" (ошибка -1)
	}

	// Получить полное имя файла ( в форме: Signature1 + имя + тип + Signature2 )
	full_name = p_fcs->FNT.FullName;										// Указатель на полное имя файла
	FS_GetFullName(p_fcs->Name, p_fcs->Type, full_name);

	// Проверить уникальность имени (ошибка -2)
	fnt_num = FS_FindFileByName(full_name);									// Найти файл с заданным именем (включая сигнатуру)
	if (fnt_num != 0xFFFFFFFF) {											// Найден файл с заданным именем?
		return EFS_FILE_NAME_IS_EXIST;															// ДА - Вернуть ошибку "Файл с заданным именем уже существует" (ошибка -2)
	}

	// Найти свободную запись в таблице FNT (ошибка -3)
	fnt_num = FS_FindFreeFNT();
	if (fnt_num == 0xFFFFFFFF) {											// Свободная запись FNT найдена?
		return EFS_NO_FREE_FNT;															// НЕТ - Вернуть ошибку "Нет свободной записи FNT" (ошибка -3)
	}

	// Проверить наличие свободного места (ошибка -4)
	clust_num = FS_FindFreeCluster();										// Найти свободный кластер в таблице CAT
	if (clust_num == 0xFFFF) {												// Свободный кластер найден?
		return EFS_NO_FREE_SPACE;															// НЕТ - Вернуть ошибку "Недостаточно места" (ошибка -4)
	}

	// ОШИБОК НЕТ - ОТКРЫТЬ ФАЙЛ

	// Пометить занятые записи в таблицах FNT и CAT
	FS_FNTWriteFullName(fnt_num, full_name);								// Пометить запись FNT = "Занято" (записать полное имя файла)
	FS_ClusterSetFlag(clust_num, 0xFE);										// Пометить кластер в таблице CAT = "Занято"

	// Заполнить начальными значениями структуру FCS.FNT
	//p_fcs->FNT.FullName[];												...(полное имя = уже заполнено)
	p_fcs->FNT.Attribute = FILE_ATTR_NOATTR;								// Файл без атрибутов
	p_fcs->FNT.FirstCluster = clust_num;									// Первый кластер = текущий кластер
	p_fcs->FNT.Size = 0;													// Начальный размер = 0

	// Заполнить FCS
	p_fcs->State = FCS_STATE_OPENED_WRITE;									// Пометить - "Структура FCS открыта для записи файла"
	p_fcs->FNT_num = fnt_num;												// Номер записи таблицы FNT
	p_fcs->CurrCluster = clust_num;											// Номер текущего кластера
	p_fcs->CurrPage = 0;													// Номер текущей страницы в текущем кластере
	p_fcs->PageBufPtr = 0;													// Текущий указатель в буфере страницы
	//p_fcs->PageBuffer[];													...(буфер текущей страницы флэш-памяти = не определено)

//------
//<!> ДЛЯ ОТЛАДКИ !!!
//ОЧИСТИТЬ БУФЕР СТРАНИЦЫ
for (k = 0; k < PAGE_SIZE; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}
//------

	return FS_RESULT_OK;																// Файл для записи успешно открыт
}


//-----------------------------------------------------------------------------
//            ОТКРЫТЬ СУЩЕСТВУЮЩИЙ ФАЙЛ ДЛЯ ДОБАВЛЕНИЯ
//-----------------------------------------------------------------------------
s8 FS_Append(tFile fcs_num) {
	tFCS *p_fcs;															// Указатель на FCS
	u8 *full_name;															// Указатель на полное имя файла
	u32 fnt_num_old, fnt_num_new;											// Старый и новый номера записей в таблице FNT
	u32 addr;																// Адрес флэш-памяти
	u8 len;
	u32 file_size;															// Размер файла
	u16 clust_num;															// Индекс (в таблице CAT) последнего кластера
	u8 page_num;															// Номер последней страницы внутри последнего кластера
	u32 n_bytes;															// Кол-во байт в последней странице
	u16 i;
	u16 k;

	// Проверить файловую переменную (ошибка -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// Файловая переменная назначена файлу?
		return EFS_INVALID_FSC;															// НЕТ - Вернуть ошибку "Файловая переменная не назначена файлу" (ошибка -9)
	}

	p_fcs = pFCSArray[fcs_num];												// Получить указатель на FCS

	// ПЕРЕД ОТКРЫТИЕМ ФАЙЛА - ПРОВЕРИТЬ ВОЗМОЖНЫЕ ОШИБКИ

	// Проверить состояние структуры FCS (ошибка -1)
	if (p_fcs->State != FCS_STATE_OPENED) {									// Структура FCS открыта?
		return EFS_FCS_NOT_OPENED;															// НЕТ - Вернуть ошибку "Структура FCS не открыта" (ошибка -1)
	}

	// Получить полное имя файла ( в форме: Signature1 + имя + тип + Signature2 )
	full_name = p_fcs->FNT.FullName;										// Указатель на полное имя файла
	FS_GetFullName(p_fcs->Name, p_fcs->Type, full_name);

	// Поиск запрошенного файла в таблице FNT (ошибка -2)
	fnt_num_old = FS_FindFileByName(full_name);								// Найти файл с заданным именем (включая сигнатуру)
	if (fnt_num_old == 0xFFFFFFFF) {										// Найден файл с заданным именем?
		return EFS_FILE_NOT_FOUND;															// НЕТ - Вернуть ошибку "Файл с заданным именем не найден" (ошибка -2)
	}

	// Найти свободную запись в таблице FNT (ошибка -3)
	fnt_num_new = FS_FindFreeFNT();
	if (fnt_num_new == 0xFFFFFFFF) {										// Свободная запись FNT найдена?
		return EFS_NO_FREE_FNT;															// НЕТ - Вернуть ошибку "Нет свободной записи FNT" (ошибка -3)
	}

	// ОШИБОК НЕТ - ПОПЫТКА ОТКРЫТЬ ФАЙЛ

	// Заполнить начальными значениями структуру FCS.FNT

	//p_fcs->FNT.FullName[];												(полное имя = уже заполнено)

	// Копировать в FCS.FNT запись из таблицы FNT файла
	addr = FNT_BASE_ADDRESS + fnt_num_old * FNT_RECORD_SIZE;				// Адрес начала FNT открываемого файла
	len = 1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1;						// Длина полного имени
	addr += len;															// Пропустить полное имя (полное имя не копировать, оно уже заполнено)
	FLASH_Read(full_name + len, addr, FNT_RECORD_SIZE - len);				// Прочитать запись FNT кроме полного имени

	// Проверить разрешена или нет запись в файл  (ошибка -4)
	if (p_fcs->FNT.Attribute == FILE_ATTR_READONLY) {						// В файл разрешена запись?
		return EFS_WRITE_DISABLED;															// НЕТ - Вернуть ошибку "Запись в файл запрещена"  (ошибка -4)
	}

	file_size = p_fcs->FNT.Size;											// Размер файла
	page_num = ( (file_size / PAGE_SIZE) % PAGES_PER_CLUSTER );				// Номер последней страницы внутри кластера
	n_bytes = file_size % PAGE_SIZE;										// Количество байт в последней странице

	// Вычислить индекс (в таблице CAT) последнего кластера
	i = (file_size / CLUSTER_SIZE);											// Кол-во целых кластеров
	clust_num = p_fcs->FNT.FirstCluster;									// Начинаем с первого кластера цепочки
	while (i--) {															// Идти по цепочке кластеров
		clust_num = FS_GetNextCluster(clust_num);
	}

	// Пометить записи в таблице FNT
	FS_FNTSetSignature1(fnt_num_old, 0x00);									// Пометить старую запись FNT = "Удалено"
	FS_FNTWriteFullName(fnt_num_new, full_name);							// Пометить новую запись FNT = "Занято" (записать полное имя файла)

	// Заполнить FCS
	p_fcs->State = FCS_STATE_OPENED_WRITE;									// Пометить - "Структура FCS открыта для записи файла"
	p_fcs->FNT_num = fnt_num_new;											// Номер записи таблицы FNT
	p_fcs->CurrCluster = clust_num;											// Индекс (в таблице CAT) текущего кластера
	p_fcs->CurrPage = page_num;												// Номер текущей страницы в текущем кластере
	p_fcs->PageBufPtr = n_bytes;											// Текущий указатель в буфере страницы

	// Прочитать последнюю страницу в буфер страницы
	if (n_bytes) {															// Первая страница содержит данные?
		addr = CLUSTERS_BASE_ADDRESS +										// Адрес страницы в флэш-памяти
		       clust_num * CLUSTER_SIZE +
		       page_num * PAGE_SIZE;
		FLASH_Read(p_fcs->PageBuffer, addr, n_bytes);						// Прочитать страницу
	}

//------
//<!> ДЛЯ ОТЛАДКИ !!!
//ОЧИСТИТЬ ОСТАТОК БУФЕРА СТРАНИЦЫ
for (k = n_bytes; k < PAGE_SIZE; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}
//------

	return FS_RESULT_OK;																// Файл для записи успешно открыт
}


//-----------------------------------------------------------------------------
//                 ОТКРЫТЬ ФАЙЛ ДЛЯ ЧТЕНИЯ
//-----------------------------------------------------------------------------
s8 FS_Reset(tFile fcs_num) {
	tFCS *p_fcs;															// Указатель на FCS
	u8 *full_name;															// Указатель на полное имя файла
	u32 fnt_num;															// Номер записи в таблице FNT
	u8 len;
	u32 addr;																// Адрес флэш-памяти
	u32 size;
	u16 k;

	// Проверить файловую переменную (ошибка -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// Файловая переменная назначена файлу?
		return EFS_INVALID_FSC;															// НЕТ - Вернуть ошибку "Файловая переменная не назначена файлу" (ошибка -9)
	}

	p_fcs = pFCSArray[fcs_num];												// Получить указатель на FCS

	// ПЕРЕД ОТКРЫТИЕМ ФАЙЛА - ПРОВЕРИТЬ ВОЗМОЖНЫЕ ОШИБКИ

	// Проверить состояние структуры FCS (ошибка -1)
	if (p_fcs->State != FCS_STATE_OPENED) {									// Структура FCS открыта?
		return EFS_FCS_NOT_OPENED;															// НЕТ - Вернуть ошибку "Структура FCS не открыта" (ошибка -1)
	}

	// Получить полное имя файла ( в форме: Signature1 + имя + тип + Signature2 )
	full_name = p_fcs->FNT.FullName;										// Указатель на полное имя файла
	FS_GetFullName(p_fcs->Name, p_fcs->Type, full_name);

	// Поиск запрошенного файла в таблице FNT (ошибка -2)
	fnt_num = FS_FindFileByName(full_name);									// Найти файл с заданным именем (включая сигнатуру)
	if (fnt_num == 0xFFFFFFFF) {											// Найден файл с заданным именем?
		return EFS_FILE_NOT_FOUND;															// НЕТ - Вернуть ошибку "Файл с заданным именем не найден" (ошибка -2)
	}

	// ОШИБОК НЕТ - ОТКРЫТЬ ФАЙЛ

	// Заполнить начальными значениями структуру FCS.FNT
	//p_fcs->FNT.FullName[];												...(полное имя = уже заполнено)

	// Копировать в FCS.FNT запись из таблицы FNT
	addr = FNT_BASE_ADDRESS + fnt_num * FNT_RECORD_SIZE;					// Адрес начала FNT открываемого файла

	len = 1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1;						// Длина полного имени
	addr += len;															// Пропустить полное имя (полное имя не копировать, оно уже заполнено)
	FLASH_Read(full_name + len, addr, FNT_RECORD_SIZE - len);				// Прочитать запись FNT (кроме полного имени)

	// Заполнить FCS
	p_fcs->State = FCS_STATE_OPENED_READ;									// Пометить - "Структура FCS открыта для чтения файла"
	p_fcs->FNT_num = fnt_num;												// Номер записи таблицы FNT
	p_fcs->CurrCluster = p_fcs->FNT.FirstCluster;							// Индекс (в таблице CAT) текущего кластера
	p_fcs->CurrPage = 0;													// Номер текущей страницы в текущем кластере
	p_fcs->PageBufPtr = 0;													// Текущий указатель в буфере страницы

	size = p_fcs->FNT.Size;													// Взять размер файла
	p_fcs->RemainSize = size;												// Осталось не прочитано байт

	if (size > PAGE_SIZE) {													// Вычислить количество байт в первой странице
		size = PAGE_SIZE;
	}

	// Прочитать первую страницу в буфер страницы
	if (size) {																// Первая страница содержит данные?
		addr = CLUSTERS_BASE_ADDRESS +										// Адрес страницы в флэш-памяти
		       p_fcs->CurrCluster * CLUSTER_SIZE;							// (здесь номер страницы = 0)
		FLASH_Read(p_fcs->PageBuffer, addr, size);							// Прочитать страницу
	}

//------
//<!> ДЛЯ ОТЛАДКИ !!!
//ОЧИСТИТЬ ОСТАТОК БУФЕРА СТРАНИЦЫ
for (k = size; k < PAGE_SIZE; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}
//------

	p_fcs->MinFilePosition = 0;												// Мин. позиция файла в текущей странице
	if (size == PAGE_SIZE) {												// Макс. позиция файла в текущей странице
		p_fcs->MaxFilePosition = PAGE_SIZE-1;
	}
	else {
		// здесь size < PAGE_SIZE
		p_fcs->MaxFilePosition = size;
	}

	return FS_RESULT_OK;																// Файл для чтения успешно открыт
}


//-----------------------------------------------------------------------------
//                     ЗАПИСАТЬ БАЙТ В ОТКРЫТЫЙ ФАЙЛ
//-----------------------------------------------------------------------------
s8 FS_WriteByte(tFile fcs_num, u8 data) {
	tFCS *p_fcs;															// Указатель на FCS
	u16 page_buf_ptr;														// Указатель в буфере страницы
	u8 curr_page;															// Номер текущей страницы в текущем кластере
	u16 clust_num_next;
	s8 result;																// Результат записи байта
	u16 k;

	// Проверить файловую переменную (ошибка -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// Файловая переменная назначена файлу?
		return EFS_INVALID_FSC;															// НЕТ - Вернуть ошибку "Файловая переменная не назначена файлу" (ошибка -9)
	}

	p_fcs = pFCSArray[fcs_num];												// Получить указатель на FCS

	// ПЕРЕД ЗАПИСЬЮ - ПРОВЕРИТЬ ВОЗМОЖНЫЕ ОШИБКИ

	// Проверить состояние структуры FCS (ошибка -1)
	if (p_fcs->State != FCS_STATE_OPENED_WRITE) {							// Структура FCS открыта для записи файла?
		return EFS_FCS_NOT_OPENED_WRITE;															// НЕТ - Вернуть ошибку "Структура FCS не открыта для записи файла" (ошибка -1)
	}

	// ОШИБОК НЕТ - ЗАПИСАТЬ БАЙТ

	p_fcs->FNT.Size++;														// Увеличить размер файла
	page_buf_ptr = p_fcs->PageBufPtr;										// Взять текущий указатель в буфере страницы
	p_fcs->PageBuffer[page_buf_ptr++] = data;								// Записать байт данных в буфер страницы

	result = FS_RESULT_OK;																// Предварительный результат "Байт успешно записан"
	if (page_buf_ptr == PAGE_SIZE) {										// Буфер страницы заполнился?
		page_buf_ptr = 0;													// ДА - Сбросить текущий указатель в буфере страницы
		FS_FlushPageBuffer(p_fcs, PAGE_SIZE);								// Записать буфер страницы в файл

//------
//<!> ДЛЯ ОТЛАДКИ !!!
//ОЧИСТИТЬ БУФЕР СТРАНИЦЫ
for (k = 0; k < PAGE_SIZE; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}
//------
		curr_page = p_fcs->CurrPage + 1;									// Увеличить номер текущей страницы
		if (curr_page == PAGES_PER_CLUSTER) {								// Кластер заполнился?
			curr_page = 0;													// ДА - Обнулить номер текущей страницы

			// Проверить наличие свободного места (ошибка -2)
			clust_num_next = FS_FindFreeCluster();							// Найти свободный кластер в таблице CAT
			if (clust_num_next == 0xFFFF) {									// Свободный кластер найден?
				result = EFS_NO_FREE_SPACE;												// НЕТ - Результат "Недостаточно места для последующей записи" (ошибка -2)
			}
			else {
				FS_SetNextCluster(p_fcs->CurrCluster, clust_num_next);		// Записать указатель на следующий кластер в таблице CAT
				FS_ClusterSetFlag(clust_num_next, 0xFE);					// Пометить новый кластер в таблице CAT = "Занято"
				p_fcs->CurrCluster = clust_num_next;						// Изменить номер текущего кластера
			}
		}
		p_fcs->CurrPage = curr_page;										// Сохранить номер текущей страницы
	}
	p_fcs->PageBufPtr = page_buf_ptr;										// Обновить текущий указатель в буфере страницы


	return result;															// Результат записи байта
}


//-----------------------------------------------------------------------------
//                    ПРОЧИТАТЬ БАЙТ ИЗ ОТКРЫТОГО ФАЙЛА
//-----------------------------------------------------------------------------
s8 FS_ReadByte(tFile fcs_num, u8 *data) {
	tFCS *p_fcs;															// Указатель на FCS
	u16 page_buf_ptr;														// Указатель в буфере страницы
	u8 *page_buffer;
	u16 page_size;															// Размер буфера страницы
	u32 remain_size;														// Оставшийся объем данных в файле
	u8  curr_page;															// Номер текущей страницы в текущем кластере
	u16 clust_num;
	u32 addr;
	u16 k;

	// Проверить файловую переменную (ошибка -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// Файловая переменная назначена файлу?
		return EFS_INVALID_FSC;															// НЕТ - Вернуть ошибку "Файловая переменная не назначена файлу" (ошибка -9)
	}

	p_fcs = pFCSArray[fcs_num];												// Получить указатель на FCS

	// Проверить состояние структуры FCS (ошибка -1)
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							// Структура FCS открыта для чтения файла?
		return EFS_FCS_NOT_OPENED_READ;															// НЕТ - Вернуть ошибку "Структура FCS не открыта для чтения файла" (ошибка -1)
	}

	remain_size = p_fcs->RemainSize;

	// Проверить кол-во непрочитанных байт (ошибка -2)
	if (! remain_size) {													// Имеются непрочитанные байты?
		return EFS_NO_DATA;															// НЕТ - Вернуть ошибку "Файл пуст" (ошибка -2)
	}

	// ЗДЕСЬ ИМЕЮТСЯ ДАННЫЕ ДЛЯ ЧТЕНИЯ

	p_fcs->RemainSize = --remain_size;										// Уменьшить кол-во непрочитанных байт

	page_buf_ptr = p_fcs->PageBufPtr;										// Взять текущий указатель в буфере страницы
	page_buffer = p_fcs->PageBuffer;										// Взять указатель на буфер страницы

	// Взять байт данных из буфера страницы
	// и передвинуть указатель в буфере страницы
	*data = page_buffer[page_buf_ptr++];

	if (page_buf_ptr == PAGE_SIZE) {										// Буфер страницы полностью прочитан?
		page_buf_ptr = 0;													// ДА - Обнулить текущий указатель в буфере страницы
		clust_num = p_fcs->CurrCluster;										// Взять индекс (в таблице CAT) текущего кластера
		curr_page = p_fcs->CurrPage + 1;									// Увеличить номер текущей страницы
		if (curr_page == PAGES_PER_CLUSTER) {								// Кластер полностью прочитан?
			curr_page = 0;													// ДА - Обнулить номер текущей страницы
			clust_num = FS_GetNextCluster(clust_num);						// Следующий кластер в цепочке в таблице CAT
			p_fcs->CurrCluster = clust_num;									// Изменить номер текущего кластера
		}
		p_fcs->CurrPage = curr_page;										// Изменить номер текущей страницы

		// Получить размер следующей сраницы файла
		if (remain_size > PAGE_SIZE) {
			page_size = PAGE_SIZE;
		}
		else {
			page_size = remain_size;
		}

		// Прочитать следующую страницу файла в буфер
		if (page_size) {
			addr = CLUSTERS_BASE_ADDRESS +									// Адрес страницы в флэш-памяти
			       clust_num * CLUSTER_SIZE +
				   curr_page * PAGE_SIZE;
			FLASH_Read(page_buffer, addr, page_size);						// Прочитать страницу
		}

//------
//<!> ДЛЯ ОТЛАДКИ !!!
//ОЧИСТИТЬ ОСТАТОК БУФЕРА СТРАНИЦЫ
for (k = page_size; k < PAGE_SIZE; k++) {
	page_buffer[k] = 0xFF;
}
//------

		// Изменить диапазон позиции файла в текущей странице
		p_fcs->MinFilePosition += PAGE_SIZE;								// Мин. позиция файла в текущей странице
		if (page_size == PAGE_SIZE) {										// Макс. позиция файла в текущей странице
			p_fcs->MaxFilePosition += PAGE_SIZE;
		}
		else {
			// здесь page_size < PAGE_SIZE
			p_fcs->MaxFilePosition += page_size + 1;
		}
	}
	p_fcs->PageBufPtr = page_buf_ptr;										// Обновить текущий указатель в буфере страницы

	return FS_RESULT_OK;																// Байт успешно прочитан
}


//<!> ФУНКЦИЯ НЕ ДОДЕЛАНА !!!
//-----------------------------------------------------------------------------
//			ЗАПИСАТЬ БУФЕР В ОТКРЫТЫЙ ФАЙЛ
//-----------------------------------------------------------------------------
s32 FS_Write(tFile fcs_num, const u8 *buffer, u32 size) {
	tFCS *p_fcs;															// Указатель на FCS
	u8 *page_buffer;
	u16 page_buf_ptr;														// Указатель в буфере страницы
	u16 remain_page;														// Размер остатка буфера страницы
	u16 first_size;															// Размер первой страницы
	u16 last_size;															// Размер последней страницы
	u32 full_page_count;													// Кол-во целых страниц
	u8  curr_page;															// Номер текущей страницы в текущем кластере
	u16 clust_num_next;															// Номер текущего кластера
//	u32 addr;
	u16 k;

	// Проверить файловую переменную (ошибка -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// Файловая переменная назначена файлу?
		return -9;															// НЕТ - Вернуть ошибку "Файловая переменная не назначена файлу" (ошибка -9)
	}

	p_fcs = pFCSArray[fcs_num];												// Получить указатель на FCS

	// ПЕРЕД ЗАПИСЬЮ - ПРОВЕРИТЬ ВОЗМОЖНЫЕ ОШИБКИ

	// Проверить состояние структуры FCS (ошибка -1)
	if (p_fcs->State != FCS_STATE_OPENED_WRITE) {							// Структура FCS открыта для записи файла?
		return -1;															// НЕТ - Вернуть ошибку "Структура FCS не открыта для записи файла" (ошибка -1)
	}

	// ОШИБОК НЕТ - ЗАПИСАТЬ БУФЕР

	page_buffer = p_fcs->PageBuffer;										// Взять указатель на буфер страницы
	page_buf_ptr = p_fcs->PageBufPtr;										// Взять текущий указатель в буфере страницы

	// Получить размер первой страницы
	remain_page = PAGE_SIZE - page_buf_ptr;									// Получить размер остатка в буфере страницы
	if (size < remain_page) {
		first_size = size;													// Весь размер запишется в остаток буфера страницы
		full_page_count = 0;												// Кол-во целых страниц = 0
	}
	if (size == remain_page) {
		first_size = remain_page;											// Остаток буфера страницы полностью запишется
		full_page_count = 1;												// Кол-во целых страниц = 1
		last_size = 0;														// Размер последней страницы = 0
	}
	if (size > remain_page) {
		first_size = remain_page;											// Остаток буфера страницы полностью запишется
		full_page_count = (size - remain_page) / PAGE_SIZE + 1;				// Кол-во целых страниц
		last_size = (size - remain_page) % PAGE_SIZE;						// Размер последней страницы
	}

	// Записать первую страницу
	if (first_size) {														// Имеются байты для записи?
		memcpy(page_buffer + page_buf_ptr, buffer, first_size);				// ДА - Записать в буфер страницы
	}
	else {
		return 0;															// НЕТ - Результат = "Записано 0 байт"
	}

	// Проверить заполнился ли буфер страницы?
	if (! full_page_count) {												// Буфер страницы не заполнился?
		p_fcs->PageBufPtr += first_size;									// ДА - Обновить текущий указатель в буфере страницы
		return size;														// Результат = "Записано size байт"
	}
	// Здесь завершено без записи буфера страницы в файл

	// Здесь буфер страницы заполнен
	FS_FlushPageBuffer(p_fcs, PAGE_SIZE);									// Записать буфер страницы в файл
	full_page_count--;



	if (last_size) {
	}



//******************
		if (page_buf_ptr == PAGE_SIZE) {										// Буфер страницы заполнился?
			page_buf_ptr = 0;													// ДА - Сбросить текущий указатель в буфере страницы
			FS_FlushPageBuffer(p_fcs, PAGE_SIZE);								// Записать буфер страницы в файл
	
	//------
	//<!> ДЛЯ ОТЛАДКИ !!!
	//ОЧИСТИТЬ БУФЕР СТРАНИЦЫ
	for (k = 0; k < PAGE_SIZE; k++) {
		p_fcs->PageBuffer[k] = 0xFF;
	}
	//------
			curr_page = p_fcs->CurrPage + 1;									// Увеличить номер текущей страницы
			if (curr_page == PAGES_PER_CLUSTER) {								// Кластер заполнился?
				curr_page = 0;													// ДА - Обнулить номер текущей страницы
	
				// Проверить наличие свободного места (ошибка -2)
				clust_num_next = FS_FindFreeCluster();							// Найти свободный кластер в таблице CAT
				if (clust_num_next == 0xFFFF) {									// Свободный кластер найден?
//					result = -2;												// НЕТ - Результат "Недостаточно места для последующей записи" (ошибка -2)
				}
				else {
					FS_SetNextCluster(p_fcs->CurrCluster, clust_num_next);		// Записать указатель на следующий кластер в таблице CAT
					FS_ClusterSetFlag(clust_num_next, 0xFE);					// Пометить новый кластер в таблице CAT = "Занято"
					p_fcs->CurrCluster = clust_num_next;						// Изменить номер текущего кластера
				}
			}
			p_fcs->CurrPage = curr_page;										// Сохранить номер текущей страницы
		}
		p_fcs->PageBufPtr = page_buf_ptr;										// Обновить текущий указатель в буфере страницы








	return 0; // (фиктивный вовзврат)
}


//<!> ФУНКЦИЯ НЕ ДОДЕЛАНА !!!
//-----------------------------------------------------------------------------
//			ПРОЧИТАТЬ БУФЕР ИЗ ОТКРЫТОГО ФАЙЛА
//-----------------------------------------------------------------------------
s32 FS_Read(tFile fcs_num, u8 *buffer, u32 size) {
	tFCS *p_fcs;															// Указатель на FCS
	u8 *page_buffer;
	u16 page_buf_ptr;														// Указатель в буфере страницы
	u16 first_size;															// Размер первой страницы
	u16 last_size;															// Размер последней страницы
	u32 full_page_count;													// Кол-во целых страниц
	u32 remain_size;														// Оставшийся размер файла
	u8  curr_page;															// Номер текущей страницы в текущем кластере
	u16 clust_num;
	u32 addr;

	// Проверить файловую переменную (ошибка -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// Файловая переменная назначена файлу?
		return -9;															// НЕТ - Вернуть ошибку "Файловая переменная не назначена файлу" (ошибка -9)
	}

	p_fcs = pFCSArray[fcs_num];												// Получить указатель на FCS

	// Проверить состояние структуры FCS (ошибка -1)
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							// Структура FCS открыта для чтения файла?
		return -1;															// НЕТ - Вернуть ошибку "Структура FCS не открыта для чтения файла" (ошибка -1)
	}

	// ОШИБОК НЕТ - ПРОЧИТАТЬ БУФЕР

	remain_size = p_fcs->RemainSize;										// Оставшийся объем данных в файле

	// Проверить - Конец файла или нет?
	if (! remain_size) {													// Имеются непрочитанные байты файла?
		return 0;															// НЕТ - Вернуть результат "Прочитано 0 байт"
	}

	if (! size) {															// Запрашиваемый объем > 0?
		return 0;															// НЕТ - Вернуть результат "Прочитано 0 байт"
	}

	// Скорректировать запрашиваемый объем данных
	// (ограничить запрашиваемый объем до остатка файла)
	if (size > remain_size) {
		size = remain_size;
	}

	page_buffer = p_fcs->PageBuffer;										// Взять указатель на буфер страницы
	page_buf_ptr = p_fcs->PageBufPtr;										// Взять текущий указатель в буфере страницы

	// Получить размер первой страницы
	first_size = PAGE_SIZE - page_buf_ptr;									// Получить размер остатка в буфере страницы
	if (first_size >= size) {
		first_size = size;													// Весь запрашиваемый размер содержится в буфере страницы
		full_page_count = 0;												// Кол-во целых страниц = 0
		last_size = 0;														// Размер последней страницы = 0
	}
	else {
		full_page_count = (size - first_size) / PAGE_SIZE;					// Кол-во целых страниц
		last_size = (size - first_size) % PAGE_SIZE;						// Размер последней страницы
	}

	// Прочитать первую страницу
	// (первая страница всегда есть и находится в буфере страницы)
	memcpy(buffer, page_buffer + page_buf_ptr, first_size);					// Скопировать блок из буфера страницы
	page_buf_ptr += first_size;												// Передвинуть указатель в буфере страницы
	remain_size -= first_size;												// Скорректировать оставшийся размер файла

	clust_num = p_fcs->CurrCluster;											// Взять индекс (в таблице CAT) текущего кластера
	curr_page = p_fcs->CurrPage;											// Взять номер текущей страницы

	// Прочитать целые страницы
	if (full_page_count) {
		buffer += first_size;												// Передвинуть позицию входного буфера
	}
	while (full_page_count--) {
		// Загрузить следующую страницу файла
		curr_page++;														// Увеличить номер текущей страницы
		if (curr_page == PAGES_PER_CLUSTER) {								// Кластер полностью прочитан?
			curr_page = 0;													// ДА - Обнулить номер текущей страницы
			clust_num = FS_GetNextCluster(clust_num);						// Следующий кластер в цепочке в таблице CAT
//			p_fcs->CurrCluster = clust_num;									// Изменить номер текущего кластера
		}
//		p_fcs->CurrPage = curr_page;										// Изменить номер текущей страницы
//		page_buf_ptr = 0;													// Обнулить текущий указатель в буфере страницы

		// Прочитать следующую страницу файла в приемный буфер
		addr = CLUSTERS_BASE_ADDRESS +										// Адрес страницы в флэш-памяти
		       clust_num * CLUSTER_SIZE +
			   curr_page * PAGE_SIZE;
		FLASH_Read(buffer, addr, PAGE_SIZE);								// Прочитать страницу сразу в приемный буфер

		remain_size -= PAGE_SIZE;											// Скорректировать оставшийся размер файла
		buffer += PAGE_SIZE;												// Передвинуть позицию входного буфера
	}

	// Прочитать последнюю страницу
	if (last_size) {
		clust_num = p_fcs->CurrCluster;										// Взять индекс (в таблице CAT) текущего кластера
		curr_page = p_fcs->CurrPage;										// Взять номер текущей страницы
	}








	p_fcs->CurrCluster = clust_num;											// Изменить номер текущего кластера
	p_fcs->CurrPage = curr_page;											// Изменить номер текущей страницы




	// Изменить диапазон позиции файла в текущей странице
	p_fcs->MinFilePosition += PAGE_SIZE;									// Мин. позиция файла в текущей странице
	p_fcs->MaxFilePosition += PAGE_SIZE;									// Макс. позиция файла в текущей странице


	return 0; // (фиктивный вовзврат)
}


//<!> ФУНКЦИЯ НЕ ДОДЕЛАНА !!!
//-----------------------------------------------------------------------------
//			ЗАПИСАТЬ СТРОКУ В ОТКРЫТЫЙ ФАЙЛ
//-----------------------------------------------------------------------------
s32 FS_WriteLn(tFile fcs_num, const u8 *str) {

	// Проверить файловую переменную (ошибка -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// Файловая переменная назначена файлу?
		return -9;															// НЕТ - Вернуть ошибку "Файловая переменная не назначена файлу" (ошибка -9)
	}

	return 0; // (фиктивный вовзврат)
}


//-----------------------------------------------------------------------------
//			ПРОЧИТАТЬ СТРОКУ ИЗ ОТКРЫТОГО ФАЙЛА В ПРЯМОМ НАПРАВЛЕНИИ
//-----------------------------------------------------------------------------
s8 FS_ReadLn(tFile fcs_num, u8 *str, u32 max_size) {
	tFCS *p_fcs;															// Указатель на FCS
	u8 *page_buffer;
	u16 page_buf_ptr;														// Указатель в буфере страницы
	u16 page_size;															// Размер буфера страницы
	u32 remain_size;														// Оставшийся объем данных в файле
	u8  curr_page;															// Номер текущей страницы в текущем кластере
	u16 clust_num;
	u32 addr;
	u8 s;																	// Символ прочитанный из файла
	u32 i;																	// Индекс символа в строке
	u16 k;
	s8 result;

	// Проверить файловую переменную (ошибка -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// Файловая переменная назначена файлу?
		return -9;															// НЕТ - Вернуть ошибку "Файловая переменная не назначена файлу" (ошибка -9)
	}

	p_fcs = pFCSArray[fcs_num];												// Получить указатель на FCS

	// Проверить состояние структуры FCS (ошибка -1)
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							// Структура FCS открыта для чтения файла?
		return -1;															// НЕТ - Вернуть ошибку "Структура FCS не открыта для чтения файла" (ошибка -1)
	}

	// ОШИБОК НЕТ - ПРОЧИТАТЬ СТРОКУ

	remain_size = p_fcs->RemainSize;										// Оставшийся объем данных в файле

	// Проверить - Конец файла или нет?
	if (! remain_size) {													// Имеются непрочитанные байты файла?
		str[0] = 0;															// НЕТ - Вернуть пустую строку
		return -2;															// Вернуть ошибку "Файл пуст" (ошибка -2)
	}

	page_buffer = p_fcs->PageBuffer;										// Взять указатель на буфер страницы
	page_buf_ptr = p_fcs->PageBufPtr;										// Взять текущий указатель в буфере страницы

	page_size = PAGE_SIZE - page_buf_ptr;									// Получить размер остатка в буфере сраницы
	if (page_size > remain_size) {
		page_size = remain_size;
	}

	// Начало чтения строки
	i = 0;																	// Встать в начало строки
	do {
		// Цикл чтения строки из буфера страницы
		while (page_size) {
			s = page_buffer[page_buf_ptr++];								// Взять следующий символ из буфера страницы
			remain_size--;													// Оставшийся объем данных в файле
			if (s == 10) {													// Игнорировать символ #10
				page_size--;												// Оставшийся размер страницы
				continue;
			}
			if (s == 13) {													// Встретился символ #13 ?
				str[i] = 0;													// Завершить прочитанную строку нулевым символом
				result = 0;													// Результат = Строка успешно прочитана
				break;														// Строка прочитана, завершить цикл чтения строки
			}
			if (s == 0) {													// Встретился нулевой байт?
				str[i] = 0;													// ДА - Завершить прочитанную строку нулевым символом
				result = -3;												// Результат = Ошибка: "Нулевой байт" (ошибка -3)
				break;														// Завершить цикл чтения строки
			}
			// Здесь "хороший" символ
			if (i < max_size) {
				str[i++] = s;												// Положить очередной символ в буфер строки
			}
			else {
				str[i] = 0;													// Завершить прочитанную строку нулевым символом
				// Превышено максимальное кол-во прочитанных символов
				page_buf_ptr--;												// Откатить указатель в буфере страницы
				remain_size++;												// Откатить оставшийся объем данных в файле
				result = -4;												// Результат = Ошибка: "Превышена максимальная длина строки" (ошибка -4)
				break;														// Завершить цикл чтения строки
			}
			// (если выходим из цикла по break, то page_size не обнулится)
			page_size--;													// Оставшийся размер страницы
		}
		// Проверить причину завершения цикла чтения строки
		if (page_size) {													// Цикл завершился по break ?
			p_fcs->RemainSize = remain_size;								// ДА - Сохранить оставшийся объем данных в файле
			p_fcs->PageBufPtr = page_buf_ptr;								// Сохранить текущий указатель в буфере страницы
			return result;													// Завершить - Вернуть результат чтения строки
		}
		// Буфер страницы закончился, а строка все еще не прочитана

		// Проверить - Конец файла или нет?
		if (! remain_size) {												// Имеются еще непрочитанные байты файла?
			str[i] = 0;														// НЕТ - Завершить строку
			p_fcs->RemainSize = 0;											// Сохранить оставшийся объем данных в файле
			p_fcs->PageBufPtr = page_buf_ptr;								// Сохранить текущий указатель в буфере страницы
			return 0;														// Результат = Строка успешно прочитана
		}

		// Не конец файла - загрузить следующую страницу файла
		clust_num = p_fcs->CurrCluster;										// Взять индекс (в таблице CAT) текущего кластера
		curr_page = p_fcs->CurrPage + 1;									// Увеличить номер текущей страницы
		if (curr_page == PAGES_PER_CLUSTER) {								// Кластер полностью прочитан?
			curr_page = 0;													// ДА - Обнулить номер текущей страницы
			clust_num = FS_GetNextCluster(clust_num);						// Следующий кластер в цепочке в таблице CAT
			p_fcs->CurrCluster = clust_num;									// Изменить номер текущего кластера
		}
		p_fcs->CurrPage = curr_page;										// Изменить номер текущей страницы
		page_buf_ptr = 0;													// Обнулить текущий указатель в буфере страницы

		// Получить размер следующей сраницы файла
		if (remain_size < PAGE_SIZE) {
			page_size = remain_size;
		}
		else {
			page_size = PAGE_SIZE;
		}

		// Прочитать следующую страницу файла в буфер страницы
		addr = CLUSTERS_BASE_ADDRESS +										// Адрес страницы в флэш-памяти
		       clust_num * CLUSTER_SIZE +
			   curr_page * PAGE_SIZE;
		FLASH_Read(page_buffer, addr, page_size);							// Прочитать страницу

//------
//<!> ДЛЯ ОТЛАДКИ !!!
//ОЧИСТИТЬ ОСТАТОК БУФЕРА СТРАНИЦЫ
for (k = page_size; k < PAGE_SIZE; k++) {
	page_buffer[k] = 0xFF;
}
//------

		// Изменить диапазон позиции файла в текущей странице
		p_fcs->MinFilePosition += PAGE_SIZE;								// Мин. позиция файла в текущей странице
		p_fcs->MaxFilePosition += page_size;								// Макс. позиция файла в текущей странице

	} while (1);
	// Цикл do... while завершится выходом return внутри цикла
}


//<!> ФУНКЦИЯ НЕ ДОДЕЛАНА !!!
//-----------------------------------------------------------------------------
//			ПРОЧИТАТЬ СТРОКУ ИЗ ОТКРЫТОГО ФАЙЛА В ОБРАТНОМ НАПРАВЛЕНИИ
//-----------------------------------------------------------------------------
s8 FS_ReadPrevLn(tFile fcs_num, u8 *str, u32 max_size) {

	// Проверить файловую переменную (ошибка -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// Файловая переменная назначена файлу?
		return -9;															// НЕТ - Вернуть ошибку "Файловая переменная не назначена файлу" (ошибка -9)
	}

	return 0; // (фиктивный вовзврат)
}


//-----------------------------------------------------------------------------
//       КОЛИЧЕСТВО НЕПРОЧИТАННЫХ БАЙТ В ОТКРЫТОМ ДЛЯ ЧТЕНИЯ ФАЙЛЕ
//-----------------------------------------------------------------------------
s32 FS_RemainSize(tFile fcs_num) {
	tFCS *p_fcs;															// Указатель на FCS

	// Проверить файловую переменную (ошибка -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// Файловая переменная назначена файлу?
		return -9;															// НЕТ - Вернуть ошибку "Файловая переменная не назначена файлу" (ошибка -9)
	}

	p_fcs = pFCSArray[fcs_num];												// Получить указатель на FCS

	// Проверить состояние структуры FCS (ошибка -1)
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							// Структура FCS открыта для чтения файла?
		return -1;															// НЕТ - Вернуть ошибку "Структура FCS не открыта для чтения файла" (ошибка -1)
	}

	return p_fcs->RemainSize;												// Вернуть кол-во непрочитанных байт
}


//-----------------------------------------------------------------------------
//         ПЕРЕЙТИ В ЗАДАННУЮ ПОЗИЦИЮ В ОТКРЫТОМ ДЛЯ ЧТЕНИЯ ФАЙЛЕ
//-----------------------------------------------------------------------------
// Выполняется "абсолютный" переход по файлу
s8 FS_Seek(tFile fcs_num, u32 position) {
	tFCS *p_fcs;															// Указатель на FCS
	u16 clusters_num;
	u16 clust_num;
	u8  page_num;
	u8  old_page_ptr, new_page_ptr;
	u32 size;
	u32 addr;
	u16 i;
	u16 k;

	// Проверить файловую переменную (ошибка -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// Файловая переменная назначена файлу?
		return EFS_INVALID_FSC;															// НЕТ - Вернуть ошибку "Файловая переменная не назначена файлу" (ошибка -9)
	}

	p_fcs = pFCSArray[fcs_num];												// Получить указатель на FCS

	// Проверить состояние структуры FCS (ошибка -1)
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							// Структура FCS открыта для чтения файла?
		return EFS_FCS_NOT_OPENED_READ;															// НЕТ - Вернуть ошибку "Структура FCS не открыта для чтения файла" (ошибка -1)
	}

	// Проверить заданную позицию (ошибка -2)
	if (position > p_fcs->FNT.Size) {										// Позиция в пределах размера файла?
		return EFS_INVALID_POSITION;															// НЕТ - Вернуть ошибку "Заданная позиция не существует" (ошибка -2)
	}

	// ДАЛЕЕ КОД АНАЛОГИЧЕН ФУНКЦИИ FS_RSeek()

	page_num = position % CLUSTER_SIZE / PAGE_SIZE;							// Номер текущей страницы в текущем кластере
	new_page_ptr = position % PAGE_SIZE;									// Позиция в текущей странице

	// Проверить меняется ли страница
	if (position >= p_fcs->MinFilePosition && position <= p_fcs->MaxFilePosition) {
		// Здесь страница не меняется - изменить только текущий указатель в буфере страницы и оставшийся размер
		old_page_ptr = p_fcs->PageBufPtr;
		p_fcs->PageBufPtr = new_page_ptr;
		p_fcs->RemainSize -= new_page_ptr - old_page_ptr;
		return FS_RESULT_OK;														// OK - Завершить
	}

	// Здесь страница меняется

	// Пройти по цепочке кластеров от первого до текущего кластера файла
	clusters_num = position / CLUSTER_SIZE;									// Порядковый номер текущего кластера в цепочке
	clust_num = p_fcs->FNT.FirstCluster;									// Индекс (в таблице CAT) первого кластер цепочки
	for (i = 0; i < clusters_num; i++) {									// Получить индекс (в таблице CAT) текущего кластера
		clust_num = FS_GetNextCluster(clust_num);
	}

	// Изменить некоторые поля FCS
	p_fcs->CurrCluster = clust_num;											// Изменить номер текущего кластера
	p_fcs->CurrPage = page_num;												// Изменить номер текущей страницы в текущем кластере
	p_fcs->PageBufPtr = new_page_ptr;										// Изменить текущий указатель в буфере страницы

	size = p_fcs->FNT.Size - position;										// Осталось не прочитано байт
	p_fcs->RemainSize = size;

	// Вычислить количество байт в текущей странице
	size += new_page_ptr;													// Размер от начала текущей страницы до конца файла
	if (size >= PAGE_SIZE) {												// Размер больше чем страница?
		size = PAGE_SIZE;													// ДА - Уменьшить до размера страницы
	}

	// Прочитать страницу в буфер FCS.Buffer[]
	addr = CLUSTERS_BASE_ADDRESS +											// Адрес страницы в флэш-памяти
	       clust_num * CLUSTER_SIZE +
		   page_num * PAGE_SIZE;
	FLASH_Read(p_fcs->PageBuffer, addr, size);								// Прочитать страницу

//------
//<!> ДЛЯ ОТЛАДКИ !!!
//ОЧИСТИТЬ ОСТАТОК БУФЕРА СТРАНИЦЫ
for (k = size; k < PAGE_SIZE; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}
//------

	p_fcs->MinFilePosition = (position / PAGE_SIZE) * PAGE_SIZE;			// Мин. позиция файла в текущей странице
	p_fcs->MaxFilePosition = p_fcs->MinFilePosition + size-1;				// Макс. позиция файла в текущей странице

	return FS_RESULT_OK;																// OK - Завершить
}


//-----------------------------------------------------------------------------
//         СМЕСТИТЬ ТЕКУЩУЮ ПОЗИЦИЮ В ОТКРЫТОМ ДЛЯ ЧТЕНИЯ ФАЙЛЕ
//-----------------------------------------------------------------------------
// Выполняется "относительный" переход по файлу
// При смещении "назад" если позиция не существует, встать в позицию 0
// При смещении "вперед" если позиция не существует, встать в позицию Size
s8 FS_RSeek(tFile fcs_num, s32 disp) {
	tFCS *p_fcs;															// Указатель на FCS
	s32 position;
	u16 clusters_num;
	u16 clust_num;
	u8  page_num;
	u8  old_page_ptr, new_page_ptr;
	u32 size;
	u32 addr;
	u16 i;
	u16 k;

	// Проверить файловую переменную (ошибка -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// Файловая переменная назначена файлу?
		return EFS_INVALID_FSC;															// НЕТ - Вернуть ошибку "Файловая переменная не назначена файлу" (ошибка -9)
	}

	p_fcs = pFCSArray[fcs_num];												// Получить указатель на FCS

	// Проверить состояние структуры FCS (ошибка -1)
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							// Структура FCS открыта для чтения файла?
		return EFS_FCS_NOT_OPENED_READ;															// НЕТ - Вернуть ошибку "Структура FCS не открыта для чтения файла" (ошибка -1)
	}

	size = p_fcs->FNT.Size;													// Размер файла

	position = size - p_fcs->RemainSize + disp;								// Получить новую позицию
	// здесь p_fcs->FNT.Size - p_fcs->RemainSize - текущая позиция

	// Скорректировать позицию за пределами файла
	if (position < 0) {
		position = 0;
	}
	if (position > size) {
		position = size;
	}

	// ДАЛЕЕ КОД АНАЛОГИЧЕН ФУНКЦИИ FS_Seek()

	page_num = position % CLUSTER_SIZE / PAGE_SIZE;							// Номер текущей страницы в текущем кластере
	new_page_ptr = position % PAGE_SIZE;									// Позиция в текущей странице

	// Проверить меняется ли страница
	if (position >= p_fcs->MinFilePosition && position <= p_fcs->MaxFilePosition) {
		// Здесь страница не меняется - изменить только текущий указатель в буфере страницы и оставшийся размер
		old_page_ptr = p_fcs->PageBufPtr;
		p_fcs->PageBufPtr = new_page_ptr;
		p_fcs->RemainSize -= new_page_ptr - old_page_ptr;
		return FS_RESULT_OK;														// OK - Завершить
	}

	// Здесь страница меняется

	// Пройти по цепочке кластеров от первого до текущего кластера файла
	clusters_num = position / CLUSTER_SIZE;									// Порядковый номер текущего кластера в цепочке
	clust_num = p_fcs->FNT.FirstCluster;									// Индекс (в таблице CAT) первого кластер цепочки
	for (i = 0; i < clusters_num; i++) {									// Получить индекс (в таблице CAT) текущего кластера
		clust_num = FS_GetNextCluster(clust_num);
	}

	// Изменить некоторые поля FCS
	p_fcs->CurrCluster = clust_num;											// Изменить номер текущего кластера
	p_fcs->CurrPage = page_num;												// Изменить номер текущей страницы в текущем кластере
	p_fcs->PageBufPtr = new_page_ptr;										// Изменить текущий указатель в буфере страницы

	size = p_fcs->FNT.Size - position;										// Осталось не прочитано байт
	p_fcs->RemainSize = size;

	// Вычислить количество байт в текущей странице
	size += new_page_ptr;													// Размер от начала текущей страницы до конца файла
	if (size >= PAGE_SIZE) {												// Размер больше чем страница?
		size = PAGE_SIZE;													// ДА - Уменьшить до размера страницы
	}

	// Прочитать страницу в буфер FCS.Buffer[]
	addr = CLUSTERS_BASE_ADDRESS +											// Адрес страницы в флэш-памяти
	       clust_num * CLUSTER_SIZE +
		   page_num * PAGE_SIZE;
	FLASH_Read(p_fcs->PageBuffer, addr, size);								// Прочитать страницу

//------
//<!> ДЛЯ ОТЛАДКИ !!!
//ОЧИСТИТЬ ОСТАТОК БУФЕРА СТРАНИЦЫ
for (k = size; k < PAGE_SIZE; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}
//------

	p_fcs->MinFilePosition = (position / PAGE_SIZE) * PAGE_SIZE;			// Мин. позиция файла в текущей странице
	p_fcs->MaxFilePosition = p_fcs->MinFilePosition + size-1;				// Макс. позиция файла в текущей странице

	return FS_RESULT_OK;																// OK - Завершить
}


//-----------------------------------------------------------------------------
//                            ЗАКРЫТЬ ФАЙЛ
//-----------------------------------------------------------------------------
s8 FS_Close(tFile *fcs_num) {
	tFCS *p_fcs;															// Указатель на FCS
	u8 state;
	u32 flash_addr;
	u8 *addr;
	u8 size;

	// Проверить файловую переменную (ошибка -9)
	if (*fcs_num < 0 || *fcs_num >= MAX_FILES) {							// Файловая переменная назначена файлу?
		return EFS_INVALID_FSC;															// НЕТ - Вернуть ошибку "Файловая переменная не назначена файлу" (ошибка -9)
	}

	p_fcs = pFCSArray[*fcs_num];											// Получить указатель на FCS

	// ПЕРЕД ЗАКРЫТИЕМ ФАЙЛА - ПРОВЕРИТЬ ВОЗМОЖНЫЕ ОШИБКИ

	state = p_fcs->State;													// Взять состояние структуры FCS

	// Проверить состояние структуры FCS (ошибка -1)
	if (state == FCS_STATE_CLOSED) {										// Структура FCS открыта?
		return EFS_FILE_IS_CLOSED;															// НЕТ - Вернуть ошибку "Структура FCS не открыта" (ошибка -1)
	}

	// Структура FCS просто открыта или Файл открыт для чтения ?
	if (state == FCS_STATE_OPENED || state == FCS_STATE_OPENED_READ) {
		p_fcs->State = FCS_STATE_CLOSED;									// Пометить = "Структура FCS закрыта"
		*fcs_num = -1;														// Отвязать файловую переменную от структуры FCS
		return FS_RESULT_OK;															// ОК - Файл успешно закрыт
	}

	// Файл открыт для записи ?
	if (state == FCS_STATE_OPENED_WRITE) {
		if (p_fcs->PageBufPtr) {											// Буфер страницы не пустой?
			FS_FlushPageBuffer(p_fcs, p_fcs->PageBufPtr);					// ДА - Записать буфер страницы в файл
		}
		// Переписать структуру FCS.FNT в запись FNT текущего файла
		flash_addr = FNT_BASE_ADDRESS +										// Адрес FNT текущего файла
		       p_fcs->FNT_num * FNT_RECORD_SIZE +							// (пропустить полное имя файла)
			   1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1;
		addr = p_fcs->FNT.FullName +										// Указатель на структуру FCS.FNT
			   1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1;					// (пропустить полное имя файла)
		size = sizeof(tFNT) -
		       1 - FILE_NAME_LENGTH - FILE_TYPE_LENGTH - 1;
		FLASH_Write(flash_addr, addr, size);								// Переписать полностью запись FNT

		p_fcs->State = FCS_STATE_CLOSED;									// Пометить = "Структура FCS закрыта"
		*fcs_num = -1;														// Отвязать файловую переменную от структуры FCS
		return FS_RESULT_OK;															// ОК - Файл успешно закрыт
	}
	else {
		return EFS_UNKNOWN_FILE_STATE;															// Вернуть ошибку "Неизвестное состояние структуры FCS" (ошибка -2)
	}
}


//-----------------------------------------------------------------------------
//                            УДАЛИТЬ ФАЙЛ
//-----------------------------------------------------------------------------
s8 FS_Delete(const u8 *file_name) {
	u8 name[FILE_NAME_LENGTH + 1];
	u8 type[FILE_TYPE_LENGTH + 1];
	u8 full_name[1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1];
	u32 fnt_num;
	u32 fnt_addr;
	u32 addr;
	u16 clust_num;

	// Проверить инициализацию файловой системы (ошибка -1)
	if (! FS_IS_INITED) {													// Файловая система инициализирована?
		return EFS_FS_NOT_INITED;															// НЕТ - Вернуть ошибку "Файловая система не инициализирована" (ошибка -1)
	}

	if (! FS_GetNameAndType(file_name, name, type)) {						// Выделение имени и типа выполнилось успешно?
		return EFS_INVALID_FILE_NAME;															// НЕТ - Вернуть ошибку "Неверный формат имени файла" (ошибка -3)
	}

	// Проверить использование файла с заданным именем
	if (FS_FileUseFCS(name, type) > -1) {									// Файл с заданным именем используется?
		return EFS_FILE_IS_USED;															// ДА - Вернуть ошибку "Файл с заданным именем используется" (ошибка -4)
	};

	// Получить полное имя файла ( в форме: Signature1 + имя + тип + Signature2 )
	FS_GetFullName(name, type, full_name);

	// Поиск запрошенного файла в таблице FNT
	fnt_num = FS_FindFileByName(full_name);									// Найти файл с заданным именем (включая сигнатуру)
	if (fnt_num == 0xFFFFFFFF) {											// Найден файл с заданным именем?
		return EFS_FILE_NOT_FOUND;															// НЕТ - Вернуть ошибку "Файл с заданным именем не найден" (ошибка -2)
	}

	// ОШИБОК НЕТ - УДАЛИТЬ ФАЙЛ

	fnt_addr = FNT_BASE_ADDRESS + fnt_num * FNT_RECORD_SIZE;				// Адрес FNT удаляемого файла

	addr = fnt_addr + 1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1 + 1;		// Адрес поля FNT.FirstCluster
	FLASH_Read((u8 *)&clust_num, addr, 2);									// Прочитать индекс (в таблице CAT) первого кластера файла

	// УДАЛИТЬ КЛАСТЕРА в таблице CAT
	// Пройти по цепочке кластеров от первого до последнего кластера файла
	while (clust_num != 0xFFFF) {
		FS_ClusterSetFlag(clust_num, 0x00);									// Пометить кластер в таблице CAT = "Удалено"
		clust_num = FS_GetNextCluster(clust_num);							// Получить индекс (в таблице CAT) следующего кластера в цепочке
	}

	// УДАЛИТЬ запись FNT
	FLASH_WriteByte(fnt_addr, 0x00);										// Пометить запись FNT = "Удалено" (Signature1 = 0x00)

	return FS_RESULT_OK;																// ОК - Файл успешно удален
}


//-----------------------------------------------------------------------------
//                      ПОЛУЧИТЬ ИНФОРМАЦИЮ О ФАЙЛЕ
//-----------------------------------------------------------------------------
// Если очередной файл не найден - возвращается 0xFFFFFFFF
s8 FS_GetFileInfo(u32 * fnt_num, u8 *name, u8 *type, u8 *attr, u32 *size, tFile *f) {
	tFCS *p_fcs;															// Указатель на FCS
	u32 addr;
	__packed union {
		u8 array[FNT_RECORD_SIZE];											// Представление fnt как массива
		tFNT strc;															// Представление fnt как структуры
	} fnt;
	u8 b;
	u8 i,k;

	// Искать по всем записям от стартовой записи до конца таблицы FNT
	addr = FNT_BASE_ADDRESS + *fnt_num * FNT_RECORD_SIZE;					// Адрес стартовой записи FNT
	while (*fnt_num < FNTRecordsNumber) {
		b = FLASH_ReadByte(addr);											// Прочитать Сигнатуру1
		if (b == 0xFF) {													// Найдена свободная запись FNT?
			name[0] = 0;													// ДА - Прекратить поиск файла
			type[0] = 0;													//   и вернуть "пустую" информацию
			*attr = 0xFF;
			*size = 0;
			*f = -1;
			*fnt_num = 0xFFFFFFFF;
			return EFS_FILE_INFO_NOT_FOUND;									// Завершить с результатом "Очередной файл не найден"
		}
		if (b > 0x00) {														// Файл найден?
			break;															// ДА - Прервать поиск файла
		}
		addr += FNT_RECORD_SIZE;											// Адрес следующей записи FNT
		(*fnt_num)++;															// Номер следующей записи FNT
	}

	if ((*fnt_num) >= FNTRecordsNumber) {										// Файл найден?
			name[0] = 0;													// НЕТ - Вернуть "пустую" информацию
			type[0] = 0;
			*attr = 0xFF;
			*size = 0;
			*f = -1;
			(*fnt_num) = 0xFFFFFFFF;
			return EFS_FILE_INFO_NOT_FOUND;									// Завершить с результатом "Очередной файл не найден"
	}

	// ОЧЕРЕДНОЙ ФАЙЛ НАЙДЕН
	
	// Копировать запись FNT найденного файла
	FLASH_Read(fnt.array, addr, sizeof(tFNT));								// Прочитать запись FNT

	// Прочитать имя файла
	for (i = 0, k = 1; i < FILE_NAME_LENGTH; i++, k++) {
		b = fnt.strc.FullName[k];
		name[i] = b;
		if (! b) {
			break;
		}
	}
	if (i == FILE_NAME_LENGTH) {
		name[FILE_NAME_LENGTH] = 0;
	}

	// Прочитать тип файла
	for (i = 0, k = 1 + FILE_NAME_LENGTH; i < FILE_TYPE_LENGTH; i++, k++) {
		b = fnt.strc.FullName[k];
		type[i] = b;
		if (! b) {
			break;
		}
	}
	if (i == FILE_TYPE_LENGTH) {
		type[FILE_TYPE_LENGTH] = 0;
	}

	*f = FS_FileUseFCS(name, type);											// Проверить использование файла с заданным именем

	// Найденный файл используется
	if (*f > -1) {															// Файл с заданным именем используется?
		// Взять информацию о файле из соответствующей структуры FCS
		p_fcs = pFCSArray[*f];												// Получить указатель на FCS
		*attr = p_fcs->FNT.Attribute;
		*size = p_fcs->FNT.Size;
	}
	// Найденный файл не используется
	else {
		// Взять информацию о файле из записи FNT
		*attr = fnt.strc.Attribute;
		*size = fnt.strc.Size;
	}

	return FS_RESULT_OK;															// ОК - Информация о файле успешно получена
}


//-----------------------------------------------------------------------------
//			ПРОВЕРИТЬ КОНЕЦ ОТКРЫТОГО ДЛЯ ЧТЕНИЯ ФАЙЛА
//-----------------------------------------------------------------------------
s8 FS_Eof(tFile fcs_num) {
	tFCS *p_fcs;															// Указатель на FCS

	// Проверить файловую переменную (ошибка -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// Файловая переменная назначена файлу?
		return EFS_INVALID_FSC;															// НЕТ - Вернуть ошибку "Файловая переменная не назначена файлу" (ошибка -9)
	}

	p_fcs = pFCSArray[fcs_num];												// Получить указатель на FCS

	// Проверить состояние структуры FCS (ошибка -1)
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							// Структура FCS открыта для чтения файла?
		return EFS_FCS_NOT_OPENED_READ;															// НЕТ - Вернуть ошибку "Структура FCS не открыта для чтения файла" (ошибка -1)
	}

	// Проверить кол-во непрочитанных байт и вернуть результат
	if (p_fcs->RemainSize) {
		return FS_NOT_EOF;
	}
	else {
		return FS_EOF;
	}
}


//-----------------------------------------------------------------------------
//			ПОЛУЧИТЬ ТЕКУЩУЮ ПОЗИЦИЮ ОТКРЫТОГО ДЛЯ ЧТЕНИЯ ФАЙЛА
//-----------------------------------------------------------------------------
s8 FS_Pos(tFile fcs_num,s32 * pos) {
	tFCS *p_fcs;															// Указатель на FCS

	// Проверить файловую переменную (ошибка -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// Файловая переменная назначена файлу?
		return EFS_INVALID_FSC;															// НЕТ - Вернуть ошибку "Файловая переменная не назначена файлу" (ошибка -9)
	}

	p_fcs = pFCSArray[fcs_num];												// Получить указатель на FCS

	// Проверить состояние структуры FCS (ошибка -1)
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							// Структура FCS открыта для чтения файла?
		return EFS_FCS_NOT_OPENED_READ;															// НЕТ - Вернуть ошибку "Структура FCS не открыта для чтения файла" (ошибка -1)
	}

	// Взять кол-во непрочитанных байт и вернуть результат
	*pos = (p_fcs->FNT.Size - p_fcs->RemainSize);
	return FS_RESULT_OK;
}












//-----------------------------------------
// ТЕСТ <!>
//-----------------------------------------

// <!>
// получить состояние структуры FCS
u8 FS_GetFCSState(u8 fcs_num) {

	return pFCSArray[fcs_num]->State;
}

// <!>
// отобразить структуру FCS
void FS_FCS_Show( u8 fcs_num, void page_buf_view(u8 *buffer, u32 addr) ) {
	tFCS *p_fcs;															// Указатель на FCS
	u8 *name_buf;
	char ch;
	u8 i;

	p_fcs = pFCSArray[fcs_num];												// Получить указатель на FCS

	Msg(" - FCS %d:\r\n", fcs_num);
	Msg("   -------------------------\r\n", fcs_num);
	SMsg();
	Msg("   State: %d", p_fcs->State);
	SMsg();
	switch (p_fcs->State) {
		case FCS_STATE_CLOSED: {
			Msg(" (FCS_STATE_CLOSED)\r\n");
			SMsg();
			break;
		}
		case FCS_STATE_OPENED: {
			Msg(" (FCS_STATE_OPENED)\r\n");
			SMsg();
			break;
		}
		case FCS_STATE_OPENED_READ: {
			Msg(" (FCS_STATE_OPENED_READ)\r\n");
			SMsg();
			break;
		}
		case FCS_STATE_OPENED_WRITE: {
			Msg(" (FCS_STATE_OPENED_WRITE)\r\n");
			SMsg();
			break;
		}
	}
	Msg("   Name: \"%s\"\r\n", p_fcs->Name);
	SMsg();
	Msg("   Type: \"%s\"\r\n", p_fcs->Type);
	SMsg();
	Msg("   FNT_num: %d\r\n", p_fcs->FNT_num);
	SMsg();
	Msg("   CurrCluster: %d\r\n", p_fcs->CurrCluster);
	Msg("   CurrPage: %d\r\n", p_fcs->CurrPage);
	SMsg();
	Msg("   PageBufPtr: %d\r\n", p_fcs->PageBufPtr);
	Msg("   RemainSize: %d\r\n", p_fcs->RemainSize);
	SMsg();
	Msg("   MinFilePosition: %d\r\n", p_fcs->MinFilePosition);
	SMsg();
	Msg("   MaxFilePosition: %d\r\n", p_fcs->MaxFilePosition);
	SMsg();
	Msg("   PAGE_BUFFER:\r\n");
	page_buf_view(p_fcs->PageBuffer, 0);
	SMsg();
	Msg("   FNT:\r\n");
	Msg("   FNT.FullName: ");
	name_buf = p_fcs->FNT.FullName;
	for (i=0; i < 1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1; i++) {
		Msg(" %02X", name_buf[i]);
	}
	SMsg();
	Msg(" | ");
	for (i=0; i < 1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1; i++) {
		ch = name_buf[i];
		if (ch < 32) ch = '.';
		Msg("%c", ch);
	}
	Msg("\r\n");
	SMsg();
	Msg("   FNT.Attribute: 0x%02X\r\n", p_fcs->FNT.Attribute);
	SMsg();
	Msg("   FNT.FirstCluster: %d (0x%04X)\r\n", p_fcs->FNT.FirstCluster, p_fcs->FNT.FirstCluster);
	SMsg();
	Msg("   FNT.Size: %d\r\n", p_fcs->FNT.Size);
	Msg("   -------------------------\r\n", fcs_num);
	SMsg();
}

// <!>
// отобразить параметры файловой системы
void FS_Params_Show(void) {
	Msg("MAX_FILES = %d\r\n", MAX_FILES);
	SMsg();
	Msg("BANKS_NUM = %d\r\n", FLASH_BANKS_NUM);
	SMsg();
	Msg("SECTORS_PER_BANK = %d\r\n", FLASH_SECTORS_PER_BANK);
	SMsg();
	Msg("PAGES_PER_SECTOR = %d\r\n", FLASH_PAGES_PER_SECTOR);
	SMsg();
	Msg("PAGE_SIZE = %d\r\n", PAGE_SIZE);
	SMsg();
	Msg("PAGES_PER_CLUSTER = %d\r\n", PAGES_PER_CLUSTER);
	SMsg();
	Msg("FILE_NAME_LENGTH = %d\r\n", FILE_NAME_LENGTH);
	SMsg();
	Msg("FILE_TYPE_LENGTH = %d\r\n", FILE_TYPE_LENGTH);
	SMsg();
	Msg("FNT_RECORD_SIZE = %d\r\n", FNT_RECORD_SIZE);
	SMsg();
	Msg("CAT_RECORD_SIZE = %d\r\n", CAT_RECORD_SIZE);
	Msg("\r\n");
	SMsg();
	Msg("SECTORS_NUMBER = %d\r\n", SECTORS_NUMBER);
	SMsg();
	Msg("SECTOR_SIZE = %d\r\n", SECTOR_SIZE);
	SMsg();
	Msg("CLUSTERS_PER_SECTOR = %d\r\n", CLUSTERS_PER_SECTOR);
	SMsg();
	Msg("CLUSTERS_NUMBER = %d\r\n", CLUSTERS_NUMBER);
	SMsg();
	Msg("ClusterMAX = %d\r\n", ClusterMAX);
	SMsg();
	Msg("CLUSTER_SIZE = %d\r\n", CLUSTER_SIZE);
	SMsg();
	Msg("CAT_Size = %d\r\n", CAT_Size);
	SMsg();
	Msg("CATRecordsNumber = %d\r\n", CATRecordsNumber);
	SMsg();
	Msg("CATRecordMAX = %d\r\n", CATRecordMAX);
	SMsg();
	Msg("FNTRecordsNumber = %d\r\n", FNTRecordsNumber);
	SMsg();
	Msg("FNTRecordMAX = %d\r\n", FNTRecordMAX);
	Msg("\r\n");
	SMsg();
	Msg("FNT_BASE_ADDRESS = %d\r\n", FNT_BASE_ADDRESS);
	SMsg();
	Msg("CAT_BASE_ADDRESS = %d\r\n", CAT_BASE_ADDRESS);
	SMsg();
	Msg("CLUSTERS_BASE_ADDRESS = %d\r\n", CLUSTERS_BASE_ADDRESS);
	SMsg();
}
//-----------------------------------------
// ТЕСТ <!>
//-----------------------------------------






//=============================================================================
//
//                               End Of File
//
//=============================================================================

