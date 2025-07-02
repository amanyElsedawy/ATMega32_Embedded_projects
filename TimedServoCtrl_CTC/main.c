/*
 * main.c
 *
 *  Created on: Oct 21, 2024
 *      Author: amany_Elsedawy
 * Description:
 *
 * This project is automatic control of a Servo motor using Timer0 and Timer1
 *
 * - Timer1 is  to generate a PWM signal for the servo motor.
 * - Timer0 is used in CTC mode to create a timed interrupt every fixed interval.
 * - Inside the Timer0 ISR (callback function), the servo angle increases by 10 degrees every second.
 * - Once the angle exceeds 180°, it resets back to 0°.
 *
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

void servo(void);


volatile u16 Global_u16Counter=0;


int main(void){

MDIO_Init();
//call global interrput enable
MGIE_enable_GI();
MTMR1_voidInit_PMWServo(0);
//set call back function
MTMR0_u8SetCallBackCTCMode(&servo);
//start timer 0
MTMR0_voidInit();



while(1){




}


return 0;

}

//servo motor
void servo (void){
static u8 Global_angle=0;
	Global_u16Counter++;
	if(Global_u16Counter==10000){
		 Global_angle=Global_angle+10;

          if(Global_angle>180){
		       Global_angle=0;
          }
		        MTMR1_voidInit_PMWServo(Global_angle);
                 Global_u16Counter=0;
	}
	}




