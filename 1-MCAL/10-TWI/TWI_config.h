/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: TWI                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#ifndef TWI_CONFIG_H_
#define TWI_CONFIG_H_

/* Options:
 * 			1-DIV_BY_1
 * 			2-DIV_BY_4
 * 			3-DIV_BY_16
 * 			4-DIV_BY_64								*/

#define PRESCALER				DIV_BY_1

/* Options:
 * 			0-400000								*/

#define SCL_FREQ				400000

/* Options:
 * 			1-DISABLE
 * 			2-ENABLE								*/

#define TWI_INTERRUPT				DISABLE

#define ADDRESS_ENABLE				DISABLE

#define GENERAL_CALL				DISABLE

#define ACKNOWLEDGE					ENABLE


#endif