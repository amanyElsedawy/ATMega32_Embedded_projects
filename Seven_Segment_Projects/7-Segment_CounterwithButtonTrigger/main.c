
/*

  Author        : Amany_Elsedawy
  Description   :
  This code implements a simple counter that displays numbers
  from 0 to 9 on a 7-segment display connected to PORTB.
  Each time the user presses a button (connected to PA6),
  the counter increases by 1, and the corresponding number
  is shown on the 7-segment display.
  and  an LED (connected to PA7) lights up only
  when the button is pressed and the number is updating.
  It turns off when the button is released.*/
#include"BIT_MAC_FUC.h"
#include"STD_TYPE.h"
#include"MDIO_Interface.h"
#define F_CPU 8000000UL
#include<util/delay.h>
void display(void);
u8 count=0;
u8 Local_u8SwitchValue=1;
u8 prev_u8SwitchValue=1;
int main(void){
//function that set direction and value of DIO DRIVER
	 MDIO_Init();
while(1){
	 display();

}

	return 0;
}
void display(void){
#define zero  0b11000000
#define one   0b11111001
#define two   0b10100100
#define three 0b10110000
#define four  0b10011001
#define five  0b10010010
#define six   0b10000010
#define seven 0b11111000
#define eight 0b10000000
#define nine  0b10010000
// set an array for seven segment
unsigned int numbers[10]={zero,one,two,three,four,five,six,seven,eight,nine};

MDIO_u8GetPinValue(MDIO_PORTA,MDIO_PIN_6,& Local_u8SwitchValue);
if(prev_u8SwitchValue!=MDIO_PinLow && Local_u8SwitchValue==MDIO_PinLow){
  if(count<9){
    count++;}
MDIO_u8SetPortValue(MDIO_PORTB,numbers[count]);
//turn on led A7
MDIO_u8SetPinValue(MDIO_PORTA,MDIO_PIN_7,MDIO_PinHigh);
_delay_ms(50);

}
prev_u8SwitchValue=Local_u8SwitchValue;
if(Local_u8SwitchValue!=MDIO_PinLow && count!=9){
	//turn off led A7
	MDIO_u8SetPinValue(MDIO_PORTA,MDIO_PIN_7,MDIO_PinLow);

}

}
// Debouncing is handled using a small delay (50 ms).

