


#include "STD_TYPE.h"
#include "BIT_MAC_FUC.h"
//mcal
#include"MEXTI_Interface.h"
#include"MEXTI_Private.h"
#include"MEXTI_Config.h"
//array of pointers to function to be called from ISR
static void(*MEXTI_APEXTI[3])(void)={ NULL , NULL , NULL };
//enable extirnal ENI
//enable interrput
u8 MEXTI_u8Enable(u8 Copy_u8ExtINum,u8 Copy_u8IntSrc){//int_num,int_case

	u8 Local_u8ErrorState=STD_TYPE_OK;
	switch(Copy_u8ExtINum){

	case MEXTI_INT0:
		if(Copy_u8IntSrc== MEXTI_Falling_Edg ){
			//select falling edge
			CLR_BIT(Private_MCUCR,0);
			SET_BIT(Private_MCUCR,1);
			//enable INT0
			SET_BIT(Private_GICR,6);


		}
		else if(Copy_u8IntSrc== MEXTI_Raising_Edg ){
			//set raising edge
			SET_BIT(Private_MCUCR,0);
			SET_BIT(Private_MCUCR,1);
			//enable INT0
			SET_BIT(Private_GICR,6);
		}
		else if(Copy_u8IntSrc== MEXTI_Any_Logical_Change){
			//set any logic change
			CLR_BIT(Private_MCUCR,1);
			SET_BIT(Private_MCUCR,0);
			//enable INT0
			SET_BIT(Private_GICR,6);


		}else if(Copy_u8IntSrc== MEXTI_Low_Level){
			//set low level
			CLR_BIT(Private_MCUCR,0);
			CLR_BIT(Private_MCUCR,1);
			//enable INT0
			SET_BIT(Private_GICR,6);


		}

		else{
			Local_u8ErrorState=STD_TYPE_NOK;

		}


		break;
	case  MEXTI_INT1:
		if(Copy_u8IntSrc== MEXTI_Falling_Edg ){
			//select falling edge
			CLR_BIT(Private_MCUCR,2);
			SET_BIT(Private_MCUCR,3);
			//enable INT1
			SET_BIT(Private_GICR,7);


		}
		else if(Copy_u8IntSrc== MEXTI_Raising_Edg ){
			//set raising edge
			SET_BIT(Private_MCUCR,2);
			SET_BIT(Private_MCUCR,3);
			//enable INT1
			SET_BIT(Private_GICR,7);
		}
		else if(Copy_u8IntSrc== MEXTI_Any_Logical_Change){
			//set any logic change
			CLR_BIT(Private_MCUCR,3);
			SET_BIT(Private_MCUCR,2);
			//enable INT1
			SET_BIT(Private_GICR,7);


		}else if(Copy_u8IntSrc== MEXTI_Low_Level){
			//set low level
			CLR_BIT(Private_MCUCR,2);
			CLR_BIT(Private_MCUCR,3);
			//enable INT1
			SET_BIT(Private_GICR,7);


		}

		else{
			Local_u8ErrorState=STD_TYPE_NOK;

		}


		break;
	case  MEXTI_INT2:
		if(Copy_u8IntSrc== MEXTI_Falling_Edg){
			CLR_BIT(Private_MCUCSR,6);
			//enable INT2
			SET_BIT(Private_GICR,5);



		}else if(Copy_u8IntSrc== MEXTI_Raising_Edg){

			SET_BIT(Private_MCUCSR,6);
			//enable INT2
			SET_BIT(Private_GICR,5);
		}else{

			Local_u8ErrorState=STD_TYPE_NOK;
		}

		break;
	}



	return Local_u8ErrorState;


}

u8 MEXTI_u8DISEnable(u8 Copy_u8ExtINum){//take interrupt num
	u8 Local_u8ErrorState=STD_TYPE_OK;
	if(Copy_u8ExtINum>0 && Copy_u8ExtINum<2){
		switch(Copy_u8ExtINum){
		//clear bit
		case MEXTI_INT0:CLR_BIT(Private_GICR,6);break;
		case MEXTI_INT1:CLR_BIT(Private_GICR,7);break;
		case MEXTI_INT2:CLR_BIT(Private_GICR,5);break;

		}

	}
	return Local_u8ErrorState;



}
//back up function for 3 ISR

//implement for ISR INT0
void __vector_1(void)   __attribute__((signal));//attribute used  to not deleted by optimizer
void __vector_1(void){
	if( MEXTI_APEXTI[0]!= NULL){
		MEXTI_APEXTI[0]();//call global interrupt to function

	}
}



//implement for ISR INT1
void __vector_2(void)   __attribute__((signal));//attribute used  to not deleted by optimizer
void __vector_2(void){
	if(MEXTI_APEXTI[1]!=NULL){//can be written as this MEXTI_APEXTI[MEXTI_INT1]()
		MEXTI_APEXTI[1]();

	}
}

//implement for ISR INT2
void __vector_3(void)   __attribute__((signal));//attribute used  to not deleted by optimizer
void __vector_3(void){
	if(MEXTI_APEXTI[2]!=NULL){//can be writen as this MEXTI_APEXTI[MEXTI_INT1]()
		MEXTI_APEXTI[2]();

	}
}
u8 MEXTI_u8SetBack(u8 Copy_u8ExtINum,void(*Copy_PF)(void)){
	u8 Local_u8ErrorState=STD_TYPE_OK;
	//check for two input of function  Copy_u8ExtINum=0to 2 andCopy_u8ExtINum!=NULL at home
	if((Copy_u8ExtINum<=2) &&Copy_PF!=NULL){
		MEXTI_APEXTI[Copy_u8ExtINum]=Copy_PF;
	}else{
		Local_u8ErrorState=STD_TYPE_NOK;

	}


	return Local_u8ErrorState;


}
