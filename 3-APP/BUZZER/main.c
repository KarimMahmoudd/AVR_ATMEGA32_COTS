#include "STD_TYPES.h"
#include <util/delay.h>
#include "MATH_HELPER.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"
#include "TIMER_interface.h"

#include "KPD_interface.h"

void main(){
	u16 Local_u8Reading,Local_u16SoundLevel,Local_u16Reading,Local_u16Motor,temp;
	PORT_voidInit();
	TIMER1_voidInit();
	TIMER1_voidSetTopValue(20000);
	//	TIMER1A_voidSetCompMatchValue(20000);
	//	TIMER1B_voidSetCompMatchValue(20000);
	ADC_voidInit();
	while(1){
		Local_u16Motor=0;
		ADC_u8StartConversionSynch(ADC_SINGLE_ENDED_ADC1,&Local_u8Reading);
		ADC_u8StartConversionSynch(ADC_SINGLE_ENDED_ADC0,&Local_u16Reading);
		Local_u16SoundLevel=MATH_s32Map(0,700,5000,0,Local_u8Reading);
		temp=MATH_s32Map(0,1023,0,500,Local_u16Reading);
		if(temp>=23&&temp<40){
			Local_u16Motor=MATH_s32Map(23,40,0,20000,temp);
			TIMER1A_voidSetCompMatchValue(Local_u16Motor);
		}
		TIMER1B_voidSetCompMatchValue(Local_u16SoundLevel);
		//		ADC_u8StartConversionSynch(ADC_SINGLE_ENDED_ADC0,&Local_u8Reading);
		//		DIO_u8SetPortValue(DIO_u8PORTC,Local_u8Reading);
		//		Local_u16SoundLevel=MATH_s32Map(0,255,10000,20000,Local_u8Reading);
		//		TIMER1A_voidSetCompMatchValue(Local_u16SoundLevel);

		//		do{
		//			Local_u8PressedKey=KPD_u8GetPressedKey();
		//		}while(Local_u8PressedKey==0xff);
		//		for(u16 i=0;i<300;i++){
		//			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH);
		//			_delay_us(10*Local_u8PressedKey);
		//			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);
		//			_delay_us(10*Local_u8PressedKey);
		//		}
	}
}
