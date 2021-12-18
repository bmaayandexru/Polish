
//****************************************************************************
//
//            NXP LPC1768 SPI & M25P64/M25P128 serial memory
//
//****************************************************************************


//****************************************************************************
// Характеристики микросхем памяти:
//
// M25P64
// Размер полный:	8 МБайт
// Размер сектора:	64 кБайт	(128 секторов, каждый содержит 256 страниц)
// Размер страницы:	256 Байт	(32768 страниц)
// Стирание:
// - вся сразу (команда "Bulk Erase")
// - один сектор (команда "Sector Erase")
// Максимальная частота 75 МГц (режим "Fast Read") (* спец.технология)
//
//
//
// M25P128
// Размер полный:	16 МБайт
// Размер сектора:	256 кБайт	(64 секторов, каждый содержит 1024 страниц)
// Размер страницы:	256 Байт	(65536 страниц)
// Стирание:
// - вся сразу (команда "Bulk Erase")
// - один сектор (команда "Sector Erase")
// Максимальная частота 54 МГц (режим "Fast Read") (* спец.технология)
//
//
//
//
//
//

//****************************************************************************





#include <stdio.h>

#include "msg.h"
#include "Flash.h"


// Flash page size (number of bytes)
#define PAGESIZE 256

// SSPx Status Register Flags
#define TFE     0x01
#define TNF     0x02
#define RNE     0x04
#define RFF     0x08
#define BSY     0x10

// SPI Status Register Flags
#define SPSR_ABRT (1 << 3)			// Slave Abort Flag
#define SPSR_MODF (1 << 4)			// Mode Fault Flag
#define SPSR_ROVR (1 << 5)			// Read Overrun Flag
#define SPSR_WCOL (1 << 6)			// Write Collision Flag
#define SPSR_SPIF (1 << 7)			// Transfer Complete Flag

// FLASH Instruction Code
#define WREN      0x06				// Write Enable
#define WRDI      0x04				// Write Disable
#define RDID      0x9F				// Read Identification
#define RDSR      0x05				// Read Status Register
#define WRSR      0x01				// Write Status Register
#define READ      0x03				// Read Data Bytes
#define FAST_READ 0x0B				// Read Data Bytes at Higher Speed
#define PP        0x02				// Page Program
#define SE        0xD8				// Sector Erase
#define BE        0xC7				// Bulk Erase
#define RES       0xAB				// Read Electronic Signature

// FLASH Status Register Flags
#define FLASH_WIP  (1 << 0)			// Write In Progress Flag
#define FLASH_WEL  (1 << 1)			// Write Enable Latch Flag
#define FLASH_BP0  (1 << 2)			// Block Protect 0 Flag
#define FLASH_BP1  (1 << 3)			// Block Protect 1 Flag
#define FLASH_BP2  (1 << 4)			// Block Protect 2 Flag
// bit5 reservded
// bit6 reservded
#define FLASH_SRWD (1 << 7)			// Status Register Write Disable Flag

#define FLASH_CS0  (1UL << 24)		// P0 PIN24
#define FLASH_CS1  (1UL << 25)		// P0 PIN25
#define FLASH_CS2  (1UL << 26)		// P0 PIN26
#define FLASH_CS3  (1UL << 27)		// P0 PIN27
#define FLASH_CS4  (1UL << 28)		// P0 PIN28

#define DUMMY  0xFF					// Dummy Byte

// FLASH capacities (number of pages)
u32 FLASH_BankCapacity[4] = {0, 0, 0, 0};

// Size of each FLASH bank (number of bytes)
u32 FLASH_BankSize;

// Size of total FLASH (number of bytes)
u32 FLASH_TotalSize;

