// Spark Interval Timer demo
//
// This demo will create three Interval Timers (maximum allowed) to blink three
// LEDs at different intervals.  The first timer will blink the onboard LED
// while 2 extra LEDs (and small current limiting resistors) must be added
// by the user on pins D3 and D4.  After 100 blinks, Timer1 will reset to 1/4
// of its interval and after 200 more blinks, Timer1 is shut down and
// will stop blinking.


#include "SparkIntervalTimer.h"


//SYSTEM_MODE(MANUAL);

// Create 3 IntervalTimer objects
IntervalTimer myTimer;
IntervalTimer myTimer2;
IntervalTimer myTimer3;
#if (PLATFORM_ID == 6)
IntervalTimer myTimer4;
IntervalTimer myTimer5;
#endif

// Pre-define ISR callback functions
void blinkLED(void);
void blinkLED2(void);
void blinkLED3(void);
#if (PLATFORM_ID == 6)
void blinkLED4(void);
void blinkLED5(void);
#endif

const uint8_t ledPin = D7;		// LED for first Interval Timer
const uint8_t ledPin2 = D3;		// LED for second Interval Timer
const uint8_t ledPin3 = D4;		// LED for third Interval Timer
#if (PLATFORM_ID == 6)
const uint8_t ledPin4 = D5;
const uint8_t ledPin5 = D6;
#endif

void setup(void) {
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
 #if (PLATFORM_ID == 6)
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
#endif
  
  // AUTO allocate blinkLED to run every 500ms (1000 * .5ms period)
  myTimer.begin(blinkLED, 1000, hmSec);

  // Manually allocate blinkLED2 to hardware timer TIM4 to run every 250ms (500 * .5ms period)  
  myTimer2.begin(blinkLED2, 500, hmSec);
  
  // Manually allocate blinkLED3 to hardware timer TIM3 blinkLED to run every 1000ms (2000 * .5ms period)
  myTimer3.begin(blinkLED3, 2000, hmSec);
  
#if (PLATFORM_ID == 6)
  // Manually allocate blinkLED4 to hardware timer TIM6 to run every 250ms (500 * .5ms period)  
  myTimer4.begin(blinkLED4, 300, hmSec);
  
  // Manually allocate blinkLED5 to hardware timer TIM7 blinkLED to run every 1000ms (2000 * .5ms period)
  myTimer5.begin(blinkLED5, 3000, hmSec);
#endif
}

// The first TIMER interrupt will blink the LED, and keep
// track of how many times it has blinked.  The other 
// two timers only blink their LEDs

volatile unsigned long blinkCount = 0; // use volatile for shared variables

// functions called by IntervalTimer should be short, run as quickly as
// possible, and should avoid calling other functions if possible.

// Callback for Timer 1
void blinkLED(void) {
	digitalWrite(ledPin,!digitalRead(ledPin));
    blinkCount++;		// increase when LED turns on
}

// Callback for Timer 2
void blinkLED2(void) {
	digitalWrite(ledPin2,!digitalRead(ledPin2));
}

// Callback for Timer 3
void blinkLED3(void) {
	digitalWrite(ledPin3,!digitalRead(ledPin3));
}

 #if (PLATFORM_ID == 6)
// Callback for Timer 4
void blinkLED4(void) {
	digitalWrite(ledPin4,!digitalRead(ledPin4));
}

// Callback for Timer 5
void blinkLED5(void) {
	digitalWrite(ledPin5,!digitalRead(ledPin5));
}
#endif

// The main program will print the blink count
// to the Arduino Serial Monitor
void loop(void) {
//  unsigned long blinkCopy;  // holds a copy of the blinkCount

  // to read a variable which the interrupt code writes, we
  // must temporarily disable interrupts, to be sure it will
  // not change while we are reading.  To minimize the time
  // with interrupts off, just quickly make a copy, and then
  // use the copy while allowing the interrupt to keep working.
//  noInterrupts();
//  blinkCopy = blinkCount;
//  interrupts();
/*
  if (blinkCount == 200)	{			// After 100 blinks, shut down timer 1
    blinkCount++;						// increment count so IF does not keep passing
	myTimer.resetPeriod_SIT(250, hmSec);
	}
  else if (blinkCount >= 400) {			// After 100 blinks, shut down timer 1
	blinkCount = 0;						// reset count so IF does not keep passing
	myTimer.end();
	}
*/
}
