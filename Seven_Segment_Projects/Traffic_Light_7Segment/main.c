
#include<avr/io.h>
#define F_CPU 8000000UL
#include<util/delay.h>
//define leds of two segmant
#define zero  0b11000000
#define one   0b11111001
#define two   0b10100100
#define three 0b10110000
#define four  0b10011001
#define five  0b10010010
#define six   0b10000010
#define seven 0b11111000
#define eight 0b10000000
#define nine  0b10010000

int main(void){
// set port B as ouput fot first seven segment
	DDRB=0b11111111;
// set port D as ouput fot second seven segment
	DDRD=0b11111111;
// set red led as output
DDRA=0b10000000;
// set green led as output
DDRA=0b01000000;
// set yellow led as output
DDRA=0b00100000;
// set an array for seven segment
unsigned int numbers[10]={zero,one,two,three,four,five,six,seven,eight,nine};
while(1){
//turn green led
PORTA=0b01000000;
//turn zero in first segment
PORTB=0b11000000;
//turn zero in second segment
PORTD=0b11000000;
_delay_ms(1000);
//turn zero in first segment

PORTB=0b11000000;
//turn one in second segment
PORTD=0b11111001;
_delay_ms(1000);
for(int i=9;i>0;i--){
	PORTD=0b11000000;
PORTB=numbers[i];
_delay_ms(1000);

}
//turn off  green led
PORTA=0b00000000;
//turn on yellow led
PORTA=0b00100000;
//turn zero in first segment
PORTB=0b11000000;
//turn zero in second segment
PORTD=0b11000000;

_delay_ms(1000);
for(int i=3;i>0;i--){
	PORTD=0b11000000;
	PORTB=numbers[i];
	_delay_ms(1000);
}
//turn off  yellow led
PORTA=0b00000000;

//turn on red led
PORTA=0b10000000;
//turn zero in first segment
PORTB=0b11000000;
//turn zero in second segment
PORTD=0b11000000;
_delay_ms(1000);
//turn zero in first segment
PORTB=0b11000000;
//turn one in second segment
PORTD= 0b11111001;
_delay_ms(1000);

for(int i=9;i>0;i--){
PORTD=0b11000000;
PORTB=numbers[i];
_delay_ms(1000);

}
PORTA=00000000;
}

return 0;
}
