/*
 * LCD_interface.h
 *
 * Created: 12/2/2022 7:02:12 PM
 *  Author: A S U S
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_init    (void);
void LCD_sendCmnd(u8 cmnd);
void LCD_sendChar(u8 data);
void LCD_sendStr (u8*str , u8 row , u8 col);
void LCD_GoToPos (u8 row ,u8 col);

void LCD_TurnRight  (void);
void LCD_TurnLeft   (void);
void LCD_MoveForward(void);
void LCD_MoveBackward(void);
void LCD_Stop (void);

static void write_half_port (u8 value);



#endif /* LCD_INTERFACE_H_ */