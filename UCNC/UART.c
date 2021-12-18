//#include <RTL.h>
#include "Defs.h"
// ������ ����� �������, �������� � ����-����
#include "lpc17xx_uart.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_pinsel.h"

// ������� !!! ����� ������ !!!
// ��� ������� ������������ ������
//#include "VirtualPins.h"

#include "UART.h"
#include "ti.h"
#include "msg.h"



// ���� 2 ��� �������� RE � DE
#define DE_PORT LPC_GPIO2 
#define RE_PORT LPC_GPIO2 

// ����� ��� ����� RE � DE
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
	__IO uint8_t  dup;			// �������
	__IO uint16_t  txfree;		// ��������� ����� � tx ������
	__IO uint8_t  rxdata;		// ���������� ������ � ������ ������
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
	intsrc = UART_GetIntId(LPC_UART0); // ������ �������� IRR ��������������� UARTa
	tmp = intsrc & UART_IIR_INTID_MASK/*0000 1110*/;// ������������ 1,2 � 3 �����
	
	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS/*0000 0110*/){
		// Check line status
		tmp1 = UART_GetLineStatus(LPC_UART0); // ������ �������� LSR
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) {
				UART0_IntErr(tmp1);
		}
	}
	
	// Receive Data Available or Character time-out
	// �������� �������� �������� IRR �� ����������� �������
	// ��� Character time-out 
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
		  
			UART0_IntReceive();
		
	}
	// Transmit Holding Empty
	if (tmp == UART_IIR_INTID_THRE){
		  
			UART0_IntTransmit();
	}
	
	// ������������ ���������� TIMER0_IRQn
	// U0T0p = 1 ���� T0 � ������ ��������
//	if (!U0T0p) U0T0p = NVIC_GetPendingIRQ (TIMER0_IRQn);
	
}


void UART1_IRQHandler(void)
{
	uint32_t intsrc, tmp, tmp1;
	/* Determine the interrupt source */	

	intsrc = UART_GetIntId((LPC_UART_TypeDef *)LPC_UART1); // ������ �������� IRR ��������������� UARTa
	tmp = intsrc & UART_IIR_INTID_MASK/*0000 1110*/;// ������������ 1,2 � 3 �����
	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS/*0000 0110*/){
		// Check line status
		tmp1 = UART_GetLineStatus((LPC_UART_TypeDef *)LPC_UART1); // ������ �������� LSR !!!!����� ���� ������
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) {
				UART1_IntErr(tmp1);
		}
	}
	// Receive Data Available or Character time-out
	// �������� �������� �������� IRR �� ����������� �������
	// ��� Character time-out 
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
			//Msg("r");
			UART1_IntReceive();
	}
	// Transmit Holding Empty
	if (tmp == UART_IIR_INTID_THRE){
			UART1_IntTransmit();
	}
	
// ������������ ���������� TIMER0_IRQn
//	U1T0p = 1 ���� T0 � ������ ��������
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

// ���������� ���������� �� �������� �� UART0
void UART0_IntTransmit(void){
    // Disable THRE interrupt
		// ��������� ����������
		LPC_UART0->IER &= (~UART_IER_THREINT_EN) & UART_IER_BITMASK;

	/* Wait for FIFO buffer empty, transfer UART_TX_FIFO_SIZE bytes
	 * of data or break whenever ring buffers are empty */
	/* Wait until THR empty */
	// ���� ������������ �������� THR
		while(!(LPC_UART0->LSR & UART_LSR_TEMT));
	
	// ��������� ������� ������ � �������� ������
		if (!__BUF_IS_EMPTY(rb0.tx_head,rb0.tx_tail))
    {
        /* Move a piece of data into the transmit FIFO */
			// �������� ������ ����
    	if (UART0_Send(rb0.tx[rb0.tx_tail])){
	        /* Update transmit ring FIFO tail pointer */
	        __BUF_INCR(rb0.tx_tail);
					rb0.txfree++;
			} 
    }

    /* If there is no more data to send, disable the transmit
       interrupt - else enable it or keep it enabled */
		if (__BUF_IS_EMPTY(rb0.tx_head, rb0.tx_tail)) {
			// ����� ���� 
			// ������������� ���������� ��������
			LPC_UART0->IER &= (~UART_IER_THREINT_EN) & UART_IER_BITMASK;
    	// Reset Tx Interrupt state
			// ���������� ���� ���������� ��������
    	TxIntStat0 = RESET;
    }
    else{
			// ����� �� ����
      // Set Tx Interrupt state
			// ������������� ���� ���������� ��������
			TxIntStat0 = SET;
			// ��������� ���������� ��������
			LPC_UART0->IER |= UART_IER_THREINT_EN;
    }
		
}


