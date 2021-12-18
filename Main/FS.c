//=============================================================================
//
//                            �������� �������
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

// ����� FLASH-������
#define FLASH_ADDRESS(a) (a)


#define MAX_FILES  8														// ����. ���-�� �������� ������

//#define FLASH_BANKS_NUM  1													// ���-�� ������ FLASH-������

// ��������� FLASH-������
#define FLASH_SECTORS_PER_BANK  64											// ���-�� �������� � ����� FLASH
#define FLASH_PAGES_PER_SECTOR  1024										// ���-�� ������� � �������
#define PAGE_SIZE  256														// ������ �������� (����)

// ��������� �������� �������
#define PAGES_PER_CLUSTER  64												// ���-�� ������� � ��������
#define FNT_BASE_ADDRESS  32												// ������� ����� ������� FNT

#define FNT_RECORD_SIZE  32													// ������ ������ ������� FNT
#define CAT_RECORD_SIZE  3													// ������ ������ ������� CAT

#define FILE_NAME_LENGTH  14												// ����� ����� �����
#define FILE_TYPE_LENGTH  3													// ����� ���� �����

u8 FLASH_BANKS_NUM=0;

//=============================================================================
//                              �����������
//=============================================================================

// ��������� �������� �������
enum constFSState {
	FS_STATE_FLASH_CLEAR	= 0xFF,											// ������ FLASH (�� �����������)
//	������					= 0xFE,											//
	FS_STATE_READY			= 0xFC,											// �� ������ � ������
//	������					= 0xF8,											//
//	������					= 0xF0,											//
//	������					= 0xE0,											//
//	������					= 0xC0,											//
//	������					= 0x80,											//
//	������					= 0x00,											//
};

/*
// ��� �������� �����
enum constAssignType {
	ASSIGN_TYPE_REWRITE,													// ������� ���� ��� ������
	ASSIGN_TYPE_APPEND,														// ������� ���� ��� ����������
	ASSIGN_TYPE_RESET														// ������� ���� ��� ������
};
*/

// ��������� ��������� FCS
enum constFCSState {
	FCS_STATE_CLOSED,														// ��������� FCS �������
	FCS_STATE_OPENED,														// ��������� FCS �������
	FCS_STATE_OPENED_READ,													// ��������� FCS ������� ��� ������ �����
	FCS_STATE_OPENED_WRITE													// ��������� FCS ������� ��� ������ �����
};


// �������� �����
enum constFileAttr {
	FILE_ATTR_NOATTR   = 0xFF,												// ���� �� ����� ���������
	FILE_ATTR_READONLY = 0xFE,												// ���� "������ ��� ������"
	FILE_ATTR_HIDDEN   = 0xFD,												// ���� "�������"
	FILE_ATTR_SYSTEM   = 0xFB,												// ���� "���������"
//	FILE_ATTR_reserved   = 0xF7,												// (���������������)
};


// ��������� ������ ������� FNT (File Name Table)
typedef __packed struct {
	u8  FullName[1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1];				// ���������1 + ��� + ��� + ���������2
	u8  Attribute;															// �������� �����
	u16 FirstCluster;														// ������ (� ������� CAT) ������� �������� �����
	u32 Size;																// ������ ����� (���-�� ����)
	// reserved
} tFNT;


// ��������� ������ ������� CAT (Cluster Allocation Table)
typedef __packed struct {
	u8  Flag;
	u16 NextCluster;
} tCAT;


// FCS (File Control Structure) - ��������� ���������� ������
typedef __packed struct {
	u8  State;																// ��������� �����
	u8  Name[FILE_NAME_LENGTH + 1];											// ��� �����
	u8  Type[FILE_TYPE_LENGTH + 1];											// ��� �����
	u32 FNT_num;															// ����� ������ ������� FNT
	u16 CurrCluster;														// ������ (� ������� CAT) �������� ��������
	u8  CurrPage;															// ����� ������� �������� � ������� ��������
	u16 PageBufPtr;															// ������� ��������� � ������ PageBuffer[]
	u8  PageBuffer[PAGE_SIZE];												// ����� ������� ��������
	u32 RemainSize;															// ���������� (�������������) ������
	u32 MinFilePosition;													// ���. ������� ����� � ������� ��������
	u32 MaxFilePosition;													// ����. ������� ����� � ������� ��������
	tFNT FNT;																// ����� ������ ������� FNT ��������� �����
} tFCS;


// ������ ���������� �� ��������� FCS
tFCS  *pFCSArray[MAX_FILES];

// ������ �������� FCS
tFCS  FCSArray[MAX_FILES];


// ��������� ������� �������� ������� (������ FLASH � ��������� ������� ��)
enum constFS_PARAM {
/*u8*/  FS_PARAM_FS_STATE = FLASH_ADDRESS(0),									// ��������� ��
};


//=============================================================================
//                          ���������� ����������
//=============================================================================

//u8  FS_IS_INITED = FALSE;														// ���� ������������� �������� �������
u8  FS_IS_INITED;														// ���� ������������� �������� �������

u8  FS_STATE;																	// ��������� ��

//������� ��������� �������� �������
//(����������� � ������ ������)
u16 SECTORS_NUMBER;																// ���-�� ��������
u32 SECTOR_SIZE;																// ������ �������

u16 CLUSTERS_PER_SECTOR;														// ���-�� ��������� � �������
u16 CLUSTERS_NUMBER;															// ���-�� ���������
u16 ClusterMAX;																	// ����� ������������� ��������
u16 CLUSTER_SIZE;																// ������ �������� (����)

u32 CAT_Size;																	// ������ ��������� ��� ���������� ������� CAT
u16 CATRecordsNumber;															// ���-�� ������� � ������� CAT
u16 CATRecordMAX;																// ����� ������������ ������ � ������� CAT

u32 FNTRecordsNumber;															// ���-�� ������� � ������� FNT
u32 FNTRecordMAX;																// ����� ������������ ������ � ������� FNT

u32 CAT_BASE_ADDRESS;															// ������� ����� ������� CAT
u32 CLUSTERS_BASE_ADDRESS;														// ������� ����� ������� ���������


//=============================================================================
//                   ��������� ������� �������� �������
//=============================================================================

//-----------------------------------------------------------------------------
//              FS Init
//-----------------------------------------------------------------------------
s8 FS_Init(void) {
	u8 i;
//-	���������� ����------------------------------------
	u8 bank_num;
	u8 ID;

	FLASH_BANKS_NUM = 0;
	FS_IS_INITED = 0;															// �������� ���-�� ������ FLASH-������

	// �������� ������� ������
	for (bank_num = 0; bank_num < 4; bank_num++) {
		//	��� ������� FLASH_GetBankID ?????????? 
		ID = FLASH_GetBankID(bank_num);
//		Msg("B %d ID %X\r\n",bank_num,ID);
		if (ID == 0x18) {							// ���� ID = 18h (��� ����-������ M25P128)
			FLASH_BANKS_NUM++;													// �� - ��������� ���-�� ������
		}
//		if (FLASH_GetBankID(bank_num) == 0x18) {							// ���� ID = 18h (��� ����-������ M25P128)
//			FLASH_BANKS_NUM++;													// �� - ��������� ���-�� ������
//		}
		else {
			break;															// ��� - ��������� ����� ������
		}
	}
//	Msg("FBN %d\r\n",FLASH_BANKS_NUM);
	if (! FLASH_BANKS_NUM) {														// ���������� ����� ����-������?
		return EFS_FLASH_NOT_INITED;														// ��� - ������� ���������: "����-������ �� ����������������"
	}
//----����� ���--------------------------------------
// 	res = FLASH_Init();
//	if (res < 0) {
//  	// � res ��� ������
//	}	 
	// ��������� ��������� ��
	FS_STATE = FLASH_ReadByte(FS_PARAM_FS_STATE);

	// ���� "������ FLASH"
	if (FS_STATE == FS_STATE_FLASH_CLEAR) {

		// ���������� ��������� �� = "�� ������ � ������"
		//---------------------------------------------------------------
		FS_STATE = FS_STATE_READY;
		FLASH_WriteByte(FS_PARAM_FS_STATE, FS_STATE);
	}
	// ���� "�� ������ � ������"
	else if (FS_STATE == FS_STATE_READY) {

	}

	// ��������� ������� ��������� ��
	//---------------------------------------------------------------
	SECTORS_NUMBER = FLASH_BANKS_NUM * FLASH_SECTORS_PER_BANK;						// ���-�� ��������
	SECTOR_SIZE = FLASH_PAGES_PER_SECTOR * PAGE_SIZE;								// ������ �������

	CLUSTERS_PER_SECTOR = FLASH_PAGES_PER_SECTOR / PAGES_PER_CLUSTER;				// ���-�� ��������� � �������
	CLUSTERS_NUMBER = (SECTORS_NUMBER - 3) * CLUSTERS_PER_SECTOR;					// ���-�� ���������
	CLUSTER_SIZE = PAGES_PER_CLUSTER * PAGE_SIZE;									// ������ ��������

	// ������ ��������� ��� ���������� ������� CAT
	CAT_Size = CLUSTERS_NUMBER * CAT_RECORD_SIZE / FNT_RECORD_SIZE * FNT_RECORD_SIZE;
	if ( (CLUSTERS_NUMBER * CAT_RECORD_SIZE) % FNT_RECORD_SIZE ) {
		CAT_Size += FNT_RECORD_SIZE;												// (��������� � ��'����� �������)
	}
	CATRecordsNumber = CLUSTERS_NUMBER;												// ���-�� ������� � ������� CAT

	FNTRecordsNumber = ( (SECTOR_SIZE - CAT_Size) / FNT_RECORD_SIZE ) - 1;			// ���-�� ������� � ������� FNT

	CAT_BASE_ADDRESS = FNT_BASE_ADDRESS +
					   FNTRecordsNumber * FNT_RECORD_SIZE;							// ������� ����� ������� CAT
	CLUSTERS_BASE_ADDRESS = SECTOR_SIZE * 3;										// ������� ����� ������� ���������

	ClusterMAX   = CLUSTERS_NUMBER  - 1;											// ����� ������������� ��������
	CATRecordMAX = CATRecordsNumber - 1;											// ����� ������������ ������ � ������� CAT
	FNTRecordMAX = FNTRecordsNumber - 1;											// ����� ������������ ������ � ������� FNT

	// ��������� ������ ���������� �� ��������� FCS
	for (i=0; i<MAX_FILES; i++) {
		pFCSArray[i] = FCSArray + i;
	}

	// ��������� ���� �������� FCS = "�������"
	for (i=0; i<MAX_FILES; i++) {
		pFCSArray[i]->State = FCS_STATE_CLOSED ;
	}
// ������� ����� ������
//	return 0;

	FS_IS_INITED = 1;															// �������� ������� ����������������

	return FS_RESULT_OK;// 0
}


