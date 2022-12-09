#include "STD_TYPES.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"

#include "SERVO_interface.h"

void LedBlink();

void main(){
	Timer1_t Timer1={TIMER1_FAST_PWM_CUSTOM_TOP,PRSCLR_DIV_BY_8,OCM_FAST_PWM_NON_INVERTED,OCM_DISCONNECT,INT_DISABLE,INT_DISABLE};
	Timer_t Timer0={TIMER_CTC,PRSCLR_DIV_BY_8,OCM_DISCONNECT,INT_DISABLE,INT_DISABLE};
	PORT_voidInit();
	TIMER1_u8Init(&Timer1);
	TIMER2_u8Schedule(1000,&LedBlink,REPEAT_PERIODIC);
	GIE_voidEnable();
	while(1){
		for(u8 i=0;i<=180;i++){
			SERVO_u8Rotate(i,&Timer1);
			TIMER0_delay_ms(&Timer0,15);
		}
		for(u8 i=0;i<=180;i++){
			SERVO_u8Rotate(180-i,&Timer1);
			TIMER0_delay_ms(&Timer0,15);
		}

	}
}

void LedBlink(){
	static u8 Local_u8State=0;
	if(Local_u8State==0){
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);
		Local_u8State=1;
	}
	else if(Local_u8State==1){
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW);
		Local_u8State=0;
	}
}
