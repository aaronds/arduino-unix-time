/**
 * Unix Time Cron Example.
 *
 * Demostration of a periodic action library for Arduino.
 *
 * Depends on: UnixTime and MillisRTC
 *
 * See Timer2RTC for a much better real time clock.
 */

#include <avr/interrupt.h>
#include <UnixTime.h>
#include <MillisRTC.h>
#include <UnixTimeCron.h>

MillisRTC clock;
UnixTimeCron cron;


void test_cron_action(unsigned long long time,void *data){
  Serial.print("Time: ");
  Serial.println((unsigned long) time);
}

void say_twenty_action(unsigned long long time,void *data){
  Serial.println("Twenty");
}

/**
 * A callback action will run the function above every ten seconds.
 */

UnixTimeCronCallbackAction sayTime(0,10,&test_cron_action,NULL);

/**
 * A callback action will run only when the time is 20.
 */

UnixTimeCronCallbackAction sayTwenty(20,0,&say_twenty_action,NULL);

void setup(){
  Serial.begin(9600);
  /**
   * Setup the clock.
   */
  clock.setTime(0);
  cron.init(&clock);
  cron.add(&sayTime);
  cron.add(&sayTwenty);
  Serial.println("Clock Started");
}

void loop(){
  cron.poll();
}
