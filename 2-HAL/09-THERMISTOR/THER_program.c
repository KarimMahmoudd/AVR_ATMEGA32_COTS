/************************************************************************************************************************/
/************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            **********************************************/
/******************************           Layer: HAL                       **********************************************/
/******************************           SWC: THERMISTOR                  **********************************************/
/******************************           Version: 1.00                    **********************************************/
/******************************           Date: 23/10/2022                 **********************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
#include "STD_TYPES.h"

#include "ADC_interface.h"

#include "THER_config.h"
#include "THER_interface.h"
#include "THER_private.h"
u8 THER_u8GetTemperature(void){
    u8 Local_u8DigitalValue, Local_u8Temp; u16 Local_u16MilliVoltValue;
    Local_u8DigitalValue = ADC_u8GetChannelReading(THER_CHANNEL);
}