char str1[2000] =		// sample text buffer 1
"The LPC17xx is an ARM Cortex-M3 based microcontroller for embedded applications \
requiring a high level of integration and low power dissipation. The ARM Cortex-M3 is a \
next generation core that offers system enhancements such as modernized debug \
features and a higher level of support block integration.\n\
High speed versions (LPC1769 and LPC1759) operate at up to a 120 MHz CPU \
frequency. Other versions operate at up to an 100 MHz CPU frequency. The ARM \
Cortex-M3 CPU incorporates a 3-stage pipeline and uses a Harvard architecture with \
separate local instruction and data buses as well as a third bus for peripherals. The ARM \
Cortex-M3 CPU also includes an internal prefetch unit that supports speculative branches.\n\
The peripheral complement of the LPC17xx includes up to 512 kB of flash memory, up to \
64 kB of data memory, Ethernet MAC, a USB interface that can be configured as either \
Host, Device, or OTG, 8 channel general purpose DMA controller, 4 UARTs, 2 CAN \
channels, 2 SSP controllers, SPI interface, 3 I2C interfaces, 2-input plus 2-output \
I2S interface, 8 channel 12-bit ADC, 10-bit DAC, motor control PWM, Quadrature Encoder \
interface, 4 general purpose timers, 6-output general purpose PWM, ultra-low power RTC \
with separate battery supply, and up to 70 general purpose I/O pins.";

char str2[2000] =		// sample text buffer 2
"The Keil MDK-ARM Microcontroller Development Tool Kits (MDK-ARM) generate embedded applications \
for many popular ARM-powered devices. The tools allow engineers to write software programs in \
assembly language or in a high-level language (like C or C++) and to create a complete application \
that can be programmed into a microcontroller or other memory device. The MDK-ARM development tools \
are designed for the professional software developer, but any level of programmer can use them to \
get the most out of the ARM7/9 and Cortex-M microcontroller.\n\
The µVision4 IDE is a window-based software development platform combining a robust editor, \
project manager, and make facility. µVision4 supports all the Keil MDK-ARM tools including C/C++ \
compiler, macro assembler, linker, library manager, and object-HEX converter. Use µVision4 to create \
source files and organize them into a project that defines the target application. µVision4 automatically \
compiles, assembles, and links the application. It provides a single focal point for your development efforts.\
Source files are created by the µVision IDE and are passed to the C or C++ Compiler or Macro Assembler. \
The compiler and assembler process source files and create relocatable object files.\n\
The library manager allows creating object libraries out of the compiled and assembled object modules. \
Libraries are specially formatted ordered program collections of object modules that may be used by the \
linker at a later time. When the linker processes a library, only those modules are used that are necessary \
to create the program.";

char str3[2000];		// general-purpose text buffer

// Временный буфер страницы
u8 PageBuf[PAGESIZE];


static volatile u32 W, W1=10000;//<!>



//---------------------------------------------------------
// FLASH _ Get Bank Number
u8 FLASH_BankNumber(u32 addr);

//---------------------------------------------------------
//  FLASH _ Get Bank Address
u32 FLASH_AddressInBank(u32 addr);



//*****************************************
//              SPI Init
//*****************************************
void SPI_Init(void) {
	/* Enable AHB clock to SPI */
	LPC_SC->POWER_CONTROL = GPIO_POWERED |
                            SPI_POWERED;

	/* Divider SPI clock. Using default divided by 4 */
	LPC_SC->PCLKSEL0 &= ~(0x3 << 16);

	/* SPI Clock Counter Register. 0 for Master mode */
	LPC_SPI->SPCCR = 0;

	/* Pin configure to SPI functions */
	// SSEL functin is not used
	LPC_PINCON->PORT0_0_to_15_FUNCTION   |= PIN15_as_SCK;		// SCK
	LPC_PINCON->PORT0_16_to_31_FUNCTION  |= PIN17_as_MISO |		// MISO
                                           PIN18_as_MOSI;		// MOSI

	/* Internal pull configure */
	LPC_PINCON->PORT0_0_to_15_PULL_MODE  |= PIN15_NOPULL;
	LPC_PINCON->PORT0_16_to_31_PULL_MODE |= PIN17_NOPULL |
                                            PIN18_NOPULL;

	/* Pin configure to SPI Chip Select lines */
	LPC_PINCON->PORT0_16_to_31_FUNCTION  |= PIN24_as_GPIO |		// CS0
                                            PIN25_as_GPIO |		// CS1
                                            PIN26_as_GPIO |		// CS2
                                            PIN27_as_GPIO |		// CS3
                                            PIN28_as_GPIO;		// CS4

	/* SC Internal pull configure */
	LPC_PINCON->PORT0_16_to_31_PULL_MODE |= PIN24_NOPULL |
                                            PIN25_NOPULL |
                                            PIN26_NOPULL |
                                            PIN27_NOPULL |
                                            PIN28_NOPULL;

	/* CS direction */
	LPC_GPIO0->PORT_DIRECTION            |= PIN24_OUTPUT |
                                            PIN25_OUTPUT |
                                            PIN26_OUTPUT |
                                            PIN27_OUTPUT |
                                            PIN28_OUTPUT;

	/* Set CS (inactive state) */
	LPC_GPIO0->PORT_SET                  |= FLASH_CS0 |
                                            FLASH_CS1 |
                                            FLASH_CS2 |
                                            FLASH_CS3 |
                                            FLASH_CS4;

	/* SPI Cotrol - 8 bits, CPOL=0, CPHA=0, Master mode, SPI Int enable */
	LPC_SPI->SPCR = (1 << 7);
}


