/*
 * TIM_Interface.c
 *
 * Created: 10/1/2023 8:13:21 PM
 *  Author: User
 */ 


#include "TIM_Interface.h"
#include "../LIB/Interrupt_Vector.h"
#include "../GIE_DRIVER/GIE_DRIVER.h"
//#include "MATH.h"

#define F_CPU 16



void (*overflow_ptr)(void)= null ;
void (*CTC_ptr)(void)= null ;




void TIM0_Vid_FastPwm(u8 copy_u8_DutyCycle)
{
	/*selecting timer mode fast PWM*/
	SET_BIT(TCCR0_REG, 6);
	SET_BIT(TCCR0_REG, 3);
	
	/*compare output mode non inverting*/
	SET_BIT(TCCR0_REG, 5);
	CLR_BIT(TCCR0_REG, 4);
	
	/*set ocr0 register compare value which equals (DutyCycle(percent% ie. 25/100) = OCR/2^reslution) // or OCR = (2^reslution/100)*DustyCycle(without% ie. 25) */
	OCR0_REG = (f32)copy_u8_DutyCycle * 2.55;
	
	/*start timer*/
	TCCR0_REG&=0b11111000 ;
	TCCR0_REG|= _64_PRESCALER  ;
	
	/*wait until compare match*/
	while(GET_BIT(TIFR_REG, 1) == 0);
	
	SET_BIT(TIFR_REG, 1);
	
	
	
}



void TIM0_Vid_Start(u8 copy_u8_prescaler){
	
	TCCR0_REG&=0b11111000 ;
	TCCR0_REG|=copy_u8_prescaler ;
	
}

void TIM0_Vid_Stop(u8 copy_u8_prescaler) {
	
	TCCR0_REG&=0b11111000 ;
	TCCR0_REG|=NO_PRESCALER ;
}


void TIM0_Vid_Overflow_Init(void) {
	
	/* select prescaler  */
	TIM0_Vid_Start(_64_PRESCALER) ;
	
	/* enable global interrupt  */
	GIE_Vid_Enable() ;
	/* enable overflow interrupt*/
	SET_BIT(TIMSK_REG,0) ;
}


void TIM0_Vid_CTC_Init(void){
	/* select CTC mode  */
	SET_BIT(TCCR0_REG,3) ;
	CLR_BIT(TCCR0_REG,6) ;
	
	/* select prescaler  */
	TIM0_Vid_Start(_64_PRESCALER) ;

	/*OCR_VAL = assuming val form range 0 - 255 then mul by time tick (250 * 4 = 1000us / 1ms )  */
	OCR0_REG=OCR_VAL  ;
	
	/* enable global interrupt  */
	GIE_Vid_Enable() ;
	
	/* enable overflow interrupt*/
	SET_BIT(TIMSK_REG,1) ;
}


void TIM0_Vid_DelayMS(u32 delay)
{
	
	u32 OverFlow_Count = 0 ;
	
	u32 Num_Of_Overflowes = delay / 1.024 ;
	
	while(OverFlow_Count < Num_Of_Overflowes)
	{
		
		/* 1-timer start  */
		TIM0_Vid_Start(_64_PRESCALER) ;
	
		
		/*2- waiting to overflow happen */
		while(GET_BIT(TIFR_REG,0)==0) ;
		
		OverFlow_Count++ ;
		
		/*3- clear overflow flag  */
		SET_BIT(TIFR_REG,0) ;
		
	}
	TIM0_Vid_Stop(_64_PRESCALER);
	
	OverFlow_Count = 0;
}


void TIM0_Vid_CallBack(u8 mode , void(*ptr_fun)(void)){

	if(mode==CTC_MODE){
		
		CTC_ptr = ptr_fun ;
		
	}
	else if(mode==OV_MODE){
		overflow_ptr = ptr_fun ;
	}
	
}

ISR(TIMER0_OVF){
	
	//DIO_Vid_Toggle_Pin_Val(PORTA,PIN0) ;
	
	overflow_ptr() ;
	
	
}

ISR(TIMER0_COMP){
	
	CTC_ptr() ;
	
}