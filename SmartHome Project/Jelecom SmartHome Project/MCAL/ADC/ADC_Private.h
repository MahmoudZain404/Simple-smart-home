/*
 * ADC_Private.h
 *
 * Created: 9/25/2023 8:50:28 PM
 *  Author: mahmo
 */ 


#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_
#include "../DIO/DIO_interface.h"


#define ADMUX_REG *((volatile u8*)0x27)
#define ADCSRA_REG *((volatile u8*)0x26)
#define ADCW_REG *((volatile u16*)0x24)


#endif /* ADC_PRIVATE_H_ */