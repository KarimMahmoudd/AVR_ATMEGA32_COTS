/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: SPI                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void SPI_voidMasterInit(void);
void SPI_voidSlaveInit(void);
u8 SPI_u8SynchTranscieve(u8 Copy_u8Data,u8* Copy_pu8ReceivedData);
u8 SPI_u8AsynchTranscieve(u8 Copy_u8Data,u8* Copy_pu8ReceivedData, void (*Copy_pvNotifFunc)(void));

#endif