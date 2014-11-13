static int clockPrescaler = 0;

void setup() {
  Serial.begin(9600);
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  
  // disable a bunch of things to save current
  ADCSRA &= ~_BV(ADEN);
  ACSR |= _BV(ACD);
  DIDR0 |= _BV(ADC5D) | _BV(ADC4D) | _BV(ADC3D) | _BV(ADC2D) | _BV(ADC1D) | _BV(ADC0D);
  DIDR1 |= _BV(AIN1D) | _BV(AIN0D);
  PRR |= _BV(PRTWI) | _BV(PRTIM2) | _BV(PRTIM0) | _BV(PRTIM1) | _BV(PRSPI) | _BV(PRUSART0) | _BV(PRADC);
  
}

void loop() {
  CLKPR = 128;
  CLKPR = clockPrescaler;
  
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  my_delay();              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  my_delay();              // wait for a second
  
  clockPrescaler++;
  clockPrescaler %= 9; // we go up and including 8.
}

void my_delay() {
  unsigned long count = 1403200UL / (unsigned long) pow(2, clockPrescaler);
  
  for (volatile unsigned long i = 0; i < count; i++);
}