void UART1_IntTransmit(void){
		// Disable THRE interrupt
		// ������ UART_IntConfig ����� ��������
		((LPC_UART1_TypeDef *)LPC_UART1)->IER &= (~UART_IER_THREINT_EN) & UART1_IER_BITMASK;
		/* Wait for FIFO buffer empty, transfer UART_TX_FIFO_SIZE bytes
		* of data or break whenever ring buffers are empty */
		/* Wait until THR empty */
		// ���� ������������ �������� THR
		// UART_CheckBusy ����� ����
		while(!(((LPC_UART_TypeDef *)LPC_UART1)->LSR & UART_LSR_TEMT));
		// ���� ����������� �������� �����
//		if (rb1.dup == HALF_DUPLEX) BusyUartLine();
		if (rb1.dup == HALF_DUPLEX) DefBusyUartLine; // � � define
		
		// ��������� ������� ������ � �������� ������
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
			// UART_IntConfig DISABLE ����� ��������
			((LPC_UART1_TypeDef *)LPC_UART1)->IER &= (~UART_IER_THREINT_EN) & UART1_IER_BITMASK;
			// Reset Tx Interrupt state
    	TxIntStat1 = RESET;
			if (rb1.dup == HALF_DUPLEX) StartDelay();
    }
    else{
      // Set Tx Interrupt state
			TxIntStat1 = SET;
			// UART_IntConfig ENABLE ����� ��������
			((LPC_UART1_TypeDef *)LPC_UART1)->IER |= UART_IER_THREINT_EN;
    }
}


