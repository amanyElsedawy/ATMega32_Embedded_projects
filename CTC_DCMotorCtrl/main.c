/*
 * main.c
 *
 *  Created on: Oct 5, 2024
 *      Author: amany_Elsedawy
 * Description:
 * ------------
 *  project control  DC motor using Timer0 in CTC mode,
 * with precise period-based control for each motor state.
 * The motor  cycles through 3 timed states:
 *
 *   1. **Clockwise (CW)** rotation for 5 seconds
 *   2. **Counter-Clockwise (CCW)** rotation for 3 seconds
 *   3. **Stop** for 5 seconds
 */


#define F_CPU 8000000UL
#include<util/delay.h>

//Lib  Layer

#include "STD_TYPE.h"
#include "BIT_MAC_FUC.h"
//mcal
#include "MDIO_Interface.h"
#include "MGIE_Interface.h"
#include "MTimer0_Intrface.h"
//Hall
#include"H_DCMInterface.h"
 volatile  u16 Local_u16Counter=0 ;



volatile u8 state = 0;  // State for the DC motor control

void DC_MOTOR(void);
int main(void){

	MDIO_Init();
turn_DC_MotorCW();//start  with clock wise as i start function after5sec to turn CCW
MGIE_enable_GI();
//set call back function
MTMR0_u8SetCallBackCTCMode(&DC_MOTOR);
//start timer 0
MTMR0_voidInit();
while(1){




}


return 0;

}

//function for ctc  mode
//turn dc clock wise for 5 sec then counterclockwise for 3sec then turn off for 5 sec
void DC_MOTOR(void){
	  Local_u16Counter++ ;


switch(state){//error in this line

   case 0:
    if( Local_u16Counter>=50000){
       //turnOFF_DC_Motor();
         turn_DC_MotorCCW();
         Local_u16Counter=0;
          state = 1;

}
     break;
  case 1:
     if( Local_u16Counter>=30000){
        turnOFF_DC_Motor();
        Local_u16Counter=0;
        state = 2;

}
     break;
  case 2:
     if( Local_u16Counter>=50000){
        turn_DC_MotorCW();

       Local_u16Counter=0;
       state = 0;
}
    break;

}



}



