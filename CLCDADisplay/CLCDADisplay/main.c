/*
 * CLCDADisplay.c
 *
 * Created: 2020-12-22 오후 2:26:46
 * Author : dykan
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define BIT4_LINE_DOT58		0x28			// 4bit mode, 2 Lines, 5x8 Dot      4bit mode에서 
#define DISPON_CUROFF_BLKOFF	0x0c		// Display On, Cursor OFF, Blink OFF
#define INC_NOSHIFT		0x06				// Emtry mode, cursor Increment, Display No Shift
#define DISPCLEAR		0x01				// Display Clear, Address 0, Position, Cursor 0
#define E_BIT		0x04					// Enable 비트 번호

void CLCD_cmd(char);
void CLCD_data(char);

// PC4 ~ 7 -> DB4 ~ 7 => Data
// PD2 ~ 4 -> RS, RW, E

int main(void)
{
	DDRC = 0xff;	// CLCD Data 신호 담당
	DDRD = 0xff;	// CLCD Control 신호 담당
	
	_delay_ms(50);
	CLCD_cmd(BIT4_LINE_DOT58);
	CLCD_cmd(DISPON_CUROFF_BLKOFF);
	CLCD_cmd(INC_NOSHIFT);
	CLCD_cmd(DISPCLEAR);
	
	_delay_ms(2);	// 디스프레이 clear 실행 시간 동안 대기
	CLCD_data('A');
    
}

void CLCD_data(char data){
	PORTD = 0x04;		// E(bit4) = R/W(bit3) = 0, RS(bit2) = 1의 의미는 내부 데이터 레지스터 포인팅
	
	_delay_us(1);		// Setup Time
	PORTD = 0x14;		// E(bit4) = RS(bit1) = 1, R/W(bit3) = 0의 의미는 Write
	PORTC = data & 0xf0;
	PORTD = 0x04;
	
	_delay_us(2);		// Hold & Setup Time
	PORTD = 0x14;
	
	PORTC = (data << 4) & 0xf0;
	PORTD = 0x04;
	
	_delay_ms(1);
}

void CLCD_cmd(char cmd){
	PORTD = 0x00;		// E(bit4) = R/W(bit3) = RS(bit2) = 0
	
	_delay_us(1);
	PORTD = 0x10;		// E(bit4) = 1
	
	PORTC = cmd & 0xf0;		// 8bit 명령어 중 상위 4비트만 준비
	PORTD = 0x00;		// E: 1 -> 0
	
	_delay_us(2);		// Hold & Setup Time
	PORTD = 0x10;		// E(bit4) = 1
	
	PORTC = (cmd <<4) & 0xf0;		// 8bit 명령어 중 하위 4비트 준비
	PORTD = 0x00;		// E: 1 -> 0, data전송 start
	
	_delay_ms(1);		// Hold Time & Execution Time
}