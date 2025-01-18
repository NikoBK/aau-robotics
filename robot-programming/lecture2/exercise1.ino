/*
   exercise1.ino

    Created on: Oct 5, 2022,
    Author: Nikolaj Krebs,
    Lecture 2, Exercise 1 - Operation with variables, Friday Sep. 23
*/ 

int var1 = 10;
int var2 = 2;

// Note that the datatype 'int' is only declared once here because all these variables
// are all ints with no predefined values. We will change these variable values in the code
// during runtime.
int addition, subtraction, multiplication, division;

void setup() 
{
  // Initialize the serial port:
  Serial.begin(9600); // 9600 is the frequency for the serial monitor.

  addition = var1 + var2;
  subtraction = var1 - var2; // Remember to subtract biggest from smallest. var2 - var1 yields a negative value and var1 - var2 positive.
  multiplication = var1 * var2;
  division = var1 / var2; // Do not divide by 0. Same rules apply here as in math.
}

void loop() 
{
  // Prints all the calculated sums and products on the serial monitor
  Serial.println("Hello I am Zumo, these are my variables:"); // Our greetings string :)

  // Print the var1 and var2 values:
  Serial.println("var1:");
  Serial.println(var1);
  Serial.println("var2:");
  Serial.println(var2);

  // Print the addition, subtraction, multiplication & division values:
  Serial.println("addition:");
  Serial.println(addition);

  Serial.println("subtraction:");
  Serial.println(subtraction);

  Serial.println("multiplication:");
  Serial.println(multiplication);

  Serial.println("division:");
  Serial.println(division);

  // Print the closer text, that indicates where the loop stops.
  Serial.println("------- I will send the variables again each 10 seconds -------");
  delay(10000); // Wait 10 seconds before restarting the loop.
}