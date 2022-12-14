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

#define ENABLE						 	1
#define DISABLE							2

#define NORMAL							1
#define PWM								2
#define CTC								3
#define FAST_PWM						4

#define DISCONNECT						0
#define TOGGLE							1
#define CLR								2
#define SET								3

#define  DISABLE_CLOCK                  0
#define  DIV_BY_1                       1
#define  DIV_BY_8                       2
#define  DIV_BY_64                      3
#define  DIV_BY_256                     4
#define  DIV_BY_1024                    5
#define  EXT_CLK_FALLING_EDGE           6
#define  EXT_CLK_RISING_EDGE            7

#define PRESCALER_MASK					0b11111000
#define COMP_MATCH_OUT_MASK				0b11001111

#endif
