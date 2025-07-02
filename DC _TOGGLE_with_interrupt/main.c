/*
 * main.c
 *
 *  Created on: Sep 27, 2024
 *      Author: amanyElsedawy
 */




#define F_CPU 8000000UL
#include <util/delay.h>

//library layer
#include "STD_TYPE.h"
#include "BIT_MAC_FUC.h"
// MCAL
#include "MDIO_Interface.h"
//driverMCAl
#include"MGIE_Interface.h"
#include"MEXTI_Interface.h"
//HALL
#include"H_DCMInterface.h"
//ISR CODE
void tog_DC(void){


	static u8 local_u8flag=0;//use static to not deleted after go out from function
	if(local_u8flag==0){

		turn_DC_MotorCW();

		local_u8flag=1;

        //_delay_ms(100);


	}else{
	     turnOFF_DC_Motor();
	    //  turn_DC_MotorCCW();
		 local_u8flag=0;
		 //_delay_ms(100);



	}
}



int main(void){
	MDIO_Init();
    //set call back of EXTI INT0
	MEXTI_u8SetBack(MEXTI_INT0,&tog_DC);


	MEXTI_u8Enable(MEXTI_INT0,MEXTI_Falling_Edg);

	MGIE_enable_GI();



	while(1){






	}

	return 0;
}

