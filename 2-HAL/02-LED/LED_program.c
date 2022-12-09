/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: HAL                      ***********************************************/
/******************************           SWC: LED                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "LED_interface.h"
#include "LED_private.h"
#include "LED_config.h"

u8 LED_u8TurnOn(LED_t* LED){
	u8 Local_u8ErrorState=0;
	if(LED->CONN_TYPE==SOURCE){
		DIO_u8SetPinValue(LED->Port,LED->Pin,DIO_u8PIN_HIGH);
	}
	else if(LED->CONN_TYPE==SINK){
		DIO_u8SetPinValue(LED->Port,LED->Pin,DIO_u8PIN_LOW);
	}
	else{
		Local_u8ErrorState=1;

	}
	return Local_u8ErrorState;
}
u8 LED_u8TurnOff(LED_t* LED){
	u8 Local_u8ErrorState=0;
	if(LED->CONN_TYPE==SOURCE){
		DIO_u8SetPinValue(LED->Port,LED->Pin,DIO_u8PIN_LOW);
	}
	else if(LED->CONN_TYPE==SINK){
		DIO_u8SetPinValue(LED->Port,LED->Pin,DIO_u8PIN_HIGH);
	}
	else{
		Local_u8ErrorState=1;

	}
	return Local_u8ErrorState;

}
