/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: WDT                       ***********************************************/
/******************************           SWC: PORT                        ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_

#define SLEEP_16_3_ms			0
#define SLEEP_32_5_ms			1
#define SLEEP_65_ms				2
#define SLEEP_0_13_s			3
#define SLEEP_0_26_s			4
#define SLEEP_0_52_s			5
#define SLEEP_1_s				6
#define SLEEP_2_1_s				7


void WDT_voidSleep(u8 Copy_u8SleepTime);
void WDT_voidEnable(void);
void WDT_voidDisable(void);

#endif