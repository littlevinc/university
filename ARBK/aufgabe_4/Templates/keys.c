     /*
 * keys.c
 *
 * Created: 24.10.2022 14:38:35
 *  Author: Jeremias
 */ 

#include "keys.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h> 
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

