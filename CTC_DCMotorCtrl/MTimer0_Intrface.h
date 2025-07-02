
#ifndef  MTimer0_Interface_H
#define  MTimer0_Interface_H


//timer0
void MTMR0_voidInit(void);

u8 MTMR0_u8SetCallBack(void(*Copy_pf)(void));
u8 MTMR0_u8SetCallBackCTCMode(void(*Copy_pf)(void));
void MTMR0_voidSetOCR0Value(u8 Copy_u8OCR0value);


//timer1
void MTMR1_voidInit(void);

void MTMR1_voidInit_PMWServo(u8 Copy_u8LocalAngle);


#endif
