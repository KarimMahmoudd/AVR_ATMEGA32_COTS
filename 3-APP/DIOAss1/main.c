#include <avr/io.h>
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
void counter(s8);
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
	DDRC=0xff;
	DDRA=0b00000111;
	while(1){
		SET_BIT(PORTA,0);
		counter(15);
		CLR_BIT(PORTA,0);
		SET_BIT(PORTA,1);
		counter(3);
		CLR_BIT(PORTA,1);
		SET_BIT(PORTA,2);
		counter(15);
		CLR_BIT(PORTA,2);
	}
}
void counter(s8 period){
	for(s8 i=period;i>=0;i--){
				PORTD=SevenSegArr[i/10];
				PORTC=SevenSegArr[i%10];
				_delay_ms(1000);
			}
}
