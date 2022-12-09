#include <avr/io.h>
#include <util/delay.h>
#include "STD_TYPES.h"
void main(){
	u8 SevenSegArray[10]={
			0b00111111,
			0b00000110,
			0b01011011,
			0b01001111,
			0b01100110,
			0b01101101,
			0b01111101,
			0b00000111,
			0b01111111,
			0b01101111};
	DDRD=0xff;
	while(1){
		for(u8 i=0;i<10;i++){
			PORTD=SevenSegArray[i];
			_delay_ms(1000);
		}
	}
}
