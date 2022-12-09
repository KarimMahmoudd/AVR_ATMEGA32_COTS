#include "STD_TYPES.h"
#include <util/delay.h>

#include "PORT_interface.h"

#include "DCM_Interface.h"

void main(){
	PORT_voidInit();
	while(1){
		DCM_voidRotateClockwise();
		_delay_ms(5000);
		DCM_voidStop();
		_delay_ms(5000);
		DCM_voidRotateCounterClockwise();
		_delay_ms(5000);
		DCM_voidStop();
		_delay_ms(5000);
	}
}
