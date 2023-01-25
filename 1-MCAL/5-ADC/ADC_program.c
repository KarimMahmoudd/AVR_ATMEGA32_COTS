/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: ADC                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_register.h"
//variables for Asynchronous Single Conversion
static u16* ADC_pu16Reading = NULL;
static void (*ADC_pvCallBackNotificationFunc)(void)=NULL;
//Busy State Variable for ADC
static u8 ADC_u8BusyState=IDLE;
//Conversion Mode single or chain
static u8 ADC_u8ConversionMode;
//variables for Asynchronous Chain Conversion
static Chain_t *ADC_psChain=NULL;
static u8 ADC_u8ChainIndex=0;

void ADC_voidInit(void){

	//Reference Selection
#if REFERENCE_SELECTION==AREF_REF
	CLR_BIT(ADMUX,ADMUX_REFS1);
	CLR_BIT(ADMUX,ADMUX_REFS0);
#elif REFERENCE_SELECTION==AVCC_REF
	CLR_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);
#elif REFERENCE_SELECTION==INTERNAL_REF
	SET_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);
#else
#error "Wrong Reference Selection Option"
#endif
	//Adjust Resultion
#if ADC_RESOLUTION==10
	CLR_BIT(ADMUX,ADMUX_ADLAR);
#elif ADC_RESOLUTION==8
	SET_BIT(ADMUX,ADMUX_ADLAR);
#else
#error "WRONG ADJUST OPTION"
#endif

	//auto trigger setting
#if AUTO_TRIGGER==ENABLE
	SET_BIT(ADCSRA,ADCSRA_ADATE);
	//Auto trigger source
	SFIOR&=AUTO_TRIG_SRC_MASK;
	SFIOR|=(AUTO_TRIGGER_SOURCE<<5);
#if AUTO_TRIGGER_SOURCE==FREE_RUNNING
	SET_BIT(ADCSRA,ADCSRA_ADSC);
#endif
#elif AUTO_TRIGGER==DISABLE
	CLR_BIT(ADCSRA,ADCSRA_ADATE);
#else
#error "WRONG AUTO TRIGGER OPTION"
#endif

	//Interrupt enable
#if ADC_INT==ENABLE
	SET_BIT(ADCSRA,ADCSRA_ADIE);
#elif ADC_INT==DISABLE
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
#else
#error "WRONG INT OPTION"
#endif

	//Prescaler Setting
	ADCSRA&=ADC_PRESCALER_MASK;
	ADCSRA|=PRESCALER ;

	//Enable or Disable ADC
#if ADC_ENABLE==ENABLE
	SET_BIT(ADCSRA,ADCSRA_ADEN);
#elif ADC_ENABLE==DISABLE
	CLR_BIT(ADCSRA,ADCSRA_ADEN);
#else
#error "Wrong ADC_ENABLE Option"
#endif
}

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel,u16* Copy_pu16Reading){
	u32 Local_u32Counter=0;
	u8 Local_u8ErrorState=OK;
	if(ADC_u8BusyState==IDLE){
		if(Copy_pu16Reading==NULL){
			Local_u8ErrorState=NULL_POINTER;
		}
		else{
			ADC_u8BusyState=BUSY;
			//adjusting the channel using bit masking
			ADMUX&=CHANNEL_MUX_MASK;
			ADMUX|=Copy_u8Channel;
			//start conversion
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			//polling until the conversion is finished using the interrupt flag
			while((GET_BIT(ADCSRA,ADCSRA_ADIF)==0) && (Local_u32Counter!=ADC_u32TIMEOUT)){
				Local_u32Counter++;
			}
			//clearing the interrupt flag by writing 1
			if(Local_u32Counter==ADC_u32TIMEOUT){
				//loop is broken because timeout is reached
				Local_u8ErrorState=NOK;
			}
			else{
				//flag is raised
				SET_BIT(ADCSRA,ADCSRA_ADIF);
				//returning the reading
#if ADC_RESOLUTION == 8
				*Copy_pu16Reading= ADCH;
#elif ADC_RESOLUTION == 10
				*Copy_pu16Reading = ADC;
#else
#error "Wrong ADJUST OPTION"
#endif
				ADC_u8BusyState=IDLE;
			}
		}
	}
	else{
		Local_u8ErrorState=BUSY_FUNC;
	}


	return Local_u8ErrorState;
}

