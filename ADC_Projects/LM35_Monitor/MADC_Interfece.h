#ifndef   MADC_INTERFACE_H
#define   MADC_INTERFACE_H



void  MADC_voidInit  (void);

u8 MADC_u8GetADCValueSynch(u8 Copy_u8ChannelNum, u16* Copy_pu16ADCValue);

u8 MADC_u8GetADCValueAsynch(u8 Copy_u8ChannelNum,void(*Copy_pf)(u16));
#endif
