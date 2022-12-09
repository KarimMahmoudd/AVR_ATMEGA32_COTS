/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: USART                       ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#ifndef USART_REGISTER_H_
#define USART_REGISTER_H_

//USART I/O Data Register

#define UDR                             *((volatile u8*)(0x2c))

// USART Control and Status Register A

#define UCSRA                           *((volatile u8*)(0x2b))
#define UCSRA_RXC                       7       // USART Receive Complete Flag
#define UCSRA_TXC                       6       // USART Transmit Complete Flag
#define UCSRA_UDRE                      5       // USART Data Register Empty Flag
#define UCSRA_FE                        4       // Frame Error Flag
#define UCSRA_DOR                       3       // Data OverRun Flag
#define UCSRA_PE                        2       // Parity Error Flag
#define UCSRA_U2X                       1       // Double the USART Transmission Speed
#define UCSRA_MPCM                      0       // Multi-processor Communication Mode

//USART Control and Status Register B

#define UCSRB                           *((volatile u8*)(0x2a))
#define UCSRB_RXCIE                     7       // RX Complete Interrupt Enable
#define UCSRB_TXCIE                     6       // TX Complete Interrupt Enable
#define UCSRB_UDRIE                     5       // USART Data Register Empty Interrupt Enable
#define UCSRB_RXEN                      4       // Receiver Enable
#define UCSRB_TXEN                      3       // Transmitter Enable
#define UCSRB_UCSZ2                     2       // Character Size Select Bit 2
#define UCSRB_RXB8                      1       // Receive Data Bit 8
#define UCSRB_TXB8                      0       // Transmit Data Bit 8

//USART Control and Status Register C

#define UCSRC                           *((volatile u8*)(0x40))
#define UCSRC_URSEL                     7       // Register Select (Set to 1 For USCRC and 0 for UBRRH)
#define UCSRC_UMSEL                     6       // USART Mode Select
#define UCSRC_UPM1                      5       // Parity Mode Select Bit 1
#define UCSRC_UPM0                      4       // Parity Mode Select Bit 0
#define UCSRC_USBS                      3       // Stop Bit Select
#define UCSRC_UCSZ1                     2       // Character Size Select Bit 1
#define UCSRC_UCSZ0                     1       // Character Size Select Bit 0
#define UCSRC_UCPOL                     0       // Clock Polarity Select

//USART Baud Rate Registers High and Low
#define UBRRH                           *((volatile u8*)(0x40))
#define UBRRL                           *((volatile u8*)(0x29))

#endif
