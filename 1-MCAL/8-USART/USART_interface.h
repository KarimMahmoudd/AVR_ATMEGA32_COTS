/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: USART                       ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

void USART_voidInit(void);

u8 USART_u8SendCharSynch(u16 Copy_u16Data);

u8 USART_u8SendCharAsynch(u16 Copy_u16Data,void (*Copy_pvNotifFunc)(void));

u8 USART_u8SendStringSynch(char* Copy_pchString);

u8 USART_u8SendStringAsynch(char* Copy_pchString,void (*Copy_pvNotifFunc)(void));

u8 USART_u8ReceiveCharSynch(u16* Copy_pu16ReceivedData);

u8 USART_u8ReceiveCharAsynch(u16* Copy_pu16ReceivedData,void (*Copy_pvNotifFunc)(void));

u8 USART_u8ReceiveBufferSynch(u8* Copy_u8Buffer,u8 Copy_u8BufferSize);

u8 USART_u8ReceiveBufferAsynch(u8* Copy_u8Buffer,u8 Copy_u8BufferSize,void (*Copy_pvNotifFunc)(void));
#endif
