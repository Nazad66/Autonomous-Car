/*
 * LCD_program.c
 *
 * Created: 12/2/2022 7:02:34 PM
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
#include "LCD_interface.h"

void LCD_init    (void)
{
	DIO_setPinDirection(DIO_PORTA,DIO_PIN4,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTA,DIO_PIN5,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTA,DIO_PIN6,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTA,DIO_PIN7,DIO_PIN_OUTPUT);
	
	DIO_setPinDirection(DIO_PORTB,DIO_PIN1,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTB,DIO_PIN2,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTB,DIO_PIN3,DIO_PIN_OUTPUT);

	_delay_ms(35);
	//SET Rs pin TO 0 = COMMAND
	DIO_setPinValue(DIO_PORTB,DIO_PIN1,DIO_PIN_LOW);
	
	//SET Rw pin TO 0 = Write
	DIO_setPinValue(DIO_PORTB,DIO_PIN2,DIO_PIN_LOW);
	
	write_half_port(0b0010);
	
	//Enable Pulse High Then Low
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_LOW);
	
	LCD_sendCmnd(0b00101000);
	
	_delay_us(45);
	//Display Off Control (Display,Cursor,Blink)
	LCD_sendCmnd(0b00001100);
	
	_delay_us(45);
	//Clear Display
	LCD_sendCmnd(0b00000001);
	
	_delay_ms(2);
	//Set Entry Mode
	LCD_sendCmnd(0b00000110);
	
}

void LCD_sendCmnd(u8 cmnd)
{
	//set Rs pin =0 (write command)
	DIO_setPinValue(DIO_PORTB,DIO_PIN1,DIO_PIN_LOW);
	
	//set Rw pin =0 (write)
	DIO_setPinValue(DIO_PORTB,DIO_PIN2,DIO_PIN_LOW);
	
	//write the most 4 bits of command on data pins
	write_half_port(cmnd>>4);
	
	//Enable pulse high then low
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_LOW);
	
	//write the Least 4 bits of command on data pins
	write_half_port(cmnd);
	
	//Enable pulse high then low
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_LOW);	

}

void LCD_sendChar(u8 data)
{
	//set Rs pin =1 (write data)
	DIO_setPinValue(DIO_PORTB,DIO_PIN1,DIO_PIN_HIGH);
	
	//set Rw pin =0 (write)
	DIO_setPinValue(DIO_PORTB,DIO_PIN2,DIO_PIN_LOW);
	
	//write the most 4 bits of command on data pins
	write_half_port(data>>4);
	
	//Enable pulse high then low
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_LOW);
	
	//write the Least 4 bits of command on data pins
	write_half_port(data);
	
	//Enable pulse high then low
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_LOW);
	
	
}

static void write_half_port(u8 value)
{
	if (1== GET_BIT(value,0))
	{
		DIO_setPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_HIGH);
	}
	else
	{
		DIO_setPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_LOW);
	}
	
	if (1== GET_BIT(value,1))
	{
		DIO_setPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_HIGH);
	}
	else
	{
		DIO_setPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_LOW);
	}
	
	if (1== GET_BIT(value,2))
	{
		DIO_setPinValue(DIO_PORTA,DIO_PIN6,DIO_PIN_HIGH);
	}
	else
	{
		DIO_setPinValue(DIO_PORTA,DIO_PIN6,DIO_PIN_LOW);
	}
	
	if (1== GET_BIT(value,3))
	{
		DIO_setPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_HIGH);
	}
	else
	{
		DIO_setPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_LOW);
	}
}

void LCD_GoToPos (u8 row ,u8 col)
{
	u8 Adress;
	if (row<2 && col<16)
	{
		Adress= (row * 0b01000000) + col;
		Adress=  SET_BIT(Adress,7);
		LCD_sendCmnd(Adress);
	}
	
}

void LCD_sendStr (u8*str , u8 row , u8 col)
{
  LCD_GoToPos(row,col);
  u8 index=0;
  u8 line0=0;
  
  while(str[index] != NULL && ((row*16)+(index+col)) <32)
  {
    if (((row*16)+(index+col)) <16)
    {
      LCD_sendChar(str[index]);
      index++;
    }
    else if (((row*16)+(index+col)) == 16 && line0==0)
    {
      LCD_GoToPos(1,0);  
      line0++;
    }
    else if (((row*16)+(index+col)) < 32 && line0==1)
    {
      LCD_sendChar(str[index]);
      index++;  
    }  
  }
}


void LCD_TurnRight  (void)
{
   LCD_init();
   LCD_sendStr("Turn Right" , 0 , 4);
}

void LCD_TurnLeft  (void)
{
  LCD_init();
  LCD_sendStr("Turn Left" , 0 , 4);
}

void LCD_MoveForward (void)
{
  LCD_init();
  LCD_sendStr("Move Forward" , 0 , 2);
}

void LCD_MoveBackward (void)
{
  LCD_init();
  LCD_sendStr("Move Backward" , 0 , 1);
}

void LCD_Stop (void)
{
	LCD_init();
	LCD_sendStr("STOP" , 0 , 6);
}