void SSP0_Init(void) {
	LPC_SC->PCONP       |= (1 << 21);				/* Enable power to SSPI0 block */

	/* SSEL is GPIO, output set to high. */
	LPC_GPIO0->FIODIR   |=  (1<<16);				/* P0.16 is output             */
	LPC_GPIO0->FIOPIN   |=  (1<<16);				/* set P0.16 high (SSEL inact.)*/
	LPC_PINCON->PINSEL1 &= ~(3<<0);					/* P0.16 SSEL (used as GPIO)   */

	/* SCK, MISO, MOSI are SSP pins. */
	LPC_PINCON->PINSEL0 &= ~(3UL<<30);				/* P0.15 cleared               */
	LPC_PINCON->PINSEL0 |=  (2UL<<30);				/* P0.15 SCK0                  */
	LPC_PINCON->PINSEL1 &= ~((3<<2) | (3<<4));		/* P0.17, P0.18 cleared        */
	LPC_PINCON->PINSEL1 |=  ((2<<2) | (2<<4));		/* P0.17 MISO0, P0.18 MOSI0    */

	LPC_SC->PCLKSEL1    &= ~(3<<10);				/* PCLKSP0 = CCLK/4 ( 25MHz)   */
	LPC_SC->PCLKSEL1    |=  (1<<10);				/* PCLKSP0 = CCLK   (100MHz)   */

	LPC_SSP0->CPSR       = 10;						/* 100MHz / 10 = 10MHz         */
													/* maximum of 18MHz is possible*/    
	LPC_SSP0->CR0        = 0x0007;					/* 8Bit, SPI format, CPOL=0, CPHA=0 */
	LPC_SSP0->CR1        = 0x0002;					/* SSP0 enable, master         */

	/* Pin configure to SPI Chip Select lines */
	LPC_PINCON->PORT0_16_to_31_FUNCTION  |= PIN24_as_GPIO |		// CS0
                                            PIN25_as_GPIO |		// CS1
                                            PIN26_as_GPIO |		// CS2
                                            PIN27_as_GPIO |		// CS3
                                            PIN28_as_GPIO;		// CS4

	/* SC Internal pull configure */
	LPC_PINCON->PORT0_16_to_31_PULL_MODE |= PIN24_NOPULL |
                                            PIN25_NOPULL |
                                            PIN26_NOPULL |
                                            PIN27_NOPULL |
                                            PIN28_NOPULL;

	/* CS direction */
	LPC_GPIO0->PORT_DIRECTION            |= PIN24_OUTPUT |
                                            PIN25_OUTPUT |
                                            PIN26_OUTPUT |
                                            PIN27_OUTPUT |
                                            PIN28_OUTPUT;

	/* Set CS (inactive state) */
	LPC_GPIO0->PORT_SET                  |= FLASH_CS0 |
                                            FLASH_CS1 |
                                            FLASH_CS2 |
                                            FLASH_CS3 |
                                            FLASH_CS4;
}


//*****************************************
//        SSP0 Get Status Flag
//*****************************************
u8 SSP0_GetStatusFlag(u8 flag) {
	return (LPC_SSP0->SR & flag);
}

