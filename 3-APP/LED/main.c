#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "LED_interface.h"

#include <util/delay.h>

void main(){
	LED_t LED1 = {SINK,DIO_u8PORTD,DIO_u8PIN0};
	while(1){
		LED_u8TurnOn(&LED1);
		_delay_ms(1000);
		LED_u8TurnOff(&LED1);
		_delay_ms(1000);
	}
}
