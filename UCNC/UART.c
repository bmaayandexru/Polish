//#include <RTL.h>
#include "Defs.h"
// импорт типов притета, битности и стоп-бита
#include "lpc17xx_uart.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_pinsel.h"

// ОТЛАДКА !!! ПОТОМ УБРАТЬ !!!
// для отладки переполнения буфера
//#include "VirtualPins.h"

#include "UART.h"
#include "ti.h"
#include "msg.h"



// порт 2 для сигналов RE и DE
#define DE_PORT LPC_GPIO2 
#define RE_PORT LPC_GPIO2 

// маски для пинов RE и DE
#define DE_PIN_MASK (1L<<2)
#define RE_PIN_MASK (1L<<3)


/* buffer size definition */
#define UART_RING_BUFSIZE 512
//#define UART_RING_BUFSIZE 1024

/* Buf mask */
#define __BUF_MASK (UART_RING_BUFSIZE-1)
/* Check buf is full or not */
#define __BUF_IS_FULL(head, tail) ((tail&__BUF_MASK)==((head+1)&__BUF_MASK))
/* Check buf will be full in next receiving or not */
#define __BUF_WILL_FULL(head, tail) ((tail&__BUF_MASK)==((head+2)&__BUF_MASK))
/* Check buf is empty */
#define __BUF_IS_EMPTY(head, tail) ((head&__BUF_MASK)==(tail&__BUF_MASK))
/* Reset buf */
#define __BUF_RESET(bufidx)	(bufidx=0)
#define __BUF_INCR(bufidx)	(bufidx=(bufidx+1)&__BUF_MASK)

/** @brief UART Ring buffer structure */
typedef struct
{
    __IO uint32_t tx_head;                /*!< UART Tx ring buffer head index */
    __IO uint32_t tx_tail;                /*!< UART Tx ring buffer tail index */
    __IO uint32_t rx_head;                /*!< UART Rx ring buffer head index */
    __IO uint32_t rx_tail;                /*!< UART Rx ring buffer tail index */
    __IO uint8_t  tx[UART_RING_BUFSIZE];  /*!< UART Tx data ring buffer */
    __IO uint8_t  rx[UART_RING_BUFSIZE];  /*!< UART Rx data ring buffer */
	__IO uint8_t  dup;			// дуплекс
	__IO uint16_t  txfree;		// свободное место в tx буфере
	__IO uint8_t  rxdata;		// количество данных в буфере приема
} UART_RING_BUFFER_T;

// UART Ring buffers
UART_RING_BUFFER_T rb0,rb1;

// Current Tx Interrupt enable state
__IO FlagStatus TxIntStat0,TxIntStat1;

/* Interrupt service routines */
// For UART0
void UART0_IRQHandler(void);
void UART0_IntErr(u8 bLSErrType);
void UART0_IntTransmit(void);
void UART0_IntReceive(void);

// For UART1
void UART1_IRQHandler(void);
void UART1_IntErr(u8 bLSErrType);
void UART1_IntTransmit(void);
void UART1_IntReceive(void);


void UART0_IRQHandler(void)
{
	uint32_t intsrc, tmp, tmp1;
//	static uint32_t f=0;
	/* Determine the interrupt source */
	intsrc = UART_GetIntId(LPC_UART0); // чтение регистра IRR соответсвующего UARTa
	tmp = intsrc & UART_IIR_INTID_MASK/*0000 1110*/;// маскирование 1,2 и 3 битов
	
	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS/*0000 0110*/){
		// Check line status
		tmp1 = UART_GetLineStatus(LPC_UART0); // чтение регистра LSR
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) {
				UART0_IntErr(tmp1);
		}
	}
	
	// Receive Data Available or Character time-out
	// проверка значения регистра IRR на присутствие символа
	// или Character time-out 
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
		  
			UART0_IntReceive();
		
	}
	// Transmit Holding Empty
	if (tmp == UART_IIR_INTID_THRE){
		  
			UART0_IntTransmit();
	}
	
	// исследование прерывания TIMER0_IRQn
	// U0T0p = 1 если T0 в режиме ожидания
//	if (!U0T0p) U0T0p = NVIC_GetPendingIRQ (TIMER0_IRQn);
	
}


