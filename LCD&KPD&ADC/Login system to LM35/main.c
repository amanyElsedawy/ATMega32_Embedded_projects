/*
 * main.c
 *
 *  Created on: Oct 10, 2024
 *      Author: amany_Elsedawy
 *
 *Description:
 *This project implements a login-protected temperature monitoring system
 *using the LM35 analog temperature sensor, LCD, and a keypad Using ADC.
 *After Correct login, a simple menu is displayed:
 *     1. View temperature using the LM35 sensor
 *     2. Exit and return to the login screen
 *  If the user selects LM35:
 *     - The system continuously reads analog voltage from the sensor (via ADC).
 *     - It calculates the temperature in Celsius Degree.
 *     - The temperature is updated every second and shown on the LCD.
 *     - The user can press '1' to go back to the main menu.
 *
 *
 *
 */


#define F_CPU 8000000UL
#include<util/delay.h>

#include"STD_TYPE.h"
#include"BIT_MAC_FUC.h"
//MCAL
#include"MDIO_Interface.h"
#include"MADC_Interfece.h"
//HALL
#include"HLCD_Interface.h"
#include"HKPD_Interface.h"


u16 Local_u16DigitalValue=0;
u16 Local_u16AnalogValue=0;
u16 local_u16TempValue=0;

u8 Local_u8PressedKey;
void loginSystem(void);
void LM35(void);


int main(void){
    MDIO_Init();
	MADC_voidInit();
    HLCD_void_Init();


while(1){
 loginSystem();

}

return 0;
}

void loginSystem(void){
u8 CHECK_PASS =0;
u8 pass[4]={'1','2','3','4'};

HLCD_WriteStirng((const u8*)"Enter PASSWORD");
_delay_ms(1000);
HLCD_CLEAR();
// loop to try enter password for 3 time
for(u8 attemp=0;attemp<3;attemp++){
	CHECK_PASS =1;
	// to loop to enter pass consist of 4 number
for(u8 i=0;i<4;i++){

	 do {//get until pressed
	       HKPD_u8GetPressedKey(&Local_u8PressedKey);
	    } while (Local_u8PressedKey == HKPD_NoKeyPressed);
	   HLCD_voidWriteChar('*');
	   _delay_ms(200);
	  //check if each pressed key==each number in password
     if(Local_u8PressedKey!=pass[i]){
          CHECK_PASS=0;
          //break;


     }

}
_delay_ms(500);
	HLCD_CLEAR();

if( CHECK_PASS==1){
//turn on green led on port b pin0
MDIO_u8SetPinValue(MDIO_PORTD,MDIO_PIN_6,MDIO_PinHigh);
//display pass is correct onLCD
HLCD_WriteStirng((const u8*)"CORRECT PASS");
_delay_ms(2000);
//after2 second clear LCD and turn off green led
HLCD_CLEAR();
MDIO_u8SetPinValue(MDIO_PORTD,MDIO_PIN_6,MDIO_PinLow);
HLCD_WriteStirng((const u8*)"Welcome to LM35 ");
_delay_ms(3000);
HLCD_CLEAR();
//go out from loop

 LM35();
return ;

}else{
	if(attemp<2){
	MDIO_u8SetPinValue(MDIO_PORTD,MDIO_PIN_7,MDIO_PinHigh);
    HLCD_WriteStirng((const u8*)"Try again");
	_delay_ms(600);
	MDIO_u8SetPinValue(MDIO_PORTD,MDIO_PIN_7,MDIO_PinLow);
	HLCD_CLEAR();}
}
}
// if user enter password incorrect for 3 time
//display valid and turn on red led
HLCD_WriteStirng((const u8*)"INVALID TRY");
MDIO_u8SetPinValue(MDIO_PORTD,MDIO_PIN_7,MDIO_PinHigh);
_delay_ms(2000);
//after2 second clear LCD and turn off red led
HLCD_CLEAR();
MDIO_u8SetPinValue(MDIO_PORTD,MDIO_PIN_7,MDIO_PinLow);

}


//function to turn motor
void LM35(void){


HLCD_CLEAR();
HLCD_SetCursor(1,0);
HLCD_WriteStirng((const u8*)"1.LM35");
HLCD_SetCursor(2,0);
HLCD_WriteStirng((const u8*)"2.Exit");


do {//get until pressed
	       HKPD_u8GetPressedKey(&Local_u8PressedKey);
	    } while (Local_u8PressedKey == HKPD_NoKeyPressed);

if(Local_u8PressedKey=='1'){
	HLCD_CLEAR();
	HLCD_SetCursor(1,0);

while(1){
    		    //turn LM35 sensor
    		     MADC_u8GetADCValueSynch(0,&Local_u16DigitalValue);
    		 	 HLCD_SetCursor(HLCD_Line1,0);
                 Local_u16AnalogValue=((u32)Local_u16DigitalValue*5000UL) / 1024;  //or (Local_u16DigitalValue*5000UL)or ((u32)Local_u16DigitalValue*5000)
                 local_u16TempValue=(Local_u16AnalogValue / 10);
                 HLCD_SetCursor(1,0);
    		    // write votlage from 0 to 5000 on LCD by change value of voltage by potionemter
    		     HLCD_voidWriteNumbers(local_u16TempValue);
                 HLCD_SetCursor(HLCD_Line2,0);
    		     HLCD_WriteStirng((const u8*)"1.Back");

    		      _delay_ms(1000);


    		      HLCD_CLEAR();
    		       HLCD_SetCursor(HLCD_Line1,0);

    		     HKPD_u8GetPressedKey(&Local_u8PressedKey);

                 if(Local_u8PressedKey=='1'){
                	 HLCD_CLEAR();
                      return;

}

   }
}
else if(Local_u8PressedKey=='2'){
    	  HLCD_CLEAR();

          loginSystem();
    }


}



