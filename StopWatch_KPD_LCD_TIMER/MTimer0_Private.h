
#ifndef MTimer0_Private_H
#define MTimer0_Private_H
extern volatile u16 Global_u16OverflowCount;

#define private_TCCR0          *((volatile u8*)0x53)
#define private_TCNT0          *((volatile u8*)0x52)

#define private_TIMSK          *((volatile u8*)0x59)
#define private_TIFR           *((volatile u8*)0x58)
#define private_OCR0          *((volatile u8*)0x5C)

//timer 1 register

#define private_TCCR1A             *((volatile u8*)0x4F)

#define private_TCCR1B            *((volatile u8*)0x4E)

#define private_u16_TCNT1         *((volatile u16*)0x4C)

#define private_u16_OCR1A         *((volatile u16*)0x4A)

#define private_u16_OCR1B         *((volatile u16*)0x48)

#define private_u16_ICR1          *((volatile u16*)0x46)


#endif
