/*
 * Virtual Class for a time source capable of suppling UnixTime.
 */

#ifndef __UNIXTIME
#define __UNIXTIME

class UnixTime {
	public:
		virtual unsigned long long getTime();
};

#endif
