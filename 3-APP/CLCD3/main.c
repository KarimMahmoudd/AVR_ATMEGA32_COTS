#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"

#include "CLCD_interface.h"



void main(void){
	u8 name[3][8] ={
			{
					0b00000001,
					0b00000000,
					0b00000001,
					0b00000001,
					0b00000010,
					0b00000100,
					0b00011000,
					0b00000000},
					{
							0b00000001,
							0b00000001,
							0b00011111,
							0b00000000,
							0b00000100,
							0b00000000,
							0b00000000,
							0b00000000},
							{
									0b00000000,
									0b00000000,
									0b00000111,
									0b00000100,
									0b00000111,
									0b00010001,
									0b00011111,
									0b00000000},


	};
	s8 xpos=0;
	/*Initialize pins directions*/
	PORT_voidInit();
	/*Initialize LCD 8 BIT MODE*/
	CLCD_voidInit();

	while(1){
		s8 ypos=15;
		while(ypos>0){
			for(u8 i=0;i<3;i++){
				CLCD_voidWriteSpecialCharacter(name[i],i);
				CLCD_voidSendSpecialCharacter(i,xpos,ypos);
				ypos--;
			}
			_delay_ms(1000);
			xpos= (xpos==0)?1:0;
			CLCD_voidSendCommand(1);
		}
	}
}




