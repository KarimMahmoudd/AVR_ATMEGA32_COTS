#include "STD_TYPES.h"
#include <util/delay.h>

#include "CLCD_interface.h"

#include "DIO_interface.h"

void main(void){
	/*Initialize LCD pins direction*/
	DIO_u8SetPortDirection(DIO_u8PORTD,DIO_u8PORT_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_OUTPUT);

	CLCD_voidInit();

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




