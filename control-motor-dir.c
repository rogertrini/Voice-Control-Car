/*
 * voice-control-led.c
 *
 * Created: 5/3/2026 5:49:21 PM
 * Author : Roger Trinidad
 */ 

// This code contains UART functions for turning on motors based on the
// message received from UART. The design uses an ATMega328P micro controller.
// This specific design implements the PWM signal to control the speed
// of the motors. This gives a simple left and right direction control.
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// initialize UART (9600 baud rate)
void UART_init(){
	uint16_t ubrr = 103; // for 16mhz at 9600 br

	UBRR0H = (ubrr >> 8);
	UBRR0L = ubrr;
    // enable receiver and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); 
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

// --------------------------- PWM + DIR CTRL ----------------------------
/* Add the PWM signal for motor speed control*/
void PWM_init(){
    // PB1 = 0C1A, PB2 = 0C1B as outputs
    DDRB |= (1 << PB1) | (1 << PB2);

    // Fast PWM 8-bit, non-inverting mode
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 <<WGM10);
    TCCR1B = (1 << WGM12) | (1 << CS11); // prescaler = 8

    // 0CR1A and 0CR1B control the duty cycles on those pins
    // 128 = about 50% and 255 = full speed

    // initially be stopped (speed = 0 %)
    OCR1A = 0; // ENA speed
    OCR1B = 0; // ENB speed
}

// speed helper funtions
void setSpeed(uint8_t leftSpeed, uint8_t rightSpeed){
    OCR1A = leftSpeed; // ENA
    OCR1B = rightSpeed; // ENB
}

void clearDirectionPins(){
    PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5));
}

void stopMotors(){
    setSpeed(0,0);
    PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5));
}

// -------------------------------- main ------------------------------------
// main program that implements the outputs to 4 leds
// it maps the characters F, B, L, R (forward, back, left, right)
int main(void){
	// set pd2-pd5 as outputs
	DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);

	UART_init();
    PWM_init();

	while(1){
        
		// the rx will receive a character command
		char cmd = UART_receive();

		// Turn all outputs OFF first (default) evertime a message is received
		// use new helper function
        clearDirectionPins();

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
            // both sides forward
            PORTD |= (1 << PD2) | (1 << PD4);
            setSpeed(180,180);
            _delay_ms(4000);
            stopMotors();
        }
        else if (cmd == 'B'){
            // both sides backward
            PORTD |= (1 << PD3) | (1 << PD5);
            setSpeed(180,180);
            _delay_ms(4000);
            stopMotors();
        }
        else if (cmd == 'L'){
            // turn left
            PORTD |= (1 << PD2) | (1 << PD4);
            setSpeed(180,255);
            _delay_ms(4000);
            stopMotors();
        }
        else if (cmd == 'R'){
            // turn right
            PORTD |= (1 << PD2) | (1 << PD4);
            setSpeed(255, 180);
            _delay_ms(4000);
            stopMotors();
        }
        else if (cmd == 'S'){
            stopMotors();
        }

	}
}

