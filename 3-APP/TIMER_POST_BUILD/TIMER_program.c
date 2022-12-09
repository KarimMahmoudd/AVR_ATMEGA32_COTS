/***************  **********************************************************************************************************/
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

static void (*TIMER0_pvOVFCallBackFunc)(void)=NULL;
static void (*TIMER0_pvCOMPCallBackFunc)(void)=NULL;
static void (*TIMER1_pvOVFCallBackFunc)(void)=NULL;
static void (*TIMER1_pvCAPTCallBackFunc)(void)=NULL;
static void (*TIMER1A_pvCOMPCallBackFunc)(void)=NULL;
static void (*TIMER1B_pvCOMPCallBackFunc)(void)=NULL;
static void (*TIMER2_pvOVFCallBackFunc)(void)=NULL;
static void (*TIMER2_pvCOMPCallBackFunc)(void)=NULL;


u8 TIMER_u8SetCompMatch(u8 Copy_u8TimerID,u16 Copy_u16Value){
	u8 Local_u8ErrorState=OK;
	switch(Copy_u8TimerID){
	case TIMER0  : if(Copy_u16Value<256){OCR0  = Copy_u16Value;} else{Local_u8ErrorState=NOK;} break;
	case TIMER1A : OCR1A = Copy_u16Value; break;
	case TIMER1B : OCR1B = Copy_u16Value; break;
	case TIMER2  : if(Copy_u16Value<256){OCR2  = Copy_u16Value;} else{Local_u8ErrorState=NOK;} break;
	default: Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

u8 TIMER_u8SetPreload(u8 Copy_u8TimerID,u16 Copy_u16Value){
	u8 Local_u8ErrorState=OK;
	switch(Copy_u8TimerID){
	case TIMER0  : if(Copy_u16Value<256){TCNT0  = Copy_u16Value;} else{Local_u8ErrorState=NOK;} break;
	case TIMER1A : TCNT1 = Copy_u16Value; break;
	case TIMER1B : TCNT1 = Copy_u16Value; break;
	case TIMER2  : if(Copy_u16Value<256){TCNT2  = Copy_u16Value;} else{Local_u8ErrorState=NOK;} break;
	default: Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}


/********************************************************TIMER0**********************************************************
 ************************************************************************************************************************/


u8 TIMER0_u8Init(Timer_t* Copy_psTimer){
	u8 Local_u8ErrorState=OK;
	//Initialize Wave Generation Mode
	if(Copy_psTimer!=NULL){
		if(Copy_psTimer->WaveGenMode==TIMER_NORMAL){
			CLR_BIT(TCCR0,TCCR0_WGM01);
			CLR_BIT(TCCR0,TCCR0_WGM00);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER_PHC_PWM){
			CLR_BIT(TCCR0,TCCR0_WGM01);
			SET_BIT(TCCR0,TCCR0_WGM00);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER_CTC){
			SET_BIT(TCCR0,TCCR0_WGM01);
			CLR_BIT(TCCR0,TCCR0_WGM00);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER_FAST_PWM){
			SET_BIT(TCCR0,TCCR0_WGM01);
			SET_BIT(TCCR0,TCCR0_WGM00);
		}
		else{
			Local_u8ErrorState=NOK;
		}
		//Initialize Compare Match Output Mode
		TCCR0&=COMP_MATCH_OUT_MASK;
		TCCR0|=((Copy_psTimer->CompareMatchOutputMode)<<4);
		//Initialize Interrupt Enable pins
		if(Copy_psTimer->CompareMatchInterrupt==INT_ENABLE){
			SET_BIT(TIMSK,TIMSK_OCIE0);
		}
		else if(Copy_psTimer->CompareMatchInterrupt==INT_DISABLE){
			CLR_BIT(TIMSK,TIMSK_OCIE0);
		}
		else{
			Local_u8ErrorState=NOK;
		}

		if(Copy_psTimer->OverFlowInterrupt==INT_ENABLE){
			SET_BIT(TIMSK,TIMSK_TOIE0);
		}
		else if(Copy_psTimer->OverFlowInterrupt==INT_DISABLE){
			CLR_BIT(TIMSK,TIMSK_TOIE0);
		}
		else{
			Local_u8ErrorState=NOK;
		}

		//Initialize Prescaler
		TCCR0&=PRESCALER_MASK;
		TCCR0|=Copy_psTimer->Prescaler;
	}
	else{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}





/************************************************************************************************************************
 ************************************************************************************************************************/


/********************************************************TIMER1**********************************************************
 ************************************************************************************************************************/


u8 TIMER1_u8Init(Timer1_t* Copy_psTimer){
	u8 Local_u8ErrorState=OK;
	if(Copy_psTimer!=NULL){
		//initialize wave generation mode
		if(Copy_psTimer->WaveGenMode==TIMER1_NORMAL){
			CLR_BIT(TCCR1B,TCCR1B_WGM13);
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER1_PHC_PWM_8_BIT){
			CLR_BIT(TCCR1B,TCCR1B_WGM13);
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);
			SET_BIT(TCCR1A,TCCR1A_WGM10);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER1_PHC_PWM_9_BIT){
			CLR_BIT(TCCR1B,TCCR1B_WGM13);
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER1_PHC_PWM_10_BIT){
			CLR_BIT(TCCR1B,TCCR1B_WGM13);
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			SET_BIT(TCCR1A,TCCR1A_WGM10);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER1_CTC){
			CLR_BIT(TCCR1B,TCCR1B_WGM13);
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER1_FAST_PWM_8_BIT){
			CLR_BIT(TCCR1B,TCCR1B_WGM13);
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);
			SET_BIT(TCCR1A,TCCR1A_WGM10);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER1_FAST_PWM_9_BIT){
			CLR_BIT(TCCR1B,TCCR1B_WGM13);
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER1_FAST_PWM_10_BIT){
			CLR_BIT(TCCR1B,TCCR1B_WGM13);
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			SET_BIT(TCCR1A,TCCR1A_WGM10);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER1_PHFC_PWM_CUSTOM_TOP){
			SET_BIT(TCCR1B,TCCR1B_WGM13);
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER1_PHFC_PWM){
			SET_BIT(TCCR1B,TCCR1B_WGM13);
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);
			SET_BIT(TCCR1A,TCCR1A_WGM10);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER1_PHC_PWM_CUSTOM_TOP){
			SET_BIT(TCCR1B,TCCR1B_WGM13);
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER1_PHC_PWM){
			SET_BIT(TCCR1B,TCCR1B_WGM13);
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			SET_BIT(TCCR1A,TCCR1A_WGM10);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER1_CTC_CUSTOM_TOP){
			SET_BIT(TCCR1B,TCCR1B_WGM13);
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER1_FAST_PWM_CUSTOM_TOP){
			SET_BIT(TCCR1B,TCCR1B_WGM13);
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER1_FAST_PWM){
			SET_BIT(TCCR1B,TCCR1B_WGM13);
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			SET_BIT(TCCR1A,TCCR1A_WGM10);
		}
		else{
			Local_u8ErrorState=NOK;
		}
		//Set Match Compare Output Mode for both channel A and B
		TCCR1A&=T1_COMP_MATCH_OUT_MASK;
		TCCR1A|=((Copy_psTimer->CompareMatchOutputMode_B)<<4);
		TCCR1A|=((Copy_psTimer->CompareMatchOutputMode_A)<<6);
		//Initialize Interrupt Enable pins
		if(Copy_psTimer->CompareMatchInterrupt_A==INT_ENABLE){
			SET_BIT(TIMSK,TIMSK_OCIE1A);
		}
		else if(Copy_psTimer->CompareMatchInterrupt_A==INT_DISABLE){
			CLR_BIT(TIMSK,TIMSK_OCIE1A);
		}
		else{
			Local_u8ErrorState=NOK;
		}

		if(Copy_psTimer->CompareMatchInterrupt_B==INT_ENABLE){
			SET_BIT(TIMSK,TIMSK_OCIE1B);
		}
		else if(Copy_psTimer->CompareMatchInterrupt_B==INT_DISABLE){
			CLR_BIT(TIMSK,TIMSK_OCIE1B);
		}
		else{
			Local_u8ErrorState=NOK;
		}


		if(Copy_psTimer->OverFlowInterrupt==INT_ENABLE){
			SET_BIT(TIMSK,TIMSK_TOIE1);
		}
		else if(Copy_psTimer->OverFlowInterrupt==INT_DISABLE){
			CLR_BIT(TIMSK,TIMSK_TOIE1);
		}
		else{
			Local_u8ErrorState=NOK;
		}

		if(Copy_psTimer->InputCapInterrupt==INT_ENABLE){
			SET_BIT(TIMSK,TIMSK_TICIE1);
		}
		else if(Copy_psTimer->InputCapInterrupt==INT_DISABLE){
			CLR_BIT(TIMSK,TIMSK_TICIE1);
		}
		else{
			Local_u8ErrorState=NOK;
		}

		//Initialize Prescaler
		TCCR1B&=PRESCALER_MASK;
		TCCR1B|=Copy_psTimer->Prescaler;
	}
	else{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;

}


void TIMER1_voidSetTopValue(u16 Copy_u16Value){
	ICR1=Copy_u16Value;
}

u8 TIMER_u8PWMGenerate(Timer1_t* Copy_psTimer,u8 Copy_u8ChannelID,u16 Copy_u16PeriodTime,u16 Copy_u16OnTime){
	u8 Local_u8ErrorState=OK;
	if(Copy_psTimer!=NULL){
		if((Copy_psTimer->WaveGenMode)==TIMER1_FAST_PWM_CUSTOM_TOP){

			switch(Copy_psTimer->Prescaler){
			case TIMER_DIV_BY_1    : ICR1 = Copy_u16PeriodTime*8   ; break;
			case TIMER_DIV_BY_8    : ICR1 = Copy_u16PeriodTime     ; break;
			case TIMER_DIV_BY_64   : ICR1 = Copy_u16PeriodTime/8   ; break;
			case TIMER_DIV_BY_256  : ICR1 = Copy_u16PeriodTime/32  ; break;
			case TIMER_DIV_BY_1024 : ICR1 = Copy_u16PeriodTime/128 ; break;
			default: Local_u8ErrorState=NOK;
			}

			if(Copy_u16OnTime<=Copy_u16PeriodTime){
				if(Copy_u8ChannelID==CHANNEL_A){
					OCR1A=Copy_u16OnTime;
				}
				else if(Copy_u8ChannelID==CHANNEL_B){
					OCR1B=Copy_u16OnTime;
				}
				else{
					Local_u8ErrorState=NOK;
				}
			}
			else{
				Local_u8ErrorState=NOK;

			}
		}
		else{
			Local_u8ErrorState=NOK;
		}
	}
	else{
		Local_u8ErrorState=NULL_POINTER;
	}


	return Local_u8ErrorState;

}

/************************************************************************************************************************
 ************************************************************************************************************************/




/********************************************************TIMER2**********************************************************
 ************************************************************************************************************************/

u8 TIMER2_u8Init(Timer_t* Copy_psTimer){
	u8 Local_u8ErrorState=OK;
	//Initialize Wave Generation Mode
	if(Copy_psTimer!=NULL){
		if(Copy_psTimer->WaveGenMode==TIMER_NORMAL){
			CLR_BIT(TCCR2,TCCR2_WGM21);
			CLR_BIT(TCCR2,TCCR2_WGM20);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER_PHC_PWM){
			CLR_BIT(TCCR2,TCCR2_WGM21);
			SET_BIT(TCCR2,TCCR2_WGM20);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER_CTC){
			SET_BIT(TCCR2,TCCR2_WGM21);
			CLR_BIT(TCCR2,TCCR2_WGM20);
		}
		else if(Copy_psTimer->WaveGenMode==TIMER_FAST_PWM){
			SET_BIT(TCCR2,TCCR2_WGM21);
			SET_BIT(TCCR2,TCCR2_WGM20);
		}
		else{
			Local_u8ErrorState=NOK;
		}
		//Initialize Compare Match Output Mode
		TCCR2&=COMP_MATCH_OUT_MASK;
		TCCR2|=((Copy_psTimer->CompareMatchOutputMode)<<4);
		//Initialize Interrupt Enable pins
		if(Copy_psTimer->CompareMatchInterrupt==INT_ENABLE){
			SET_BIT(TIMSK,TIMSK_OCIE2);
		}
		else if(Copy_psTimer->CompareMatchInterrupt==INT_DISABLE){
			CLR_BIT(TIMSK,TIMSK_OCIE2);
		}
		else{
			Local_u8ErrorState=NOK;
		}

		if(Copy_psTimer->OverFlowInterrupt==INT_ENABLE){
			SET_BIT(TIMSK,TIMSK_TOIE2);
		}
		else if(Copy_psTimer->OverFlowInterrupt==INT_DISABLE){
			CLR_BIT(TIMSK,TIMSK_TOIE2);
		}
		else{
			Local_u8ErrorState=NOK;
		}

		//Initialize Prescaler
		TCCR2&=PRESCALER_MASK;
		TCCR2|=Copy_psTimer->Prescaler;
	}
	else{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}

u8 TIMER2_delay_ms(Timer_t* Copy_psTimer,u16 Copy_u16Time){
	u8 Local_u8ErrorState=OK,Local_u8Break=1; u16 Local_u16Counter=0;u32 Local_u32usTime,Local_u32CompMatchCount;
	if(Copy_psTimer!=NULL){
		Timer_t Timer ={TIMER_CTC,TIMER_DIV_BY_8,TIMER_DISCONNECT,INT_DISABLE,INT_DISABLE};
		TIMER2_u8Init(&Timer);
		TIMER_u8SetCompMatch(TIMER2,250);
		Local_u32usTime=(u32)Copy_u16Time*1000UL;
		Local_u32CompMatchCount=Local_u32usTime/250;
		while(Local_u8Break==1){
			if(GET_BIT(TIFR,TIFR_OCF2)==1){
				if(Local_u16Counter==Local_u32CompMatchCount){
					Local_u8Break=0;
					SET_BIT(TIFR,TIFR_OCF2);
				}
				else{
					Local_u16Counter++;
					SET_BIT(TIFR,TIFR_OCF2);
				}
			}
		}
		TIMER2_u8Init(Copy_psTimer);

	}
	else{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}

u8 TIMER2_delay_us(Timer_t* Copy_psTimer,u16 Copy_u16Time){
	u8 Local_u8ErrorState=OK,Local_u8Break=1,Local_u8CompMatch; u16 Local_u16Counter=0;u32 Local_u32usTime,Local_u32CompMatchCount;
	if(Copy_psTimer!=NULL){
		Timer_t Timer ={TIMER_CTC,TIMER_DIV_BY_8,TIMER_DISCONNECT,INT_DISABLE,INT_DISABLE};
		TIMER2_u8Init(&Timer);
		for(Local_u8CompMatch=255;Local_u8CompMatch>0;Local_u8CompMatch--){
			if(Copy_u16Time%Local_u8CompMatch==0){
				break;
			}
		}
		TIMER_u8SetCompMatch(TIMER2,Local_u8CompMatch);
		Local_u32CompMatchCount=Local_u32usTime/Local_u8CompMatch;
		while(Local_u8Break==1){
			if(GET_BIT(TIFR,TIFR_OCF2)==1){
				if(Local_u16Counter==Local_u32CompMatchCount){
					Local_u8Break=0;
					SET_BIT(TIFR,TIFR_OCF2);
				}
				else{
					Local_u16Counter++;
					SET_BIT(TIFR,TIFR_OCF2);
				}
			}
		}
		TIMER2_u8Init(Copy_psTimer);

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

u8 TIMER_u8SetCallBack(u8 Copy_u8InterruptID,void(*Copy_pvCallBackFunc)(void)){
	u8 Local_u8ErrorState=OK;
	if(Copy_pvCallBackFunc!=NULL){
		switch(Copy_u8InterruptID){
		case TIMER0_OVF  : TIMER0_pvOVFCallBackFunc   = Copy_pvCallBackFunc; break;
		case TIMER0_COMP : TIMER0_pvCOMPCallBackFunc  = Copy_pvCallBackFunc; break;
		case TIMER1_OVF  : TIMER1_pvOVFCallBackFunc   = Copy_pvCallBackFunc; break;
		case TIMER1_CAPT : TIMER1_pvCAPTCallBackFunc  = Copy_pvCallBackFunc; break;
		case TIMER1A_COMP: TIMER1A_pvCOMPCallBackFunc = Copy_pvCallBackFunc; break;
		case TIMER1B_COMP: TIMER1B_pvCOMPCallBackFunc = Copy_pvCallBackFunc; break;
		case TIMER2_OVF	 : TIMER2_pvOVFCallBackFunc   = Copy_pvCallBackFunc; break;
		case TIMER2_COMP : TIMER2_pvCOMPCallBackFunc  = Copy_pvCallBackFunc; break;
		default: Local_u8ErrorState=NOK;
		}
	}
	else{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}




//TIMER2 Compare Match ISR
void __vector_4(void)  __attribute__((signal));
void __vector_4(void){
	if(TIMER2_pvCOMPCallBackFunc!=NULL){
		TIMER2_pvCOMPCallBackFunc();
	}
}

//TIMER2 Overflow ISR
void __vector_5(void)  __attribute__((signal));
void __vector_5(void){
	if(TIMER2_pvOVFCallBackFunc!=NULL){
		TIMER2_pvOVFCallBackFunc();
	}
}

//TIMER1 Capture Event ISR
void __vector_6(void)  __attribute__((signal));
void __vector_6(void){
	if(TIMER1_pvCAPTCallBackFunc!=NULL){
		TIMER1_pvCAPTCallBackFunc();
	}
}


//TIMER1 Compare Match A ISR
void __vector_7(void)  __attribute__((signal));
void __vector_7(void){
	if(TIMER1A_pvCOMPCallBackFunc!=NULL){
		TIMER1A_pvCOMPCallBackFunc();
	}
}

//TIMER1 Compare Match B ISR
void __vector_8(void)  __attribute__((signal));
void __vector_8(void){
	if(TIMER1B_pvCOMPCallBackFunc!=NULL){
		TIMER1B_pvCOMPCallBackFunc();
	}
}

//TIMER1 Overflow ISR
void __vector_9(void)  __attribute__((signal));
void __vector_9(void){
	if(TIMER1_pvOVFCallBackFunc!=NULL){
		TIMER1_pvOVFCallBackFunc();
	}
}

//TIMER0 Compare Match ISR
void __vector_10(void)  __attribute__((signal));
void __vector_10(void){
	if(TIMER0_pvCOMPCallBackFunc!=NULL){
		TIMER0_pvCOMPCallBackFunc();
	}
}

//TIMER0 Overflow ISR
void __vector_11(void)  __attribute__((signal));
void __vector_11(void){
	if(TIMER0_pvOVFCallBackFunc!=NULL){
		TIMER0_pvOVFCallBackFunc();
	}
}

