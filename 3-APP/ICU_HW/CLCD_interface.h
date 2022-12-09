/************************************************************************************************************************/
/************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            **********************************************/
/******************************           Layer: HAL                       **********************************************/
/******************************           SWC: CLCD                        **********************************************/
/******************************           Version: 1.00                    **********************************************/
/******************************           Date: 9/10/2022                  **********************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

void CLCD_voidSendCommand(u8 Copy_u8Command);

void CLCD_voidSendData(u8 Copy_u8Data);

void CLCD_voidSendString(const char* Copy_pu8Arr);

void CLCD_voidInit(void);

void CLCD_voidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos);

void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Arr,u8 Copy_u8BlockNumber);

void CLCD_voidSendSpecialCharacter(u8 Copy_u8PatternNumber,u8 Copy_u8XPos,u8 Copy_u8YPos);

void CLCD_voidSendNumber(u32 Copy_u32Number);

void CLCD_voidCLR(void);

#endif
