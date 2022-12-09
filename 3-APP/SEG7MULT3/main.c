#include <avr/io.h>
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"

u8 inc_state();
u8 dec_state();
void increment(s8*,s8*);
void decrement(s8*,s8*);
void display(s8,s8);
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
	SET_BIT(PORTC,2);
	SET_BIT(PORTC,3);
	s8 units=0,tens=5;
	while(1){
		increment(&units,&tens);
		decrement(&units,&tens);
		display(units,tens);
	}
}
u8 inc_state(){
	if(GET_BIT(PINC,2)==0){
		_delay_ms(50);
		if(GET_BIT(PINC,2)==0){
			return 1;
		}
	}
	return 0;
}
u8 dec_state(){
	if(GET_BIT(PINC,3)==0){
		_delay_ms(50);
		if(GET_BIT(PINC,3)==0){
			return 1;
		}
	}
	return 0;
}
void increment(s8* units,s8* tens){
	if(inc_state()){
		(*units)++;
		if(*units>9){
			*units=0;
		}
		if(*units==0){
			(*tens)++;
			if(*tens>9){
				*tens=0;
			}
		}
	}
}
void decrement(s8* units,s8* tens){
	if(dec_state()){
		(*units)--;
		if(*units<0){
			*units=9;
		}
		if(*units==9){
			(*tens)--;
			if(*tens<0){
				*tens=9;
			}
		}
	}
}
void display(s8 units,s8 tens){
	SET_BIT(PORTC,0);
	PORTD=SevenSegArr[units];
	_delay_ms(10);
	CLR_BIT(PORTC,0);
	SET_BIT(PORTC,1);
	PORTD=SevenSegArr[tens];
	_delay_ms(10);
	CLR_BIT(PORTC,1);

}
