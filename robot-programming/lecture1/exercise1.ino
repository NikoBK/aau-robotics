/*
   exercise1.ino

    Created on: Oct 3, 2022,
    Author: Nikolaj Krebs,
    Lecture 1, Exercise 1 - Arduino Hello World, Friday Sep. 16
*/ 

/* Summary:
    Simple code based on the blink example code. This code
    blinks pin 17, at every 250th milliseconds.
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(17, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(17, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(250);                       // wait for a second
  digitalWrite(17, LOW);    // turn the LED off by making the voltage LOW
  delay(250);                       // wait for a second
}

