/*
 * ADC_Interface.c
 *
 * Created: 9/25/2023 8:50:50 PM
 *  Author: mahmo
 */ 

#include "ADC_Interface.h"


void static (*ADC_Call_Back_Ptr)(S8*); //ADC PTR to function

void ADC_Void_Init(u8 copy_u8_channel)				/* ADC Initialization function */
{
	DIO_Vid_Set_Pin_Dir(PORTA, copy_u8_channel, INPUT);		/* Make ADC port as input */
	
	CLR_BIT(ADMUX_REG,7) ;
	SET_BIT(ADMUX_REG,6) ;			/* Vref: Avcc*/
	
	ADCSRA_REG |= (1<< 7)|(1<< 3)|(1<< 2)|(1<< 1);			/* Enable ADC, with freq/128, and enable interrupt  |(1<< 0)*/
	
}

u16 ADC_Void_Read(u8 copy_u8_channel)		/* ADC Read function */
{
	ADMUX_REG = (1<< 6) | (copy_u8_channel & 0x07);/* set input channel to read */
	ADCSRA_REG |= (1<<6);		/* Start ADC conversion */
	while (!(ADCSRA_REG & (1<<4)));	/* Wait until end of conversion */
	ADCSRA_REG |= (1<<4);		/* Clear interrupt flag */
	
	return ADCW_REG;			/* Return ADC word */
}

void ADC_Vid_ADC_CallBack(void (*CallBack)(S8*))
{
	ADC_Call_Back_Ptr = CallBack;
}

ADC_ISR(ADC_INT_16)
{
	DIO_Vid_Set_Pin_Val(PORTC, PIN1,LOW);
	DIO_Vid_Set_Pin_Val(PORTC, PIN0,HIGH);
	
	ADC_Call_Back_Ptr("Now ADC ISR()");
	
	//main();
}