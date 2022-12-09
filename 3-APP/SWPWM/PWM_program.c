/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: PWM                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MATH_HELPER.h"

#include "PWM_config.h"
#include "PWM_interface.h"
#include "PWM_private.h"
#include "PWM_register.h"

u8 PWM_voidGenerate(u8 Copy_u8DutyCycle){
	u8 Local_u8ErrorState=OK;
#if TIMER0_WAVE_GEN_MODE==PHASE_CORRECT_PWM
	CLR_BIT(TCCR0,TCCR0_WGM01);
	SET_BIT(TCCR0,TCCR0_WGM00);
#elif TIMER0_WAVE_GEN_MODE==FAST_PWM
	SET_BIT(TCCR0,TCCR0_WGM01);
	SET_BIT(TCCR0,TCCR0_WGM00);
#endif
	//Initialize Compare Match Output Mode
		TCCR0&=COMP_MATCH_OUT_MASK;
		TCCR0|=(TIMER0_PWM_MODE<<4);
	if(Copy_u8DutyCycle<=100){
		OCR0=MATH_s32Map(0,100,0,255,Copy_u8DutyCycle);
	}
	else{
		Local_u8ErrorState=NOK;
	}

	TCCR0&=PRESCALER_MASK;
	TCCR0|=TIMER0_CLOCK_TICK;

	return Local_u8ErrorState;

}
