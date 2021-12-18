#include "LPC17xx.h"

#include "Defs.h"

/****************************************************************************
 *   $Id:: pwm.c 5748 2010-11-30 23:48:37Z usb00423                         $
 *   Project: NXP LPC17xx PWM example
 *
 *   Description:
 *     This file contains PWM code example which include PWM initialization, 
 *     PWM interrupt handler, and APIs for PWM access.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/

/******************************************************************************
** Function name:		PWM_Init
**
** Descriptions:		PWM initialization, setup all GPIOs to PWM0~6,
**						reset counter, all latches are enabled, interrupt
**						on PWMMR0, install PWM interrupt to the VIC table.
**
** parameters:			Duty cycle
** Returned value:		none
** 
******************************************************************************/
void PWM_Init( uint32_t cycle )
{

	LPC_PINCON->PINSEL4 |= (01 << 10);	// Set P2.5 to PWM1.6

	LPC_PWM1->TCR = 0x00000002;			// Timer/Counter and prescaler Reset and Enable
	LPC_PWM1->PR = 0x00;				// count frequency:Fpclk// период
	LPC_PWM1->MCR = (1 << 1);			// no interrupt, reset on LPC_PWM1->MR0, reset TC if PWM matches
// cycle 
	LPC_PWM1->MR0 = cycle;				// set PWM cycle
	LPC_PWM1->LER |= (1 << 0);			// Enable Load MR0 to Shadow MR0
}

/******************************************************************************
** Function name:		PWM_Start
**
** Descriptions:		Enable PWM by setting the PCR, PTCR registers
**
** parameters:			none
** Returned value:		None
** 
******************************************************************************/
void PWM_Start(void)
{
	LPC_PWM1->PCR = (1 << 13) | (1 << 14);		// All single edge, all enable
	LPC_PWM1->TCR = 0x00000001 | 0x00000008;	// counter enable, PWM enable
}

/******************************************************************************
** Function name:		PWM_Stop
**
** Descriptions:		Stop all PWM channels
**
** parameters:			none
** Returned value:		None
** 
******************************************************************************/
void PWM_Stop(void)
{
	LPC_PWM1->PCR = 0;
	LPC_PWM1->TCR = 0x00;		/* Stop all PWMs */
}

/******************************************************************************
** Function name:		PWM_Set
**
** Descriptions:		PWM cycle setup
**
** parameters:			offset
** Returned value:		None
** 
******************************************************************************/
void PWM_Set( uint32_t offset )
{			
	LPC_PWM1->MR6 = offset;
	LPC_PWM1->LER |=  (1 << 6);			// Enable Load MR6 to Shadow MR6

	/* The LER will be cleared when the Match 0 takes place, in order to
	load and execute the new value of match registers, all the PWMLERs need to
	reloaded. PWM latch enabled */
}

/******************************************************************************
**                            End Of File
******************************************************************************/
