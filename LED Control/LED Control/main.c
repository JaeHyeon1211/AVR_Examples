/*
 * GccApplication1.c
 *
 * Created: 2022-07-26 오전 9:27:49
 * Author : skdis
 */ 

#define F_CPU 14745600L
#include <avr/io.h>
#include <util/delay.h>

/*
//Button - LED Control
int main(void)
{
	DDRE = 0x00; //0b 0000 0000 / pinMode(13,OUTPUT)
	DDRD =0xff; //0b 0000 0000
	
	while (1)
	{
		PORTD = PINE;
	}
}
*/


//같은 포트의 Button - LED
int main(void)
{
	DDRE = 0xf0; //0b 1111 0000  LED SW/ pinMode(13,OUTPUT)

    /* Replace with your application code */
    while (1) 
    {
		PORTE = PINE << 4; 
		
    }
}

