/*
 * motor_program.c
 *
 * Created: 11/30/2022 8:41:53 PM
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

/* HAL */
#include "MOTOR_interface.h"


void MOTOR_init(void)
{
	  DIO_setPortDirection(DIO_PORTD,DIO_PORT_OUTPUT);   //Direction of PORTD Output
	  DIO_setPortDirection(DIO_PORTC,DIO_PORT_OUTPUT);   //Direction of PORTC Output
}

void MOTOR_rotateClockwise(void)
{
	//MOVE FORWARD
	//Motor 1
	DIO_setPinValue(DIO_PORTC,DIO_PIN0,DIO_PIN_HIGH); //IN1
	DIO_setPinValue(DIO_PORTC,DIO_PIN1,DIO_PIN_LOW);  //IN2
	DIO_setPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_HIGH); //ENABLE1
	
	//Motor 2
	DIO_setPinValue(DIO_PORTC,DIO_PIN4,DIO_PIN_HIGH); //IN3
	DIO_setPinValue(DIO_PORTC,DIO_PIN5,DIO_PIN_LOW);  //IN4
	DIO_setPinValue(DIO_PORTC,DIO_PIN3,DIO_PIN_HIGH); //ENABLE2
	
	//Motor 3
	DIO_setPinValue(DIO_PORTC,DIO_PIN6,DIO_PIN_HIGH); //IN1
	DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_LOW); //IN2
	DIO_setPinValue(DIO_PORTD,DIO_PIN0,DIO_PIN_HIGH); //ENABLE3
	
	//Motor 4
	DIO_setPinValue(DIO_PORTD,DIO_PIN2,DIO_PIN_HIGH); //IN3
	DIO_setPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_LOW); //IN4
	DIO_setPinValue(DIO_PORTD,DIO_PIN1,DIO_PIN_HIGH); //ENABLE4
	
	
}

void MOTOR_rotateAntiClockwise(void)
{
	//MOVE BACKWARD
	//Motor 1
	DIO_setPinValue(DIO_PORTC,DIO_PIN1,DIO_PIN_HIGH); //IN2
	DIO_setPinValue(DIO_PORTC,DIO_PIN0,DIO_PIN_LOW);  //IN1
	DIO_setPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_HIGH); //ENABLE1
	
	//Motor 2
	DIO_setPinValue(DIO_PORTC,DIO_PIN4,DIO_PIN_LOW); //IN4
	DIO_setPinValue(DIO_PORTC,DIO_PIN5,DIO_PIN_HIGH);  //IN3
	DIO_setPinValue(DIO_PORTC,DIO_PIN3,DIO_PIN_HIGH); //ENABLE2
	
	//Motor 3
	DIO_setPinValue(DIO_PORTC,DIO_PIN6,DIO_PIN_LOW);
	DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_HIGH);
	DIO_setPinValue(DIO_PORTD,DIO_PIN0,DIO_PIN_HIGH); //ENABLE3
	
	//Motor 4
	DIO_setPinValue(DIO_PORTD,DIO_PIN2,DIO_PIN_LOW);
	DIO_setPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_HIGH);
	DIO_setPinValue(DIO_PORTD,DIO_PIN1,DIO_PIN_HIGH); //ENABLE4
	
	
}

void MOTOR_stop(void)
{
	
	//Motor 1
	DIO_setPinValue(DIO_PORTC,DIO_PIN1,DIO_PIN_LOW);
	DIO_setPinValue(DIO_PORTC,DIO_PIN0,DIO_PIN_LOW);
	DIO_setPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_LOW); //ENABLE3
	
	//Motor 2
	DIO_setPinValue(DIO_PORTC,DIO_PIN4,DIO_PIN_LOW);
	DIO_setPinValue(DIO_PORTC,DIO_PIN5,DIO_PIN_LOW);
	DIO_setPinValue(DIO_PORTC,DIO_PIN3,DIO_PIN_LOW); //ENABLE4
	
	//Motor 3
	DIO_setPinValue(DIO_PORTC,DIO_PIN6,DIO_PIN_LOW);
	DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_LOW);
	DIO_setPinValue(DIO_PORTD,DIO_PIN0,DIO_PIN_LOW); //ENABLE1
	
	//Motor 4
	DIO_setPinValue(DIO_PORTD,DIO_PIN2,DIO_PIN_LOW);
	DIO_setPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_LOW);
	DIO_setPinValue(DIO_PORTD,DIO_PIN1,DIO_PIN_LOW); //ENABLE2
		
}

void MOTOR_turnRight(void)
{
	
	//MOTOR 2 & 4 CLOCKWISE
	//Motor 2
	DIO_setPinValue(DIO_PORTC,DIO_PIN4,DIO_PIN_HIGH); //IN3
	DIO_setPinValue(DIO_PORTC,DIO_PIN5,DIO_PIN_LOW);  //IN4
	DIO_setPinValue(DIO_PORTC,DIO_PIN3,DIO_PIN_HIGH); //ENABLE2
	//Motor 4
	DIO_setPinValue(DIO_PORTD,DIO_PIN2,DIO_PIN_HIGH); //IN3
	DIO_setPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_LOW); //IN4
	DIO_setPinValue(DIO_PORTD,DIO_PIN1,DIO_PIN_HIGH); //ENABLE4
	
	//MOTOR 1 & 3 ANTI-CLOCKWISE
	//Motor 1
	DIO_setPinValue(DIO_PORTC,DIO_PIN1,DIO_PIN_HIGH); //IN2
	DIO_setPinValue(DIO_PORTC,DIO_PIN0,DIO_PIN_LOW);  //IN1
	DIO_setPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_HIGH); //ENABLE1
	//Motor 3
	DIO_setPinValue(DIO_PORTC,DIO_PIN6,DIO_PIN_LOW);
	DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_HIGH);
	DIO_setPinValue(DIO_PORTD,DIO_PIN0,DIO_PIN_HIGH); //ENABLE3
	
}

void MOTOR_turnLeft(void)
{
	
	//MOTOR 1 & 3 CLOCKWISE
	//Motor 1
	DIO_setPinValue(DIO_PORTC,DIO_PIN1,DIO_PIN_LOW);  //IN2
	DIO_setPinValue(DIO_PORTC,DIO_PIN0,DIO_PIN_HIGH); //IN1
	DIO_setPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_HIGH); //ENABLE1
	//Motor 3
	DIO_setPinValue(DIO_PORTC,DIO_PIN6,DIO_PIN_HIGH); //IN1
	DIO_setPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_LOW); //IN2
	DIO_setPinValue(DIO_PORTD,DIO_PIN0,DIO_PIN_HIGH); //ENABLE3
	
	//MOTOR 2 & 4 ANTI-CLOCKWISE
	//Motor 2
	DIO_setPinValue(DIO_PORTC,DIO_PIN4,DIO_PIN_LOW); //IN4
	DIO_setPinValue(DIO_PORTC,DIO_PIN5,DIO_PIN_HIGH);  //IN3
	DIO_setPinValue(DIO_PORTC,DIO_PIN3,DIO_PIN_HIGH); //ENABLE2
	//Motor 4
	DIO_setPinValue(DIO_PORTD,DIO_PIN2,DIO_PIN_LOW);
	DIO_setPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_HIGH);
	DIO_setPinValue(DIO_PORTD,DIO_PIN1,DIO_PIN_HIGH); //ENABLE4
}
