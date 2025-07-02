/*
 * main.c
 *
 *  Created on: Nov 5, 2024
 *      Author: amany_Elsedawy
 *
 *Description:
 *     :A TWO-microcontroller system where the master reads temperature via ADC and
 * sends it over SPI. The slave receives the temperature and activates a DC motor if the temperature exceeds 50°C.
 */



// look main contain two code for 2 microcontroller
//code in first microcontroller as Master
/* code description:MC  work as master send temp from TEMP_SENSOR based on ADC to another MC by Communication protocol SPI*/
#define F_CPU 8000000UL
#include <util/delay.h>
#include "STD_TYPE.h"
#include "BIT_MAC_FUC.h"

//MCAL
#include"MDIO_Interface.h"
#include"MADC_Interfece.h"

#include"MSPI_Interface.h"


u16 Return_TempFromSensor(void);

int main(void){


	MDIO_Init();
	MADC_voidInit();
	MSPI_voidMasterInit();
	u8 Local_u8receivedData = 0;
	u8 bufferSize;             // Size of data to send
	u8 tempDigits[2];          // Array to hold each digit of the temperature

while(1){

 u16 Local_u16Tempture=Return_TempFromSensor();//how loop escape from read temp to next line?
u8 Local_u8Temp=(u8)Local_u16Tempture;

if (Local_u8Temp >= 10) {
            tempDigits[0] = (Local_u8Temp / 10) + '0';  // turn  digit as ASCII character
            tempDigits[1] = (Local_u8Temp % 10) + '0';
            bufferSize = 2;  // Two digits to send
        } else {
            tempDigits[0] = Local_u8Temp + '0';         // Single digit as ASCII
            bufferSize = 1;  // one digit to send
        }

        // Send each digit to the second microcontroller using SPI
        MSPI_u8BufferTranRecSynch(tempDigits, &Local_u8receivedData, bufferSize);
        _delay_ms(1000);


      }
return 0;
}
u16 Return_TempFromSensor(void){
	u16 Local_u16AnalogValue=0;//0 to 5000
	u16 Local_u16TempValue=0;
	u16 Local_u16DigitalValue=0;

     //read  temp sensor using synchronus
	//LM2 sensor code correct it as num>100
MADC_u8GetADCValueSynch(0,& Local_u16DigitalValue);

Local_u16AnalogValue=((u32)Local_u16DigitalValue*5000UL) / 1024;
	    Local_u16TempValue=(Local_u16AnalogValue / 10);

	     _delay_ms(500);

return  Local_u16TempValue;
}

//SECOND MICROCONTROLLER


//Code in SECOND microcontroller as SLAVE
/* code description:MC  work as slave recieve temp from another MC by Communication protocol SPI and if temp>50 turn DC Motor*/
#define F_CPU 8000000UL
#include <util/delay.h>
#include "STD_TYPE.h"
#include "BIT_MAC_FUC.h"

//MCAL
#include"MDIO_Interface.h"

#include"MSPI_Interface.h"
//HALL
#include"H_DCMInterface.h"



u8 stringToNumber(u8* str);
int main(void){


	MDIO_Init();

// init SPI as Slave
	MSPI_voidSlaveInit();
	u8 Local_u8SendData = 0;
	u8 Local_u8Temp=0;
	u8 Recive_tempDigits[2]={0};          // Array to hold each digit of the temperature

while(1){
//recieve temp from first microcontroller
	 // Clear the receive buffer before each transmission
 for (u8 i = 0; i < 2; i++) {
	  Recive_tempDigits[i] = 0; // Ensure the buffer is clear
	  }

MSPI_u8BufferTranRecSynch(&Local_u8SendData,Recive_tempDigits,2);//correct  it if i want to recieve tempfrpm one dight or two dight

 Local_u8Temp=stringToNumber((u8*)Recive_tempDigits);
if(Local_u8Temp>50){//if temp exceed 50 turn DC motor
  turn_DC_MotorCW();

}
_delay_ms(1000);
      }
return 0;
}
u8 stringToNumber(u8* str) {
    u8 num = 0;
    while (*str) {
        num = num * 10 + (*str - '0');
        str++;
    }
    return num;
}


