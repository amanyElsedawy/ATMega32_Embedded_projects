
#define F_CPU 8000000UL
#include<util/delay.h>
//library
#include"STD_TYPE.h"
#include"BIT_MAC_FUC.h"

//MCAL
#include"MDIO_Interface.h"
//HALL
#include "HKPD_Interface.h"
#include"HKPD_Private.h"
#include"HKPD_Config.h"

static u8 HKPD_Au8RowPins[4]={HKPD_R1_PIN,HKPD_R2_PIN,HKPD_R3_PIN,HKPD_R4_PIN};
static u8 HKPD_Au8ColPins[4]={HKPD_C1_PIN,HKPD_C2_PIN,HKPD_C3_PIN,HKPD_C4_PIN};
//2D array for KPD pattern
static u8 HKPD_Au8Keys[4][4]=HKPD_KPD;

u8 HKPD_u8GetPressedKey(u8 *Copy_u8KeyPressed){

	u8 Local_u8ErorrState=STD_TYPE_NOK;
	u8 Local_u8RowCount;
	u8 Local_u8ColCount;
	u8 Local_u8PinValue;

	if(Copy_u8KeyPressed!=NULL){
		Local_u8ErorrState=STD_TYPE_OK;
		*Copy_u8KeyPressed=HKPD_NoKeyPressed;

		//active row pin
		for(Local_u8RowCount=0;Local_u8RowCount<4;Local_u8RowCount++){
			MDIO_u8SetPinValue(HKPD_ROWS_PORT,HKPD_Au8RowPins[Local_u8RowCount],MDIO_PinLow);
			//check for colum
			for(Local_u8ColCount=0;Local_u8ColCount<4;Local_u8ColCount++){

				MDIO_u8GetPinValue(HKPD_COLS_PORT,HKPD_Au8ColPins[Local_u8ColCount],&Local_u8PinValue);
				if(Local_u8PinValue==MDIO_PinLow){
					//bouncing effect solution

					_delay_ms(20);
					//wait till user unpressed the switch
					//loop until pin=high
					while(Local_u8PinValue==MDIO_PinLow){

						MDIO_u8GetPinValue(HKPD_COLS_PORT,HKPD_Au8ColPins[Local_u8ColCount],&Local_u8PinValue);

					}
					*Copy_u8KeyPressed=HKPD_Au8Keys[Local_u8RowCount][Local_u8ColCount];


				}
			}   // DE_activefor current row
			MDIO_u8SetPinValue(HKPD_ROWS_PORT,HKPD_Au8RowPins[Local_u8RowCount],MDIO_PinHigh);

		}
	}
	return  Local_u8ErorrState;


}
