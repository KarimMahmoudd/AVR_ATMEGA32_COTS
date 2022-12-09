#include "STD_TYPES.h"
#include "MATH_HELPER.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"
#include "TIMER_interface.h"

#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "DCM_Interface.h"
#include "STPR_Interface.h"

#include "APP_interface.h"

void main(void){
	u8 Local_u8ErrorState,Local_u8IDArr[4],Local_u8PassArr[4];
	PORT_voidInit();
	ADC_voidInit();
	CLCD_voidInit();
	TIMER1_voidInit();
	APP_voidShowStartMenu();
	APP_voidGetID(Local_u8IDArr);
	APP_voidGetPassword(Local_u8PassArr);
	Local_u8ErrorState=APP_voidCheckPassword(Local_u8IDArr,Local_u8PassArr);
	while(1){
		if(Local_u8ErrorState==OK){
			APP_voidShowMainMenu();
			APP_voidChooseMotor();
		}
	}
}






