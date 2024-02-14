/*
 * LCD_interface.h
 *
 * Created: 07/09/2023 19:17:53
 *  Author: fathi
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "LCD_config.h"
#include "../../MCAL/DIO/DIO_interface.h"
#define  F_CPU 16000000UL

#include <util/delay.h>

#define  FOUR_BIT_MODE      0 
#define  EIGHT_BIT_MODE     1

#define  LCD_MODE    FOUR_BIT_MODE 

#define PLAYER_STAND 0
#define PLAYER_SHOOT_LEFT  1
#define PLAYER_SHOOT_RIGHT 2
#define BALL 3
#define GOAL 4
#define Empty 5
#define RIES_LEFT 6
#define CELEBRATE 7
			

void LCD_Vid_Init(void); 

void LCD_Vid_Send_Data(u8 copy_u8_data);

void LCD_Vid_Send_Command(u8 copy_u8_command);

void LCD_Vid_Send_String( char *str); 

void LCD_Vid_FootBall_Game(void);

void LCD_Vid_Move_Cursor_To(u8 copy_u8_Col, u8 copy_u8_Row);

void LCD_Vid_Send_Custom_char(u8 copy_u8_location, u8 *char_arr);

void LCD_Vid_Send_Integer(u64 copy_u32_Value);

void LCD_Vid_Move_XY(u8 copy_u8_Col, u8 copy_u8_Row);

#endif /* LCD_INTERFACE_H_ */