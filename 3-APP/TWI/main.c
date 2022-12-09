#include "STD_TYPES.h"
#include <util/delay.h>

#include "PORT_interface.h"
#include "TWI_interface.h"
#include "DIO_interface.h"

#include "EEPROM_interface.h"

void main(){
	u8 Local_u8DataByte;
	PORT_voidInit();
	TWI_MasterInit(0);
	EEPROM_voidSendDataByte(1023,0b10111001);
	_delay_ms(10);
	EEPROM_voidReadDataByte(1023,&Local_u8DataByte);
	DIO_u8SetPortValue(DIO_u8PORTA,Local_u8DataByte);
	while(1){

	}
}
