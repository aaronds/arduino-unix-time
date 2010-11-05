/**
 * UnixTimeCron - perform a time dependend action.
 */

#ifndef __UNIX_TIME_CRON
#define __UNIX_TIME_CRON

#include <UnixTime.h>

extern "C" {
	#include <string.h>
}

class UnixTimeCronAction {
	public:
		/**
		 * constructor.
		 *
		 * if repeat = 0 then the action will be triggered when the clock.getTime() == time.
		 * else action will be triggered every repeat seconds offset by time.
		 *
		 */ 
		UnixTimeCronAction(unsigned long long time,unsigned long long repeat);
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

		UnixTimeCronAction *next;
};

class UnixTimeCronCallbackAction : public UnixTimeCronAction {
	public:
		/**
		 * A simple callback action will call 'cb' when the action is triggered data is also passed to the callback.
		 */

		UnixTimeCronCallbackAction(unsigned long long time,unsigned long repeat,void (*cb) (unsigned long long time,void *data),void *data); 
		void go(unsigned long long time);
		
		void *data;
		void (*callback) (unsigned long long time,void *data);

};



class UnixTimeCron {

	public:
		UnixTimeCron();


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
		void add(UnixTimeCronAction *action);
		
		/**
		 * rem.
		 *
		 * Remove an action.
		 */
		void rem(UnixTimeCronAction *action);

		/**
		 * The last time poll was called.
		 */
		unsigned long long lastPoll;

		/**
		 * The first action associated with this poll.
		 */
		UnixTimeCronAction *first;

		/**
		 * The clock.
		 */
		UnixTime *rtc;
};

#endif
