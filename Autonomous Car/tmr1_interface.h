/*
 * tmr1_interface.h
 *
 * Created: 12/1/2022 7:45:34 PM
 *  Author: A S U S
 */ 


#ifndef TMR1_INTERFACE_H_
#define TMR1_INTERFACE_H_


#define TMR_TIMER1_TOP_VALUE                319999

void TMR_timer1InitFastPWM           (void);
void TMR_timerInitNormalMode         (void);
void TMR_timer1Enable                (void);   //NO prescaller
void TMR_Timer1_start                (void);   //prescaller = 8
void TMR_timer1_stop                 (void);
void TMR_timer1_setCompareMatchAValue(u16 compareValue);




#endif /* TMR1_INTERFACE_H_ */