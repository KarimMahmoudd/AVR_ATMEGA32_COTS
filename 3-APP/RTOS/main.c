#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "RTOS_interface.h"

void LED1(void);
void LED2(void);
void LED3(void);

void main(void){
	PORT_voidInit();

	RTOS_voidCreateTask(0,1000,&LED1);
	RTOS_voidCreateTask(1,2000,&LED2);
	RTOS_voidCreateTask(2,3000,&LED3);

	RTOS_voidStart();

	while(1){

	}
}

void LED1(void){
	DIO_u8TogglePinValue(DIO_u8PORTA,DIO_u8PIN0);
}
void LED2(void){
	DIO_u8TogglePinValue(DIO_u8PORTA,DIO_u8PIN1);
}
void LED3(void){
	DIO_u8TogglePinValue(DIO_u8PORTA,DIO_u8PIN2);
}
