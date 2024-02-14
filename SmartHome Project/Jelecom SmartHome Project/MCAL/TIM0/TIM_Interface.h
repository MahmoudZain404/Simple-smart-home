/*
 * TIM_Interface.h
 *
 * Created: 10/1/2023 8:13:41 PM
 *  Author: User
 */ 


#ifndef TIM_INTERFACE_H_
#define TIM_INTERFACE_H_

#include "TIM_Private.h"

#define  TIMER_STOP           0
#define  NO_PRESCALER         1
#define  _8_PRESCALER         2
#define  _64_PRESCALER        3
#define  _256_PRESCALER       4
#define  _1024_PRESCALER      5

/*modes*/

#define  CTC_MODE     1
#define  OV_MODE      2

/* VAL OF OCR  */
#define  OCR_VAL  250


void TIM0_Vid_FastPwm(u8 copy_u8_DutyCycle);

void TIM0_Vid_CallBack(u8 mode , void(*ptr_fun)(void)) ;

void TIM0_Vid_Overflow_Init(void) ;

void TIM0_Vid_CTC_Init(void) ;

void TIM0_Vid_Start(u8 copy_u8_prescaler) ;

void TIM0_Vid_Stop(u8 copy_u8_prescaler) ;

void TIM0_Vid_DelayMS(u32 delay) ;



#endif /* TIM_INTERFACE_H_ */