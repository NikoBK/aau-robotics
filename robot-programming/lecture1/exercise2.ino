/*
   exercise2.ino

    Created on: Oct 3, 2022,
    Author: Nikolaj Krebs,
    Lecture 1, Exercise 2 - LED Carousel, Friday Sep. 16
*/ 

int onTimeMS = 2000; // How long each LED is on (in milliseconds). Set to 2 seconds.

// LED PINS
int leftIRIndicator = 5;
int rightIRIndicator = 19;
int txLed = 30;
int rxLed = 17;
int yellowLed = 13; // This is also LED_BUILTIN.

// The setup function runs once when you press reset or power the board.
void setup()
{
    // Setting all the following pins to OUTPUT mode, so we can write to them.
    pinMode(leftIRIndicator, OUTPUT);
    pinMode(rightIRIndicator, OUTPUT);
    pinMode(txLed, OUTPUT);
    pinMode(rxLed, OUTPUT);
    pinMode(yellowLed, OUTPUT);
}

// The loop function runs over and over again forever.
void loop() 
{
    // Turn the left IR Indicator LED on and off.
    digitalWrite(rightIRIndicator, LOW);
    digitalWrite(leftIRIndicator, HIGH);
    delay(onTimeMS);
    digitalWrite(rightIRIndicator, HIGH);
    digitalWrite(leftIRIndicator, LOW);
    delay(250); // This is just a delay to move on to the next LED, no need to change this.

    // Turn the right IR Indicator LED on and off (basically the same as the above code).
    digitalWrite(rightIRIndicator, HIGH);
    digitalWrite(leftIRIndicator, HIGH);
    delay(onTimeMS);
    digitalWrite(rightIRIndicator, LOW);
    digitalWrite(leftIRIndicator, LOW);
    delay(250);

    // Turn the RX LED ( The red one ) on and off.
    digitalWrite(rxLed, LOW);
    delay(onTimeMS);
    digitalWrite(rxLed, HIGH);
    delay(250);

    // Turn the TX LED ( The green one ) on and off.
    digitalWrite(txLed, LOW);
    delay(onTimeMS);
    digitalWrite(txLed, HIGH);
    delay(250);

    // Turn the yellow LED on and off.
    digitalWrite(yellowLed, HIGH);
    delay(onTimeMS);
    digitalWrite(yellowLed, LOW);
    delay(250);

    // At this point it will loop up back to the top of loop and restart the LED carousel.
}
