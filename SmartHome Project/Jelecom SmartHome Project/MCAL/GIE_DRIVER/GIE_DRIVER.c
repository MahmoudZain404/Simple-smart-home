/*
 * GIE_DRIVER.h
 *
 * Created: 9/21/2023 8:55:35 PM
 *  Author: User
 */ 


#include "GIE_DRIVER.h"



void GIE_Vid_Enable(void)
{
	//SET_BIT(SREG, I);
	
	__asm__ __volatile__("SEI");
	
}
void GIE_Vid_Disable(void)

{
	//CLR_BIT(SREG, I);
		
	__asm__ __volatile__("CLI");

}
