/*
 * TIM1_Interface.h
 *
 * Created: 10/9/2023 8:51:49 PM
 *  Author: mahmo
 */ 


#ifndef TIM1_INTERFACE_H_
#define TIM1_INTERFACE_H_

#include "TIMER1_Interface.h"
#include "../LIB/MATH.h"



void (*InputCapture_Ptr)(void) = null;


void TIMER1_Vid_CAPT_EdgeSelect(u8 Edge)
{
	if (Edge == ISP_RISING_EDGE)
	{
		SET_BIT(TCCR1B_REG, 6);
	}
	
	if (Edge == ISP_FALLING_EDGE)
	{
		CLR_BIT(TCCR1B_REG, 6);
	}
}

void TIMER1_Vid_InputCAPT_CTC_Init(void)
{
	/* Normal mode  */
	CLR_BIT(TCCR1A_REG,0) ; // WGM10
	CLR_BIT(TCCR1A_REG,1) ; // WGM11
	CLR_BIT(TCCR1B_REG,3) ; // WGM12
	CLR_BIT(TCCR1B_REG,4) ; // WGM13

	/* prescaler 64*/
	SET_BIT(TCCR1B_REG,0) ; // CS10
	SET_BIT(TCCR1B_REG,1) ;	// CS11
	CLR_BIT(TCCR1B_REG,2) ;	// CS12
	
	
		
	/*Enable Input capture interrupt*/
	
	SET_BIT(TIMSK_REG, 5);
	
}



void TIMER1_Vid_NormalMode_Init()
{
	/* Normal mode  */
	CLR_BIT(TCCR1A_REG,0) ; // WGM10
	CLR_BIT(TCCR1A_REG,1) ; // WGM11
	CLR_BIT(TCCR1B_REG,3) ; // WGM12
	CLR_BIT(TCCR1B_REG,4) ; // WGM13
	
	/* prescaler 64*/
	SET_BIT(TCCR1B_REG,0) ; // CS10
	SET_BIT(TCCR1B_REG,1) ;	// CS11
	CLR_BIT(TCCR1B_REG,2) ;	// CS12
		
}

void TIMER1_Vid_RestVal()
{
	
	TCNT1_REG=0x00 ; 
	
}

u16  TIMER1_u16_ICR_ReadVal(void)
{
	
	return ICR_REG ;
	
}

u16  TIMER1_u16_ReadVal()
{
	
	return TCNT1_REG ; 
	
}


void TIMER1_Vid_FastPWM_ICR_Init(void)
{
	/*fast PWM mode*/
	SET_BIT(TCCR1A_REG, 7);
	CLR_BIT(TCCR1A_REG, 6);
	
	CLR_BIT(TCCR1A_REG, 0);
	SET_BIT(TCCR1A_REG, 1);
	SET_BIT(TCCR1B_REG, 3);
	SET_BIT(TCCR1B_REG, 4);
	
	
	ICR_REG = 40000;
	
	
	/*set prescaler 8*/
	
	CLR_BIT(TCCR1B_REG, 0); // prescler 64 SET this bit CS10
	SET_BIT(TCCR1B_REG, 1); // CS11
	CLR_BIT(TCCR1B_REG, 2); // CS12
	
}



void TIMER1_Vid_OCR1A_Val(u16 val)
{
	OCR1A_REG = val;
}






void TIMER1_Vid_FastPWM_10bit_res(u8 copy_u8_pin, u8 copy_u8_DC)
{
	//SET FAST PWM 10BIT RESOLUTION MODE
	SET_BIT(TCCR1A_REG,0) ; // WGM10
	SET_BIT(TCCR1A_REG,1) ; // WGM11
	SET_BIT(TCCR1B_REG,3) ; // WGM12
	CLR_BIT(TCCR1B_REG,4) ; // WGM13
	
	//set prescaler 8
	
	CLR_BIT(TCCR1B_REG, 0); // prescler 64 SET this bit CS10
	SET_BIT(TCCR1B_REG, 1); // CS11
	CLR_BIT(TCCR1B_REG, 2); // CS12
	switch(copy_u8_pin)
	{
		case (_OCR1A):
					SET_BIT(TCCR1A_REG, 7);
					CLR_BIT(TCCR1A_REG, 6);
					OCR1A_REG =(f32)copy_u8_DC*10.23;
					break;
		case (_OCR1B):
					SET_BIT(TCCR1A_REG, 5);
					CLR_BIT(TCCR1A_REG, 4);
					OCR1A_REG =(f32)copy_u8_DC*10.23;
					break;
	}
}






void TIMER1_Vid_SetCallBack(void (*Call_Ptr)(void))
{
	InputCapture_Ptr = Call_Ptr;
}


ISR(TIMER1_CAPT)
{
	InputCapture_Ptr();
}



#endif /* TIM1_INTERFACE_H_ */