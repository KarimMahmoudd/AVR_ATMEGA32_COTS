/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: TIMER                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

void TIMER0_voidInit(void);

void TIMER1_voidInit(void);

void TIMER2_voidInit(void);

void TIMER0_voidSetCompMatchValue(u8 Copy_u8Value);

void TIMER0_voidSetPreloadValue(u8 Copy_u8Value);

void TIMER1A_voidSetCompMatchValue(u16 Copy_u16Value);

void TIMER1B_voidSetCompMatchValue(u16 Copy_u16Value);

void TIMER1_voidSetTopValue(u16 Copy_u16Value);

void TIMER2_voidSetCompMatchValue(u8 Copy_u8Value);

void TIMER2_voidSetPreloadValue(u8 Copy_u8Value);

u8 TIMER0_u8SetCallBack(void(*Copy_pvCallBackFunc)(void));

u8 TIMER1_u8SetCallBack(void(*Copy_pvCallBackFunc)(void));

u8 TIMER2_u8SetCallBack(void(*Copy_pvCallBackFunc)(void));

#endif
