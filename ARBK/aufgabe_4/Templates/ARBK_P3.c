unsigned int counter = 0;
volatile uint32_t t_ms= 0; // valotile, da diese variable sich ver�ndert, ohne dass der compiler das einplant

ISR(TIMER0_OVF_vect) //interupt fuer timeroverflow(bei 255) da timer 0 verwendet wird
{
	counter++;
	if(counter > 63)//Wenn counter 63 erreicht ist erh�he t_ms und setze counter auf 0 (63 x 255 x 1000 = 16.065.000 )
	{
		t_ms++;
		counter = 0;
	}
	
	
	TCNT0=0; //setze overflow auf null
	
	return;
}

void waitFor(uint32_t ms)
{
	uint32_t tmp = t_ms;
	while(t_ms < ms+tmp)//solange t_ms kleiner als ms+t_ms (differenz warten)
	{

	}
	return;
}

void waitUntil(uint32_t ms)
{
	
	while(t_ms < ms){ //bis ms von t_ms erreich wird
	}

	return;
}



int main(void)
{
	
	DDRD = 0xff;
    PORTD = 0x00; // turn all LEDs off
	TIMSK0=0b00000001; //timer 0 mit Intrerrupt bei overflow enabled
	TCNT0=0;
	TCCR0B=0b00000001; //setze das prescaling auf no prescaling (prescaling reduziert taktrate)
	sei();

		while(1){

           PORTD = 0b11110000;

           
		};
		
	
}