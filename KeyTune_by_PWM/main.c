/*
 * main.c
 *
 *  Created on: Oct 18, 2024
 *      Author: amany_Elsedawy
 *
 * Description:
 *project that turns a keypad into a piano.
 * When a user presses a key on the keypad, the buzzer generates a specific tone by adjusting
 * the PWM signal (OCR0 value) from Timer0.
 */
#define F_CPU 8000000UL
#include<util/delay.h>
#include"BIT_MAC_FUC.h"
#include"STD_TYPE.h"
#include"MDIO_Interface.h"
#include"MTimer0_Intrface.h"
#include"HKPD_Interface.h"
void Keypad_piano(void);
int main(void){

	MDIO_Init();
	MTMR0_voidInit();


while(1){

	 Keypad_piano();



}

return 0;
}
// i want keypad always take num that turn buzzer in different tone
void Keypad_piano(void){
	u8 Local_u8PressesKey;
	static u8  Local_u8OCR0Value=0;

	HKPD_u8GetPressedKey(&Local_u8PressesKey);
	 if(Local_u8PressesKey!=HKPD_NoKeyPressed){
		 switch (Local_u8PressesKey) {
		             case '1':
		                 Local_u8OCR0Value = 200;/// 50% duty cycle for key '1'
		                 MTMR0_voidSetOCR0Value(Local_u8OCR0Value);
		                 break;

		             case '2':
		                 Local_u8OCR0Value = 51;   // 25% duty cycle for key '2'
		                 MTMR0_voidSetOCR0Value(Local_u8OCR0Value);
		                 break;

		             case '3':
		                 Local_u8OCR0Value = 102;  // 70% duty cycle for key '3'
		                 MTMR0_voidSetOCR0Value(Local_u8OCR0Value);
		                 break;

		             case '4':  // Changed from '1' to '4' to avoid redundancy
		                 Local_u8OCR0Value = 30;  // Custom duty cycle for key '4'
		                 MTMR0_voidSetOCR0Value(Local_u8OCR0Value);
		                 break;
		             case '5':  // Changed from '1' to '4' to avoid redundancy
		            		     Local_u8OCR0Value = 188;  // Custom duty cycle for key '4'
		            		       MTMR0_voidSetOCR0Value(Local_u8OCR0Value);
		            		         break;

		             default:
		                 // Handle invalid input, if necessary
		                 break;
		         }
		 _delay_ms(100);


	 }
}
