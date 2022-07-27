/*
 * Timer.c
 *
 * Created: 2022-07-26 오후 3:27:12
 * Author : skdis
 */ 

#define F_CPU 14745600L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int t_cnt = 0;
int m_cnt = 0;


unsigned char font[] = {0x3f, 0x06, 0x5b, 0x4f,
	0x66, 0x6d, 0x7c, 0x07,
	0x7f, 0x6f, 0x77, 0x7c,
	0x39, 0x5e, 0x79, 0x71,
0x08, 0x80 };

void segment(int n)
{
	unsigned char n1000,n100,n10, n1;
	int buff;
	
	n1000 = n/1000;
	buff = n %1000;
	
	n100 = buff/100;
	buff = buff % 100;
	
	n10 = buff / 10;
	n1 = buff % 10;
	
	for (int i =0; i < 30; i++ )
	{
		PORTC = 0x0e;
		PORTA = font[n1000];
		_delay_ms(1);
		
		PORTC = 0x0d;
		PORTA = font[n100];
		_delay_ms(1);
		
		PORTC = 0x0b;
		PORTA = font[n10];
		_delay_ms(1);
		
		PORTC = 0x07;
		PORTA = font[n1];
		_delay_ms(1);
	}
}

ISR(TIMER2_COMP_vect)
{
	TCNT0 = 0xf2;
	t_cnt++;	
	if(t_cnt >= 1000)
	{
		t_cnt = 0;
		m_cnt++;		
	}
	
}

int main(void)
{
	DDRA = 0xff;
	DDRC = 0x0f;
	DDRB = 0x80; //pb7 출력(OC1)
	
	PORTA = 0xff;
	PORTC = 0x0f;
	
	
	TCCR2 |= (1<<CS20) | (1<<CS22); //1024분주
	TCCR2 |= (1<<WGM21); //CTC모드
	TCCR2 |= (1<<COM20); //OC2 출력 토글
	
	
	
	TIMSK |= (1<<OCIE2); //0x01
	OCR0 = 14;
	
	
	sei();
    /* Replace with your application code */
    while (1) 
    {
		segment(m_cnt);
		
    }
}

