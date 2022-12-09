#include "STD_TYPES.h"
#include <util/delay.h>

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"
#include "PWM_interface.h"
#include "ADC_interface.h"

#include "SSD_interface.h"

void PWM(void);

void main(){
	Timer_t Timer0 = {TIMER_CTC,TIMER_DIV_BY_64,TIMER_DISCONNECT,INT_ENABLE,INT_DISABLE};
	PORT_voidInit();
	GIE_voidEnable();
	TIMER0_u8Init(&Timer0);
	TIMER_u8SetCompMatch(TIMER0,125);
	TIMER_u8SetCallBack(TIMER0_COMP,&PWM);
	while(1){

	}
}

void PWM(void){
	static u8 Local_u8Counter=0;
	Local_u8Counter++;
	if(Local_u8Counter==1){
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_HIGH);
	}
	else if(Local_u8Counter==5){
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8PIN_LOW);
	}
	else if(Local_u8Counter==15){
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
	}
	else if(Local_u8Counter==20){
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
		Local_u8Counter=0;
	}

}
