

/*
  owner:amany_Elsedawy
  version:4


   Description:

  This project is a motor control system that starts
  with a password login. The user enters a 4-digit password using a keypad ,
  user has a limited number of attempts (3) to enter the correct password.
  During input, each digit is masked and shown as a star (*) on the LCD for privacy.
  If the password is correct, a menu appears on the LCD allowing the user
  to control different types of motors: DC, Stepper, and Servo.

  Here's what the system can do:

    Password Protection:
      The system asks the user to enter a 4-digit password. Only if the
      password is correct, the user can access the motor controls.

    Motor Control Menu:
      After logging in, a menu appears on the LCD with four options:

      1. **DC Motor**
         - Rotate in clockwise (CW) or counter-clockwise (CCW) direction.
         - The motor runs for 3 seconds and then stops.

      2. **Stepper Motor**
         - The user enters an angle (from 0 to 360 degrees).
         - The motor rotates to that angle in CW or CCW as selected.
         - If the angle is invalid, an error message is shown.

      3. **Servo Motor**
         - The user inputs an angle between 0 and 180 degrees.
         - The servo motor moves to that angle.

      4. **Exit**
         - Returns to the password screen, ending the current session.

  Notes:

   All interactions happen through the keypad and LCD.
   The system ensures invalid inputs are handled gracefully.

 */



#define F_CPU 8000000UL
#include <util/delay.h>

#include "STD_TYPE.h"
#include "MDIO_Interface.h"
#include"MTimer_Intrface.h"
#include "HLCD_Interface.h"
#include "HKPD_Interface.h"
#include "H_DCMInterface.h"
#include "H_StepIntrface.h"


u8 Local_u8PressedKey;

void loginSystem(void);
void moveMotor(void);

int main(void) {
    MDIO_Init();       // Initialize the I/O pins
    HLCD_void_Init();  // Initialize the LCD

    while (1) {
        HLCD_CLEAR();
        loginSystem();     // Start the login system
    }

    return 0;
}

void loginSystem(void) {
    u8 CHECK_PASS = 1;
    u8 pass[4] = { '1', '2', '3', '4' };  // Predefined password
    u8 entered_pass[4];

    HLCD_WriteStirng((const u8*)"Enter PASSWORD");
    _delay_ms(2000);
    HLCD_CLEAR();

    // Loop for entering the password
    for (u8 i = 0; i < 4; i++) {
        do {
            HKPD_u8GetPressedKey(&Local_u8PressedKey);
        } while (Local_u8PressedKey == HKPD_NoKeyPressed);

        entered_pass[i] = Local_u8PressedKey;
        HLCD_voidWriteChar('*');  // Display a star for each digit
        _delay_ms(500);
    }

    // Check if entered password matches the predefined password
    for (u8 i = 0; i < 4; i++) {
        if (entered_pass[i] != pass[i]) {
            CHECK_PASS = 0;
            break;
        }
    }

    HLCD_CLEAR();
    if (CHECK_PASS) {
        HLCD_WriteStirng((const u8*)"Correct PASS");
        _delay_ms(2000);
        HLCD_CLEAR();
        moveMotor();  // Call motor control after correct password
    } else {
        HLCD_WriteStirng((const u8*)"Wrong PASS");
        _delay_ms(2000);
        HLCD_CLEAR();
    }
}

