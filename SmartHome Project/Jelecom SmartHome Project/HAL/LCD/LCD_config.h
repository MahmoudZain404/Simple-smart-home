/*
 * LCD_config.h
 *
 * Created: 07/09/2023 19:18:07
 *  Author: FATHI
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


#if LCD_MODE == FOUR_BIT_MODE

#define LCD_DPORT   PORTA 
#define LCD_D4_PIN  PIN3
#define LCD_D5_PIN  PIN4
#define LCD_D6_PIN  PIN5
#define LCD_D7_PIN  PIN6

#endif 

#define LCD_DPORT   PORTA 

#define LCD_CPORT   PORTA

#define LCD_RS_PIN  PIN1 
//#define LCD_RW_PIN  PIN0 
#define LCD_E_PIN   PIN2 



#endif /* LCD_CONFIG_H_ */