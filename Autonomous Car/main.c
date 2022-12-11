/*
 * Autonomous Car.c
 *
 * Created: 12/8/2022 1:48:07 PM
 * Author : A S U S
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

/* HAL */
#include "Sensor_interface.h"
#include "servo_interface.h"
#include "MOTOR_interface.h"
#include "LCD_interface.h"


int main(void)
{
	
	SERVO_init();
	SENSOR_init();
	MOTOR_init();
	LCD_init();
	
	static volatile u16 D_left;
	static volatile u16 D_right;

	while (1)
	{
		u16 dis = SENSOR_LOOP(); //DISTANCE MEASURED FROM SENSOR IN CM
		while( dis >= 20 )
		{
			LCD_MoveForward();
			MOTOR_rotateClockwise();
			dis = SENSOR_LOOP();
			if ( dis < 20)
			{
				break;
			}
		}
		
		LCD_Stop();
		MOTOR_stop();
		_delay_ms(1000);
		
		SERVO_positive90Degree(); // FOR SCANING LEFT SIDE
		_delay_ms(1000);
		dis = SENSOR_LOOP();
		D_left = dis;
		SERVO_0Degree();
		
		SERVO_negative90Degree(); // FOR SCANING RIGHT SIDE
		_delay_ms(1000);
		dis = SENSOR_LOOP();
		D_right = dis;
		SERVO_0Degree();
		
		//CHOOSING THE RIGHT SIDE TO MOVE
		if ( D_left > D_right && D_left > 20)
		{
			
			LCD_TurnLeft();
			MOTOR_turnLeft();
			_delay_ms(1000);     //ROTATE 90 DEGREE MEASURED BY OUR BATTERIES
			
		}
		
		else if ( D_right > D_left && D_right > 20)
		{
			LCD_TurnRight();
			MOTOR_turnRight();
			_delay_ms(1000);    //ROTATE 90 DEGREE MEASURED BY OUR BATTERIES
		}
		
		else
		{
			LCD_MoveBackward();
			MOTOR_rotateAntiClockwise();
			
			_delay_ms(2000);
			
			LCD_TurnRight();
			MOTOR_turnRight();
			
			_delay_ms(1000);    //ROTATE 180 DEGREE
		}
	}
}