/*
 * APP.h
 *
 * Created: 11/29/2023 11:38:07 AM
 *  Author: Mahmoud Zain
 */ 


#ifndef APP_H_
#define APP_H_

#define F_CPU 16000000UL
#include <util/delay.h>

/*Include Needed MicroController Peripherals Drivers */
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/TIM0/TIM_Interface.h"
#include "../MCAL/TIM1/TIMER1_Interface.h"
#include "../MCAL/ADC/ADC_Interface.h"

/*Include Needed HardWare Drivers */
#include "../HAL/KEYPAD/KEYPAD_inteface.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/LED/LED.h"


void APP_Start(void);






#endif /* APP_H_ */