/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: USART                       ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

/*Options:
            1-  ENABLE 
            2-  DISABLE 
                                                            */

#define DOUBLE_TRANSMISSION_SPEED              	DISABLE


#define MULTI_PROCESSOR_COMM_MODE               DISABLE


#define RX_COMPLETE_INT                         DISABLE


#define TX_COMPLETE_INT                         DISABLE


#define DATA_REG_EMPTY_INT                      DISABLE


#define TRANSMITTER                             ENABLE


#define RECEIVER                                ENABLE 

/*Options:
            1- CHAR_5_BITS
            2- CHAR_6_BITS
            3- CHAR_7_BITS
            4- CHAR_8_BITS
            5- CHAR_9_BITS
                                                            */

#define CHARACTER_SIZE                          CHAR_8_BITS

/*Options:
            1- ASYNCHRO
            2- SYNCHRO
                                                            */

#define USART_MODE                              ASYNCHRO

/*Options:
            1- DISABLE
            2- ODD
            3- EVEN
                                                            */

#define PARITY_MODE                              DISABLE


/*Options:
            1- STOP_1_BIT
            2- STOP_2_BITS
                                                            */

#define STOP_BIT_SELECT                          STOP_1_BIT


/*Options:
            1- TX_RISING_RX_FALLING
            2- TX_FALLING_RX_RISING
                                                            */

#define CLOCK_POLARITY                           TX_RISING_RX_FALLING


/*Options:
            1-  BAUD_RATE_2_4_K
            2-  BAUD_RATE_4_8_K
            3-  BAUD_RATE_9_6_K
            4-  BAUD_RATE_14_4_K
            5-  BAUD_RATE_19_2_K
            6-  BAUD_RATE_28_8_K
            7-  BAUD_RATE_38_4_K
            8-  BAUD_RATE_57_6_K
            9-  BAUD_RATE_76_8_K
            10- BAUD_RATE_115_2_K
            11- BAUD_RATE_230_4_K
            12- BAUD_RATE_250_K
            13- BAUD_RATE_500_K
            14- BAUD_RATE_1000_K
                                                            */

#define BAUD_RATE                          BAUD_RATE_9_6_K

#endif
