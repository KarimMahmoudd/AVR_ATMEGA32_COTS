/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************           Author: Karim Mahmoud            ***********************************************/
/******************************           Layer: RTOS Stack                ***********************************************/
/******************************           SWC: RTOS                      ***********************************************/
/******************************           Version: 1.00                    ***********************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/

#include "STD_TYPES.h"

#include "TIMER0_interface.h"
#include "GIE_interface.h"

#include "RTOS_interface.h"
#include "RTOS_config.h"
#include "RTOS_private.h"

Task_t SystemTasks[TASK_NUM]={{NULL}};

void RTOS_voidStart(void){
	TIMER0_u8SetCallBack(&voidScheduler);
	GIE_voidEnable();
	TIMER0_voidInit();
}

u8 RTOS_u8CreateTask(u8 Copy_u8Priority, u16 Copy_u16Periodicity,u16 Copy_u16FirstDelay, void (*Copy_pvTaskFunc)(void)){
	u8 Local_u8ErrorState=OK;
	if(Copy_pvTaskFunc!=NULL){
		if(SystemTasks[Copy_u8Priority].TaskFunc==NULL){
			SystemTasks[Copy_u8Priority].Periodicity = Copy_u16Periodicity;
			SystemTasks[Copy_u8Priority].TaskFunc = Copy_pvTaskFunc;
			SystemTasks[Copy_u8Priority].State = TASK_RESUMED;
			SystemTasks[Copy_u8Priority].FirstDelay=Copy_u16FirstDelay;
		}
		else{
			Local_u8ErrorState=NOK;
		}
	}
	else{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}

static void voidScheduler(void){

	u8 Local_u8TaskCounter;

	//Loop through the tasks according to priority in array
	for(Local_u8TaskCounter=0;Local_u8TaskCounter<TASK_NUM;Local_u8TaskCounter++){
		if(SystemTasks[Local_u8TaskCounter].State == TASK_RESUMED){
			if(SystemTasks[Local_u8TaskCounter].FirstDelay == 0){

				//Invoke Task
				if(SystemTasks[Local_u8TaskCounter].TaskFunc!=NULL){
					SystemTasks[Local_u8TaskCounter].TaskFunc();

					SystemTasks[Local_u8TaskCounter].FirstDelay=SystemTasks[Local_u8TaskCounter].Periodicity-1;
				}
			}
			else{
				SystemTasks[Local_u8TaskCounter].FirstDelay--;
			}
		}

	}
}

void RTOS_voidSuspendTask(u8 Copy_u8Priority){
	SystemTasks[Copy_u8Priority] = TASK_SUSPENDED;
}

void RTOS_voidResumeTask(u8 Copy_u8Priority){
	SystemTasks[Copy_u8Priority] = TASK_RESUMED;
}

void RTOS_u8DeleteTask(u8 Copy_u8Priority){
	SystemTasks[Copy_u8Priority].TaskFunc=NULL;
}
