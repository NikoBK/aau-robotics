/*
   exercise3.ino

    Created on: Nov 11, 2022,
    Author: Nikolaj Krebs,
    Lecture 4, Exercise 3 - simple arrays 1, Friday Oct. 14
*/

// int array of 5 values, taken from the lecture exercise slide.
int intArray[] = {10, 23, 7, 411, 53};

void setup()
{
  Serial.begin(9600);

  // Creates a int value that represents the value of the array.
  int arraySize = sizeof(intArray) / sizeof(int);

  // Creating a int 'i' that starts as 0.
  // 'i' represents where in the array we read from it.
  // Remember that the very first value in a array is 0.
  for (int i = 0; i < arraySize; i++) {
    // Print the value of each array entry.
    Serial.println((String)intArray[i]);
  }

  Serial.println("The size of the array is " + (String)arraySize);
}

// NOTE: We can complete this exercise all within the setup function as it would be
// pointless to run the same values over and over on loop.
// Just keep in mind the loop method must exist for it to compile.
void loop() { } // This can be kept the way it is. It does nothing :)