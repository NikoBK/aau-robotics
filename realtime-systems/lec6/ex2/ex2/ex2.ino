volatile bool doTask = false;

ISR(TIMER1_COMPA_vect) {
  doTask = true;
}

void setup() {
  pinMode(8, OUTPUT);

  // Configure Timer1 for 100ms (10Hz)
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;

  OCR1A = 15624;             // Compare match register = 100ms
  TCCR1B |= (1 << WGM12);    // CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10);  // Prescaler 1024
  TIMSK1 |= (1 << OCIE1A);   // Enable timer compare interrupt
  interrupts();
}

void loop() {
  if (doTask) {
    doTask = false;
    digitalWrite(8, HIGH);
    delay(10);  // simulate task duration
    digitalWrite(8, LOW);
  }
}