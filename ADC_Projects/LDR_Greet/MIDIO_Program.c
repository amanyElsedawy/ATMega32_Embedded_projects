/*******NAME:       Amany Sabry*******/
/*******DATE:       9/2024***********/
/*******Version:    1.o*************/

/* LIB LAYER*/
#include"STD_TYPE.h"
#include"BIT_MAC_FUC.h"


#include"MDIO_Interface.h"
#include "MDIO_Private.h"
#include"MDIO_Config.h"

void MDIO_Init(void){
 PRIVATE_DDRA_REG=PRIVATE_CONC(MDIO_PA7_DIRECTION,MDIO_PA6_DIRECTION,MDIO_PA5_DIRECTION,MDIO_PA4_DIRECTION,MDIO_PA3_DIRECTION,MDIO_PA2_DIRECTION,MDIO_PA1_DIRECTION,MDIO_PA0_DIRECTION);
 PRIVATE_DDRB_REG=PRIVATE_CONC(MDIO_PB7_DIRECTION,MDIO_PB6_DIRECTION,MDIO_PB5_DIRECTION,MDIO_PB4_DIRECTION,MDIO_PB3_DIRECTION,MDIO_PB2_DIRECTION,MDIO_PB1_DIRECTION,MDIO_PB0_DIRECTION);
 PRIVATE_DDRC_REG=PRIVATE_CONC(MDIO_PC7_DIRECTION,MDIO_PC6_DIRECTION,MDIO_PC5_DIRECTION,MDIO_PC4_DIRECTION,MDIO_PC3_DIRECTION,MDIO_PC2_DIRECTION,MDIO_PC1_DIRECTION,MDIO_PC0_DIRECTION);
 PRIVATE_DDRD_REG=PRIVATE_CONC(MDIO_PD7_DIRECTION,MDIO_PD6_DIRECTION,MDIO_PD5_DIRECTION,MDIO_PD4_DIRECTION,MDIO_PD3_DIRECTION,MDIO_PD2_DIRECTION,MDIO_PD1_DIRECTION,MDIO_PD0_DIRECTION);
 //set initial value
 PRIVATE_PORTA_REG=PRIVATE_CONC(MDIO_PA7_VALUE,MDIO_PA6_VALUE,MDIO_PA5_VALUE,MDIO_PA4_VALUE,MDIO_PA3_VALUE,MDIO_PA2_VALUE,MDIO_PA1_VALUE,MDIO_PA0_VALUE);
 PRIVATE_PORTB_REG=PRIVATE_CONC(MDIO_PB7_VALUE,MDIO_PB6_VALUE,MDIO_PB5_VALUE,MDIO_PB4_VALUE,MDIO_PB3_VALUE,MDIO_PB2_VALUE,MDIO_PB1_VALUE,MDIO_PB0_VALUE);
 PRIVATE_PORTC_REG=PRIVATE_CONC(MDIO_PC7_VALUE,MDIO_PC6_VALUE,MDIO_PC5_VALUE,MDIO_PC4_VALUE,MDIO_PC3_VALUE,MDIO_PC2_VALUE,MDIO_PC1_VALUE,MDIO_PC0_VALUE);
 PRIVATE_PORTD_REG=PRIVATE_CONC(MDIO_PD7_VALUE,MDIO_PD6_VALUE,MDIO_PD5_VALUE,MDIO_PD4_VALUE,MDIO_PD3_VALUE,MDIO_PD2_VALUE,MDIO_PD1_VALUE,MDIO_PD0_VALUE);

}

