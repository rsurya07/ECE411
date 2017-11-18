/*
 * ADCexample.c
 *
 * Created: 4/13/2013 5:22:48 PM
 *  Author: SAM
 */
 
//#define F_CPU   8000000
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//#define bit_is_clear(sfr,bit);
// \(!(_SFR_BYTE(sfr) & _BV(bit)))
#define WAIT_MS  10// Time in ms to wait for debounce.

 
double dutyCycle = 0;
 
// ADC convert start   
   void startConversion()
   {
	   ADCSRA |= (1 << ADSC);
   }
 
 // Setup ADC conversion
  void setupADC()
  {
	  ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX2);
	  ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	  DIDR0 = (1 << ADC5D);
	  
	  startConversion();
  }


// Timer Interrupt  
  ISR(TIMER0_OVF_vect)
  {
	  OCR0A = dutyCycle;
  }
 
 // Pot Interrupt 
  ISR(ADC_vect)
  {
	  dutyCycle = ADC;
	  startConversion();
  }


int main(void)
{
	
    DDRD = (1 << PORTD6);								// Output LED on PD6 -- LCD indicator
	//DDRB = (1 << PORTB1);								// Output LED on PD6 -- FAN indicator
	//DDRD = (1 << PORTB0);								// Output LED on PD6 -- Heat indicator
	//PORTD = (1<<PORTD0);
	int cur = PIND;
	int prev = PIND;
	int toggle = 0;
	while(1)
	 {
		cur = PIND;
		
		 //PORTD ^= 1 << PIND6;
		 //if (bit_is_clear(PIND, 0)==0)
		 if ((prev & (1 << PIND0))<(cur & (1 << PIND0)))
		 {
			// Potentiometer controlling LED on PD6
			cur = PIND;
			toggle ^= 1;
			switch (toggle)
			{
			case 0:
				PORTD ^= 1 << PIND6;
				PORTB &= 0 << PINB1;
				/*TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
				TIMSK0 = (1 << TOIE0);
				
				setupADC();
				
				sei();
				
				TCCR0B = (1 << CS00) | (1 << CS02);*/
				break;
			case 1:
				PORTB ^= 1 << PINB1;
				PORTD &= 0 << PIND6;	
				break;
			}
		//	PORTD ^= 1 << PIND6;
			//PORTB ^= 1 << PINB1;						// Turn Fan on
			//PORTB ^= 1 << PINB0;						// Turn heat on
			
		}
			prev = PIND;
			_delay_ms(WAIT_MS); // Wait for debounce. 
			
			//TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
			//TIMSK0 = (1 << TOIE0);
			
			//setupADC();
			
			//sei();
			
			//TCCR0B = (1 << CS00) | (1 << CS02);
		// }
		/* else
		 {
			toggle = 0;
			//PORTD &= 0 << PIND6;	
		 }
		 
		 if (toggle == 1)
		 {
			PORTD |= 1 << PIND6; 
			toggle = 0;
			
		 }
		 else
		 {
			 PORTD &= 0 << PIND6;
			 toggle = 1;
		 }
		 */
			 
	 }
  
}







/*
 * GccApplication1.c
 *
 * Created: 11/10/2017 11:39:09 PM
 * Author : dawit
 * 

//#include <avr/io.h>
#define toggle_pin(port, pin) (port ^=pin) 		//toggle
#define clear_pin(port, pin)(port &= ~pin)
#include <util/delay.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>

int main(void)
{
	// Button Working
	DDRB |= 1 << PINB1;			// OUTPUT on pin 13 pb0
  
	DDRD &= ~(1 << PIND0);		// INPUT on pin 1 pdo button
	PORTD |= 1 << PIND0;		// Pullup resistor high for button input
	
BUTTON WORKING*//*
    while(1)
    {
		//PORTB ^= 1 << PINB0;
		if (bit_is_clear(PIND, 0))
			PORTB |= 1 << PINB1;
		else
			PORTB &= 1 << PINB1;	
    }*//*
    while(1)
    {
	
	
}*/
