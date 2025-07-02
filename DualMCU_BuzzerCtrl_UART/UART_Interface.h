#ifndef MUART_Interface_H
#define MUART_Interface_H


#define MAX_STRING_LENGTH 20
void MUART_voidInit(void);


void MUART_voidSendByte(u8 Copy_u8TxByte);


u8 MUART_voidRecieveByte(void);




void MUART_voidSynSendString(const u8* Copy_u8TxString);
void MUART_voidSynReceiveString(u8* Copy_u8RxString);

void MUART_AsynSendString(const u8* Copy_u8PtrString);
void MUART_voidAsyncReceiveString(void);

#endif