//set pin direction
u8 MDIO_u8SetPinDirection(u8 Copy_u8PortId,u8 Copy_u8PinId, u8 Copy_u8PinDirec){
u8 Local_u8ErrorState=STD_TYPE_OK ;

if(Copy_u8PinId<=MDIO_PIN_7){
  switch(Copy_u8PortId){
    case MDIO_PORTA:
    if(Copy_u8PinDirec==MDIO_OUTPUT ){
	 SET_BIT(PRIVATE_DDRA_REG ,Copy_u8PinId);
}   else if(Copy_u8PinDirec==MDIO_INPUT_FLOATING){

	CLR_BIT(PRIVATE_DDRA_REG ,Copy_u8PinId);
}   else if(Copy_u8PinDirec==MDIO_INPUT_PULLEdUP){
	CLR_BIT(PRIVATE_DDRA_REG ,Copy_u8PinId);
	SET_BIT(PRIVATE_PORTA_REG  ,Copy_u8PinId);

}
   else{
	Local_u8ErrorState=STD_TYPE_NOK;
}
  break;
  case MDIO_PORTB :
      if(Copy_u8PinDirec==MDIO_OUTPUT ){
	  SET_BIT(PRIVATE_DDRB_REG ,Copy_u8PinId);
}
     else if(Copy_u8PinDirec==MDIO_INPUT_FLOATING){

	    CLR_BIT(PRIVATE_DDRB_REG ,Copy_u8PinId);
}
    else if(Copy_u8PinDirec==MDIO_INPUT_PULLEdUP){
	CLR_BIT(PRIVATE_DDRB_REG ,Copy_u8PinId);
	SET_BIT(PRIVATE_PORTB_REG  ,Copy_u8PinId);

}
    else{
	Local_u8ErrorState=STD_TYPE_NOK;
}
  break;
 case MDIO_PORTC:

    if(Copy_u8PinDirec==MDIO_OUTPUT ){
	SET_BIT(PRIVATE_DDRC_REG ,Copy_u8PinId);
}
    else if(Copy_u8PinDirec==MDIO_INPUT_FLOATING){

	CLR_BIT(PRIVATE_DDRC_REG ,Copy_u8PinId);
}
    else if(Copy_u8PinDirec==MDIO_INPUT_PULLEdUP){
	CLR_BIT(PRIVATE_DDRC_REG ,Copy_u8PinId);
	SET_BIT(PRIVATE_PORTC_REG  ,Copy_u8PinId);

}
    else{
	Local_u8ErrorState=STD_TYPE_NOK;
}
 break;
 case MDIO_PORTD:
   if(Copy_u8PinDirec==MDIO_OUTPUT ){
	SET_BIT(PRIVATE_DDRD_REG ,Copy_u8PinId);
}
   else if(Copy_u8PinDirec==MDIO_INPUT_FLOATING){

	CLR_BIT(PRIVATE_DDRD_REG ,Copy_u8PinId);
}
   else if(Copy_u8PinDirec==MDIO_INPUT_PULLEdUP){
	CLR_BIT(PRIVATE_DDRD_REG ,Copy_u8PinId);
	SET_BIT(PRIVATE_PORTD_REG  ,Copy_u8PinId);

}
   else{
	Local_u8ErrorState=STD_TYPE_NOK;
}
 break;
default:
	Local_u8ErrorState=STD_TYPE_NOK;


}


}
else{
	Local_u8ErrorState=STD_TYPE_NOK;
}

return Local_u8ErrorState;
//set port direction
}

