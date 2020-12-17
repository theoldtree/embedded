/*
 * GccApplication1.c
 *
 * Created: 2020-12-17 오후 5:16:53
 * Author : admin
 */ 

#define F_CPU 16000000UL
#define <util/delay.h>

#include <util/delay.h> 
#include <avr/io.h>

#define S_LEVEL_8 1024*3.2/5
#define S_LEVEL_7 1024*2.8/5
#define S_LEVEL_6 1024*2.4/5
#define S_LEVEL_5 1024*2.0/5
#define S_LEVEL_4 1024*1.6/5
#define S_LEVEL_3 1024*1.2/5
#define S_LEVEL_2 1024*0.8/5
#define S_LEVEL_1 1024*0.4/5

void init_adc();
unsigned short read_adc();
void show_adc_led(unsigned short data);

int main(void)
{
    unsigned short value;
	DDRA = 0xff;
	init_adc();
	while(1){
		value = read_adc();
		show_adc_led(value);
		_delay_ms(1000);
	}
}

void init_adc(){
	ADMUX = 0x41;
	ADCSRA = 0x87;
}

unsigned short read_adc(){
	unsigned char adc_low, adc_high;
	unsigned short value;
	ADCSRA |= 0x40;
	while((ADCSRA & 0x10) != 0x10)
		;
	adc_low = ADCL;
	adc_high = ADCH;
	value = (adc_high << 8) | adc_low;
	return value;
}

void show_adc_led(unsigned short data){
	if(value >= S_LEVEL_8) PORTA = 0xff;
	if(value >= S_LEVEL_8) PORTA = 0x71;
	if(value >= S_LEVEL_8) PORTA = 0x3f;
	if(value >= S_LEVEL_8) PORTA = 0x1f;
	if(value >= S_LEVEL_8) PORTA = 0x0f;
	if(value >= S_LEVEL_8) PORTA = 0x07;
	if(value >= S_LEVEL_8) PORTA = 0x03;
	if(value >= S_LEVEL_8) PORTA = 0x01;
	else PORTA = 0x00;
}