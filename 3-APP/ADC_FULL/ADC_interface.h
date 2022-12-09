/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: ADC                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

//ADC Channels 
#define ADC_SINGLE_ENDED_ADC0                0
#define ADC_SINGLE_ENDED_ADC1                1
#define ADC_SINGLE_ENDED_ADC2                2
#define ADC_SINGLE_ENDED_ADC3                3
#define ADC_SINGLE_ENDED_ADC4                4
#define ADC_SINGLE_ENDED_ADC5                5
#define ADC_SINGLE_ENDED_ADC6                6
#define ADC_SINGLE_ENDED_ADC7                7
#define ADC_DIFF_ADC0P_ADC0N_10XG            8
#define ADC_DIFF_ADC1P_ADC0N_10XG            9
#define ADC_DIFF_ADC0P_ADC0N_200XG           10
#define ADC_DIFF_ADC1P_ADC0N_200XG           11
#define ADC_DIFF_ADC2P_ADC2N_10XG            12
#define ADC_DIFF_ADC3P_ADC2N_10XG            13
#define ADC_DIFF_ADC2P_ADC2N_200XG           14
#define ADC_DIFF_ADC3P_ADC2N_200XG           15
#define ADC_DIFF_ADC0P_ADC1N_1XG             16
#define ADC_DIFF_ADC1P_ADC1N_1XG             17
#define ADC_DIFF_ADC2P_ADC1N_1XG             18
#define ADC_DIFF_ADC3P_ADC1N_1XG             19
#define ADC_DIFF_ADC4P_ADC1N_1XG             20
#define ADC_DIFF_ADC5P_ADC1N_1XG             21
#define ADC_DIFF_ADC6P_ADC1N_1XG             22
#define ADC_DIFF_ADC7P_ADC1N_1XG             23
#define ADC_DIFF_ADC0P_ADC2N_1XG             24
#define ADC_DIFF_ADC1P_ADC2N_1XG             25
#define ADC_DIFF_ADC2P_ADC2N_1XG             26
#define ADC_DIFF_ADC3P_ADC2N_1XG             27
#define ADC_DIFF_ADC4P_ADC2N_1XG             28
#define ADC_DIFF_ADC5P_ADC2N_1XG             29
#define ADC_SINGLE_ENDED_VBG                 30
#define ADC_SINGLE_ENDED_GND                 31

typedef struct Chain{
	u8 ChainID[32];
	u8 Size;
	void (*NotiFunc)(void);
	u16 ResultArr[32];
}ADC_Chain_t;

void ADC_voidInit(void);

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel,u16* Copy_pu16Reading);

u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel,u16* Copy_pu16Reading, void(*Copy_pvNotificationFunc)(void));

u8 ADC_u8StartChainConversion(ADC_Chain_t* Copy_psADCChain);
#endif
