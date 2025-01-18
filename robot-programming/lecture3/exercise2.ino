/*
   exercise2.ino

    Created on: Oct 5, 2022,
    Author: Nikolaj Krebs,
    Lecture 3, Exercise 2 - while, Friday Sep. 30
*/ 

int yellowLED = 13; // The pin for the yellow LED.
int greenLED = 30; // The pin for the green LED.

void setup()
{
  Serial.begin(9600);

  // Make sure we can write to the yellow and green LED pins:
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop()
{
  digitalWrite(yellowLED, HIGH); // As long as we are not inside the while loop, the yellow LED will be lit, indicating idle station.
  digitalWrite(greenLED, HIGH); // Turn the green LED off when we are not inside the while loop. Remember; HIGH = off, LOW = on for the green led.

  // Serial.available() returns how many bytes of data there is in the serial monitor buffer.
  // When you type something in this value will increase and if you wrote anything we will jump inside
  // the while loop and run all the code inside it.
  while (Serial.available() > 0)
  {
    digitalWrite(yellowLED, LOW); // Turn off the yellow LED.

    delay(150); // Remember the delay needed.
    digitalWrite(greenLED, LOW); // Turn the green LED on while inside the while loop.

    char data = Serial.read(); // Get the text we wrote as a single char.
    Serial.println(data); // Print the char we just got above.
  }
}