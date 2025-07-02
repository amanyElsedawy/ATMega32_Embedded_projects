/*
 * main.c
 *
 *  Created on: Sep 28, 2024
 *      Author: amany_Elsedawy
 * Description:
 *   fun project that reads analog input  from a potentiometer
 * and moves a custom character (boy) across an LCD
 * The position is calculated based on the ADC value (0–1023), scaled to the 16-character LCD width.
 */



#define F_CPU 8000000UL
#include <util/delay.h>
//library

#include "STD_TYPE.h"
#include "BIT_MAC_FUC.h"

//MCALL
#include"MDIO_Interface.h"
#include"MADC_Interfece.h"

//HAll
#include"HLCD_Interface.h"
#include"HLCD_EXTRACHAR.h"

int main(void){
	u16 Local_u16DigitalValue;
	//u16 Local_u16AnalogValue;//0 to 5000
	u8 boy_position=0;

	MDIO_Init();
	MADC_voidInit();
    HLCD_void_Init();

while(1){
//read digital value
	//HLCD_WriteStirng((const u8*)"hello");
	MADC_u8GetADCValue(0,&Local_u16DigitalValue);
	//Local_u16AnalogValue=((u32)Local_u16DigitalValue*5000UL) / 1024;  //or (Local_u16DigitalValue*5000UL)or ((u32)Local_u16DigitalValue*5000)
    boy_position=(Local_u16DigitalValue*16)/1024;
    HLCD_voidSendExtraChar2(HLCD_Line1, boy_position,HLCD_u8ExtraCharBOY);
    _delay_ms(100);
     HLCD_CLEAR();


}
  return 0;

}
