/*
 * tmr1_program.c
 *
 * Created: 12/1/2022 7:45:50 PM
 *  Author: A S U S
 */ 

/* Utiles Lib */
#include "STDIN_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "tmr1_interface.h"

void TMR_timer1InitFastPWM(void)
{
	//Select Mode = Fast PWM Mode (14)
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
	
	//Select Non Inverting Mode
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
	
	//Set Max Of Timer
	ICR1_u16 = TMR_TIMER1_TOP_VALUE;   //(16MHZ / 1*50) - 1
	
}

void TMR_timerInitNormalMode(void)
{
	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
}

void TMR_timer1Enable(void)
{
	//Select Prescaler Value = 1
	SET_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
}

void TMR_Timer1_start(void)
{
	//Select Prescaler Value = 8
	CLR_BIT(TCCR1B,0);
	SET_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
}

void TMR_timer1_stop(void)
{
	CLR_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
}

void TMR_timer1_setCompareMatchAValue(u16 compareValue)
{
	//Init Timer with compare value
	OCR1A_u16 = compareValue;
}