/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: TIMER                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_
//TIMER0

/*Options:
 *			1-NORMAL
 *			2-PWM
 *			3-CTC
 *			4-FAST_PWM
										*/
#define TIMER0_GEN_MODE						CTC

/*Options:
 *			1-DISCONNECT
 *			2-TOGGLE
 *			3-CLR
 *			4-SET
										*/
#define TIMER0_COMP_MATCH_OUTPUT_MODE			DISCONNECT

/*Options:
 *			1-DISABLE_CLOCK
 *			2-DIV_BY_1
 *			3-DIV_BY_8
 *			4-DIV_BY_64
 *			5-DIV_BY_256
 *			6-DIV_BY_1024
 *			7-EXT_CLK_FALLING_EDGE
 *			8-EXT_CLK_RISING_EDGE
										*/
#define TIMER0_PRESCALER						DIV_BY_8

/*Options:
 *			1-ENABLE
 *			2-DISABLE
										*/
#define TIMER0_COMP_MATCH_INT					ENABLE

/*Options:
 *			1-ENABLE
 *			2-DISABLE
										*/
#define TIMER0_OVERFLOW_INT					DISABLE

/*Options:
 *			0-255
										*/
#define TIMER0_COMP_MATCH_VAL					250

/*Options:
 *			0-255
										*/
#define TIMER0_PRELOAD_VAL					0


//TIMER1



//TIMER2

/*Options:
 *			1-NORMAL
 *			2-PWM
 *			3-CTC
 *			4-FAST_PWM
										*/
#define TIMER2_GEN_MODE						CTC

/*Options:
 *			1-DISCONNECT
 *			2-TOGGLE
 *			3-CLR
 *			4-SET
										*/
#define TIMER2_COMP_MATCH_OUTPUT_MODE			DISCONNECT

/*Options:
 *			1-DISABLE_CLOCK
 *			2-DIV_BY_1
 *			3-DIV_BY_8
 *			4-DIV_BY_64
 *			5-DIV_BY_256
 *			6-DIV_BY_1024
 *			7-EXT_CLK_FALLING_EDGE
 *			8-EXT_CLK_RISING_EDGE
										*/
#define TIMER2_PRESCALER						DIV_BY_8

/*Options:
 *			1-ENABLE
 *			2-DISABLE
										*/
#define TIMER2_COMP_MATCH_INT					ENABLE

/*Options:
 *			1-ENABLE
 *			2-DISABLE
										*/
#define TIMER2_OVERFLOW_INT					ENABLE

/*Options:
 *			0-255
										*/
#define TIMER2_COMP_MATCH_VAL					250

/*Options:
 *			0-255
										*/
#define TIMER2_PRELOAD_VAL					0

#endif
