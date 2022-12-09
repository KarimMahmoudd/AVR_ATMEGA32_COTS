#include "STD_TYPES.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "USART_interface.h"
#include "GIE_interface.h"
#include <string.h>

void LOL(void);
void LMAO();
void LMFAO();
u16 Local_u8Data;
u16 Local_u8Status=0;
u8 Local_u8Buffer[4];
char Local_u8String[5];
char Comp1[]="open";
char Comp2[]="shut";
void main(){
	u8 Local_u8ErrorState;
	PORT_voidInit();
	USART_voidInit();
	GIE_voidEnable();
	while(1){
		USART_u8ReceiveBufferAsynch(Local_u8Buffer,4,&LOL);
	}
}

void LOL(void){
	for(int i=0;i<5;i++){
		if(i==4){
			Local_u8String[i]='\0';
		}
		else{
			Local_u8String[i]=Local_u8Buffer[i];
		}
	}
	if(strcmp(Local_u8String,Comp1)==0){
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);
	}
	else if(strcmp(Local_u8String,Comp2)==0){
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW);
	}
	USART_u8SendStringAsynch(Local_u8String,&LMAO);
}
void LMAO (){
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8PIN_HIGH);
}
void LMFAO(){
	if(Local_u8Data=='1'){
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);
	}
	else if(Local_u8Data=='2'){
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW);
	}
}
