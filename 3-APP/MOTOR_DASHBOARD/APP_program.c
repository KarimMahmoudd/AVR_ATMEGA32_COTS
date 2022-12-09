#include "STD_TYPES.h"
#include "MATH_HELPER.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"
#include "TIMER_interface.h"

#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "STPR_Interface.h"
#include "DCM_Interface.h"

#include "APP_interface.h"


void APP_voidShowStartMenu(){
	CLCD_voidCLR();
	CLCD_voidSendString("Welcome to Motor");
	CLCD_voidGoToXY(1,0);
	CLCD_voidSendString("Dashboard App");
	_delay_ms(3000);
}

void APP_voidGetID(u8 *Copy_pu8IDArr){
	if(Copy_pu8IDArr!=NULL){
		u8 Local_u8PressedKey;
		CLCD_voidCLR();
		CLCD_voidSendString("Enter ID:");
		for(u8 Local_u8Iterator=0;Local_u8Iterator<4;Local_u8Iterator++){
			APP_voidReadKey(&Local_u8PressedKey);
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
			APP_voidReadKey(&Local_u8PressedKey);
			CLCD_voidSendNumber(Local_u8PressedKey);
			Copy_pu8PassArr[Local_u8Iterator]=Local_u8PressedKey;
		}
	}
}
u8 APP_voidCheckPassword(const u8* Copy_pu8IDArr,u8* Copy_pu8PassArr){
	u8 Local_u8ErrorState=OK;
	if(Copy_pu8IDArr!=NULL && Copy_pu8PassArr!=NULL){
		for(u8 Local_u8Iterator=1;Local_u8Iterator<4;Local_u8Iterator++){
			if(Copy_pu8PassArr[3]!=Copy_pu8IDArr[0]||Copy_pu8PassArr[2]!=Copy_pu8IDArr[1]||Copy_pu8PassArr[1]!=Copy_pu8IDArr[2]||Copy_pu8PassArr[0]!=Copy_pu8IDArr[3]){
				if(Local_u8Iterator==3){
					CLCD_voidCLR();
					CLCD_voidSendString("BYE BYE");
					for(s8 Local_s8CountDown=3;Local_s8CountDown>=0;Local_s8CountDown--){
						CLCD_voidGoToXY(1,4);
						CLCD_voidSendNumber(Local_s8CountDown);
						_delay_ms(1000);
					}
					DIO_u8SetPortValue(DIO_u8PORTD,0);
					CLCD_voidCLR();
					Local_u8ErrorState = NOK;
					return Local_u8ErrorState;
				}
				else{
					CLCD_voidCLR();
					CLCD_voidSendString("TRY AGAIN!");
					CLCD_voidGoToXY(1,4);
					CLCD_voidSendNumber(3-Local_u8Iterator);
					_delay_ms(1000);
					APP_voidGetPassword(Copy_pu8PassArr);
				}
			}
		}
		CLCD_voidCLR();
		CLCD_voidSendString("Welcome ");
		for(u8 Local_u8Iterator=0;Local_u8Iterator<4;Local_u8Iterator++){
			CLCD_voidSendNumber(Copy_pu8IDArr[Local_u8Iterator]);
		}
		_delay_ms(3000);
	}
	return Local_u8ErrorState;
}

void APP_voidShowMainMenu(){
	CLCD_voidCLR();
	CLCD_voidSendString("for DC>1 STPR>2");
	CLCD_voidGoToXY(1,0);
	CLCD_voidSendString("Servo>3 Exit>4");
}

void APP_voidShowRotateMenu(){
	CLCD_voidCLR();
	CLCD_voidSendString("Rotation Dir.");
	CLCD_voidGoToXY(1,0);
	CLCD_voidSendString("CW->1 CCW->2");
}

void APP_voidShowDCSpeedMenu(){
	CLCD_voidCLR();
	CLCD_voidSendString("Speed Control");
	_delay_ms(2000);
	CLCD_voidCLR();
	CLCD_voidSendString("Full->1 Poten->2");
	CLCD_voidGoToXY(1,0);
	CLCD_voidSendString("LM35->3");
}

void APP_voidReadKey(u8* Copy_pu8Key){
	do{
		*Copy_pu8Key=KPD_u8GetPressedKey();
	}while(*Copy_pu8Key==0xff);
}

