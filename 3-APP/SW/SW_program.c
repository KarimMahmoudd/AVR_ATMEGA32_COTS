/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: HAL                      ***********************************************/
/******************************           SWC: SW                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "SW_interface.h"
#include "SW_private.h"
#include "SW_config.h"

#include <util/delay.h>

u8 SW_u8GetState(SW_t* SW,u8* Copy_pu8SwitchState){
	u8 Local_u8ErrorState=0;
	if((SW->LockingType) == BOUNCING){
		if((SW->PullType) == PULL_UP){
			DIO_u8SetPinDirection(SW->Port,SW->Pin,DIO_u8PIN_INPUT);
			DIO_u8SetPinValue(SW->Port,SW->Pin,DIO_u8PIN_HIGH);
			DIO_u8GetPinValue(SW->Port,SW->Pin,Copy_pu8SwitchState);
			if((*Copy_pu8SwitchState) == DIO_u8PIN_LOW){
				_delay_ms(60);
				DIO_u8GetPinValue(SW->Port,SW->Pin,Copy_pu8SwitchState);
				if((*Copy_pu8SwitchState) == DIO_u8PIN_LOW){
					*Copy_pu8SwitchState = PRESSED;
				}
				else if((*Copy_pu8SwitchState)==DIO_u8PIN_HIGH){
					*Copy_pu8SwitchState = NOT_PRESSED;
				}
			}
			else if((*Copy_pu8SwitchState)==DIO_u8PIN_HIGH){
				*Copy_pu8SwitchState = NOT_PRESSED;
			}
		}
		else if((SW->PullType)==PULL_DOWN){
			/*implement for pull down atmega 32 doesn't have pull down resistors*/
		}
		else{
			Local_u8ErrorState=1;
		}
	}
	else if((SW->LockingType) == LOCKING){
		if((SW->PullType) == PULL_UP){
			DIO_u8SetPinDirection(SW->Port,SW->Pin,DIO_u8PIN_INPUT);
			DIO_u8SetPinValue(SW->Port,SW->Pin,DIO_u8PIN_HIGH);
			DIO_u8GetPinValue(SW->Port,SW->Pin,Copy_pu8SwitchState);
			if((*Copy_pu8SwitchState) == DIO_u8PIN_LOW){
				*Copy_pu8SwitchState = PRESSED;
			}
			else if((*Copy_pu8SwitchState)==DIO_u8PIN_HIGH){
				*Copy_pu8SwitchState = NOT_PRESSED;
			}
			else if((SW->PullType)==PULL_DOWN){
				/*implement for pull down atmega 32 doesn't have pull down resistors*/
			}
			else{
				Local_u8ErrorState=1;
			}
		}
	}
	else{
		Local_u8ErrorState=1;
	}
	return Local_u8ErrorState;
}
