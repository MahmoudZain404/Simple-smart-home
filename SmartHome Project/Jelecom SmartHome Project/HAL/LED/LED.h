/*
 * LED.h
 *
 * Created: 9/4/2023 7:20:49 PM
 *  Author: Jelecom
 */
#ifndef LED_H_
#define LED_H_


#include "../../MCAL/DIO/DIO_interface.h"

void LED_Vid_Init (u8 copy_u8_port,u8 copy_u8_pin);
void LED_Vid_On (u8 copy_u8_port,u8 copy_u8_pin);
void LED_Vid_Off (u8 copy_u8_port,u8 copy_u8_pin);
void LED_Vid_Toggle (u8 copy_u8_port,u8 copy_u8_pin);

void Toggle_LED(void);
#endif
