#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "WDT_interface.h"




void main(){
	PORT_voidInit();
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);
	_delay_ms(1000);
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW);

	WDT_voidEnable();
	WDT_voidSleep(SLEEP_1_s);
	WDT_voidDisable();
	while(1){
	}
}

