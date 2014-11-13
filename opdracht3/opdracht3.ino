// Pin definitions
#define SLIDER1  0
#define SLIDER2  1
#define SLIDER3  2
#define LIGHT    3
#define TEMP     4
#define KNOCK    5

#define BUZZER   3
#define DATA     4
#define LED1     5
#define LED2     6
#define LATCH    7
#define CLOCK    8
#define BUTTON1  10
#define BUTTON2  11
#define BUTTON3  12

int previousValueSlider = 0;
boolean dotState = false;
long dotTimer = 0;

const uint8_t displayCharSet[] = 
{
  // each byte represent one appearance of the 8-segment display
  // each bit in a byte represent one segment of the 8-segment display
  0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92,  0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};

void inc_8segment()
{
  static int i = 0;
  uint8_t val;

  val = displayCharSet[i];
  if (dotState) {
      val = val & ~(_BV(7));
  }

  digitalWrite(LATCH,LOW);
  shiftOut(DATA,CLOCK,MSBFIRST,val);  
  digitalWrite(LATCH,HIGH);

  i++;
  i %= sizeof (displayCharSet);
}

ISR(TIMER1_COMPA_vect) {
  dotTimer += OCR1A;
  //250000 is 1 seconde
  if (dotTimer >= 250000) {
    dotTimer -= 250000;
    dotState = !dotState;
  }
    inc_8segment();
}

ISR(PCINT0_vect) {
  static boolean state = false;

  state = !state;
  digitalWrite(LED1, state ? HIGH : LOW);
}

void setup() {

  Serial.begin(9600);
  
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);

  digitalWrite(BUTTON1, HIGH);
  digitalWrite(BUTTON2, HIGH);
  digitalWrite(BUTTON3, HIGH);

  pinMode(BUZZER, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);

  //Interrupt
  PCMSK0 |= _BV(PCINT3); //PCINT3 is digital pin 11.
  PCIFR |= _BV(PCIF0); // clear de value van de interrupt.
  PCICR  |= _BV (PCIE0); // set interrupts voor pcint0-7 aan.
  sei();

  //Timer
  TCCR1A = 0; // reset
  TCCR1B = 0; //reset

  OCR1A = 65535;

  TIFR1  |= _BV(OCF1A);   // clear any outstanding interrupts

  TCCR1B |= _BV(WGM12); //CTC modus

  TCCR1B |= _BV(CS10); // voor prescaler 64
  TCCR1B |= _BV(CS11); // idem


  TIMSK1 = 0;
  TIMSK1 |= _BV(OCIE1A); //  Output Compare A Match Interrupt Enable
}

void loop() {
  int currentValueSlider = analogRead(SLIDER1);
  
  // have a margin of 2, because slider was not exact.
  if (currentValueSlider > (previousValueSlider + 2) || currentValueSlider < (previousValueSlider - 2)) {
    Serial.println(currentValueSlider);
    cli();
    OCR1A = map(currentValueSlider, 0, 1023, 1000, 65535);
    sei();
    previousValueSlider = currentValueSlider;
  }
}


