/*
 * main.c
 *
 *  Created on: Sep 28, 2024
 *      Author: amany_Elsedawy
 *
 * Description:
 * A temperature monitoring system using the LM35 sensor
 * The temperature is read via ADC (asynchronously) and displayed on an LCD.
 * Uses interrupt-based ADC reading for efficient,OR by Synchronous ADC Reading (commented out).
 */




#define F_CPU 8000000UL
#include <util/delay.h>
#include "STD_TYPE.h"
#include "BIT_MAC_FUC.h"

//MCAL
#include"MDIO_Interface.h"
#include"MADC_Interfece.h"
#include"MGIE_Interface.h"
//Hall
#include"HLCD_Interface.h"

void APP_voidGetADCDigitalValue(u16 Copy_u16DigitalValue);
static  u16 APP_16ADCDigitalValue=0xFFFF;

int main(void){
	//u16 Local_u16DigitalValue=0;
	u16 Local_u16AnalogValue=0;//0 to 5000
    u16 local_u16TempValue=0;
    MGIE_enable_GI();
	MDIO_Init();
	MADC_voidInit();
    HLCD_void_Init();

while(1){
//read  temp sensor using synchronus
//LM2 sensor code correct it as num>100
	/*MADC_u8GetADCValueSynch(0,&Local_u16DigitalValue);
	 HLCD_SetCursor(HLCD_Line1,0);



	Local_u16AnalogValue=((u32)Local_u16DigitalValue*5000UL) / 1024;  //or (Local_u16DigitalValue*5000UL)or ((u32)Local_u16DigitalValue*5000)

    local_u16TempValue=(Local_u16AnalogValue / 10);
   // write votlage from 0 to 5000 on LCD by change value of voltage by potionemter
    HLCD_voidWriteNumbers(local_u16TempValue);
   //HLCD_voidLcdWriteNumber( local_u16TempValue);
     _delay_ms(500);
     HLCD_CLEAR();
      HLCD_SetCursor(HLCD_Line1,0);*/
//read temp sensor using asynchronus
    MADC_u8GetADCValueAsynch(0,&APP_voidGetADCDigitalValue);
      if(APP_16ADCDigitalValue!=0xFFFF){

    	  Local_u16AnalogValue=((u32)APP_16ADCDigitalValue*5000UL) / 1024;
    	      HLCD_SetCursor(HLCD_Line1,0);
    	      local_u16TempValue=(Local_u16AnalogValue/10);
    	     // write voltage from 0 to 5000 on LCD by change value of voltage by potionemter
    	      HLCD_voidWriteNumbers( local_u16TempValue);
    	       _delay_ms(1000);
    	       HLCD_CLEAR();
    	       HLCD_SetCursor(HLCD_Line1,0);
    	       APP_16ADCDigitalValue=0xFFFF;
      }

      }
return 0;
}



void APP_voidGetADCDigitalValue(u16 Copy_u16DigitalValue){
	 APP_16ADCDigitalValue=Copy_u16DigitalValue;

}
