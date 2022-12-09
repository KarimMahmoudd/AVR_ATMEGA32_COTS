/************************************************************************************************************************/
/************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            **********************************************/
/******************************           Layer: HAL                       **********************************************/
/******************************           SWC: KEYPAD                      **********************************************/
/******************************           Version: 1.00                    **********************************************/
/******************************           Date: 14/10/2022                 **********************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "KPD_config.h"
#include "KPD_interface.h"
#include "KPD_private.h"

u8 KPD_u8GetPressedKey(void)
{
	u8 Local_u8PressedKey = KPD_NO_PRESSED_KEY, Local_u8ColumnIdx,Local_u8RowIdx,Local_u8PinState;
	static u8 Local_u8KPDArr[ROW_NUM][COLUMN_NUM] = KPD_ARR_VAL;
	static u8 Local_u8ColumnArr[COLUMN_NUM] ={KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN,KPD_COLUMN3_PIN};
	static u8 Local_u8RowArr[ROW_NUM] = {KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};

	for(Local_u8ColumnIdx=0;Local_u8ColumnIdx<COLUMN_NUM;Local_u8ColumnIdx++)
	{
		//Activate Current Column
		DIO_u8SetPinValue(KPD_PORT,Local_u8ColumnArr[Local_u8ColumnIdx],DIO_u8PIN_LOW);
		for(Local_u8RowIdx=0;Local_u8RowIdx<ROW_NUM;Local_u8RowIdx++)
		{
			//Read the current Row
			DIO_u8GetPinValue(KPD_PORT,Local_u8RowArr[Local_u8RowIdx],&Local_u8PinState);
			//check if switch is pressed
			if(DIO_u8PIN_LOW==Local_u8PinState)
			{
				Local_u8PressedKey= Local_u8KPDArr[Local_u8RowIdx][Local_u8ColumnIdx];
				//polling(busy waiting until the key is released
				while(DIO_u8PIN_LOW==Local_u8PinState)
				{
					DIO_u8GetPinValue(KPD_PORT,Local_u8RowArr[Local_u8RowIdx],&Local_u8PinState);
				}
				return Local_u8PressedKey;
			}
		}
		//Activate Current Column
		DIO_u8SetPinValue(KPD_PORT,Local_u8ColumnArr[Local_u8ColumnIdx],DIO_u8PIN_HIGH);
	}

	return Local_u8PressedKey;
}
