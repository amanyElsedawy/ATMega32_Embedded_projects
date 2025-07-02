

#include"BIT_MAC_FUC.h"

#include"STD_TYPE.h"


#include"UART_Interface.h"
#include"UART_Private.h"
#include "UART_Config.h"









void MUART_voidInit(void){

u8 Local_U8UCSRCValue=0b10000000;
	//set baud rate 9600

	u16 Local_u16BaudRateValue=51;
private_UBRRL=(u8)Local_u16BaudRateValue;
private_UBRRH=(u8)(Local_u16BaudRateValue>>8);

//set normal speed
CLR_BIT(private_UCSRA,1);
//no multi processor mode
CLR_BIT(private_UCSRA,0);
//enabl2 RX and TX
SET_BIT(private_UCSRB,4);
SET_BIT(private_UCSRB,3);
//select Ascronus mode

CLR_BIT(Local_U8UCSRCValue,6);
//no parity bit
CLR_BIT(Local_U8UCSRCValue,5);
CLR_BIT(Local_U8UCSRCValue,4);
//stop bit
SET_BIT(Local_U8UCSRCValue,3);
//select char size->8bit
#if  UART_Char_Size ==UART_Char_8
SET_BIT(Local_U8UCSRCValue,2);
SET_BIT(Local_U8UCSRCValue,1);
CLR_BIT(private_UCSRB,2);

#elif  UART_Char_Size ==UART_Char_9

SET_BIT(Local_U8UCSRCValue,2);
SET_BIT(Local_U8UCSRCValue,1);
SET_BIT(private_UCSRB,2);
#elif  UART_Char_Size ==UART_Char_7

CLR_BIT(Local_U8UCSRCValue,2);
SET_BIT(Local_U8UCSRCValue,1);
CLR_BIT(private_UCSRB,2);
#elif  UART_Char_Size ==UART_Char_6

SET_BIT(Local_U8UCSRCValue,2);
CLR_BIT(Local_U8UCSRCValue,1);
CLR_BIT(private_UCSRB,2);
#elif  UART_Char_Size ==UART_Char_5

ClR_BIT(Local_U8UCSRCValue,2);
CLR_BIT(Local_U8UCSRCValue,1);
CLR_BIT(private_UCSRB,2);
#endif
//update UCSRC register

private_UCSRC=Local_U8UCSRCValue;

}


void MUART_voidSendByte(u8 Copy_u8TxByte){
//check the flag for empty data register
//in home set counter for flag return states
while((GET_BIT(private_UCSRA,5)) ==0 );
//send data byte
private_UDR=Copy_u8TxByte;


}


u8 MUART_voidRecieveByte(void){
	//in home set counter for flag return states
	while((GET_BIT(private_UCSRA,7)) ==0 );
    return private_UDR;

}

//send string syncrounous
void MUART_voidSynSendString(const u8* Copy_u8TxString) {
    // Loop through the string until the null terminator is reached

    while (*Copy_u8TxString != '\0') {
        // Wait until the data register is empty (UDRE flag)
        while (GET_BIT(private_UCSRA, 5) == 0); // Check UDRE flag

        // Send the current character
        private_UDR = *Copy_u8TxString;

        // Move to the next character
        Copy_u8TxString++;
    }
}
/*//recieve synchronous
void MUART_voidSynReceiveString(u8* Copy_u8RxString) {
    u8 index = 0;

    // Loop to receive characters until a null terminator is received
    while (1) {
        // Wait until data is received (RXC flag)
        while (GET_BIT(private_UCSRA, 7) == 0); // Check RXC flag

        // Read the received character
        u8 receivedChar = private_UDR;

        // Store the character in the output string
        Copy_u8RxString[index] = receivedChar;

        // Break if the null terminator is received
        if (receivedChar == '\n') {
            break;
        }

        // Move to the next index
        index++;
    }

    // Null-terminate the received string
    Copy_u8RxString[index] = '\0';
}

*/


void MUART_voidSynReceiveString(u8* Copy_u8RxString) {
    u8 index = 0;

    while (1) {
        // Wait until data is received (RXC flag)
        while (GET_BIT(private_UCSRA, 7) == 0); // Check RXC flag

        // Read the received character
        u8 receivedChar = private_UDR;

        // Check for newline as the terminator
        if (receivedChar == '\n' || receivedChar == '\r') {
            break;  // Exit the loop if newline is received
        }

        // Store the character in the output string if there's space
        if (index < MAX_STRING_LENGTH - 1) {  // Ensure space for null terminator
            Copy_u8RxString[index++] = receivedChar;
        }
    }

    // Null-terminate the received string
    Copy_u8RxString[index] = '\0';
}



volatile const u8* G_u8SendPtrString;
volatile u8  G_SendCounterIndex=0;
void MUART_AsynSendString(const u8* Copy_u8PtrString){
	 G_u8SendPtrString=Copy_u8PtrString;
	 G_SendCounterIndex=0;
	 //enable Udr interrupt
   SET_BIT(private_UCSRB,5);


}

//why i not loop untill complete string store in UDR
//how it return again after increase index
//ISR of UDR(RX is empty)
void __vector_14(void) __attribute__((signal));

void __vector_14(void){

  if(G_u8SendPtrString[G_SendCounterIndex] != '\0'){

     private_UDR=G_u8SendPtrString[G_SendCounterIndex];
     G_SendCounterIndex++;

}else{
    //disable interrupt
	   CLR_BIT(private_UCSRB,5);

}
}
//Recieve Asyn
volatile u8 g_RecArr[100];  // Buffer for the received string
volatile u8 g_RecIndex = 0;          // Index for tracking the position in the buffer

void MUART_voidAsyncReceiveString(void){
    g_RecIndex = 0;  // Start at the beginning of the buffer

    // Enable RX Complete interrupt (RXCIE)
    SET_BIT(private_UCSRB, 7);
}

// ISR for Receive Complete (RXCIE)
void __vector_13(void) __attribute__((signal));

void __vector_13(void) {

    u8 receivedByte = private_UDR;  // Read the received byte
    if (receivedByte != '\n' && receivedByte != '\0') {  // Check for termination
    	g_RecArr[g_RecIndex] = receivedByte;  // Store the received byte
        g_RecIndex++;  // Move to the next position in the buffer
    } else {
    	g_RecArr[g_RecIndex] = '\0';  // Null-terminate the string
        // Optionally, you can disable the RXC interrupt if the string is complete

        CLR_BIT(private_UCSRB, 7);
    }
}

