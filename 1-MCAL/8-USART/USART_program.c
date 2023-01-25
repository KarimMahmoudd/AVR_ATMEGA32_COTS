/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: USART                       ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_config.h"
#include "USART_interface.h"
#include "USART_private.h"
#include "USART_register.h"
static u8 USART_u8State=IDLE;
static u8 USART_u8TransmissionState;
static u16 USART_u16TransmittedData;
static char* USART_pchTransmittedString;
static u16* USART_pu16ReceivedData;
static u8* USART_pu8ReceivedBuffer;
static u8 USART_u8ReceivedBufferSize;
static void (*TXC_pvNotifFunc)(void);
static void (*RXC_pvNotifFunc)(void);
static void (*UDRE_pvNotifFunc)(void);

void USART_voidInit(void){
	u16 Local_u16UBRR;
	u8 Local_u8UCSRC=0;
	SET_BIT(Local_u8UCSRC,UCSRC_URSEL);
	//Receive Complete Interrupt
#if RX_COMPLETE_INT==ENABLE
	SET_BIT(UCSRB,UCSRB_RXCIE);
#elif RX_COMPLETE_INT==DISABLE
	CLR_BIT(UCSRB,UCSRB_RXCIE);
#else

#error "WRONG RX INT CONFIGURATION"

#endif

	//Transmission Complete Interrupt
#if TX_COMPLETE_INT==ENABLE
	SET_BIT(UCSRB,UCSRB_TXCIE);
#elif TX_COMPLETE_INT==DISABLE
	CLR_BIT(UCSRB,UCSRB_TXCIE);
#else

#error "WRONG TX INT CONFIGURATION"

#endif

	//Data Register Empty Interrupt
#if DATA_REG_EMPTY_INT==ENABLE
	SET_BIT(UCSRB,UCSRB_UDRIE);
#elif DATA_REG_EMPTY_INT==DISABLE
	CLR_BIT(UCSRB,UCSRB_UDRIE);
#else

#error "WRONG DATA REG EMPTY INT CONFIGURATION"

#endif

	//USART MODE and Clock Configurations
#if USART_MODE==ASYNCHRO
	CLR_BIT(Local_u8UCSRC,UCSRC_UMSEL);
#elif USART_MODE==SYNCHRO
	SET_BIT(Local_u8UCSRC,UCSRC_UMSEL);

#if DOUBLE_TRANSMISSION_SPEED==ENABLE
	SET_BIT(UCSRB,UCSRA_U2X);
#elif DOUBLE_TRANSMISSION_SPEED==DISABLE
	CLR_BIT(UCSRB,UCSRA_U2X);
#else

#error "WRONG DOUBLE TRANSMISSION SPEED CONFIGURATION"

#endif

#if MULTI_PROCESSOR_COMM_MODE==ENABLE
	SET_BIT(UCSRB,UCSRA_MPCM);
#elif MULTI_PROCESSOR_COMM_MODE==DISABLE
	CLR_BIT(UCSRB,UCSRA_MPCM);
#else

#error "WRONG MULTIPROCESSOR COMM MODE CONFIGURATION"

#endif

#if CLOCK_POLARITY==TX_FALLING_RX_RISING
	SET_BIT(Local_u8UCSRC,UCSRC_UCPOL);
#elif CLOCK_POLARITY==TX_RISING_RX_FALLING
	CLR_BIT(Local_u8UCSRC,UCSRC_UCPOL);
#else

#error "WRONG CLOCK POLARITY CONFIGURATION"

#endif

#else

#error "WRONG USART MODE CONFIGURATION"

#endif

	//Parity Mode
#if PARITY_MODE==DISABLE
	CLR_BIT(Local_u8UCSRC,UCSRC_UPM1);
	CLR_BIT(Local_u8UCSRC,UCSRC_UPM0);
#elif PARITY_MODE==EVEN
	SET_BIT(Local_u8UCSRC,UCSRC_UPM1);
	CLR_BIT(Local_u8UCSRC,UCSRC_UPM0);
#elif PARITY_MODE==ODD
	SET_BIT(Local_u8UCSRC,UCSRC_UPM1);
	SET_BIT(Local_u8UCSRC,UCSRC_UPM0);
#else

#error "WRONG PARITY MODE CONFIGURATION"

#endif

	//Stop Bit Configuration
#if STOP_BIT_SELECT==STOP_1_BIT
	CLR_BIT(Local_u8UCSRC,UCSRC_USBS);
#elif USART_MODE==STOP_2_BIT
	SET_BIT(Local_u8UCSRC,UCSRC_USBS);
#else

#error "WRONG STOP BIT CONFIGURATION"

#endif

	//Character(Data) Size Per Frame Configuration
#if CHARACTER_SIZE == CHAR_5_BITS
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
	CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
#elif CHARACTER_SIZE == CHAR_6_BITS
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
#elif CHARACTER_SIZE == CHAR_7_BITS
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	SET_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
	CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
#elif CHARACTER_SIZE == CHAR_8_BITS
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	SET_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
#elif CHARACTER_SIZE == CHAR_9_BITS
	SET_BIT(UCSRB,UCSRB_UCSZ2);
	SET_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
#else

#error "WRONG CHARACTER SIZE CONFIGURATION"

#endif

	//Setting UCSRC Register
	UCSRC=Local_u8UCSRC;

	//Baud Rate Configuration
#if DOUBLE_TRANSMISSION_SPEED==ENABLE
	Local_u16UBRR = (((SYSTEM_FREQ)/(8*BAUD_RATE))-1);
	UBRRL=Local_u16UBBR;
	UBRRH = (Local_u16UBBR>>8);
#elif DOUBLE_TRANSMISSION_SPEED==DISABLE
	Local_u16UBRR = ((SYSTEM_FREQ)/(16*BAUD_RATE))-1;
	UBRRL=Local_u16UBRR;
	UBRRH = (Local_u16UBRR>>8);
#endif

	//Reciever and Transmitter Setting
#if RECEIVER==ENABLE
	SET_BIT(UCSRB,UCSRB_RXEN);
#elif RECEIVER==DISABLE
	CLR_BIT(UCSRB,UCSRB_RXEN);
#else

#error "WRONG RECEIVER CONFIGURATION"

#endif

#if TRANSMITTER==ENABLE
	SET_BIT(UCSRB,UCSRB_TXEN);
#elif TRANSMITTER==DISABLE
	CLR_BIT(UCSRB,UCSRB_TXEN);
#else

#error "WRONG TRANSMITTER CONFIGURATION"

#endif

}

