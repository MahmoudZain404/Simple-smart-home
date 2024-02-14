/*
 * LCD_interface.c
 *
 * Created: 07/09/2023 19:17:11
 *  Author: fathi
 */ 

 

#include "LCD_interface.h" 




              
static void LCD_Vid_Half_Data(u8 copy_u8_data){
	
	u8 Loc_u8_dataArr[4]={LCD_D4_PIN,LCD_D5_PIN,LCD_D6_PIN,LCD_D7_PIN} ; 
	u8 Loc_u8_index=0; 
	
	for(Loc_u8_index = 0; Loc_u8_index < 4; Loc_u8_index++)
	{
	
	  DIO_Vid_Set_Pin_Val(LCD_DPORT,Loc_u8_dataArr[Loc_u8_index],GET_BIT(copy_u8_data,Loc_u8_index)); 
	
	}	
}


void Send_Enable(){
	
	 /* SEND enable pulse  */
	 DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_E_PIN,HIGH) ;
	 _delay_ms(2) ;
	 DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_E_PIN,LOW) ;
}


void LCD_Vid_Send_Command(u8 copy_u8_command){
	
	  /* Active RS ---> LOW  to send command  */
	  DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_RS_PIN,LOW) ;
	  /* set RW --> low  to write in lcd */
	 // DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_RW_PIN,LOW) ; 
	  
	  #if LCD_MODE == FOUR_BIT_MODE 
	  
	   /* send HSB */
	  LCD_Vid_Half_Data(copy_u8_command>>4) ;
	  Send_Enable() ; 
	  
	    _delay_us(1);
	  
	  LCD_Vid_Half_Data(copy_u8_command) ;
	  Send_Enable() ; 
	  
	  #elif LCD_MODE == EIGHT_BIT_MODE	
	  
	  DIO_Vid_Set_Port_Val(LCD_DPORT,copy_u8_command) ; 
	  Send_Enable() ; 
	 
	  #endif 
}


void LCD_Vid_Send_Data(u8 copy_u8_data){
	
	  /* Active RS ---> HIGH  to send DATA  */
	  DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_RS_PIN,HIGH) ;
	  
	  /* set RW --> low  to write in LCD */
	//  DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_RW_PIN,LOW) ;
	  
	  #if LCD_MODE == FOUR_BIT_MODE
	  /* send HSB */
	  LCD_Vid_Half_Data(copy_u8_data>>4) ;
	  Send_Enable() ;
	  
	  _delay_us(1);
	  
	  LCD_Vid_Half_Data(copy_u8_data) ;
	  Send_Enable() ;

	  #elif LCD_MODE == EIGHT_BIT_MODE
	  
	  DIO_Vid_Set_Port_Val(LCD_DPORT,copy_u8_data) ;
	  
	  Send_Enable() ;
	  
	  #endif
	
}


void LCD_Vid_Init(void){
	
	_delay_ms(40) ; 
	
	#if LCD_MODE == FOUR_BIT_MODE 
	
	/* Function set  ( N :1  , F:0) */
	LCD_Vid_Half_Data(0b0010) ; 
	Send_Enable() ; 
	LCD_Vid_Half_Data(0b0010) ;
	Send_Enable() ;
	LCD_Vid_Half_Data(0b1000) ;
	Send_Enable() ;
	
	#elif LCD_MODE == EIGHT_BIT_MODE
	
	/* Function set  ( N :1  , F:0) */
	LCD_Vid_Send_Command(0x38) ; 
	
	#endif 
	
	/* display on/off control  D :1  B:0 C : 0  */
	LCD_Vid_Send_Command(0x0c) ;
	
	/* clr LCD  */
	LCD_Vid_Send_Command(1) ;
	
	LCD_Vid_Send_Command(0x06);
	
	
	
}


void LCD_Vid_Send_String( S8 *str) {
	
	u8 Loc_u8_Indiex = 0 ; 
	while (str[Loc_u8_Indiex]!='\0')
	{
		LCD_Vid_Send_Data(str[Loc_u8_Indiex]) ; 
		
		Loc_u8_Indiex ++ ;
	}

}


void LCD_Vid_Send_Custom_char(u8 copy_u8_location, u8 *char_arr)
{
	LCD_Vid_Send_Command((0x40+(copy_u8_location*8)));

	for (int i = 0; i<8; i++)
	{
		LCD_Vid_Send_Data(char_arr[i]);
	}
	LCD_Vid_Send_Command(0x80);
}


void LCD_Vid_Move_XY(u8 copy_u8_Col, u8 copy_u8_Row)
{
	u8 DDRAM_Add = 0;
	
	if(copy_u8_Col == 0)
	{
		DDRAM_Add = copy_u8_Row;
	}
	else
	{
		DDRAM_Add = 0x40 + copy_u8_Row;
	}
		
	
	LCD_Vid_Send_Command(0x80 + DDRAM_Add);
}



