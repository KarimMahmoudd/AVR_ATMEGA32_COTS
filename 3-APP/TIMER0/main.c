#include "STD_TYPES.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"

#include "SSD_interface.h"

SSD_t SSD1 ={CATHODE,DIO_u8PORTA,DIO_u8PORTD,DIO_u8PIN0};
SSD_t SSD2 ={CATHODE,DIO_u8PORTA,DIO_u8PORTD,DIO_u8PIN1};
void SSDPOV(void);

void main(){
	PORT_voidInit();
	GIE_voidEnable();
	TIMER0_u8SetCallBack(&SSDPOV);
	TIMER0_voidInit();
	while(1){
	}
}

void SSDPOV(void){
	static u32 Local_u32Counter=0;
	static u8 num=0;
	static u8 state=0;
	Local_u32Counter++;
	if(state==0){
		SSD_u8Disable(&SSD1);
		SSD_u8SetNumber(num,&SSD2);
		SSD_u8Enable(&SSD2);
		state=1;
	}
	else if(state==1){
		SSD_u8Disable(&SSD2);
		SSD_u8SetNumber(9-num,&SSD1);
		SSD_u8Enable(&SSD1);
		state=0;
	}

	if(Local_u32Counter==4000){
		if(num==9){
			num=0;
		}
		else{
			num++;
		}
		Local_u32Counter=0;
	}
}