//-----------------------------------------------------------------------------
// ��������� ������ �� ���������� �������
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
// �������� �� ����� ����� �������� ��� � ���
//-----------------------------------------------------------------------------
// � ������ ������ - ������������ ������ ������
bool FS_GetNameAndType(const u8 *file_name, u8 *name, u8 *type) {
	u8 i, k;
	u8 s;

	// �������� ���
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
	if (k == 0 || k > FILE_NAME_LENGTH) {									// ��� ����������� ��� ������� �������?
		name[0] = 0;
		type[0] = 0;
		return FALSE;														// �� - ��������� � ������� "�������� ������ ����� �����"
	}

	// �������� ���
	if (s == '.') {
		for (i++, k = 0; k <= FILE_TYPE_LENGTH; i++, k++) {
			s = file_name[i];
			type[k] = s;
			if (!s) {
				break;
			}
		}
		if (k == 0 || k > FILE_TYPE_LENGTH) {								// ��� ����������� ����� ����� ��� ������� �������?
			name[0] = 0;
			type[0] = 0;
			return FALSE;													// �� - ��������� � ������� "�������� ������ ����� �����"
		}
	}
	else {
		type[0] = 0;
	}

	// ��������� ��� � ��� �� ���������� �������
	if ( ! FS_StrSymbolsValid(name) ) {										// ������� ����� ���������?
		name[0] = 0;
		type[0] = 0;
		return FALSE;														// ��� - ��������� � ������� "�������� ������ ����� �����"
	}
	if ( ! FS_StrSymbolsValid(type) ) {										// ������� ���� ���������?
		name[0] = 0;
		type[0] = 0;
		return FALSE;														// ��� - ��������� � ������� "�������� ������ ����� �����"
	}

	return TRUE;															// ��������� � ����������� "��"
}


//-----------------------------------------------------------------------------
// �������� ������ ��� ����� ( Signature1 + ��� + ��� + Signature2 )
//-----------------------------------------------------------------------------
void FS_GetFullName(const u8 *name, const u8 *type, u8 *full_name) {
	u8 len;
	u8 i, j;
	u8 crc;

	// ����� ��� �����
	i = 1;
	j = 0;
	len = strlen((char *)name);
	while (i <= len) {
		full_name[i++] = name[j++];
	}

	// ��� ����� ��������� ������
	len = FILE_NAME_LENGTH;
	while (i <= len) {
		full_name[i++] = 0;
	}

	// �������� ��� �����
	len += strlen((char *)type);
	j = 0;
	while (i <= len) {
		full_name[i++] = type[j++];
	}

	// ��� ����� ��������� ������
	len = FILE_NAME_LENGTH + FILE_TYPE_LENGTH;
	while (i <= len) {
		full_name[i++] = 0;
	}

	// �������� CRC ��� ���� �����
	crc = CRC8(full_name + len, 0xFF, FILE_TYPE_LENGTH);
	full_name[i] = crc;

	// �������� CRC ��� ������� ����� (��� + ���)
	crc = CRC8(full_name + len - FILE_TYPE_LENGTH, crc, FILE_NAME_LENGTH);
	if ( crc == 0x00 || crc == 0xFF ) {
		crc = 0x01;
	}
	full_name[0] = crc;
}


//-----------------------------------------------------------------------------
//             ��������� ������������� ����� � �������� ������
//-----------------------------------------------------------------------------
// ���� ���� ������������ (������) - ������������ ����� FCS ����������� �� ������ ����
// ����� - ������������ -1 
tFile FS_FileUseFCS(const u8 *name, const u8 *type) {
	u8 fcs_num;																// ��������� �� FCS
	tFCS *p_fcs;
	u8 state;

	for (fcs_num = 0; fcs_num < MAX_FILES; fcs_num++) {						// ��������� ��� ��������� FCS
		p_fcs = pFCSArray[fcs_num];											// �������� ��������� �� FCS

		state = p_fcs->State;
		if (state == FCS_STATE_CLOSED) {									// ��������� FCS �������?
			continue;														// �� - ������� � ���������� ��������� FCS
		}

		// ����� ��������� FCS �� �������
		if ( ! strcmp( (char *)name, (char *)p_fcs->Name ) &&				// ����� ���������?
		     ! strcmp( (char *)type, (char *)p_fcs->Type ) ) {				// � ���� ���������?
			return fcs_num;													// ������� ����� ��������� FCS
		};
	}

	return -1;																// ������� ��������� "���� �� ������������"
}


//-----------------------------------------------------------------------------
// �������� ����� ������ ��������� ������ � ������� FNT
//-----------------------------------------------------------------------------
// ���� ��������� ������� ��� - ������������ 0xFFFFFFFF
u32 FS_FindFreeFNT(void) {
	u32 fnt_num1;															// ����� ������� ��� ������ = ������ ������
	u32 fnt_num2;															// ������ ������� ��� ������ = ��������� ������
	u32 fnt_num;															// ������������� ������� ��� ������
	u32 addr;

	fnt_num1 = 0;															// ����� ������� ��� ������ = ������ ������
	fnt_num2 = FNTRecordMAX;												// ������ ������� ��� ������ = ��������� ������

	// ���������� ������
	addr = FNT_BASE_ADDRESS;
	if (FLASH_ReadByte(addr) == 0xFF) {										// ������ ������ ��������?
		return 0;															// �� - ��������� ������ FNT = 0
	}
	addr += FNTRecordMAX * FNT_RECORD_SIZE;
	if (FLASH_ReadByte(addr) != 0xFF) {										// ��������� ������ ������?
		return 0xFFFFFFFF;													// �� - ��������� ������� FNT ���
	}

	// �������������� ����� �� ������� FNT
	while ( (fnt_num2 - fnt_num1) > 1 ) {									// ��������� ����� ����� � ������ ������� ��������� �����
		fnt_num = (fnt_num1 + fnt_num2) >> 1;
		addr = FNT_BASE_ADDRESS + fnt_num * FNT_RECORD_SIZE;
		if (FLASH_ReadByte(addr) == 0xFF) {
			fnt_num2 = fnt_num;
		}
		else {
			fnt_num1 = fnt_num;
		}
	}
	return fnt_num2;														// ��������� ������ FNT = ������ �������
}


//-----------------------------------------------------------------------------
// �������� ����� ������ ����� � �������� ������ � ������� FNT
//-----------------------------------------------------------------------------
// ������ �� ���� ������� �� ������ �� ����� ������� FNT
// ����� ����������� �� ������� ����� (��� + ���)
// ���� ���� �� ������ - ������������ 0xFFFFFFFF
u32 FS_FindFileByName(const u8 *full_name) {
	u32 fnt_num;
	u32 fnt_addr;
	u32 addr;
	u8 len;
	u8 i;
	u8 b;

	len = 1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH;							// ����� ������
	fnt_addr = FNT_BASE_ADDRESS;											// ����� ������ ������ FNT
	for (fnt_num = 0; fnt_num < FNTRecordsNumber; fnt_num++) {				// ��������� ��� ������ � ������� FNT
		addr = fnt_addr;													// ����� ������� ������
		for (i=0; i<len; i++) {												// ���������� ��� ����� � �������� ������
			b = FLASH_ReadByte(addr++);										// ��������� ���� �� ������
			if (b != full_name[i]) {										// ������� �����?
				break;														// ��� - �������� ��������� �����
			}
		}
		if (i == len) {														// ��� ����� �������?
			return fnt_num;													// �� - ������� ����� ������ FNT
		}
		fnt_addr += FNT_RECORD_SIZE;										// ����� ��������� ������ FNT
	}
	return 0xFFFFFFFF;														// ��������� = "���� �� ������"
}

//-----------------------------------------------------------------------------
// ����� c�������� ������� � ������� CAT
//-----------------------------------------------------------------------------
// ������ �� ���� ������� �� ������ �� ����� ������� CAT
// ���� ��������� ��������� ��� - ������������ 0xFFFF
u16 FS_FindFreeCluster(void) {
	u16 cat_num;
	u32 cat_addr;

	cat_addr = CAT_BASE_ADDRESS;											// ����� ������ ������ CAT
	for (cat_num = 0; cat_num < CATRecordsNumber; cat_num++) {				// ��������� ��� ������ � ������� CAT
		if (FLASH_ReadByte(cat_addr) == 0xFF) {								// ������ ��������?
			return cat_num;													// �� - ������� ����� ������ CAT
		}
		cat_addr += CAT_RECORD_SIZE;										// ����� ��������� ������ CAT
	}
	return 0xFFFF;															// ��������� = "��������� ������ CAT �� �������"
}


//-----------------------------------------------------------------------------
// �������� ���-�� c�������� ��������� � ������� CAT
//-----------------------------------------------------------------------------
// ������ �� ���� ������� �� ������ �� ����� ������� CAT
u16 FS_GetFreeClustersNum(void) {
	u16 cat_num;
	u32 cat_addr;
	u16 n = 0;

	cat_addr = CAT_BASE_ADDRESS;											// ����� ������ ������ CAT
	for (cat_num = 0; cat_num < CATRecordsNumber; cat_num++) {				// ��������� ��� ������ � ������� CAT
		if (FLASH_ReadByte(cat_addr) == 0xFF) {								// ������ ��������?
			n++;															// �� - ������� ���-�� ��������� ���������
		}
		cat_addr += CAT_RECORD_SIZE;										// ����� ��������� ������ CAT
	}
	return n;																// ��������� = ���-�� ��������� ���������
}


//-----------------------------------------------------------------------------
// �������� ������ ��� ����� � ������ FNT
//-----------------------------------------------------------------------------
void FS_FNTWriteFullName(u32 fnt_num, const u8 *full_name) {
	u8 len;

	len = 1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1;
	FLASH_Write( FNT_BASE_ADDRESS + fnt_num * FNT_RECORD_SIZE, full_name, len );
}


//-----------------------------------------------------------------------------
// �������� ���������1 � ������ FNT
//-----------------------------------------------------------------------------
void FS_FNTSetSignature1(u32 fnt_num, u8 signature) {
	FLASH_WriteByte( FNT_BASE_ADDRESS + fnt_num * FNT_RECORD_SIZE, signature );
}


//-----------------------------------------------------------------------------
// �������� ���� �������� � ������� CAT
//-----------------------------------------------------------------------------
void FS_ClusterSetFlag(u16 clust_num, u8 flag) {
	FLASH_WriteByte( CAT_BASE_ADDRESS + clust_num * CAT_RECORD_SIZE, flag );
}


