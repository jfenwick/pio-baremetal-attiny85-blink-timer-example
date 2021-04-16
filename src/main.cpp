#include <avr\interrupt.h>
#include <avr\io.h>

volatile uint16_t time_now = 0;

ISR(TIMER1_COMPA_vect)
{
	TCNT1 = 0;				// Reset counter value
	time_now++;
}

int main(void)
{
	uint16_t time_delay = 0;
	
	// Make PB0 an output
	DDRB |= (1 << PB0);
	
	// Setup Timer1
	TCCR1 |= 0x04;				// Set clock prescaler to 8
	TCNT1 = 0;				// Reset counter value
	OCR1A = 100;				// Set compare register A
	TIMSK |= (1 << OCIE1A);			// Enable register A compare interrupt
	
	// Enable Global Interrupts
	SREG |= (1 << SREG_I);
	
	while(1)
	{
		if (time_now == (time_delay))
		{
			PORTB ^= (1 << PB0);	// Toggle PB0 with XOR
			time_delay = time_now + 5000;
		}
	}
} 