/************************************************************************************************************************/
/************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            **********************************************/
/******************************           Layer: HAL                       **********************************************/
/******************************           SWC: STEPPER MOTOR               **********************************************/
/******************************           Version: 1.00                    **********************************************/
/******************************           Date: 18/10/2022                 **********************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/

#ifndef STPR_INTERFACE_H_
#define STPR_INTERFACE_H_

#define STPR_CLOCKWISE					0
#define STPR_COUNTER_CLOCKWISE			1

void STPR_voidRotateClockwise();
void STPR_voidRotateCounterClockwise();
void STPR_voidRotateAngle(u8 Copy_u8Direction, u32 Copy_u8Angle);

#endif
