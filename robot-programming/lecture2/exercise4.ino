/*
   exercise4.ino

    Created on: Oct 5, 2022,
    Author: Nikolaj Krebs,
    Lecture 2, Exercise 4 - if-else, Friday Sep. 23
*/ 

int randomMinimum = 0; // The smallest random number we can get.
int randomMaximum = 101; // The largest random number we can get. random() will only ever go as high as the max - 1.
int randomNumber; // The value for this will be randomly assigned in loop().
int iterations = 0; // The amount of times we have iterated through the loop() function. 0 on startup (0 iterations).
int above60Count = 0; // How many times the randomly generated number (randomNumber) is above 60. 0 on startup.
int below30Count = 0; // How many times the randomly generated number (randomNumber) is below 30. 0 on startup.
int betweenCount = 0; // How many times the randomly generated number (randomNumber) is between 30 and 60. 0 on startup.

void setup()
{
  // If you do not know what this code does, at this point.
  // Please read the comments in exercise 1 and 2.
  Serial.begin(9600);

  // If analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  // In summary this ensures better randomness when using random().
  randomSeed(analogRead(0));
}

void loop()
{
  randomNumber = random(randomMinimum, randomMaximum); // Generate our random number.

  // Check if the random number is above 60:
  if (randomNumber > 60){
    above60Count++; // If it is, we add 1 to the count of above 60's.
  }
  // If it is NOT above 60, check if it is below 30:
  else if (randomNumber < 30){
    below30Count++; // If it is, we add 1 to the count of below 30's.
  }
  // If it is neither above 60 or below 30. We know it has to be a number inbetween 30 and 60.
  else {
    betweenCount++; // If it is, we add 1 to the count of inbetween 30 and 60's.
  }

  delay(500); // The exercise requires us to generate a new random number every half second (500ms);
  iterations++; // ++ just adds 1 to count of iterations. Example: 0++ is 1, and 1++ is 2, and so on. It is the same as saying += 1.

  // Here we print:
  // How many iterations we have run, how many times we have generated a number above 60 so far, lower than 30 so far, and the rest, which are how many that has been inbetween 30 and 60 so far.
  Serial.println("Number of values read = " + (String)iterations + "; Higher than 60 = " + (String)above60Count + " ; Lower than 30 = " + (String)below30Count + " ; Rest = " + (String)betweenCount);
}