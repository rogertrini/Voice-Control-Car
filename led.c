// This code contains UART functions for turning on an LED based on the 
// message received from UART. The design uses an ATMega328P microcontroller.

#define F_CPU 16000000UL
#include <avr/io.h>


// initialize UART (9600 baud rate)
void UART_init(){
    uint16_t ubbr 103; // for 16mhz at 9600 br

    UBBR0H = (ubbr >> 8);
    UBBR0L = ubbr;

    UCSR0B = (1 << RXEN0); // enable receiver
    UCSR0C (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data
}

// receive one character
char UART_receive(){
    while(!(UCSR0A & (1 << RXC0))); // Wait for data
    return UDR0;
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

        // Turn all LEDs OFF first (default) evertime a message is received
        PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5));

        // Turn on 1 LED per command
        if (cmd == 'F'){
            PORTD |= (1 << PD2);
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