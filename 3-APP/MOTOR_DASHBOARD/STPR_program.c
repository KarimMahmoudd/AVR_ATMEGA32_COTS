/************************************************************************************************************************/
/************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            **********************************************/
/******************************           Layer: HAL                       **********************************************/
/******************************           SWC: STEPPER MOTOR               **********************************************/
/******************************           Version: 1.00                    **********************************************/
/******************************           Date: 18/10/2022                 **********************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/

#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h"

#include "STPR_config.h"
#include "STPR_private.h"
#include "STPR_Interface.h"

void STPR_voidRotateClockwise(){
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_BLUE,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_PINK,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_YELLOW,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_ORANGE,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_BLUE,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_PINK,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_YELLOW,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_ORANGE,DIO_u8PIN_LOW);
	_delay_ms(2);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_BLUE,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_PINK,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_YELLOW,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_ORANGE,DIO_u8PIN_LOW);
	_delay_ms(2);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_BLUE,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_PINK,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_YELLOW,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_ORANGE,DIO_u8PIN_LOW);
	_delay_ms(2);
}
void STPR_voidRotateCounterClockwise(){
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_BLUE,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_PINK,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_YELLOW,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_ORANGE,DIO_u8PIN_LOW);
	_delay_ms(2);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_BLUE,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_PINK,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_YELLOW,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_ORANGE,DIO_u8PIN_LOW);
	_delay_ms(2);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_BLUE,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_PINK,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_YELLOW,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_ORANGE,DIO_u8PIN_LOW);
	_delay_ms(2);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_BLUE,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_PINK,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_YELLOW,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPR_PORT,STPR_COIL_ORANGE,DIO_u8PIN_HIGH);
	_delay_ms(2);
}
void STPR_voidRotateAngle(u8 Copy_u8Direction, u32 Copy_u8Angle){
	u32 Local_u8Iterations=((Copy_u8Angle*10)/7);
	if(Copy_u8Direction==STPR_CLOCKWISE){
		for(u32 Local_u8Iterator=0;Local_u8Iterator<Local_u8Iterations;Local_u8Iterator++){
			STPR_voidRotateClockwise();
		}
	}
	else if(Copy_u8Direction==STPR_COUNTER_CLOCKWISE){
		for(u32 Local_u8Iterator=0;Local_u8Iterator<Local_u8Iterations;Local_u8Iterator++){
			STPR_voidRotateCounterClockwise();
		}
	}
}
