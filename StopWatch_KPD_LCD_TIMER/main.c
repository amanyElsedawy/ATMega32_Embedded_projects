/*
 * main.c
 *
 *  Created on: Oct 15, 2024
 *      Author: amany_Elsedawy
 *Description:
    Countdown Timer(Stop watch) Using Keypad & LCD &Timer0 (CTC Mode)
  This project implements a user-configurable countdown timer using:
  Keypad for time input(Hours : Minutes : Seconds)//as user enter HH:MM:SS then press = to start
  and can use symbol"+","-" for right/left cursor move
  LCD to display the countdown
  Timer0 in CTC mode to trigger the countdown every second
  Interrupts for precise timing without blocking main execution


 */

//delay library
#define F_CPU 8000000UL
#include <util/delay.h>
//library layer
#include"STD_TYPE.h"
#include"BIT_MAC_FUC.h"
//MCALL
#include"MDIO_Interface.h"
#include"MGIE_Interface.h"
#include"MTimer0_Intrface.h"

//HALL
#include"HKPD_Interface.h"
#include"HLCD_Interface.h"

void Get_Hour(void);
void Get_MINUTES(void);
void Get_SECOND(void);

void  count_down(void);

u8 Local_val;
u16 hour=0;
u16 min=0;
u16 sec=0;


int main(void){
MDIO_Init();
HLCD_void_Init();


//set  time on LCD  by Keypad
	 Get_Hour();
	 Get_MINUTES();
	 Get_SECOND();
	 //start count down stop watch by timer0 in CTC mode
//call global interrupt enable
     MGIE_enable_GI();
   //set call back function
	MTMR0_u8SetCallBackCTCMode(& count_down);
	 //start timer 0
	 MTMR0_voidInit();


	while(1){





	}



	return 0;
}
void Get_Hour(void){

	u8 Local_digitCount = 0;

while(1){
  HKPD_u8GetPressedKey(&Local_val);
  if(Local_val!=HKPD_NoKeyPressed && Local_val>='0'&& Local_val<='9'){
      _delay_ms(20);
	   if (Local_digitCount < 2) {  // Limit input to 2 digits
		   hour = hour * 10 + (Local_val - '0');
             HLCD_voidWriteChar(Local_val);
	                  Local_digitCount++;  // Increment digit counter
	              }


  }else if (Local_val == ':') {
      HLCD_voidWriteChar(Local_val);
      break;
  }else if(Local_val == '+'){// if press + will move cursor right position

	  moveCursorRight();

}else if(Local_val == '-'){// if press - will move cursor left position

	  moveCursorLeft();

}
}
}

//function to take minute
void Get_MINUTES(void){

	u8 Local_digitCount = 0;

while(1){
  HKPD_u8GetPressedKey(&Local_val);
  if(Local_val!=HKPD_NoKeyPressed && Local_val>='0'&& Local_val<='9'){
      _delay_ms(20);
	   if (Local_digitCount < 2) {  // Limit input to 2 digits
		   min = min * 10 + (Local_val - '0');
             HLCD_voidWriteChar(Local_val);
	                  Local_digitCount++;  // Increment digit counter
	              }


  }else if (Local_val == ':') {
      HLCD_voidWriteChar(Local_val);
      break;
  }else if(Local_val == '+'){

	  moveCursorRight();

}else if(Local_val == '-'){

	  moveCursorLeft();

}
}
}
// function to GET second
void Get_SECOND(void){

	u8 Local_digitCount = 0;

while(1){
  HKPD_u8GetPressedKey(&Local_val);
  if(Local_val!=HKPD_NoKeyPressed && Local_val>='0'&& Local_val<='9'){
      _delay_ms(20);
	   if (Local_digitCount < 2) {  // Limit input to 2 digits
		   sec = sec * 10 + (Local_val - '0');
             HLCD_voidWriteChar(Local_val);
	                  Local_digitCount++;  // Increment digit counter
	              }

//press it to start count down stop watch
  }else if (Local_val == '=') {
     // HLCD_voidWriteChar(Local_val);
      break;
  }
  else if(Local_val == '+'){

  	  moveCursorRight();

  }else if(Local_val == '-'){

  	  moveCursorLeft();

  }
}
}

//function that passed to ISR to count down

void    count_down(void){

if(sec>0){

 sec--;
}else if(min>0){

    min--;
   sec=59;
 }else if(hour>0){
    hour--;
    min=59;
    sec=59;

 }
HLCD_CLEAR();
HLCD_voidWriteNumbers(hour);
HLCD_voidWriteChar(':');
HLCD_voidWriteNumbers(min);
HLCD_voidWriteChar(':');
HLCD_voidWriteNumbers(sec);

	}



