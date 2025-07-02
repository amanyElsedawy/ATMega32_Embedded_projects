/*******NAME:       Amany Sabry*******/
/*******DATE:       9/2024***********/
/*******Version:    1.o*************/

#ifndef MDIO_PRIVATE_H
#define MDIO_PRIVATE_H
// define portA registers
#define PRIVATE_PORTA_REG     *((volatile u8*)0x3B)
#define PRIVATE_DDRA_REG     *((volatile u8*)0x3A)
#define PRIVATE_PINA_REG     *(( volatile u8*)0x39)

// define portB registers
#define PRIVATE_PORTB_REG     *((volatile u8*)0x38)
#define PRIVATE_DDRB_REG     *((volatile u8*)0x37)
#define PRIVATE_PINB_REG     *(( volatile u8*)0x36)
// define portC registers

#define PRIVATE_PORTC_REG     *((volatile u8*)0x35)
#define PRIVATE_DDRC_REG     *((volatile u8*)0x34)
#define PRIVATE_PINC_REG     *((volatile u8*)0x33)
// define portD registers
#define PRIVATE_PORTD_REG     *((volatile u8*)0x32)
#define PRIVATE_DDRD_REG     *((volatile u8*)0x31)
#define PRIVATE_PIND_REG     *(( volatile u8*)0x30)

// set macro for direction
#define PRIVATE_OUTPUT    1
#define PRIVATE_INPUT    0
#define PRIVATE_CONC(b7,b6,b5,b4,b3,b2,b1,b0)     PRIVATE_CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)

#define PRIVATE_CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)  0b##b7##b6##b5##b4##b3##b2##b1##b0
// set macro for values
#define PRIVATE_OUTPUT_HIGH  1
#define PRIVATE_OUTPUT_LOW  0
#define PRIVATE_INPUT_FLOATING  0
#define PRIVATE_INPUT_PULLEDUP  1
/*//for seven segment
#define PRIVATE_zero    0b11000000
#define PRIVATE_One     0b11111001
#define PRIVATE_Two     0b10100100
#define PRIVATE_Three   0b10110000
#define PRIVATE_Four    0b10011001
#define PRIVATE_Five    0b10010010
#define PRIVATE_Six     0b10000010
#define PRIVATE_Seven   0b11111000
#define PRIVATE_Eight   0b10000000
#define PRIVATE_Nine    0b10010000
*/
#endif