void UART1_IRQHandler(void)
{
	uint32_t intsrc, tmp, tmp1;
	/* Determine the interrupt source */	

	intsrc = UART_GetIntId((LPC_UART_TypeDef *)LPC_UART1); // чтение регистра IRR соответсвующего UARTa
	tmp = intsrc & UART_IIR_INTID_MASK/*0000 1110*/;// маскирование 1,2 и 3 битов
	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS/*0000 0110*/){
		// Check line status
		tmp1 = UART_GetLineStatus((LPC_UART_TypeDef *)LPC_UART1); // чтение регистра LSR !!!!Здесь была ошибка
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) {
				UART1_IntErr(tmp1);
		}
	}
	// Receive Data Available or Character time-out
	// проверка значения регистра IRR на присутствие символа
	// или Character time-out 
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
			//Msg("r");
			UART1_IntReceive();
	}
	// Transmit Holding Empty
	if (tmp == UART_IIR_INTID_THRE){
			UART1_IntTransmit();
	}
	
// исследование прерывания TIMER0_IRQn
//	U1T0p = 1 если T0 в режиме ожидания
//	if (!U1T0p) U1T0p = NVIC_GetPendingIRQ (TIMER0_IRQn);
}

void UART0_IntErr(u8 bLSErrType){
/*
	uint8_t test;
	// Loop forever
	while (1){
		// For testing purpose
		test = bLSErrType;
	}
*/
}

void UART1_IntErr(u8 bLSErrType){
/*
	uint8_t test;
	// Loop forever
	while (1){
		// For testing purpose
		test = bLSErrType;
	}
*/
}

// обработчик прерываний по передаче по UART0
void UART0_IntTransmit(void){
    // Disable THRE interrupt
		// запрещаем прерывания
		LPC_UART0->IER &= (~UART_IER_THREINT_EN) & UART_IER_BITMASK;

	/* Wait for FIFO buffer empty, transfer UART_TX_FIFO_SIZE bytes
	 * of data or break whenever ring buffers are empty */
	/* Wait until THR empty */
	// Ждем освобождения регистра THR
		while(!(LPC_UART0->LSR & UART_LSR_TEMT));
	
	// проверяем наличие данных в выходном буфере
		if (!__BUF_IS_EMPTY(rb0.tx_head,rb0.tx_tail))
    {
        /* Move a piece of data into the transmit FIFO */
			// передаем первый байт
    	if (UART0_Send(rb0.tx[rb0.tx_tail])){
	        /* Update transmit ring FIFO tail pointer */
	        __BUF_INCR(rb0.tx_tail);
					rb0.txfree++;
			} 
    }

    /* If there is no more data to send, disable the transmit
       interrupt - else enable it or keep it enabled */
		if (__BUF_IS_EMPTY(rb0.tx_head, rb0.tx_tail)) {
			// буфер пуст 
			// останавливаем прерывания передачи
			LPC_UART0->IER &= (~UART_IER_THREINT_EN) & UART_IER_BITMASK;
    	// Reset Tx Interrupt state
			// сбрасываем флаг прерывания передачи
    	TxIntStat0 = RESET;
    }
    else{
			// буфер не пуст
      // Set Tx Interrupt state
			// устанавливаем флаг прерывания передачи
			TxIntStat0 = SET;
			// разрешаем прерывания передачи
			LPC_UART0->IER |= UART_IER_THREINT_EN;
    }
		
}


void UART1_IntTransmit(void){
		// Disable THRE interrupt
		// замена UART_IntConfig через регистры
		((LPC_UART1_TypeDef *)LPC_UART1)->IER &= (~UART_IER_THREINT_EN) & UART1_IER_BITMASK;
		/* Wait for FIFO buffer empty, transfer UART_TX_FIFO_SIZE bytes
		* of data or break whenever ring buffers are empty */
		/* Wait until THR empty */
		// Ждем освобождения регистра THR
		// UART_CheckBusy через порт
		while(!(((LPC_UART_TypeDef *)LPC_UART1)->LSR & UART_LSR_TEMT));
		// если полудуплекс занимаем линию
//		if (rb1.dup == HALF_DUPLEX) BusyUartLine();
		if (rb1.dup == HALF_DUPLEX) DefBusyUartLine; // т к define
		
		// проверяем наличие данных в выходном буфере
		if (!__BUF_IS_EMPTY(rb1.tx_head,rb1.tx_tail))
    {
        /* Move a piece of data into the transmit FIFO */
    	if (UART1_Send(rb1.tx[rb1.tx_tail])){
	        /* Update transmit ring FIFO tail pointer */
	      __BUF_INCR(rb1.tx_tail);
				rb1.txfree++;
    	} 
    }
    /* If there is no more data to send, disable the transmit
       interrupt - else enable it or keep it enabled */
		if (__BUF_IS_EMPTY(rb1.tx_head, rb1.tx_tail)) {
			// UART_IntConfig DISABLE через регистры
			((LPC_UART1_TypeDef *)LPC_UART1)->IER &= (~UART_IER_THREINT_EN) & UART1_IER_BITMASK;
			// Reset Tx Interrupt state
    	TxIntStat1 = RESET;
			if (rb1.dup == HALF_DUPLEX) StartDelay();
    }
    else{
      // Set Tx Interrupt state
			TxIntStat1 = SET;
			// UART_IntConfig ENABLE через регистры
			((LPC_UART1_TypeDef *)LPC_UART1)->IER |= UART_IER_THREINT_EN;
    }
}


