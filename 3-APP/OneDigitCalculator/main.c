#include "STD_TYPES.h"

#include "PORT_interface.h"

#include "KPD_interface.h"
#include "CLCD_interface.h"
void main(void)
{
	u8 Local_u8OperatorCounter=0;
	char Local_chOperatorArr[4] ={'+','-','*','/'},Local_chOperator=Local_chOperatorArr[Local_u8OperatorCounter];
	u8 Local_u8Key,Local_u8Operand1=1,Local_u8Operand2=1,Local_u8PosCounter=0;
	PORT_voidInit();
	CLCD_voidInit();
	CLCD_voidSendNumber(Local_u8Operand1);
	CLCD_voidSendData(Local_chOperator);
	CLCD_voidSendNumber(Local_u8Operand2);
	CLCD_voidGoToXY(0,0);
	while(1)
	{
		do
		{
			Local_u8Key=KPD_u8GetPressedKey();
		}while(Local_u8Key == 0xff);

		if(Local_u8Key==0)
		{
			if(Local_u8PosCounter==0)
			{
				if(Local_u8Operand1==9)
				{
					Local_u8Operand1=0;
				}
				else
				{
					Local_u8Operand1++;
				}
				CLCD_voidSendNumber(Local_u8Operand1);
			}
			else if(Local_u8PosCounter==1)
			{
				if(Local_u8OperatorCounter==3){
					Local_u8OperatorCounter=0;
				}
				else{
					Local_u8OperatorCounter++;
				}
				CLCD_voidSendData(Local_chOperatorArr[Local_u8OperatorCounter]);
				Local_chOperator=Local_chOperatorArr[Local_u8OperatorCounter];
			}
			else if(Local_u8PosCounter==2){
				if(Local_chOperator=='/'){
					if(Local_u8Operand2==9){
						Local_u8Operand2=1;
					}
					else{
						Local_u8Operand2++;
					}
				}
				else{
					if(Local_u8Operand2==9)
					{
						Local_u8Operand2=0;
					}
					else
					{
						Local_u8Operand2++;
					}
				}
				CLCD_voidSendNumber(Local_u8Operand2);
			}
			CLCD_voidGoToXY(0,Local_u8PosCounter);
		}
		else if(Local_u8Key==1)
		{
			if(Local_u8PosCounter==0)
			{
				if(Local_u8Operand1==0)
				{
					Local_u8Operand1=9;
				}
				else
				{
					Local_u8Operand1--;
				}
				CLCD_voidSendNumber(Local_u8Operand1);
			}
			else if(Local_u8PosCounter==1)
			{
				if(Local_u8OperatorCounter==0){
					Local_u8OperatorCounter=3;
				}
				else{
					Local_u8OperatorCounter--;
				}
				CLCD_voidSendData(Local_chOperatorArr[Local_u8OperatorCounter]);
				Local_chOperator=Local_chOperatorArr[Local_u8OperatorCounter];
			}
			else if(Local_u8PosCounter==2){
				if(Local_chOperator=='/'){
					if(Local_u8Operand2==1){
						Local_u8Operand2=9;
					}
					else{
						Local_u8Operand2--;
					}
				}
				else{
					if(Local_u8Operand2==0)
					{
						Local_u8Operand2=9;
					}
					else
					{
						Local_u8Operand2--;
					}
				}
				CLCD_voidSendNumber(Local_u8Operand2);
			}
			CLCD_voidGoToXY(0,Local_u8PosCounter);
		}
		else if(Local_u8Key==2){
			Local_u8PosCounter++;
			CLCD_voidGoToXY(0,Local_u8PosCounter);
			if(Local_u8PosCounter==3){
				CLCD_voidSendData('=');
				switch(Local_chOperator){
				case '+':CLCD_voidSendNumber(Local_u8Operand1+Local_u8Operand2);break;
				case '-':if(Local_u8Operand1<Local_u8Operand2){
					CLCD_voidSendData('-');
					CLCD_voidSendNumber(Local_u8Operand2-Local_u8Operand1);
				}
				else{
					CLCD_voidSendNumber(Local_u8Operand1-Local_u8Operand2);}break;
				case '*':CLCD_voidSendNumber(Local_u8Operand1*Local_u8Operand2);break;
				case '/':CLCD_voidSendNumber(Local_u8Operand1/Local_u8Operand2);
				CLCD_voidSendData('.');
				CLCD_voidSendNumber(((Local_u8Operand1%Local_u8Operand2)*1000)/Local_u8Operand2);break;
				}
			}
			else if(Local_u8PosCounter>3){
				Local_u8PosCounter=0;
				Local_u8Operand1=1;
				Local_u8Operand2=1;
				Local_u8OperatorCounter=0;
				Local_chOperator=Local_chOperatorArr[Local_u8OperatorCounter];
				CLCD_voidSendCommand(1);
				CLCD_voidSendNumber(Local_u8Operand1);
				CLCD_voidSendData(Local_chOperator);
				CLCD_voidSendNumber(Local_u8Operand2);
				CLCD_voidGoToXY(0,Local_u8PosCounter);
			}
		}

	}
}
