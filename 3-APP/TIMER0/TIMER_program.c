/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: TIMER                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_register.h"
#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_config.h"

static void (*TIMER0_pvCallBackFunc)(void)=NULL;

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

	//Initialize Compare Match Output Mode
	TCCR0&=COMP_MATCH_OUT_MASK;
	TCCR0|=(TIMER0_COMP_MATCH_OUTPUT_MODE<<4);

	//Initialize Interrupt Enable pins
#if TIMER0_COMP_MATCH_INT==ENABLE
	SET_BIT(TIMSK,TIMSK_OCIE0);
#elif TIMER0_COMP_MATCH_INT==DISABLE
	CLR_BIT(TIMSK,TIMSK_OCIE0);
#endif

#if TIMER0_OVERFLOW_INT==ENABLE
	SET_BIT(TIMSK,TIMSK_TOIE0);
#elif TIMER0_OVERFLOW_INT==DISABLE
	CLR_BIT(TIMSK,TIMSK_TOIE0);
#endif
	//Initialize Compare Match Value
	OCR0=TIMER0_COMP_MATCH_VAL;
	//Initialize Preload Value
	TCNT0=TIMER0_PRELOAD_VAL;
	//Initialize Prescaler
	TCCR0&=PRESCALER_MASK;
	TCCR0|=TIMER0_PRESCALER;
}

void TIMER2_voidInit(void){

	//Initialize Wave Generation Mode
#if TIMER2_GEN_MODE==NORMAL
	CLR_BIT(TCCR2,TCCR2_WGM21);
	CLR_BIT(TCCR2,TCCR2_WGM20);
#elif TIMER2_GEN_MODE==PWM
	CLR_BIT(TCCR2,TCCR2_WGM21);
	SET_BIT(TCCR2,TCCR2_WGM20);
#elif TIMER2_GEN_MODE==CTC
	SET_BIT(TCCR2,TCCR2_WGM21);
	CLR_BIT(TCCR2,TCCR2_WGM20);
#elif TIMER2_GEN_MODE==FAST_PWM
	SET_BIT(TCCR2,TCCR2_WGM21);
	SET_BIT(TCCR2,TCCR2_WGM20);
#endif

	//Initialize Compare Match Output Mode
	TCCR2&=COMP_MATCH_OUT_MASK;
	TCCR2|=(TIMER2_COMP_MATCH_OUTPUT_MODE<<4);

	//Initialize Interrupt Enable pins
#if TIMER2_COMP_MATCH_INT==ENABLE
	SET_BIT(TIMSK,TIMSK_OCIE2);
#elif TIMER2_COMP_MATCH_INT==DISABLE
	CLR_BIT(TIMSK,TIMSK_OCIE2);
#endif

#if TIMER2_OVERFLOW_INT==ENABLE
	SET_BIT(TIMSK,TIMSK_TOIE2);
#elif TIMER0_OVERFLOW_INT==DISABLE
	CLR_BIT(TIMSK,TIMSK_TOIE2);
#endif

	//Initialize Compare Match Value
	OCR2=TIMER2_COMP_MATCH_VAL;

	//Initialize Preload Value
	TCNT2=TIMER2_PRELOAD_VAL;

	//Initialize Prescaler
	TCCR2&=PRESCALER_MASK;
	TCCR2|=TIMER2_PRESCALER;
}

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

//TIMER2 Compare Match ISR
void __vector_4(void)  __attribute__((signal));
void __vector_4(void){

}

//TIMER2 Overflow ISR
void __vector_5(void)  __attribute__((signal));
void __vector_5(void){

}

//TIMER1 Capture Event ISR
void __vector_6(void)  __attribute__((signal));
void __vector_6(void){

}


//TIMER1 Compare Match A ISR
void __vector_7(void)  __attribute__((signal));
void __vector_7(void){

}

//TIMER1 Compare Match B ISR
void __vector_8(void)  __attribute__((signal));
void __vector_8(void){

}

//TIMER1 Overflow ISR
void __vector_9(void)  __attribute__((signal));
void __vector_9(void){

}

//TIMER0 Compare Match ISR
void __vector_10(void)  __attribute__((signal));
void __vector_10(void){
	if(TIMER0_pvCallBackFunc!=NULL){
		TIMER0_pvCallBackFunc();
	}
}

//TIMER0 Overflow ISR
void __vector_11(void)  __attribute__((signal));
void __vector_11(void){

}