void UART0_IntReceive(void){
	uint8_t tmpc;
	uint32_t rLen;

	while(1){
		// Call UART read function in UART driver
		rLen = UART_Receive((LPC_UART_TypeDef *)LPC_UART0, &tmpc, 1, NONE_BLOCKING);
		//				^ можно ускорить. надо
		// If data received
		if (rLen){
			// проверка на свободное место в буфере
			// если места нет символ теряется
			if (!__BUF_IS_FULL(rb0.rx_head,rb0.rx_tail)){
				rb0.rx[rb0.rx_head] = tmpc;
				__BUF_INCR(rb0.rx_head);
				rb0.rxdata++;
			}
		}
		// no more data
		else {
			break;
		}
	}
}

void UART1_IntReceive(void){
	uint8_t tmpc;
	uint32_t rLen;

	while(1){
		// Call UART read function in UART driver
		rLen = UART_Receive((LPC_UART_TypeDef *)LPC_UART1, &tmpc, 1, NONE_BLOCKING);
		//			^ можно ускорить. надо
		// If data received
		if (rLen){
			/* Check if buffer is more space
			 * If no more space, remaining character will be trimmed out
			 */
			// проверка на свободное место в буфере
			// если места нет символ теряется
			if (!__BUF_IS_FULL(rb1.rx_head,rb1.rx_tail)){
				rb1.rx[rb1.rx_head] = tmpc;
				__BUF_INCR(rb1.rx_head);
				rb1.rxdata++;
			}
		}
		// no more data
		else {
			break;
		}
	}
}

