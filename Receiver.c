/*
 * UART_RX_INT.c
 *
 * ATtiny2313 UART receive interrupt example

 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

 #define BAUD 2400                                   // define baud
 #define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)            // set baud rate value for UBRR
 
volatile uint8_t received_byte = 2;
volatile uint8_t new_data = 0;

void uart_init(void)
{
	UBRRH = (BAUDRATE>>8); // shift the register right by 8 bits
	UBRRL = BAUDRATE; // set baud rate
	UCSRB = (1<<TXEN)|(1<<RXEN)|(1<<RXCIE); // enable receiver and transmitter
	UCSRC = (1<<UCSZ0)|(1<<UCSZ1); // 8bit data format
}

void uart_transmit(uint8_t data)
{
	 while (!( UCSRA & (1<<UDRE))); // wait while register is free
	 UDR = data; // load data in the register
}

 //UART RX Complete interrupt service routine
ISR(USART_RX_vect)
{
	cli();
	received_byte = UDR;  // Read received data
	new_data = 1;         // Flag for main loop
}

int main(void)
{
	DDRB = 0x1F;
	PORTB = 0x00;
    uart_init();
	
    sei(); // Enable global interrupts

    while (1)
    {
		if(new_data==1){
			switch (received_byte){
				case '1':
				//uart_transmit(received_byte);
				PORTB |= (1<<PB0);
				break;
				case '2':
				//uart_transmit(received_byte);
				PORTB |= (1<<PB1);
				break;
				case '3':
				PORTB |= (1<<PB2);
				//uart_transmit(received_byte);
				break;
				case '4':
				PORTB |= (1<<PB3);
				//uart_transmit(received_byte);
				break;
				case '5':
				PORTB |= (1<<PB4);
				//uart_transmit(received_byte);
				break;
				default:
				new_data=0;
				PORTB = 0x00;
			}
				
			
		}
		_delay_ms(5);
    }
}



