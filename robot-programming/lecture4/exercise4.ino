/*
   exercise4.ino

    Created on: Nov 11, 2022,
    Author: Nikolaj Krebs,
    Lecture 4, Exercise 4 - simple arrays2, Friday Oct. 14
*/

// Our int array with the default values: 4, 3, 2, 1.
int intArray[] = {4, 3, 2, 1};

void setup()
{
  Serial.begin(9600);
}

// NOTE:
// When we reach array values of: [16384, 12288, 8192, 4096] things will
// look weird, because we exceed max values!
void loop()
{
  Serial.println("----- New Loop -----");

  // Size of our array. (See exercise 3 for better theorem on this).
  int arraySize = sizeof(intArray) / sizeof(int);

  for (int i = 0; i < arraySize; i++) {
    // Print the current value of the array entry of whatever i is, during this iteration.
    Serial.println((String)intArray[i]);

    // We can change the current value for the array entry of what i is, while we are still in the for
    // loop for printing each value. We print it first, and multiply it with 2 after so it is changed the next
    // time it is printed.
    intArray[i] = intArray[i] * 2;
  }

  // This delay is not a requirement for the exercise
  // but it makes the reading process a lot easier ;)
  delay(1000);
}