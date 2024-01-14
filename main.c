/*
 * main.c
 *
 *  Created on: Dec 17, 2023
 *      Author: Aya Mousa
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "common_Macros.h"
#include "External_interrupt.h"
#include <util/delay.h>
unsigned char g_hour = 0;
unsigned char g_minuts = 0;
unsigned char g_second = 0;
ISR (TIMER1_COMPA_vect){
	//enter here every one second
	//increment seconds count
	g_second++;
	if(g_second == 60){
		g_second = 0;
		g_minuts++;
	}
	if(g_minuts == 60){
		g_minuts = 0;
		g_hour++;
	}
	if(g_hour == 24){
		g_hour =0;
	}
}




void Timer1_CTC_init(){
	/* Configure timer1 control registers
	 * 1. Non PWM mode FOC1A=1 and FOC1B=1
	 * 2. No need for OC1A & OC1B in this example so COM1A0=0 & COM1A1=0 & COM1B0=0 & COM1B1=0
	 * 3. CTC Mode and compare value in OCR1A WGM10=0 & WGM11=0 & WGM12=1 & WGM13=0
	 */
	SET_BIT(TCCR1A,FOC1A);
	SET_BIT(TCCR1B,WGM12);
	TCNT1 = 0;   //timer initial value
	OCR1A = 977;
	SET_BIT(TIMSK,OCIE1A);
	/*
	 * 4. Clock = F_CPU/1024 CS10=1 CS11=0 CS12=1
     */
	SET_BIT(TCCR1B,CS10);
	SET_BIT(TCCR1B,CS12);


}
void INT0_processing(){
	g_hour = 0;
	g_minuts = 0;
	g_second = 0;
}
void INT1_processing(){
	// Pause the stop watch by disable the timer
	// Clear the timer clock bits (CS10=0 CS11=0 CS12=0) to stop the timer clock.
	CLEAR_BIT(TCCR1B,CS10);
	CLEAR_BIT(TCCR1B,CS12);

}
void INT2_processing(){
	// resume the stop watch by enable the timer through the clock bits.
	SET_BIT(TCCR1B,CS10);
	SET_BIT(TCCR1B,CS12);
}

int main(void){
	// configure first four pins of PORTC as output pins
	DDRC |= 0X0F;
	// configure first 6 pins in PORTA as output pins
	DDRA |= 0X3F;
	PORTD |= 1 << PD2;
	PORTB |= 1 << PB2;
	// Enable global interrupts in MC.
	SREG  |= (1<<7);
	// Start timer1 to generate compare interrupt every 1000 MiliSeconds(1 Second)
	Timer1_CTC_init();
	// Activate external interrupt INT0
	INT0_INIT(FAILLING_EDGE);
	int0_setCallBack(&INT0_processing);
	// Activate external interrupt INT1
	INT1_INIT(RISING_EDGE);
	int1_setCallBack(&INT1_processing);
	// Activate external interrupt INT2
	INT2_INIT(FAILLING_EDGE);
	int2_setCallBack(&INT2_processing);
	while(1){
		// out the number of seconds
		PORTA = (PORTA & 0XC0) | 0X01;
		PORTC = (PORTC  & 0XF0)  | (g_second%10);
		// make small delay to see the changes in the 7-segment
		// 2Miliseconds delay will not effect the seconds count
		_delay_ms(2);

		PORTA = (PORTA & 0XC0) | 0X02;
		PORTC = (PORTC  & 0XF0)  | (g_second/10);
	    _delay_ms(2);
	    // out the number of minutes
		PORTA = (PORTA & 0XC0) | 0X04;
		PORTC = (PORTC  & 0XF0)  | (g_minuts%10);
		_delay_ms(2);
		PORTA = (PORTA & 0XC0) | 0X08;
		PORTC = (PORTC  & 0XF0)  | (g_minuts/10);
		_delay_ms(2);
		  // out the number of hours
		PORTA = (PORTA & 0XC0) | 0X10;
		PORTC = (PORTC  & 0XF0)  | (g_hour%10);
		_delay_ms(2);
		PORTA = (PORTA & 0XC0) | 0X20;
		PORTC = (PORTC  & 0XF0)  | (g_hour/10);
		_delay_ms(2);

	}
}
