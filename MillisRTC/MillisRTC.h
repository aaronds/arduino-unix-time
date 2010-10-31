/**
 * A unix time clock using millis (i.e not very accurate)
 */

#ifndef __MILLIS_RTC
#define __MILLIS_RTC

#include <WProgram.h>
#include <UnixTime.h>

class MillisRTC : public UnixTime {

	public:
		MillisRTC();
		unsigned long long getTime();
		void setTime(unsigned long long time);

	private:
		unsigned long long unixTime;
		unsigned long lastMillis;

};

#endif
