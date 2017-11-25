/*
 * ADCexample.c
 *
 * Created: 4/13/2013 5:22:48 PM
 
 */
 
//#define F_CPU   8000000
 
#include <avr/io.h>
//#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#define BIT_IS_SET(byte, bit)(byte & (1 << bit))
#define BIT_IS_CLEAR(byte, bit)(!(byte &(1<<bit)))
#define WAIT_MS  10// Time in ms to wait for debounce.

void fanOn()
{
	PORTB &= 0 << PINB0;								// heat off;
	//PORTB = 0xFF;
	PORTB |= 1 << PINB1;								// fan on blu light on
	PORTD |= 1 << PIND6;								// Display on
	//PORTB |= 1 << PINB2;								// heat on red light on
	return;
}

void heatOn()
{
	
	//PORTB |= 1 << PINB2;								// heat on red light on
	PORTB &= 0 << PINB1;								// fan off;
	PORTD |= 1 << PIND6;								// Display on
	PORTB |= 1 << PINB2;								// heat on red light on
	return;
}

 
void control (int setPoint, int room_temp)
{
	//room_temp = 75;	//PC0 value Sensor value -----Surya code

	/*if ((room_temp <= setPoint+3)&&(room_temp >=setPoint-3))
	{
		_delay_ms(5000); // delay 5 min
		// Display Temp -----------------------Dai code
		
		
	}*/
	//PORTB |= 1 << PINB2;								// heat on red light on
	 if ( room_temp > setPoint + 3)
	{
		fanOn();
	}
	else if ( room_temp < setPoint )
	{
		heatOn();
	}
}


int main(void)
{
	
	DDRD = (1 << PORTD6);								// Output LED on PD6 -- LCD indicator
	DDRB = (1 << PORTB1);								// Output LED on PD6 -- FAN indicator
	DDRB = (1 << PORTB2);								// Output LED on PD6 -- Heat indicator
	//PORTD = (1<<PORTD0);
	//PORTB |= 1 << PINB2;								// heat on red light on
	int cur = PIND;
	int prev = PIND;
	int toggle = 1;
	int potValue = 0;
	int current_temp = 0;
	int setTo = 0;
	/* Set ADMUX register -- use to pick ref Voltage and ADC pin*/
	ADMUX = (1 << REFS0) | (1<<ADLAR)|(1 << MUX0) | (1 << MUX2);
/* Set ADSCRA register leave ADSCRB register zero -- resolution*/
	ADCSRA = (1 << ADEN) | (0 << ADATE) | (1 << ADPS0) | (1 << ADPS1) | (0 << ADPS2);
	ADCSRB = 0x00;
	while(1)
	{
		// Measure Temp-----------------------Put code here
		// Display Temp-----------------------Put code here
		
//PORTB |= 1 << PINB2;								// heat on red light on
		// Check for button press-------------Code is below
		cur = PIND;
		
		//PORTD ^= 1 << PIND6;
		//if (bit_is_clear(PIND, 0)==0)
		if ((prev & (1 << PIND0))<(cur & (1 << PIND0)))
		{
		
			cur = PIND;
			toggle ^= 1;						// toggle is needed to  switch between Auto and User mode
		}
		prev = PIND;
		_delay_ms(WAIT_MS); 			// Wait for debounce.
			switch (toggle)
			{
			case 0:				// Turn USER on
				//PORTD &= 0 << PIND6;
				//PORTB ^= 1 << PINB1;
				// Turn Auto OFF------------------|CODE HERE
				// Read POT-----------------------|CODE HERE
				_delay_ms(5000); 
				
				ADCSRA |= (1<<ADSC);			// Start Conversion pot input
				while (BIT_IS_SET(ADCSRA, ADSC)) {} // poll until ADSC bit is set
				// Quantize potvalue between 50c to 90c
				// Get pot value and display here  
				// Use this pot value to set temp -- GO TO CONTROL
				potValue = ADCH;																				// capture pot value
			/*	if (potValue == 0)
				{
					PORTD &= 0 <<PIND6;
				}
				else if (potValue > 100)
				{
					PORTD |= 1 <<PIND6;
				} 
			*/
				// Display POT value--------------|CODE HERE
				// Wait 5 sec---------------------|CODE HERE
				// Go to Control with POT Value---|CODE HERE
				//goto CONTROL-- procedure takes setPoint and decides on temp value
				current_temp = 50;
				//if (potValue > 100)
				control(potValue, current_temp);
				//else
				//printf("Less than 100 '\n'");

				break;
			case 1:				// Turn AUTO on
				//PORTB &= 0 << PINB1;
				//PORTD &= 0 << PIND6;
				//_delay_ms(100); 
				// Measure room temp
				current_temp = 50; //PC 0 value --- SURYA code
				setTo = 100;
				PORTB |= 1 << PINB2;								// heat on red light on
				control(setTo, current_temp);
				/*if (current_temp > 75) {
					setTo = 65;
					control(setTo, current_temp);		//goto CONTROL;
				}
				else if (current_temp < 65) {
					setTo = 75;
					control(setTo, current_temp);		//goto CONTROL;
				}*/

				// Display Room temp-------- DAI code
				
				break;
			}
						
		//	PORTD ^= 1 << PIND6;
			//PORTB ^= 1 << PINB1;			// Turn Fan on
			//PORTB ^= 1 << PINB0;			// Turn heat on
			
		
					 
	 }
  
}
