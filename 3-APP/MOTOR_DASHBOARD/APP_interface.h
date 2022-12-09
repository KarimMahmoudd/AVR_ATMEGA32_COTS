#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

#define DCM_PORT      		DIO_u8PORTD
#define DCM_PIN				DIO_u8PIN4
#define THER_CHANNEL		ADC_SINGLE_ENDED_ADC1
#define LDR_CHANNEL			ADC_SINGLE_ENDED_ADC2
#define POTENTIO_CHANNEL	ADC_SINGLE_ENDED_ADC0


#define DC					1
#define STPR				2
#define SERVO				3
#define EXIT				4

#define CW					1
#define CCW					2

#define FULL				1
#define POTENTIO			2
#define LM35				3

void APP_voidShowStartMenu(void);
void APP_voidGetID(u8 *Copy_pu8IDArr);
void APP_voidGetPassword(u8* Copy_u8pu8PassArr);
u8 APP_voidCheckPassword(const u8* Copy_pu8IDArr,u8* Copy_pu8PassArr);
void APP_voidShowMainMenu();
void APP_voidShowRotateMenu();
void APP_voidShowDCSpeedMenu();
void APP_voidReadKey(u8* Copy_pu8Key);
void APP_voidChooseMotor();
u16 APP_u16GetAngle();
void ADCNotifFunc(void);
#endif /* APP_INTERFACE_H_ */
