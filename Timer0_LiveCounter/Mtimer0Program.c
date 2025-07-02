
//Lib  Layer

#include "STD_TYPE.h"
#include "BIT_MAC_FUC.h"

//mcal

#include"MTimer0_Intrface.h"
#include"MTimer0_Private.h"
#include"MTimer0_Config.h"


static void(*MTMR0_pf)(void)=NULL;
static void(*MTMR0_pfCtcmode)(void)=NULL;
volatile u16 Global_u16OverflowCount = 0;  // 16-bit variable to track overflow


void MTMR0_voidInit(void){
//set timer 0 mode->normal mode
#if Timer_mode == normal_mode
    CLR_BIT(private_TCCR0,6);
	CLR_BIT(private_TCCR0,3);
//enable normal mode interrput
SET_BIT(private_TIMSK,0);
//set pre load value
private_TCNT0=192;
//start timer by select prescaler timer
CLR_BIT(private_TCCR0,0);
CLR_BIT(private_TCCR0,2);
SET_BIT(private_TCCR0,1);

//CtC mode
//timer0->ctc mode
#elif Timer_mode == CTC_mode
CLR_BIT(private_TCCR0,6);
SET_BIT(private_TCCR0,3);
//enable compare match intterput

SET_BIT(private_TIMSK,1);
//set compare match regigter
private_OCR0=99;
//start timer by select prescaler timer
CLR_BIT(private_TCCR0,0);
CLR_BIT(private_TCCR0,2);
SET_BIT(private_TCCR0,1);
//PWM MODE
//timer0->PWM mode
#elif  Timer_mode == PWM_mode_Fast
SET_BIT(private_TCCR0,6);
SET_BIT(private_TCCR0,3);
//set hardware pin oc0->non_inverted mode
SET_BIT(private_TCCR0,5);
CLR_BIT(private_TCCR0,4);
//set duty_cycle
private_OCR0=0;
//start timer by select prescaler timer
CLR_BIT(private_TCCR0,0);
CLR_BIT(private_TCCR0,2);
SET_BIT(private_TCCR0,1);

//PWM_mode_phase
#elif  Timer_mode == PWM_mode_phase
SET_BIT(private_TCCR0,6);
CLR_BIT(private_TCCR0,3);
//set hardware pin oc0->non_inverted mode
SET_BIT(private_TCCR0,5);
CLR_BIT(private_TCCR0,4);
//set duty_cycle
private_OCR0=0;
//start timer by select prescaler timer
CLR_BIT(private_TCCR0,0);
CLR_BIT(private_TCCR0,2);
SET_BIT(private_TCCR0,1);


//COUNTER in NORMAL mode

#elif  Timer_mode == Normal_counter_mode
private_TCNT0=0;
//counter on normal mode
     CLR_BIT(private_TCCR0,6);
	CLR_BIT(private_TCCR0,3);

	//enable normal mode interrupt
	SET_BIT(private_TIMSK,0);

//init  timer as counter
    CLR_BIT(private_TCCR0,0);
	SET_BIT(private_TCCR0,1);
	SET_BIT(private_TCCR0,2);


#endif
}
void MTMR0_voidSetOCR0Value(u8 Copy_u8OCR0value){

	private_OCR0= Copy_u8OCR0value;


}


u8 MTMR0_u8SetCallBack(void(*Copy_pf)(void)){

u8 Local_u8ErrorState=STD_TYPE_NOK;
if(Copy_pf!=NULL){
	 Local_u8ErrorState=STD_TYPE_OK;
	 //set call back function
	 MTMR0_pf=Copy_pf;


}

return  Local_u8ErrorState;

}
u8 MTMR0_u8SetCallBackCTCMode(void(*Copy_pf)(void)){


	u8 Local_u8ErrorState=STD_TYPE_NOK;
	if(Copy_pf!=NULL){
		 Local_u8ErrorState=STD_TYPE_OK;
		 //set call back function
		 MTMR0_pfCtcmode=Copy_pf;


	}

	return  Local_u8ErrorState;



}
// Normal Mode ISR (Overflow Interrupt)
//ISR for tomer0 ovf
#if Timer_mode == normal_mode
void __vector_11(void) __attribute__((signal));

void __vector_11(void){

static u16 Local_u16Counter=0;
  Local_u16Counter++;

if( Local_u16Counter==3907){

//set timer counter with preload value
  private_TCNT0=192;
//action
   if(MTMR0_pf!=NULL){
      MTMR0_pf();
}
   //clear counter
   Local_u16Counter=0;

}
}
#endif

//ISR forNORMAL_COUNTER mode
#if Timer_mode ==Normal_counter_mode
void __vector_11(void) __attribute__((signal));

void __vector_11(void){
	 Global_u16OverflowCount++;

}
#endif
// CTC Mode ISR (Compare Match Interrupt)
//ISR for tomer0 compare match
#if Timer_mode == CTC_mode
void __vector_10(void) __attribute__((signal));

void __vector_10(void){

	static u16 Local_u16Counter=0;
	  Local_u16Counter++;
	if(Local_u16Counter==10000){
		if(MTMR0_pfCtcmode!=NULL){

			MTMR0_pfCtcmode();

}
//clear counter
	 Local_u16Counter=0;
}

}
#endif

//timer1
void MTMR1_voidInit(void){
//select timer1 mode=14
SET_BIT(private_TCCR1A  ,1);
CLR_BIT(private_TCCR1A  ,0);


SET_BIT(private_TCCR1B  ,4);
SET_BIT(private_TCCR1B  ,3);
//set OC1A pin->non verted mode
SET_BIT(private_TCCR1A,7);
CLR_BIT(private_TCCR1A,6);
//set max value in ICR1  as mode of mode 14
private_u16_ICR1=19999;
//set OCR1A to make server motor go to angle zero
private_u16_OCR1A=1499;
//set timer1 by set prescaler value=8
CLR_BIT(private_TCCR1B,2);
CLR_BIT(private_TCCR1B,0);

SET_BIT(private_TCCR1B,1);
//on pin 5 portD
}
