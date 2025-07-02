
#define F_CPU 8000000UL
#include<util/delay.h>
// include library
#include"STD_TYPE.h"
#include"BIT_MAC_FUC.h"
//MCAL
#include"MDIO_Interface.h"
//HALL
#include "H_StepIntrface.h"
#include"H_StepPrivate.h"
#include"H_StepConfig.h"

void Stepper_MotorMove(u8 direc,u16 angle){
	 u16 n_step=( angle*2048UL)/360;
	 u16 n_iteration=(n_step/4);
//to move 360 degree need to step 2048 steps

switch(direc){
   case 1:
	//move clockwise

// move stepper motor stpes=number of iteration to move as the input degree
      for(u16 i=0;i<n_iteration;i++){
         MDIO_u8SetPinValue(Step_ULN1_port,Step_ULN1_pin,MDIO_PinLow);
         MDIO_u8SetPinValue(Step_ULN2_port,Step_ULN2_pin,MDIO_PinHigh);
         MDIO_u8SetPinValue(Step_ULN3_port,Step_ULN3_pin,MDIO_PinHigh);
         MDIO_u8SetPinValue(Step_ULN4_port,Step_ULN4_pin,MDIO_PinHigh);
         _delay_ms(10);
         //step2
         MDIO_u8SetPinValue(Step_ULN1_port,Step_ULN1_pin,MDIO_PinHigh);
         MDIO_u8SetPinValue(Step_ULN2_port,Step_ULN2_pin,MDIO_PinLow);
         MDIO_u8SetPinValue(Step_ULN3_port,Step_ULN3_pin,MDIO_PinHigh);
         MDIO_u8SetPinValue(Step_ULN4_port,Step_ULN4_pin,MDIO_PinHigh);

         _delay_ms(10);
                 //step3
         MDIO_u8SetPinValue(Step_ULN1_port,Step_ULN1_pin,MDIO_PinHigh);
         MDIO_u8SetPinValue(Step_ULN2_port,Step_ULN2_pin,MDIO_PinHigh);
         MDIO_u8SetPinValue(Step_ULN3_port,Step_ULN3_pin,MDIO_PinLow);
         MDIO_u8SetPinValue(Step_ULN4_port,Step_ULN4_pin,MDIO_PinHigh);
         _delay_ms(10);
                         //step4
         MDIO_u8SetPinValue(Step_ULN1_port,Step_ULN1_pin,MDIO_PinHigh);
         MDIO_u8SetPinValue(Step_ULN2_port,Step_ULN2_pin,MDIO_PinHigh);
         MDIO_u8SetPinValue(Step_ULN3_port,Step_ULN3_pin,MDIO_PinHigh);
         MDIO_u8SetPinValue(Step_ULN4_port,Step_ULN4_pin,MDIO_PinLow);
         _delay_ms(10);

}
break;
   case 2:
	//move underclockwise

	// move stepper motor stpes=number of iteration
	      for(u16 i=0;i<n_iteration;i++){
	         MDIO_u8SetPinValue(Step_ULN1_port,Step_ULN1_pin,MDIO_PinHigh);
	         MDIO_u8SetPinValue(Step_ULN2_port,Step_ULN2_pin,MDIO_PinHigh);
	         MDIO_u8SetPinValue(Step_ULN3_port,Step_ULN3_pin,MDIO_PinHigh);
	         MDIO_u8SetPinValue(Step_ULN4_port,Step_ULN4_pin,MDIO_PinLow);
	         _delay_ms(10);
	         //step2
	         MDIO_u8SetPinValue(Step_ULN1_port,Step_ULN1_pin,MDIO_PinHigh);
	         MDIO_u8SetPinValue(Step_ULN2_port,Step_ULN2_pin,MDIO_PinHigh);
	         MDIO_u8SetPinValue(Step_ULN3_port,Step_ULN3_pin,MDIO_PinLow);
	         MDIO_u8SetPinValue(Step_ULN4_port,Step_ULN4_pin,MDIO_PinHigh);

	         _delay_ms(10);
	                 //step3
	         MDIO_u8SetPinValue(Step_ULN1_port,Step_ULN1_pin,MDIO_PinHigh);
	         MDIO_u8SetPinValue(Step_ULN2_port,Step_ULN2_pin,MDIO_PinLow);
	         MDIO_u8SetPinValue(Step_ULN3_port,Step_ULN3_pin,MDIO_PinHigh);
	         MDIO_u8SetPinValue(Step_ULN4_port,Step_ULN4_pin,MDIO_PinHigh);
	         _delay_ms(10);
	                         //step4
	         MDIO_u8SetPinValue(Step_ULN1_port,Step_ULN1_pin,MDIO_PinLow);
	         MDIO_u8SetPinValue(Step_ULN2_port,Step_ULN2_pin,MDIO_PinHigh);
	         MDIO_u8SetPinValue(Step_ULN3_port,Step_ULN3_pin,MDIO_PinHigh);
	         MDIO_u8SetPinValue(Step_ULN4_port,Step_ULN4_pin,MDIO_PinHigh);
	         _delay_ms(10);
}
	break;

}

}
