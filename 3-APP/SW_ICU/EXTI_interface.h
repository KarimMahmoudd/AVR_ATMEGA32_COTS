/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: MCAL                      ***********************************************/
/******************************           SWC: EXTI                        ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#define EXTI_LOW_LEVEL								1
#define EXTI_ON_CHANGE								2
#define	EXTI_FALLING_EDGE							3
#define EXTI_RISING_EDGE							4

#define EXTI_INT0				1
#define EXTI_INT1				2
#define EXTI_INT2				3

#define EXTI_ENABLE				1
#define EXTI_DISABLE			2
void EXTI_voidInt0Init(void);

void EXTI_voidInt1Init(void);

void EXTI_voidInt2Init(void);
/*Description: A function that sets the control sense for any of the three external interrupt pins using postbuild configuration
  Input: Copy_u8Interrupt, options are: 	1- EXTI_INT0
											2- EXTI_INT1
											3- EXTI_INT2

 	 	 Copy_u8Sense, options are:  	1- EXTI_LOW_LEVEL
										2- EXTI_ON_CHANGE
										3- EXTI_FALLING_EDGE
										4- EXTI_RISING_EDGE

Output: Error status with type u8
																																		*/
u8 EXTI_u8SetSenseControl(u8 Copy_u8Interrupt, u8 Copy_u8Sense);
/*Description: A function that enables or disables any of the three external interrupt pins using postbuild configuration
  Input: Copy_u8Interrupt, options are: 	1- EXTI_INT0
											2- EXTI_INT1
											3- EXTI_INT2

 	 	 	 Copy_u8Sense, options are:  	1- EXTI_ENABLE
											2- EXTI_DISABLE

Output: Error status with type u8
																																		*/
u8 EXTI_u8SetInterruptStatus(u8 Copy_u8Interrupt, u8 Copy_u8Status);

u8 EXTI_u8Int0SetCallBack(void(*Copy_pvInt0Func)(void));

u8 EXTI_u8Int1SetCallBack(void(*Copy_pvInt1Func)(void));

u8 EXTI_u8Int2SetCallBack(void(*Copy_pvInt2Func)(void));
#endif
