/**
 * Unix Time Chron Example.
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
#include <UnixTimeChron.h>

MillisRTC clock;
UnixTimeChron chron;


void test_chron_action(unsigned long long time,void *data){
  Serial.print("Time: ");
  Serial.println((unsigned long) time);
}

void say_twenty_action(unsigned long long time,void *data){
  Serial.println("Twenty");
}

/**
 * A callback action will run the function above every ten seconds.
 */

UnixTimeChronCallbackAction sayTime(0,10,&test_chron_action,NULL);

/**
 * A callback action will run only when the time is 20.
 */

UnixTimeChronCallbackAction sayTwenty(20,0,&say_twenty_action,NULL);

void setup(){
  Serial.begin(9600);
  /**
   * Setup the clock.
   */
  clock.setTime(0);
  chron.init(&clock);
  chron.add(&sayTime);
  chron.add(&sayTwenty);
  Serial.println("Clock Started");
}

void loop(){
  chron.poll();
}
