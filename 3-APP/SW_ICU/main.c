#include "STD_TYPES.h"
#include "MATH_HELPER.h"

#include "PORT_interface.h"
#include "TIMER_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"

#include "CLCD_interface.h"
void ICU_SW(void);

static u16 PeriodTicks=0;
static u16 OnTimeTicks=0;

void main(void){
	Timer1_t Local_Timer1={TIMER1_NORMAL,PRSCLR_DIV_BY_8,OCM_DISCONNECT,OCM_DISCONNECT,INT_DISABLE,INT_DISABLE,INT_DISABLE,INT_DISABLE};
	Timer_t Local_Timer2={TIMER_FAST_PWM,PRSCLR_DIV_BY_8,OCM_FAST_PWM_NON_INVERTED,INT_DISABLE,INT_DISABLE};

	PORT_voidInit();


	EXTI_u8Int0SetCallBack(&ICU_SW);
	EXTI_voidInt0Init();
	CLCD_voidInit();
	//	TIMER2_u8Init(&Local_Timer2);
	//	TIMER_u8SetCompMatch(TIMER2,64);
	TIMER1_u8Init(&Local_Timer1);
	TIMER2_u8PWMGenerate(&Local_Timer2,25);
	GIE_voidEnable();
	while((PeriodTicks==0) && (OnTimeTicks==0));
	CLCD_voidGoToXY(0,0);
	CLCD_voidSendString("Period Ticks=");
	CLCD_voidSendNumber(PeriodTicks);
	CLCD_voidGoToXY(1,0);
	CLCD_voidSendString("On Ticks=");
	CLCD_voidSendNumber(OnTimeTicks);

	while(1){

	}
}



void ICU_SW(void){
	static u8 Local_u8Counter=0;
	Local_u8Counter++;

	if(Local_u8Counter==1){
		TIMER_u8SetTimerVal(TIMER1A,0);
	}
	else if(Local_u8Counter==2){
		TIMER_u8GetTimerVal(TIMER1A,&PeriodTicks);
		EXTI_u8SetSenseControl(EXTI_INT0,EXTI_FALLING_EDGE);
	}
	else if(Local_u8Counter==3){
		TIMER_u8GetTimerVal(TIMER1A,&OnTimeTicks);
		OnTimeTicks-=PeriodTicks;
		EXTI_u8SetInterruptStatus(EXTI_INT0,EXTI_DISABLE);
	}
}


