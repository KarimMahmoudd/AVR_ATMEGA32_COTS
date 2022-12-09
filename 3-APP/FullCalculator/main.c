#include "STD_TYPES.h"

#include "PORT_interface.h"

#include "KPD_interface.h"
#include "CLCD_interface.h"

u32 u32Power(u32 Copy_u32Base,s32 Copy_u32Exponent);

void main(void)
{
	char Local_chOperator;
	u32 Local_u32Key,Local_u32Operand1=0,Local_u32Operand2=0,Local_u32PosCounter=0,Local_u32OperatorPos,Local_u32OperandArr[20]={0};
	u8 Local_u8EndState=0,Local_u8OperatorState=0;
	PORT_voidInit();
	CLCD_voidInit();
	while(1){
		do{
			Local_u32Key=KPD_u8GetPressedKey();
		}while(Local_u32Key == 0xff);

		if(Local_u32Key=='+'||Local_u32Key=='-'||Local_u32Key=='*'||Local_u32Key=='/'){
			if(Local_u8EndState==1){
				CLCD_voidSendCommand(1);
				Local_u32Operand1=0;
				Local_u32Operand2=0;
				Local_u32PosCounter=0;
				Local_u8OperatorState=0;
				Local_u8EndState=0;
				for(u8 Local_u8Iterator=0;Local_u8Iterator<20;Local_u8Iterator++){
					Local_u32OperandArr[Local_u8Iterator]=0;
				}
			}
			if(Local_u8OperatorState==0){
				Local_chOperator=Local_u32Key;
				Local_u32OperandArr[Local_u32PosCounter]=Local_u32Key;
				CLCD_voidSendData(Local_u32Key);
				Local_u32OperatorPos=Local_u32PosCounter;
				Local_u32PosCounter++;
				for(u8 Local_u8Iterator=0;Local_u8Iterator<Local_u32OperatorPos;Local_u8Iterator++){
					Local_u32Operand1+=(u32Power(10,Local_u32OperatorPos-Local_u8Iterator-1))*Local_u32OperandArr[Local_u8Iterator];
				}
				Local_u8OperatorState=1;
			}
		}
		else if(Local_u32Key=='='){
			if(Local_u8EndState==1){
				CLCD_voidSendCommand(1);
				Local_u32Operand1=0;
				Local_u32Operand2=0;
				Local_u32PosCounter=0;
				Local_u8OperatorState=0;
				Local_u8EndState=0;
				for(u8 Local_u8Iterator=0;Local_u8Iterator<20;Local_u8Iterator++){
					Local_u32OperandArr[Local_u8Iterator]=0;
				}
			}
			for(u8 Local_u8Iterator=Local_u32OperatorPos+1;Local_u8Iterator<Local_u32PosCounter;Local_u8Iterator++){
				Local_u32Operand2+=(u32Power(10,Local_u32PosCounter-Local_u8Iterator-1))*Local_u32OperandArr[Local_u8Iterator];
			}
			CLCD_voidSendData(Local_u32Key);
			switch(Local_chOperator){
			case '+':CLCD_voidSendNumber(Local_u32Operand1+Local_u32Operand2);break;
			case '-':if(Local_u32Operand1<Local_u32Operand2){
				CLCD_voidSendData('-');
				CLCD_voidSendNumber(Local_u32Operand2-Local_u32Operand1);
			}
			else{
				CLCD_voidSendNumber(Local_u32Operand1-Local_u32Operand2);}break;
			case '*':CLCD_voidSendNumber(Local_u32Operand1*Local_u32Operand2);break;
			case '/':CLCD_voidSendNumber(Local_u32Operand1/Local_u32Operand2);
			CLCD_voidSendData('.');
			CLCD_voidSendNumber(((Local_u32Operand1%Local_u32Operand2)*1000)/Local_u32Operand2);break;
			}
			Local_u8EndState=1;

		}
		else if(Local_u32Key=='r'){
			CLCD_voidSendCommand(1);
			Local_u32Operand1=0;
			Local_u32Operand2=0;
			Local_u32PosCounter=0;
			Local_u8OperatorState=0;
			Local_u8EndState=0;
			for(u8 Local_u8Iterator=0;Local_u8Iterator<20;Local_u8Iterator++){
				Local_u32OperandArr[Local_u8Iterator]=0;
			}
		}
		else if(Local_u32Key==0||Local_u32Key==1||Local_u32Key==2||Local_u32Key==3||Local_u32Key==4||Local_u32Key==5||Local_u32Key==6||Local_u32Key==7||Local_u32Key==8||Local_u32Key==9){
			if(Local_u8EndState==1){
				CLCD_voidSendCommand(1);
				Local_u32Operand1=0;
				Local_u32Operand2=0;
				Local_u32PosCounter=0;
				Local_u8OperatorState=0;
				Local_u8EndState=0;
				for(u8 Local_u8Iterator=0;Local_u8Iterator<20;Local_u8Iterator++){
					Local_u32OperandArr[Local_u8Iterator]=0;
				}
			}
			CLCD_voidSendNumber(Local_u32Key);
			Local_u32OperandArr[Local_u32PosCounter]=Local_u32Key;
			Local_u32PosCounter++;
		}

	}
}

u32 u32Power(u32 Copy_u32Base,s32 Copy_u32Exponent){
	u32 Local_u32Result=1;
	for(u32 i=0;i<Copy_u32Exponent;i++){
		Local_u32Result*=Copy_u32Base;
	}
	return Local_u32Result;
}