//-----------------------------------------------------------------------------
// �������� ����� ���������� �������� � ������� CAT
//-----------------------------------------------------------------------------
void FS_SetNextCluster(u16 clust_num_curr, u16 clust_num_next) {
	FLASH_Write( CAT_BASE_ADDRESS + clust_num_curr * CAT_RECORD_SIZE + 1, (u8 *)&clust_num_next, 2 );
}


//-----------------------------------------------------------------------------
// ��������� ����� ���������� �������� � ������� CAT
//-----------------------------------------------------------------------------
u16 FS_GetNextCluster(u16 clust_num_curr) {
	u16 clust_num_next;

	FLASH_Read( (u8 *)&clust_num_next, CAT_BASE_ADDRESS + clust_num_curr * CAT_RECORD_SIZE + 1, 2 );
	return clust_num_next;
}


//-----------------------------------------------------------------------------
// �������� ����� �������� � ����
//-----------------------------------------------------------------------------
void FS_FlushPageBuffer(const tFCS *p_fcs, u16 size) {
	u32 addr;

	addr = CLUSTERS_BASE_ADDRESS +											// ����� �������� � ����-������
	       p_fcs->CurrCluster * CLUSTER_SIZE +
		   p_fcs->CurrPage * PAGE_SIZE;
 	FLASH_Write(addr, p_fcs->PageBuffer, size);								// �������� �������� ����-������
}


//-----------------------------------------------------------------------------
// �������� ����� ��������� ��������� FCS
//-----------------------------------------------------------------------------
s8 FS_GetFreeFCS() {
	u8 i;

	for (i=0; i<MAX_FILES; i++) {											// ��������� ��� ��������� FCS
		if (pFCSArray[i]->State == FCS_STATE_CLOSED) {						// ������� ��������� (��������) ��������� FCS?
			return i;														// �� - ������� ����� ��������� ��������� FCS
		}
	}
	return -1;																// ��� - ������� ������ "��� ��������� ��������� FCS" (������ -1)
}




//					*	*	*	*	*	*	*	*	*




//-----------------------------------------------------------------------------
//               ��������� �������� ���������� �����
//-----------------------------------------------------------------------------
s8 FS_Assign(const u8 *file_name,tFile * f) {
	s8 fcs_num;
	u8 name[FILE_NAME_LENGTH + 1];
	u8 type[FILE_TYPE_LENGTH + 1];

	// ��������� ������������� �������� ������� (������ -1)
	if (! FS_IS_INITED) {													// �������� ������� ����������������?
		return EFS_FS_NOT_INITED;															// ��� - ������� ������ "�������� ������� �� ����������������" (������ -1)
	}

	if (! FS_GetNameAndType(file_name, name, type)) {						// ��������� ����� � ���� ����������� �������?
		return EFS_INVALID_FILE_NAME;															// ��� - ������� ������ "�������� ������ ����� �����" (������ -3)
	}

	// ��������� ������������� ����� � �������� ������
	if (FS_FileUseFCS(name, type) > -1) {									// ���� � �������� ������ ������������?
		return EFS_FILE_IS_USED;															// �� - ������� ������ "���� � �������� ������ ������������" (������ -4)
	};

	// �������� ����� ��������� ��������� FCS
	fcs_num = FS_GetFreeFCS();
	if (fcs_num < 0) {														// ��������� ��������� FCS �������?
		return EFS_NO_FREE_FCS;											// ��� - ������� ������ "��� ��������� ��������� FCS" (������ -2)
	}

	// ��������� ������� ��������� FCS
	pFCSArray[fcs_num]->State = FCS_STATE_OPENED;							// ��������� FCS = �������
	strcpy((char *)pFCSArray[fcs_num]->Name, (char *)name);					// �������� ��� �����
	strcpy((char *)pFCSArray[fcs_num]->Type, (char *)type);					// �������� ��� �����
	*f = fcs_num;
	return FS_RESULT_OK;															// ������� ����� �������� ��������� FCS
}


//-----------------------------------------------------------------------------
//                 ������� ����� ���� ��� ������
//-----------------------------------------------------------------------------
s8 FS_Rewrite(tFile fcs_num) {
	tFCS *p_fcs;															// ��������� �� FCS
	u32 fnt_num;															// ����� ������ � ������� FNT
	u16 clust_num;
	u8 *full_name;															// ��������� �� ������ ��� �����
	u16 k;

	// ��������� �������� ���������� (������ -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// �������� ���������� ��������� �����?
		return EFS_INVALID_FSC;															// ��� - ������� ������ "�������� ���������� �� ��������� �����" (������ -9)
	}

	p_fcs = pFCSArray[fcs_num];												// �������� ��������� �� FCS

	// ��������� ��������� ��������� FCS (������ -1)
	if (p_fcs->State != FCS_STATE_OPENED) {									// ��������� FCS �������?
		return EFS_FCS_NOT_OPENED;															// ��� - ������� ������ "��������� FCS �� �������" (������ -1)
	}

	// �������� ������ ��� ����� ( � �����: Signature1 + ��� + ��� + Signature2 )
	full_name = p_fcs->FNT.FullName;										// ��������� �� ������ ��� �����
	FS_GetFullName(p_fcs->Name, p_fcs->Type, full_name);

	// ��������� ������������ ����� (������ -2)
	fnt_num = FS_FindFileByName(full_name);									// ����� ���� � �������� ������ (������� ���������)
	if (fnt_num != 0xFFFFFFFF) {											// ������ ���� � �������� ������?
		return EFS_FILE_NAME_IS_EXIST;															// �� - ������� ������ "���� � �������� ������ ��� ����������" (������ -2)
	}

	// ����� ��������� ������ � ������� FNT (������ -3)
	fnt_num = FS_FindFreeFNT();
	if (fnt_num == 0xFFFFFFFF) {											// ��������� ������ FNT �������?
		return EFS_NO_FREE_FNT;															// ��� - ������� ������ "��� ��������� ������ FNT" (������ -3)
	}

	// ��������� ������� ���������� ����� (������ -4)
	clust_num = FS_FindFreeCluster();										// ����� ��������� ������� � ������� CAT
	if (clust_num == 0xFFFF) {												// ��������� ������� ������?
		return EFS_NO_FREE_SPACE;															// ��� - ������� ������ "������������ �����" (������ -4)
	}

	// ������ ��� - ������� ����

	// �������� ������� ������ � �������� FNT � CAT
	FS_FNTWriteFullName(fnt_num, full_name);								// �������� ������ FNT = "������" (�������� ������ ��� �����)
	FS_ClusterSetFlag(clust_num, 0xFE);										// �������� ������� � ������� CAT = "������"

	// ��������� ���������� ���������� ��������� FCS.FNT
	//p_fcs->FNT.FullName[];												...(������ ��� = ��� ���������)
	p_fcs->FNT.Attribute = FILE_ATTR_NOATTR;								// ���� ��� ���������
	p_fcs->FNT.FirstCluster = clust_num;									// ������ ������� = ������� �������
	p_fcs->FNT.Size = 0;													// ��������� ������ = 0

	// ��������� FCS
	p_fcs->State = FCS_STATE_OPENED_WRITE;									// �������� - "��������� FCS ������� ��� ������ �����"
	p_fcs->FNT_num = fnt_num;												// ����� ������ ������� FNT
	p_fcs->CurrCluster = clust_num;											// ����� �������� ��������
	p_fcs->CurrPage = 0;													// ����� ������� �������� � ������� ��������
	p_fcs->PageBufPtr = 0;													// ������� ��������� � ������ ��������
	//p_fcs->PageBuffer[];													...(����� ������� �������� ����-������ = �� ����������)

//------
//<!> ��� ������� !!!
//�������� ����� ��������
for (k = 0; k < PAGE_SIZE; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}
//------

	return FS_RESULT_OK;																// ���� ��� ������ ������� ������
}


//-----------------------------------------------------------------------------
//            ������� ������������ ���� ��� ����������
//-----------------------------------------------------------------------------
s8 FS_Append(tFile fcs_num) {
	tFCS *p_fcs;															// ��������� �� FCS
	u8 *full_name;															// ��������� �� ������ ��� �����
	u32 fnt_num_old, fnt_num_new;											// ������ � ����� ������ ������� � ������� FNT
	u32 addr;																// ����� ����-������
	u8 len;
	u32 file_size;															// ������ �����
	u16 clust_num;															// ������ (� ������� CAT) ���������� ��������
	u8 page_num;															// ����� ��������� �������� ������ ���������� ��������
	u32 n_bytes;															// ���-�� ���� � ��������� ��������
	u16 i;
	u16 k;

	// ��������� �������� ���������� (������ -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// �������� ���������� ��������� �����?
		return EFS_INVALID_FSC;															// ��� - ������� ������ "�������� ���������� �� ��������� �����" (������ -9)
	}

	p_fcs = pFCSArray[fcs_num];												// �������� ��������� �� FCS

	// ����� ��������� ����� - ��������� ��������� ������

	// ��������� ��������� ��������� FCS (������ -1)
	if (p_fcs->State != FCS_STATE_OPENED) {									// ��������� FCS �������?
		return EFS_FCS_NOT_OPENED;															// ��� - ������� ������ "��������� FCS �� �������" (������ -1)
	}

	// �������� ������ ��� ����� ( � �����: Signature1 + ��� + ��� + Signature2 )
	full_name = p_fcs->FNT.FullName;										// ��������� �� ������ ��� �����
	FS_GetFullName(p_fcs->Name, p_fcs->Type, full_name);

	// ����� ������������ ����� � ������� FNT (������ -2)
	fnt_num_old = FS_FindFileByName(full_name);								// ����� ���� � �������� ������ (������� ���������)
	if (fnt_num_old == 0xFFFFFFFF) {										// ������ ���� � �������� ������?
		return EFS_FILE_NOT_FOUND;															// ��� - ������� ������ "���� � �������� ������ �� ������" (������ -2)
	}

	// ����� ��������� ������ � ������� FNT (������ -3)
	fnt_num_new = FS_FindFreeFNT();
	if (fnt_num_new == 0xFFFFFFFF) {										// ��������� ������ FNT �������?
		return EFS_NO_FREE_FNT;															// ��� - ������� ������ "��� ��������� ������ FNT" (������ -3)
	}

	// ������ ��� - ������� ������� ����

	// ��������� ���������� ���������� ��������� FCS.FNT

	//p_fcs->FNT.FullName[];												(������ ��� = ��� ���������)

	// ���������� � FCS.FNT ������ �� ������� FNT �����
	addr = FNT_BASE_ADDRESS + fnt_num_old * FNT_RECORD_SIZE;				// ����� ������ FNT ������������ �����
	len = 1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1;						// ����� ������� �����
	addr += len;															// ���������� ������ ��� (������ ��� �� ����������, ��� ��� ���������)
	FLASH_Read(full_name + len, addr, FNT_RECORD_SIZE - len);				// ��������� ������ FNT ����� ������� �����

	// ��������� ��������� ��� ��� ������ � ����  (������ -4)
	if (p_fcs->FNT.Attribute == FILE_ATTR_READONLY) {						// � ���� ��������� ������?
		return EFS_WRITE_DISABLED;															// ��� - ������� ������ "������ � ���� ���������"  (������ -4)
	}

	file_size = p_fcs->FNT.Size;											// ������ �����
	page_num = ( (file_size / PAGE_SIZE) % PAGES_PER_CLUSTER );				// ����� ��������� �������� ������ ��������
	n_bytes = file_size % PAGE_SIZE;										// ���������� ���� � ��������� ��������

	// ��������� ������ (� ������� CAT) ���������� ��������
	i = (file_size / CLUSTER_SIZE);											// ���-�� ����� ���������
	clust_num = p_fcs->FNT.FirstCluster;									// �������� � ������� �������� �������
	while (i--) {															// ���� �� ������� ���������
		clust_num = FS_GetNextCluster(clust_num);
	}

	// �������� ������ � ������� FNT
	FS_FNTSetSignature1(fnt_num_old, 0x00);									// �������� ������ ������ FNT = "�������"
	FS_FNTWriteFullName(fnt_num_new, full_name);							// �������� ����� ������ FNT = "������" (�������� ������ ��� �����)

	// ��������� FCS
	p_fcs->State = FCS_STATE_OPENED_WRITE;									// �������� - "��������� FCS ������� ��� ������ �����"
	p_fcs->FNT_num = fnt_num_new;											// ����� ������ ������� FNT
	p_fcs->CurrCluster = clust_num;											// ������ (� ������� CAT) �������� ��������
	p_fcs->CurrPage = page_num;												// ����� ������� �������� � ������� ��������
	p_fcs->PageBufPtr = n_bytes;											// ������� ��������� � ������ ��������

	// ��������� ��������� �������� � ����� ��������
	if (n_bytes) {															// ������ �������� �������� ������?
		addr = CLUSTERS_BASE_ADDRESS +										// ����� �������� � ����-������
		       clust_num * CLUSTER_SIZE +
		       page_num * PAGE_SIZE;
		FLASH_Read(p_fcs->PageBuffer, addr, n_bytes);						// ��������� ��������
	}

