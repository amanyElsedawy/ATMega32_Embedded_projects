#include"STD_TYPE.h"
#include"BIT_MAC_FUC.h"


#include "MSPI_Interface.h"
#include "MSPI_Private.h"
#include "MSPI_Config .h"



/*Global variable to carry the Transmit Data*/
static u8 * MSPI_pu8TData = NULL ;

/*Global variable to carry the Receive Data*/
static u8 * MSPI_pu8RData = NULL ;

/*Global variable to carry the buffer size*/
static u8 MSPI_u8BufferSize;

/*Global variable to indicate for the current Data index of the buffer*/
static u8 MSPI_u8Index;

/*Global pointer to function to carry the notification function called by ISR*/


static void(*MSPI_pf)(void)=NULL;
static u8 MSPI_u8State=STD_Empty;

void MSPI_voidMasterInit(void){
//select data order->LSB
	SET_BIT(private_SPCR,5);
//enable master mode
	SET_BIT(private_SPCR,4);
//CPOL=Raising edge//CPHA=Setup
	CLR_BIT(private_SPCR,3);
	SET_BIT(private_SPCR,2);
//select clock to 64
	SET_BIT(private_SPCR,1);
	CLR_BIT(private_SPCR,0);
	//CLR_BIT(private_SPSR,0);
//enable SPI perf
	SET_BIT(private_SPCR,6);

}
void MSPI_voidSlaveInit(void){

	//select data order->LSB
		SET_BIT(private_SPCR,5);
	//enable slave mode
		CLR_BIT(private_SPCR,4);
	//CPOL=Raising edge//CPHA=Setup
		CLR_BIT(private_SPCR,3);
		SET_BIT(private_SPCR,2);
   //enable SPI perf
		SET_BIT(private_SPCR,6);

}
u8 MSPI_u8TransmitRecByteSimple(u8 Copy_u8TXByte){

private_SPDR=Copy_u8TXByte;
while((GET_BIT(private_SPSR,7))==0);
return private_SPDR;



}

/*//send string sync
void MSPi_TransmitStringSync(u8* Copy_TransString){
	if (Copy_TransString == NULL) {
	        return; // Early return if the input is NULL
	    }

while(*Copy_TransString != '\0'){
	while((GET_BIT(private_SPSR,7))==0);

	private_SPDR=*Copy_TransString;
	Copy_TransString++;

}

}
////rec string sync

void MSPI_RecStringSync(u8* Copy_RecString){

u8 Local_u8index=0;
if( Copy_RecString==NULL){
  return;
}
while(1){

	while((GET_BIT(private_SPSR,7))==0);
    u8 Local_rec=private_SPDR;

    Copy_RecString[Local_u8index]=Local_rec;

    if(Local_rec!='\0'){

       break;
                 }
    Local_u8index++;


}


}
*/
//send and recieve byte
u8  MSPI_u8TransmitRecByte(u8 Copy_u8TByte,u8* Copy_u8RByte){

  u8 Local_ErrorState=STD_TYPE_OK;

  u32 Local_MSPI_TimeCounter=0;
if(MSPI_u8State==STD_Empty){

	MSPI_u8State=STD_Busy;
		//transfer the data
	private_SPDR=Copy_u8TByte;
	while(((GET_BIT(private_SPSR,7))==0)&&(Local_MSPI_TimeCounter<MSPI_u32TimeOut)){
		 Local_MSPI_TimeCounter++;
	}
     if(Local_MSPI_TimeCounter==MSPI_u32TimeOut){

	      Local_ErrorState=STD_TimeOutState;
}       else{
	         * Copy_u8RByte=private_SPDR;

}

     MSPI_u8State=STD_Empty;
}else{
	 Local_ErrorState=STD_BusyState;
}

return Local_ErrorState;
}
//syn function to send/rec
u8 MSPI_u8BufferTranRecSynch(u8* Copy_u8TransData,u8* Copy_u8RecData,u8 Copy_BufferSize){
u8 Local_ErrorState=STD_TYPE_OK;
u8 Local_Counter=0;
if(Copy_u8TransData!=NULL && Copy_u8RecData!=NULL ){

//loop until send and receive all data
	while(Local_Counter<Copy_BufferSize){//here i think it will send one number as size=1 or not?
//call  function that Trans/Rec Byte

         MSPI_u8TransmitRecByte(Copy_u8TransData[Local_Counter],&Copy_u8RecData[Local_Counter]);
          Local_Counter++;
	}

}else{
    Local_ErrorState=STD_TYPE_NOK;
}

return Local_ErrorState;

}
//Trans/Rec Function Asynch

u8 MSPI_u8BufferTransRecAsynch(u8* Copy_u8TransData,u8* Copy_u8RecData,u8 Copy_BufferSize){
u8 Local_ErrorState=STD_TYPE_OK;
if(MSPI_u8State==STD_Empty){
	if(Copy_u8TransData!=NULL && Copy_u8RecData!=NULL ){
	    MSPI_u8State=STD_Busy;

         MSPI_pu8TData=Copy_u8TransData;
         MSPI_pu8RData=Copy_u8RecData;
         MSPI_u8BufferSize= Copy_BufferSize;

  //start index=0
         MSPI_u8Index=0;
         //start Transmit
         private_SPDR=MSPI_pu8TData[MSPI_u8Index];
         //start interrupt
           SET_BIT(private_SPCR,7);





	}else{
        Local_ErrorState=STD_TYPE_NOK;
	}



}else{
	Local_ErrorState=STD_BusyState;

}
return  Local_ErrorState;

}
//set call backfunction
u8 MSPI_SetCallBack(void(*Copy_pf)(void)){

u8 LocalErrorState=STD_TYPE_NOK;
if(Copy_pf!=NULL){
	LocalErrorState=STD_TYPE_OK;

    MSPI_pf=Copy_pf;
}
return LocalErrorState;
}
//ISR

void __vector_12 (void)		__attribute__ ((signal)) ;
void __vector_12 (void)
{

MSPI_pu8RData[MSPI_u8Index]=private_SPDR;
MSPI_u8Index++;
if(MSPI_u8Index==MSPI_u8BufferSize){
	 MSPI_u8State=STD_Empty;
//enable interrupt
     CLR_BIT(private_SPDR,7);
//call set call back function
     if(MSPI_pf!=NULL){
          MSPI_pf();
     }

}else{


    //transmit agian
    private_SPDR=MSPI_pu8TData[MSPI_u8Index];



}


}
