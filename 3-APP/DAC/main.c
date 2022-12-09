#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"
#include "CLCD_interface.h"
#include "GIE_interface.h"

#include "DAC_interface.h"

#include <util/delay.h>

void ADC_voidNotificationFunc(void);

u16 APP_u16ADCReading;

void main(void){
	PORT_voidInit();
	ADC_voidInit();
	GIE_voidEnable();
	int temp;
	while(1){

		ADC_u8StartConversionSynch(0,&temp);
//		DIO_u8SetPortValue(DIO_u8PORTD,temp);
				for(int i=0;i<5000;i++){
					DAC_voidSetAnalogVolt(i);
//					DIO_u8SetPortValue(DIO_u8PORTC,i);
					ADC_u8StartConversionSynch(0,&temp);
					DIO_u8SetPortValue(DIO_u8PORTD,temp);
					_delay_ms(15);

				}

	}
}

void ADC_voidNotificationFunc(void){
	DIO_u8SetPortValue(DIO_u8PORTB,APP_u16ADCReading);
}
