/**************************************************************endif***********************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: TIMER                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#define ENABLE						 		1
#define DISABLE								2

#define NORMAL								1
#define PHC_PWM								2
#define CTC									3
#define FAST_PWM							4

#define DISCONNECT							0
#define CTC_TOGGLE							1
#define CTC_CLR								2
#define CTC_SET								3
#define FAST_PWM_NON_INVERTED				2
#define FAST_PWM_INVERTED					3
#define PHC_PWM_NON_INVERTED   				2
#define PHC_PWM_INVERTED		   			3

#define  DISABLE_CLOCK                  	0
#define  DIV_BY_1                       	1
#define  DIV_BY_8                       	2
#define  DIV_BY_64                      	3
#define  DIV_BY_256                     	4
#define  DIV_BY_1024                    	5
#define  EXT_CLK_FALLING_EDGE           	6
#define  EXT_CLK_RISING_EDGE            	7

#define T1_NORMAL                           1
#define T1_PHC_PWM_8_BIT                    2
#define T1_PHC_PWM_9_BIT                    3
#define T1_PHC_PWM_10_BIT                   4
#define T1_CTC                              5
#define T1_FAST_PWM_8_BIT                   6
#define T1_FAST_PWM_9_BIT                   7
#define T1_FAST_PWM_10_BIT                  8
#define T1_PHFC_PWM_CUSTOM_TOP              9
#define T1_PHFC_PWM                         10
#define T1_PHC_PWM_CUSTOM_TOP               11
#define T1_PHC_PWM                          12
#define T1_CTC_CUSTOM_TOP                   13
#define T1_FAST_PWM_CUSTOM_TOP              14
#define T1_FAST_PWM                         15

#define PRESCALER_MASK						0b11111000
#define COMP_MATCH_OUT_MASK					0b11001111
#define T1_COMP_MATCH_OUT_MASK				0b00001111

#endif
