#ifndef   MADC_INTERFACE_H
#define   MADC_INTERFACE_H



void  MADC_voidInit  (void);//have function enable only//advanced make function to enable and  one to disable

u8 MADC_u8GetADCValueSynch(u8 Copy_u8ChannelNum, u16* Copy_pu16ADCValue);

u8 MADC_u8GetADCValueAsynch(u8 Copy_u8ChannelNum,void(*Copy_pf)(u16));
#endif
