/*
   exercise1.ino

    Created on: Nov 11, 2022,
    Author: Nikolaj Krebs,
    Lecture 5, Exercise 1 - Simple functions, Friday Oct. 28 (moved to Friday Nov. 4)
*/ 

int values[] = { 1, 10, 100, 1000, 10000 };
String measures[] = { "nm", "mm", "cm", "m", "km" };

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // We know both our values & measures arrays have the size of 5.
  for (int i = 0; i < 5; i++) {
    // 'i' represents the position of which we read the arrays in at 
    // a given time.
    Serial.println("Reading arrays on position: " + (String)i);
    readValues(values, measures, i);
  }

  delay(1000);
}

// Our greeting function that greets the user through the serial monitor.
void greeting() {
  Serial.println("Hello World!");
}

// Our value print function, that prints a value of parameter type int, representing x units, in 
// measurement units represented by the parameter type of String.
void printValue(int value, String measure) {
  // Say that int value is: 3, and String measure is "mm".
  // The print will be: The given parameters are: 3 mm.
  Serial.println("The given parameters are: " + (String)value + measure);
}

// Used to read given arrays, in this exercise a int array followed by a String array.
// The 'pos' parameter of type int, is used to define the reading position in both arrays
// at the same time.
void readValues(int values[], String measures[], int pos) {

  // Grab the array entries from the given position.
  // NOTE: If the value of parameter 'pos' is any number higher than
  // the array sizes, things will break.
  int value = values[pos];
  String measure = measures[pos];

  // Say the line, Bart!
  printValue(value, measures);
}