#include<avr/io.h>
#include <util/delay.h>
#include<avr/interrupt.h>

/*
    A = PD0
    B = PD1
    C = PD2
    D = PD3
    E = PD4
    F = PD5
    G = PD6
*/

#define zero 0b11000000;
#define one 0b11111001;
#define two 0b10100100;
#define three 0b10110000;
#define four 0b10011001;
#define five 0b10010010;
#define six 0b00000010;
#define seven 0b11111000;
#define eight 0b10000000;
#define nine 0b10010000;


/**
 * Variables to handle numbers
*/

volatile short int global_number = 0;
volatile unsigned short num_one_display = zero; // PORTB = 0x01 (Zehnerstellen)
volatile unsigned short num_two_display = zero; // PORTB = 0x00 (Einerstellen)

volatile unsigned short int portchistory = 0xff;
volatile short int down=1;
uint8_t changedbits;


void display() {

    /**
     * Structure Arrays Digits
     * [Zehnerstellemn, Einerstellen]
    */

    int digits[] = {0, 0};

    digits[0] = (global_number / 10) % 10;
    digits[1] = global_number % 10;

    switch (digits[0]) {
        case 1: num_one_display = one; break;
        case 2: num_one_display = two; break;
        case 3: num_one_display = three; break;
        case 4: num_one_display = four; break;
        case 5: num_one_display = five; break;
        case 6: num_one_display = six; break;
        case 7: num_one_display = seven; break;
        case 8: num_one_display = eight; break;
        case 9: num_one_display = nine; break;
        case 0: num_one_display = zero; break;
        default: num_one_display = zero; break;
    }

    switch (digits[1]) {
        case 1: num_two_display = one; break;
        case 2: num_two_display = two; break;
        case 3: num_two_display = three; break;
        case 4: num_two_display = four; break;
        case 5: num_two_display = five; break;
        case 6: num_two_display = six; break;
        case 7: num_two_display = seven; break;
        case 8: num_two_display = eight; break;
        case 9: num_two_display = nine; break;
        case 0: num_two_display = zero; break;
        default: num_two_display = zero; break;
    }

}

ISR(PCINT1_vect) {

    /**
     * Interrupts steps:
     * 1. trigger interrup via vector
     * 2. read PINC states via PIN register
     * 3. determine if SW1 or SW2 was pressed
     * 
     * SW1 = Increase (connected to PC5)
     * SW2 = Decrease (connected to PC4)
    */

    changedbits = PINC ^ portchistory;
	portchistory = PINC;

    if(changedbits == 0b00100000) {

        if(global_number<99 && down == 1) {
            global_number++;
            down = 0;
        } else
            down = 1;

    } else {

        if(global_number> 0 && down == 1) {
            global_number--;
            down = 0;
        } else
            down = 1;

    }

    display();
    
}





int main(void) {

    // Interrupt Pins
    DDRC = 0x00;
	PORTC = 0xff;

    // LED Output Pins
    DDRD = 0xff; // set PORTD Pins to output

    // Digit Controller Pin
    DDRB = 0x01;

    /**
     * Enable PIN Change Interrupts
    */
    cli();
    PCICR = 0b00000010;
    PCMSK1 = 0b00110000;
    sei();

    
    while(1) {

        PORTB = 0x01;
        PORTD = num_one_display;
        _delay_ms(50);
        PORTB = 0x00;
        PORTD = num_two_display;
        _delay_ms(50);
       

    }

}




