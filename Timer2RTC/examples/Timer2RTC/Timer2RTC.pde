/**
 * Timer2RTC example.
 *
 * DO NOT TRY TO USE THIS SKETCH ON AN UNMODIFIED ARDUIO IT
 * RELIES ON A 37Khz OSILLATOR.
 *
 * As the name sudgests it uses Timer 2 so you CAN NOT use pwm on pin 3
 * and 11.
 */
 
#include <UnixTime.h>
#include <Timer2RTC.h>

/*The clock*/
Timer2RTC clock;

/*A seconds counter, used to detect when time changes.*/
unsigned long long seconds = 0;

void setup(){
  Serial.begin(9600);
  Serial.println("Starting Clock");
  
  /* Initalize the clock, this configures the timer an zeros everything.*/
  
  clock.init();
}

void loop(){
  if(clock.getTime() != seconds){
    seconds = clock.getTime();
    Serial.println((long)seconds);
  }
}
