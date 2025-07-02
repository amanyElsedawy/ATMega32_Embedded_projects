/*
 * main.c
 *
 *  Created on: Oct 31, 2024
 *      Author:amany_Elsedawy
 *
 *Description:A Two-microcontroller system where one MCU reads an OCR value
 * from a keypad and sends it via UART to another MCU,
 * which then second MCU drives a buzzer using PWM tones based on the received value
 */
//code on first Microcontroller
//program to receive OCR value from user by Keypad and send to another microcontroller by UART Protocol
#define F_CPU 8000000UL
#include<util/delay.h>


//LIB Layer

#include"STD_TYPE.h"
#include"BIT_MAC_FUC.h"

//MCALL
#include"MDIO_Interface.h"
//#include"MTimer0_Intrface.h"
#include"UART_Interface.h"

//HALL
#include"HKPD_Interface.h"


void Receive_OCERFromKeypad_SendValByUART(void);
int main(void){
MDIO_Init();
//MTMR0_voidInit();
MUART_voidInit();

while(1){
	Receive_OCERFromKeypad_SendValByUART();

}



return 0;
}
//function that receive OCR value from user and send by UART
void Receive_OCERFromKeypad_SendValByUART(void){
u8  Local_u8PressVal;
u8 Local_OCRVal[4];//max digit is three+null terminal
u8 Local_index=0;
// Clear the buffer before starting
 for (u8 i = 0; i < 4; i++) {
        Local_OCRVal[i] = '\0';
    }

while(1){

	//recieve until user enter'='
HKPD_u8GetPressedKey(&Local_u8PressVal);
if(Local_u8PressVal!=HKPD_NoKeyPressed){//keypad get pressed
 if(Local_u8PressVal=='='){
	 Local_OCRVal[Local_index]='\0';
//send number enter to PUTY(TTL)by UART
	 _delay_ms(100);
      MUART_voidSynSendString((const u8*)Local_OCRVal);
      _delay_ms(100);

        break;
}
 else if(Local_index<3 && Local_u8PressVal >= '0' && Local_u8PressVal <= '9'){
     Local_OCRVal[Local_index]=Local_u8PressVal;
       Local_index++;

}

}
  _delay_ms(100);
}


}

// second code on second  Microcontroller
/*program to receive OCR value from another microcontroller by UART Protocol and turn Buzzer by pwm mode
  on  tones match with OCR Received */
#define F_CPU 8000000UL
#include<util/delay.h>


//LIB Layer

#include"STD_TYPE.h"
#include"BIT_MAC_FUC.h"

//MCALL
#include"MDIO_Interface.h"
#include"MTimer0_Intrface.h"
#include"UART_Interface.h"

//HALL
#include"HKPD_Interface.h"

u8 stringToNumber(u8* str);
void TurnBuzzeronRecTones(void);

int main(void){
MDIO_Init();
MTMR0_voidInit();
MUART_voidInit();

while(1){
	//received  constantly OCR value and turn Buzzer
 TurnBuzzeronRecTones();


}



return 0;
}
//function that receive OCR value from anoter microcontroler and turn buzzer on this tones
void TurnBuzzeronRecTones(void){
	//receive OCR Value by UART
	u8 Local_OCRValue[4];

MUART_voidSynReceiveString(Local_OCRValue);
//  turn OCR that received to REAl numbers
u8 i=0;
for (i = 0; i < 4; i++) {
       if (Local_OCRValue[i] == '\0') {
           break; // Stop at the null character
       }
   }
   Local_OCRValue[i] = '\0'; // Ensure null-termination

u8 number=stringToNumber((u8* )Local_OCRValue);
//turn buzzer on the tone by timer0->pwm_mode
 MTMR0_voidSetOCR0Value(number);


}
u8 stringToNumber(u8* str) {
    u8 num = 0;
    while (*str) {
        num = num * 10 + (*str - '0');
        str++;
    }
    return num;
}