BOOL UARTx_Init(u8 num, 
				UART_DUPLEX_Type dup,	
				u32 baud_rate,
				UART_PARITY_Type par,
				UART_DATABIT_Type dbits,
				UART_STOPBIT_Type stopbits)
{
	// UART Configuration structure variable
	UART_CFG_Type UARTConfigStruct;

	// UART FIFO configuration Struct variable
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;

	// Pin configuration for UART
	PINSEL_CFG_Type PinCfg;

	// RS485 configuration
//	UART1_RS485_CTRLCFG_Type rs485cfg;
///*	
	LPC_UART_TypeDef *UARTPort;
	UART_RING_BUFFER_T * rb;

	switch (num) {
		case 0:
			PinCfg.Funcnum = 1;
			PinCfg.OpenDrain = 0;
			PinCfg.Pinmode = 0;
			PinCfg.Pinnum = 2;
			PinCfg.Portnum = 0;
			PINSEL_ConfigPin(&PinCfg);
			PinCfg.Pinnum = 3;
			PINSEL_ConfigPin(&PinCfg);
			UARTPort = LPC_UART0;
			rb = &rb0;
			break;
		case 1:
			// RS 232
			PinCfg.Funcnum = 2;
			PinCfg.OpenDrain = 0;
			PinCfg.Pinmode = 0;
			PinCfg.Portnum = 2;
			PinCfg.Pinnum = 0;
			PINSEL_ConfigPin(&PinCfg);
			PinCfg.Pinnum = 1;
			PINSEL_ConfigPin(&PinCfg);
			UARTPort = (LPC_UART_TypeDef*)LPC_UART1;
			rb = &rb1;
			break;
		default: return FALSE;
	}// switch (num)


	UARTConfigStruct.Baud_rate = baud_rate;
	UARTConfigStruct.Databits = dbits;
	UARTConfigStruct.Parity = par;
	UARTConfigStruct.Stopbits = stopbits;

	// Initialize UART0 peripheral with given to corresponding parameter
	UART_Init(UARTPort, &UARTConfigStruct);


//	 Initialize FIFOConfigStruct to default state:
//	 * 				- FIFO_DMAMode = DISABLE
//	 * 				- FIFO_Level = UART_FIFO_TRGLEV0
//	 * 				- FIFO_ResetRxBuf = ENABLE
//	 * 				- FIFO_ResetTxBuf = ENABLE
//	 * 				- FIFO_State = ENABLE
	
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
	// Initialize FIFO for UART0 peripheral
	UART_FIFOConfig(UARTPort, &UARTFIFOConfigStruct);
  
	// Enable UART Transmit
	UART_TxCmd(UARTPort, ENABLE);

    // Enable UART Rx interrupt 
	UART_IntConfig(UARTPort, UART_INTCFG_RBR, ENABLE);
	// Enable UART line status interrupt 
	UART_IntConfig(UARTPort, UART_INTCFG_RLS, ENABLE);


//	 * Do not enable transmit interrupt here, since it is handled by
//	 * UART_Send() function, just to reset Tx Interrupt state for the
//	 * first time
	switch (num) {
		case 0: TxIntStat0 = RESET; break;
		case 1: TxIntStat1 = RESET; break;
	}

	// Reset ring buf head and tail idx
	__BUF_RESET((*rb).rx_head);
	__BUF_RESET((*rb).rx_tail);
	__BUF_RESET((*rb).tx_head);
	__BUF_RESET((*rb).tx_tail);
	(*rb).txfree = UART_RING_BUFSIZE; 	// буфер пустой
	(*rb).rxdata = 0;					// буфер пустой 
	(*rb).dup = dup;					// установка ппризнака дуплекса

	if (UARTPort == (LPC_UART_TypeDef*)LPC_UART1) {
		if ((*rb).dup) {
			 InitHalfDupControlSignal();
			 InitHalfDupWaitInterval(baud_rate);
		} else InitFullDupControlSignal();
	} 

	switch (num) {
		case 0: 
		  NVIC_EnableIRQ(UART0_IRQn);
			NVIC_SetPriority(UART0_IRQn, 3);
		break;
		case 1: 
			NVIC_EnableIRQ(UART1_IRQn);
			NVIC_SetPriority(UART1_IRQn, 2);
		break;
	}

	return TRUE;
//*/
}


u16 UARTx_PlaceForSend(u8 num)
// возвращает количество свободных байт для передачи
{
	if (num/*==1*/) return rb1.txfree;
	else return rb0.txfree;
}

u16 UARTx_SendBuffer(u8 num,u8 * buffer,u16 buflen)
// передает buffer размером count
// возвращает количество фактически переданных байт
{
    u8 *data = (u8 *) buffer;
    u32 bytes = 0;
	LPC_UART_TypeDef *UARTPort;
	volatile UART_RING_BUFFER_T * rb;
	switch (num) {
		case 0:
			UARTPort = LPC_UART0;
			rb = &rb0;
			break;
		case 1:
			UARTPort = (LPC_UART_TypeDef*)LPC_UART1;
			rb = &rb1;
			break;
		default: return 0;// ошибка 
	}
  UART_IntConfig(UARTPort, UART_INTCFG_THRE, DISABLE);
	while ((buflen > 0) && (!__BUF_IS_FULL((*rb).tx_head, (*rb).tx_tail)))
	{
		(*rb).tx[(*rb).tx_head] = *data;
		data++;
		__BUF_INCR((*rb).tx_head);
		bytes++;
		buflen--;
		(*rb).txfree--;
	}
// отладка переполнения
//	if (buflen > 0) SetPin(OUT13);
	switch (num) {	 
		case 0:
			if (TxIntStat0 == RESET)  
				UART0_IntTransmit();
			else
				UART_IntConfig(UARTPort, UART_INTCFG_THRE, ENABLE);
			break;
		case 1:
			if (TxIntStat1 == RESET)  
				UART1_IntTransmit();
			else
				UART_IntConfig(UARTPort, UART_INTCFG_THRE, ENABLE);
			break;
		default: break; // ошибка
	}
    return bytes;
}

