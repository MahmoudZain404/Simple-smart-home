/*
 * ADC_Interface.h
 *
 * Created: 9/25/2023 8:51:00 PM
 *  Author: mahmo
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_
#include "ADC_Private.h"


#define ADC_INT_16   __vector_16

#define ADC_ISR(__vector_NUM) void __vector_NUM(void)__attribute__((signal, used)) ;\
void __vector_NUM(void)

void ADC_Vid_ADC_CallBack(void (*CallBack)(S8*));

void ADC_Void_Init(u8 copy_u8_channel);

u16 ADC_Void_Read(u8 copy_u8_channel);


#endif /* ADC_INTERFACE_H_ */