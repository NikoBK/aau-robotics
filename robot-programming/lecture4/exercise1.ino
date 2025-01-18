/*
   exercise1.ino

    Created on: Nov 10, 2022,
    Author: Nikolaj Krebs,
    Lecture 4, Exercise 1 - for loop, Friday Oct. 14
*/ 

int iterations = 10; // How many times we want to iterate.

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // We create a new int called "i" which starts on 0.
  // as long as i is less than iterations (10) we add one to i
  // and do all the code inside of the for loop.
  for (int i = 0; i < iterations; i++) {
    // As we increase i, we print i as a string.
    Serial.println("iteration " + (String)i);
  }

  // This delay is not a requirement for the exercise
  // but it makes the reading process a lot easier ;)
  delay(1000);
}
