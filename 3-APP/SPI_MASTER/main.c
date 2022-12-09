#include "STD_TYPES.h"

#include <util/delay.h>

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "SPI_interface.h"
#include "GIE_interface.h"

void LOL ();
void main(){
	u8 Data;
	PORT_voidInit();
	SPI_voidMasterInit();
	GIE_voidEnable();
	while(1){
		SPI_u8AsynchTranscieve(1,&Data,&LOL);
		_delay_ms(1000);
	}
}

void LOL(){

}
