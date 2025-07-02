#ifndef MUART_Private_H
#define MUART_Private_H



#define private_UDR          *((volatile u8*)0x2C)

#define private_UCSRA         *((volatile u8*)0x2B)

#define private_UCSRB         *((volatile u8*)0x2A)

#define private_UCSRC         *((volatile u8*)0x40)

#define private_UBRRH         *((volatile u8*)0x40)

#define private_UBRRL        *((volatile u8*)0x29)



#endif
