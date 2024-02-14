/*
 * Interrupt_Vector.h
 *
 * Created: 10/5/2023 1:47:42 PM
 *  Author: mahmo
 */ 


#ifndef INTERRUPT_VECTOR_H_
#define INTERRUPT_VECTOR_H_


#define ISR(__vector_NUM) void __vector_NUM(void)__attribute__((signal, used)) ;\
void __vector_NUM(void)


#define EXT_INT_0    __vector_1
#define EXT_INT_1    __vector_2
#define EXT_INT_2    __vector_3
#define TIMER0_COMP  __vector_10
#define TIMER0_OVF   __vector_11
#define TIMER1_CAPT  __vector_6


#endif /* INTERRUPT_VECTOR_H_ */