u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel,u16* Copy_pu16Reading, void (*Copy_pvNotificationFunc)(void)){
	u8 Local_u8ErrorState=OK;
	if(ADC_u8BusyState==IDLE){
		ADC_u8BusyState=BUSY;
		if(Copy_pu16Reading==NULL||Copy_pvNotificationFunc==NULL){
			Local_u8ErrorState=NULL_POINTER;
		}
		else{
			ADC_u8ConversionMode=SINGLE;
			//put the local variables into global so they can be used in the ISR
			ADC_pu16Reading=Copy_pu16Reading;
			ADC_pvCallBackNotificationFunc=Copy_pvNotificationFunc;
			//adjusting the channel using bit masking
			ADMUX&=CHANNEL_MUX_MASK;
			ADMUX|=Copy_u8Channel;
			//start conversion
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			//Interrupt enable user enables global interrupt
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
	}
	else{
		Local_u8ErrorState=BUSY_FUNC;
	}
	return Local_u8ErrorState;
}

u8 ADC_u8StartChainConversionAsynch(Chain_t* Copy_psADCChain){
	u8 Local_u8ErrorState=OK;
	if(ADC_u8BusyState==IDLE){
		if(Copy_psADCChain==NULL){
			Local_u8ErrorState=NULL_POINTER;
		}
		else{
			//make ADC busy
			ADC_u8BusyState=BUSY;
			//make Conversion Mode Chain Conversion
			ADC_u8ConversionMode=CHAIN;
			//put the local variables into global so they can be used in the ISR
			ADC_psChain=Copy_psADCChain;
			//adjusting the channel using bit masking
			ADC_u8ChainIndex=0;
			ADMUX&=CHANNEL_MUX_MASK;
			ADMUX|=Copy_psADCChain->ChannelArr[ADC_u8ChainIndex];
			//start conversion
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			//Interrupt enable user enables global interrupt
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
	}
	else{
		Local_u8ErrorState=BUSY_FUNC;
	}
	return Local_u8ErrorState;
}


u8 ADC_u8StartChainConversionSynch(Chain_t* Copy_psADCChain){
	u8 Local_u8ErrorState=OK;
	if(ADC_u8BusyState==IDLE){
		if(Copy_psADCChain!=NULL){
			u8 Local_u8Iterator;
			for(Local_u8Iterator=0;Local_u8Iterator<Copy_psADCChain->Size;Local_u8Iterator++){
				ADC_u8StartConversionSynch(Copy_psADCChain->ChannelArr[Local_u8Iterator],Copy_psADCChain->ResultArr[Local_u8Iterator]);
			}
		}
		else{
			Local_u8ErrorState=NULL_POINTER;
		}
	}
	else{
		Local_u8ErrorState=BUSY_FUNC;
	}
	return Local_u8ErrorState;

}

void __vector_16(void)   __attribute__((signal));
void __vector_16(void){
	if(ADC_u8ConversionMode==SINGLE){
		//read result
#if ADC_RESOLUTION == 8
		*ADC_pu16Reading= ADCH;
#elif ADC_RESOLUTION == 10
		*ADC_pu16Reading = ADC;
#else
#error "Wrong ADJUST OPTION"
#endif
		//make the adc idle to work again
		ADC_u8BusyState=IDLE;
		//call the notification function
		ADC_pvCallBackNotificationFunc();
		//disable interrupt
		CLR_BIT(ADCSRA,ADCSRA_ADIE);
	}
	else if(ADC_u8ConversionMode==CHAIN){
#if ADC_RESOLUTION == 8
		ADC_psChain->ResultArr[ADC_u8ChainIndex]= ADCH;
#elif ADC_RESOLUTION == 10
		ADC_psChain->ResultArr[ADC_u8ChainIndex] = ADC;
#else
#error "WRONG RESOLUTION OPTION"
#endif
		//increment index
		ADC_u8ChainIndex++;

		if(ADC_u8ChainIndex==ADC_psChain->Size){
			ADC_psChain->NotiFunc();
			//disable interrupt
			CLR_BIT(ADCSRA,ADCSRA_ADIE);
			//make the adc idle to work again
			ADC_u8BusyState=IDLE;
		}
		else{
			//store the result

			//set new channel and start next conversion
			ADMUX&=CHANNEL_MUX_MASK;
			ADMUX|=ADC_psChain->ChannelArr[ADC_u8ChainIndex];
			SET_BIT(ADCSRA,ADCSRA_ADSC);

		}
	}
}