u8 MDIO_u8SetPortDirection(u8 Copy_u8PortId, u8 Copy_u8PortDirec){
u8 Local_u8ErrorState=STD_TYPE_OK ;
	switch(Copy_u8PortId){

	  case MDIO_PORTA:
		 if( Copy_u8PortDirec==MDIO_OUTPUT){
		   PRIVATE_DDRA_REG=0xFF;
		 }
		 else if( Copy_u8PortDirec==MDIO_INPUT_FLOATING){
			 PRIVATE_DDRA_REG=0x00;
		 }else if( Copy_u8PortDirec==MDIO_INPUT_PULLEdUP ){

			 PRIVATE_DDRA_REG=0x00;
			 PRIVATE_PORTA_REG=0xFF;

		 }else{
			 Local_u8ErrorState=STD_TYPE_NOK;

		 }

		break;
	  case MDIO_PORTB:
	  		 if( Copy_u8PortDirec==MDIO_OUTPUT){
	  		   PRIVATE_DDRB_REG=0xFF;
	  		 }
	  		 else if( Copy_u8PortDirec==MDIO_INPUT_FLOATING){
	  			 PRIVATE_DDRB_REG=0x00;
	  		 }else if( Copy_u8PortDirec==MDIO_INPUT_PULLEdUP ){

	  			 PRIVATE_DDRB_REG=0x00;
	  			 PRIVATE_PORTB_REG=0xFF;

	  		 }else{
	  			  Local_u8ErrorState=STD_TYPE_NOK;

	  		 }

	  		break;
	  case MDIO_PORTC:
	  		 if( Copy_u8PortDirec==MDIO_OUTPUT){
	  		   PRIVATE_DDRC_REG=0xFF;
	  		 }
	  		 else if( Copy_u8PortDirec==MDIO_INPUT_FLOATING){
	  			 PRIVATE_DDRC_REG=0x00;
	  		 }else if( Copy_u8PortDirec==MDIO_INPUT_PULLEdUP ){

	  			 PRIVATE_DDRC_REG=0x00;
	  			 PRIVATE_PORTC_REG=0xFF;

	  		 }else{
	  			  Local_u8ErrorState=STD_TYPE_NOK;

	  		 }

	  		break;
	  case MDIO_PORTD:
	  		 if( Copy_u8PortDirec==MDIO_OUTPUT){
	  		   PRIVATE_DDRD_REG=0xFF;
	  		 }
	  		 else if( Copy_u8PortDirec==MDIO_INPUT_FLOATING){
	  			 PRIVATE_DDRD_REG=0x00;
	  		 }else if( Copy_u8PortDirec==MDIO_INPUT_PULLEdUP ){

	  			 PRIVATE_DDRD_REG=0x00;
	  			 PRIVATE_PORTD_REG=0xFF;

	  		 }

	   else{
	  			 Local_u8ErrorState=STD_TYPE_NOK;
	   }



            break;
	  default:
		   Local_u8ErrorState=STD_TYPE_NOK;

	}

	return Local_u8ErrorState;

}
//set pin value
u8 MDIO_u8SetPinValue(u8 Copy_u8PortId,u8 Copy_u8PinId,u8 Copy_u8PinValue){
u8 Local_u8ErrorState=STD_TYPE_OK ;
 if(Copy_u8PinId<=MDIO_PIN_7 ){
   switch(Copy_u8PortId){
   case  MDIO_PORTA:
    switch(Copy_u8PinValue){
      case MDIO_PinHigh:
	   SET_BIT(PRIVATE_PORTA_REG , Copy_u8PinId);
	   break;
      case MDIO_PinLow:
   	   CLR_BIT(PRIVATE_PORTA_REG , Copy_u8PinId);
   	    break;
   }
       break;
    case  MDIO_PORTB:
   switch(Copy_u8PinValue){
	   case MDIO_PinHigh:
		   SET_BIT(PRIVATE_PORTB_REG , Copy_u8PinId);
		   break;
	   case MDIO_PinLow:
	   	   CLR_BIT(PRIVATE_PORTB_REG , Copy_u8PinId);
	   	 break;
	   }
     break;
     case  MDIO_PORTC:
  switch(Copy_u8PinValue){
	   case MDIO_PinHigh:
		   SET_BIT(PRIVATE_PORTC_REG,Copy_u8PinId );

		   break;
	   case MDIO_PinLow:
	   	   CLR_BIT(PRIVATE_PORTC_REG , Copy_u8PinId);
	   	   break;
	   }
        break;
      case  MDIO_PORTD:
 switch(Copy_u8PinValue){
	   case MDIO_PinHigh:
		   SET_BIT(PRIVATE_PORTD_REG , Copy_u8PinId);
		   break;
	   case MDIO_PinLow:
	   	   CLR_BIT(PRIVATE_PORTD_REG , Copy_u8PinId);
	   	 break;
	   }
break;
default:
	Local_u8ErrorState=STD_TYPE_NOK;

}
}
else{
	Local_u8ErrorState=STD_TYPE_NOK;

}
return Local_u8ErrorState;
}
//set port value
u8 MDIO_u8SetPortValue(u8 Copy_u8PortId,u8 Copy_u8PortValue){
	u8 Local_u8ErrorState=STD_TYPE_OK ;
    if( Copy_u8PortId<= Copy_u8PortId){
      switch(Copy_u8PortId){
      case MDIO_PORTA :PRIVATE_PORTA_REG= Copy_u8PortValue;break;
      case MDIO_PORTB :PRIVATE_PORTB_REG= Copy_u8PortValue;break;
      case MDIO_PORTC :PRIVATE_PORTC_REG= Copy_u8PortValue;break;
      case MDIO_PORTD :PRIVATE_PORTD_REG= Copy_u8PortValue;break;



      }

    }else{
    	Local_u8ErrorState=STD_TYPE_NOK;}

return Local_u8ErrorState;
}
//get pin value
u8 MDIO_u8GetPinValue(u8 Copy_u8PortId,u8 Copy_u8PinId,u8 *Copy_Pu8ReturnPinValue){
	u8 Local_u8ErrorState=STD_TYPE_OK ;
	if((Copy_u8PinId<=MDIO_PIN_7) && (Copy_u8PortId<=MDIO_PORTD)&&(Copy_Pu8ReturnPinValue!=NULL)){
         switch(Copy_u8PortId){
         case  MDIO_PORTA:  *Copy_Pu8ReturnPinValue = GET_BIT(PRIVATE_PINA_REG ,Copy_u8PinId);break;
         case  MDIO_PORTB:  *Copy_Pu8ReturnPinValue = GET_BIT(PRIVATE_PINB_REG ,Copy_u8PinId);break;
         case  MDIO_PORTC:  *Copy_Pu8ReturnPinValue = GET_BIT(PRIVATE_PINC_REG ,Copy_u8PinId);break;
         case  MDIO_PORTD:  *Copy_Pu8ReturnPinValue = GET_BIT(PRIVATE_PIND_REG ,Copy_u8PinId);break;



}

}else{

		Local_u8ErrorState=STD_TYPE_NOK;
	}
	return Local_u8ErrorState;

}
//get port valueTD
u8 MDIO_u8GetPortValue(u8 Copy_u8PortId,u8 *Copy_Pu8ReturnPortValue){
	u8 Local_u8ErrorState=STD_TYPE_OK ;
if((Copy_u8PortId<=MDIO_PORTD)&&(Copy_Pu8ReturnPortValue!= NULL)){
 switch( Copy_u8PortId){

        case  MDIO_PORTA:  *Copy_Pu8ReturnPortValue = PRIVATE_PINA_REG ;break;
         case  MDIO_PORTB:  *Copy_Pu8ReturnPortValue = PRIVATE_PINB_REG ;break;
         case  MDIO_PORTC:  *Copy_Pu8ReturnPortValue = PRIVATE_PINC_REG ;break;
         case  MDIO_PORTD:  *Copy_Pu8ReturnPortValue= PRIVATE_PIND_REG ;break;

 }

}else{
	Local_u8ErrorState=STD_TYPE_NOK ;
}



return  Local_u8ErrorState;
}