//*****************************************
//          SSP0 Send Byte
//*****************************************
u8 SSP0_SendByte(u8 b) {
	u8 result;
	LPC_SSP0->DR = b;
	while ( SSP0_GetStatusFlag(BSY) );							// Wait for transfer to finish
	result = LPC_SSP0->DR;
	return (result);											// Return received value
}


//*********************************************************
//
//                      SPI FLASH
//
//*********************************************************

//---------------------------------------------------------
//                     Bank Select
//---------------------------------------------------------
// Select Bank - Chip Select to low
void FLASH_BankSelect(u8 bank_num) {
	switch (bank_num) {
		case 0: // Select Bank 0 - CS0 low
			LPC_GPIO0->PORT_CLEAR |= FLASH_CS0;
			break;
		case 1: // Select Bank 1 - CS1 low
			LPC_GPIO0->PORT_CLEAR |= FLASH_CS1;
			break;
		case 2: // Select Bank 2 - CS2 low
			LPC_GPIO0->PORT_CLEAR |= FLASH_CS2;
			break;
		case 3: // Select Bank 3 - CS3 low
			LPC_GPIO0->PORT_CLEAR |= FLASH_CS3;
			break;
		case 4: // Select Bank 4 - CS4 low
			LPC_GPIO0->PORT_CLEAR |= FLASH_CS4;
			break;
	}
}


//---------------------------------------------------------
//                    Bank Deselect
//---------------------------------------------------------
// Deselect Bank - Chip Select to high
void FLASH_BankDeselect(u8 bank_num) {
	switch (bank_num) {
		case 0: // Deselect Bank 0 - CS0 high
			LPC_GPIO0->PORT_SET |= FLASH_CS0;
			break;
		case 1: // Deselect Bank 1 - CS1 high
			LPC_GPIO0->PORT_SET |= FLASH_CS1;
			break;
		case 2: // Deselect Bank 2 - CS2 high
			LPC_GPIO0->PORT_SET |= FLASH_CS2;
			break;
		case 3: // Deselect Bank 3 - CS3 high
			LPC_GPIO0->PORT_SET |= FLASH_CS3;
			break;
		case 4: // Deselect Bank 4 - CS4 high
			LPC_GPIO0->PORT_SET |= FLASH_CS4;
			break;
	}
}


//---------------------------------------------------------
//                 FLASH _ SPI Send Byte
//---------------------------------------------------------
// Отправить 1 байт в SPI флэш-памяти,
// Функция возвращает принятый из SPI флэш-памяти 1 байт
u8 FLASH_SendByte(u8 b) {
	return SSP0_SendByte(b);									// Отправить байт в SPI флэш-памяти
}


//---------------------------------------------------------
//                 FLASH _ SPI Receive Byte
//---------------------------------------------------------
// Принять 1 байт из SPI флэш-памяти, для этого передается фиктивный байт
// Функция возвращает принятый байт
u8 FLASH_ReceiveByte(void) {
	return SSP0_SendByte(DUMMY);								// Отправить фиктивный байт в SPI флэш-памяти
}


//---------------------------------------------------------
//                 FLASH _ Get Сapacity
//---------------------------------------------------------
// Получить емкость заданного банка флэш-памяти (количество страниц)
u32 FLASH_GetBankCapacity(u8 bank_num) {						// (bank_num = номер банка флэш-памяти, 0..3)
	u8 tmp;
	u32 capacity;

	FLASH_BankSelect(bank_num);									// Выбрать банк
	FLASH_SendByte(RDID);										// Отправить команду "Read Identification"
	tmp = FLASH_ReceiveByte();									// Принять первый байт - игнорировать его
	tmp = FLASH_ReceiveByte();									// Принять второй байт - игнорировать его
	tmp = FLASH_ReceiveByte();									// Принять третитий байт = это ID выбранного банка
	FLASH_BankDeselect(bank_num);								// Снять выбор банка
	if (tmp == 0x17) {											// Если ID = 17h (тип флэш-памяти M25P64)
		capacity = 32768;										//   значит емкость банка 32768 страниц
	}
	else if (tmp == 0x18) {										// Если ID = 18h (тип флэш-памяти M25P128)
		capacity = 65536;						//   значит емкость банка 65536 страниц
	}
	else {
		capacity = 0;											// Иначе - считаем, что выбранный банк отсутствует (емкость 0 страниц)
	}
	//Msg("b%d t%x c%d\r\n",bank_num,tmp,capacity);
	return capacity;
}


