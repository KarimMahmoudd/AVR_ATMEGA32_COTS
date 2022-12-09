#include "STD_TYPES.h"
#include "MATH_HELPER.h"

#include "PORT_interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"

#include "CLCD_interface.h"

void ICU_HW(void);
void OVF_Count(void);

static u32 PeriodTicks=0;
static u32 OnTimeTicks=0;
static u8  Reading1Overflows=0;
static u8  Reading2Overflows=0;
static u8  Reading1Flag=0;
static u8  Reading2Flag=0;
static u8  ResetFlag=0;
static u16 OVFTicks=0xffff;

void main(void){
	Timer1_t Local_Timer1={TIMER1_NORMAL,PRSCLR_DIV_BY_8,OCM_DISCONNECT,OCM_DISCONNECT,INT_DISABLE,INT_DISABLE,INT_ENABLE};
	Timer_t Local_Timer2={TIMER_FAST_PWM,PRSCLR_DIV_BY_1024,OCM_FAST_PWM_NON_INVERTED,INT_DISABLE,INT_DISABLE};

	PORT_voidInit();

	TIMER_u8SetCallBack(INT_TIMER1_CAPT,&ICU_HW);
	TIMER_u8SetCallBack(INT_TIMER1_OVF,&OVF_Count);
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
//	CLCD_voidSendString("On Ticks=");
	CLCD_voidSendNumber(OnTimeTicks);


	while(1){

	}
}

void OVF_Count(void){
	static u8 Local_u8Counter=0;
	if(ResetFlag==1){
		Local_u8Counter=0;
		ResetFlag=0;
	}
	if(Reading1Flag==1){
		Reading1Overflows=Local_u8Counter;
		Reading1Flag=0;
	}
	if(Reading2Flag==1){
		Reading2Overflows=Local_u8Counter;
		Reading2Flag=0;
		TIMER_u8SetIntStatus(INT_TIMER2_OVF,INT_DISABLE);

	}

	Local_u8Counter++;
}


void ICU_HW(void){
	static u32 Reading1, Reading2;
	static u8 Local_u8Counter=0;

	Local_u8Counter++;

	if(Local_u8Counter==1){
		TIMER_u8SetTimerVal(TIMER1,0);
		ResetFlag=1;
	}
	else if(Local_u8Counter==2){
		Reading1=ICU_u16ReadInputCapture();
		Reading1Flag=1;
		ICU_u8SetEdge(FALLING_EDGE);
	}
	else if(Local_u8Counter==3){
		Reading2=ICU_u16ReadInputCapture();
		Reading2Flag=1;
		ICU_u8SetEdge(RISING_EDGE);
	}
	else if(Local_u8Counter==4){
		Reading1+=(Reading1Overflows*OVFTicks);
		Reading2+=(Reading2Overflows*OVFTicks);
		PeriodTicks=Reading1;
		OnTimeTicks=Reading2-Reading1;
		TIMER_u8SetIntStatus(INT_TIMER1_CAPT,INT_DISABLE);
	}

}


