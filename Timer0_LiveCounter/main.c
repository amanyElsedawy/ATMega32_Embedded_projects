/*
 * main.c
 *
 *  Created on: Oct 14, 2024
 *      Author: amany_Elsedawy
 * Description:
 *This project implements a simple digital counter using Timer0 in Normal Mode on AVR.
 *
 *Timer0 runs in Normal Mode (overflow mode).
 *  Overflow count + current TCNT0 value are used to compute an accurate count.
 *  Result is continuously displayed on the LCD.
 *  Uses global interrupts and tracks overflows using a global variable.
 */




#define F_CPU 8000000UL
#include<util/delay.h>

//Lib  Layer

#include "STD_TYPE.h"
#include "BIT_MAC_FUC.h"



//MCALL
#include"MDIO_Interface.h"
#include "MGIE_Interface.h"
#include"MTimer0_Intrface.h"
#include"MTimer0_Private.h"
//HALL
#include"HLCD_Interface.h"


int main(void){
MDIO_Init();
HLCD_void_Init();
MGIE_enable_GI();
MTMR0_voidInit();
u16 Local_u16Count;





while(1){
	 // _delay_ms(100);
	  HLCD_SetCursor(1,0);

if(private_TCNT0>0 ||Global_u16OverflowCount>0){
	Local_u16Count=((256*Global_u16OverflowCount)+private_TCNT0-1);
    HLCD_voidWriteNumbers(Local_u16Count);
    //_delay_ms(200);
}else{
	  HLCD_voidWriteNumbers(0);
	 // _delay_ms(200);
}



}

 return 0;
}
