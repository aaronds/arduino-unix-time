/**
 * UnixTimeChron - perform a time dependend action.
 */

#ifndef __UNIX_TIME_CHRON
#define __UNIX_TIME_CHRON

#include <UnixTime.h>

extern "C" {
	#include <string.h>
}

class UnixTimeChronAction {
	public:
		/**
		 * constructor.
		 *
		 * if repeat = 0 then the action will be triggered when the clock.getTime() == time.
		 * else action will be triggered every repeat seconds offset by time.
		 *
		 */ 
		UnixTimeChronAction(unsigned long long time,unsigned long long repeat);
		unsigned long long time;
		unsigned long long repeat;
		
		/**
		 * go.
		 *
		 * The method called by chron to trigger the action.
		 */
		virtual void go(unsigned long long time);

		/**
		 * next.
		 *
		 * The next item in the list of actions.
		 */

		UnixTimeChronAction *next;
};

class UnixTimeChronCallbackAction : public UnixTimeChronAction {
	public:
		/**
		 * A simple callback action will call 'cb' when the action is triggered data is also passed to the callback.
		 */

		UnixTimeChronCallbackAction(unsigned long long time,unsigned long repeat,void (*cb) (unsigned long long time,void *data),void *data); 
		void go(unsigned long long time);
		
		void *data;
		void (*callback) (unsigned long long time,void *data);

};



class UnixTimeChron {

	public:
		UnixTimeChron();


		/**
		 * init.
		 * 
		 * Initalize chron with the clock 'r'.
		 */
		void init(UnixTime *r);

		/**
		 * poll.
		 *
		 * Check for changes since the last time poll was called and fire the appropriate actions.
		 */
		void poll();

		/**
		 * add.
		 *
		 * Add an action to this chron.
		 */
		void add(UnixTimeChronAction *action);
		
		/**
		 * rem.
		 *
		 * Remove an action.
		 */
		void rem(UnixTimeChronAction *action);

		/**
		 * The last time poll was called.
		 */
		unsigned long long lastPoll;

		/**
		 * The first action associated with this poll.
		 */
		UnixTimeChronAction *first;

		/**
		 * The clock.
		 */
		UnixTime *rtc;
};

#endif
