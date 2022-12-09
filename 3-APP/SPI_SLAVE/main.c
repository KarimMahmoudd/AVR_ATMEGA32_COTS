#include "STD_TYPES.h"

#include <util/delay.h>

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "SPI_interface.h"
#include "GIE_interface.h"
void LOL ();
u8 Data,state=0;
void main(){
	PORT_voidInit();
	SPI_voidSlaveInit();
	GIE_voidEnable();
	while(1){
		SPI_u8AsynchTranscieve(10,&Data,&LOL);
		_delay_ms(1000);
	}
}

void LOL(){
//	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);
	if(Data==1){
		if(state==0){
			DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);
			state=1;
		}
		else if(state==1){
			DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW);
			state=0;
		}

	}
}
