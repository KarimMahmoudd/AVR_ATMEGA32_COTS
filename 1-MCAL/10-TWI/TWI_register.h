/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: TWI                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#ifndef TWI_REGISTER_H_
#define TWI_REGISTER_H_

#define TWDR			*((volatile u8 *)(0x23))			//  TWI Data Register
#define	TWDR_TWD0		0									//  TWI Read/Write Request


#define TWAR			*((volatile u8 *)(0x22))			//  TWI Address Register
#define	TWAR_TWGCE		0									//  TWI Global Call Enable

#define TWSR			*((volatile u8 *)(0x21))			//  TWI Status Register
#define TWSR_TWPS0		0									//  TWI Prescaler bit0
#define TWSR_TWPS1		1                                   //  TWI Prescaler bit1

#define TWCR			*((volatile u8 *)(0x56))			//  TWI Control Register
#define	TWCR_TWIE		0									//  TWI Interrupt Enable
#define	TWCR_TWEN		2									//  TWI Enable
#define	TWCR_TWWC		3									//  TWI Write Collision Flag
#define	TWCR_TWSTO		4									//  TWI Stop Condition
#define	TWCR_TWSTA		5									//  TWI Start Condition
#define	TWCR_TWEA		6									//  TWI Enable Acknowledge
#define	TWCR_TWINT		7									//  TWI Interrupt Flag

#define TWBR			*((volatile u8 *)(0x20))			//  TWI Bit Rate Register


#endif
