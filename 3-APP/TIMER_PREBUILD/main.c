#include "STD_TYPES.h"
#include "MATH_HELPER.h"
#include <util/delay.h>

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"
#include "PWM_interface.h"
#include "ADC_interface.h"

#include "SSD_interface.h"

void PWM(void);

void main(){
	u16 Local_u16Angle, Local_u16Reading,Local_u16Counter;
	PORT_voidInit();
	TIMER1_voidInit();
	ADC_voidInit();
	TIMER1_voidSetTopValue(20000);
	while(1){
		ADC_u8StartConversionSynch(ADC_SINGLE_ENDED_ADC0,&Local_u16Reading);
		DIO_u8SetPortValue(DIO_u8PORTC,Local_u16Reading);
		Local_u16Angle=MATH_s32Map(0,255,400,2500,Local_u16Reading);
		TIMER1A_voidSetCompMatchValue(Local_u16Angle);
//		for(Local_u16Counter=750;Local_u16Counter<2500;Local_u16Counter++){
//			TIMER1A_voidSetCompMatchValue(Local_u16Counter);
//			_delay_ms(10);
//		}

	}
}

void PWM(void){
	static u8 Local_u8Counter=0;
	Local_u8Counter++;
	if(Local_u8Counter==1){
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW);
	}
	else if(Local_u8Counter==5){
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8PIN_LOW);
	}
	else if(Local_u8Counter==15){
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
	}
	else if(Local_u8Counter==20){
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
		Local_u8Counter=0;
	}

}
