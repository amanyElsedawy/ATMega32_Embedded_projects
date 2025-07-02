#ifndef MSPI_Interface_H
#define MSPI_Interface_H





void MSPI_voidMasterInit(void);
void MSPI_voidSlaveInit(void);
u8 MSPI_u8TransmitRecByteSimple(u8 Copy_u8TXByte);


//send and receive byte
u8  MSPI_u8TransmitRecByte(u8 Copy_u8TByte,u8* Copy_u8RByte);
//call in main//pass char to first argument ,create val of u8 and give second argument it address

//syn function to send/rec
u8 MSPI_u8BufferTranRecSynch(u8* Copy_u8TransData,u8* Copy_u8RecData,u8 Copy_BufferSize);
/*call in main
   u8 receivedData[sizeof(Buffer)];
   u8 MSPI_u8BufferTranRecSynch((u8*)"amany",receivedData, Buffer_Size->this case =6//Null in Count);
   */
//send and Receive Function Asynch
u8 MSPI_u8BufferTransRecAsynch(u8* Copy_u8TransData,u8* Copy_u8RecData,u8 Copy_BufferSize);
//MSPI call back function
u8 MSPI_SetCallBack(void(*Copy_pf)(void));

#endif

