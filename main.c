/*
 * main.c
 *
 *  Created on: Jan 2, 2024
 *      Author: lenovo
 */
#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/delay.h>

enum {yellow , green ,red} ;

int main () {

	DDRC = 0xFF ;
	DDRA = 0x0F ;

	PORTC = 0 ;
	PORTA = 0  ;

	char wait_time =12 ;
	unsigned char traffic_color =  red ;
	unsigned char right_segment ;
	unsigned char left_segment  ;
	PORTA |= (1<<PA0) ; //turn on the red led

	PORTC = 0x00 ;

	while (1) {

		if (traffic_color == red  ) {
			PORTA &= ~(1<<PA1) ; //turn OFF the yellow led
			PORTA |= (1<<PA0) ; //turn on the red led
			right_segment = wait_time % 10 ; // get the reminder of 25 == > 5
			right_segment = (right_segment << 4) ; //shift the reminder 4 bits to the right to display on the most significant bits
			PORTC = (PORTC & 0x0F) | (right_segment & 0xF0) ;//display 5 on the most significant bits
			left_segment = wait_time / 10 ; //get number 2 from 25 (25/10) = 2.5 == > 2
			PORTC = (PORTC & 0xF0) | (left_segment & 0x0F) ; //display 2 on the least significant bits
			wait_time -- ;
			_delay_ms (500) ;
			if (wait_time == 0) {
				traffic_color = green ;
				wait_time =12 ;
			}
		}
		if ( traffic_color == green  ) {
			PORTA &= ~(1<<PA0) ; //turn OFF the red led
			PORTA |= (1<<PA2) ; //turn on the Green led
			right_segment = wait_time % 10 ;
			right_segment = (right_segment << 4) ;
			PORTC = (PORTC & 0x0F) | (right_segment & 0xF0) ;
			left_segment = wait_time / 10 ;
			PORTC = (PORTC & 0xF0) | (left_segment & 0x0F) ;
			wait_time -- ;
			_delay_ms (500) ;
			if (wait_time == 0) {
			traffic_color = yellow ;
			wait_time = 5 ;
			}

		}
		if ( traffic_color == yellow  ) {
		PORTA &= ~(1<<PA2) ; //turn OFF the green led
		PORTA |= (1<<PA1) ; //turn on the yellow led
		right_segment = wait_time % 10 ;
		right_segment = (right_segment << 4) ;
		PORTC = (PORTC & 0x0F) | (right_segment & 0xF0) ;
		wait_time -- ;
		_delay_ms (500) ;
		if (wait_time ==0 ) {
			traffic_color = red ;
			wait_time =12 ;
		}
}

	}
	}
