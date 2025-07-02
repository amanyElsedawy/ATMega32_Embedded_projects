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
//#include"HLCD_EXTRACHAR.h"

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

// function to write numbers

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
//function to write char in arabic
void HLCD_voidSendExtraChar(u8 Copy_LineNb,u8 Copy_CharNb){
	u8 HLCD_u8ExtraChar[]={
			//type  name in arabic
	   0x00,0x00,0x00,0x00,0x03,0x12,0x1E,0x0C,//char  5ي
	   0x00,0x01,0x00,0x01,0x1F,0x00,0x00,0x00,	//char 4ن
	   0x04,0x04,0x04,0x04,0x04,0x00,0x00,0x00,//char  3ا
	   0x00,0x00,0x07,0x05,0x1F,0x00,0x00, 0x00,//char 2   م
	   0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00//  char 1أ*/

	};

u8 LOCAL_u8count=0;

//set Ac refer to CGRAM
HLCD_voidLcdWriteCmd(HLCD_CGRAM);
for (LOCAL_u8count=0;LOCAL_u8count<sizeof(HLCD_u8ExtraChar)/sizeof(HLCD_u8ExtraChar[0]);LOCAL_u8count++){
//save EXTRAchar in CGRAM
     HLCD_voidWriteChar(HLCD_u8ExtraChar[LOCAL_u8count]);
}
// BACK (AC) to DDRAM
// CALL CURSOR FUNCTION

HLCD_SetCursor( Copy_LineNb, Copy_CharNb);
//send char toDDRAM to DISPLAY
for(LOCAL_u8count=0;LOCAL_u8count<5;LOCAL_u8count++){
HLCD_voidWriteChar(LOCAL_u8count);

}
}


// function can display one character
// recall this function overwrite on postion zero
void HLCD_voidSendExtraChar2(u8 Copy_LineNb, u8 Copy_CharNb, u8 * Copy_pointer) {
    u8 LOCAL_u8count = 0;

    // Set the address counter to CGRAM in first postion
    HLCD_voidLcdWriteCmd(HLCD_CGRAM);

    // Write custom character data to CGRAM (8 bytes per character)
    for (LOCAL_u8count = 0; LOCAL_u8count < 8; LOCAL_u8count++) {
        // Save extra character pattern in CGRAM
        HLCD_voidWriteChar(Copy_pointer[LOCAL_u8count]);
    }

    // Move the cursor back to DDRAM
    HLCD_SetCursor(Copy_LineNb, Copy_CharNb);

    // Display the custom character stored in CGRAM (usually 0x00 to 0x07)
    HLCD_voidWriteChar(0);  //Send CGRAM at position 0//how it can display char if i not give it counter like this HLCD_voidWriteCha(LOCAL_u8count)?
}
/*
// Custom function to display a float on the LCD
void HLCD_voidWriteFloat(float number) {
    u16 int_part = (u16)number;               // Get the integer part
    float fraction_part = number - int_part;  // Get the fractional part
    fraction_part = fraction_part * 100;      // Shift fractional part two decimal places
    u16 fractional_part = (u16)round(fraction_part);  // Round to the nearest integer

    // Prepare a string to store the float representation
    char buffer[10];  // Buffer to hold formatted number

    // Format the float into a string
    sprintf(buffer, "%u.%02u", int_part, fractional_part);

    // Write each character to the LCD
    for (u8 i = 0; buffer[i] != '\0'; i++) {
        HLCD_voidWriteChar(buffer[i]);
    }
}
*/

/*
void HLCD_voidWriteFloat(float number) {
    // Step 1: Get the integer part of the number
    u16 int_part = (u16)number;

    // Step 2: Calculate the fractional part
    float fraction_part = (number - int_part) * 100;

    // Step 3: Round the fractional part manually
    if (fraction_part < 0) {
        fraction_part = -fraction_part; // In case of negative numbers, ensure the fraction is positive
    }
    u16 fractional_part = (u16)(fraction_part + 0.5); // Add 0.5 to round correctly

    // Step 4: Handle edge case where rounding causes fractional part to exceed 100 (like 1.995 rounding to 2.00)
    if (fractional_part >= 100) {
        fractional_part = 0;   // Set fractional part back to 0
        int_part += 1;         // Increment the integer part
    }

    // Step 5: Prepare a buffer for the integer and fractional parts (max 10 chars)
    char buffer[10];
    u8 i = 0;

    // Convert the integer part to characters and store in buffer
    u16 temp = int_part;
    do {
        buffer[i++] = (temp % 10) + '0';  // Extract least significant digit and convert to char
        temp /= 10;                        // Shift right
    } while (temp > 0);

    // Reverse the buffer to correct the order of the integer part
    u8 start = 0;
    u8 end = i - 1;
    while (start < end) {
        char temp_char = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp_char;
        start++;
        end--;
    }

    // Step 6: Add decimal point
    buffer[i++] = '.';

    // Step 7: Ensure the fractional part has exactly 2 digits
    if (fractional_part < 10) {
        buffer[i++] = '0';  // Add leading zero if the fractional part is less than 10
    }

    // Convert the fractional part to characters and store in buffer
    temp = fractional_part;
    do {
        buffer[i++] = (temp % 10) + '0';  // Extract least significant digit
        temp /= 10;
    } while (temp > 0);

    // Null-terminate the string
    buffer[i] = '\0';

    // Step 8: Write each character of the buffer to the LCD
    for (u8 j = 0; buffer[j] != '\0'; j++) {
        HLCD_voidWriteChar(buffer[j]);
    }
}


*/
void HLCD_VoidLcdWriteFloat(float Copy_f32Number)
{
    // Buffer to hold the final string to be displayed
    char buffer[20];
    int intPart = (int)Copy_f32Number;    // Extract the integer part
    int isNegative = 0;

    // Handle negative numbers
    if (Copy_f32Number < 0) {
        isNegative = 1;
        Copy_f32Number = -Copy_f32Number;  // Make the number positive
        intPart = -intPart;                // Convert integer part to positive
    }

    float fractionalPart = Copy_f32Number - (float)intPart;  // Extract the fractional part
    int decimalPart = (int)(fractionalPart * 100);           // Get two decimal places

    // Convert integer part to string
    HLCD_VoidLcdWriteInt(intPart);

    // Display decimal point
    HLCD_VoidLcdWriteChar('.');

    // Convert and display the decimal part (up to two decimal places)
    HLCD_VoidLcdWriteInt(decimalPart);
}

