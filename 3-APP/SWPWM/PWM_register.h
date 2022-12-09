/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: PWM                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
#ifndef PWM_REGISTER_H_
#define PWM_REGISTER_H_

#define TCCR0                       *((volatile u8*)(0x53))         //Timer/Counter0 Control Register
#define TCCR0_WGM00                 6                               //Wave Generation Mode Bit 0 (Timer Mode)
#define TCCR0_COM01                 5                               //Compare Match Output Mode Bit 1
#define TCCR0_COM00                 4                               //Compare Match Output Mode Bit 0
#define TCCR0_WGM01                 3                               //Wave Generation Mode Bit 1 (Timer Mode)
#define TCCR0_CS02                  2                               //Clock Select Bit 2
#define TCCR0_CS01                  1                               //Clock Select Bit 1
#define TCCR0_CS00                  0                               //Clock Select Bit 0

#define TCCR1A                      *((volatile u8*)(0x4f))         //Timer/Counter1 Control Register A
#define TCCR1A_COM1A1               7                               //Compare Match Output Mode Bit 1 for Channel A
#define TCCR1A_COM1A0               6                               //Compare Match Output Mode Bit 0 for Channel A
#define TCCR1A_COM1B1               5                               //Compare Match Output Mode Bit 1 for Channel B
#define TCCR1A_COM1B0               4                               //Compare Match Output Mode Bit 0 for Channel B
#define TCCR1A_WGM11                1                               //Wave Generation Mode Bit 1(Timer Mode)
#define TCCR1A_WGM10                0                               //Wave Generation Mode Bit 0(Timer Mode)

#define TCCR1B                      *((volatile u8*)(0x4e))         //Timer/Counter1 Control Register B
#define TCCR1B_ICNC1                7                               //Input Capture Noise Canceler
#define TCCR1B_ICES1                6                               //Input Capture Edge Select
#define TCCR1B_WGM13                4                               //Wave Generation Mode Bit 3(Timer Mode)
#define TCCR1B_WGM12                3                               //Wave Generation Mode Bit 2(Timer Mode)
#define TCCR1B_CS12                 2                               //Clock Select Bit 2
#define TCCR1B_CS11                 1                               //Clock Select Bit 1
#define TCCR1B_CS10                 0                               //Clock Select Bit 0

#define TCCR2                       *((volatile u8*)(0x45))         //Timer/Counter2 Control Register
#define TCCR2_WGM20                 6                               //Wave Generation Mode Bit 0 (Timer Mode)
#define TCCR2_WGM21                 3                               //Wave Generation Mode Bit 1 (Timer Mode)
#define TCCR2_COM21                 5                               //Compare Match Output Mode Bit 1
#define TCCR2_COM20                 4                               //Compare Match Output Mode Bit 0
#define TCCR2_CS22                  2                               //Clock Select Bit 2
#define TCCR2_CS21                  1                               //Clock Select Bit 1
#define TCCR2_CS20                  0                               //Clock Select Bit 0

#define OCR0                        *((volatile u8*)(0x5c))         //Output Compare Register 0

#define OCR1A                       *((volatile u16*)(0x4a))        //Output Compare Register 1A
#define OCR1AH                      *((volatile u8*)(0x4b))         //Output Compare Register 1A High Byte
#define OCR1AL                      *((volatile u8*)(0x4a))         //Output Compare Register 1A Low Byte

#define OCR1B                       *((volatile u16*)(0x48))        //Output Compare Register 1B
#define OCR1BH                      *((volatile u8*)(0x49))         //Output Compare Register 1B High Byte
#define OCR1BL                      *((volatile u8*)(0x48))         //Output Compare Register 1B Low Byte

#define OCR2                        *((volatile u8*)(0x43))         //Output Compare Register 2

#define ICR1                        *((volatile u16*)(0x46))        //Input Capture Register 1
#define ICR1H                       *((volatile u8*)(0x47))         //Input Capture Register 1 High Byte
#define ICR1L                       *((volatile u8*)(0x46))         //Input Capture Register 1 Low Byte

#endif /* PWM_REGISTER_H_ */
