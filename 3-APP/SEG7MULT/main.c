#include <avr/io.h>
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"

u8 SevenSegArr[10]={
			0b00111111,
			0b00000110,
			0b01011011,
			0b01001111,
			0b01100110,
			0b01101101,
			0b01111101,
			0b00000111,
			0b01111111,
			0b01101111
			};
void main(){
	DDRD=0xff;
	SET_BIT(DDRC,0);
	SET_BIT(DDRC,1);
	while(1){
		SET_BIT(PORTC,0);
		PORTD=SevenSegArr[8];
		_delay_ms(10);
		CLR_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		PORTD=SevenSegArr[9];
		_delay_ms(10);
		CLR_BIT(PORTC,1);
	}
}
