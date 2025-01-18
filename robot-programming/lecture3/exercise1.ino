/*
   exercise1.ino

    Created on: Oct 5, 2022,
    Author: Nikolaj Krebs,
    Lecture 3, Exercise 1 - switch, Friday Sep. 30
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
  char input = Serial.read(); // This is what you write into the Serial monitor.

  // Turn both off at the start of the loop to prevent two from being lit at the same time.
  digitalWrite(yellowLED, LOW); // Turn off the yellow LED.
  digitalWrite(greenLED, HIGH); // The green LED is not like the others. LOW = on and HIGH = off.

  // Make sure the Serial buffer has any data in it before we read anything.
  if (Serial.available() > 0)
  {
    // Make a switch that checks what the input is:
    switch(input)
    {
      // If the input is the char 'y':
      case 'Y': // This runs the same code for 'y' if you write a uppercase y 'Y'.
      case 'y':
        digitalWrite(yellowLED, HIGH); // Turns the yellow LED on when either a 'y' or 'Y' is received.
      break;

      // If the input is the char 'g':
      case 'G': // This runs the same code for 'g' if you write a uppercase g 'G'.
      case 'g':
        // Add this delay to prevent state override when sending data. 
        // This is because the tx LED, lights up when data is sent.
        delay(150); // I just keep the delay as small as possible, 100 ms is the lowest you can go. :)

        digitalWrite(greenLED, LOW);
      break;
    }
  }

  // Wait 2.5 seconds before turning all lights off again.
  delay(2500);
}