//------
//<!> ��� ������� !!!
//�������� ������� ������ ��������
for (k = n_bytes; k < PAGE_SIZE; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}
//------

	return FS_RESULT_OK;																// ���� ��� ������ ������� ������
}


//-----------------------------------------------------------------------------
//                 ������� ���� ��� ������
//-----------------------------------------------------------------------------
s8 FS_Reset(tFile fcs_num) {
	tFCS *p_fcs;															// ��������� �� FCS
	u8 *full_name;															// ��������� �� ������ ��� �����
	u32 fnt_num;															// ����� ������ � ������� FNT
	u8 len;
	u32 addr;																// ����� ����-������
	u32 size;
	u16 k;

	// ��������� �������� ���������� (������ -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// �������� ���������� ��������� �����?
		return EFS_INVALID_FSC;															// ��� - ������� ������ "�������� ���������� �� ��������� �����" (������ -9)
	}

	p_fcs = pFCSArray[fcs_num];												// �������� ��������� �� FCS

	// ����� ��������� ����� - ��������� ��������� ������

	// ��������� ��������� ��������� FCS (������ -1)
	if (p_fcs->State != FCS_STATE_OPENED) {									// ��������� FCS �������?
		return EFS_FCS_NOT_OPENED;															// ��� - ������� ������ "��������� FCS �� �������" (������ -1)
	}

	// �������� ������ ��� ����� ( � �����: Signature1 + ��� + ��� + Signature2 )
	full_name = p_fcs->FNT.FullName;										// ��������� �� ������ ��� �����
	FS_GetFullName(p_fcs->Name, p_fcs->Type, full_name);

	// ����� ������������ ����� � ������� FNT (������ -2)
	fnt_num = FS_FindFileByName(full_name);									// ����� ���� � �������� ������ (������� ���������)
	if (fnt_num == 0xFFFFFFFF) {											// ������ ���� � �������� ������?
		return EFS_FILE_NOT_FOUND;															// ��� - ������� ������ "���� � �������� ������ �� ������" (������ -2)
	}

	// ������ ��� - ������� ����

	// ��������� ���������� ���������� ��������� FCS.FNT
	//p_fcs->FNT.FullName[];												...(������ ��� = ��� ���������)

	// ���������� � FCS.FNT ������ �� ������� FNT
	addr = FNT_BASE_ADDRESS + fnt_num * FNT_RECORD_SIZE;					// ����� ������ FNT ������������ �����

	len = 1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1;						// ����� ������� �����
	addr += len;															// ���������� ������ ��� (������ ��� �� ����������, ��� ��� ���������)
	FLASH_Read(full_name + len, addr, FNT_RECORD_SIZE - len);				// ��������� ������ FNT (����� ������� �����)

	// ��������� FCS
	p_fcs->State = FCS_STATE_OPENED_READ;									// �������� - "��������� FCS ������� ��� ������ �����"
	p_fcs->FNT_num = fnt_num;												// ����� ������ ������� FNT
	p_fcs->CurrCluster = p_fcs->FNT.FirstCluster;							// ������ (� ������� CAT) �������� ��������
	p_fcs->CurrPage = 0;													// ����� ������� �������� � ������� ��������
	p_fcs->PageBufPtr = 0;													// ������� ��������� � ������ ��������

	size = p_fcs->FNT.Size;													// ����� ������ �����
	p_fcs->RemainSize = size;												// �������� �� ��������� ����

	if (size > PAGE_SIZE) {													// ��������� ���������� ���� � ������ ��������
		size = PAGE_SIZE;
	}

	// ��������� ������ �������� � ����� ��������
	if (size) {																// ������ �������� �������� ������?
		addr = CLUSTERS_BASE_ADDRESS +										// ����� �������� � ����-������
		       p_fcs->CurrCluster * CLUSTER_SIZE;							// (����� ����� �������� = 0)
		FLASH_Read(p_fcs->PageBuffer, addr, size);							// ��������� ��������
	}

//------
//<!> ��� ������� !!!
//�������� ������� ������ ��������
for (k = size; k < PAGE_SIZE; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}
//------

	p_fcs->MinFilePosition = 0;												// ���. ������� ����� � ������� ��������
	if (size == PAGE_SIZE) {												// ����. ������� ����� � ������� ��������
		p_fcs->MaxFilePosition = PAGE_SIZE-1;
	}
	else {
		// ����� size < PAGE_SIZE
		p_fcs->MaxFilePosition = size;
	}

	return FS_RESULT_OK;																// ���� ��� ������ ������� ������
}


//-----------------------------------------------------------------------------
//                     �������� ���� � �������� ����
//-----------------------------------------------------------------------------
s8 FS_WriteByte(tFile fcs_num, u8 data) {
	tFCS *p_fcs;															// ��������� �� FCS
	u16 page_buf_ptr;														// ��������� � ������ ��������
	u8 curr_page;															// ����� ������� �������� � ������� ��������
	u16 clust_num_next;
	s8 result;																// ��������� ������ �����
	u16 k;

	// ��������� �������� ���������� (������ -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// �������� ���������� ��������� �����?
		return EFS_INVALID_FSC;															// ��� - ������� ������ "�������� ���������� �� ��������� �����" (������ -9)
	}

	p_fcs = pFCSArray[fcs_num];												// �������� ��������� �� FCS

	// ����� ������� - ��������� ��������� ������

	// ��������� ��������� ��������� FCS (������ -1)
	if (p_fcs->State != FCS_STATE_OPENED_WRITE) {							// ��������� FCS ������� ��� ������ �����?
		return EFS_FCS_NOT_OPENED_WRITE;															// ��� - ������� ������ "��������� FCS �� ������� ��� ������ �����" (������ -1)
	}

	// ������ ��� - �������� ����

	p_fcs->FNT.Size++;														// ��������� ������ �����
	page_buf_ptr = p_fcs->PageBufPtr;										// ����� ������� ��������� � ������ ��������
	p_fcs->PageBuffer[page_buf_ptr++] = data;								// �������� ���� ������ � ����� ��������

	result = FS_RESULT_OK;																// ��������������� ��������� "���� ������� �������"
	if (page_buf_ptr == PAGE_SIZE) {										// ����� �������� ����������?
		page_buf_ptr = 0;													// �� - �������� ������� ��������� � ������ ��������
		FS_FlushPageBuffer(p_fcs, PAGE_SIZE);								// �������� ����� �������� � ����

//------
//<!> ��� ������� !!!
//�������� ����� ��������
for (k = 0; k < PAGE_SIZE; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}
//------
		curr_page = p_fcs->CurrPage + 1;									// ��������� ����� ������� ��������
		if (curr_page == PAGES_PER_CLUSTER) {								// ������� ����������?
			curr_page = 0;													// �� - �������� ����� ������� ��������

			// ��������� ������� ���������� ����� (������ -2)
			clust_num_next = FS_FindFreeCluster();							// ����� ��������� ������� � ������� CAT
			if (clust_num_next == 0xFFFF) {									// ��������� ������� ������?
				result = EFS_NO_FREE_SPACE;												// ��� - ��������� "������������ ����� ��� ����������� ������" (������ -2)
			}
			else {
				FS_SetNextCluster(p_fcs->CurrCluster, clust_num_next);		// �������� ��������� �� ��������� ������� � ������� CAT
				FS_ClusterSetFlag(clust_num_next, 0xFE);					// �������� ����� ������� � ������� CAT = "������"
				p_fcs->CurrCluster = clust_num_next;						// �������� ����� �������� ��������
			}
		}
		p_fcs->CurrPage = curr_page;										// ��������� ����� ������� ��������
	}
	p_fcs->PageBufPtr = page_buf_ptr;										// �������� ������� ��������� � ������ ��������


	return result;															// ��������� ������ �����
}


