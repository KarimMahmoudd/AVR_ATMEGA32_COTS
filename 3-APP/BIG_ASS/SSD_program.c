/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: HAL                      ***********************************************/
/******************************           SWC: SSD                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
#include "STD_TYPES.h"

#include "SSD_interface.h"
#include "SSD_private.h"
#include "SSD_config.h"

#include "DIO_interface.h"

u8 SevenSegArray[10]={
		0b00111111,
		0b00000110,
		0b01011011,
		0b01001111,
		0b01100110,
		0b01101101,
		0b01111101,
		0b00000111,
		0b01111111,
		0b01101111};

u8 SSD_u8SetNumber(u8 Copy_u8Number,SSD_t* SSD){
	u8 Local_u8ErrorStatus=OK;
	if(Copy_u8Number<=9){
		if((SSD->COM_TYPE)==ANODE){
			DIO_u8SetPortValue((SSD)->Port,~(SevenSegArray[Copy_u8Number]));
		}
		else if((SSD->COM_TYPE)==CATHODE){
			DIO_u8SetPortValue((SSD)->Port,SevenSegArray[Copy_u8Number]);
		}
		else{
			Local_u8ErrorStatus=NOK;
		}
	}
	else{
		Local_u8ErrorStatus=NOK;
	}
	return Local_u8ErrorStatus;
}

u8 SSD_u8Enable(SSD_t* SSD){
	u8 Local_u8ErrorStatus=OK;
	if((SSD->COM_TYPE)==ANODE){
		DIO_u8SetPinValue((SSD)->EnablePort,(SSD)->EnablePin,DIO_u8PIN_HIGH);
	}
	else if((SSD->COM_TYPE)==CATHODE){
		DIO_u8SetPinValue((SSD)->EnablePort,(SSD)->EnablePin,DIO_u8PIN_LOW);
	}
	else{
		Local_u8ErrorStatus=NOK;
	}
	return Local_u8ErrorStatus;
}

u8 SSD_u8Disable(SSD_t* SSD){
	u8 Local_u8ErrorStatus=OK;
	if((SSD->COM_TYPE)==ANODE){
		DIO_u8SetPinValue((SSD)->EnablePort,(SSD)->EnablePin,DIO_u8PIN_LOW);
	}
	else if((SSD->COM_TYPE)==CATHODE){
		DIO_u8SetPinValue((SSD)->EnablePort,(SSD)->EnablePin,DIO_u8PIN_HIGH);
	}
	else{
		Local_u8ErrorStatus=NOK;
	}
	return Local_u8ErrorStatus;
}
