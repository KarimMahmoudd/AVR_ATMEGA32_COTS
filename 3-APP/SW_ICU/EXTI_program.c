/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: EXTI                        ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"
#include "EXTI_register.h"

/*Global Pointer to Function to hold INT0,INT2,INT3 ISR addresses*/
void (*EXTI_pvInt0Func)(void)=NULL;
void (*EXTI_pvInt1Func)(void)=NULL;
void (*EXTI_pvInt2Func)(void)=NULL;

void EXTI_voidInt0Init(void){
	// Set sense control for int0
#if INT0_SENSE==LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SENSE==ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SENSE==FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SENSE==RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#else

#error "Wrong INT0_SENSE configuration option"

#endif
	//peripheral interrupt enable
#if INT0_INITIAL_STATE==ENABLED
	SET_BIT(GICR,GICR_INT0);
#elif INT0_INITIAL_STATE==DISABLED
	CLR_BIT(GICR,GICR_INT0);
#else
#error "Wrong INT0_INITIAL_STATE configuration option"
#endif
}

void EXTI_voidInt1Init(void){

	// Check and set sense control for int0
#if INT1_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);
#elif INT1_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);
#elif INT1_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
#elif INT1_SENSE == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#endif
	//peripheral interrupt enable
#if INT1_INITIAL_STATE==ENABLED
	SET_BIT(GICR,GICR_INT1);
#elif INT1_INITIAL_STATE==DISABLED
	CLR_BIT(GICR,GICR_INT1);
#else
#error "Wrong INT1_INITIAL_STATE configuration option"

#endif
}

void EXTI_voidInt2Init(void){

	// Set sense control for int0

#if INT2_SENSE == FALLING_EDGE
	CLR_BIT(MCUCSR,MCUCSR_INT2);
#elif INT2_SENSE == RISING_EDGE
	SET_BIT(MCUCSR,MCUCSR_INT2);
#endif
#if INT0_INITIAL_STATE==ENABLED
	SET_BIT(GICR,GICR_INT2);
#elif INT0_INITIAL_STATE==DISABLED
	CLR_BIT(GICR,GICR_INT2);
#else
#error "Wrong INT2_INITIAL_STATE configuration option"
#endif
}

u8 EXTI_u8SetSenseControl(u8 Copy_u8Interrupt, u8 Copy_u8Sense){
	u8 Local_u8ErrorState = OK;
	if(Copy_u8Interrupt==EXTI_INT0){
		switch (Copy_u8Sense){
		case EXTI_LOW_LEVEL:
			CLR_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);
			break;
		case EXTI_ON_CHANGE:
			SET_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);
			break;
		case EXTI_FALLING_EDGE:
			CLR_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
			break;
		case EXTI_RISING_EDGE:
			SET_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
			break;
		default: Local_u8ErrorState=NOK;
		}
	}
	else if(Copy_u8Interrupt==EXTI_INT1){
		switch (Copy_u8Sense){
		case EXTI_LOW_LEVEL:
			CLR_BIT(MCUCR,MCUCR_ISC10);
			CLR_BIT(MCUCR,MCUCR_ISC11);
			break;
		case EXTI_ON_CHANGE:
			SET_BIT(MCUCR,MCUCR_ISC10);
			CLR_BIT(MCUCR,MCUCR_ISC11);
			break;
		case EXTI_FALLING_EDGE:
			CLR_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
			break;
		case EXTI_RISING_EDGE:
			SET_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
			break;
		default: Local_u8ErrorState=NOK;
		}

	}
	else if(Copy_u8Interrupt==EXTI_INT2){

		if(Copy_u8Sense==EXTI_FALLING_EDGE){
			CLR_BIT(MCUCSR,MCUCSR_INT2);
		}
		else if(Copy_u8Sense==EXTI_RISING_EDGE){
			SET_BIT(MCUCSR,MCUCSR_INT2);
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

u8 EXTI_u8SetInterruptStatus(u8 Copy_u8Interrupt, u8 Copy_u8Status){
	u8 Local_u8ErrorState=OK;
	if(Copy_u8Interrupt==EXTI_INT0){
		if(Copy_u8Status==EXTI_ENABLE){
			SET_BIT(GICR,GICR_INT0);
		}
		else if(Copy_u8Status==EXTI_DISABLE){
			CLR_BIT(GICR,GICR_INT0);
		}
		else{
			Local_u8ErrorState=NOK;
		}
	}
	else if(Copy_u8Interrupt==EXTI_INT1){
		if(Copy_u8Status==EXTI_ENABLE){
			SET_BIT(GICR,GICR_INT1);
		}
		else if(Copy_u8Status==EXTI_DISABLE){
			CLR_BIT(GICR,GICR_INT1);
		}
		else{
			Local_u8ErrorState=NOK;
		}
	}
	else if(Copy_u8Interrupt==EXTI_INT2){

		if(Copy_u8Status==EXTI_ENABLE){
			SET_BIT(GICR,GICR_INT2);
		}
		else if(Copy_u8Status==EXTI_DISABLE){
			CLR_BIT(GICR,GICR_INT2);
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

u8 EXTI_u8Int0SetCallBack(void(*Copy_pvInt0Func)(void)){
	u8 Local_u8ErrorState=OK;
	if(Copy_pvInt0Func!=NULL){
		EXTI_pvInt0Func=Copy_pvInt0Func;
	}
	else{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}

u8 EXTI_u8Int1SetCallBack(void(*Copy_pvInt1Func)(void)){
	u8 Local_u8ErrorState=OK;
	if(Copy_pvInt1Func!=NULL){
		EXTI_pvInt1Func=Copy_pvInt1Func;
	}
	else{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}

u8 EXTI_u8Int2SetCallBack(void(*Copy_pvInt2Func)(void)){
	u8 Local_u8ErrorState=OK;
	if(Copy_pvInt2Func!=NULL){
		EXTI_pvInt2Func=Copy_pvInt2Func;
	}
	else{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}

/*ISR For INT0*/
void __vector_1(void)    __attribute__((signal));
void __vector_1(void){
	if(EXTI_pvInt0Func!=NULL){
		EXTI_pvInt0Func();
	}
}

void __vector_2(void)    __attribute__((signal));
void __vector_2(void){
	if(EXTI_pvInt1Func!=NULL){
		EXTI_pvInt1Func();
	}
}

void __vector_3(void)    __attribute__((signal));
void __vector_3(void){
	if(EXTI_pvInt2Func!=NULL){
		EXTI_pvInt2Func();
	}
}

