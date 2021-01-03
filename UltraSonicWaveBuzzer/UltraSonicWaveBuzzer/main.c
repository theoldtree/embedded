/*
 * UltraSonicWaveBuzzer.c
 *
 * Created: 2021-01-03 오후 7:15:01
 * Author : admin
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define TRIG 6
#define ECHO 7
#define SOUND_VELOCITY 340UL

int main(void)
{
	unsigned int distance;
	DDRB = 0x10;
	DDRE = ((DDRE | (1<<TRIG))) & ~(1<<ECHO);
    /* Replace with your application code */
    while (1) 
    {  
		TCCR1B = 0x03;
		PORTE &= ~(1<<TRIG);
		_delay_ms(10);
		PORTE |= (1<<TRIG);
		_delay_ms(10);
		PORTE &= ~(1<<TRIG);
		while(!(PINE & (1<<ECHO)));
		TCNT1 = 0x00;
		while(PINE & (1<<ECHO));
		TCCR1B = 0x00;
		distance = (unsigned int)(SOUND_VELOCITY * (TCNT1 * 4/2)/1000);
		
		int i;
		if(distance < 300){
			for(i=0; i<5; i ++){
				PORTB = 0x10;
				_delay_ms(1);
				PORTB = 0x00;
				_delay_ms(1);
			}
		}
		
		else if(distance < 600){
			for(i=0; i<50; i ++){
				PORTB = 0x10;
				_delay_ms(1);
				PORTB = 0x00;
				_delay_ms(1);
			}
			_delay_ms(100);
		}
		
		else if(distance<1000){
			for(i=0; i<250; i ++){
				PORTB = 0x10;
				_delay_ms(1);
				PORTB = 0x00;
				_delay_ms(1);
			}
			_delay_ms(300);
		}
		else;
    }
}


