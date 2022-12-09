#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"
#include "CLCD_interface.h"
#include "GIE_interface.h"
#include <util/delay.h>

void ADC_voidNotificationFunc(void);

u16 APP_u16ADCReading;

void main(void){
	PORT_voidInit();
	ADC_voidInit();
	GIE_voidEnable();
	while(1){
//		ADC_u8StartConversionAsynch(ADC_SINGLE_ENDED_ADC0,&APP_u16ADCReading,&ADC_voidNotificationFunc);
		ADC_u8StartConversionSynch(ADC_SINGLE_ENDED_ADC0,&APP_u16ADCReading);
		DIO_u8SetPortValue(DIO_u8PORTC,APP_u16ADCReading);
	}
}

void ADC_voidNotificationFunc(void){
	DIO_u8SetPortValue(DIO_u8PORTB,APP_u16ADCReading);
}
