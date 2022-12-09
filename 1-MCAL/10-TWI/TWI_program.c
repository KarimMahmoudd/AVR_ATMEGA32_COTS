/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: TWI                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MATH_HELPER.h"

#include "TWI_config.h"
#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_register.h"


TWI_ErrStatus TWI_MasterInit(u8 Copy_u8Address){
	TWI_ErrStatus Local_ErrorStatus = NoError;
	u16 Local_u16Prescaler = MATH_u32Power(4,PRESCALER);
	u16 Local_u16TWBR = (((SYSTEM_FREQ/SCL_FREQ)-16)/(2*Local_u16Prescaler));
	//Set Prescaler
		TWSR&= PRESCALER_MASK;
		TWSR|= PRESCALER;

	//Set Bit Rate
	TWBR = Local_u16TWBR;
	//Configure Acknowledge Bit
#if ACKNOWLEDGE==ENABLE
	SET_BIT(TWCR,TWCR_TWEA);
#elif ACKNOWLEDGE==DISABLE
	CLR_BIT(TWCR,TWCR_TWEA);
#else
#error "WRONG ACKNOWLEDGE BIT CONFIGURATION"
#endif

#if TWI_INTERRUPT==ENABLE
	SET_BIT(TWCR,TWCR_TWINT);
#elif TWI_INTERRUPT==DISABLE
	CLR_BIT(TWCR,TWCR_TWINT);
#else
#error "WRONG ACKNOWLEDGE BIT CONFIGURATION"
#endif
	//setting the address if it exists
#if ADDRESS_ENABLE==ENABLE
	if(Copy_u8Address<120 && Copy_u8Address!=0){
		TWAR = Copy_u8Address<<1;
#if GENERAL_CALL==ENABLE
		SET_BIT(TWAR,TWAR_TWGCE);
#elif GENERAL_CALL==DISABLE
		CLR_BIT(TWAR,TWAR_TWGCE);
#else
#error "WRONG GENERAL CALL CONFIGURATION"
#endif
	}
	else{
		Local_ErrorStatus=ReservedAddressError;
	}

#endif
	//Enabling the TWI
	SET_BIT(TWCR,TWCR_TWEN);

	return Local_ErrorStatus;
}

TWI_ErrStatus TWI_SlaveInit(u8 Copy_u8Address){
	TWI_ErrStatus Local_ErrorStatus=NoError;

	if(Copy_u8Address<120&&Copy_u8Address!=0){
		TWAR = Copy_u8Address<<1;
#if GENERAL_CALL==ENABLE
		SET_BIT(TWAR,TWAR_TWGCE);
#elif GENERAL_CALL==DISABLE
		CLR_BIT(TWAR,TWAR_TWGCE);
#else
#error "WRONG GENERAL CALL CONFIGURATION"
#endif
	}
	else{
		Local_ErrorStatus=ReservedAddressError;
	}


	//Configure Acknowledge Bit
#if ACKNOWLEDGE==ENABLE
	SET_BIT(TWCR,TWCR_TWEA);
#elif ACKNOWLEDGE==DISABLE
	CLR_BIT(TWCR,TWCR_TWEA);
#else
#error "WRONG ACKNOWLEDGE BIT CONFIGURATION"
#endif

	//Enabling the TWI
	SET_BIT(TWCR,TWCR_TWEN);

	return Local_ErrorStatus;
}

TWI_ErrStatus TWI_SendStartCondition(void){
	TWI_ErrStatus Local_ErrorStatus=NoError;u32 Local_u32Counter=0;

	//Send Start Condition
	SET_BIT(TWCR,TWCR_TWSTA);

	//Clear The Interrupt Flag To Start the operation
	SET_BIT(TWCR,TWCR_TWINT);

	//wait until operation is complete
	while(GET_BIT(TWCR,TWCR_TWINT)==0 && Local_u32Counter<TIMEOUT){
		Local_u32Counter++;
	}
	if(Local_u32Counter==TIMEOUT){
		Local_ErrorStatus=TimeOutError;
	}
	else{
		//Read The Status Register
		if((TWSR & STATUS_BIT_MASK)!= START_ACK){
			Local_ErrorStatus= StartConditionError;
		}
	}

	return Local_ErrorStatus;
}

TWI_ErrStatus TWI_SendRepeatedStart(void){
	TWI_ErrStatus Local_ErrorStatus=NoError;u32 Local_u32Counter=0;

	//Send Start Condition
	SET_BIT(TWCR,TWCR_TWSTA);

	//Clear The Interrupt Flag To Start the operation
	SET_BIT(TWCR,TWCR_TWINT);

	//wait until operation is complete
	while(GET_BIT(TWCR,TWCR_TWINT)==0 && Local_u32Counter<TIMEOUT){
		Local_u32Counter++;
	}
	if(Local_u32Counter==TIMEOUT){
		Local_ErrorStatus=TimeOutError;
	}
	else{
		//Read The Status Register
		if((TWSR & STATUS_BIT_MASK)!= REP_START_ACK){
			Local_ErrorStatus= RepeatedStartError;
		}
	}



	return Local_ErrorStatus;
}

