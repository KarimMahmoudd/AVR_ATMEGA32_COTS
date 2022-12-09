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
static void (*TIMER0_pvScheduleFunc)(void)=NULL;
static u32 TIMER_u32ScheduleCompMatchCount;
static u8 TIMER_u8ScheduleRepeatability;


static void TIMER0_voidScheduleFunc(void){
	static u32 Local_u32Counter=0;
	Local_u32Counter++;
	if(Local_u32Counter==TIMER_u32ScheduleCompMatchCount){
		TIMER0_pvScheduleFunc();
		Local_u32Counter=0;
		if(TIMER_u8ScheduleRepeatability==REPEAT_ONCE){
			TIMER_u8SetIntStatus(INT_TIMER0_COMP,INT_DISABLE);
		}
		else if(TIMER_u8ScheduleRepeatability==REPEAT_PERIODIC){
			TIMER_u8SetIntStatus(INT_TIMER0_COMP,INT_ENABLE);
		}
	}
}

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


void TIMER0_voidSetIntStatus(u8 Copy_u8Status){

	if(Copy_u8Status==INT_ENABLE){
		SET_BIT(TIMSK,TIMSK_OCIE0 );
	}
	else if(Copy_u8Status==INT_DISABLE){
		
		CLR_BIT(TIMSK,TIMSK_OCIE0 );
	}
	
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

u8 TIMER0_u8Schedule(u16 Copy_u16msDelayTime,void(*Copy_pvFunc)(void),u8 Copy_u8Repeatability){
	u8 Local_u8ErrorState=OK; u16 Local_u16Counter=0;u32 Local_u32usTime,Local_u32CompMatchCount;
	if(Copy_pvFunc!=NULL){
		TIMER0_pvScheduleFunc=Copy_pvFunc;
		TIMER0_pvCallBackFunc= (&TIMER0_voidScheduleFunc);
		Local_u32usTime=(u32)Copy_u16msDelayTime*1000UL;
		Local_u32CompMatchCount=Local_u32usTime/TIMER0_COMP_MATCH_VAL;
		TIMER_u8ScheduleRepeatability=Copy_u8Repeatability;
		TIMER_u32ScheduleCompMatchCount=Local_u32CompMatchCount;

	}
	else{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
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

