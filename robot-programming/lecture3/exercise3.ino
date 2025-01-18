/*
   exercise3.ino

    Created on: Oct 5, 2022,
    Author: Nikolaj Krebs,
    Lecture 3, Exercise 3 - while and a button, Friday Sep. 30
*/ 

#include <Zumo32U4.h> // We now need to include the Zumo.h library to use onboard buttons.

Zumo32U4ButtonA aButton; // The A-button on the Zumo board.
int yellowLED = 13; // The pin for the yellow LED.

void setup()
{
  Serial.begin(9600);

  // Make sure we can write to the yellow LED pin:
  pinMode(yellowLED, OUTPUT);
}

void loop()
{
  // As long as the button is not pressed the yellow light is off.
  digitalWrite(yellowLED, LOW);

  // buttonA.isPressed returns a bool value of true as long as it is pressed down, and false when released.
  while (aButton.isPressed()) {
    digitalWrite(yellowLED, HIGH); // Turn on the yellow LED.
  }
}