void moveMotor(void) {
    u8 exit_flag = 0;  // Flag to handle exit

    while (!exit_flag) {
        HLCD_CLEAR();
        HLCD_SetCursor(1, 0);
        HLCD_WriteStirng((const u8*)"1.DCMotor");
        HLCD_SetCursor(2, 0);
        HLCD_WriteStirng((const u8*)"2.Stepper");
        HLCD_SetCursor(1, 9);
        HLCD_WriteStirng((const u8*)"3.SERVO");
        HLCD_SetCursor(2, 9);
        HLCD_WriteStirng((const u8*)"4.EXIT");

        do {
            HKPD_u8GetPressedKey(&Local_u8PressedKey);
        } while (Local_u8PressedKey == HKPD_NoKeyPressed);

        // Control DC Motor
        if (Local_u8PressedKey == '1') {
            HLCD_CLEAR();
            HLCD_SetCursor(1, 0);
            HLCD_WriteStirng((const u8*)"1.CW");
            HLCD_SetCursor(2, 0);
            HLCD_WriteStirng((const u8*)"2.CCW");

            do {
                HKPD_u8GetPressedKey(&Local_u8PressedKey);
            } while (Local_u8PressedKey == HKPD_NoKeyPressed);

            if (Local_u8PressedKey == '1') {
                HLCD_CLEAR();
                HLCD_WriteStirng((const u8*)"DC_Motor_CW");
                turn_DC_MotorCW();  // Turn DC motor clockwise
                _delay_ms(3000);  // Run motor for 3 seconds
                turnOFF_DC_Motor();
            } else if (Local_u8PressedKey == '2') {
                HLCD_CLEAR();
                HLCD_WriteStirng((const u8*)"DC_Motor_CCW");
                turn_DC_MotorCCW();  // Turn DC motor counterclockwise
                _delay_ms(3000);  // Run motor for 3 seconds
                turnOFF_DC_Motor();
            }
            _delay_ms(1000);
        }

        // Control Stepper Motor
        else if (Local_u8PressedKey == '2') {
            HLCD_CLEAR();
            HLCD_SetCursor(1, 0);
            HLCD_WriteStirng((const u8*)"Stepper Angle:");

            u16 angle = 0;
            u8 digit_count = 0;

            // Get angle input from the user
            while (digit_count < 3) {
                do {
                    HKPD_u8GetPressedKey(&Local_u8PressedKey);
                } while (Local_u8PressedKey == HKPD_NoKeyPressed);
                if(Local_u8PressedKey =='='){
                                 break;

                }



                else if (Local_u8PressedKey >= '0' && Local_u8PressedKey <= '9') {
                    angle = angle * 10 + (Local_u8PressedKey - '0');
                    HLCD_voidWriteChar(Local_u8PressedKey);  // Display digit
                    digit_count++;
                }

                if (angle > 360) {
                    HLCD_CLEAR();
                    HLCD_WriteStirng((const u8*)"Invalid Angle");
                    _delay_ms(1000);
                    HLCD_CLEAR();
                    return;
                }
            }

            HLCD_CLEAR();
            HLCD_SetCursor(1, 0);
            HLCD_WriteStirng((const u8*)"1.CW");
            HLCD_SetCursor(2, 0);
            HLCD_WriteStirng((const u8*)"2.CCW");

            do {
                HKPD_u8GetPressedKey(&Local_u8PressedKey);
            } while (Local_u8PressedKey == HKPD_NoKeyPressed);

            if (Local_u8PressedKey == '1') {
                Stepper_MotorMove(1, angle);  // Move stepper CW
            } else if (Local_u8PressedKey == '2') {
                Stepper_MotorMove(2, angle);  // Move stepper CCW
            }
            _delay_ms(1000);
        }

        // Control Servo Motor
        else if (Local_u8PressedKey == '3') {
            HLCD_CLEAR();
            HLCD_WriteStirng((const u8*)"Servo Angle:");
            u16 angle = 0;
            u8 digit_count = 0;

            // Get angle input from the user
            while (digit_count < 3) {
                do {
                    HKPD_u8GetPressedKey(&Local_u8PressedKey);
                } while (Local_u8PressedKey == HKPD_NoKeyPressed);
             if(Local_u8PressedKey =='='){
                 break;

}

             else if (Local_u8PressedKey >= '0' && Local_u8PressedKey <= '9') {
                    angle = angle * 10 + (Local_u8PressedKey - '0');
                    HLCD_voidWriteChar(Local_u8PressedKey);
                    digit_count++;
                }

                if (angle > 180) {
                    HLCD_CLEAR();
                    HLCD_WriteStirng((const u8*)"Invalid Angle");
                    _delay_ms(1000);
                    HLCD_CLEAR();
                    return;
                }
            }

            MTMR1_voidInit_PMWServo(angle);  // Move servo to the angle
            _delay_ms(1000);
        }

        // Exit motor control
        else if (Local_u8PressedKey == '4') {
            exit_flag = 1;
        }
    }
}
