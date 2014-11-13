#define PI 3.14159265359

const int AMOUNT_SIN_VALUES = 360;
int previousValueSlider = 0;
uint8_t sinusValues[AMOUNT_SIN_VALUES];

void inc_sinus(int i)
{
  PORTD = i;
  digitalWrite(8, bitRead(i, 0));
  digitalWrite(9, bitRead(i, 1));
}

ISR(TIMER1_COMPA_vect) {
  static int i = 0;
  i++;
  inc_sinus(sinusValues[i]);
  i %= AMOUNT_SIN_VALUES;
}

int map(float value) {
  return (value + 1) * 255.0 / 2;
}

void setup() {
  Serial.begin(9600);

  //Generate Sin array
  for (int i = 0; i < AMOUNT_SIN_VALUES; i++) {
    sinusValues[i] = map(sin((2 * PI * (float)i) / AMOUNT_SIN_VALUES));
  }

  pinMode(A0, INPUT);
  //Setting analog input
  //Analog Comparator Multiplexer Enable bit
  ADCSRB |= _BV(ACME);
  //Enable ADC
  ADCSRA |= _BV(ADEN);
  //We set this to 1 to use internal reference Voltage.
  ADMUX |= _BV(REFS0);
  // We are going to use A0 so we set 000 to MUX.
  ADMUX &= ~_BV(MUX0) & ~_BV(MUX1) & ~_BV(MUX2);
  //Disable some power saving so we can use ADC.
  PRR &= ~_BV(PRADC);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  sei();

  //Timer
  TCCR1A = 0; // reset
  TCCR1B = 0; //reset

  OCR1A = 65535;

  TIFR1  |= _BV(OCF1A);   // clear any outstanding interrupts

  TCCR1B |= _BV(WGM12); //CTC modus

  TCCR1B |= _BV(CS10); // voor prescaler 1

  TIMSK1 = 0;
  TIMSK1 |= _BV(OCIE1A); //  Output Compare A Match Interrupt Enable
}

void loop() {
  //Start the conversion.
  ADCSRA |= _BV(ADSC);
  while (bitRead(ADCSRA, ADSC) == 1) {
    //Waiting till the ADC conversion is done
  }
  // We combine 2 and 8 bits to get 10 bits conversion.
  int low = ADCL;
  int high = ADCH;

  int currentValueSlider = (high << 8) | low;

  // have a margin of 2, because slider was not exact.
  if (currentValueSlider > (previousValueSlider + 2) || currentValueSlider < (previousValueSlider - 2)) {
    Serial.println(currentValueSlider);
    cli();
    OCR1A = map(currentValueSlider, 0, 1023, 1000, 65535);
    sei();
    previousValueSlider = currentValueSlider;
  }
}

