#include "StaticPins.h"

// таблица пинов общего назначения для платы UCNC board 1.0
// параметр инверсия (INV) настраивается таким образом, чтобы на выходе
// активный сигнал имел положительный уровень, т.е. процедуры SetPin() и QSetPin()
// устанавливают положительный уровень, а процедуры ClrPin() и QClrPin() устанавливают
// нулевой уровень. При смене логики внешнего устройства с pnp на npn необходимо
// изменить этот параметр с помощью процедуры SetPinInv()
TPin aPin[PinCount] = {
//	 порт пин напр. 
// выходы платы
	{LPC_GPIO1,(1L<<0),	DIR_OUT},	// OUT1  = P1.0
	{LPC_GPIO1,(1L<<1),	DIR_OUT},	// OUT2  = P1.1
	{LPC_GPIO1,(1L<<4),	DIR_OUT},	// OUT3  = P1.4
	{LPC_GPIO1,(1L<<8),	DIR_OUT},	// OUT4  = P1.8
	{LPC_GPIO1,(1L<<9),	DIR_OUT},	// OUT5  = P1.9
	{LPC_GPIO1,(1L<<10),DIR_OUT},	// OUT6  = P1.10
	{LPC_GPIO1,(1L<<14),DIR_OUT},	// OUT7  = P1.14
	{LPC_GPIO1,(1L<<15),DIR_OUT},	// OUT8  = P1.15
	{LPC_GPIO1,(1L<<16),DIR_OUT},	// OUT9  = P1.16
	{LPC_GPIO1,(1L<<17),DIR_OUT},	// OUT10 = P1.17
	{LPC_GPIO1,(1L<<18),DIR_OUT},	// OUT11 = P1.18
	{LPC_GPIO1,(1L<<19),DIR_OUT},	// OUT12 = P1.19
	{LPC_GPIO1,(1L<<21),DIR_OUT},	// OUT13 = P1.21
	{LPC_GPIO1,(1L<<22),DIR_OUT},	// OUT14 = P1.22
	{LPC_GPIO1,(1L<<25),DIR_OUT},	// OUT15 = P1.25
	{LPC_GPIO1,(1L<<26),DIR_OUT},	// OUT16 = P1.26
	{LPC_GPIO1,(1L<<27),DIR_OUT},	// OUT17 = P1.27
	{LPC_GPIO1,(1L<<28),DIR_OUT},	// OUT18 = P1.28
	{LPC_GPIO1,(1L<<29),DIR_OUT},	// OUT19 = P1.29
	{LPC_GPIO1,(1L<<30),DIR_OUT},	// OUT20 = P1.30
// входы платы
	{LPC_GPIO2,(1L<<13),DIR_IN},	// IN1   = P2.13
	{LPC_GPIO2,(1L<<12),DIR_IN},	// IN2   = P2.12
	{LPC_GPIO2,(1L<<11),DIR_IN},	// IN3   = P2.11
	{LPC_GPIO2,(1L<<9),	DIR_IN},	// IN4   = P2.9
	{LPC_GPIO2,(1L<<8),	DIR_IN},	// IN5   = P2.8
	{LPC_GPIO2,(1L<<7),	DIR_IN},	// IN6   = P2.7
	{LPC_GPIO2,(1L<<6),	DIR_IN},	// IN7   = P2.6
	{LPC_GPIO4,(1L<<28),DIR_IN},	// IN8   = P4.28
	{LPC_GPIO0,(1L<<6),	DIR_IN},	// IN9   = P0.6
	{LPC_GPIO0,(1L<<10),DIR_IN},	// IN10  = P0.10
	{LPC_GPIO3,(1L<<25),DIR_IN},	// IN11  = P3.25
	{LPC_GPIO3,(1L<<26),DIR_IN},	// IN12  = P3.26
	{LPC_GPIO0,(1L<<0),	DIR_IN},	// IN13  = P0.0
	{LPC_GPIO0,(1L<<1),	DIR_IN},	// IN14  = P0.1
	{LPC_GPIO0,(1L<<4),	DIR_IN},	// IN15  = P0.4
	{LPC_GPIO0,(1L<<5),	DIR_IN}		// IN16  = P0.5
};
