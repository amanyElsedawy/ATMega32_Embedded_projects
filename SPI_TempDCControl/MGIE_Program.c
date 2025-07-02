

#include "STD_TYPE.h"
#include "BIT_MAC_FUC.h"
//mcal
#include"MGIE_Interface.h"
#include"MGIE_Private.h"
#include"MGIE_Config.h"




void MGIE_enable_GI(void){


SET_BIT(Private_SREG,7);
}
void MGIE_disenable_GI(void){


CLR_BIT(Private_SREG,7);

}
