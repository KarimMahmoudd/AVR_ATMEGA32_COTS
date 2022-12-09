#include "STD_TYPES.h"
#include <util/delay.h>

#include "PORT_interface.h"
#include "DIO_interface.h"

#include "KPD_interface.h"
#include "CLCD_interface.h"
#include "LED_interface.h"
void PrintInPosition(u8 Copy_u8Key,u8 Copy_u8Pos,u8* Copy_pu8Arr);

void main(void)
{
	LED_t LED1={SOURCE,DIO_u8PORTC,DIO_u8PIN3};
	u8 Local_u8Key, Local_u8PosCounter=0;s8 Local_u8Seconds,Local_u8Minutes,Local_u8Hours;
	u8 Local_u8StopWatchArr[8] ={0,0,':',0,0,':',0,0};
	PORT_voidInit();
	CLCD_voidInit();
	CLCD_voidGoToXY(0,Local_u8PosCounter+4);
	CLCD_voidSendString("00:00:00");
	CLCD_voidGoToXY(0,Local_u8PosCounter+4);

	while(1)
	{
		do
		{
			Local_u8Key=KPD_u8GetPressedKey();
		}while(Local_u8Key == 0xff);

		if(Local_u8Key=='r')
		{
			if(Local_u8PosCounter==7)
			{
				Local_u8PosCounter=0;
			}
			else
			{
				Local_u8PosCounter++;
			}
			CLCD_voidGoToXY(0,Local_u8PosCounter+4);
		}
		else if(Local_u8Key=='l')
		{
			if(Local_u8PosCounter==0)
			{
				Local_u8PosCounter=7;
			}
			else
			{
				Local_u8PosCounter--;
			}
			CLCD_voidGoToXY(0,Local_u8PosCounter+4);
		}
		else if(Local_u8Key=='e'){
			if(Local_u8PosCounter<7)
			{
				Local_u8PosCounter++;
				CLCD_voidGoToXY(0,Local_u8PosCounter+4);
			}
		}
		else if(Local_u8Key=='s'){
			Local_u8Hours=Local_u8StopWatchArr[0]*10+Local_u8StopWatchArr[1];
			Local_u8Minutes=Local_u8StopWatchArr[3]*10+Local_u8StopWatchArr[4];
			Local_u8Seconds=Local_u8StopWatchArr[6]*10+Local_u8StopWatchArr[7];
			for(Local_u8Hours;Local_u8Hours>=0;Local_u8Hours--){
				for(Local_u8Minutes;Local_u8Minutes>=0;Local_u8Minutes--){
					for(Local_u8Seconds;Local_u8Seconds>=0;Local_u8Seconds--){
						CLCD_voidGoToXY(0,10);
						if(Local_u8Seconds<10){
							CLCD_voidSendData('0');
							CLCD_voidSendNumber(Local_u8Seconds);
						}
						else{
							CLCD_voidSendNumber(Local_u8Seconds);
						}
						CLCD_voidGoToXY(0,10);
						_delay_ms(1000);
					}
					CLCD_voidGoToXY(0,7);
					if(Local_u8Minutes<=10&&Local_u8Minutes>0){
						CLCD_voidSendData('0');
						CLCD_voidSendNumber(Local_u8Minutes-1);
					}
					else if(Local_u8Minutes>10){
						CLCD_voidSendNumber(Local_u8Minutes-1);
					}
					if(Local_u8Minutes!=0){
						Local_u8Seconds=59;
					}
				}
				CLCD_voidGoToXY(0,4);
				if(Local_u8Hours<=10&&Local_u8Hours>0){
					CLCD_voidSendData('0');
					CLCD_voidSendNumber(Local_u8Hours-1);
				}
				else if(Local_u8Hours>10){
					CLCD_voidSendNumber(Local_u8Hours-1);
				}
				if(Local_u8Hours!=0){
					Local_u8Minutes=59;
				}
			}
			LED_u8TurnOn(&LED1);
			CLCD_voidGoToXY(1,4);
			CLCD_voidSendString("It's Time");
			CLCD_voidGoToXY(0,4);

		}
		else if(Local_u8Key==0||Local_u8Key==1||Local_u8Key==2||Local_u8Key==3||Local_u8Key==4||Local_u8Key==5||Local_u8Key==6||Local_u8Key==7||Local_u8Key==8||Local_u8Key==9){

			if(Local_u8StopWatchArr[Local_u8PosCounter]!=':'){
				if(Local_u8PosCounter==3||Local_u8PosCounter==6){
					if(Local_u8Key<6){
						PrintInPosition(Local_u8Key,Local_u8PosCounter,Local_u8StopWatchArr);
					}
				}
				else{
					PrintInPosition(Local_u8Key,Local_u8PosCounter,Local_u8StopWatchArr);
				}
			}

		}

	}
}
void PrintInPosition(u8 Copy_u8Key,u8 Copy_u8Pos,u8* Copy_pu8Arr){
	CLCD_voidSendNumber(Copy_u8Key);
	CLCD_voidGoToXY(0,Copy_u8Pos+4);
	Copy_pu8Arr[Copy_u8Pos]=Copy_u8Key;
}
