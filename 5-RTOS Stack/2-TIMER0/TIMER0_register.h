/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: RTOS Stack                ***********************************************/
/******************************           SWC: TIMER0                      ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
#ifndef TIMER0_REGISTER_H_
#define TIMER0_REGISTER_H_

#define TCCR0                       *((volatile u8*)(0x53))         //Timer/Counter0 Control Register
#define TCCR0_FOC0                  7                               //Force Output Compare
#define TCCR0_WGM00                 6                               //Wave Generation Mode Bit 0 (Timer Mode)
#define TCCR0_COM01                 5                               //Compare Match Output Mode Bit 1
#define TCCR0_COM00                 4                               //Compare Match Output Mode Bit 0
#define TCCR0_WGM01                 3                               //Wave Generation Mode Bit 1 (Timer Mode)
#define TCCR0_CS02                  2                               //Clock Select Bit 2
#define TCCR0_CS01                  1                               //Clock Select Bit 1
#define TCCR0_CS00                  0                               //Clock Select Bit 0


#define TCNT0                       *((volatile u8*)(0x52))         //Timer/Counter0 Register

#define OCR0                        *((volatile u8*)(0x5c))         //Output Compare Register 0

#define TIMSK                       *((volatile u8*)(0x59))         //Timer/Counter Interrupt Mask Register
#define TIMSK_OCIE0                 1                               //Timer/Counter0 Output Compare Match Interrupt Enable
#define TIMSK_TOIE0                 0                               //Timer/Counter0 Overflow Interrupt Enable

#define TIFR                        *((volatile u8*)(0x58))         //Timer/Counter Interrupt Flag Register
#define TIFR_OCF0                   1                               //Output Compare Flag 0
#define TIFR_TOV0                   0                               //Timer/Counter0 Overflow Flag

#endif