u8 USART_u8SendCharSynch(u16 Copy_u16Data){
	u8 Local_u8ErrorState=OK;
	if(USART_u8State==IDLE){
		USART_u8State=BUSY;
		u32 Local_u32Counter=0;
		while(GET_BIT(UCSRA,UCSRA_UDRE)==0&&Local_u32Counter!=TIMEOUT){
			Local_u32Counter++;
		}
		if(Local_u32Counter==TIMEOUT){
			Local_u8ErrorState=FUNC_TIMEOUT;
		}
		else{
			UDR=Copy_u16Data;

			if(CHARACTER_SIZE==CHAR_9_BITS){
				if(GET_BIT(Copy_u16Data,8)==1){
					SET_BIT(UCSRB,UCSRB_TXB8);
				}
				else if(GET_BIT(Copy_u16Data,8)==0){
					CLR_BIT(UCSRB,UCSRB_TXB8);
				}
			}
		}
		USART_u8State=IDLE;
	}
	else{
		Local_u8ErrorState=BUSY_FUNC;
	}



	return Local_u8ErrorState;


}

u8 USART_u8SendCharAsynch(u16 Copy_u16Data,void (*Copy_pvNotifFunc)(void)){
	u8 Local_u8ErrorState=OK;
	if(USART_u8State==IDLE){
		if(Copy_pvNotifFunc!=NULL){
			USART_u8State=BUSY;
			USART_u8TransmissionState=CHAR;
			USART_u16TransmittedData=Copy_u16Data;
			TXC_pvNotifFunc=Copy_pvNotifFunc;
			SET_BIT(UCSRB,UCSRB_UDRIE);
		}
		else{
			Local_u8ErrorState=NULL_POINTER;
		}
	}
	else{
		Local_u8ErrorState=BUSY_FUNC;
	}

	return Local_u8ErrorState;
}