//-----------------------------------------------------------------------------
//                    ��������� ���� �� ��������� �����
//-----------------------------------------------------------------------------
s8 FS_ReadByte(tFile fcs_num, u8 *data) {
	tFCS *p_fcs;															// ��������� �� FCS
	u16 page_buf_ptr;														// ��������� � ������ ��������
	u8 *page_buffer;
	u16 page_size;															// ������ ������ ��������
	u32 remain_size;														// ���������� ����� ������ � �����
	u8  curr_page;															// ����� ������� �������� � ������� ��������
	u16 clust_num;
	u32 addr;
	u16 k;

	// ��������� �������� ���������� (������ -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// �������� ���������� ��������� �����?
		return EFS_INVALID_FSC;															// ��� - ������� ������ "�������� ���������� �� ��������� �����" (������ -9)
	}

	p_fcs = pFCSArray[fcs_num];												// �������� ��������� �� FCS

	// ��������� ��������� ��������� FCS (������ -1)
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							// ��������� FCS ������� ��� ������ �����?
		return EFS_FCS_NOT_OPENED_READ;															// ��� - ������� ������ "��������� FCS �� ������� ��� ������ �����" (������ -1)
	}

	remain_size = p_fcs->RemainSize;

	// ��������� ���-�� ������������� ���� (������ -2)
	if (! remain_size) {													// ������� ������������� �����?
		return EFS_NO_DATA;															// ��� - ������� ������ "���� ����" (������ -2)
	}

	// ����� ������� ������ ��� ������

	p_fcs->RemainSize = --remain_size;										// ��������� ���-�� ������������� ����

	page_buf_ptr = p_fcs->PageBufPtr;										// ����� ������� ��������� � ������ ��������
	page_buffer = p_fcs->PageBuffer;										// ����� ��������� �� ����� ��������

	// ����� ���� ������ �� ������ ��������
	// � ����������� ��������� � ������ ��������
	*data = page_buffer[page_buf_ptr++];

	if (page_buf_ptr == PAGE_SIZE) {										// ����� �������� ��������� ��������?
		page_buf_ptr = 0;													// �� - �������� ������� ��������� � ������ ��������
		clust_num = p_fcs->CurrCluster;										// ����� ������ (� ������� CAT) �������� ��������
		curr_page = p_fcs->CurrPage + 1;									// ��������� ����� ������� ��������
		if (curr_page == PAGES_PER_CLUSTER) {								// ������� ��������� ��������?
			curr_page = 0;													// �� - �������� ����� ������� ��������
			clust_num = FS_GetNextCluster(clust_num);						// ��������� ������� � ������� � ������� CAT
			p_fcs->CurrCluster = clust_num;									// �������� ����� �������� ��������
		}
		p_fcs->CurrPage = curr_page;										// �������� ����� ������� ��������

		// �������� ������ ��������� ������� �����
		if (remain_size > PAGE_SIZE) {
			page_size = PAGE_SIZE;
		}
		else {
			page_size = remain_size;
		}

		// ��������� ��������� �������� ����� � �����
		if (page_size) {
			addr = CLUSTERS_BASE_ADDRESS +									// ����� �������� � ����-������
			       clust_num * CLUSTER_SIZE +
				   curr_page * PAGE_SIZE;
			FLASH_Read(page_buffer, addr, page_size);						// ��������� ��������
		}

//------
//<!> ��� ������� !!!
//�������� ������� ������ ��������
for (k = page_size; k < PAGE_SIZE; k++) {
	page_buffer[k] = 0xFF;
}
//------

		// �������� �������� ������� ����� � ������� ��������
		p_fcs->MinFilePosition += PAGE_SIZE;								// ���. ������� ����� � ������� ��������
		if (page_size == PAGE_SIZE) {										// ����. ������� ����� � ������� ��������
			p_fcs->MaxFilePosition += PAGE_SIZE;
		}
		else {
			// ����� page_size < PAGE_SIZE
			p_fcs->MaxFilePosition += page_size + 1;
		}
	}
	p_fcs->PageBufPtr = page_buf_ptr;										// �������� ������� ��������� � ������ ��������

	return FS_RESULT_OK;																// ���� ������� ��������
}


//<!> ������� �� �������� !!!
//-----------------------------------------------------------------------------
//			�������� ����� � �������� ����
//-----------------------------------------------------------------------------
s32 FS_Write(tFile fcs_num, const u8 *buffer, u32 size) {
	tFCS *p_fcs;															// ��������� �� FCS
	u8 *page_buffer;
	u16 page_buf_ptr;														// ��������� � ������ ��������
	u16 remain_page;														// ������ ������� ������ ��������
	u16 first_size;															// ������ ������ ��������
	u16 last_size;															// ������ ��������� ��������
	u32 full_page_count;													// ���-�� ����� �������
	u8  curr_page;															// ����� ������� �������� � ������� ��������
	u16 clust_num_next;															// ����� �������� ��������
//	u32 addr;
	u16 k;

	// ��������� �������� ���������� (������ -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// �������� ���������� ��������� �����?
		return -9;															// ��� - ������� ������ "�������� ���������� �� ��������� �����" (������ -9)
	}

	p_fcs = pFCSArray[fcs_num];												// �������� ��������� �� FCS

	// ����� ������� - ��������� ��������� ������

	// ��������� ��������� ��������� FCS (������ -1)
	if (p_fcs->State != FCS_STATE_OPENED_WRITE) {							// ��������� FCS ������� ��� ������ �����?
		return -1;															// ��� - ������� ������ "��������� FCS �� ������� ��� ������ �����" (������ -1)
	}

	// ������ ��� - �������� �����

	page_buffer = p_fcs->PageBuffer;										// ����� ��������� �� ����� ��������
	page_buf_ptr = p_fcs->PageBufPtr;										// ����� ������� ��������� � ������ ��������

	// �������� ������ ������ ��������
	remain_page = PAGE_SIZE - page_buf_ptr;									// �������� ������ ������� � ������ ��������
	if (size < remain_page) {
		first_size = size;													// ���� ������ ��������� � ������� ������ ��������
		full_page_count = 0;												// ���-�� ����� ������� = 0
	}
	if (size == remain_page) {
		first_size = remain_page;											// ������� ������ �������� ��������� ���������
		full_page_count = 1;												// ���-�� ����� ������� = 1
		last_size = 0;														// ������ ��������� �������� = 0
	}
	if (size > remain_page) {
		first_size = remain_page;											// ������� ������ �������� ��������� ���������
		full_page_count = (size - remain_page) / PAGE_SIZE + 1;				// ���-�� ����� �������
		last_size = (size - remain_page) % PAGE_SIZE;						// ������ ��������� ��������
	}

	// �������� ������ ��������
	if (first_size) {														// ������� ����� ��� ������?
		memcpy(page_buffer + page_buf_ptr, buffer, first_size);				// �� - �������� � ����� ��������
	}
	else {
		return 0;															// ��� - ��������� = "�������� 0 ����"
	}

	// ��������� ���������� �� ����� ��������?
	if (! full_page_count) {												// ����� �������� �� ����������?
		p_fcs->PageBufPtr += first_size;									// �� - �������� ������� ��������� � ������ ��������
		return size;														// ��������� = "�������� size ����"
	}
	// ����� ��������� ��� ������ ������ �������� � ����

	// ����� ����� �������� ��������
	FS_FlushPageBuffer(p_fcs, PAGE_SIZE);									// �������� ����� �������� � ����
	full_page_count--;



	if (last_size) {
	}



//******************
		if (page_buf_ptr == PAGE_SIZE) {										// ����� �������� ����������?
			page_buf_ptr = 0;													// �� - �������� ������� ��������� � ������ ��������
			FS_FlushPageBuffer(p_fcs, PAGE_SIZE);								// �������� ����� �������� � ����
	
	//------
	//<!> ��� ������� !!!
	//�������� ����� ��������
	for (k = 0; k < PAGE_SIZE; k++) {
		p_fcs->PageBuffer[k] = 0xFF;
	}
	//------
			curr_page = p_fcs->CurrPage + 1;									// ��������� ����� ������� ��������
			if (curr_page == PAGES_PER_CLUSTER) {								// ������� ����������?
				curr_page = 0;													// �� - �������� ����� ������� ��������
	
				// ��������� ������� ���������� ����� (������ -2)
				clust_num_next = FS_FindFreeCluster();							// ����� ��������� ������� � ������� CAT
				if (clust_num_next == 0xFFFF) {									// ��������� ������� ������?
//					result = -2;												// ��� - ��������� "������������ ����� ��� ����������� ������" (������ -2)
				}
				else {
					FS_SetNextCluster(p_fcs->CurrCluster, clust_num_next);		// �������� ��������� �� ��������� ������� � ������� CAT
					FS_ClusterSetFlag(clust_num_next, 0xFE);					// �������� ����� ������� � ������� CAT = "������"
					p_fcs->CurrCluster = clust_num_next;						// �������� ����� �������� ��������
				}
			}
			p_fcs->CurrPage = curr_page;										// ��������� ����� ������� ��������
		}
		p_fcs->PageBufPtr = page_buf_ptr;										// �������� ������� ��������� � ������ ��������








	return 0; // (��������� ��������)
}


