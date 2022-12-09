#include "STD_TYPES.h"
#include <util/delay.h>

#include "PORT_interface.h"
#include "DIO_interface.h"

#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "DCM_Interface.h"
#include "STPR_Interface.h"

void ShowMainMenu();
void ShowRotateMenu();
void ReadKey(u8* Copy_pu8Key);
u32 u32Power(u32 Copy_u32Base,s32 Copy_u32Exponent);

void main(){
	u8 Local_u8Key,Local_u8AngleArr[3],Local_u8AngleIterator;u16 Local_u8Angle;
	PORT_voidInit();
	CLCD_voidInit();
	ShowMainMenu();

	while(1){
		ReadKey(&Local_u8Key);
		if(Local_u8Key==1){
			ShowRotateMenu();
			ReadKey(&Local_u8Key);
			if(Local_u8Key==1){
				DCM_voidRotateClockwise();
			}
			else if(Local_u8Key==2){
				DCM_voidRotateCounterClockwise();
			}
			CLCD_voidSendCommand(1);
			CLCD_voidSendString("Press Any Key");
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("To Stop");
			ReadKey(&Local_u8Key);
			DCM_voidStop();
			ShowMainMenu();
		}
		else if(Local_u8Key==2){
			ShowRotateMenu();
			ReadKey(&Local_u8Key);
			if (Local_u8Key==1){
				CLCD_voidSendCommand(1);
				CLCD_voidSendString("Angle:");
				Local_u8AngleIterator=0;
				do{
					ReadKey(&Local_u8Key);
					if(Local_u8Key!='e'){
						Local_u8AngleArr[Local_u8AngleIterator]=Local_u8Key;
						CLCD_voidSendNumber(Local_u8Key);
						Local_u8AngleIterator++;
					}
				}while(Local_u8Key!='e');
				Local_u8Angle=0;
				for(u8 Local_u8Iterator=0;Local_u8Iterator<Local_u8AngleIterator;Local_u8Iterator++){

					Local_u8Angle+=(u32Power(10,Local_u8AngleIterator-Local_u8Iterator-1))*Local_u8AngleArr[Local_u8Iterator];
				}
				STPR_voidRotateAngle(STPR_CLOCKWISE,Local_u8Angle);
				for(u8 Local_u8Iterator=0;Local_u8Iterator<3;Local_u8Iterator++){
					Local_u8AngleArr[Local_u8Iterator]=0;
				}
				ShowMainMenu();
			}
			else if(Local_u8Key==2){
				CLCD_voidSendCommand(1);
				CLCD_voidSendString("Angle:");
				Local_u8AngleIterator=0;
				do{
					ReadKey(&Local_u8Key);
					if(Local_u8Key!='e'){
						Local_u8AngleArr[Local_u8AngleIterator]=Local_u8Key;
						CLCD_voidSendNumber(Local_u8Key);
						Local_u8AngleIterator++;
					}
				}while(Local_u8Key!='e');
				Local_u8Angle=0;
				for(u8 Local_u8Iterator=0;Local_u8Iterator<Local_u8AngleIterator;Local_u8Iterator++){
					Local_u8Angle+=(u32Power(10,Local_u8AngleIterator-Local_u8Iterator-1))*Local_u8AngleArr[Local_u8Iterator];
				}
				STPR_voidRotateAngle(STPR_COUNTER_CLOCKWISE,Local_u8Angle);
				for(u8 Local_u8Iterator=0;Local_u8Iterator<3;Local_u8Iterator++){
					Local_u8AngleArr[Local_u8Iterator]=0;
				}
				ShowMainMenu();
			}
		}
		else if(Local_u8Key==3){
			CLCD_voidSendCommand(1);
			CLCD_voidSendString("Thank you for");
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("using the app");
			_delay_ms(2000);
			CLCD_voidSendCommand(1);
		}
	}
}

void ShowMainMenu(){
	CLCD_voidSendCommand(1);
	CLCD_voidSendString("Welcome to motor");
	CLCD_voidGoToXY(1,0);
	CLCD_voidSendString("Dashboard App");
	_delay_ms(4000);
	CLCD_voidSendCommand(1);
	CLCD_voidSendString("for DC Motor>1");
	CLCD_voidGoToXY(1,0);
	CLCD_voidSendString("Stepper>2 Exit>3");
}

void ShowRotateMenu(){
	CLCD_voidSendCommand(1);
	CLCD_voidSendString("Rotate CW->1");
	CLCD_voidGoToXY(1,0);
	CLCD_voidSendString("Rotate CCW->2");
}

void ReadKey(u8* Copy_pu8Key){
	do{
		*Copy_pu8Key=KPD_u8GetPressedKey();
	}while(*Copy_pu8Key==0xff);
}

u32 u32Power(u32 Copy_u32Base,s32 Copy_u32Exponent){
	u32 Local_u32Result=1;
	for(u32 i=0;i<Copy_u32Exponent;i++){
		Local_u32Result*=Copy_u32Base;
	}
	return Local_u32Result;
}
