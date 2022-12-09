/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: USART                       ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

#define ENABLE                          1
#define DISABLE                         2

#define CHAR_5_BITS                     1
#define CHAR_6_BITS                     2
#define CHAR_7_BITS                     3
#define CHAR_8_BITS                     4
#define CHAR_9_BITS                     5

#define ASYNCHRO                        1
#define SYNCHRO                         2

#define ODD                             3
#define EVEN                            4

#define STOP_1_BIT                      1
#define STOP_2_BITS                     2

#define TX_RISING_RX_FALLING            1
#define TX_FALLING_RX_RISING            2

#define BAUD_RATE_2_4_K                 2400UL
#define BAUD_RATE_4_8_K                 4800UL
#define BAUD_RATE_9_6_K                 9600UL
#define BAUD_RATE_14_4_K                14400UL
#define BAUD_RATE_19_2_K                19200UL
#define BAUD_RATE_28_8_K                28800UL
#define BAUD_RATE_38_4_K                38400UL
#define BAUD_RATE_57_6_K                57600UL
#define BAUD_RATE_76_8_K                76800UL
#define BAUD_RATE_115_2_K               115200UL
#define BAUD_RATE_230_4_K               230400UL
#define BAUD_RATE_250_K                 250000UL
#define BAUD_RATE_500_K                 500000UL
#define BAUD_RATE_1000_K                1000000UL
#define SYSTEM_FREQ						8000000UL

#define TIMEOUT							500000

#define CHAR							1
#define STRING							2
#define BUFFER							3

#define BUSY							0
#define IDLE							1
#endif
