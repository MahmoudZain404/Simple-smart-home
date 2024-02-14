/*
 * APP.c
 *
 * Created: 11/29/2023 11:37:57 AM
 *  Author: Mahmoud Zain
 */ 


#include "APP.h"



void APP_Start(void)
{
		u8 Lock[8]   =	{0b01110, 0b10001, 0b10001, 0b11111, 0b11011, 0b11011, 0b11111, 0b00000};
		u8 Unlock[8] =  {0b01110, 0b10000, 0b10000, 0b11111, 0b11011, 0b11011, 0b11111, 0b00000};
		u8 sunny[8]  =	{0b10101, 0b01110, 0b11111, 0b11111, 0b11111, 0b01110, 0b10101, 0b00000};
		u8 AC[8]     =	{0b01000, 0b10100, 0b11100, 0b10100, 0b00111, 0b00100, 0b00111, 0b00000};
		u8 LAMP[8]   =	{0b10101, 0b01110, 0b11111, 0b11111, 0b11111, 0b01110, 0b00100, 0b00000};
		u8 Moon[8]   =	{0b01000, 0b00100, 0b00110, 0b00110, 0b00100, 0b01000, 0b00000, 0b00000};
		u8 nal[8]   =	{0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000};
	
		//GREEN LED PC / RED LED PC 0 / Buzzer PC5
		LED_Vid_Init(PORTC, PIN0);
		LED_Vid_Init(PORTC, PIN1);
		DIO_Vid_Set_Pin_Dir(PORTC, PIN2, OUTPUT); // AC REALAY
		DIO_Vid_Set_Pin_Dir(PORTC, PIN3, OUTPUT); // LIGHTS RELAY
		DIO_Vid_Set_Pin_Dir(PORTC, PIN5, OUTPUT); // Buzzer
		DIO_Vid_Set_Pin_Dir(PORTC, PIN4, INPUT);  // MQ-5 Gas Sensor
		DIO_Vid_Set_Pin_Dir(PORTD, PIN5, OUTPUT); // OC1A PWM

		//LCD
		DDRA_REG = 0b01111110;
		DIO_Vid_Set_Pin_Dir(LCD_CPORT, LCD_RS_PIN, OUTPUT);
		DIO_Vid_Set_Pin_Dir(LCD_CPORT, LCD_E_PIN, OUTPUT);



		LCD_Vid_Init();


		LCD_Vid_Send_Custom_char(0, Lock); // send custom character to lcd memory
		LCD_Vid_Send_Custom_char(1, Unlock);
		LCD_Vid_Send_Custom_char(2, sunny);
		LCD_Vid_Send_Custom_char(3, AC);
		LCD_Vid_Send_Custom_char(4, LAMP);
		LCD_Vid_Send_Custom_char(5, nal);
		LCD_Vid_Send_Custom_char(6, Moon);
	


		//Keypad
		KEYPAD_Vid_Init();
		u16 Key_val = 0;
		u8 Sec_Dig = 0;
		u8 Sec_Dig_Flag = 0;
		u8 Num_Of_Tries = 1;
		const u16 Password = 4466;
		u16 User_Input = 0;


		LCD_Vid_Send_String("Enter Password:");
		LCD_Vid_Move_XY(1,0);
	
	
		//ADC
		u16 ADC_Val = 0;
		ADC_Void_Init(PIN7);
		ADC_Void_Init(PIN0);

	
	
		//timer1
		TIMER1_Vid_FastPWM_ICR_Init();
		u16 ServoMotorAngle;
		TIMER1_Vid_OCR1A_Val(2999);
		
		//POWER ON LED ON
		LED_Vid_On(PORTC, PIN0);
		
		//Sensors Threshold
		u8 TempSensor_Threshold = 30; 
		u16 LDRSensor_Threshold = 1023;
		u8 MQ5Sensor_Threshold = 1;
		while(1)
		{
			if (Num_Of_Tries <=3 && Num_Of_Tries >=1)
			{
				Key_val = KEYPAD_u8_GetKey();

				switch(Key_val)
				{
					case (0xff):break;

					case (61): // =

					if (User_Input == Password)
					{
						User_Input = 0;
						LCD_Vid_Send_Command(1);
					
						LCD_Vid_Send_String("Correct Password");
						LCD_Vid_Move_XY(1,8);
						LCD_Vid_Send_Data(1);
						TIM0_Vid_DelayMS(500);
					
						LCD_Vid_Send_Command(1); // clear lcd screen
						LCD_Vid_Send_String("  WELCOME TO ");
						LCD_Vid_Move_XY(1, 0);
						LCD_Vid_Send_String("  SMART HOME!");
						TIM0_Vid_DelayMS(300);
						LCD_Vid_Send_Command(1);
						
						LCD_Vid_Send_String("GATE OPENS...");
						
						ServoMotorAngle = 5200;
						
						TIMER1_Vid_OCR1A_Val(ServoMotorAngle);
						TIM0_Vid_DelayMS(300);
							
						ServoMotorAngle = 0;
					
						LCD_Vid_Send_Command(1);
					
						LCD_Vid_Send_String("Temp:");
						while(1)
						{
							ADC_Val  = ADC_Void_Read(0);
							ADC_Val  = (ADC_Val * 500 ) / 1023;
						
							LCD_Vid_Move_XY(0, 5);
							LCD_Vid_Send_Integer(ADC_Val);

							LCD_Vid_Send_String("'C");
						
							if (ADC_Val > TempSensor_Threshold)
							{
								DIO_Vid_Set_Pin_Val(PORTC, PIN2, HIGH); //AC ON
								LCD_Vid_Move_XY(1, 0);
								LCD_Vid_Send_String("Temp Increased!  ");	
								
								LCD_Vid_Move_XY(0, 10);
								LCD_Vid_Send_Data(3); // AC icon
															
								//DIO_Vid_Set_Pin_Val(PORTC, PIN5, HIGH); //Alarm ON
								TIM0_Vid_DelayMS(200);
								//DIO_Vid_Set_Pin_Val(PORTC, PIN5, LOW); //Alarm OFF
							}
							else
							{
								LCD_Vid_Move_XY(0, 10);
								LCD_Vid_Send_Data(5); //null icon
								DIO_Vid_Set_Pin_Val(PORTC, PIN2, LOW); //AC OFF
							}
						
							if (ADC_Void_Read(7) == LDRSensor_Threshold)
							{
								LCD_Vid_Move_XY(0, 12); // lamp
								LCD_Vid_Send_Data(4); // lamp
								LCD_Vid_Move_XY(0, 15); // sun Position
								LCD_Vid_Send_Data(6); // sun off / moon on
								
								DIO_Vid_Set_Pin_Val(PORTC, PIN3, HIGH); // Turn On Lights
								if (ADC_Val <= TempSensor_Threshold && GET_BIT(PINC_REG, PIN4) != MQ5Sensor_Threshold)
								{
									LCD_Vid_Move_XY(1, 0);
									LCD_Vid_Send_String("Good Night     ");
								}
							}
							else
							{
								LCD_Vid_Move_XY(0, 12);
								LCD_Vid_Send_Data(5);// null icon
							
								LCD_Vid_Move_XY(0, 15);//sun on
								LCD_Vid_Send_Data(2);//sun on / moon off
							
								DIO_Vid_Set_Pin_Val(PORTC, PIN3, LOW); // Turn Off Lights
								
								if (ADC_Val <= TempSensor_Threshold && GET_BIT(PINC_REG, PIN4) != MQ5Sensor_Threshold)
								{
									LCD_Vid_Move_XY(1, 0);
									LCD_Vid_Send_String("Good Morning   ");
								}
							}
							
							if ( GET_BIT(PINC_REG, PIN4) == MQ5Sensor_Threshold)
							{
								LCD_Vid_Move_XY(1, 0);
								LCD_Vid_Send_String("GAS DETECTED!  ");
								
								DIO_Vid_Set_Pin_Val(PORTC, PIN5, HIGH); //Alarm ON
								TIM0_Vid_DelayMS(200);
								DIO_Vid_Set_Pin_Val(PORTC, PIN5, LOW); //Alarm OFF
							}
							
							LED_Vid_Toggle(PORTC, PIN1); // toggle green LED program is running
						}
					}
					else
					{
					
						User_Input = 0;
						Num_Of_Tries++;
						LCD_Vid_Send_Command(1);
						LCD_Vid_Send_String("Wrong Password ");
						LCD_Vid_Move_XY(1,8);
						LCD_Vid_Send_Data(0); // lock icon
						TIM0_Vid_DelayMS(150);
						DIO_Vid_Set_Pin_Val(PORTC, PIN5, HIGH); // Turn on Buzzer
						TIM0_Vid_DelayMS(300);
						DIO_Vid_Set_Pin_Val(PORTC, PIN5, LOW); // Turn off Buzzer
						if (Num_Of_Tries <= 3)
						{
							LCD_Vid_Send_Command(1);
							LCD_Vid_Send_String("Please Try Again");
						
					
							
							TIM0_Vid_DelayMS(100);
							LCD_Vid_Send_Command(1);
							LCD_Vid_Send_String("Enter Password:");
							LCD_Vid_Move_XY(1,0);
						}
					
					}
					break;

					default:
					if(Sec_Dig_Flag == 0)
					{
						User_Input = Key_val;
						Sec_Dig_Flag = 1;
					}
					else
					{
						Sec_Dig = Key_val;
						User_Input = (User_Input * 10) + Sec_Dig;
					}
					LCD_Vid_Send_Integer(Key_val);
					break;
				}
			
			}
			else
			{
				LCD_Vid_Send_Command(1);
				LCD_Vid_Send_String("You've exceeded");
				LCD_Vid_Move_XY(1,0);
				LCD_Vid_Send_String("Number of tries");
				TIM0_Vid_DelayMS(800);
				LCD_Vid_Send_Command(1);
				LCD_Vid_Move_XY(1,8);
				LCD_Vid_Send_Data(0); // send custom character to LCD SCREEN
				while(1)
				{
					LED_Vid_On(PORTC, PIN0);
					//DIO_Vid_Set_Pin_Val(PORTC, PIN5, HIGH);
				}
			}
		}
	}