//<!> ������� �� �������� !!!
//-----------------------------------------------------------------------------
//			��������� ����� �� ��������� �����
//-----------------------------------------------------------------------------
s32 FS_Read(tFile fcs_num, u8 *buffer, u32 size) {
	tFCS *p_fcs;															// ��������� �� FCS
	u8 *page_buffer;
	u16 page_buf_ptr;														// ��������� � ������ ��������
	u16 first_size;															// ������ ������ ��������
	u16 last_size;															// ������ ��������� ��������
	u32 full_page_count;													// ���-�� ����� �������
	u32 remain_size;														// ���������� ������ �����
	u8  curr_page;															// ����� ������� �������� � ������� ��������
	u16 clust_num;
	u32 addr;

	// ��������� �������� ���������� (������ -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// �������� ���������� ��������� �����?
		return -9;															// ��� - ������� ������ "�������� ���������� �� ��������� �����" (������ -9)
	}

	p_fcs = pFCSArray[fcs_num];												// �������� ��������� �� FCS

	// ��������� ��������� ��������� FCS (������ -1)
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							// ��������� FCS ������� ��� ������ �����?
		return -1;															// ��� - ������� ������ "��������� FCS �� ������� ��� ������ �����" (������ -1)
	}

	// ������ ��� - ��������� �����

	remain_size = p_fcs->RemainSize;										// ���������� ����� ������ � �����

	// ��������� - ����� ����� ��� ���?
	if (! remain_size) {													// ������� ������������� ����� �����?
		return 0;															// ��� - ������� ��������� "��������� 0 ����"
	}

	if (! size) {															// ������������� ����� > 0?
		return 0;															// ��� - ������� ��������� "��������� 0 ����"
	}

	// ��������������� ������������� ����� ������
	// (���������� ������������� ����� �� ������� �����)
	if (size > remain_size) {
		size = remain_size;
	}

	page_buffer = p_fcs->PageBuffer;										// ����� ��������� �� ����� ��������
	page_buf_ptr = p_fcs->PageBufPtr;										// ����� ������� ��������� � ������ ��������

	// �������� ������ ������ ��������
	first_size = PAGE_SIZE - page_buf_ptr;									// �������� ������ ������� � ������ ��������
	if (first_size >= size) {
		first_size = size;													// ���� ������������� ������ ���������� � ������ ��������
		full_page_count = 0;												// ���-�� ����� ������� = 0
		last_size = 0;														// ������ ��������� �������� = 0
	}
	else {
		full_page_count = (size - first_size) / PAGE_SIZE;					// ���-�� ����� �������
		last_size = (size - first_size) % PAGE_SIZE;						// ������ ��������� ��������
	}

	// ��������� ������ ��������
	// (������ �������� ������ ���� � ��������� � ������ ��������)
	memcpy(buffer, page_buffer + page_buf_ptr, first_size);					// ����������� ���� �� ������ ��������
	page_buf_ptr += first_size;												// ����������� ��������� � ������ ��������
	remain_size -= first_size;												// ��������������� ���������� ������ �����

	clust_num = p_fcs->CurrCluster;											// ����� ������ (� ������� CAT) �������� ��������
	curr_page = p_fcs->CurrPage;											// ����� ����� ������� ��������

	// ��������� ����� ��������
	if (full_page_count) {
		buffer += first_size;												// ����������� ������� �������� ������
	}
	while (full_page_count--) {
		// ��������� ��������� �������� �����
		curr_page++;														// ��������� ����� ������� ��������
		if (curr_page == PAGES_PER_CLUSTER) {								// ������� ��������� ��������?
			curr_page = 0;													// �� - �������� ����� ������� ��������
			clust_num = FS_GetNextCluster(clust_num);						// ��������� ������� � ������� � ������� CAT
//			p_fcs->CurrCluster = clust_num;									// �������� ����� �������� ��������
		}
//		p_fcs->CurrPage = curr_page;										// �������� ����� ������� ��������
//		page_buf_ptr = 0;													// �������� ������� ��������� � ������ ��������

		// ��������� ��������� �������� ����� � �������� �����
		addr = CLUSTERS_BASE_ADDRESS +										// ����� �������� � ����-������
		       clust_num * CLUSTER_SIZE +
			   curr_page * PAGE_SIZE;
		FLASH_Read(buffer, addr, PAGE_SIZE);								// ��������� �������� ����� � �������� �����

		remain_size -= PAGE_SIZE;											// ��������������� ���������� ������ �����
		buffer += PAGE_SIZE;												// ����������� ������� �������� ������
	}

	// ��������� ��������� ��������
	if (last_size) {
		clust_num = p_fcs->CurrCluster;										// ����� ������ (� ������� CAT) �������� ��������
		curr_page = p_fcs->CurrPage;										// ����� ����� ������� ��������
	}








	p_fcs->CurrCluster = clust_num;											// �������� ����� �������� ��������
	p_fcs->CurrPage = curr_page;											// �������� ����� ������� ��������




	// �������� �������� ������� ����� � ������� ��������
	p_fcs->MinFilePosition += PAGE_SIZE;									// ���. ������� ����� � ������� ��������
	p_fcs->MaxFilePosition += PAGE_SIZE;									// ����. ������� ����� � ������� ��������


	return 0; // (��������� ��������)
}


//<!> ������� �� �������� !!!
//-----------------------------------------------------------------------------
//			�������� ������ � �������� ����
//-----------------------------------------------------------------------------
s32 FS_WriteLn(tFile fcs_num, const u8 *str) {

	// ��������� �������� ���������� (������ -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// �������� ���������� ��������� �����?
		return -9;															// ��� - ������� ������ "�������� ���������� �� ��������� �����" (������ -9)
	}

	return 0; // (��������� ��������)
}


//-----------------------------------------------------------------------------
//			��������� ������ �� ��������� ����� � ������ �����������
//-----------------------------------------------------------------------------
s8 FS_ReadLn(tFile fcs_num, u8 *str, u32 max_size) {
	tFCS *p_fcs;															// ��������� �� FCS
	u8 *page_buffer;
	u16 page_buf_ptr;														// ��������� � ������ ��������
	u16 page_size;															// ������ ������ ��������
	u32 remain_size;														// ���������� ����� ������ � �����
	u8  curr_page;															// ����� ������� �������� � ������� ��������
	u16 clust_num;
	u32 addr;
	u8 s;																	// ������ ����������� �� �����
	u32 i;																	// ������ ������� � ������
	u16 k;
	s8 result;

	// ��������� �������� ���������� (������ -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// �������� ���������� ��������� �����?
		return -9;															// ��� - ������� ������ "�������� ���������� �� ��������� �����" (������ -9)
	}

	p_fcs = pFCSArray[fcs_num];												// �������� ��������� �� FCS

	// ��������� ��������� ��������� FCS (������ -1)
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							// ��������� FCS ������� ��� ������ �����?
		return -1;															// ��� - ������� ������ "��������� FCS �� ������� ��� ������ �����" (������ -1)
	}

	// ������ ��� - ��������� ������

	remain_size = p_fcs->RemainSize;										// ���������� ����� ������ � �����

	// ��������� - ����� ����� ��� ���?
	if (! remain_size) {													// ������� ������������� ����� �����?
		str[0] = 0;															// ��� - ������� ������ ������
		return -2;															// ������� ������ "���� ����" (������ -2)
	}

	page_buffer = p_fcs->PageBuffer;										// ����� ��������� �� ����� ��������
	page_buf_ptr = p_fcs->PageBufPtr;										// ����� ������� ��������� � ������ ��������

	page_size = PAGE_SIZE - page_buf_ptr;									// �������� ������ ������� � ������ �������
	if (page_size > remain_size) {
		page_size = remain_size;
	}

	// ������ ������ ������
	i = 0;																	// ������ � ������ ������
	do {
		// ���� ������ ������ �� ������ ��������
		while (page_size) {
			s = page_buffer[page_buf_ptr++];								// ����� ��������� ������ �� ������ ��������
			remain_size--;													// ���������� ����� ������ � �����
			if (s == 10) {													// ������������ ������ #10
				page_size--;												// ���������� ������ ��������
				continue;
			}
			if (s == 13) {													// ���������� ������ #13 ?
				str[i] = 0;													// ��������� ����������� ������ ������� ��������
				result = 0;													// ��������� = ������ ������� ���������
				break;														// ������ ���������, ��������� ���� ������ ������
			}
			if (s == 0) {													// ���������� ������� ����?
				str[i] = 0;													// �� - ��������� ����������� ������ ������� ��������
				result = -3;												// ��������� = ������: "������� ����" (������ -3)
				break;														// ��������� ���� ������ ������
			}
			// ����� "�������" ������
			if (i < max_size) {
				str[i++] = s;												// �������� ��������� ������ � ����� ������
			}
			else {
				str[i] = 0;													// ��������� ����������� ������ ������� ��������
				// ��������� ������������ ���-�� ����������� ��������
				page_buf_ptr--;												// �������� ��������� � ������ ��������
				remain_size++;												// �������� ���������� ����� ������ � �����
				result = -4;												// ��������� = ������: "��������� ������������ ����� ������" (������ -4)
				break;														// ��������� ���� ������ ������
			}
			// (���� ������� �� ����� �� break, �� page_size �� ���������)
			page_size--;													// ���������� ������ ��������
		}
		// ��������� ������� ���������� ����� ������ ������
		if (page_size) {													// ���� ���������� �� break ?
			p_fcs->RemainSize = remain_size;								// �� - ��������� ���������� ����� ������ � �����
			p_fcs->PageBufPtr = page_buf_ptr;								// ��������� ������� ��������� � ������ ��������
			return result;													// ��������� - ������� ��������� ������ ������
		}
		// ����� �������� ����������, � ������ ��� ��� �� ���������

		// ��������� - ����� ����� ��� ���?
		if (! remain_size) {												// ������� ��� ������������� ����� �����?
			str[i] = 0;														// ��� - ��������� ������
			p_fcs->RemainSize = 0;											// ��������� ���������� ����� ������ � �����
			p_fcs->PageBufPtr = page_buf_ptr;								// ��������� ������� ��������� � ������ ��������
			return 0;														// ��������� = ������ ������� ���������
		}

		// �� ����� ����� - ��������� ��������� �������� �����
		clust_num = p_fcs->CurrCluster;										// ����� ������ (� ������� CAT) �������� ��������
		curr_page = p_fcs->CurrPage + 1;									// ��������� ����� ������� ��������
		if (curr_page == PAGES_PER_CLUSTER) {								// ������� ��������� ��������?
			curr_page = 0;													// �� - �������� ����� ������� ��������
			clust_num = FS_GetNextCluster(clust_num);						// ��������� ������� � ������� � ������� CAT
			p_fcs->CurrCluster = clust_num;									// �������� ����� �������� ��������
		}
		p_fcs->CurrPage = curr_page;										// �������� ����� ������� ��������
		page_buf_ptr = 0;													// �������� ������� ��������� � ������ ��������

		// �������� ������ ��������� ������� �����
		if (remain_size < PAGE_SIZE) {
			page_size = remain_size;
		}
		else {
			page_size = PAGE_SIZE;
		}

		// ��������� ��������� �������� ����� � ����� ��������
		addr = CLUSTERS_BASE_ADDRESS +										// ����� �������� � ����-������
		       clust_num * CLUSTER_SIZE +
			   curr_page * PAGE_SIZE;
		FLASH_Read(page_buffer, addr, page_size);							// ��������� ��������

//------
//<!> ��� ������� !!!
//�������� ������� ������ ��������
for (k = page_size; k < PAGE_SIZE; k++) {
	page_buffer[k] = 0xFF;
}
//------

		// �������� �������� ������� ����� � ������� ��������
		p_fcs->MinFilePosition += PAGE_SIZE;								// ���. ������� ����� � ������� ��������
		p_fcs->MaxFilePosition += page_size;								// ����. ������� ����� � ������� ��������

	} while (1);
	// ���� do... while ���������� ������� return ������ �����
}


//<!> ������� �� �������� !!!
//-----------------------------------------------------------------------------
//			��������� ������ �� ��������� ����� � �������� �����������
//-----------------------------------------------------------------------------
s8 FS_ReadPrevLn(tFile fcs_num, u8 *str, u32 max_size) {

	// ��������� �������� ���������� (������ -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// �������� ���������� ��������� �����?
		return -9;															// ��� - ������� ������ "�������� ���������� �� ��������� �����" (������ -9)
	}

	return 0; // (��������� ��������)
}


