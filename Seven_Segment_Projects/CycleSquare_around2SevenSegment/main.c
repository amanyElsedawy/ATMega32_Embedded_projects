// Description   :
 /*This program controls 8 LED of 2 seven segments connected to PORTB
  of  microcontroller . It allows the user to cycle through the LEDs in clockwise or counterclockwise
  direction using two push buttons connected to PORTA pins.
 */
#include"STD_TYPE.h"
#include"BIT_MAC_FUC.h"
#include"MDIO_Interface.h"
#define F_CPU 8000000UL
#include<util/delay.h>
void clockwise(void);
void unclockwise(void);
void handle_2switches(void);
void chosse_case(void);
u8 count =0;
u8 prev1=1,prev2=1;
u8 Local_u8SwitchValue1=1;
u8 Local_u8SwitchValue2=1;

int main(void){
 MDIO_Init();
while(1){

 chosse_case();
}


return 0;
}
void clockwise(void){
#define a1  0
#define b1  1
#define c1  2
#define d1  3
#define d2  4
#define e2  5
#define f2  6
#define a2  7
unsigned int segments[8] = {a1, b1, c1, d1, d2, e2, f2, a2};
MDIO_u8SetPortValue(MDIO_PORTB,~(1 << segments[count])); // Display the current segment

      _delay_ms(500);  // Delay for visibility
   count++;
   if (count >= 8) {
       count = 0;  // Wrap around the array if reaching the end
   }


}
void unclockwise(void){
#define a1  0
#define b1  1
#define c1  2
#define d1  3
#define d2  4
#define e2  5
#define f2  6
#define a2  7
unsigned int segments[8] = {a1, b1, c1, d1, d2, e2, f2, a2};

if (count == 0) {
       count = 7;  // Wrap around the array if reaching the beginning
   } else {
       count--;
   }
MDIO_u8SetPortValue(MDIO_PORTB,~(1 << segments[count])); // Display the current segment

         _delay_ms(500);  // Delay for visibility

}

void handle_2switches(void) {

    MDIO_u8SetPortValue(MDIO_PORTB,MDIO_PinLow);

}
void chosse_case(void){

MDIO_u8GetPinValue(MDIO_PORTA,MDIO_PIN_7,&Local_u8SwitchValue1);
MDIO_u8GetPinValue(MDIO_PORTA,MDIO_PIN_6,&Local_u8SwitchValue2);
if(Local_u8SwitchValue1==MDIO_PinLow && prev2!=MDIO_PinLow){
	 clockwise();
}else if(Local_u8SwitchValue2==MDIO_PinLow && prev1!=MDIO_PinLow){
	 unclockwise();
}else if(Local_u8SwitchValue1==MDIO_PinLow && Local_u8SwitchValue2==MDIO_PinLow){
	handle_2switches();

}
prev1=Local_u8SwitchValue1;
prev2=Local_u8SwitchValue2;
_delay_ms(200);

}
