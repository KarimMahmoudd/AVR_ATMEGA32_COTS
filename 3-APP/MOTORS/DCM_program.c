/************************************************************************************************************************/
/************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            **********************************************/
/******************************           Layer: HAL                       **********************************************/
/******************************           SWC: DC MOTOR                    **********************************************/
/******************************           Version: 1.00                    **********************************************/
/******************************           Date: 18/10/2022                 **********************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/

#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h"

#include "DCM_config.h"
#include "DCM_private.h"
#include "DCM_Interface.h"

void DCM_voidRotateClockwise(){
	DIO_u8SetPinValue(DCM_PORT,DCM_CTR_CLKWISE_PIN,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DCM_PORT,DCM_CLKWISE_PIN,DIO_u8PIN_HIGH);
}
void DCM_voidRotateCounterClockwise(){
	DIO_u8SetPinValue(DCM_PORT,DCM_CLKWISE_PIN,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DCM_PORT,DCM_CTR_CLKWISE_PIN,DIO_u8PIN_HIGH);
}

void DCM_voidStop(){
		DIO_u8SetPinValue(DCM_PORT,DCM_CLKWISE_PIN,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DCM_PORT,DCM_CTR_CLKWISE_PIN,DIO_u8PIN_LOW);
}