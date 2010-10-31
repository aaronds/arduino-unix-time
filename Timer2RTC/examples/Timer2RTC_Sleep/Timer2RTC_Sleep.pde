/**
 * Timer2RTC example - including sending the ardunio to sleep while waiting.
 *
 * DO NOT TRY TO USE THIS SKETCH ON AN UNMODIFIED ARDUIO IT
 * RELIES ON A 37Khz OSILLATOR.
 *
 * Sleeping stuf from:
 * http://www.arduino.cc/playground/Learning/ArduinoSleepCode
 *
 * WARNING: Serial and sleep modes don't play well together expect 
 * some random characters as it wakes up.
 */
 
#include <avr/sleep.h>
 
#include <UnixTime.h>
#include <Timer2RTC.h>

/*The clock*/
Timer2RTC clock;

/*A seconds counter, used to detect when time changes.*/
unsigned long long seconds = 0;

void toSleep(){
  /* See ATmega168 datasheet section 9.5: Timer 2 overflow wakes ardunio 
     from a 'deep' sleep.*/
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);
  sleep_enable();
  sleep_mode();
  sleep_disable();
}


void setup(){
  Serial.begin(9600);
  Serial.println("Starting Clock");
  
  /* Initalize the clock, this configures the timer an zeros everything.*/
  
  clock.init();
  sei();
}

void loop(){
  if(clock.getTime() != seconds){
    seconds = clock.getTime();
    Serial.println("   ");   
    /*Sleep mode and serial do not play well.*/
    Serial.println((long)seconds);
  }
  toSleep();
}
