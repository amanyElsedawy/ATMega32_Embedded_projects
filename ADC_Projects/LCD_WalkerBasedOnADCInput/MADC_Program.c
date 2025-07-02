

#include "STD_TYPE.h"
#include "BIT_MAC_FUC.h"
//mcal
#include"MADC_Interfece.h"
#include"MADC_Private.h"
#include"MADC_Config.h"





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
void disable_ADC(void){
CLR_BIT(private_ADCSRA,7);

}


u8 MADC_u8GetADCValue(u8 Copy_u8ChannelNum, u16* Copy_pu16ADCValue){

	u8 local_u8ErrorState=STD_TYPE_NOK;
if((Copy_u8ChannelNum<32) &&  (Copy_pu16ADCValue!=NULL)){
	local_u8ErrorState=STD_TYPE_OK;
	//clear channel number bits
	private_ADCMUX &=0b11100000;
//set channel number
    private_ADCMUX |= Copy_u8ChannelNum;
//start conversion
SET_BIT(private_ADCSRA,6);
//wait for ADC FLAG
while(GET_BIT(private_ADCSRA,4)==0);
//or by this way
//while(!(GET_BIT(private_ADCSRA,4)));
//read ADC_VALUe
*Copy_pu16ADCValue=private_u16_ADC;
//clear flag
SET_BIT(private_ADCSRA,4);

}


return  local_u8ErrorState;



}
