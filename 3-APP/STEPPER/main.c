#include "STD_TYPES.h"
#include <util/delay.h>

#include "PORT_interface.h"
#include "DIO_interface.h"

#include "STPR_Interface.h"

void main(){
	PORT_voidInit();
	STPR_voidRotateAngle(STPR_COUNTER_CLOCKWISE,360);
	while(1){
		STPR_voidRotateClockwise();
	}
}