void LCD_Vid_Move_Cursor_To(u8 copy_u8_Row, u8 copy_u8_Col)
{
	if(copy_u8_Row == 1)
	{
		LCD_Vid_Send_Command((0x80|copy_u8_Col));
	}

	else if(copy_u8_Row == 2)
	{
		LCD_Vid_Send_Command((0x80|0x40|copy_u8_Col));

	}


}



void LCD_Vid_Send_Integer(u64 copy_u64_Value)
{
	s8 Local_s8_Iter = 0;
	
	u8 Local_u8_Buffer[50];

	
	if (copy_u64_Value == 0 )  //it means the number is 0
	{
		LCD_Vid_Send_Data('0');
	}
	
	
	while (copy_u64_Value != 0)
	{
		
		Local_u8_Buffer[Local_s8_Iter] = (copy_u64_Value % 10) + 48 ;
		
		copy_u64_Value = copy_u64_Value / 10;
		
		Local_s8_Iter++;
	}
	
	Local_s8_Iter --;
	 
	while(Local_s8_Iter >= 0)
	{
		
		LCD_Vid_Send_Data(Local_u8_Buffer[Local_s8_Iter]);
		
		Local_s8_Iter--;
	}
}



void LCD_Vid_FootBall_Game(void)
{
	u8 Loc_u8_Iter = 0;	
	const u8 Loc_u8_FPS = 200;

	u8 stand_Player[8] = {0b01110, 0b01110, 0b00100, 0b01110, 0b10101, 0b00100, 0b01010, 0b00000};
	u8 shoot_left[8]   = {0b01110, 0b01110, 0b00100, 0b01110, 0b10101, 0b01100, 0b10010, 0b00000};
	u8 shoot_right[8]  = {0b01110, 0b01110, 0b00100, 0b01110, 0b10101, 0b00110, 0b01001, 0b00000};
	u8 Ball[8]		   = {0b00000, 0b00000, 0b00000, 0b00000, 0b01110, 0b11111, 0b01110, 0b00000};
	u8 Goal[8]		   = {0b11111, 0b10110, 0b10100, 0b11000, 0b11000, 0b10100, 0b10010};
	u8 Left_Hand[8]	   = {0b01110,0b01110,0b10100,0b01110,0b00101,0b00100,0b01010,0b00000};	
	u8 erase[8]		   = {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000};
	u8 celebr[8]       = {0b01110,0b01110,0b10101,0b01110,0b00100,0b00100,0b01010,0b00000};
	
	LCD_Vid_Send_Custom_char(0, stand_Player);

	LCD_Vid_Send_Custom_char(1, shoot_left);

	LCD_Vid_Send_Custom_char(2, shoot_right);

	LCD_Vid_Send_Custom_char(3, Ball);

	LCD_Vid_Send_Custom_char(4, Goal);
	
	LCD_Vid_Send_Custom_char(5, erase);

	LCD_Vid_Send_Custom_char(6, Left_Hand);	
	
	LCD_Vid_Send_Custom_char(7, celebr);

	
	/*Draw Goal*/
	LCD_Vid_Move_Cursor_To(1, 0);
	LCD_Vid_Send_Data(GOAL);

	LCD_Vid_Move_Cursor_To(1, 8);
	LCD_Vid_Send_Data(PLAYER_STAND);
	
	
	LCD_Vid_Move_Cursor_To(2, 1);
	LCD_Vid_Send_Data(PLAYER_STAND);
	LCD_Vid_Send_Data(BALL);

	LCD_Vid_Move_Cursor_To(2, 6);
	LCD_Vid_Send_Data(PLAYER_STAND);
	_delay_ms(Loc_u8_FPS+100);
	LCD_Vid_Move_Cursor_To(2, 6);
	LCD_Vid_Send_Data(RIES_LEFT);
	
	LCD_Vid_Send_String("PASSS!!!");
	
	_delay_ms(Loc_u8_FPS);
	
	LCD_Vid_Move_Cursor_To(2, 1);
	_delay_ms(Loc_u8_FPS);
	LCD_Vid_Send_Data(PLAYER_SHOOT_RIGHT);
	_delay_ms(Loc_u8_FPS);
	LCD_Vid_Send_Data(Empty);
	
	LCD_Vid_Move_Cursor_To(2, 1);
	_delay_ms(Loc_u8_FPS);
	LCD_Vid_Send_Data(PLAYER_STAND);
	
	LCD_Vid_Move_Cursor_To(1, 3);
	LCD_Vid_Send_Data(BALL);
	_delay_ms(Loc_u8_FPS);
	
	LCD_Vid_Move_Cursor_To(1, 3);
	LCD_Vid_Send_Data(Empty);
	
	
	LCD_Vid_Move_Cursor_To(2, 6);
	LCD_Vid_Send_Data(PLAYER_STAND);
	LCD_Vid_Send_String("WTF Man!");
	_delay_ms(Loc_u8_FPS);
	
	for (Loc_u8_Iter = 4; Loc_u8_Iter < 7; Loc_u8_Iter++)
	{
		LCD_Vid_Move_Cursor_To(1, Loc_u8_Iter);
		LCD_Vid_Send_Data(BALL);
		_delay_ms(Loc_u8_FPS-100);
		LCD_Vid_Move_Cursor_To(1, Loc_u8_Iter);
		LCD_Vid_Send_Data(Empty);
		_delay_ms(Loc_u8_FPS-100);
	}
	
	LCD_Vid_Send_Data(BALL);
	
	LCD_Vid_Move_Cursor_To(2, 7);
	LCD_Vid_Send_String("WHAT!!!");
	_delay_ms(Loc_u8_FPS);
	
	LCD_Vid_Move_Cursor_To(1, 8);
	LCD_Vid_Send_Data(PLAYER_SHOOT_LEFT);
	_delay_ms(Loc_u8_FPS);
	LCD_Vid_Move_Cursor_To(1, 8);
	LCD_Vid_Send_Data(PLAYER_STAND);

	Loc_u8_Iter = 0;
	
	for (Loc_u8_Iter = 7; Loc_u8_Iter > 0; Loc_u8_Iter--)
	{
		LCD_Vid_Move_Cursor_To(1, Loc_u8_Iter);
		LCD_Vid_Send_Data(BALL);
		_delay_ms(Loc_u8_FPS-100);
		LCD_Vid_Move_Cursor_To(1, Loc_u8_Iter);
		LCD_Vid_Send_Data(Empty);
		_delay_ms(Loc_u8_FPS-100);
	}
	
	Loc_u8_Iter = 0;
	
	
	LCD_Vid_Send_Command(28);
	
	
	
	for (Loc_u8_Iter = 0; Loc_u8_Iter < 15; Loc_u8_Iter++)
	{
		LCD_Vid_Send_Command(28);
		_delay_ms(Loc_u8_FPS-100);
	}
	
	LCD_Vid_Send_Command(1);
	
	LCD_Vid_Move_Cursor_To(1, 0);
	LCD_Vid_Send_String("GOAAAAAALLLLL!!!");
	_delay_ms(Loc_u8_FPS);
	
	LCD_Vid_Move_Cursor_To(2, 0);
	LCD_Vid_Send_Data(CELEBRATE);
	_delay_ms(Loc_u8_FPS);
	
	LCD_Vid_Move_Cursor_To(2, 0);
	LCD_Vid_Send_Data(Empty);
	
	Loc_u8_Iter = 0;
	
	for (Loc_u8_Iter = 1; Loc_u8_Iter < 16; Loc_u8_Iter++)
	{
		LCD_Vid_Move_Cursor_To(2, Loc_u8_Iter);
		LCD_Vid_Send_Data(CELEBRATE);
		_delay_ms(Loc_u8_FPS-50);
		LCD_Vid_Move_Cursor_To(2, Loc_u8_Iter);
		LCD_Vid_Send_Data(Empty);
		_delay_ms(Loc_u8_FPS-50);
	}
	
	LCD_Vid_Send_Command(1);
	
	LCD_Vid_Move_Cursor_To(1, 2);
	LCD_Vid_Send_String("Created BY");
	_delay_ms(1000);
	
	LCD_Vid_Move_Cursor_To(2, 2);
	
	LCD_Vid_Send_String("Mahmoud Zain");
	_delay_ms(1000);
	
	for (Loc_u8_Iter = 0; Loc_u8_Iter < 15; Loc_u8_Iter++)
	{
		LCD_Vid_Send_Command(28);
		_delay_ms(Loc_u8_FPS-100);
	}
	
	LCD_Vid_Send_Command(1);
	
	LCD_Vid_Move_Cursor_To(1, 6);
	LCD_Vid_Send_String("AKA");
	
	LCD_Vid_Move_Cursor_To(2, 3);
	LCD_Vid_Send_String("SHADOW404");
	_delay_ms(1500);
	
	LCD_Vid_Send_Command(1);
	
	
	LCD_Vid_Send_String("  THANKS FOR");
	LCD_Vid_Move_Cursor_To(2, 4);
	LCD_Vid_Send_String("WATCHING!");

}
