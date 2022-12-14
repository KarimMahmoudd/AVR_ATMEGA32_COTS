/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: RTOS Stack                ***********************************************/
/******************************           SWC: TIMER0                      ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

u8 TIMER0_u8SetCallBack(void(*Copy_pvCallBackFunc)(void));

void TIMER0_voidSetTimerVal(u8 Copy_u8Value);

u8 TIMER0_u8GetTimerVal(void);

void TIMER0_voidSetCompMatch(u8 Copy_u8Value);

void TIMER0_voidInit(void);

#endif