void UART0_IntReceive(void){
	uint8_t tmpc;
	uint32_t rLen;

	while(1){
		// Call UART read function in UART driver
		rLen = UART_Receive((LPC_UART_TypeDef *)LPC_UART0, &tmpc, 1, NONE_BLOCKING);
		//				^ ����� ��������. ����
		// If data received
		if (rLen){
			// �������� �� ��������� ����� � ������
			// ���� ����� ��� ������ ��������
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
		//			^ ����� ��������. ����
		// If data received
		if (rLen){
			/* Check if buffer is more space
			 * If no more space, remaining character will be trimmed out
			 */
			// �������� �� ��������� ����� � ������
			// ���� ����� ��� ������ ��������
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
	(*rb).txfree = UART_RING_BUFSIZE; 	// ����� ������
	(*rb).rxdata = 0;					// ����� ������ 
	(*rb).dup = dup;					// ��������� ��������� ��������

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
// ���������� ���������� ��������� ���� ��� ��������
{
	if (num/*==1*/) return rb1.txfree;
	else return rb0.txfree;
}

u16 UARTx_SendBuffer(u8 num,u8 * buffer,u16 buflen)
// �������� buffer �������� count
// ���������� ���������� ���������� ���������� ����
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
		default: return 0;// ������ 
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
// ������� ������������
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
		default: break; // ������
	}
    return bytes;
}

u16 UART0_SendBuffer(u8 * buffer,u16 buflen)
// �������� buffer �������� count
// ���������� ���������� ���������� ���������� ����
{
		u32 bytes = 0;
		
//		UART_IntConfig(LPC_UART0, UART_INTCFG_THRE, DISABLE);
		// ���������������� �����
		LPC_UART0->IER &= (~UART_IER_THREINT_EN) & UART_IER_BITMASK;
		// ���������� ������ � ��������� �����
		while ((buflen > 0) && (!__BUF_IS_FULL(rb0.tx_head, rb0.tx_tail)))
		{
			rb0.tx[rb0.tx_head] = *buffer;
			buffer++;
			__BUF_INCR(rb0.tx_head);
			bytes++;
			buflen--;
			rb0.txfree--;
		}

		// ��������� �����
		if (TxIntStat0 == RESET) 
			UART0_IntTransmit();
		else
//			UART_IntConfig(LPC_UART0, UART_INTCFG_THRE, ENABLE);
			LPC_UART0->IER |= UART_IER_THREINT_EN;

    return bytes;
}

u16 UART1_SendBuffer(u8 * buffer,u16 buflen)
// �������� buffer �������� count
// ���������� ���������� ���������� ���������� ����
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
// ���������� ���������� ���� ������� � ������
{
	if (num/*==1*/) return rb1.rxdata;
	else return rb0.rxdata;
}

u16 UARTx_RecvBuffer(u8 num,u8 * buffer,u16 buflen)
// ��������� count ���� � buffer
// ���������� ���������� ���������� �������� ����
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
		default: return 0;// ������ 
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
// ��������� count ���� � buffer
// ���������� ���������� ���������� �������� ����
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
// ��������� count ���� � buffer
// ���������� ���������� ���������� �������� ����
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

// ���������� �������� ������ �����������
//#pragma push
// ��������� ������� ������ �����������
//#pragma O3

/* 
void BusyUartLine(void){
// �������� �����. ������ ��� UART1 !!!!!!!!!!!! 
//	RE_PORT->FIOPIN |=  RE_PIN_MASK; // RE(2.3) = 1 // �������� ��������
//	__nop();__nop();
//	DE_PORT->FIOPIN |=  DE_PIN_MASK; // DE(2.2) = 1 // ������� ����������
	// ��� ��� ����� ���������� ���������� ��� �� ���� ���
	// �� ���� ����� ���������� �� ������ ����� �������� �� �����!!!!!!
	DE_PORT->FIOSET = (DE_PIN_MASK|RE_PIN_MASK); 
}

void FreeUartLine(void){
	// ����������� �����. ������ ��� UART1 !!!!!!!!!!!! 
//	DE_PORT->FIOPIN &= ~DE_PIN_MASK; // DE(2.2) = 0 // �������� ����������
//	__nop();__nop(); 
//	RE_PORT->FIOPIN &= ~RE_PIN_MASK; // RE(2.3) = 0 // ������� ��������
	// ��� ��� ����� ���������� ���������� ��� �� ���� ���
	// �� ���� ����� ���������� �� ������ ����� �������� �� �����!!!!!!!
	DE_PORT->FIOCLR = (DE_PIN_MASK|RE_PIN_MASK); 
}
*/

// �������������� ������������ ������ �����������
//#pragma pop

volatile u32 Delay; // ���������� ��� �������� �������� ������������ �����

void InitHalfDupWaitInterval(u32 baud_rate){
//							����	��� �� ���� 	��� � ������� ��������
	Delay = (u32)(1			*10						*1000000 		/ baud_rate);
	// �������� � ���
}

void StartDelay(void){
//		StartTI(tiTx485Delay,2); // ���� ����� MR0 = TC + interval
	// ����� ������� �� ��� �������� ����� !!!
	// StartTI(tiTx485Delay,0); // �������� !!!
	// ���� ������ �� ���
	StartTI(tiTx485Delay,tiMksToTick(Delay));
}

void WaitAndFreeUartLine(void) {
	if EndTI(tiTx485Delay) {
//		FreeUartLine();
		DefFreeUartLine; // � � define
		StopTI(tiTx485Delay);
	}
}

void InitHalfDupControlSignal(void){
	// ������������� �������� �������� ��� ������������
	// ������ ��� UART1 !!!!!!!!!!!! 
	// DE(2.2) = 1; RE(2.3)=0
	DE_PORT->FIODIR |= DE_PIN_MASK; // DE(2.2) - �������� ��� 
	RE_PORT->FIODIR |= RE_PIN_MASK; // RE(2.3) - �������� ��� 
	// ��������� �� ����� �� ��������� (������������ �����)
//	FreeUartLine();
	DefFreeUartLine; // ��� () � � define
}

void InitFullDupControlSignal(void){
	// ������������� �������� �������� ��� ������� ��������
	// ������ ��� UART1 !!!!!!!!!!!! 
	// DE(2.2) = 1; RE(2.3)=0
	DE_PORT->FIODIR |= DE_PIN_MASK; // DE(2.2) - �������� ��� 
	RE_PORT->FIODIR |= RE_PIN_MASK; // RE(2.2) - �������� ��� 
	// ��������� � ����� � ��������
	DE_PORT->FIOPIN |=  DE_PIN_MASK; // DE(2.2) = 1 
	RE_PORT->FIOPIN &= ~RE_PIN_MASK; // RE(2.3) = 0 
}



