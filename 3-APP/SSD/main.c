#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "SSD_interface.h"

#include <util/delay.h>

void main(){
	SSD_t SSD1 = {CATHODE,DIO_u8PORTD,DIO_u8PORTC,DIO_u8PIN0};
//	SSD_t SSD2 = {CATHODE,DIO_u8PORTD,DIO_u8PORTC,DIO_u8PIN1};
	while(1){
		SSD_u8SetNumber(2,&SSD1);
		SSD_u8Enable(&SSD1);
		_delay_ms(500);
		SSD_u8Disable(&SSD1);
		_delay_ms(500);
		SSD_u8SetNumber(1,&SSD1);
		SSD_u8Enable(&SSD1);
		_delay_ms(500);
		SSD_u8Disable(&SSD1);
		_delay_ms(500);
	}
}