//---------------------------------------------------------
//                     FLASH _ Init
//---------------------------------------------------------
// Инициализация флэш-памяти
// Здесь проверяется яналичие и емкость каждго банка,
//   вычисляется размер каждого банка и общий размер флэш-памяти (количество байт)
void FLASH_Init(void) {
	u32 tmp;

	//SPI_Init();
	SSP0_Init();

	FLASH_BankCapacity[0] = FLASH_GetBankCapacity(0);
	FLASH_BankCapacity[1] = FLASH_GetBankCapacity(1);
	FLASH_BankCapacity[2] = FLASH_GetBankCapacity(2);
	FLASH_BankCapacity[3] = FLASH_GetBankCapacity(3);

	FLASH_BankSize = FLASH_BankCapacity[1] * PAGESIZE;			// Сохоранить размер банка (количество байт)

	tmp  = FLASH_BankCapacity[0];
	tmp += FLASH_BankCapacity[1];
	tmp += FLASH_BankCapacity[2];
	tmp += FLASH_BankCapacity[3];

	FLASH_TotalSize = tmp * PAGESIZE;							// Сохранить общий размер флэш-памяти (количество байт)
}


//---------------------------------------------------------
//                FLASH _ Get Total Size
//---------------------------------------------------------
// Функция возвращает общий размер флэш-памяти (количество байт)
u32 FLASH_GetTotalSize(void) {
	return FLASH_TotalSize;
}


//---------------------------------------------------------
//                 FLASH _ Read Status Register
//---------------------------------------------------------
// Функция читает и возвращает регистр статуса заданного банка флэш-памяти
u8 FLASH_ReadStatusRegister(u8 bank_num) {
	u8 result;

	FLASH_BankSelect(bank_num);									// Выбрать банк
	FLASH_SendByte(RDSR);										// Отправить команду "Read Status Register"
	result = FLASH_ReceiveByte();								// Принять ответный байт
	FLASH_BankDeselect(bank_num);								// Снять выбор банка

	return result;
}


//---------------------------------------------------------
//                 FLASH _ Wait Writing
//---------------------------------------------------------
// Ожидание завершения записи заданного банка флэш-памяти
// Функция возвращает результат ожидания:
//   1 - OK (ожидание записи завершилось успешно)
//   0 - Ошибка (ожидание записи прервано по тайм-ауту)
u8 FLASH_WaitWriting(u8 bank_num) {
//	u32 i = 0;
	u8 result = 1;

	FLASH_BankSelect(bank_num);									// Выбрать банк
	FLASH_SendByte(RDSR);												// Отправить команду "Read Status Register"
	while ( FLASH_ReceiveByte() & FLASH_WIP ) {	// Выполняется запись - ожидаем завершения
//		if ( i++ > 250 ) {											// Считаем циклы ожидания - для избежания зацикливания
//			result = 0;
//			break;
//		}
	}
	FLASH_BankDeselect(bank_num);								// Снять выбор банка

	return result;
}


//---------------------------------------------------------
//               FLASH _ Wait Bulk Erasing
//---------------------------------------------------------
u8 FLASH_WaitBulkErasing(u8 bank_num) {
//	u32 i = 0;
	u8 result = 0;

	FLASH_BankSelect(bank_num);									// Select Bank
	FLASH_SendByte(RDSR);										// Send "Read Status Register" instruction
	while ( FLASH_ReceiveByte() & FLASH_WIP ) {					// Write in progress
//		if ( i++ > 250 ) {										// Считаем циклы ожидания - для избежания зацикливания
//			result = 1;
//			break;
//		}
	}
	FLASH_BankDeselect(bank_num);								// Deselect Bank

	return result;
}


