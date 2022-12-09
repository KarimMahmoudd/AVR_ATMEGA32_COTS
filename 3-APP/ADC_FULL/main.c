#include "STD_TYPES.h"
#include "MATH_HELPER.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"
#include "GIE_interface.h"

#include "SSD_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"

#include "APP_interface.h"
SSD_t SSD1 = {CATHODE,DIO_u8PORTB,DIO_u8PORTA,DIO_u8PIN4};
ADC_Chain_t ADCChain1 = {{THER_CHANNEL,LDR_CHANNEL},2,&ADCNotifFunc,{0}};
void main(void){
	u8 Local_u8ErrorState,Local_u8IDArr[4],Local_u8PassArr[4];
	PORT_voidInit();
	ADC_voidInit();
	CLCD_voidInit();
	GIE_voidEnable();
	APP_voidShowStartMenu();
	APP_voidGetID(Local_u8IDArr);
	APP_voidGetPassword(Local_u8PassArr);
	Local_u8ErrorState=APP_voidCheckPassword(&SSD1,Local_u8IDArr,Local_u8PassArr);
	while(1){
		if(Local_u8ErrorState==OK){
			ADC_u8StartChainConversion(&ADCChain1);
		}
	}
}






