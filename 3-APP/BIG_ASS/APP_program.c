#include "STD_TYPES.h"
#include "MATH_HELPER.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"
#include "GIE_interface.h"
#include "TIMER_interface.h"

#include "SSD_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"

#include "APP_interface.h"

extern Chain_t ADCChain1;

void APP_voidShowStartMenu(){
	CLCD_voidCLR();
	CLCD_voidGoToXY(0,4);
	CLCD_voidSendString("WELCOME");
	_delay_ms(3000);
}

void APP_voidGetID(u8 *Copy_pu8IDArr){
	if(Copy_pu8IDArr!=NULL){
		u8 Local_u8PressedKey;
		CLCD_voidCLR();
		CLCD_voidSendString("Enter ID:");
		for(u8 Local_u8Iterator=0;Local_u8Iterator<4;Local_u8Iterator++){
			do{
				Local_u8PressedKey=KPD_u8GetPressedKey();
			}while(Local_u8PressedKey==0xff);
			CLCD_voidSendNumber(Local_u8PressedKey);
			Copy_pu8IDArr[Local_u8Iterator]=Local_u8PressedKey;
		}
	}
}
void APP_voidGetPassword(u8* Copy_pu8PassArr){
	if(Copy_pu8PassArr!=NULL){
		u8 Local_u8PressedKey;
		CLCD_voidCLR();
		CLCD_voidSendString("Enter Password:");
		CLCD_voidGoToXY(1,0);
		for(u8 Local_u8Iterator=0;Local_u8Iterator<4;Local_u8Iterator++){
			do{
				Local_u8PressedKey=KPD_u8GetPressedKey();
			}while(Local_u8PressedKey==0xff);
			CLCD_voidSendNumber(Local_u8PressedKey);
			Copy_pu8PassArr[Local_u8Iterator]=Local_u8PressedKey;
		}
	}
}
u8 APP_voidCheckPassword(const SSD_t* Copy_psSSD,const u8* Copy_pu8IDArr,u8* Copy_pu8PassArr){
	u8 Local_u8ErrorState=OK;
	if(Copy_pu8IDArr!=NULL && Copy_psSSD!=NULL && Copy_pu8PassArr!=NULL){
		SSD_u8Enable(Copy_psSSD);
		SSD_u8SetNumber(3,Copy_psSSD);
		for(u8 Local_u8Iterator=1;Local_u8Iterator<4;Local_u8Iterator++){
			if(Copy_pu8PassArr[3]!=Copy_pu8IDArr[0]||Copy_pu8PassArr[2]!=Copy_pu8IDArr[1]||Copy_pu8PassArr[1]!=Copy_pu8IDArr[2]||Copy_pu8PassArr[0]!=Copy_pu8IDArr[3]){
				if(Local_u8Iterator==3){
					CLCD_voidCLR();
					CLCD_voidSendString("BYE BYE");
					for(s8 Local_s8CountDown=3;Local_s8CountDown>=0;Local_s8CountDown--){
						SSD_u8SetNumber(Local_s8CountDown,Copy_psSSD);
						_delay_ms(1000);
					}
					SSD_u8Disable(Copy_psSSD);
					DIO_u8SetPortValue(DIO_u8PORTD,0);
					CLCD_voidCLR();
					Local_u8ErrorState = NOK;
					return Local_u8ErrorState;
				}
				else{
					SSD_u8SetNumber(3-Local_u8Iterator,Copy_psSSD);
					CLCD_voidCLR();
					CLCD_voidSendString("TRY AGAIN!");
					_delay_ms(1000);
					APP_voidGetPassword(Copy_pu8PassArr);
				}
			}
		}
		SSD_u8Disable(Copy_psSSD);
		CLCD_voidCLR();
		CLCD_voidSendString("Welcome ");
		for(u8 Local_u8Iterator=0;Local_u8Iterator<4;Local_u8Iterator++){
			CLCD_voidSendNumber(Copy_pu8IDArr[Local_u8Iterator]);
		}
		_delay_ms(3000);
	}
	return Local_u8ErrorState;
}

void ADCNotifFunc(void){
	TIMER1_voidSetTopValue(20000);
	u16 Local_u16Temp=MATH_s32Map(0,255,0,5000,ADCChain1.ResultArr[0]),Local_u16OnTime;
	Local_u16Temp/=10;
	u16 Local_u16Leds=MATH_s32Map(0,255,0,100,ADCChain1.ResultArr[1]);
	CLCD_voidCLR();
	CLCD_voidSendString("Temp: ");
	CLCD_voidSendNumber(Local_u16Temp);
	CLCD_voidSendString(" 'c");
	CLCD_voidGoToXY(1,0);
	CLCD_voidSendString("LEVEL: ");
	CLCD_voidSendNumber(100-Local_u16Leds);
	if(Local_u16Temp>25){
		DIO_u8SetPinValue(DCM_PORT,DCM_PIN,DIO_u8PIN_HIGH);
		CLCD_voidGoToXY(0,15);
		CLCD_voidSendData('M');
		Local_u16OnTime=MATH_s32Map(25,40,0,20000,Local_u16Temp);
		TIMER1B_voidSetCompMatchValue(Local_u16OnTime);
	}
	else{
		CLCD_voidGoToXY(0,15);
		CLCD_voidSendData(' ');
		DIO_u8SetPinValue(DCM_PORT,DCM_PIN,DIO_u8PIN_LOW);
	}
	Local_u16Leds=MATH_s32Map(10,100,0,20000,Local_u16Leds);
	TIMER1A_voidSetCompMatchValue(Local_u16Leds);
	_delay_ms(1000);
}