//---------------------------------------------------------
//                 FLASH _ Sector Erase
//---------------------------------------------------------
u8 FLASH_SectorErase(u32 addr) {
	u8 bank_num;
	u32 addr_in_bank;

	bank_num = FLASH_BankNumber(addr);
	addr_in_bank = FLASH_AddressInBank(addr);

	FLASH_BankSelect(bank_num);									// Select Bank
	FLASH_SendByte(WREN);										// Send "Write Enable" instruction
	FLASH_BankDeselect(bank_num);								// Deselect Bank

	FLASH_BankSelect(bank_num);									// Select Bank
	FLASH_SendByte(SE);											// Send "Sector Erase" instruction
	FLASH_SendByte((u8)(addr_in_bank >> 16));					// Send Write Address high byte
	FLASH_SendByte((u8)(addr_in_bank >> 8));					// Send Write Address medium byte
	FLASH_SendByte((u8)addr_in_bank);							// Send Write Address low byte
	FLASH_BankDeselect(bank_num);								// Deselect Bank

	FLASH_BankSelect(bank_num);									// Select Bank
	FLASH_SendByte(RDSR);										// Send "Read Status Register" instruction
	while ( FLASH_ReceiveByte() & FLASH_WIP );					// Write in progress
	FLASH_BankDeselect(bank_num);								// Deselect Bank
Msg("complete SectorErase\r\n");//<!>
SMsg();//<!>
W=W1;while(W--);//<!>

	return 0;
}


//---------------------------------------------------------
//                  FLASH _ Bulk Erase
//---------------------------------------------------------
u32 FLASH_BulkErase(void) {
	u8 i;
	u32 ret[4] = {55,55,55,55};

	for (i=0; i<4; i++) {
		Msg("Bulk erasing bank %d...\r\n",i); SMsg();
		if ( FLASH_BankCapacity[i] ) {
			FLASH_BankSelect(i);								// Select Bank
			FLASH_SendByte(WREN);								// Send "Write Enable" instruction
			FLASH_BankDeselect(i);								// Deselect Bank

			FLASH_BankSelect(i);								// Select Bank
			FLASH_SendByte(BE);									// Send "Bulk Erase" instruction
			FLASH_BankDeselect(i);								// Deselect Bank
		}
	}

	for (i=0; i<4; i++) {
		Msg("Wait erasing bank %d...\r\n",i); SMsg();
		if ( FLASH_BankCapacity[i] )
			ret[i] = FLASH_WaitBulkErasing(i);					// Wait for Flash erasing
		Msg("Complete bank %d.\r\n",i); SMsg();
	}

	return ret[0];
}


/*
 Full memory is 4x M25P64:
 0000000bbpppppppppppppppxxxxxxxx - "bb" is bank number, "ppppppppppppppp" is page number
 0000000bbsssssssxxxxxxxxxxxxxxxx - "bb" is bank number, "sssssss" is sector number
 0000000bbaaaaaaaaaaaaaaaaaaaaaaa - "bb" is bank number, "aaaaaaaaaaaaaaaaaaaaaaa" is address in bank

 Full memory is 4x M25P128:
 000000bbppppppppppppppppxxxxxxxx - "bb" is bank number, "pppppppppppppppp" is page number
 000000bbssssssxxxxxxxxxxxxxxxxxx - "bb" is bank number, "ssssss" is sector number
 000000bbaaaaaaaaaaaaaaaaaaaaaaaa - "bb" is bank number, "aaaaaaaaaaaaaaaaaaaaaaaa" is address in bank
*/


//---------------------------------------------------------
//                 FLASH _ Get Bank Number
//---------------------------------------------------------
u8 FLASH_BankNumber(u32 addr) {
	if (FLASH_BankCapacity[0] == 32768) {						// Flash type is M25P64
		addr >>= 23;
	}
	else {														// Flash type is M25P128
		addr >>= 24;
	}

	return (u8)(addr);
}


//---------------------------------------------------------
//                  FLASH _ Get Bank Address
//---------------------------------------------------------
u32 FLASH_AddressInBank(u32 addr) {
	if (FLASH_BankCapacity[0] == 32768) {						// If Flash type is M25P64
		addr &= 0x007FFFFF;										// then Flash address is 23 low bits of full address
	}
	else {														// If Flash type is M25P64
		addr &= 0x00FFFFFF;										// and Flash number is 24 low bits of full address
	}

	return addr;
}


//---------------------------------------------------------
//                 FLASH _ Get Page Address
//---------------------------------------------------------
u32 FLASH_PageAddress(u32 addr) {
	return addr &= 0x000000FF;									// Page address is 8 low bits of address
}																// (for page size of 256 bytes)


