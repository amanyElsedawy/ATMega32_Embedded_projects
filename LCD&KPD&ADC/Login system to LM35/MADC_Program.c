

#include "STD_TYPE.h"
#include "BIT_MAC_FUC.h"
//mcal
#include"MADC_Interfece.h"
#include"MADC_Private.h"
#include"MADC_Config.h"


 static u8  private_u8BusyFlag=private_NOT_Busy;
static(*private_pf)(u16)=NULL;

void  MADC_voidInit  (void){

//Set vref=5v(AVCC)
#if  MADC_Voltage_REF == MADC_AVCC

CLR_BIT(private_ADCMUX,7);
SET_BIT(private_ADCMUX,6);
#elif  MADC_Voltage_REF ==MADC_AREF
CLR_BIT(private_ADCMUX,6);
CLR_BIT(private_ADCMUX,7);
#elif  MADC_Voltage_REF ==MADC_INTERNAL_2_V
SET_BIT(private_ADCMUX,6);
SET_BIT(private_ADCMUX,7);

#endif
//Adjustment value ==>right->zero for right //and one for left
CLR_BIT(private_ADCMUX,5);
//select single_conversion_mode
CLR_BIT(private_ADCSRA,5);
//set prescaler value
SET_BIT(private_ADCSRA,2);
SET_BIT(private_ADCSRA,1);
CLR_BIT(private_ADCSRA,0);
//enable ACD peri
SET_BIT(private_ADCSRA,7);

}

u8 MADC_u8GetADCValueSynch(u8 Copy_u8ChannelNum, u16* Copy_pu16ADCValue){

	u8 local_u8ErrorState=STD_TYPE_NOK;
    u32 local_u32timeoutCounter=0;
if((Copy_u8ChannelNum<32) &&  (Copy_pu16ADCValue!=NULL)){
	local_u8ErrorState=STD_TYPE_OK;
	//clear channel number bits
	private_ADCMUX &=0b11100000;
//set channel number
    private_ADCMUX |= Copy_u8ChannelNum;
//start conversion
SET_BIT(private_ADCSRA,6);
//wait for ADC FLAG && check if hardware(ADC)is ok by counter expect time working of ADC
  while(( local_u32timeoutCounter<private_TimeOutMaxValue )&&(GET_BIT(private_ADCSRA,4)==0)){
	 local_u32timeoutCounter++;
  }
  if(GET_BIT(private_ADCSRA,4)){
	  //read ADC_VALUe
	  *Copy_pu16ADCValue=private_u16_ADC;
	  //clear flag
	  SET_BIT(private_ADCSRA,4);

  }else{
	  local_u8ErrorState=STD_TYPE_NOK;
  }



}


return  local_u8ErrorState;



}
//GetADCValueAsynch function
u8 MADC_u8GetADCValueAsynch(u8 Copy_u8ChannelNum,void(*Copy_pf)(u16)){
u8 local_u8ErrorState=STD_TYPE_NOK;
if((Copy_u8ChannelNum<32 )&&( Copy_pf!=NULL )&&( private_u8BusyFlag!=private_NOT_Busy)){
	local_u8ErrorState=STD_TYPE_OK;
//ADC is busy now
	 private_u8BusyFlag=private_Busy;
//set call back function
	 private_pf=Copy_pf;
	 //clear channel number bits
	 private_ADCMUX &=0b11100000;
	 //set channel number
	  private_ADCMUX |= Copy_u8ChannelNum;
	  //enable ADC interrput
     SET_BIT(private_ADCSRA,3);
     //start conversion
     SET_BIT(private_ADCSRA,6);
}



return local_u8ErrorState;
}

//ADC ISR
void __Vector_16(void)    __attribute__((signal));
void __Vector_16(void){

if(private_pf!=NULL){

	private_pf(private_u16_ADC);
  //ADC NOT BUSY NOW
    private_u8BusyFlag=private_NOT_Busy;
//unable interrupt
    CLR_BIT(private_ADCSRA,3);
}
}