//-----------------------------------------------------------------------------
//       ���������� ������������� ���� � �������� ��� ������ �����
//-----------------------------------------------------------------------------
s32 FS_RemainSize(tFile fcs_num) {
	tFCS *p_fcs;															// ��������� �� FCS

	// ��������� �������� ���������� (������ -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// �������� ���������� ��������� �����?
		return -9;															// ��� - ������� ������ "�������� ���������� �� ��������� �����" (������ -9)
	}

	p_fcs = pFCSArray[fcs_num];												// �������� ��������� �� FCS

	// ��������� ��������� ��������� FCS (������ -1)
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							// ��������� FCS ������� ��� ������ �����?
		return -1;															// ��� - ������� ������ "��������� FCS �� ������� ��� ������ �����" (������ -1)
	}

	return p_fcs->RemainSize;												// ������� ���-�� ������������� ����
}


//-----------------------------------------------------------------------------
//         ������� � �������� ������� � �������� ��� ������ �����
//-----------------------------------------------------------------------------
// ����������� "����������" ������� �� �����
s8 FS_Seek(tFile fcs_num, u32 position) {
	tFCS *p_fcs;															// ��������� �� FCS
	u16 clusters_num;
	u16 clust_num;
	u8  page_num;
	u8  old_page_ptr, new_page_ptr;
	u32 size;
	u32 addr;
	u16 i;
	u16 k;

	// ��������� �������� ���������� (������ -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// �������� ���������� ��������� �����?
		return EFS_INVALID_FSC;															// ��� - ������� ������ "�������� ���������� �� ��������� �����" (������ -9)
	}

	p_fcs = pFCSArray[fcs_num];												// �������� ��������� �� FCS

	// ��������� ��������� ��������� FCS (������ -1)
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							// ��������� FCS ������� ��� ������ �����?
		return EFS_FCS_NOT_OPENED_READ;															// ��� - ������� ������ "��������� FCS �� ������� ��� ������ �����" (������ -1)
	}

	// ��������� �������� ������� (������ -2)
	if (position > p_fcs->FNT.Size) {										// ������� � �������� ������� �����?
		return EFS_INVALID_POSITION;															// ��� - ������� ������ "�������� ������� �� ����������" (������ -2)
	}

	// ����� ��� ���������� ������� FS_RSeek()

	page_num = position % CLUSTER_SIZE / PAGE_SIZE;							// ����� ������� �������� � ������� ��������
	new_page_ptr = position % PAGE_SIZE;									// ������� � ������� ��������

	// ��������� �������� �� ��������
	if (position >= p_fcs->MinFilePosition && position <= p_fcs->MaxFilePosition) {
		// ����� �������� �� �������� - �������� ������ ������� ��������� � ������ �������� � ���������� ������
		old_page_ptr = p_fcs->PageBufPtr;
		p_fcs->PageBufPtr = new_page_ptr;
		p_fcs->RemainSize -= new_page_ptr - old_page_ptr;
		return FS_RESULT_OK;														// OK - ���������
	}

	// ����� �������� ��������

	// ������ �� ������� ��������� �� ������� �� �������� �������� �����
	clusters_num = position / CLUSTER_SIZE;									// ���������� ����� �������� �������� � �������
	clust_num = p_fcs->FNT.FirstCluster;									// ������ (� ������� CAT) ������� ������� �������
	for (i = 0; i < clusters_num; i++) {									// �������� ������ (� ������� CAT) �������� ��������
		clust_num = FS_GetNextCluster(clust_num);
	}

	// �������� ��������� ���� FCS
	p_fcs->CurrCluster = clust_num;											// �������� ����� �������� ��������
	p_fcs->CurrPage = page_num;												// �������� ����� ������� �������� � ������� ��������
	p_fcs->PageBufPtr = new_page_ptr;										// �������� ������� ��������� � ������ ��������

	size = p_fcs->FNT.Size - position;										// �������� �� ��������� ����
	p_fcs->RemainSize = size;

	// ��������� ���������� ���� � ������� ��������
	size += new_page_ptr;													// ������ �� ������ ������� �������� �� ����� �����
	if (size >= PAGE_SIZE) {												// ������ ������ ��� ��������?
		size = PAGE_SIZE;													// �� - ��������� �� ������� ��������
	}

	// ��������� �������� � ����� FCS.Buffer[]
	addr = CLUSTERS_BASE_ADDRESS +											// ����� �������� � ����-������
	       clust_num * CLUSTER_SIZE +
		   page_num * PAGE_SIZE;
	FLASH_Read(p_fcs->PageBuffer, addr, size);								// ��������� ��������

//------
//<!> ��� ������� !!!
//�������� ������� ������ ��������
for (k = size; k < PAGE_SIZE; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}
//------

	p_fcs->MinFilePosition = (position / PAGE_SIZE) * PAGE_SIZE;			// ���. ������� ����� � ������� ��������
	p_fcs->MaxFilePosition = p_fcs->MinFilePosition + size-1;				// ����. ������� ����� � ������� ��������

	return FS_RESULT_OK;																// OK - ���������
}


//-----------------------------------------------------------------------------
//         �������� ������� ������� � �������� ��� ������ �����
//-----------------------------------------------------------------------------
// ����������� "�������������" ������� �� �����
// ��� �������� "�����" ���� ������� �� ����������, ������ � ������� 0
// ��� �������� "������" ���� ������� �� ����������, ������ � ������� Size
s8 FS_RSeek(tFile fcs_num, s32 disp) {
	tFCS *p_fcs;															// ��������� �� FCS
	s32 position;
	u16 clusters_num;
	u16 clust_num;
	u8  page_num;
	u8  old_page_ptr, new_page_ptr;
	u32 size;
	u32 addr;
	u16 i;
	u16 k;

	// ��������� �������� ���������� (������ -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// �������� ���������� ��������� �����?
		return EFS_INVALID_FSC;															// ��� - ������� ������ "�������� ���������� �� ��������� �����" (������ -9)
	}

	p_fcs = pFCSArray[fcs_num];												// �������� ��������� �� FCS

	// ��������� ��������� ��������� FCS (������ -1)
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							// ��������� FCS ������� ��� ������ �����?
		return EFS_FCS_NOT_OPENED_READ;															// ��� - ������� ������ "��������� FCS �� ������� ��� ������ �����" (������ -1)
	}

	size = p_fcs->FNT.Size;													// ������ �����

	position = size - p_fcs->RemainSize + disp;								// �������� ����� �������
	// ����� p_fcs->FNT.Size - p_fcs->RemainSize - ������� �������

	// ��������������� ������� �� ��������� �����
	if (position < 0) {
		position = 0;
	}
	if (position > size) {
		position = size;
	}

	// ����� ��� ���������� ������� FS_Seek()

	page_num = position % CLUSTER_SIZE / PAGE_SIZE;							// ����� ������� �������� � ������� ��������
	new_page_ptr = position % PAGE_SIZE;									// ������� � ������� ��������

	// ��������� �������� �� ��������
	if (position >= p_fcs->MinFilePosition && position <= p_fcs->MaxFilePosition) {
		// ����� �������� �� �������� - �������� ������ ������� ��������� � ������ �������� � ���������� ������
		old_page_ptr = p_fcs->PageBufPtr;
		p_fcs->PageBufPtr = new_page_ptr;
		p_fcs->RemainSize -= new_page_ptr - old_page_ptr;
		return FS_RESULT_OK;														// OK - ���������
	}

	// ����� �������� ��������

	// ������ �� ������� ��������� �� ������� �� �������� �������� �����
	clusters_num = position / CLUSTER_SIZE;									// ���������� ����� �������� �������� � �������
	clust_num = p_fcs->FNT.FirstCluster;									// ������ (� ������� CAT) ������� ������� �������
	for (i = 0; i < clusters_num; i++) {									// �������� ������ (� ������� CAT) �������� ��������
		clust_num = FS_GetNextCluster(clust_num);
	}

	// �������� ��������� ���� FCS
	p_fcs->CurrCluster = clust_num;											// �������� ����� �������� ��������
	p_fcs->CurrPage = page_num;												// �������� ����� ������� �������� � ������� ��������
	p_fcs->PageBufPtr = new_page_ptr;										// �������� ������� ��������� � ������ ��������

	size = p_fcs->FNT.Size - position;										// �������� �� ��������� ����
	p_fcs->RemainSize = size;

	// ��������� ���������� ���� � ������� ��������
	size += new_page_ptr;													// ������ �� ������ ������� �������� �� ����� �����
	if (size >= PAGE_SIZE) {												// ������ ������ ��� ��������?
		size = PAGE_SIZE;													// �� - ��������� �� ������� ��������
	}

	// ��������� �������� � ����� FCS.Buffer[]
	addr = CLUSTERS_BASE_ADDRESS +											// ����� �������� � ����-������
	       clust_num * CLUSTER_SIZE +
		   page_num * PAGE_SIZE;
	FLASH_Read(p_fcs->PageBuffer, addr, size);								// ��������� ��������

//------
//<!> ��� ������� !!!
//�������� ������� ������ ��������
for (k = size; k < PAGE_SIZE; k++) {
	p_fcs->PageBuffer[k] = 0xFF;
}
//------

	p_fcs->MinFilePosition = (position / PAGE_SIZE) * PAGE_SIZE;			// ���. ������� ����� � ������� ��������
	p_fcs->MaxFilePosition = p_fcs->MinFilePosition + size-1;				// ����. ������� ����� � ������� ��������

	return FS_RESULT_OK;																// OK - ���������
}


