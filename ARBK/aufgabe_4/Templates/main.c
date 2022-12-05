/*
 * Praktikum4.c
 *
 * Created: 24.10.2022 12:09:29
 * Author : Jeremias
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


// sevenseg.h

volatile short int num1 = 0;
volatile short int num2 = 0;

volatile short int switch_var = 0;

volatile unsigned short num1_bin = 0b01111111;
volatile unsigned short num2_bin = 0b01111111;

/*
		  1.
	 ___________
	|			|
6.	|			|	2.
	|	  7.	|
	|___________|
	|			|
5.	|			|	3.
	|	  4.	|
	|___________|	
					o 8.	
		
*/




#define one 0b1111001;
#define two 0b0100100;
#define three 0b0110000;
#define four 0b0011001;
#define five 0b0010010;
#define six 0b0000010;
#define seven 0b1111000;
#define eight 0b0000000;
#define nine 0b0010000;
#define zero 0b1000000;

void setNum(int num)
{		
	if(num > 0&&num <= 99)
	{
		num1 = num/10;
		num2 = num%10;
	}
	else
	{
		num1 = 0;
		num2 = 0;
	}
	
	switch(num1) {
		case 1: num1_bin=one; break;
		case 2: num1_bin=two; break;
		case 3: num1_bin=three; break;
		case 4: num1_bin=four; break;
		case 5: num1_bin=five; break;
		case 6: num1_bin=six; break;
		case 7: num1_bin=seven; break;
		case 8: num1_bin=eight; break;
		case 9: num1_bin=nine; break;
		default: num1_bin=zero; break;
	}
	switch(num2) {
		case 1: num2_bin=one; break;
		case 2: num2_bin=two; break;
		case 3: num2_bin=three; break;
		case 4: num2_bin=four; break;
		case 5: num2_bin=five; break;
		case 6: num2_bin=six; break;
		case 7: num2_bin=seven; break;
		case 8: num2_bin=eight; break;
		case 9: num2_bin=nine; break;
		default: num2_bin=zero; break;
	}
	
	
	return;
}

int getNum()
{
	return (num1*10+num2);
}

void _switch()
{	
	_delay_ms(200);
	switch_var--;
	PORTB = switch_var;
	PORTD = num1_bin;
	_delay_ms(200);
	switch_var++;
	PORTB = switch_var;
	PORTD = num2_bin;
	return;
}

// --- end sevenseg.h


// keys.c

volatile int short tmp_num = 0;
volatile short int down=1;
volatile unsigned short int portchistory = 0xff;
uint8_t changedbits;

ISR(PCINT1_vect) //PCINt interrupt vektor pin(8-14)
{
	
	changedbits = PINC ^ portchistory;	//akuelle bits xor mit den letzten bits
	portchistory = PINC;				//die letzten bits werden aktualisiert
	if(changedbits == 0b00100000)       //schaut ob die changed bits auf dem port f�r sw1 liegen
	{
		
	
		if(tmp_num<99&&down==1)    //
		{
			tmp_num++;
			down = 0;
		}
		else
		{
			down = 1;
		}
	}
	else
	{
		
		if(tmp_num>0&&down==1)
		{
			tmp_num--;
			down = 0;
		}
		else
		{
			down = 1;
		}
	}
	
}

int getSwitchNum() 
{
return tmp_num;
}


void initExternalSoftwareInterrupts()
{
	PCICR = 0b00000010;	
	PCMSK1 = 0b00110000;
	
	sei();
}

//--- end keys.c
int main(void)
{
	DDRB=0b00000001;
	PORTB=0xFF;
	DDRD=0b11111111;
	PORTD=0b00000000;
	DDRC = 0x0;
	PORTC = 0xff;
	initExternalSoftwareInterrupts();
	
	
	
    while (1) 
    {
		setNum(getSwitchNum());
		_switch();
		
    }
}

