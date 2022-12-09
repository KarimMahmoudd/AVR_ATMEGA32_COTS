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


/*******************************************************************TIMER0***********************************************
 ************************************************************************************************************************/

/*Options:
 *			1-NORMAL
 *			2-PHC_PWM
 *			3-CTC
 *			4-FAST_PWM
										*/
#define TIMER0_GEN_MODE						FAST_PWM

/*Options:
 *			1-DISCONNECT
 *			2-CTC_TOGGLE (RESERVED For fast PWM)
 *			3-CTC_CLR
 *			4-CTC_SET
 *			5-FAST_PWM_NON_INVERTED (CLR ON COMP SET ON TOP)
 *			6-FAST_PWM_INVERTED     (SET ON COMP CLR ON TOP)
 *			7-PHC_PWM_NON_INVERTED	(CLR ON COMP UP SET ON COMP DOWN)
 *			8-PHC_PWM_INVERTED	    (CLR ON COMP UP SET ON COMP DOWN)
																			*/
#define TIMER0_COMP_MATCH_OUTPUT_MODE			FAST_PWM_NON_INVERTED

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
#define TIMER0_PRESCALER						DIV_BY_64

/*Options:
 *			1-ENABLE
 *			2-DISABLE
										*/
#define TIMER0_COMP_MATCH_INT					DISABLE

/*Options:
 *			1-ENABLE
 *			2-DISABLE
										*/
#define TIMER0_OVERFLOW_INT					DISABLE



/************************************************************************************************************************
 ************************************************************************************************************************/


/*******************************************************TIMER1***********************************************************
 ************************************************************************************************************************/

/*Options:
 *			1-T1_NORMAL
 *			2-T1_PHC_PWM_8_BIT
 *			3-T1_PHC_PWM_9_BIT
 *			4-T1_PHC_PWM_10_BIT
 *			5-T1_CTC
 *			6-T1_FAST_PWM_8_BIT
 *			7-T1_FAST_PWM_9_BIT
 *			8-T1_FAST_PWM_10_BIT
 *			9-T1_PHFC_PWM_CUSTOM_TOP
 *			10-T1-PHFC_PWM
 *			11-T1_PHC_PWM_CUSTOM_TOP
 *			12-T1_PHC_PWM
 *			13-T1_CTC_CUSTOM_TOP
 *			14-T1_FAST_PWM_CUSTOM_TOP
 *			15-T1_FAST_PWM
										*/
#define TIMER1_GEN_MODE						T1_FAST_PWM_CUSTOM_TOP

/*Options:
 *			1-DISCONNECT
 *			2-CTC_TOGGLE (RESERVED For fast PWM)
 *			3-CTC_CLR
 *			4-CTC_SET
 *			5-FAST_PWM_NON_INVERTED (CLR ON COMP SET ON TOP)
 *			6-FAST_PWM_INVERTED     (SET ON COMP CLR ON TOP)
 *			7-PHC_PWM_NON_INVERTED	(CLR ON COMP UP SET ON COMP DOWN)
 *			8-PHC_PWM_INVERTED	    (CLR ON COMP UP SET ON COMP DOWN)
																			*/
#define TIMER1A_COMP_MATCH_OUTPUT_MODE			FAST_PWM_NON_INVERTED

/*Options:
 *			1-DISCONNECT
 *			2-CTC_TOGGLE (RESERVED For fast PWM)
 *			3-CTC_CLR
 *			4-CTC_SET
 *			5-FAST_PWM_NON_INVERTED (CLR ON COMP SET ON TOP)
 *			6-FAST_PWM_INVERTED     (SET ON COMP CLR ON TOP)
 *			7-PHC_PWM_NON_INVERTED	(CLR ON COMP UP SET ON COMP DOWN)
 *			8-PHC_PWM_INVERTED	    (CLR ON COMP UP SET ON COMP DOWN)
																			*/
#define TIMER1B_COMP_MATCH_OUTPUT_MODE			FAST_PWM_NON_INVERTED

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
#define TIMER1_PRESCALER						DIV_BY_8


/*Options:
 *			1-ENABLE
 *			2-DISABLE
										*/
#define TIMER1_OVERFLOW_INT					DISABLE

/*Options:
 *			1-ENABLE
 *			2-DISABLE
										*/
#define TIMER1A_COMP_MATCH_INT					DISABLE

/*Options:
 *			1-ENABLE
 *			2-DISABLE
										*/
#define TIMER1B_COMP_MATCH_INT					DISABLE





/************************************************************************************************************************
 ************************************************************************************************************************/



/********************************************************TIMER2**********************************************************
 ************************************************************************************************************************/
/*Options:
 *			1-NORMAL
 *			2-PHC_PWM
 *			3-CTC
 *			4-FAST_PWM
										*/
#define TIMER2_GEN_MODE						CTC

/*Options:
 *			1-DISCONNECT
 *			2-CTC_TOGGLE (RESERVED For fast PWM)
 *			3-CTC_CLR
 *			4-CTC_SET
 *			5-FAST_PWM_NON_INVERTED (CLR ON COMP SET ON TOP)
 *			6-FAST_PWM_INVERTED     (SET ON COMP CLR ON TOP)
 *			7-PHC_PWM_NON_INVERTED	(CLR ON COMP UP SET ON COMP DOWN)
 *			8-PHC_PWM_INVERTED	    (CLR ON COMP UP SET ON COMP DOWN)
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



/************************************************************************************************************************
 ************************************************************************************************************************/

#endif
