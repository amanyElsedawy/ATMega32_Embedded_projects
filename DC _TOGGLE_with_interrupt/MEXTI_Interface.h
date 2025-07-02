#ifndef   MEXTI_INTERFACE_H
#define   MEXTI_INTERFACE_H


#define MEXTI_INT0  0
#define MEXTI_INT1  1
#define MEXTI_INT2  2

#define MEXTI_Falling_Edg         0
#define MEXTI_Raising_Edg         1
#define MEXTI_Any_Logical_Change  2
#define MEXTI_Low_Level           3

//enable interrput
u8 MEXTI_u8Enable(u8 Copy_u8ExtINum,u8 Copu_u8IntSrc);
u8 MEXTI_u8DISEnable(u8 Copy_u8ExtINum);
u8 MEXTI_u8SetBack(u8 Copy_u8ExtINum,void(*Copy_PF)(void));

#endif

