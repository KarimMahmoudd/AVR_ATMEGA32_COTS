/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: PWM                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#ifndef PWM_CONFIG_H_
#define PWM_CONFIG_H_
//TIMER0
/*Options:
 *			1-PHASE_CORRECT_PWM
 *			2-FAST_PWM
										*/
#define TIMER0_WAVE_GEN_MODE						FAST_PWM

/*Options:
 *			1-PHC_PWM_DISCONNECT
 *			2-PHC_PWM_NON_INVERTED	(CLR ON COMP UP CLR ON COMP DOWN)
 *			3-PHC_PWM_INVERTED 		(SET ON COMP UP CLR ON COMP DOWN)
 *			4-FAST_PWM_DISCONNECT
 *			5-FAST_PWM_NON_INVERTED (CLR ON COMP SET ON TOP)
 *			6-FAST_PWM_INVERTED     (SET ON COMP CLR ON TOP)
																				*/
#define TIMER0_PWM_MODE								FAST_PWM_NON_INVERTED


/*Options:
 *			1-DISABLE_CLOCK
 *			2-us_0_125(32 us OVF)
 *			3-us_1 (256 us OVF)
 *			4-us_8 (2,048 us OVF)
 *			5-us_32 (8,192 us OVF)
 *			6-us_128 (32,768 us OVF)
 *			7-EXT_CLK_FALLING_EDGE
 *			8-EXT_CLK_RISING_EDGE
										*/
#define TIMER0_CLOCK_TICK						us_8


//TIMER2
/*Options:
 *			1-PHASE_CORRECT_PWM
 *			2-FAST_PWM
										*/
#define TIMER2_WAVE_GEN_MODE						FAST_PWM

/*Options:
 *			1-PHC_PWM_DISCONNECT
 *			3-PHC_PWM_CLR_ON_CMP_UP
 *			4-PHC_PWM_SET_ON_CMP_UP
 *			5-FAST_PWM_DISCONNECT
 *			6-FAST_PWM_NON_INVERTED (CLR ON COMP SET ON TOP For fast PWM)
 *			7-FAST_PWM_INVERTED     (SET ON COMP CLR ON TOP For fast PWM)
																				*/
#define TIMER2_PWM_MODE								FAST_PWM_NON_INVERTED

/*Options:
 *			1-DISABLE_CLOCK
 *			2-us_0_125(32 us OVF)
 *			3-us_1 (256 us OVF)
 *			4-us_8 (2,048 us OVF)
 *			5-us_32 (8,192 us OVF)
 *			6-us_128 (32,768 us OVF)
 *			7-EXT_CLK_FALLING_EDGE
 *			8-EXT_CLK_RISING_EDGE
										*/
#define TIMER0_CLOCK_TICK						us_8

#endif /* PWM_CONFIG_H_ */
