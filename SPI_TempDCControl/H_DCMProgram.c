
#define F_CPU 8000000UL
#include<util/delay.h>
// include library
#include"STD_TYPE.h"
#include"BIT_MAC_FUC.h"
//MCAL
#include"MDIO_Interface.h"
//HALL
#include "H_DCMInterface.h"
#include"H_DCMPrivate.h"
#include"H_DCMCONFIG.h"

void turn_DC_MotorCW(){

MDIO_u8SetPinValue(DC_Base2_port,DC_Base2_pin,MDIO_PinHigh);

MDIO_u8SetPinValue(DC_Base1_port,DC_Base1_pin,MDIO_PinLow);


}
void turn_DC_MotorCCW(){
	MDIO_u8SetPinValue(DC_Base1_port,DC_Base1_pin,MDIO_PinHigh);
	MDIO_u8SetPinValue(DC_Base2_port,DC_Base2_pin,MDIO_PinLow);


}
