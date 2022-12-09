/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: SPI                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_config.h"
#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_register.h"

static u8* SPI_pu8ReceivedData=NULL;
static void (*SPI_voidNotifFunc)(void);
static u8 SPI_u8STATUS=IDLE;
void SPI_voidMasterInit(void){

	//Set to Master
	SET_BIT(SPCR,SPCR_MSTR);

	//Set Interrupt
#if SPI_INTERRUPT == DISABLE
	CLR_BIT(SPCR,SPCR_SPIE);
#elif SPI_INTERRUPT == ENABLE
	SET_BIT(SPCR,SPCR_SPIE);
#else
#error "WRONG INTERRUPT CONFIGURATION"
#endif

	//Set Data Order
#if DATA_ORDER == MSB
	CLR_BIT(SPCR,SPCR_DORD);
#elif DATA_ORDER == LSB
	SET_BIT(SPCR,SPCR_DORD);
#else
#error "WRONG DATA ORDER CONFIGURATION"
#endif

	//Set Clock Polarity
#if LEADING_EDGE == RISING
	CLR_BIT(SPCR,SPCR_CPOL);
#elif LEADING_EDGE == FALLING
	SET_BIT(SPCR,SPCR_CPOL);
#else
#error "WRONG CLOCK POLARITY CONFIGURATION"
#endif

	//Set Clock Phase
#if LEADING_EDGE_ACTION == SETUP
	CLR_BIT(SPCR,SPCR_CPHA);
#elif LEADING_EDGE_ACTION == SAMPLE
	SET_BIT(SPCR,SPCR_CPHA);
#else
#error "WRONG CLOCK PHASE CONFIGURATION"
#endif

	//Set Clock Prescaler
#if PRESCALER == DIV_BY_2
	SET_BIT(SPSR,SPSR_SPI2X);
	CLR_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPCR,SPCR_SPR0);
#elif PRESCALER ==DIV_BY_4
	CLR_BIT(SPSR,SPSR_SPI2X);
	CLR_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPCR,SPCR_SPR0);
#elif PRESCALER ==DIV_BY_8
	SET_BIT(SPSR,SPSR_SPI2X);
	CLR_BIT(SPCR,SPCR_SPR1);
	SET_BIT(SPCR,SPCR_SPR0);
#elif PRESCALER ==DIV_BY_16
	CLR_BIT(SPSR,SPSR_SPI2X);
	CLR_BIT(SPCR,SPCR_SPR1);
	SET_BIT(SPCR,SPCR_SPR0);
#elif PRESCALER ==DIV_BY_32
	SET_BIT(SPSR,SPSR_SPI2X);
	SET_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPCR,SPCR_SPR0);
#elif PRESCALER ==DIV_BY_64
	CLR_BIT(SPSR,SPSR_SPI2X);
	SET_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPCR,SPCR_SPR0);
#elif PRESCALER ==DIV_BY_128
	CLR_BIT(SPSR,SPSR_SPI2X);
	SET_BIT(SPCR,SPCR_SPR1);
	SET_BIT(SPCR,SPCR_SPR0);
#else
#error "WRONG PRESCALER CONFIGURATION"
#endif

	//ENABLE SPI
#if SPI_ENABLE == DISABLE
	CLR_BIT(SPCR,SPCR_SPE);
#elif SPI_ENABLE == ENABLE
	SET_BIT(SPCR,SPCR_SPE);
#else
#error "WRONG SPI CONFIGURATION"
#endif

}
void SPI_voidSlaveInit(void){
	//Set to Slave
	CLR_BIT(SPCR,SPCR_MSTR);

	//Set Interrupt
#if SPI_INTERRUPT == DISABLE
	CLR_BIT(SPCR,SPCR_SPIE);
#elif SPI_INTERRUPT == ENABLE
	SET_BIT(SPCR,SPCR_SPIE);
#else
#error "WRONG INTERRUPT CONFIGURATION"
#endif

	//Set Data Order
#if DATA_ORDER == MSB
	CLR_BIT(SPCR,SPCR_DORD);
#elif DATA_ORDER == LSB
	SET_BIT(SPCR,SPCR_DORD);
#else
#error "WRONG DATA ORDER CONFIGURATION"
#endif

	//Set Clock Polarity
#if LEADING_EDGE == RISING
	CLR_BIT(SPCR,SPCR_CPOL);
#elif LEADING_EDGE == FALLING
	SET_BIT(SPCR,SPCR_CPOL);
#else
#error "WRONG CLOCK POLARITY CONFIGURATION"
#endif

	//Set Clock Phase
#if LEADING_EDGE_ACTION == SETUP
	CLR_BIT(SPCR,SPCR_CPHA);
#elif LEADING_EDGE_ACTION == SAMPLE
	SET_BIT(SPCR,SPCR_CPHA);
#else
#error "WRONG CLOCK PHASE CONFIGURATION"
#endif

	//ENABLE SPI
#if SPI_ENABLE == DISABLE
	CLR_BIT(SPCR,SPCR_SPE);
#elif SPI_ENABLE == ENABLE
	SET_BIT(SPCR,SPCR_SPE);
#else
#error "WRONG SPI CONFIGURATION"
#endif

}


u8 SPI_u8SynchTranscieve(u8 Copy_u8Data,u8* Copy_pu8ReceivedData){
	u8 Local_u8ErrorState=OK;
	if(Copy_pu8ReceivedData!=NULL){
		u32 Local_u32Counter=0;
		SPDR = Copy_u8Data;
		while (GET_BIT(SPSR,SPSR_SPIF)==0&&Local_u32Counter!=TIMEOUT){
			Local_u32Counter++;
		}
		if(Local_u32Counter==TIMEOUT){
			Local_u8ErrorState=NOK;
		}
		else{
			*Copy_pu8ReceivedData = SPDR;
		}

	}
	else{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}

u8 SPI_u8AsynchTranscieve(u8 Copy_u8Data,u8* Copy_pu8ReceivedData, void (*Copy_pvNotifFunc)(void)){
	u8 Local_u8ErrorState=OK;
	if(SPI_u8STATUS==IDLE){
		if(Copy_pu8ReceivedData!=NULL){
			SPI_u8STATUS=BUSY;
			SPI_pu8ReceivedData=Copy_pu8ReceivedData;
			SPI_voidNotifFunc=Copy_pvNotifFunc;
			SET_BIT(SPCR,SPCR_SPIE);
			SPDR = Copy_u8Data;

		}
		else{
			Local_u8ErrorState=NULL_POINTER;
		}
	}
	else if(SPI_u8STATUS==BUSY){
		Local_u8ErrorState=BUSY_FUNC;
	}


	return Local_u8ErrorState;


}

void __vector_12 (void)  __attribute__((signal));
void __vector_12 (void){

	*SPI_pu8ReceivedData=SPDR;
	SPI_voidNotifFunc();
	CLR_BIT(SPCR,SPCR_SPIE);
	SPI_u8STATUS=IDLE;
}
