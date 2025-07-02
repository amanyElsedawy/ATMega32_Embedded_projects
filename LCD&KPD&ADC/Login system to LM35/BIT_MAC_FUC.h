#ifndef BIT_MAC_h
#define BIT_MAC_h

#define SET_BIT(value,Bitn) ((value)|=(1<<(Bitn)))
#define CLR_BIT(value,Bitn)  ((value)&=(~(1<<(Bitn))))
#define TOGGLE_BIT(value,Bitn) ((value)^=(1<<(Bitn)))
// function to return value of pin as it high or low
#define GET_BIT(REG,BIT_NUM)  ((REG>>BIT_NUM)&1)//REG indicate for PIN
#endif
//#include "BIT_MAC_FUC.h"

