/*
   exercise2.ino

    Created on: Oct 5, 2022,
    Author: Nikolaj Krebs,
    Lecture 2, Exercise 2 - Strings, Friday Sep. 23
*/ 

String nameString = "Zumo"; // Strings use " because a string is multiple chars pieced together :)
char nameChar = 'W'; // Remember to always use ' for chars. Strings use " and chars use '.
int nameInt = 10;
float nameFloat = 0.23;

// This bool value is really bad practice. Please always use 'true' or 'false' instead of 1 and 0 for a bool.
// For this exercise I will use 1 for the bool to do the exercise but please always use true/false!! :)
bool nameBool = 1;

String charName, intName, floatName, boolName; // All the names made with string and various datatype combinations.

void setup()
{
  // Remember you always want to do this if you want to use the
  // serial monitor. If not you do not need this line of code. For all
  // exercises the serial monitor is used though.
  Serial.begin(9600);

  charName = nameString + (String)nameChar; // Remember to cast a variable that is NOT a String to String when you want to merge it with a string.
  intName = nameString + (String)nameInt; // Same as the comment above
  floatName = nameString + (String)nameFloat; // Same as the comment above
  boolName = nameString + (String)nameBool; // Please read the comments above and ESEPCIALLY the comment above 'boolName'!
}

void loop()
{
  Serial.println("String + char: " + charName); // No need for (String) here since 'charName' we add on is already a string.
  Serial.println("String + int: " + intName); // Same as the comment above.
  Serial.println("String + float: " + floatName); // Same as the comment above.
  Serial.println("String + bool: " + boolName); // Same as the comment above.
  delay(10000); // Wait 10 seconds before printing again (This prevents the Serial Monitor from being spammed);
}