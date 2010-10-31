/**
 * A real time clock using Timer2.
 *
 * NB: THIS WILL NOT WORK WITH AN UNMODIFIED ARDUINO A 37.768Khz OSSILATOR IS REQUIRED.
 */

#ifndef __TIMER_2_RTC
#define __TIMER_2_RTC

#include <avr/interrupt.h>
#include <UnixTime.h>

class Timer2RTC : public UnixTime {

	public:
		void init();
		unsigned long long getTime();
		void setTime(unsigned long long time);
};

extern volatile unsigned long long __TIMER_2_RTC_CTIME;
extern volatile bool __TIMER_2_RTC_UPDATE;


ISR (TIMER2_OVF_vect);

#endif
