/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: ADC                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ENABLE              1
#define DISABLE             2


#define IDLE				0
#define BUSY				1

#define SINGLE				0
#define CHAIN				1

//ADC Reference Modes
#define AREF_REF            1
#define AVCC_REF            2
#define INTERNAL_REF        3

//Auto Trigger Sources
#define FREE_RUNNING        0
#define ANALOG_COMP         1
#define EXTI0               2
#define TIMER0_COMP_MATCH   3
#define TIMER0_OVF          4
#define TIMER_MATCH_B       5
#define TIMER1_OVF          6
#define TIMER1_CAP_EVENT    7

//Prescaler
#define DIV_BY2             0
#define DIV_BY4             2
#define DIV_BY8             3
#define DIV_BY16            4
#define DIV_BY32            5
#define DIV_BY64            6
#define DIV_BY128           7

#define ADC_PRESCALER_MASK  0b11111000
#define AUTO_TRIG_SRC_MASK  0b00001111
#define CHANNEL_MUX_MASK    0b11100000
#endif
