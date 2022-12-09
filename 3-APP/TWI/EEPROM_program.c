/************************************************************************************************************************/
/************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            **********************************************/
/******************************           Layer: HAL                       **********************************************/
/******************************           SWC: EEPROM                       **********************************************/
/******************************           Version: 1.00                    **********************************************/
/******************************           Date: 12/11/2022                  **********************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MATH_HELPER.h"

#include "TWI_interface.h"

#include "EEPROM_config.h"
#include "EEPROM_interface.h"
#include "EEPROM_private.h"

void EEPROM_voidSendDataByte(u16 Copy_u16Address,u8 Copy_u8DataByte){

	u8 Local_u8SlaveAdress=0b1010000;
	Local_u8SlaveAdress|=(A2_CONN<<2);
	Local_u8SlaveAdress|=(Copy_u16Address>>8);

	TWI_SendStartCondition();

	TWI_SendSlaveAddressWithWrite(Local_u8SlaveAdress);

	TWI_MasterWriteDataByte((u8)Copy_u16Address);

	TWI_MasterWriteDataByte(Copy_u8DataByte);

	TWI_SendStopCondition();

}


void EEPROM_voidReadDataByte(u16 Copy_u16Address,u8* Copy_pu8DataByte){

	u8 Local_u8SlaveAdress=0b1010000;
	Local_u8SlaveAdress|=(A2_CONN<<2);
	Local_u8SlaveAdress|=(Copy_u16Address>>8);

	TWI_SendStartCondition();

	TWI_SendSlaveAddressWithWrite(Local_u8SlaveAdress);

	TWI_MasterWriteDataByte((u8)Copy_u16Address);

	TWI_SendRepeatedStart();

	TWI_SendSlaveAddressWithRead(Local_u8SlaveAdress);

	TWI_MasterReadDataByte(Copy_pu8DataByte);

	TWI_SendStopCondition();

}
