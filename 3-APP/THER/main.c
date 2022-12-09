#include "STD_TYPES.h"
#include "MATH_HELPER.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"

#include "CLCD_interface.h"
#include <util/delay.h>

void main(void){
	u8 temp,Leds;
	PORT_voidInit();
	ADC_voidInit();
	CLCD_voidInit();
	CLCD_voidSendString("LDR Val is: ");
	while(1){
		temp= ADC_u8GetChannelReading(ADC_SINGLE_ENDED_ADC1);
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("       ");
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendNumber(temp);
		Leds=MATH_s32Map(0,240,0,7,temp);
		if(Leds==0){
			DIO_u8SetPortValue(DIO_u8PORTB,0xff);
		}
		else if(Leds==1){
			DIO_u8SetPortValue(DIO_u8PORTB,0b11111110);
		}
		else if(Leds==2){
			DIO_u8SetPortValue(DIO_u8PORTB,0b11111100);
		}
		else if(Leds==3){
			DIO_u8SetPortValue(DIO_u8PORTB,0b11111000);
		}
		else if(Leds==4){
			DIO_u8SetPortValue(DIO_u8PORTB,0b11110000);
		}
		else if(Leds==5){
			DIO_u8SetPortValue(DIO_u8PORTB,0b11100000);
		}
		else if(Leds==6){
			DIO_u8SetPortValue(DIO_u8PORTB,0b11000000);
		}
		else if(Leds==7){
			DIO_u8SetPortValue(DIO_u8PORTB,0b10000000);
		}
		_delay_ms(1000);


	}
}
