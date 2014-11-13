extern int *__data_start;
extern int *__data_end;
extern int *__bss_start;
extern int *__bss_end;
extern int *__heap_start;

int data_val = 0x70;
int bss_val = 0x0;

unsigned char array[100];
int j = 0;

void setup() {
  Serial.begin(9600);
  Serial.println((int)&__data_start , HEX);
  Serial.println((int)&__data_end , HEX);
  Serial.println((int)&__bss_start , HEX);
  Serial.println((int)&__bss_end , HEX);
  Serial.println((int)&__heap_start , HEX);

  Serial.println(SP, HEX);
  Serial.println(RAMEND, HEX);

  // Testing stack
  int stack = 0x15;
  Serial.println((int)&stack, HEX);

  //Testing heap
  int * heap = new int(0x15);
  Serial.println((int)heap, HEX);

  //Testing data
  Serial.println((int)&data_val, HEX);

  //Testing bss
  Serial.println((int)&bss_val, HEX);
  
  dd();
  
  Serial.print("dump ");
  for (int i = 0; i < j; i++) {
    Serial.print((int)array[i], HEX); Serial.print(" ");
  }
  Serial.println();
  void (*pf_aa)() = aa;
  Serial.print((int)pf_aa, HEX); Serial.print(" ");
  Serial.print((int)pf_aa << 1, HEX); Serial.println(" aa");
  void (*pf_bb)() = bb;
  Serial.print((int)pf_bb, HEX); Serial.print(" ");
  Serial.print((int)pf_bb << 1, HEX); Serial.println(" bb");
  void (*pf_cc)() = cc;
  Serial.print((int)pf_cc, HEX); Serial.print(" ");
  Serial.print((int)pf_cc << 1, HEX); Serial.println(" cc");
  void (*pf_dd)() = dd;
  Serial.print((int)pf_dd, HEX); Serial.print(" ");
  Serial.print((int)pf_dd << 1, HEX); Serial.println(" dd");
}


void aa() {
  volatile char a = 0x44;
  dumpStack();
}
void bb() {
  volatile char b = 0x55;
  aa();
}
void cc() {
  volatile char c = 0x66;
  bb();
}
void dd() {
  volatile char d = 0x77;
  cc();
}

void dumpStack() {
  for (char * i = (char*)(SP-1); (int)i <= RAMEND; i++) {
    array[j] = *i;
    j++;
  }
}

void loop() {

}
