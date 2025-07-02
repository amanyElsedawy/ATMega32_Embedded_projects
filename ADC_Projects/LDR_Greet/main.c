/*
 * main.c
 *
 *  Created on: Oct 10, 2024
 *      Author:amany_Elsedawy
 *      Description:
 * Program : indicate Day state morning or night by Using LDR Sensor that connected to the ADC (channel 0) AND
 * LCD Display :
 *    Good Morning" +  boy character
 *        and turns **off** the LED (on PORTB, PIN0).
 *    If it's night time :
 *       "Good Evening" + sleeping boy character
 *        and turns **on** the LED.
 */



#define F_CPU 8000000UL
#include <util/delay.h>
#include "STD_TYPE.h"
#include "BIT_MAC_FUC.h"

//MCAL
#include"MDIO_Interface.h"
#include"MADC_Interfece.h"

//HALL
#include"HLCD_Interface.h"
#include"HLCD_EXTRACHAR.h"

int main(void){
     u16 Local_u16DigitalValue;
	u16 Local_u16AnalogValue;//0 to 5000

	    //MGIE_enable_GI();
		MDIO_Init();
		MADC_voidInit();
        HLCD_void_Init();
	   while(1){
			MADC_u8GetADCValueSynch(0,&Local_u16DigitalValue);
			Local_u16AnalogValue=((u32)Local_u16DigitalValue*5000UL) / 1024;
          if(Local_u16AnalogValue<4761 && Local_u16AnalogValue>=283){
        	 //if it LDR darkness tur on led//v0=4761
              HLCD_CLEAR();
             MDIO_u8SetPinValue(MDIO_PORTB,MDIO_PIN_0,MDIO_PinLow);
             HLCD_SetCursor(1,0);
             HLCD_WriteStirng((const u8*)"Good Morning");

            HLCD_voidSendExtraChar2(2,4,HLCD_u8ExtraCharBOY);


}       else{
	       HLCD_CLEAR();
	       MDIO_u8SetPinValue(MDIO_PORTB,MDIO_PIN_0,MDIO_PinHigh);
	       HLCD_SetCursor(1,0);
	       HLCD_WriteStirng((const u8*)"Good evening");
           HLCD_voidSendExtraChar2(2,4,HLCD_u8ExtraCharSleepBOY);
}

          // Small delay to allow for stable readings
                  _delay_ms(100);

	   }


return 0;

}
