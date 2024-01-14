/*
 * External_interrupt.h
 *
 *  Created on: Dec 12, 2023
 *      Author: AA
 */

#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_

typedef enum{
	LOW_LEVEL,
	HIGH_LEVEL,
	RISING_EDGE,
	FAILLING_EDGE
}EXTERNAL_INTERRUPT_SENSE;

typedef enum{
	INVAILID_LOW_LEVEL,
	INVAILID_HIGH_LEVEL,
	INVAILID_RISING_EDGE,
	INVAILID_FAILLING_EDGE
}EXTERNAL_INTERRUPT_SENSE_ERROR;


void INT0_INIT(EXTERNAL_INTERRUPT_SENSE sense);
void int0_setCallBack(void (*a_ptr)(void));
void INT1_INIT(EXTERNAL_INTERRUPT_SENSE sense);
void int1_setCallBack(void (*a_ptr)(void));
void INT2_INIT(EXTERNAL_INTERRUPT_SENSE sense);
void int2_setCallBack(void (*a_ptr)(void));


#endif /* EXTERNAL_INTERRUPT_H_ */