u8 USART_u8SendStringSynch(char* Copy_pchString){
	u8 Local_u8ErrorState=OK;
	if(Copy_pchString!=NULL){
		u8 Local_u8Index=0;
		while(Copy_pchString[Local_u8Index]!='\0'){
			USART_u8SendCharSynch(Copy_pchString[Local_u8Index++]);
		}
	}
	else{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}

u8 USART_u8SendStringAsynch(char* Copy_pchString,void (*Copy_pvNotifFunc)(void)){
	u8 Local_u8ErrorState=OK;
	if(USART_u8State==IDLE){
		if(Copy_pvNotifFunc!=NULL&&Copy_pchString!=NULL){
			USART_u8State=BUSY;
			USART_u8TransmissionState=STRING;
			USART_pchTransmittedString=Copy_pchString;
			UDRE_pvNotifFunc = Copy_pvNotifFunc;
			SET_BIT(UCSRB,UCSRB_UDRIE);
		}
		else{
			Local_u8ErrorState=NULL_POINTER;
		}
	}
	else{
		Local_u8ErrorState=BUSY_FUNC;
	}

	return Local_u8ErrorState;
}

u8 USART_u8ReceiveCharSynch(u16* Copy_pu16ReceivedData){
	u8 Local_u8ErrorState=OK;
	if(USART_u8State==IDLE){
		if(Copy_pu16ReceivedData!=NULL){
			USART_u8State=BUSY;
			u32 Local_u32Counter=0;
			while(GET_BIT(UCSRA,UCSRA_RXC)==0&&Local_u32Counter!=TIMEOUT){
				Local_u32Counter++;
			}
			if(Local_u32Counter==TIMEOUT){
				Local_u8ErrorState= FUNC_TIMEOUT;
			}
			else{
				*Copy_pu16ReceivedData=UDR;

				if(CHARACTER_SIZE==CHAR_9_BITS){
					if(GET_BIT(UCSRB,UCSRB_RXB8)==1){
						SET_BIT(*Copy_pu16ReceivedData,8);
					}
					else if(GET_BIT(UCSRB,UCSRB_RXB8)==0){
						CLR_BIT(*Copy_pu16ReceivedData,8);
					}
				}
			}
			USART_u8State=IDLE;
		}
		else{
			Local_u8ErrorState=NULL_POINTER;
		}
	}
	else{
		Local_u8ErrorState=BUSY_FUNC;
	}
	return Local_u8ErrorState;
}

u8 USART_u8ReceiveCharAsynch(u16* Copy_pu16ReceivedData,void (*Copy_pvNotifFunc)(void)){
	u8 Local_u8ErrorState=OK;
	if(USART_u8State==IDLE){
		if(Copy_pu16ReceivedData!=NULL && Copy_pvNotifFunc!=NULL){
			USART_u8State=BUSY;
			USART_u8TransmissionState=CHAR;
			RXC_pvNotifFunc=Copy_pvNotifFunc;
			USART_pu16ReceivedData = Copy_pu16ReceivedData;
			SET_BIT(UCSRB,UCSRB_RXCIE);
		}
		else{
			Local_u8ErrorState=NULL_POINTER;
		}
	}
	else{
		Local_u8ErrorState=BUSY_FUNC;
	}


	return Local_u8ErrorState;
}

u8 USART_u8ReceiveBufferSynch(u8* Copy_u8Buffer,u8 Copy_u8BufferSize){
	u8 Local_u8ErrorState=OK;
	if(USART_u8State==IDLE){
		if(Copy_u8Buffer!=NULL){
			u8 Local_u8Iterator;
			for(Local_u8Iterator=0;Local_u8Iterator<Copy_u8BufferSize;Local_u8Iterator++){
				USART_u8ReceiveCharSynch(&Copy_u8Buffer[Local_u8Iterator]);
			}
		}
		else{
			Local_u8ErrorState=NULL_POINTER;
		}
	}
	else{
		Local_u8ErrorState=BUSY_FUNC;
	}

	return Local_u8ErrorState;
}

u8 USART_u8ReceiveBufferAsynch(u8* Copy_u8Buffer,u8 Copy_u8BufferSize,void (*Copy_pvNotifFunc)(void)){
	u8 Local_u8ErrorState=OK;
	if(USART_u8State==IDLE){
		if(Copy_u8Buffer!=NULL && Copy_pvNotifFunc!=NULL){
			USART_u8State=BUSY;
			USART_u8TransmissionState=STRING;
			USART_pu8ReceivedBuffer=Copy_u8Buffer;
			USART_u8ReceivedBufferSize=Copy_u8BufferSize;
			RXC_pvNotifFunc=Copy_pvNotifFunc;
			SET_BIT(UCSRB,UCSRB_RXCIE);
		}
		else{
			Local_u8ErrorState=NULL_POINTER;
		}
	}
	else{
		Local_u8ErrorState=BUSY_FUNC;
	}

	return Local_u8ErrorState;
}

//RX Complete ISR
void __vector_13(void)  __attribute__((signal));
void __vector_13(void){
	if(USART_u8TransmissionState==CHAR){
		*USART_pu16ReceivedData = UDR;
		if(CHARACTER_SIZE==CHAR_9_BITS){
			if(GET_BIT(UCSRB,UCSRB_RXB8)==1){
				SET_BIT((*USART_pu16ReceivedData),8);
			}
			else if(GET_BIT(UCSRB,UCSRB_RXB8)==0){
				CLR_BIT((*USART_pu16ReceivedData),8);
			}
		}
		USART_u8State=IDLE;
		RXC_pvNotifFunc();
		CLR_BIT(UCSRB,UCSRB_RXCIE);
	}
	else if(USART_u8TransmissionState==STRING){
		static u8 Local_u8Counter=0;
		if(Local_u8Counter<USART_u8ReceivedBufferSize){
			USART_pu8ReceivedBuffer[Local_u8Counter++]=UDR;
			if(Local_u8Counter==USART_u8ReceivedBufferSize){
				USART_u8State=IDLE;
				Local_u8Counter=0;
				RXC_pvNotifFunc();
				CLR_BIT(UCSRB,UCSRB_RXCIE);
			}
		}

	}

}

//Data Register Empty ISR
void __vector_14(void)  __attribute__((signal));
void __vector_14(void){
	static u8 Local_u8Counter=0;
	if(USART_u8TransmissionState==CHAR){

		UDR=USART_u16TransmittedData;

		if(CHARACTER_SIZE==CHAR_9_BITS){
			if(GET_BIT(USART_u16TransmittedData,8)==1){
				SET_BIT(UCSRB,UCSRB_TXB8);
			}
			else if(GET_BIT(USART_u16TransmittedData,8)==0){
				CLR_BIT(UCSRB,UCSRB_TXB8);
			}
		}
		SET_BIT(UCSRB,UCSRB_TXCIE);
		CLR_BIT(UCSRB,UCSRB_UDRIE);
	}
	else if(USART_u8TransmissionState==STRING){
		if(USART_pchTransmittedString[Local_u8Counter]!='\0'){
			UDR=USART_pchTransmittedString[Local_u8Counter++];
		}
		else{
			USART_u8State=IDLE;
			Local_u8Counter=0;
			UDRE_pvNotifFunc();
			CLR_BIT(UCSRB,UCSRB_UDRIE);
		}
	}


}

//TX Complete ISR
void __vector_15(void)  __attribute__((signal));
void __vector_15(void){
	if(USART_u8TransmissionState==CHAR){
		USART_u8State=IDLE;
		TXC_pvNotifFunc();
		CLR_BIT(UCSRB,UCSRB_TXCIE);
	}
	else if(USART_u8TransmissionState==STRING){

	}

}


