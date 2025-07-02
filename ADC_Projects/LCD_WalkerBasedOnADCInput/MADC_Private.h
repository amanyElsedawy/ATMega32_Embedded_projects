
#ifndef   MADC_PRIVATE_H
#define   MADC_PRIVATE_H

#define  private_ADCMUX      *((volatile u8*)0x27)
#define  private_ADCSRA      *((volatile u8*)0x26)
#define  private_SFIOR       *((volatile u8*)0x50)
#define  private_ADCH        *((volatile u8*)0x25)
#define  private_ADCL        *((volatile u8*)0x24)
#define  private_u16_ADC      *((volatile u16*)0x24)//as to reed l and high one time as they next them



#endif
