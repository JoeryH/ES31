#include <avr/sleep.h>
#include <avr/wdt.h>
static int k = 0;
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  WDTCSR |= _BV(WDCE) | _BV(WDE);
  WDTCSR = _BV(WDP3) + _BV(WDE) + _BV(WDIE);
  Serial.println("setup");
}

ISR(WDT_vect) {
  // empty
  //Serial.println("interrupt");
  //delay(10);
}

// the loop function runs over and over again forever
void loop() {
  Serial.println(k);
  if (k == 5) {
    SMCR |= _BV(SM1) | _BV(SE);
    sleep_cpu();
  }
  // reset the watch dog, because we are running normally.
  wdt_reset();
  
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);               // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(500);               // wait for a second
  k++;

}

