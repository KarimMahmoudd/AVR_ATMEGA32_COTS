#include "STD_TYPES.h"
#include "MATH_HELPER.h"

#include "PORT_interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"

#include "CLCD_interface.h"
void ICU_HW(void);

static u16 PeriodTicks=0;
static u16 OnTimeTicks=0;


void main(void){
	Timer1_t Local_Timer1={TIMER1_NORMAL,PRSCLR_DIV_BY_8,OCM_DISCONNECT,OCM_DISCONNECT,INT_DISABLE,INT_DISABLE,INT_DISABLE};
	Timer_t Local_Timer2={TIMER_FAST_PWM,PRSCLR_DIV_BY_1024,OCM_FAST_PWM_NON_INVERTED,INT_DISABLE,INT_DISABLE};

	PORT_voidInit();

	TIMER_u8SetCallBack(INT_TIMER1_CAPT,&ICU_HW);
	ICU_u8Init(RISING_EDGE,INT_ENABLE);

	CLCD_voidInit();

	TIMER1_u8Init(&Local_Timer1);
	TIMER2_u8PWMGenerate(&Local_Timer2,25);

	GIE_voidEnable();


	while((PeriodTicks==0) && (OnTimeTicks==0));
	CLCD_voidGoToXY(0,0);
//	CLCD_voidSendString("Period Ticks=");
	CLCD_voidSendNumber(PeriodTicks);
	CLCD_voidGoToXY(1,0);
	CLCD_voidSendString("On Ticks=");
	CLCD_voidSendNumber(OnTimeTicks);


	while(1){

	}
}




void ICU_HW(void){
	static u16 Reading1, Reading2,Reading3;
	static u8 Local_u8Counter=0;
	Local_u8Counter++;
	if(Local_u8Counter==1){
		Reading1=ICU_u16ReadInputCapture();
	}
	else if(Local_u8Counter==2){
		Reading2=ICU_u16ReadInputCapture();
		PeriodTicks=Reading2-Reading1;
		ICU_u8SetEdge(FALLING_EDGE);
	}
	else if(Local_u8Counter==3){
		Reading3=ICU_u16ReadInputCapture();
		OnTimeTicks=Reading3-Reading2;
		TIMER_u8SetIntStatus(INT_TIMER1_CAPT,INT_DISABLE);
	}

}


