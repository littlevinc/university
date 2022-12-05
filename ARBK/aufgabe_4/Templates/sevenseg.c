/*
 * sevenseg.c
 *
 * Created: 24.10.2022 14:39:04
 *  Author: Jeremias
 */ 
#include "sevenseg.h"
#include <util/delay.h>
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