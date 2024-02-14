/*
 * KEYPAD_inteCface.c
 *
 * CCeated: 18/09/2023 19:20:46
 *  Author: FATHI
 */ 
#include "../../MCAL/DIO/DIO_interface.h"
#include "KEYPAD_inteface.h" 


u8   Keypad_u8_data[4][4]={{7,8,9,'/'         },
	                       {4,5,6,'*'         },
						   {1,2,3,'-'         },
						   {'C',0,'=','+'    }};



void KEYPAD_Vid_Init(void)
{
	 
	 u8 Loc_u8RArray[4]={KEYPAD_R0_PIN,KEYPAD_R1_PIN,KEYPAD_R2_PIN,KEYPAD_R3_PIN} ; 
	 u8 Loc_u8CArray[4]={KEYPAD_C0_PIN,KEYPAD_C1_PIN,KEYPAD_C2_PIN,KEYPAD_C3_PIN} ; 
	 u8 Loc_u8_Rin=0 ; 	 
     u8 Loc_u8_Cin=0 ; 	 
	 
	    for(Loc_u8_Rin=0 ; Loc_u8_Rin<4;Loc_u8_Rin++)
		{
		    /* set ROWS--> INPUT  */
		    DIO_Vid_Set_Pin_Dir(KEYPAD_ROW_PORT,Loc_u8RArray[Loc_u8_Rin],INPUT) ; 
			
			/* ACTIVE PULLUP  */
			DIO_Vid_Set_Pin_Val(KEYPAD_ROW_PORT,Loc_u8RArray[Loc_u8_Rin],HIGH) ;
		}	 
		
	    for(Loc_u8_Cin=0 ; Loc_u8_Cin<4;Loc_u8_Cin++)
		{
			DIO_Vid_Set_Pin_Dir(KEYPAD_COL_PORT,Loc_u8CArray[Loc_u8_Cin],OUTPUT) ; 
			 
			DIO_Vid_Set_Pin_Val(KEYPAD_COL_PORT,Loc_u8CArray[Loc_u8_Cin],HIGH) ; 
		}
	
	
	
}

u8 KEYPAD_u8_GetKey(void)
{
	
	  u8 Loc_u8RArray[4]={KEYPAD_R0_PIN,KEYPAD_R1_PIN,KEYPAD_R2_PIN,KEYPAD_R3_PIN} ;
	  u8 Loc_u8CArray[4]={KEYPAD_C0_PIN,KEYPAD_C1_PIN,KEYPAD_C2_PIN,KEYPAD_C3_PIN} ;
	  u8 Loc_u8_Rin=0 ;
	  u8 Loc_u8_Cin=0 ;
	  u8 Loc_u8_val=0xff ; 
	  for(Loc_u8_Cin=0 ; Loc_u8_Cin<4;Loc_u8_Cin++)
	  {
		  
		      /* ACIVE COL(N) --->LOW */
		  DIO_Vid_Set_Pin_Val(KEYPAD_COL_PORT,Loc_u8CArray[Loc_u8_Cin],LOW) ; 
		  
		  
		  for(Loc_u8_Rin=0 ; Loc_u8_Rin<4;Loc_u8_Rin++)
		  {
			  if(DIO_u8_Get_Pin_Val(KEYPAD_ROW_PORT,Loc_u8RArray[Loc_u8_Rin])==0)
			  {
				  
				  Loc_u8_val=Keypad_u8_data[Loc_u8_Rin][Loc_u8_Cin] ; 
				  while(DIO_u8_Get_Pin_Val(KEYPAD_ROW_PORT,Loc_u8RArray[Loc_u8_Rin])==0) ; 
				  
				  return  Loc_u8_val ; 
			  } 
		  }
		DIO_Vid_Set_Pin_Val(KEYPAD_COL_PORT,Loc_u8CArray[Loc_u8_Cin],HIGH) ; 
	 }
	return Loc_u8_val ; 
}

/*
void str_cat(S8 *dest, const S8 *src)
{
	u8 i,j;
	for (i = 0; dest[i] != '\0'; i++)
	;
	for (j = 0; src[j] != '\0'; j++)
	dest[i+j] = src[j];
	dest[i+j] = '\0';
}
*/