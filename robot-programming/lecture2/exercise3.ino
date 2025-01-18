/*
   exercise3.ino

    Created on: Oct 5, 2022,
    Author: Nikolaj Krebs,
    Lecture 2, Exercise 3 - Random numbers, Friday Sep. 23
*/ 

int randomMinimum = 200; // The smallest random number we can get.
int randomMaximum = 1000; // The largest random number we can get.
int randomDelay; // We will set this value in the loop.

int yellowLED = 13; // The LED on pin13.

void setup()
{
  // if you do not know what this does at this point, 
  // go back to exercise 1 and 2 and read the comments.
  Serial.begin(9600);

  // Make sure we can write to pin13.
  pinMode(yellowLED, OUTPUT);

  // If analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  // In summary this ensures better randomness when using random().
  randomSeed(analogRead(0));
}

void loop()
{
    randomDelay = random(randomMinimum, randomMaximum); // This will be a different value everytime loop starts over.
    Serial.println("Blinking period = " + (String)randomDelay); // Print the randomly generated delay time.
    digitalWrite(yellowLED, HIGH); // Turn the LED on.
    delay(randomDelay); // Leave it on for the random generated amount of time.
    digitalWrite(yellowLED, LOW); // Turn it off after the time has expired.
    delay(randomDelay); // Wait for the same randomized time before generating a new random time and doing all this again.
}