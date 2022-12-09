#include "STD_TYPES.h"

#include "PORT_interface.h"

#include "KPD_interface.h"
#include "CLCD_interface.h"

void main(void)
{
	char Local_u8Key;
	PORT_voidInit();
	CLCD_voidInit();
	while(1)
	{
		do
		{
			Local_u8Key=KPD_u8GetPressedKey();
		}while(Local_u8Key == 0xff);

		if(Local_u8Key=='\n')
		{
			CLCD_voidGoToXY(1,0);
		}
		else
		{
			CLCD_voidSendData(Local_u8Key);
		}

	}
}
