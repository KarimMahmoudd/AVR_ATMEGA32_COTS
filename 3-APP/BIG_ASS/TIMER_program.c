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
static void (*TIMER2_pvCallBackFunc)(void)=NULL;
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

	//Initialize Prescaler
	TCCR0&=PRESCALER_MASK;
	TCCR0|=TIMER0_PRESCALER;
}

void TIMER0_voidSetCompMatchValue(u8 Copy_u8Value){
	OCR0=Copy_u8Value;
}

void TIMER0_voidSetPreloadValue(u8 Copy_u8Value){
	TCNT0=Copy_u8Value;
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

u8 TIMER0_voidPWMGenerate(u8 Copy_u8DutyCycle){
	u8 Local_u8ErrorState=OK;
	if(TIMER0_GEN_MODE==PHC_PWM||TIMER0_GEN_MODE==FAST_PWM){
		if(Copy_u8DutyCycle<=100){
			OCR0=MATH_s32Map(0,100,0,255,Copy_u8DutyCycle);
		}
		else{
			Local_u8ErrorState=NOK;

	}
}
	else{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;

}


/************************************************************************************************************************
 ************************************************************************************************************************/


/********************************************************TIMER1**********************************************************
 ************************************************************************************************************************/


void TIMER1_voidInit(void){
	//initialize wave generation mode
#if TIMER1_GEN_MODE==T1_NORMAL
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
#elif TIMER1_GEN_MODE==T1_PHC_PWM_8_BIT
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1A,TCCR1A_WGM10);
#elif TIMER1_GEN_MODE==T1_PHC_PWM_9_BIT
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
#elif TIMER1_GEN_MODE==T1_PHC_PWM_10_BIT
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1A,TCCR1A_WGM10);
#elif TIMER1_GEN_MODE==T1_CTC
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
#elif TIMER1_GEN_MODE==T1_FAST_PWM_8_BIT
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1A,TCCR1A_WGM10);
#elif TIMER1_GEN_MODE==T1_FAST_PWM_9_BIT
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
#elif TIMER1_GEN_MODE==T1_FAST_PWM_10_BIT
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1A,TCCR1A_WGM10);
#elif TIMER1_GEN_MODE==T1_PHFC_PWM_CUSTOM_TOP
	SET_BIT(TCCR1B,TCCR1B_WGM13);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
#elif TIMER1_GEN_MODE==T1_PHFC_PWM
	SET_BIT(TCCR1B,TCCR1B_WGM13);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1A,TCCR1A_WGM10);
#elif TIMER1_GEN_MODE==T1_PHC_PWM_CUSTOM_TOP
	SET_BIT(TCCR1B,TCCR1B_WGM13);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
#elif TIMER1_GEN_MODE==T1_PHC_PWM
	SET_BIT(TCCR1B,TCCR1B_WGM13);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1A,TCCR1A_WGM10);
#elif TIMER1_GEN_MODE==T1_CTC_CUSTOM_TOP
	SET_BIT(TCCR1B,TCCR1B_WGM13);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
#elif TIMER1_GEN_MODE==T1_FAST_PWM_CUSTOM_TOP
	SET_BIT(TCCR1B,TCCR1B_WGM13);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
#elif TIMER1_GEN_MODE==T1_FAST_PWM
	SET_BIT(TCCR1B,TCCR1B_WGM13);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1A,TCCR1A_WGM10);
#endif
	//Set Match Compare Output Mode for both channel A and B
	TCCR1A&=T1_COMP_MATCH_OUT_MASK;
	TCCR1A|=(TIMER1B_COMP_MATCH_OUTPUT_MODE<<4);
	TCCR1A|=(TIMER1A_COMP_MATCH_OUTPUT_MODE<<6);
	//Settine interrupts
#if TIMER1A_COMP_MATCH_INT==ENABLE
	SET_BIT(TIMSK,TIMSK_OCIE1A);
#elif TIMER1A_COMP_MATCH_INT==DISABLE
	CLR_BIT(TIMSK,TIMSK_OCIE1A);
#endif

#if TIMER1B_COMP_MATCH_INT==ENABLE
	SET_BIT(TIMSK,TIMSK_OCIE1B);
#elif TIMER1B_COMP_MATCH_INT==DISABLE
	CLR_BIT(TIMSK,TIMSK_OCIE1B);
#endif

#if TIMER1_OVERFLOW_INT==ENABLE
	SET_BIT(TIMSK,TIMSK_TOIE1);
#elif TIMER1_OVERFLOW_INT==DISABLE
	CLR_BIT(TIMSK,TIMSK_TOIE1);
#endif

	//Set Prescaler
	TCCR1B&=PRESCALER_MASK;
	TCCR1B|=TIMER1_PRESCALER;

}

void TIMER1A_voidSetCompMatchValue(u16 Copy_u16Value){
	OCR1A=Copy_u16Value;
}

void TIMER1B_voidSetCompMatchValue(u16 Copy_u16Value){
	OCR1B=Copy_u16Value;
}

void TIMER1_voidSetTopValue(u16 Copy_u16Value){
	ICR1=Copy_u16Value;
}


/************************************************************************************************************************
 ************************************************************************************************************************/




/********************************************************TIMER2**********************************************************
 ************************************************************************************************************************/


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

	//Initialize Prescaler
	TCCR2&=PRESCALER_MASK;
	TCCR2|=TIMER2_PRESCALER;
}

void TIMER2_voidSetCompMatchValue(u8 Copy_u8Value){
	OCR2=Copy_u8Value;
}

void TIMER2_voidSetPreloadValue(u8 Copy_u8Value){
	TCNT2=Copy_u8Value;
}

u8 TIMER2_u8SetCallBack(void(*Copy_pvCallBackFunc)(void)){
	u8 Local_u8ErrorState=OK;
	if(Copy_pvCallBackFunc!=NULL){
		TIMER2_pvCallBackFunc=Copy_pvCallBackFunc;
	}
	else{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}


/************************************************************************************************************************
 ************************************************************************************************************************/









//TIMER2 Compare Match ISR
void __vector_4(void)  __attribute__((signal));
void __vector_4(void){
	if(TIMER2_pvCallBackFunc!=NULL){
		TIMER2_pvCallBackFunc();
	}
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

