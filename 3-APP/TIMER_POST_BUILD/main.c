#include "STD_TYPES.h"
#include "MATH_HELPER.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "TIMER_interface.h"

#include "SERVO_interface.h"

void main(void){
	Timer1_t Local_Timer1={TIMER1_FAST_PWM_CUSTOM_TOP,TIMER_DIV_BY_8,TIMER_FAST_PWM_NON_INVERTED,TIMER_DISCONNECT,INT_DISABLE,INT_DISABLE,INT_DISABLE,INT_DISABLE};
	Timer_t Local_Timer2={TIMER_CTC,TIMER_DIV_BY_8,TIMER_DISCONNECT,INT_DISABLE,INT_DISABLE};
	PORT_voidInit();
	TIMER1_u8Init(&Local_Timer1);
	TIMER2_u8Init(&Local_Timer2);
//	SERVO_u8Rotate(CHANNEL_A,0,&Local_Timer1);
	while(1){
//		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);
//		TIMER2_delay_ms(&Local_Timer2,1000);
//		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW);
//		TIMER2_delay_ms(&Local_Timer2,1000);
		for(u8 i=0;i<=180;i++){
			SERVO_u8Rotate(CHANNEL_A,i,&Local_Timer1);
			TIMER2_delay_ms(&Local_Timer2,15);
		}
		for(u8 i=0;i<=180;i++){
			SERVO_u8Rotate(CHANNEL_A,180-i,&Local_Timer1);
			TIMER2_delay_ms(&Local_Timer2,15);
		}
	}
}






