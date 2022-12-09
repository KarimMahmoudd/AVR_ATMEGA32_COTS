/************************************************************************************************************************/
/************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            **********************************************/
/******************************           Layer: HAL                       **********************************************/
/******************************           SWC: CLCD                        **********************************************/
/******************************           Version: 1.00                    **********************************************/
/******************************           Date: 9/10/2022                  **********************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_


#define CLCD_DATA_PORT              			DIO_u8PORTD
/*Function Set: 2 lines, 5*8 font size*/
#define CLCD_FUNCTION_SET						0b00111000
/*Display on off control: display enable, disable cursor, no blink cursor*/
#define CLCD_DISPLAY_ON_OFF_CTRL				0b00001100
#define CLCD_DISPLAY_CLR								1

#define CLCD_CTRL_PORT              			DIO_u8PORTC
#define CLCD_RS_PIN                				DIO_u8PIN0
#define CLCD_RW_PIN                 			DIO_u8PIN1
#define CLCD_E_PIN                  			DIO_u8PIN2




#endif