//---------------------------------------------------------
//              FLASH _ Записать 1 байт
//---------------------------------------------------------
// Функция возвращает результат записи:
//   0 - OK (запись завершилась успешно)
//   1 - Ошибка (ожидание записи прервано по тайм-ауту)
u8 FLASH_WriteByte(u32 addr, u8 b) {
	u8 bank_num;
	u32 addr_in_bank;

	bank_num = FLASH_BankNumber(addr);
	addr_in_bank = FLASH_AddressInBank(addr);

	FLASH_BankSelect(bank_num);									// Select Bank
	FLASH_SendByte(WREN);										// Send "Write Enable" instruction
	FLASH_BankDeselect(bank_num);								// Deselect Bank

	FLASH_BankSelect(bank_num);									// Select Bank
	FLASH_SendByte(PP);											// Send "Page Program" instruction
	FLASH_SendByte((u8)(addr_in_bank >> 16));					// Send Write Address high byte
	FLASH_SendByte((u8)(addr_in_bank >> 8));					// Send Write Address medium byte
	FLASH_SendByte((u8)addr_in_bank);							// Send Write Address low byte
	FLASH_SendByte(b);											// Send data byte
	FLASH_BankDeselect(bank_num);								// Deselect Bank

	return FLASH_WaitWriting(bank_num);							// Wait for Flash writing
}


//---------------------------------------------------------
//              FLASH _ Прочитать 1 байт
//---------------------------------------------------------
u8 FLASH_ReadByte(u32 addr) {
	u8 bank_num;
	u32 addr_in_bank;
	u8 b;

	bank_num = FLASH_BankNumber(addr);
	addr_in_bank = FLASH_AddressInBank(addr);
	FLASH_BankSelect(bank_num);									// Select Bank
	FLASH_SendByte(READ);										// Send "Read Data Bytes" instruction
	FLASH_SendByte((u8)(addr_in_bank >> 16));					// Send Read Address high byte
	FLASH_SendByte((u8)(addr_in_bank >> 8));					// Send Read Address medium byte
	FLASH_SendByte((u8)addr_in_bank);							// Send Read Address low byte
	b = FLASH_ReceiveByte();									// Read data byte
	FLASH_BankDeselect(bank_num);								// Deselect Bank

	return b;
}


//---------------------------------------------------------
//                  FLASH _ Page Write
//---------------------------------------------------------
// Функция возвращает результат ожидания записи страницы:
//   1 - OK (ожидание записи завершилось успешно)
//   0 - Ошибка (ожидание записи прервано по тайм-ауту)
u8 FLASH_PageWrite(u32 addr, const u8 *buffer, u16 size) {
	u8 bank_num;
	u32 addr_in_bank;

	bank_num = FLASH_BankNumber(addr);
	addr_in_bank = FLASH_AddressInBank(addr);

	FLASH_BankSelect(bank_num);									// Select Bank
	FLASH_SendByte(WREN);										// Send "Write Enable" instruction
	FLASH_BankDeselect(bank_num);								// Deselect Bank

	FLASH_BankSelect(bank_num);									// Select Bank
	FLASH_SendByte(PP);											// Send "Page Program" instruction
	FLASH_SendByte((u8)(addr_in_bank >> 16));					// Send Write Address high byte
	FLASH_SendByte((u8)(addr_in_bank >> 8));					// Send Write Address medium byte
	FLASH_SendByte((u8)addr_in_bank);							// Send Write Address low byte
	while(size--) {												// While there is data to be written on FLASH
		FLASH_SendByte(*buffer++);								// Send next byte
	}
	FLASH_BankDeselect(bank_num);								// Deselect Bank

	return FLASH_WaitWriting(bank_num);							// Wait for Flash writing
}


