#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "PORT_interface.h"
#include "GIE_interface.h"

#include "CLCD_interface.h"
#include "KPD_interface.h"

void INT0_ISR(void);
void INT1_ISR(void);

u8 Bat1_Pos=0;
u8 Bat2_Pos=0;

void main(void){
	u8 Local_u8Key;
	u8 Local_u8Bat1[8]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	u8 Local_u8Bat2[8]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	char Local_u8Ball ='+';
	PORT_voidInit();
	CLCD_voidInit();
	EXTI_voidInt0Init();
	EXTI_voidInt1Init();
	GIE_voidEnable();
	EXTI_u8Int0SetCallBack(&INT0_ISR);
	EXTI_u8Int1SetCallBack(&INT1_ISR);
	CLCD_voidWriteSpecialCharacter(&Local_u8Bat1,0);
	CLCD_voidSendSpecialCharacter(0,0,0);
	CLCD_voidWriteSpecialCharacter(&Local_u8Bat2,1);
	CLCD_voidSendSpecialCharacter(1,0,15);
	while(1){
		Bat1_Pos=0;Bat2_Pos=0;
		CLCD_voidGoToXY(0,1);
		CLCD_voidSendData(Local_u8Ball);
		_delay_ms(500);
		for(u8 Local_u8Iterator=1;Local_u8Iterator<14;Local_u8Iterator++){
			CLCD_voidGoToXY(0,Local_u8Iterator);
			CLCD_voidSendData(' ');
			CLCD_voidSendData(Local_u8Ball);
			_delay_ms(500);
		}
		if(Bat2_Pos==1){
			CLCD_voidGoToXY(0,14);
			CLCD_voidSendData(' ');
			CLCD_voidSendData(Local_u8Ball);
			_delay_ms(500);
			CLCD_voidSendCommand(1);
			CLCD_voidSendString("Player 2 LOSES");
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("Press any Key");
			do{
				Local_u8Key = KPD_u8GetPressedKey();
			}while(Local_u8Key==0xff);
			CLCD_voidSendCommand(1);
			CLCD_voidWriteSpecialCharacter(&Local_u8Bat1,0);
			CLCD_voidSendSpecialCharacter(0,0,0);
			CLCD_voidWriteSpecialCharacter(&Local_u8Bat2,1);
			CLCD_voidSendSpecialCharacter(1,0,15);
		}
		for(u8 Local_u8Iterator=14;Local_u8Iterator>1;Local_u8Iterator--){
			CLCD_voidGoToXY(0,Local_u8Iterator);
			CLCD_voidSendData(' ');
			CLCD_voidGoToXY(0,Local_u8Iterator-1);
			CLCD_voidSendData(Local_u8Ball);
			_delay_ms(500);
		}
		if(Bat1_Pos==1){
			CLCD_voidGoToXY(0,1);
			CLCD_voidSendData(' ');
			CLCD_voidGoToXY(0,0);
			CLCD_voidSendData(Local_u8Ball);
			_delay_ms(500);
			CLCD_voidSendCommand(1);
			CLCD_voidSendString("Player 1 LOSES");
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("Press any Key");
			do{
				Local_u8Key = KPD_u8GetPressedKey();
			}while(Local_u8Key==0xff);
			CLCD_voidSendCommand(1);
			CLCD_voidWriteSpecialCharacter(&Local_u8Bat1,0);
			CLCD_voidSendSpecialCharacter(0,0,0);
			CLCD_voidWriteSpecialCharacter(&Local_u8Bat2,1);
			CLCD_voidSendSpecialCharacter(1,0,15);
		}
	}
}


void INT0_ISR(void){
	if(Bat1_Pos==0){
		CLCD_voidGoToXY(0,0);
		CLCD_voidSendData(' ');
		CLCD_voidSendSpecialCharacter(0,1,0);
		Bat1_Pos=1;
	}
	else if(Bat1_Pos==1){
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendData(' ');
		CLCD_voidSendSpecialCharacter(0,0,0);
		Bat1_Pos=0;
	}
}

void INT1_ISR(void){
	if(Bat2_Pos==0){
		CLCD_voidGoToXY(0,15);
		CLCD_voidSendData(' ');
		CLCD_voidSendSpecialCharacter(0,1,15);
		Bat2_Pos=1;
	}
	else if(Bat2_Pos==1){
		CLCD_voidGoToXY(1,15);
		CLCD_voidSendData(' ');
		CLCD_voidSendSpecialCharacter(0,0,15);
		Bat2_Pos=0;
	}

}
