#include "MillisRTC.h"

#define MILLISECONDS_PER_SECOND 1000
#define MILLIS_MAX_VALUE 4294967295

MillisRTC::MillisRTC(){
	lastMillis = millis();
	unixTime = 0;
}
/*
 * Compare current value of millis() with the last observed value 
 * and increment unixTime accordingly.
 */

unsigned long long MillisRTC::getTime(){
	unsigned long curMillis = millis();
	if(curMillis == lastMillis){
		return unixTime;
	}else if(curMillis > lastMillis){
		unsigned long seconds = (curMillis - lastMillis) / MILLISECONDS_PER_SECOND;
		if(seconds){
			lastMillis += seconds * MILLISECONDS_PER_SECOND;
			unixTime += seconds;
			return unixTime;
		}else{
			return unixTime;
		}
	}else if(curMillis < lastMillis){
		/*Overflow*/
		unsigned long tmpLastMillis = curMillis + (MILLIS_MAX_VALUE - lastMillis);
		unixTime += (tmpLastMillis / MILLISECONDS_PER_SECOND);
		lastMillis = (curMillis / MILLISECONDS_PER_SECOND) * MILLISECONDS_PER_SECOND;
		return unixTime;
	}
}

void MillisRTC::setTime(unsigned long long time){
	lastMillis = millis();
	unixTime = time;
}
