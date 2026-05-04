/*
 * voice-control-led.c
 *
 * Created: 5/3/2026 5:49:21 PM
 * Author : Roger Trinidad
 */ 

// This code contains UART functions for turning on motors based on the
// message received from UART. The design uses an ATMega328P micro controller.

#define F_CPU 16000000UL
#include <avr/io.h>


// initialize UART (9600 baud rate)
void UART_init(){
	uint16_t ubrr = 103; // for 16mhz at 9600 br

	UBRR0H = (ubrr >> 8);
	UBRR0L = ubrr;

	UCSR0B = (1 << RXEN0); // enable receiver
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data
}

void UART_sendChar(char data){
    while (!(UCSR0A & (1 << UDRE0))); // wait until transmit buffer empty
    UDR0 = data;
}

// receive one character
char UART_receive(){
	while(!(UCSR0A & (1 << RXC0))); // Wait for data
	return UDR0;
}

void UART_sendString(const char *str){
    while (*str){
        UART_sendChar(*str);
        str++;
    }
}

void UART_receiveString(char *buffer, uint8_t max_len){
    uint8_t i = 0;
    char c;

    while (i < (max_len - 1)){
        c = UART_receive();

        if (c == '\n' || c == '\r'){
            break;
        }

        buffer[i++] = c;
    }

    buffer[i] = '\0'; // null terminate
}


// main program that implements the outputs to 4 leds
// it maps the characters F, B, L, R (forward, back, left, right)
int main(void){
	// set pd2-pd5 as outputs
	DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);

	UART_init();

	while(1){
        
		// the rx will receive a character command
		char cmd = UART_receive();

		// Turn all outputs OFF first (default) evertime a message is received
		PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5));

		// Mapping commands to the motor controller

        /*
        Motors Forward: IN1 HIGH, IN2 LOW, IN3 HIGH,  IN4 LOW
        MOTORS BACKWARD: IN1 LOW, IN2 HIGH, IN3 LOW, IN4 HIGH
        CAR TURN LEFT: MOTOR A SLOWER, MOTOR B FASTER
        CAR TURN RIGHT: MOTOR A FASTER, MOTOR B SLOWER

        IN1 = PD2
        IN2 = PD3
        IN3 = PD4
        IN4 = PD5

        */

		if (cmd == 'F'){ 
			PORTD |= (1 << PD2) | (1 << PD4);
            PORTD &= ~((1 << PD3) | (1 << PD5));
		}
		else if (cmd == 'B'){
			PORTD |= (1 << PD3);
		}
		else if (cmd == 'L'){
			PORTD |= (1 << PD4);
		}
		else if (cmd == 'R'){
			PORTD |= (1 << PD5);
		}
		else if (cmd == 'S'){
			// already off because all LEDs turn off per command received
		}

	}
}

