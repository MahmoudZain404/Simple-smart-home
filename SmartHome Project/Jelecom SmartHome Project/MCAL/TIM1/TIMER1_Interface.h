/*
 * TIMER1_Interface.h
 *
 * Created: 10/9/2023 9:58:02 PM
 *  Author: mahmo
 */ 


#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

#include "TIM1_Private.h"
#include "../LIB/Interrupt_Vector.h"
#include "../GIE_DRIVER/GIE_DRIVER.h"


#define ISP_FALLING_EDGE 0
#define ISP_RISING_EDGE 1

#define _OCR1A 2
#define _OCR1B 3


void TIMER1_Vid_CAPT_EdgeSelect(u8 Edge);

void TIMER1_Vid_SetCallBack(void (*Call_Ptr)(void)); 

void TIMER1_Vid_InputCAPT_CTC_Init(void);

void TIMER1_Vid_FastPWM_ICR_Init(void);


void TIMER1_Vid_OCR1A_Val(u16 val);


void TIMER1_Vid_NormalMode_Init(void) ;

void TIMER1_Vid_RestVal(void) ;

u16  TIMER1_u16_ReadVal(void) ;

u16  TIMER1_u16_ICR_ReadVal(void);


void TIMER1_Vid_FastPWM_10bit_res(u8 copy_u8_pin, u8 copy_u8_DC);

#endif /* TIMER1_INTERFACE_H_ */