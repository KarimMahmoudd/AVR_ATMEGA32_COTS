/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: PWM                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#ifndef PWM_PRIVATE_H_
#define PWM_PRIVATE_H_

#define PHASE_CORRECT_PWM					1
#define FAST_PWM							2

#define PHC_PWM_DISCONNECT  				0
#define PHC_PWM_CLR_ON_CMP_UP   			2
#define PHC_PWM_SET_ON_CMP_UP   			3
#define FAST_PWM_DISCONNECT     			0
#define FAST_PWM_NON_INVERTED 				2
#define FAST_PWM_INVERTED     				3

#define  DISABLE_CLOCK                  	0
#define  us_0_125      		              	1
#define  us_1               	         	2
#define  us_8                	        	3
#define  us_32                  	     	4
#define  us_128                		      	5
#define  EXT_CLK_FALLING_EDGE           	6
#define  EXT_CLK_RISING_EDGE            	7

#define PRESCALER_MASK						0b11111000
#define COMP_MATCH_OUT_MASK					0b11001111

#endif /* PWM_PRIVATE_H_ */
