/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: ADC                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

#define ADMUX                   *((volatile u8*)(0x27)) //ADC multiplexer selection register
#define ADMUX_REFS1             7                       //Reference Selection Bit 1
#define ADMUX_REFS0             6                       //Reference Selection Bit 2
#define ADMUX_ADLAR             5                       //ADC Left Adjust Result
#define ADMUX_MUX4              4                       //Analog Channel and Gain Selection Bit 4
#define ADMUX_MUX3              3                       //Analog Channel and Gain Selection Bit 3
#define ADMUX_MUX2              2                       //Analog Channel and Gain Selection Bit 2
#define ADMUX_MUX1              1                       //Analog Channel and Gain Selection Bit 1
#define ADMUX_MUX0              0                       //Analog Channel and Gain Selection Bit 0

#define ADCSRA                  *((volatile u8*)(0x26)) //ADC Control and Status Register A
#define ADCSRA_ADEN             7                       //ADC Enable
#define ADCSRA_ADSC             6                       //ADC Start Conversion
#define ADCSRA_ADATE            5                       //ADC Auto Trigger Enable
#define ADCSRA_ADIF             4                       //ADC Interrupt Flag
#define ADCSRA_ADIE             3                       //ADC Interrupt Enable
#define ADCSRA_ADPS2            2                       //Prescaler Bit 2
#define ADCSRA_ADPS1            1                       //Prescaler Bit 1
#define ADCSRA_ADPS0            0                       //Prescaler Bit 0

#define ADCH                    *((volatile u8*)(0x25)) //ADC Data High Byte Register

#define ADCL                    *((volatile u8*)(0x24)) //ADC Data Low Byte Register
#define ADC                     *((volatile u16*)(0x24))//ADC Data Low and High

#define SFIOR                   *((volatile u8*)(0x50)) //Special Function IO Register
#define SFIOR_ADTS2             7                       //ADC Auto Trigger Source Bit 2
#define SFIOR_ADTS1             6                       //ADC Auto Trigger Source Bit 1
#define SFIOR_ADTS0             5                       //ADC Auto Trigger Source Bit 0

#endif