TWI_ErrStatus TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress){
	TWI_ErrStatus Local_ErrorStatus=NoError;u32 Local_u32Counter=0;

	//Set Slave Address in 7 Most Significant Bits
	TWDR= Copy_u8SlaveAddress<<1;

	//Clear the LSB for Write Operation
	CLR_BIT(TWDR,TWDR_TWD0);

	//Clear The Start Condition Bit
	CLR_BIT(TWCR,TWCR_TWSTA);

	//Clear The Interrupt Flag To Start the operation
	SET_BIT(TWCR,TWCR_TWINT);

	//wait until operation is complete
	while(GET_BIT(TWCR,TWCR_TWINT)==0 && Local_u32Counter<TIMEOUT){
		Local_u32Counter++;
	}
	if(Local_u32Counter==TIMEOUT){
		Local_ErrorStatus=TimeOutError;
	}
	else{
		//Read The Status Register
		if((TWSR & STATUS_BIT_MASK)!= SLAVE_ADD_AND_WR_ACK){
			Local_ErrorStatus= SlaveAddressWithWriteError;
		}
	}



	return Local_ErrorStatus;
}

TWI_ErrStatus TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress){
	TWI_ErrStatus Local_ErrorStatus=NoError; u32 Local_u32Counter=0;

	//Set Slave Address in 7 Most Significant Bits
	TWDR= Copy_u8SlaveAddress<<1;

	//Set the LSB for Read Operation
	SET_BIT(TWDR,TWDR_TWD0);

	//Clear The Start Condition Bit
	CLR_BIT(TWCR,TWCR_TWSTA);

	//Clear The Interrupt Flag To Start the operation
	SET_BIT(TWCR,TWCR_TWINT);

	//wait until operation is complete
	while(GET_BIT(TWCR,TWCR_TWINT)==0 && Local_u32Counter<TIMEOUT){
		Local_u32Counter++;
	}
	if(Local_u32Counter==TIMEOUT){
		Local_ErrorStatus=TimeOutError;
	}
	else{
		//Read The Status Register
		if((TWSR & STATUS_BIT_MASK)!= SLAVE_ADD_AND_RD_ACK){
			Local_ErrorStatus= SlaveAddressWithReadError;
		}
	}



	return Local_ErrorStatus;
}

TWI_ErrStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByte){
	TWI_ErrStatus Local_ErrorStatus=NoError; u32 Local_u32Counter=0;

	//Set Slave Address in 7 Most Significant Bits
	TWDR=Copy_u8DataByte;

	//Clear The Interrupt Flag To Start the operation
	SET_BIT(TWCR,TWCR_TWINT);

	//wait until operation is complete
	while(GET_BIT(TWCR,TWCR_TWINT)==0 && Local_u32Counter<TIMEOUT){
		Local_u32Counter++;
	}

	if(Local_u32Counter==TIMEOUT){
		Local_ErrorStatus=TimeOutError;
	}
	else{
		//Read The Status Register
		if((TWSR & STATUS_BIT_MASK)!= MSTR_WR_BYTE_ACK){
			Local_ErrorStatus= WriteDataByteError;
		}
	}


	return Local_ErrorStatus;
}

TWI_ErrStatus TWI_MasterReadDataByte(u8* Copy_pu8DataByte){
	TWI_ErrStatus Local_ErrorStatus=NoError; u32 Local_u32Counter=0;
	if(Copy_pu8DataByte!=NULL){
		//Clear The Interrupt Flag To Start the operation (Allowing Slave to send data)
		SET_BIT(TWCR,TWCR_TWINT);

		//wait until operation is complete
		while(GET_BIT(TWCR,TWCR_TWINT)==0 && Local_u32Counter<TIMEOUT){
			Local_u32Counter++;
		}

		if(Local_u32Counter==TIMEOUT){
			Local_ErrorStatus=TimeOutError;
		}
		else{
#if ACKNOWLEDGE==ENABLE
			//Read The Status Register
			if((TWSR & STATUS_BIT_MASK)!= MSTR_RD_BYTE_WITH_ACK){
				Local_ErrorStatus= ReadDataByteError;
			}
			else{
				*Copy_pu8DataByte = TWDR;
			}
#elif ACKNOWLEDGE==DISABLE
			//Read The Status Register
			if((TWSR & STATUS_BIT_MASK)!= MSTR_RD_BYTE_WITH_NACK){
				Local_ErrorStatus= ReadDataByteError;
			}
			else{
				*Copy_pu8DataByte = TWDR;
			}
#else
#error "WRONG ACKNOWLEDGE BIT CONFIGURATION"
#endif
		}

	}
	else{
		Local_ErrorStatus=NullPointerError;
	}


	return Local_ErrorStatus;
}

void TWI_SendStopCondition(void){
	//Generate Stop Condition on the bus
	SET_BIT(TWCR,TWCR_TWSTO);
	//Clear The Interrupt Flag To Start the operation
	SET_BIT(TWCR,TWCR_TWINT);

}