//-----------------------------------------------------------------------------
//                            ������� ����
//-----------------------------------------------------------------------------
s8 FS_Close(tFile *fcs_num) {
	tFCS *p_fcs;															// ��������� �� FCS
	u8 state;
	u32 flash_addr;
	u8 *addr;
	u8 size;

	// ��������� �������� ���������� (������ -9)
	if (*fcs_num < 0 || *fcs_num >= MAX_FILES) {							// �������� ���������� ��������� �����?
		return EFS_INVALID_FSC;															// ��� - ������� ������ "�������� ���������� �� ��������� �����" (������ -9)
	}

	p_fcs = pFCSArray[*fcs_num];											// �������� ��������� �� FCS

	// ����� ��������� ����� - ��������� ��������� ������

	state = p_fcs->State;													// ����� ��������� ��������� FCS

	// ��������� ��������� ��������� FCS (������ -1)
	if (state == FCS_STATE_CLOSED) {										// ��������� FCS �������?
		return EFS_FILE_IS_CLOSED;															// ��� - ������� ������ "��������� FCS �� �������" (������ -1)
	}

	// ��������� FCS ������ ������� ��� ���� ������ ��� ������ ?
	if (state == FCS_STATE_OPENED || state == FCS_STATE_OPENED_READ) {
		p_fcs->State = FCS_STATE_CLOSED;									// �������� = "��������� FCS �������"
		*fcs_num = -1;														// �������� �������� ���������� �� ��������� FCS
		return FS_RESULT_OK;															// �� - ���� ������� ������
	}

	// ���� ������ ��� ������ ?
	if (state == FCS_STATE_OPENED_WRITE) {
		if (p_fcs->PageBufPtr) {											// ����� �������� �� ������?
			FS_FlushPageBuffer(p_fcs, p_fcs->PageBufPtr);					// �� - �������� ����� �������� � ����
		}
		// ���������� ��������� FCS.FNT � ������ FNT �������� �����
		flash_addr = FNT_BASE_ADDRESS +										// ����� FNT �������� �����
		       p_fcs->FNT_num * FNT_RECORD_SIZE +							// (���������� ������ ��� �����)
			   1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1;
		addr = p_fcs->FNT.FullName +										// ��������� �� ��������� FCS.FNT
			   1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1;					// (���������� ������ ��� �����)
		size = sizeof(tFNT) -
		       1 - FILE_NAME_LENGTH - FILE_TYPE_LENGTH - 1;
		FLASH_Write(flash_addr, addr, size);								// ���������� ��������� ������ FNT

		p_fcs->State = FCS_STATE_CLOSED;									// �������� = "��������� FCS �������"
		*fcs_num = -1;														// �������� �������� ���������� �� ��������� FCS
		return FS_RESULT_OK;															// �� - ���� ������� ������
	}
	else {
		return EFS_UNKNOWN_FILE_STATE;															// ������� ������ "����������� ��������� ��������� FCS" (������ -2)
	}
}


//-----------------------------------------------------------------------------
//                            ������� ����
//-----------------------------------------------------------------------------
s8 FS_Delete(const u8 *file_name) {
	u8 name[FILE_NAME_LENGTH + 1];
	u8 type[FILE_TYPE_LENGTH + 1];
	u8 full_name[1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1];
	u32 fnt_num;
	u32 fnt_addr;
	u32 addr;
	u16 clust_num;

	// ��������� ������������� �������� ������� (������ -1)
	if (! FS_IS_INITED) {													// �������� ������� ����������������?
		return EFS_FS_NOT_INITED;															// ��� - ������� ������ "�������� ������� �� ����������������" (������ -1)
	}

	if (! FS_GetNameAndType(file_name, name, type)) {						// ��������� ����� � ���� ����������� �������?
		return EFS_INVALID_FILE_NAME;															// ��� - ������� ������ "�������� ������ ����� �����" (������ -3)
	}

	// ��������� ������������� ����� � �������� ������
	if (FS_FileUseFCS(name, type) > -1) {									// ���� � �������� ������ ������������?
		return EFS_FILE_IS_USED;															// �� - ������� ������ "���� � �������� ������ ������������" (������ -4)
	};

	// �������� ������ ��� ����� ( � �����: Signature1 + ��� + ��� + Signature2 )
	FS_GetFullName(name, type, full_name);

	// ����� ������������ ����� � ������� FNT
	fnt_num = FS_FindFileByName(full_name);									// ����� ���� � �������� ������ (������� ���������)
	if (fnt_num == 0xFFFFFFFF) {											// ������ ���� � �������� ������?
		return EFS_FILE_NOT_FOUND;															// ��� - ������� ������ "���� � �������� ������ �� ������" (������ -2)
	}

	// ������ ��� - ������� ����

	fnt_addr = FNT_BASE_ADDRESS + fnt_num * FNT_RECORD_SIZE;				// ����� FNT ���������� �����

	addr = fnt_addr + 1 + FILE_NAME_LENGTH + FILE_TYPE_LENGTH + 1 + 1;		// ����� ���� FNT.FirstCluster
	FLASH_Read((u8 *)&clust_num, addr, 2);									// ��������� ������ (� ������� CAT) ������� �������� �����

	// ������� �������� � ������� CAT
	// ������ �� ������� ��������� �� ������� �� ���������� �������� �����
	while (clust_num != 0xFFFF) {
		FS_ClusterSetFlag(clust_num, 0x00);									// �������� ������� � ������� CAT = "�������"
		clust_num = FS_GetNextCluster(clust_num);							// �������� ������ (� ������� CAT) ���������� �������� � �������
	}

	// ������� ������ FNT
	FLASH_WriteByte(fnt_addr, 0x00);										// �������� ������ FNT = "�������" (Signature1 = 0x00)

	return FS_RESULT_OK;																// �� - ���� ������� ������
}


//-----------------------------------------------------------------------------
//                      �������� ���������� � �����
//-----------------------------------------------------------------------------
// ���� ��������� ���� �� ������ - ������������ 0xFFFFFFFF
s8 FS_GetFileInfo(u32 * fnt_num, u8 *name, u8 *type, u8 *attr, u32 *size, tFile *f) {
	tFCS *p_fcs;															// ��������� �� FCS
	u32 addr;
	__packed union {
		u8 array[FNT_RECORD_SIZE];											// ������������� fnt ��� �������
		tFNT strc;															// ������������� fnt ��� ���������
	} fnt;
	u8 b;
	u8 i,k;

	// ������ �� ���� ������� �� ��������� ������ �� ����� ������� FNT
	addr = FNT_BASE_ADDRESS + *fnt_num * FNT_RECORD_SIZE;					// ����� ��������� ������ FNT
	while (*fnt_num < FNTRecordsNumber) {
		b = FLASH_ReadByte(addr);											// ��������� ���������1
		if (b == 0xFF) {													// ������� ��������� ������ FNT?
			name[0] = 0;													// �� - ���������� ����� �����
			type[0] = 0;													//   � ������� "������" ����������
			*attr = 0xFF;
			*size = 0;
			*f = -1;
			*fnt_num = 0xFFFFFFFF;
			return EFS_FILE_INFO_NOT_FOUND;									// ��������� � ����������� "��������� ���� �� ������"
		}
		if (b > 0x00) {														// ���� ������?
			break;															// �� - �������� ����� �����
		}
		addr += FNT_RECORD_SIZE;											// ����� ��������� ������ FNT
		(*fnt_num)++;															// ����� ��������� ������ FNT
	}

	if ((*fnt_num) >= FNTRecordsNumber) {										// ���� ������?
			name[0] = 0;													// ��� - ������� "������" ����������
			type[0] = 0;
			*attr = 0xFF;
			*size = 0;
			*f = -1;
			(*fnt_num) = 0xFFFFFFFF;
			return EFS_FILE_INFO_NOT_FOUND;									// ��������� � ����������� "��������� ���� �� ������"
	}

	// ��������� ���� ������
	
	// ���������� ������ FNT ���������� �����
	FLASH_Read(fnt.array, addr, sizeof(tFNT));								// ��������� ������ FNT

	// ��������� ��� �����
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

	// ��������� ��� �����
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

	*f = FS_FileUseFCS(name, type);											// ��������� ������������� ����� � �������� ������

	// ��������� ���� ������������
	if (*f > -1) {															// ���� � �������� ������ ������������?
		// ����� ���������� � ����� �� ��������������� ��������� FCS
		p_fcs = pFCSArray[*f];												// �������� ��������� �� FCS
		*attr = p_fcs->FNT.Attribute;
		*size = p_fcs->FNT.Size;
	}
	// ��������� ���� �� ������������
	else {
		// ����� ���������� � ����� �� ������ FNT
		*attr = fnt.strc.Attribute;
		*size = fnt.strc.Size;
	}

	return FS_RESULT_OK;															// �� - ���������� � ����� ������� ��������
}


//-----------------------------------------------------------------------------
//			��������� ����� ��������� ��� ������ �����
//-----------------------------------------------------------------------------
s8 FS_Eof(tFile fcs_num) {
	tFCS *p_fcs;															// ��������� �� FCS

	// ��������� �������� ���������� (������ -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// �������� ���������� ��������� �����?
		return EFS_INVALID_FSC;															// ��� - ������� ������ "�������� ���������� �� ��������� �����" (������ -9)
	}

	p_fcs = pFCSArray[fcs_num];												// �������� ��������� �� FCS

	// ��������� ��������� ��������� FCS (������ -1)
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							// ��������� FCS ������� ��� ������ �����?
		return EFS_FCS_NOT_OPENED_READ;															// ��� - ������� ������ "��������� FCS �� ������� ��� ������ �����" (������ -1)
	}

	// ��������� ���-�� ������������� ���� � ������� ���������
	if (p_fcs->RemainSize) {
		return FS_NOT_EOF;
	}
	else {
		return FS_EOF;
	}
}


//-----------------------------------------------------------------------------
//			�������� ������� ������� ��������� ��� ������ �����
//-----------------------------------------------------------------------------
s8 FS_Pos(tFile fcs_num,s32 * pos) {
	tFCS *p_fcs;															// ��������� �� FCS

	// ��������� �������� ���������� (������ -9)
	if (fcs_num < 0 || fcs_num >= MAX_FILES) {								// �������� ���������� ��������� �����?
		return EFS_INVALID_FSC;															// ��� - ������� ������ "�������� ���������� �� ��������� �����" (������ -9)
	}

	p_fcs = pFCSArray[fcs_num];												// �������� ��������� �� FCS

	// ��������� ��������� ��������� FCS (������ -1)
	if (p_fcs->State != FCS_STATE_OPENED_READ) {							// ��������� FCS ������� ��� ������ �����?
		return EFS_FCS_NOT_OPENED_READ;															// ��� - ������� ������ "��������� FCS �� ������� ��� ������ �����" (������ -1)
	}

	// ����� ���-�� ������������� ���� � ������� ���������
	*pos = (p_fcs->FNT.Size - p_fcs->RemainSize);
	return FS_RESULT_OK;
}












//-----------------------------------------
// ���� <!>
//-----------------------------------------

// <!>
// �������� ��������� ��������� FCS
u8 FS_GetFCSState(u8 fcs_num) {

	return pFCSArray[fcs_num]->State;
}

// <!>
// ���������� ��������� FCS
void FS_FCS_Show( u8 fcs_num, void page_buf_view(u8 *buffer, u32 addr) ) {
	tFCS *p_fcs;															// ��������� �� FCS
	u8 *name_buf;
	char ch;
	u8 i;

	p_fcs = pFCSArray[fcs_num];												// �������� ��������� �� FCS

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
// ���������� ��������� �������� �������
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
// ���� <!>
//-----------------------------------------






//=============================================================================
//
//                               End Of File
//
//=============================================================================

