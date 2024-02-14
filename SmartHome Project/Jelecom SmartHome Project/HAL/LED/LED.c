/*
 * LED.c
 *
 * Created: 9/4/2023 7:19:52 PM
 *  Author: Jelecom
 */ 

#include "LED.h"

void LED_Vid_Init(u8 copy_u8_port,u8 copy_u8_pin)
{
	DIO_Vid_Set_Pin_Dir(copy_u8_port, copy_u8_pin, OUTPUT);
}

void LED_Vid_On (u8 copy_u8_port,u8 copy_u8_pin)
{
	DIO_Vid_Set_Pin_Val(copy_u8_port,  copy_u8_pin, HIGH);
}

void LED_Vid_Off (u8 copy_u8_port,u8 copy_u8_pin)
{
	DIO_Vid_Set_Pin_Val(copy_u8_port,  copy_u8_pin, LOW);
}

void LED_Vid_Toggle (u8 copy_u8_port,u8 copy_u8_pin)
{
	DIO_Vid_Toggle_Pin_Val(copy_u8_port, copy_u8_pin);
}

void Toggle_LED(void)
{
	DIO_Vid_Toggle_Pin_Val(PORTC, PIN0);
	
} 