/*
 * KEYPAD_inteface.h
 *
 * Created: 18/09/2023 19:20:18
 *  Author: fathi
 */ 


#ifndef KEYPAD_INTEFACE_H_
#define KEYPAD_INTEFACE_H_

#include "KEYPAD_config.h"



typedef enum EN_OPERATION_t
{
	DIV = 1,MUL,SUB,ADD
}EN_OPERATION_t;

void KEYPAD_Vid_Init(void) ; 

u8 KEYPAD_u8_GetKey(void) ; 

//void str_cat(S8 *dest, const S8 *src);

#endif /* KEYPAD_INTEFACE_H_ */