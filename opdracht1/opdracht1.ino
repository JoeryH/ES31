const int ledPin =  PORTD5;      // the number of the LED pin
const int ledPin2 =  PORTD6;      // the number of the LED pin

const int buttonOnePin = PINB2; // the number of the button pin
const int buttonTwoPin = PINB4; // the number of the button pin

const  int buzzerPin = PORTD3;

int ledState = LOW;             // ledState used to set the LED
int ledState2 = LOW;             // ledState used to set the LED

int buttonOneState = HIGH;
int buttonTwoState = HIGH;

void setup() {
  //pinMode(ledPin, OUTPUT);
  DDRD |= _BV(DDD5);
  //pinMode(ledPin2, OUTPUT);
  DDRD |= _BV(DDD6);
  DDRD |= _BV(DDD3);
  //pinMode(buttonOnePin, INPUT_PULLUP);
  DDRB &= ~_BV(DDB2);
  PORTB |= _BV(PORTB2);
  //pinMode(buttonTwoPin, INPUT_PULLUP);
  DDRB &= ~_BV(DDB4);
  PORTB |= _BV(PORTB4);
  
  Serial.begin(9600);
}

void loop()
{
  buttonOneState = (PINB & _BV(buttonOnePin)) != 0;
  buttonTwoState = (PINB & _BV(buttonTwoPin)) != 0;

  if (buttonOneState == LOW && buttonTwoState == LOW)
  {
    ledState = HIGH;
    ledState2 = HIGH;
    PORTD |= _BV(buzzerPin);
  }
  else if (buttonOneState == LOW)
  {
      ledState = HIGH;
      ledState2 = LOW;
  }
  else if (buttonTwoState == LOW)
  {
      ledState = LOW;
      ledState2 = HIGH;
      Serial.println("Hello world!");
  }
  else
  {
      ledState = LOW;
      ledState2 = LOW;
  }
  PORTD &= ~_BV(buzzerPin);
  //digitalWrite(ledPin, ledState);
  if (ledState) {
    PORTD |= _BV(ledPin);
  } else {
    PORTD &= ~_BV(ledPin);
  }
  //digitalWrite(ledPin2, ledState2);
  if (ledState2) {
    PORTD |= _BV(ledPin2);
  } else {
    PORTD &= ~_BV(ledPin2);
  }
}
