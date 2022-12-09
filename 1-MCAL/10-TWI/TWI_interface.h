/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: TWI                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef enum
{
	NoError,
	NullPointerError,
	TimeOutError,
	BitRateError,
	ReservedAddressError,
	StartConditionError,
	RepeatedStartError,
	SlaveAddressWithWriteError,
	SlaveAddressWithReadError,
	WriteDataByteError,
	ReadDataByteError,

}TWI_ErrStatus;
//Pass 0 in the address argument if the master will not be addressed

TWI_ErrStatus TWI_MasterInit(u8 Copy_u8Address);

TWI_ErrStatus TWI_SlaveInit(u8 Copy_u8Address);

TWI_ErrStatus TWI_SendStartCondition(void);

TWI_ErrStatus TWI_SendRepeatedStart(void);

TWI_ErrStatus TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);

TWI_ErrStatus TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);

TWI_ErrStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByte);

TWI_ErrStatus TWI_MasterReadDataByte(u8* Copy_pu8DataByte);

void TWI_SendStopCondition(void);

#endif
