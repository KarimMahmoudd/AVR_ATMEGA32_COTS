#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "SW_interface.h"

#include "LED_interface.h"

#include <util/delay.h>

void main(){
	SW_t Button={DIO_u8PORTD,DIO_u8PIN0,BOUNCING,PULL_UP};
	SW_t Switch={DIO_u8PORTD,DIO_u8PIN1,LOCKING,PULL_UP};
	LED_t LED1={SOURCE,DIO_u8PORTD,DIO_u8PIN3};
	LED_t LED2={SOURCE,DIO_u8PORTD,DIO_u8PIN4};
	u8 ButtonState;
	u8 SwitchState;
	while(1){
		SW_u8GetState(&Button,&ButtonState);
		SW_u8GetState(&Switch,&SwitchState);
		if(ButtonState==PRESSED){
			LED_u8TurnOn(&LED1);
		}
		else if(ButtonState==NOT_PRESSED){
			LED_u8TurnOff(&LED1);
		}

		if(SwitchState==PRESSED){
			LED_u8TurnOn(&LED2);
		}
		else if(SwitchState==NOT_PRESSED){
			LED_u8TurnOff(&LED2);
		}
	}
}
