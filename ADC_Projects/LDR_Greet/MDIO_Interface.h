/*******NAME:       Amany Sabry*******/
/*******DATE:       9/2024***********/
/*******Version:    1.o***********/
#ifndef MDIO_INTERFACE_H
#define MDIO_INTERFACE_H
//define port id
#define MDIO_PORTA 0
#define MDIO_PORTB 1
#define MDIO_PORTC 2
#define MDIO_PORTD 3
//define pin id
#define MDIO_PIN_0  0
#define MDIO_PIN_1  1
#define MDIO_PIN_2  2
#define MDIO_PIN_3  3
#define MDIO_PIN_4  4
#define MDIO_PIN_5  5
#define MDIO_PIN_6  6
#define MDIO_PIN_7  7
// define pin direction
#define MDIO_OUTPUT  0
#define MDIO_INPUT_FLOATING   1
#define MDIO_INPUT_PULLEdUP  2
//macro value of pin
#define MDIO_PinHigh  1
#define MDIO_PinLow  0
void MDIO_Init(void);

u8 MDIO_u8SetPinDirection(u8 Copy_u8PortId,u8 Copy_u8PinId, u8 Copy_u8PinDirec);
u8 MDIO_u8SetPortDirection(u8 Copy_u8PortId, u8 Copy_u8PortDirec);
u8 MDIO_u8SetPinValue(u8 Copy_u8PortId,u8 Copy_u8PinId,u8 Copy_u8PinValue);
u8 MDIO_u8SetPortValue(u8 Copy_u8PortId,u8 Copy_u8PortValue);
u8 MDIO_u8GetPinValue(u8 Copy_u8PortId,u8 Copy_u8PinId,u8 *Copy_Pu8ReturnPinValue);
u8 MDIO_u8GetPortValue(u8 Copy_u8PortId,u8 *Copy_Pu8ReturnPortValue);
#endif
