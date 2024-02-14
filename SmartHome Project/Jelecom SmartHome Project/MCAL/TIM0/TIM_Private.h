/*
 * TIM_Private.h
 *
 * Created: 10/1/2023 8:13:07 PM
 *  Author: User
 */ 


#ifndef TIM_PRIVATE_H_
#define TIM_PRIVATE_H_
#include "../DIO/DIO_interface.h"

#define  TCCR0_REG *((volatile u8*)0x53)
#define  TNTR0_REG *((volatile u8*)0x52)
#define  OCR0_REG  *((volatile u8*)0x5c)
#define  TIMSK_REG *((volatile u8*)0x59)
#define  TIFR_REG  *((volatile u8*)0x58)



#endif /* TIM_PRIVATE_H_ */