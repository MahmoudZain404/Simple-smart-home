/*
 * TIM1_Private.h
 *
 * Created: 10/9/2023 9:55:49 PM
 *  Author: mahmo
 */ 


#ifndef TIM1_PRIVATE_H_
#define TIM1_PRIVATE_H_

#include "../DIO/DIO_interface.h"

#define TCCR1A_REG *((volatile u8*)0x4f)
#define TCCR1B_REG *((volatile u8*)0x4E)
#define OCR1A_REG  *((volatile u16*)0x4A)
#define OCR1B_REG  *((volatile u16*)0x48)
#define ICR_REG    *((volatile u16*)0x46)
#define TIFR_REG   *((volatile u8*)0x58)
#define TCNT1_REG  *((volatile u16*)0x4C)
#define TIMSK_REG  *((volatile u8*)0x59)


#endif /* TIM1_PRIVATE_H_ */