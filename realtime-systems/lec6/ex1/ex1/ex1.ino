// Pin assignments
const int pinTask1 = 8;
const int pinTask2 = 9;
const int pinTask3 = 3;

// Timing configuration (ms)
const unsigned long Tp1 = 200;
const unsigned long Tp2 = 150;
const unsigned long Tp3 = 100;

const unsigned int Td1 = 40;
const unsigned int Td2 = 70;
const unsigned int Td3 = 40;  // Adjust this if needed later

// Last execution timestamps
unsigned long tLast1 = 0;
unsigned long tLast2 = 0;
unsigned long tLast3 = 0;

// Simulates CPU workload by blocking for eatTime ms
void do_eat_msec(unsigned int eatTime) {
  while (eatTime > 10) {
    delayMicroseconds(10000);
    eatTime -= 10;
  }
  delayMicroseconds(eatTime * 1000);
}

void setup() {
  pinMode(pinTask1, OUTPUT);
  pinMode(pinTask2, OUTPUT);
  pinMode(pinTask3, OUTPUT);
}

void loop() {
  unsigned long now = millis();

  // Task 1
  if ((unsigned long)(now - tLast1) >= Tp1) {
    tLast1 += Tp1;
    digitalWrite(pinTask1, HIGH);
    do_eat_msec(Td1);
    digitalWrite(pinTask1, LOW);
  }

  // Task 2
  if ((unsigned long)(now - tLast2) >= Tp2) {
    tLast2 += Tp2;
    digitalWrite(pinTask2, HIGH);
    do_eat_msec(Td2);
    digitalWrite(pinTask2, LOW);
  }

  // Task 3
  if ((unsigned long)(now - tLast3) >= Tp3) {
    tLast3 += Tp3;
    digitalWrite(pinTask3, HIGH);
    do_eat_msec(Td3);
    digitalWrite(pinTask3, LOW);
  }
}
