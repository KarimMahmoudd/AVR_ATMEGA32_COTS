/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: RTOS Stack                ***********************************************/
/******************************           SWC: TIMER0                      ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER0_register.h"
#include "TIMER0_interface.h"
#include "TIMER0_private.h"
#include "TIMER0_config.h"

static void (*TIMER0_pvCallBackFunc)(void)= {NULL};



/********************************************************GENERAL TIMER FUNCTIONS*****************************************
 ************************************************************************************************************************/

void TIMER0_voidSetTimerVal(u8 Copy_u8Value){
	TCNT0  = Copy_u8Value;
}


u8 TIMER0_u8GetTimerVal(void){
	return TCNT0;
}


void TIMER0_voidSetCompMatch(u8 Copy_u8Value){
	OCR0  = Copy_u8Value;
	
}




/********************************************************TIMER0**********************************************************
 ************************************************************************************************************************/


void TIMER0_voidInit(void){

	//Initialize Wave Generation Mode
#if TIMER0_GEN_MODE==NORMAL
	CLR_BIT(TCCR0,TCCR0_WGM01);
	CLR_BIT(TCCR0,TCCR0_WGM00);
#elif TIMER0_GEN_MODE==PWM
	CLR_BIT(TCCR0,TCCR0_WGM01);
	SET_BIT(TCCR0,TCCR0_WGM00);
#elif TIMER0_GEN_MODE==CTC
	SET_BIT(TCCR0,TCCR0_WGM01);
	CLR_BIT(TCCR0,TCCR0_WGM00);
#elif TIMER0_GEN_MODE==FAST_PWM
	SET_BIT(TCCR0,TCCR0_WGM01);
	SET_BIT(TCCR0,TCCR0_WGM00);
#endif

	//Initialize Interrupt Enable pins
#if TIMER0_COMP_MATCH_INT==ENABLE
	SET_BIT(TIMSK,TIMSK_OCIE0);
#elif TIMER0_COMP_MATCH_INT==DISABLE
	CLR_BIT(TIMSK,TIMSK_OCIE0);
#endif
	OCR0  = TIMER0_COMP_MATCH_VAL;

	//Initialize Prescaler
	TCCR0&=PRESCALER_MASK;
	TCCR0|=TIMER0_PRESCALER;
}




/************************************************************************************************************************
 ************************************************************************************************************************/



/********************************************************ISRs************************************************************
 ************************************************************************************************************************/


u8 TIMER0_u8SetCallBack(void(*Copy_pvCallBackFunc)(void)){
	u8 Local_u8ErrorState=OK;
	if(Copy_pvCallBackFunc!=NULL){
		TIMER0_pvCallBackFunc=Copy_pvCallBackFunc;
	}
	else{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}

//TIMER0 Compare Match ISR
void __vector_10(void)  __attribute__((signal));
void __vector_10(void){
	if(TIMER0_pvCallBackFunc!=NULL){
		TIMER0_pvCallBackFunc();
	}
}


/************************************************************************************************************************
 ************************************************************************************************************************/

