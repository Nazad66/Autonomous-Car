/*
 * motor_interface.h
 *
 * Created: 11/30/2022 8:42:28 PM
 *  Author: A S U S
 */ 


#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_


void MOTOR_init(void);
void MOTOR_rotateClockwise(void);
void MOTOR_rotateAntiClockwise(void);
void MOTOR_stop(void);
void MOTOR_turnLeft(void);
void MOTOR_turnRight(void);


#endif /* MOTOR_INTERFACE_H_ */