u16 UART0_SendBuffer(u8 * buffer,u16 buflen)
// передает buffer размером count
// возвращает количество фактически переданных байт
{
		u32 bytes = 0;
		
//		UART_IntConfig(LPC_UART0, UART_INTCFG_THRE, DISABLE);
		// приостанавливаем обмен
		LPC_UART0->IER &= (~UART_IER_THREINT_EN) & UART_IER_BITMASK;
		// перегоняем данные в колбцевой буфер
		while ((buflen > 0) && (!__BUF_IS_FULL(rb0.tx_head, rb0.tx_tail)))
		{
			rb0.tx[rb0.tx_head] = *buffer;
			buffer++;
			__BUF_INCR(rb0.tx_head);
			bytes++;
			buflen--;
			rb0.txfree--;
		}

		// запускаем обмен
		if (TxIntStat0 == RESET) 
			UART0_IntTransmit();
		else
//			UART_IntConfig(LPC_UART0, UART_INTCFG_THRE, ENABLE);
			LPC_UART0->IER |= UART_IER_THREINT_EN;

    return bytes;
}

u16 UART1_SendBuffer(u8 * buffer,u16 buflen)
// передает buffer размером count
// возвращает количество фактически переданных байт
{
		u32 bytes = 0;
		
//		UART_IntConfig(LPC_UART0, UART_INTCFG_THRE, DISABLE);
		LPC_UART1->IER &= (~UART_IER_THREINT_EN) & UART_IER_BITMASK;
		while ((buflen > 0) && (!__BUF_IS_FULL(rb1.tx_head, rb1.tx_tail)))
		{
			rb1.tx[rb1.tx_head] = *buffer;
			buffer++;
			__BUF_INCR(rb1.tx_head);
			bytes++;
			buflen--;
			rb1.txfree--;
		}

		if (TxIntStat1 == RESET) 
			UART1_IntTransmit();
		else
//			UART_IntConfig(LPC_UART0, UART_INTCFG_THRE, ENABLE);
			LPC_UART1->IER |= UART_IER_THREINT_EN;

    return bytes;
}


u16 UARTx_ReadyRecvData(u8 num)
// возвращает количество байт готовых к приему
{
	if (num/*==1*/) return rb1.rxdata;
	else return rb0.rxdata;
}

u16 UARTx_RecvBuffer(u8 num,u8 * buffer,u16 buflen)
// принимает count байт в buffer
// возвращает количество фактически принятых байт
{
    u8 *data = (u8 *) buffer;
    u32 bytes = 0;
	LPC_UART_TypeDef *UARTPort;
	UART_RING_BUFFER_T * rb;

	switch (num) {
		case 0:
			UARTPort = LPC_UART0;
			rb = &rb0;
			break;
		case 1:
			UARTPort = (LPC_UART_TypeDef*)LPC_UART1;
			rb = &rb1;
			break;
		default: return 0;// ошибка 
	}

	UART_IntConfig(UARTPort, UART_INTCFG_RBR, DISABLE);
	while ((buflen > 0) && (!(__BUF_IS_EMPTY((*rb).rx_head, (*rb).rx_tail))))
	{
		*data = (*rb).rx[(*rb).rx_tail];
		data++;
		__BUF_INCR((*rb).rx_tail);
		bytes++;
		buflen--;
		(*rb).rxdata--;
	}

	UART_IntConfig(UARTPort, UART_INTCFG_RBR, ENABLE);
    return bytes;
}

u16 UART0_RecvBuffer(u8 * buffer,u16 buflen)
// принимает count байт в buffer
// возвращает количество фактически принятых байт
{
		u32 bytes = 0;

		//UART_IntConfig(LPC_UART0, UART_INTCFG_RBR, DISABLE);
		LPC_UART0->IER &= (~UART_IER_RBRINT_EN) & UART_IER_BITMASK;
		while ((buflen > 0) && (!(__BUF_IS_EMPTY(rb0.rx_head, rb0.rx_tail))))
		{
			*buffer = rb0.rx[rb0.rx_tail];
			buffer++;
			__BUF_INCR(rb0.rx_tail);
			bytes++;
			buflen--;
			rb0.rxdata--;
		}
		//UART_IntConfig(LPC_UART0, UART_INTCFG_RBR, ENABLE);
		LPC_UART0->IER |= UART_IER_RBRINT_EN;
		return bytes;
}

