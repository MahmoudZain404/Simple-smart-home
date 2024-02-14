/*
 * DIO_interface.c
 *
 * Created: 9/3/2023 7:56:56 PM
 *  Author: mahmo
 */ 



#include "DIO_interface.h"


void DIO_Vid_Set_Pin_Dir(u8 copy_u8_port,u8 copy_u8_pin,u8 copy_u8_dir)
{
	
	if(copy_u8_dir==OUTPUT || copy_u8_dir==INPUT)
	{
		if(copy_u8_dir==OUTPUT)
		{
			
			switch(copy_u8_port)
			{
				case PORTA: SET_BIT(DDRA_REG,copy_u8_pin); break;
				case PORTB: SET_BIT(DDRB_REG,copy_u8_pin); break;
				case PORTC: SET_BIT(DDRC_REG,copy_u8_pin); break;
				case PORTD: SET_BIT(DDRD_REG,copy_u8_pin); break;
			}	
		}
		else
		{
			switch(copy_u8_port)
			{
				case PORTA: CLR_BIT(DDRA_REG,copy_u8_pin); break;
				case PORTB: CLR_BIT(DDRB_REG,copy_u8_pin); break;
				case PORTC: CLR_BIT(DDRC_REG,copy_u8_pin); break;
				case PORTD: CLR_BIT(DDRD_REG,copy_u8_pin); break;
			}
		}
	}
}

void DIO_Vid_Set_Pin_Val(u8 copy_u8_port,u8 copy_u8_pin,u8 copy_u8_val)
{
	if(copy_u8_val==HIGH || copy_u8_val==LOW )
	{
		if(copy_u8_val==HIGH)
		{
			
			switch(copy_u8_port)
			{
				case PORTA: SET_BIT(PORTA_REG,copy_u8_pin); break;
				case PORTB: SET_BIT(PORTB_REG,copy_u8_pin); break;
				case PORTC: SET_BIT(PORTC_REG,copy_u8_pin); break;
				case PORTD: SET_BIT(PORTD_REG,copy_u8_pin); break;
			}
			
		}
		
		else
		{
			
			switch(copy_u8_port)
			{
				case PORTA: CLR_BIT(PORTA_REG,copy_u8_pin); break;
				case PORTB: CLR_BIT(PORTB_REG,copy_u8_pin); break;
				case PORTC: CLR_BIT(PORTC_REG,copy_u8_pin); break;
				case PORTD: CLR_BIT(PORTD_REG,copy_u8_pin); break;
				
			}
		}
	}
}


u8 DIO_u8_Get_Pin_Val(u8 copy_u8_port,u8 copy_u8_pin)
{
	u8 Loc_u8_val = 0;
	
	switch(copy_u8_port)
	{
		case PORTA: Loc_u8_val=GET_BIT(PINA_REG,copy_u8_pin); break;
		case PORTB: Loc_u8_val=GET_BIT(PINB_REG,copy_u8_pin); break;
		case PORTC: Loc_u8_val=GET_BIT(PINC_REG,copy_u8_pin); break;
		case PORTD: Loc_u8_val=GET_BIT(PIND_REG,copy_u8_pin); break;	
	}
	return Loc_u8_val  ;
}


void DIO_Vid_Toggle_Pin_Val(u8 copy_u8_port,u8 copy_u8_pin)
{
	switch(copy_u8_port)
	{
		case PORTA: TOGGLE_BIT(PORTA_REG,copy_u8_pin); break;
		case PORTB: TOGGLE_BIT(PORTB_REG,copy_u8_pin); break;
		case PORTC: TOGGLE_BIT(PORTC_REG,copy_u8_pin); break;
		case PORTD: TOGGLE_BIT(PORTD_REG,copy_u8_pin); break;
	}
}


void DIO_Vid_Set_Port_Dir(u8 copy_u8_port, u8 copy_u8_dir)
{
	
	switch(copy_u8_port)
	{
		case PORTA: DDRA_REG = copy_u8_dir; break;
		case PORTB: DDRB_REG = copy_u8_dir; break;
		case PORTC: DDRC_REG = copy_u8_dir; break;
		case PORTD: DDRD_REG = copy_u8_dir; break;
	}
}



void DIO_Vid_Set_Port_Val(u8 copy_u8_port, u8 copy_u8_val)
{

	switch(copy_u8_port)
	{
		
		case PORTA: PORTA_REG = copy_u8_val; break;
		case PORTB: PORTB_REG = copy_u8_val; break;
		case PORTC: PORTC_REG = copy_u8_val; break;
		case PORTD: PORTD_REG = copy_u8_val; break;
	}
}

