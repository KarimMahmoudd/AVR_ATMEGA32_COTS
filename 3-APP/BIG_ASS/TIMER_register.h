/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: TIMER                         ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

#define TCCR0                       *((volatile u8*)(0x53))         //Timer/Counter0 Control Register
#define TCCR0_FOC0                  7                               //Force Output Compare
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
#define TCCR1A_FOC1A                3                               //Force Output Compare for Channel A
#define TCCR1A_FOC1B                2                               //Force Output Compare for Channel B
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
#define TCCR2_FOC2                  7                               //Force Output Compare
#define TCCR2_WGM20                 6                               //Wave Generation Mode Bit 0 (Timer Mode)
#define TCCR2_COM21                 5                               //Compare Match Output Mode Bit 1
#define TCCR2_COM20                 4                               //Compare Match Output Mode Bit 0
#define TCCR2_WGM21                 3                               //Wave Generation Mode Bit 1 (Timer Mode)
#define TCCR2_CS22                  2                               //Clock Select Bit 2
#define TCCR2_CS21                  1                               //Clock Select Bit 1
#define TCCR2_CS20                  0                               //Clock Select Bit 0

#define TCNT0                       *((volatile u8*)(0x52))         //Timer/Counter0 Register

#define TCNT1                       *((volatile u16*)(0x4c))        //Timer/Counter1 Register
#define TCNT1H                      *((volatile u8*)(0x4d))         //Timer/Counter1 Register High Byte
#define TCNT1L                      *((volatile u8*)(0x4c))         //Timer/Counter1 Register Low Byte

#define TCNT2                       *((volatile u8*)(0x44))         //Timer/Counter2 Register

#define OCR0                        *((volatile u8*)(0x5c))         //Output Compare Register 0

#define OCR1A                       *((volatile u16*)(0x4a))        //Output Compare Register 1A
#define OCR1AH                      *((volatile u8*)(0x4b))         //Output Compare Register 1A High Byte
#define OCR1AL                      *((volatile u8*)(0x4a))         //Output Compare Register 1A Low Byte

#define OCR1B                       *((volatile u16*)(0x48))        //Output Compare Register 1B
#define OCR1BH                      *((volatile u8*)(0x49))         //Output Compare Register 1B High Byte
#define OCR1BL                      *((volatile u8*)(0x48))         //Output Compare Register 1B Low Byte

#define ICR1                        *((volatile u16*)(0x46))        //Input Capture Register 1
#define ICR1H                       *((volatile u8*)(0x47))         //Input Capture Register 1 High Byte
#define ICR1L                       *((volatile u8*)(0x46))         //Input Capture Register 1 Low Byte

#define OCR2                        *((volatile u8*)(0x43))         //Output Compare Register 2

#define TIMSK                       *((volatile u8*)(0x59))         //Timer/Counter Interrupt Mask Register
#define TIMSK_OCIE2                 7                               //Timer/Counter2 Output Compare Match Interrupt Enable
#define TIMSK_TOIE2                 6                               //Timer/Counter2 Overflow Interrupt Enable
#define TIMSK_TICIE1                5                               //Timer/Counter1 Input Capture Interrupt Enable
#define TIMSK_OCIE1A                4                               //Timer/Counter1 Output Compare A Match Interrupt Enable
#define TIMSK_OCIE1B                3                               //Timer/Counter1 Output Compare B Match Interrupt Enable
#define TIMSK_TOIE1                 2                               //Timer/Counter1 Overflow Interrupt Enable
#define TIMSK_OCIE0                 1                               //Timer/Counter0 Output Compare Match Interrupt Enable
#define TIMSK_TOIE0                 0                               //Timer/Counter0 Overflow Interrupt Enable

#define TIFR                        *((volatile u8*)(0x58))         //Timer/Counter Interrupt Flag Register
#define TIFR_OCF2                   7                               //Output Compare Flag 2
#define TIFR_TOV2                   6                               //Timer/Counter2 Overflow Flag
#define TIFR_ICF1                   5                               //Timer/Counter1 Input Capture Flag
#define TIFR_OCF1A                  4                               //Timer/Counter1 Output Compare A Match Flag
#define TIFR_OCF1B                  3                               //Timer/Counter1 Output Compare B Match Flag
#define TIFR_TOV1                   2                               //Timer/Counter1 Overflow Flag
#define TIFR_OCF0                   1                               //Output Compare Flag 0
#define TIFR_TOV0                   0                               //Timer/Counter0 Overflow Flag

#define ASSR                        *((volatile u8*)(0x42))         //Asynchronous Status Register
#define ASSR_AS2                    3                               //Asynchronous Timer/Counter2
#define ASSR_TCN2UB                 2                               //Timer/Counter2 Update Busy
#define ASSR_OCR2UB                 1                               //Output Compare Register2 Update Busy
#define ASSR_TCR2UB                 0                               //Timer/Counter Control Register2 Update Busy

#endif
