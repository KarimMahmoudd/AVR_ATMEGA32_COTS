/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: ADC                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/* Options: 1-AREF_REF
            2-AVCC_REF
            3-INTERNAL_REF
                                 */
#define REFERENCE_SELECTION  AVCC_REF

/* Options: 1-8
            2-10
                                 */
#define ADC_RESOLUTION       8

/* Options:
            1-ENABLE
            2-DISABLE
                                 */
#define AUTO_TRIGGER         DISABLE

/* Options:
            1-ENABLE
            2-DISABLE
                                 */
#define ADC_INT               DISABLE

/* Options:
            1-DIV_BY2  
            2-DIV_BY4  
            3-DIV_BY8  
            4-DIV_BY16 
            5-DIV_BY32 
            6-DIV_BY64 
            7-DIV_BY128
                                 */
#define PRESCALER    DIV_BY128

/* Options:
            1-FREE_RUNNING
            2-ANALOG_COMP
            3-EXTI0
            4-TIMER0_COMP_MATCH
            5-TIMER0_OVF
            6-TIMER_MATCH_B
            7-TIMER1_OVF
            8-TIMER1_CAP_EVENT
                                 */
#define AUTO_TRIGGER_SOURCE     FREE_RUNNING

/* Options:
            1-ENABLE
            2-DISABLE
                                 */
#define ADC_ENABLE          ENABLE

#define ADC_u32TIMEOUT      50000
#endif