volatile bool toggleLED1 = false;
volatile bool toggleLED2 = false;

void isr1() {
  toggleLED1 = true;
}

void isr2() {
  toggleLED2 = true;
}

void setup() {
  pinMode(2, INPUT);  // Interrupt source 1
  pinMode(3, INPUT);  // Interrupt source 2

  pinMode(8, OUTPUT); // LED 1
  pinMode(9, OUTPUT); // LED 2

  attachInterrupt(digitalPinToInterrupt(2), isr1, RISING);
  attachInterrupt(digitalPinToInterrupt(3), isr2, RISING);
}

void loop() {
  if (toggleLED1) {
    toggleLED1 = false;
    digitalWrite(8, !digitalRead(8));
  }

  if (toggleLED2) {
    toggleLED2 = false;
    digitalWrite(9, !digitalRead(9));
  }
}
