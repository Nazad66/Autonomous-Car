/*
 * servo_program.c
 *
 * Created: 12/1/2022 7:40:09 PM
 *  Author: A S U S
 */ 

/* Utiles Lib */
#include "STDIN_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "DIO_interface.h"
#include "tmr1_interface.h"

/* HAL */
#include "servo_interface.h"

void SERVO_init(void)
{
	DIO_setPinDirection(DIO_PORTD,DIO_PIN5,DIO_PIN_OUTPUT);  //Direction of PIND5 OUTPUT
}

void SERVO_negative90Degree(void)
{
	TMR_timer1InitFastPWM();
	TMR_timer1_setCompareMatchAValue(9999); // duty cycle 1ms
	TMR_timer1Enable();
}

void SERVO_0Degree(void)
{
	TMR_timer1InitFastPWM();
	TMR_timer1_setCompareMatchAValue(23999);  //duty cycle 1.5ms
	TMR_timer1Enable();
}

void SERVO_positive90Degree(void)
{
	TMR_timer1InitFastPWM();
	TMR_timer1_setCompareMatchAValue(38999);  //duty cycle 2ms
	TMR_timer1Enable();
}
