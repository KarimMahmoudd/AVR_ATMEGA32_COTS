/************************************************************************************************************************/
/************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            **********************************************/
/******************************           Layer: HAL                       **********************************************/
/******************************           SWC: CLCD                        **********************************************/
/******************************           Version: 1.00                    **********************************************/
/******************************           Date: 9/10/2022                  **********************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"



void CLCD_voidSendCommand(u8 Copy_u8Command){
	/*set RS pin to low for command*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);
	/*set RW pin to low for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
	/*set data port to command*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Command);
	/*send enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
}

void CLCD_voidSendData(u8 Copy_u8Data){
	/*set RS pin to high for data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);
	/*set RW pin to low for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
	/*set data port to data*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);
	/*send enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
}
void CLCD_voidSendString(const char* Copy_pcString){
	while(*Copy_pcString != '\0'){
		CLCD_voidSendData(*Copy_pcString);
		Copy_pcString++;
	}
}
void CLCD_voidInit(void){
	/*wait for more than 30 ms*/
	_delay_ms(40);
	/*Function Set Command: 2 lines, 5*8 Font Size*/
	CLCD_voidSendCommand(0b00111000);
	/*Display control on off: enable display disable cursor no blinking cursor*/
	CLCD_voidSendCommand(0b00001100);
	/*clear display*/
	CLCD_voidSendCommand(1);


}

void CLCD_voidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos){
	/*converting the position into an address*/
	u8 Local_u8Adress;
	if(Copy_u8XPos==0){
		Local_u8Adress = Copy_u8YPos;
	}
	else if(Copy_u8XPos==1){
		Local_u8Adress = Copy_u8YPos+0x40;
	}
	/*setting the 7th bit so we can send the set ddram address command*/
	SET_BIT(Local_u8Adress,7);
	CLCD_voidSendCommand(Local_u8Adress);
}

void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Arr,u8 Copy_u8PatternNumber){
	u8 Local_u8Iterator;
	/*calculate CGRAM address of block 8 bytes*/
	u8 Local_u8CGRAMAdress = Copy_u8PatternNumber*8;
	/*set bit 6 for command and set the CGRAM address command*/
	SET_BIT(Local_u8CGRAMAdress,6);
	CLCD_voidSendCommand(Local_u8CGRAMAdress);
	/*write the pattern on CGRAM*/
	for(Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++){
		CLCD_voidSendData(Copy_pu8Arr[Local_u8Iterator]);
	}
}
void CLCD_voidSendSpecialCharacter(u8 Copy_u8PatternNumber,u8 Copy_u8XPos,u8 Copy_u8YPos){
	/*go back to ddram to display pattern and send pattern by choosing battern blovk*/
	CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);
	CLCD_voidSendData(Copy_u8PatternNumber);
}


void CLCD_voidSendNumber(u32 Copy_u32Number){
	/*set local variables to know the number of digits and the digit to print*/
	u8 Local_u8Quotient=1;
	u8 Local_u8NumOfDigits=0;
    u8 Local_u8Digit;
    /*calculating the number of digits in the number*/
	while(Local_u8Quotient!=0){
		Local_u8Quotient = Copy_u32Number/CLCD_u32Power(10,++Local_u8NumOfDigits);
	}
	/*separating each digit then sending then sending them separately to the CLCD*/
	for(s32 Local_u8Power =Local_u8NumOfDigits-1;Local_u8Power>=0;Local_u8Power--){
	        Local_u8Digit=Copy_u32Number/CLCD_u32Power(10,Local_u8Power);
	        Copy_u32Number %= CLCD_u32Power(10,Local_u8Power);
	        Local_u8Digit+=48;
	        CLCD_voidSendData(Local_u8Digit);
	    }
}

u32 CLCD_u32Power(u32 Copy_u32Base,s32 Copy_u32Exponent){
	u32 Local_u32Result=1;
	for(u32 i=0;i<Copy_u32Exponent;i++){
		Local_u32Result*=Copy_u32Base;
	}
	return Local_u32Result;
}
