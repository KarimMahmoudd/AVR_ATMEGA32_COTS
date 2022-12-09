#include <avr/io.h>
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
void flashing();
void shift_left();
void shift_right();
void LED_converge();
void LED_diverge();
void ping_pong_effect();
void snake_effect();
void converge_diverge();
void main(){
	DDRD=0xff;
	DDRC=0;
	PORTC=0xff;
	while(1){
		if(PINC==0b11111110){
			flashing();
		}
		else if(PINC==0b11111101){
			shift_left();
		}
		else if(PINC==0b11111011){
			shift_right();
		}
		else if(PINC==0b11110111){
			LED_converge();
		}
		else if(PINC==0b11101111){
			LED_diverge();
		}
		else if(PINC==0b11011111){
			ping_pong_effect();
		}
		else if(PINC==0b10111111){
			snake_effect();
		}
		else if(PINC==0b01111111){
			converge_diverge();
		}
	}
}
void flashing(){
	PORTD=0xff;
	_delay_ms(500);
	PORTD=0;
	_delay_ms(500);
}
void shift_left(){
	u8 initial_state=1;
	for(u8 i=0;i<8;i++){
		PORTD=initial_state;
		_delay_ms(250);
		initial_state=initial_state<<1;
	}
}
void shift_right(){
	u8 initial_state=0x80;
	for(u8 i=0;i<8;i++){
		PORTD=initial_state;
		_delay_ms(250);
		initial_state=initial_state>>1;
		}
}
void LED_converge(){
	u8 start=0,end=7;
	while(start<=end){
		SET_BIT(PORTD,end);
		SET_BIT(PORTD,start);
		_delay_ms(300);
		end--;
		start++;
	}
	PORTD=0;
	_delay_ms(300);

}
void LED_diverge(){
	s8 start=3,end=4;
	while(start>=0){
		SET_BIT(PORTD,end);
		SET_BIT(PORTD,start);
		_delay_ms(300);
		end++;
		start--;
	}
	PORTD=0;
	_delay_ms(300);
}
void ping_pong_effect(){
	shift_left();
	shift_right();
}
void snake_effect(){
	PORTD=0;
	for(u8 i=0;i<8;i++){
		SET_BIT(PORTD,i);
		_delay_ms(300);
	}
}
void converge_diverge(){
	s8 start=0,end=7;
		while(start<=end){
			SET_BIT(PORTD,end);
			SET_BIT(PORTD,start);
			_delay_ms(300);
			end--;
			start++;
		}
	start=3;end=4;
		while(start>=0){
			CLR_BIT(PORTD,end);
			CLR_BIT(PORTD,start);
			_delay_ms(300);
			end++;
			start--;
}
}
