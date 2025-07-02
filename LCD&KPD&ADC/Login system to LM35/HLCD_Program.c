// include library
#include"STD_TYPE.h"
#include"BIT_MAC_FUC.h"

#define F_CPU 8000000UL
#include<util/delay.h>
//MCAL
#include"MDIO_Interface.h"
//include HALL
#include"HLCD_Interface.h"
#include"HLCD_Private.h"
#include"HLCD_Config.h"

void HLCD_void_Init(void){
// delay
_delay_ms(31);
//send function set command
//0x38 as in data sheet
HLCD_voidLcdWriteCmd(0x38);
//delay
_delay_ms(40);
//send display on off control command as in data sheet
HLCD_voidLcdWriteCmd(0x0F);
//delay
_delay_ms(40);
//command for clear display
HLCD_voidLcdWriteCmd(0x01);
//delay
_delay_ms(2);
// send command entry mode set
HLCD_voidLcdWriteCmd(0x06);

}
void HLCD_voidLcdWriteCmd(u8 Copy_u8Cmd){
// RS pin equal zero-> select command reg
MDIO_u8SetPinValue(HLCD_RS_PORT,HLCD_RS_PIN,MDIO_PinLow);
//R/W pin equal zero->Write operation
MDIO_u8SetPinValue(HLCD_RW_PORT,HLCD_RW_PIN,MDIO_PinLow);
//enable pin equal high then//write command//then wait for required time then// enable pin equal low
MDIO_u8SetPinValue(HLCD_EN_PORT,HLCD_EN_PIN,MDIO_PinHigh);
MDIO_u8SetPortValue(HLCD_DATA_PORT,Copy_u8Cmd);
//wait
_delay_us(1);
//enable=low
MDIO_u8SetPinValue(HLCD_EN_PORT,HLCD_EN_PIN,MDIO_PinLow);

}



void HLCD_voidWriteChar(u8 Copy_u8Char){
	// RS pin equal zero-> select command reg
	MDIO_u8SetPinValue(HLCD_RS_PORT,HLCD_RS_PIN,MDIO_PinHigh);
	//R/W pin equal zero->Write operation
	MDIO_u8SetPinValue(HLCD_RW_PORT,HLCD_RW_PIN,MDIO_PinLow);
	//enable pin equal high then//write command//then wait for required time then// enable pin equal low
	MDIO_u8SetPinValue(HLCD_EN_PORT,HLCD_EN_PIN,MDIO_PinHigh);
	// write data
	MDIO_u8SetPortValue(HLCD_DATA_PORT,Copy_u8Char);
	//wait
	_delay_us(1);
	//enable=low
	MDIO_u8SetPinValue(HLCD_EN_PORT,HLCD_EN_PIN,MDIO_PinLow);

}
u8 HLCD_SetCursor(u8 Copy_LineNb,u8 Copy_CharNb){
 u8 Local_u8ErrorState=STD_TYPE_OK;
if(Copy_CharNb<40){
switch(Copy_LineNb){
case HLCD_Line1:
	HLCD_voidLcdWriteCmd(0x80+Copy_CharNb);

      break;
case HLCD_Line2:
	HLCD_voidLcdWriteCmd(0xC0+Copy_CharNb);
	    break;
default:
	Local_u8ErrorState=STD_TYPE_NOK;

}}else{
	Local_u8ErrorState=STD_TYPE_NOK;
}

 return Local_u8ErrorState;

}
// function to write string

void HLCD_WriteStirng(const u8 *Copy_u8PtrString){
 u8 string_count=0;
while(Copy_u8PtrString[string_count]!='\0'){
  HLCD_voidWriteChar(Copy_u8PtrString[string_count]);
  string_count++;
}
}
// function to clear
void HLCD_CLEAR(void){
	//command for clear display
	HLCD_voidLcdWriteCmd(HLCD_Clear);
	_delay_ms(2);

}


void HLCD_voidWriteNumbers(u16 Copy_u16Number) {
    // RS pin equal 1 -> select data register
    MDIO_u8SetPinValue(HLCD_RS_PORT, HLCD_RS_PIN, MDIO_PinHigh);
    // R/W pin equal 0 -> Write operation
    MDIO_u8SetPinValue(HLCD_RW_PORT, HLCD_RW_PIN, MDIO_PinLow);


    char arr[6];  // Max size for 5 digits + null-terminator (if needed)
    u8 i = 0;


    do {
        arr[i++] = (Copy_u16Number % 10) + '0';  // Convert to ASCII
        Copy_u16Number /= 10;
    } while (Copy_u16Number > 0);


    while (i > 0) {
        // Enable pin set to high
        MDIO_u8SetPinValue(HLCD_EN_PORT, HLCD_EN_PIN, MDIO_PinHigh);

        // Write the current character (from arr) to the LCD
        MDIO_u8SetPortValue(HLCD_DATA_PORT, arr[--i]);

        // Wait for LCD to process the data
        _delay_us(1);

        // Enable pin set to low
        MDIO_u8SetPinValue(HLCD_EN_PORT, HLCD_EN_PIN, MDIO_PinLow);

        // Small delay between each byte transfer
        _delay_us(1);
    }
}