//---------------------------------------------------------
//                 FLASH _ Write
//---------------------------------------------------------
u8 FLASH_Write(u32 addr, const u8 *buffer, u32 size) {
	u8 first_size;												// Size of first page
	u8 last_size;												// Size of last page
	u32 full_page_count;										// Count of full pages
	u8 result = 1;

 	if (!(u8)addr) {											// Size of first page
		first_size = 0;
	}
	else {
		first_size = 256 - (u8)addr;
	}
	if (first_size > size) {
		first_size = size;
	}
	full_page_count = (size - first_size) / 256;				// Count of full pages
	last_size = (size - first_size) % 256;						// Size of last page

	// Write first page
	if (first_size) {
		result = FLASH_PageWrite(addr, buffer, first_size);
		buffer += first_size;
		addr += first_size;
	}

	// Write full pages
	while (result && full_page_count--) {
		result = FLASH_PageWrite(addr, buffer, 256);
		buffer += 256;
		addr += 256;
	}

	// Write last page
	if (result && last_size) {
		result = FLASH_PageWrite(addr, buffer, last_size);
	}

	return result;
}


//---------------------------------------------------------
//                  FLASH _ Bank Read
//---------------------------------------------------------
void FLASH_BankRead(u8 *buffer, u32 addr, u32 size) {
	u8 bank_num;
	u32 addr_in_bank;

	bank_num = FLASH_BankNumber(addr);
	addr_in_bank = FLASH_AddressInBank(addr);

	FLASH_BankSelect(bank_num);									// Select Bank
	FLASH_SendByte(READ);										// Send "Read Data Bytes" instruction
	FLASH_SendByte((u8)(addr_in_bank >> 16));					// Send Read Address high byte
	FLASH_SendByte((u8)(addr_in_bank >> 8));					// Send Read Address medium byte
	FLASH_SendByte((u8)addr_in_bank);							// Send Read Address low byte
	while(size--) {												// While there is data to be read from FLASH
		*buffer++ = FLASH_ReceiveByte();						// Read next byte
	}
	FLASH_BankDeselect(bank_num);								// Deselect Bank
}


//---------------------------------------------------------
//                 FLASH _ Read
//---------------------------------------------------------
void FLASH_Read(u8 *buffer, u32 addr, u32 size) {
	u32 first_size;												// Size of first bank
	u32 last_size;												// Size of last bank
	u8 full_bank_count;											// Count of full banks

	first_size = FLASH_BankSize - FLASH_AddressInBank(addr);	// Size of first bank
	if (first_size == FLASH_BankSize) {
		first_size = 0;
	}
	if (first_size > size) {
		first_size = size;
	}
	full_bank_count = (size - first_size) / FLASH_BankSize;		// Count of full banks
	last_size = (size - first_size) % FLASH_BankSize;			// Size of last bank

	if (first_size) {
		FLASH_BankRead(buffer, addr, first_size);				// Write first bank
		buffer += first_size;
		addr += first_size;
	}

	while (full_bank_count--) {									// Write full banks
		FLASH_BankRead(buffer, addr, FLASH_BankSize);
		buffer += FLASH_BankSize;
		addr += FLASH_BankSize;
	}

	if (last_size) {
		FLASH_BankRead(buffer, addr, last_size);				// Write last bank
	}
}




//=========================================================
//   Test
//=========================================================
void FLASH_test(void) {

	// Записать текст на границе двух флэшэк (сейчас запаяны M25P128)
	FLASH_Write(32768*256 - 100, (u8 *)str1, 1000);
	FLASH_Write(1010, (u8 *)str2, 1000);

	// Прочитать содержимое на границе двух флэшек
	FLASH_Read((u8 *)str3, 32768*256 - 200, 1000);
}

//---------------------------------------------------------
//                 FLASH _ Get Bank ID
//---------------------------------------------------------
// Получить ID заданного банка флэш-памяти
u8 FLASH_GetBankID(u8 bank_num) {											// (bank_num = номер банка флэш-памяти, 0..3)
	u8 b;

	FLASH_BankSelect(bank_num);												// Выбрать банк
	FLASH_SendByte(RDID);													// Отправить команду "Read Identification"
	b = FLASH_ReceiveByte();												// Принять первый байт - игнорировать его
	b = FLASH_ReceiveByte();												// Принять второй байт - игнорировать его
	b = FLASH_ReceiveByte();												// Принять третитий байт = это ID выбранного банка
	FLASH_BankDeselect(bank_num);											// Снять выбор банка

	return b;
}





/******************************************************************************
**                            End Of File
******************************************************************************/
