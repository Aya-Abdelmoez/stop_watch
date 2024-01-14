/*
 * External_interrupt.c
 *
 *  Created on: Dec 12, 2023
 *      Author: Aya Mousa
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "External_interrupt.h"
#define NULL        ( (void *)0)
static volatile void (*g_int0_ptr_callBack)(void) = NULL;

ISR(INT0_vect){
	if(*g_int0_ptr_callBack != NULL){
		(*g_int0_ptr_callBack)();
	}
}
void int0_setCallBack(void (*a_ptr)(void))
{
	g_int0_ptr_callBack = a_ptr;
}


void INT0_INIT(EXTERNAL_INTERRUPT_SENSE sense)
{
	DDRD &= ~(1 << PD2);
	GICR |= 1 << INT0;
	SREG |= 1<< 7;
	if(sense == RISING_EDGE){
		MCUCR |= (1 << ISC01) | (1 << ISC00);
	}
	else if(sense == FAILLING_EDGE ){
		MCUCR |= (1 << ISC01);
	}
	else if(sense == HIGH_LEVEL){
		MCUCR |= (1 << ISC00);
	}
	else if(sense == LOW_LEVEL){
		MCUCR &= ~(1 << ISC00);
		MCUCR &= ~(1 << ISC01);
	}
}
/***********************************************************************************************************/
static volatile void (*g_int1_ptr_callBack)(void) = NULL;

ISR(INT1_vect){
	if(*g_int1_ptr_callBack != NULL){
		(*g_int1_ptr_callBack)();
	}
}
void int1_setCallBack(void (*a_ptr)(void))
{
	g_int1_ptr_callBack = a_ptr;
}


void INT1_INIT(EXTERNAL_INTERRUPT_SENSE sense)
{
	DDRD &= ~(1 << PD3);
	GICR |= 1 << INT1;
	SREG |= 1<< 7;
	if(sense == RISING_EDGE){
		MCUCR |= (1 << ISC10) | (1 << ISC11);
	}
	else if(sense == FAILLING_EDGE ){
		MCUCR |= (1 << ISC11);
	}
	else if(sense == HIGH_LEVEL){
		MCUCR |= (1 << ISC10);
	}
	else if(sense == LOW_LEVEL){
		MCUCR &= ~(1 << ISC10);
		MCUCR &= ~(1 << ISC11);
	}
}

/*******************************************************************************************************/
static volatile void (*g_int2_ptr_callBack)(void) = NULL;

ISR(INT2_vect){
	if(*g_int2_ptr_callBack != NULL){
		(*g_int2_ptr_callBack)();
	}
}
void int2_setCallBack(void (*a_ptr)(void))
{
	g_int2_ptr_callBack = a_ptr;
}


void INT2_INIT(EXTERNAL_INTERRUPT_SENSE sense)
{
	DDRB &= ~(1 << PB2);
	GICR |= 1 << INT2;
	SREG |= 1<< 7;
	if(sense == RISING_EDGE){
		MCUCSR |= (1 << ISC2);
	}
	else if(sense == FAILLING_EDGE ){
		MCUCSR &= ~(1 << ISC2);
	}

}
