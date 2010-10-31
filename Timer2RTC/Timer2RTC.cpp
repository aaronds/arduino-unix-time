#include "Timer2RTC.h"

volatile unsigned long long __TIMER_2_RTC_CTIME = 0;
volatile bool __TIMER_2_RTC_UPDATE = false;

void Timer2RTC::init(){
	/**
	 * Adapted from AVR Application note 134
	 */

	/* Disable TC0 interupt. */
	TIMSK2 &= ~(( 1 << TOIE2));

	/*Set timer 2 to asyn mode*/
	ASSR |= (1 << AS2);

	/*Reset timer position.*/
	TCNT2 = 0x00;

	/*Prescale the clock source to 64 -> roughly 1 second for overflow.*/
	TCCR2B = 0x04;

	/*Wait for update to finish.*/
	while((ASSR & (1 << TCN2UB)));

	/*Go! (Ensure sei() has already been called or is called soon after)*/
	TIMSK2 |= (1 << TOIE2);
	setTime(0);
}

unsigned long long Timer2RTC::getTime(){
	return __TIMER_2_RTC_CTIME;
}

void Timer2RTC::setTime(unsigned long long time){
	__TIMER_2_RTC_CTIME = time;
}

ISR (TIMER2_OVF_vect){
	__TIMER_2_RTC_UPDATE = true;
	__TIMER_2_RTC_CTIME++;
}
