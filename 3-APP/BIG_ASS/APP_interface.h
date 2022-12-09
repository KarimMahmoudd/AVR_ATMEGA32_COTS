#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

#define DCM_PORT      		DIO_u8PORTA
#define DCM_PIN				DIO_u8PIN3
#define THER_CHANNEL		ADC_SINGLE_ENDED_ADC0
#define LDR_CHANNEL			ADC_SINGLE_ENDED_ADC1

void APP_voidShowStartMenu(void);
void APP_voidGetID(u8 *Copy_pu8IDArr);
void APP_voidGetPassword(u8* Copy_u8pu8PassArr);
u8 APP_voidCheckPassword(const SSD_t* Copy_psSSD,const u8* Copy_pu8IDArr,u8* Copy_pu8PassArr);
void ADCNotifFunc(void);

#endif /* APP_INTERFACE_H_ */
