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

u16 ADC_u8GetChannelReading(u8 Copy_u8Channel){
    //adjusting the channel using bit masking
    ADMUX&=CHANNEL_MUX_MASK;
    ADMUX|=Copy_u8Channel;
    #if AUTO_TRIGGER==DISABLE
    //start conversion
    SET_BIT(ADCSRA,ADCSRA_ADSC);
    #if ADC_INT==DISABLE
    //polling until the conversion is finished using the interrupt flag
    while(GET_BIT(ADCSRA,ADCSRA_ADIF)==0);
    //clearing the interrupt flag by writing 1
    SET_BIT(ADCSRA,ADCSRA_ADIF);
    #endif
    #elif AUTO_TRIGGER==ENABLE
    #if ADC_INT==DISABLE
    //polling until the conversion is finished using the interrupt flag
    while(GET_BIT(ADCSRA,ADCSRA_ADIF)==0);
    //clearing the interrupt flag by writing 1
    SET_BIT(ADCSRA,ADCSRA_ADIF);
    #endif
    #endif
    //returning the reading
    #if ADC_RESOLUTION == 8
    return ADCH;
    #elif ADC_RESOLUTION == 10
    return ADC;
    #else
    #error "Wrong ADJUST OPTION"
    #endif
}
