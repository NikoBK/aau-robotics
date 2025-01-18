/*
   exercise2.ino

    Created on: Nov 11, 2022,
    Author: Nikolaj Krebs,
    Lecture 5, Exercise 2 - Scope of the variables., Friday Oct. 28 (moved to Friday Nov. 4)
*/ 

int myCounterGlobal = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int iterations = 5;
  int myCounterLocal = 0;

  for (int i = 0; i < iterations; i++) {
    Serial.println("-------------------------------");
    Serial.println("myCounterGlobal value is currently: " + (String)myCounterGlobal + ". We are adding: " + (String)i + " to myCounterGlobal.");
    Serial.println("myCounterLocal value is currently: " + (String)myCounterLocal + ". We are adding: " + (String)i + " to myCounterLocal.");
    increment(i, myCounterGlobal);
    increment(i + 1, myCounterLocal);
    Serial.println("myCounterGlobal has been incremented with: " + (String)i + ". myCounterGlobal is now: " + (String)myCounterGlobal);
    Serial.println("myCounterLocal has been incremented with: " + (String)i + ". myCounterLocal is now: " + (String)myCounterLocal);
    delay(4500);
  }
}

// Adds whatever value of the parameter 'inc' of type int is, to 'counter'.
void increment(int inc, int &counter)
{
  counter += inc;
}
