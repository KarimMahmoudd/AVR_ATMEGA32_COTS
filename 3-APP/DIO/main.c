#include "STD_TYPES.h"
#include "DIO_interface.h"
#include <util\delay.h>
void main (){
	DIO_u8SetPortDirection(DIO_u8PORTD,DIO_u8PORT_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_INPUT);
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH);
	u8 volatile Local_u8ButtonState;
	u8 *Local_pu8ButtonState = &Local_u8ButtonState;
	while(1){
		DIO_u8SetPortValue(DIO_u8PORTD,DIO_u8PORT_LOW);
		DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN0,DIO_u8PIN_HIGH);
		DIO_u8GetPinValue(DIO_u8PORTC,DIO_u8PIN0,Local_pu8ButtonState);
		if(Local_u8ButtonState==DIO_u8PIN_LOW){
			DIO_u8SetPortValue(DIO_u8PORTD,DIO_u8PORT_HIGH);
			DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN0,DIO_u8PIN_LOW);
			_delay_ms(1000);
		}

	}
}