void APP_voidChooseMotor(){
	u8 Local_u8PressedKey,Local_u8ServoAngle;u16 Local_u16Reading,Local_u16StepperAngle;
	APP_voidReadKey(&Local_u8PressedKey);
	if(Local_u8PressedKey==DC){
		APP_voidShowRotateMenu();
		APP_voidReadKey(&Local_u8PressedKey);
		if(Local_u8PressedKey==CW){
			APP_voidShowDCSpeedMenu();
			APP_voidReadKey(&Local_u8PressedKey);
			if(Local_u8PressedKey==FULL){
				DIO_u8SetPinValue(DCM_PORT,DCM_PIN,DIO_u8PIN_HIGH);
				DCM_voidRotateClockwise();
			}
			else if(Local_u8PressedKey==POTENTIO){
				DCM_voidRotateClockwise();
				TIMER1_voidSetTopValue(20000);
				while(1){
					ADC_u8StartConversionSynch(POTENTIO_CHANNEL,&Local_u16Reading);
					Local_u16Reading=MATH_s32Map(0,255,0,20000,Local_u16Reading);
					TIMER1B_voidSetCompMatchValue(Local_u16Reading);
				}
			}
			else if(Local_u8PressedKey==LM35){
				DCM_voidRotateClockwise();
				TIMER1_voidSetTopValue(20000);
				while(1){
					ADC_u8StartConversionSynch(THER_CHANNEL,&Local_u16Reading);
					Local_u16Reading=MATH_s32Map(0,255,0,500,Local_u16Reading);
					if(Local_u16Reading>=20&&Local_u16Reading<=40){
						Local_u16Reading=MATH_s32Map(20,40,0,20000,Local_u16Reading);
						TIMER1B_voidSetCompMatchValue(Local_u16Reading);
					}

				}

			}
		}
		else if(Local_u8PressedKey==CCW){
			APP_voidShowDCSpeedMenu();
			APP_voidReadKey(&Local_u8PressedKey);
			if(Local_u8PressedKey==FULL){
				DIO_u8SetPinValue(DCM_PORT,DCM_PIN,DIO_u8PIN_HIGH);
				DCM_voidRotateCounterClockwise();
			}
			else if(Local_u8PressedKey==POTENTIO){
				DCM_voidRotateCounterClockwise();
				TIMER1_voidSetTopValue(20000);
				while(1){
					ADC_u8StartConversionSynch(POTENTIO_CHANNEL,&Local_u16Reading);
					Local_u16Reading=MATH_s32Map(0,255,0,20000,Local_u16Reading);
					TIMER1B_voidSetCompMatchValue(Local_u16Reading);
				}
			}
			else if(Local_u8PressedKey==LM35){
				DCM_voidRotateCounterClockwise();
				TIMER1_voidSetTopValue(20000);
				while(1){
					ADC_u8StartConversionSynch(THER_CHANNEL,&Local_u16Reading);
					Local_u16Reading=MATH_s32Map(0,255,0,500,Local_u16Reading);
					if(Local_u16Reading>=20&&Local_u16Reading<=40){
						Local_u16Reading=MATH_s32Map(20,40,0,20000,Local_u16Reading);
						TIMER1B_voidSetCompMatchValue(Local_u16Reading);
					}

				}

			}
		}
	}
	else if(Local_u8PressedKey==STPR){
		APP_voidShowRotateMenu();
		APP_voidReadKey(&Local_u8PressedKey);
		if(Local_u8PressedKey==CW){
			CLCD_voidCLR();
			CLCD_voidSendString("Angle:");
			Local_u16StepperAngle=APP_u16GetAngle();
			STPR_voidRotateAngle(STPR_CLOCKWISE,Local_u16StepperAngle);
		}
		else if(Local_u8PressedKey==CCW){
			CLCD_voidCLR();
			CLCD_voidSendString("Angle:");
			Local_u16StepperAngle=APP_u16GetAngle();
			STPR_voidRotateAngle(STPR_COUNTER_CLOCKWISE,Local_u16StepperAngle);
		}
	}
	else if(Local_u8PressedKey==SERVO){
		CLCD_voidCLR();
		CLCD_voidSendString("Angle:");
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("(0->180)");
		CLCD_voidGoToXY(0,6);
		Local_u8ServoAngle=APP_u16GetAngle();
		TIMER1_voidSetTopValue(20000);
		Local_u16Reading=MATH_s32Map(0,180,400,2500,Local_u8ServoAngle);
		TIMER1A_voidSetCompMatchValue(Local_u16Reading);
	}
	else if(Local_u8PressedKey==EXIT){
		CLCD_voidCLR();
		CLCD_voidSendString("Thank You!");
		_delay_ms(1000);
		CLCD_voidCLR();
		while(1);
	}
}
u16 APP_u16GetAngle(){
	u8 Local_u8AngleArr[20],Local_u8Iterator,Local_u8DigitNum=0,Local_u8PressedKey;
	u16 Local_u16Angle=0;
	while(1){
		APP_voidReadKey(&Local_u8PressedKey);
		if(Local_u8PressedKey=='x'){
			Local_u8AngleArr[Local_u8DigitNum]=Local_u8PressedKey;
			break;
		}
		CLCD_voidSendNumber(Local_u8PressedKey);
		Local_u8AngleArr[Local_u8DigitNum++]=Local_u8PressedKey;
	}

	for(Local_u8Iterator=0;Local_u8Iterator<Local_u8DigitNum;Local_u8Iterator++){
		Local_u16Angle+=Local_u8AngleArr[Local_u8Iterator]*(MATH_u32Power(10,Local_u8DigitNum-Local_u8Iterator-1));
	}
	return Local_u16Angle;
}