u16 UART1_RecvBuffer(u8 * buffer,u16 buflen)
// принимает count байт в buffer
// возвращает количество фактически принятых байт
{
		u32 bytes = 0;
		//UART_IntConfig(LPC_UART1, UART_INTCFG_RBR, DISABLE);
		LPC_UART1->IER &= (~UART_IER_RBRINT_EN) & UART_IER_BITMASK;
		while ((buflen > 0) && (!(__BUF_IS_EMPTY(rb1.rx_head, rb1.rx_tail))))
		{
			*buffer = rb1.rx[rb1.rx_tail];
			buffer++;
			__BUF_INCR(rb1.rx_tail);
			bytes++;
			buflen--;
			rb1.rxdata--;
		}
		//UART_IntConfig(LPC_UART1, UART_INTCFG_RBR, ENABLE);
		LPC_UART1->IER |= UART_IER_RBRINT_EN;
		return bytes;
}

// сохранение текущего уровня оптимизации
//#pragma push
// включение нужного уровня оптимизации
//#pragma O3

/* 
void BusyUartLine(void){
// занимаем линию. Только для UART1 !!!!!!!!!!!! 
//	RE_PORT->FIOPIN |=  RE_PIN_MASK; // RE(2.3) = 1 // отключаю приемнмк
//	__nop();__nop();
//	DE_PORT->FIOPIN |=  DE_PIN_MASK; // DE(2.2) = 1 // включаю передатчик
	// так как порты одинаковые записываем все за один раз
	// но если ножки разнесутся на разные порты работать не будет!!!!!!
	DE_PORT->FIOSET = (DE_PIN_MASK|RE_PIN_MASK); 
}

void FreeUartLine(void){
	// освобождаем линию. Только для UART1 !!!!!!!!!!!! 
//	DE_PORT->FIOPIN &= ~DE_PIN_MASK; // DE(2.2) = 0 // отключаю передатчик
//	__nop();__nop(); 
//	RE_PORT->FIOPIN &= ~RE_PIN_MASK; // RE(2.3) = 0 // включаю приемнмк
	// так как порты одинаковые записываем все за один раз
	// но если ножки разнесутся на разные порты работать не будет!!!!!!!
	DE_PORT->FIOCLR = (DE_PIN_MASK|RE_PIN_MASK); 
}
*/

// восстановление сохраненного уровня оптимизации
//#pragma pop

volatile u32 Delay; // переменная для хранения задержки освобождения линии

void InitHalfDupWaitInterval(u32 baud_rate){
//							байт	бит на байт 	мкс в секунде скорость
	Delay = (u32)(1			*10						*1000000 		/ baud_rate);
	// задержка в мкс
}

void StartDelay(void){
//		StartTI(tiTx485Delay,2); // было когда MR0 = TC + interval
	// очень странно но так работает лучше !!!
	// StartTI(tiTx485Delay,0); // работает !!!
	// хотя должно бы так
	StartTI(tiTx485Delay,tiMksToTick(Delay));
}

void WaitAndFreeUartLine(void) {
	if EndTI(tiTx485Delay) {
//		FreeUartLine();
		DefFreeUartLine; // т к define
		StopTI(tiTx485Delay);
	}
}

void InitHalfDupControlSignal(void){
	// инициализация выходных сигналов для полудуплекса
	// Только для UART1 !!!!!!!!!!!! 
	// DE(2.2) = 1; RE(2.3)=0
	DE_PORT->FIODIR |= DE_PIN_MASK; // DE(2.2) - выходной пин 
	RE_PORT->FIODIR |= RE_PIN_MASK; // RE(2.3) - выходной пин 
	// настройка на прием по умолчанию (освобождение линии)
//	FreeUartLine();
	DefFreeUartLine; // без () т к define
}

void InitFullDupControlSignal(void){
	// инициализация выходных сигналов для полного дуплекса
	// Только для UART1 !!!!!!!!!!!! 
	// DE(2.2) = 1; RE(2.3)=0
	DE_PORT->FIODIR |= DE_PIN_MASK; // DE(2.2) - выходной пин 
	RE_PORT->FIODIR |= RE_PIN_MASK; // RE(2.2) - выходной пин 
	// разрешаем и прием и передачу
	DE_PORT->FIOPIN |=  DE_PIN_MASK; // DE(2.2) = 1 
	RE_PORT->FIOPIN &= ~RE_PIN_MASK; // RE(2.3) = 0 
}



