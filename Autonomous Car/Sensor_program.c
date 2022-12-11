/*
 * Sensor_program.c
 *
 * Created: 12/2/2022 5:00:48 PM
 *  Author: A S U S
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

/* Utiles Lib */
#include "STDIN_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "DIO_interface.h"
#include "tmr1_interface.h"
//#include "EXTI_interface.h"

/* HAL */
#include "Sensor_interface.h"


static volatile int pulse = 0;

void SENSOR_init(void)
{
	DIO_setPinDirection(DIO_PORTA,DIO_PIN0,DIO_PIN_OUTPUT);  // TRIGGER PA0 OP
	DIO_setPinDirection(DIO_PORTA,DIO_PIN1,DIO_PIN_INPUT);   //  ECHO   PA1 IP	
}

u16 SENSOR_LOOP(void)
{
	u16 Distance=0;
	
	TMR_timerInitNormalMode();
	TCNT1_u16 = 0;    //reset timer1 register
	
	//Transmit 10 us trigger pulse
	DIO_setPinValue(DIO_PORTA,DIO_PIN0,DIO_PIN_HIGH);
	_delay_us(10);
	DIO_setPinValue(DIO_PORTA,DIO_PIN0,DIO_PIN_LOW);
	
	while (GET_BIT(PINA,1) == 0);
	TMR_Timer1_start();   //start counting if echo is high
	
	while (GET_BIT(PINA,1) == 1);
	TMR_timer1_stop();    //stop counting if echo is low
	
	pulse = TCNT1_u16;  
	Distance = pulse/116 ;  //16MHZ , 8 prescaller
	
	return Distance;
	
}
