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

#define START               1
#define STOP                2

//ADC Channels 
#define SINGLE_ENDED_ADC0                0
#define SINGLE_ENDED_ADC1                1
#define SINGLE_ENDED_ADC2                2
#define SINGLE_ENDED_ADC3                3
#define SINGLE_ENDED_ADC4                4
#define SINGLE_ENDED_ADC5                5
#define SINGLE_ENDED_ADC6                6
#define SINGLE_ENDED_ADC7                7
#define DIFF_ADC0P_ADC0N_10XG            8
#define DIFF_ADC1P_ADC0N_10XG            9
#define DIFF_ADC0P_ADC0N_200XG           10
#define DIFF_ADC1P_ADC0N_200XG           11
#define DIFF_ADC2P_ADC2N_10XG            12
#define DIFF_ADC3P_ADC2N_10XG            13
#define DIFF_ADC2P_ADC2N_200XG           14
#define DIFF_ADC3P_ADC2N_200XG           15
#define DIFF_ADC0P_ADC1N_1XG             16
#define DIFF_ADC1P_ADC1N_1XG             17
#define DIFF_ADC2P_ADC1N_1XG             18
#define DIFF_ADC3P_ADC1N_1XG             19
#define DIFF_ADC4P_ADC1N_1XG             20
#define DIFF_ADC5P_ADC1N_1XG             21
#define DIFF_ADC6P_ADC1N_1XG             22
#define DIFF_ADC7P_ADC1N_1XG             23
#define DIFF_ADC0P_ADC2N_1XG             24
#define DIFF_ADC1P_ADC2N_1XG             25
#define DIFF_ADC2P_ADC2N_1XG             26
#define DIFF_ADC3P_ADC2N_1XG             27
#define DIFF_ADC4P_ADC2N_1XG             28
#define DIFF_ADC5P_ADC2N_1XG             29
#define SINGLE_ENDED_VBG                 30
#define SINGLE_ENDED_GND                 31


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