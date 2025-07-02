
/*
 * main.c
 *
 *  Created on: Sep 19, 2024
 *      Author: amany_Elsedawy
 */

#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdio.h>

#include "STD_TYPE.h"
#include "BIT_MAC_FUC.h"
// MCAL
#include "MDIO_Interface.h"
// HAL
#include "HLCD_Interface.h"
#include "HKPD_Interface.h"

void GETNUM1OP(void);
void GETNUM2eq(void);
float perform_operation(u16 num1, u16 num2, char operator);
void HLCD_voidWriteFloat(float number);  // Declare the function
u16 num1 = 0;
u16 num2 = 0;
char operator = '0';
u8 Local_val;
//u8 errorFlag = 0;  // Error flag

int main(void) {
    MDIO_Init();
    HLCD_void_Init();

    // Loop to keep the calculator running after each operation
    while (1) {
        GETNUM1OP();
        GETNUM2eq();

        float result = perform_operation(num1, num2, operator);
// we need if num2 =0 not display any number just display an ERROR   cause if it display number it display ERROE.00
        if (/*!errorFlag*/num2!=0) {
            if(operator=='/'){

        	// Only display the result if there's no error

             HLCD_voidWriteFloat(result);  // Display the float result
          }else{
              HLCD_voidWriteNumbers(result);
          }
        }
        _delay_ms(2000);
        HLCD_CLEAR();

        num1 = 0;
        num2 = 0;
        operator = '0';
       // errorFlag = 0;  // Reset the error flag
    }

    return 0;
}

// Function to get the first number and operator
void GETNUM1OP(void) {
    // Read key input
    while (1) {
        HKPD_u8GetPressedKey(&Local_val);
        if (Local_val != HKPD_NoKeyPressed && Local_val >= '0' && Local_val <= '9') {
            _delay_ms(20);
            num1 = num1 * 10 + (Local_val - '0');
            HLCD_voidWriteChar(Local_val);
        } else if (Local_val == '+' || Local_val == '-' || Local_val == '*' || Local_val == '/') {
            operator = Local_val;
            HLCD_voidWriteChar(Local_val);
            break;
        }
    }
}

// Function to get the second number and calculate the result
void GETNUM2eq(void) {
    while (1) {
        HKPD_u8GetPressedKey(&Local_val);
        if (Local_val != HKPD_NoKeyPressed && Local_val >= '0' && Local_val <= '9') {
            _delay_ms(20);
            num2 = num2 * 10 + (Local_val - '0');
            HLCD_voidWriteChar(Local_val);
        } else if (Local_val == '=') {
            HLCD_voidWriteChar(Local_val);
            break;
        }
    }
}

// Function to perform the arithmetic operation
float perform_operation(u16 num1, u16 num2, char operator) {
    switch (operator) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 != 0) {
                return (float)num1 / (float)num2;
            } else {
                HLCD_WriteStirng((const u8*)"ERROR");
                //errorFlag = 1;  // Set error flag
                return 0;  // Return 0 but it will not be displayed
            }
        default:
            return 0;
    }
}
