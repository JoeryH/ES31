int const constData = 6;
int const constBss = 0;

extern int *__data_start;
extern int *__data_end;
extern int *__bss_start;
extern int *__bss_end;
extern int *__heap_start;

void setup() {
  char variable = 0x10;
  char variable2 = 0x20;
  
  
  Serial.begin(9600);
  int const stack = 6;
  int * const heap = new int(7);
  Serial.println((int)&stack, HEX);
  Serial.println((int)heap, HEX);
  Serial.println((int)&constData, HEX);
  Serial.println((int)&constBss, HEX);

  Serial.println((int)&__data_start , HEX);
  Serial.println((int)&__data_end , HEX);
  Serial.println((int)&__bss_start , HEX);
  Serial.println((int)&__bss_end , HEX);
  Serial.println((int)&__heap_start , HEX);

  int x = 6;
  Serial.println((int)&x, HEX);
  parameter(x);
  parameterRef(x);

  delay(1000);

  start();

  Serial.println("setup done");
}

void parameter(int x) {
  Serial.println((int)&x, HEX);
}

void parameterRef(int const & x) {
  Serial.println((int)&x, HEX);
}

void loop() {
}

void start() {
  int * a1[150];
  int * a2[150];
  int * a3[150];
  int * a4[150];
  int * a5[150];
  for (int i = 0; i < 150; i++) {
    a1[i] = new int(10);
  }
  for (int i = 0; i < 150; i++) {
    a2[i] = new int(10);
  }
  for (int i = 0; i < 150; i++) {
    a3[i] = new int(10);
  }
  for (int i = 0; i < 150; i++) {
    a4[i] = new int(10);
  }
  for (int i = 0; i < 150; i++) {
    a5[i] = new int(10);
  }
  
  for (int i = 0; i < 150; i++) {
    delete a2[i];
  }
  
  for (int i = 0; i < 150; i++) {
    delete a4[i];
  }
  
  int * a6[150];
  for (int i = 0; i < 150; i++) {
    a6[i] = new int(10);
  }
}
