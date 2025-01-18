/*
   exercise2.ino

    Created on: Nov 10, 2022,
    Author: Nikolaj Krebs,
    Lecture 4, Exercise 2 - for loop increasing the iterations, Friday Oct. 14
*/ 

int iterations = 2; // How many times we want to iterate. NOTE: We start at 2 and increase this over time.

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Print the max iteraions per loop.
  Serial.println("------ new loop with max iterations = " + (String)iterations + "------");

  // We create a new int called "i" which starts on 0.
  // as long as i is less than iterations (10) we add one to i
  // and do all the code inside of the for loop.
  for (int i = 0; i < iterations; i++) {
    // As we increase i, we print i as a string.
    Serial.println("iteration " + (String)i);
  }

  // The follow code will only run once the for loop has been complete.
  // Add 2 to 'iterations' everytime we finish iterating through the for loop.
  iterations += 2;

  // This delay is not a requirement for the exercise
  // but it makes the reading process a lot easier ;)
  delay(1000);
}