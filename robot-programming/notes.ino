/*
   notes.ino

    Created on: Sep 9, 2022,
    Author: Nikolaj Krebs
*/ 

// This is called a definition and it can only be the value it is assigned here.
// This means you cannot change it in your code, only use it.
#define calculateDelay 500
#define loopEndDelay 2500

// 'int' is the variable's datatype
// 'intValue1' is the variable
// and = -2; is the variable's value.
int intValue1 = -2;
int intValue2 = 10;

// Floats are used to store decimal numeric values (to a certain extend)
float floatValue1 = 1.2346;
float floatValue2 = -3.21426;

// Strings are an assembly of the datatype char to make out a word, sentence or more.
String stringValue1 = "hello";
String stringValue2 = "there";

// Double is a float but with allowance for more decimals
double doubleValue1 = 1.234624124;
double doubleValue2 = -3.21426;

// This only ever runs in your arduino once, on startup.
void setup() {
  Serial.begin(9600);
}

void loop() {
  String hellothere = stringValue1 + " " + stringValue2; // Output: hellothere = "hello there";

  Serial.println("Addition of value 1 and value 2 (int): " + (String)intValue1 + " + " + (String)intValue2 + " = " + (String)(intValue1 + intValue2));
  // Addition of value 1 and value 2 (int): -2 + 10 = 8
  // (String) WITH the parentheses is called casting to a datatype
  // (String) = casting to string
  // (Float) = casting to float
  // Etc.

  delay(calculateDelay); // 1000ms = 1 sec

  Serial.println("Subtraction of value 1 and value 2 (int): " + (String)intValue1 + " - " + (String)intValue2 + " = " + (String)(intValue1 - intValue2));
  // +, -, *, /, etc. is called "operators"
  delay(calculateDelay);

  Serial.println("Multiplication of value 1 and value 2 (int): " + (String)intValue1 + " * " + (String)intValue2 + " = " + (String)(intValue1 * intValue2));
  delay(calculateDelay);

  Serial.println("Division of value 1 and value 2 (float): " + (String)floatValue1 + " / " + (String)floatValue2 + " = " + (String)(floatValue1 / floatValue2));
  delay(calculateDelay);

  Serial.println("Division of value 1 and value 2 (double): " + (String)doubleValue1 + " / " + (String)doubleValue2 + " = " + (String)(doubleValue1 / doubleValue2));
  delay(calculateDelay);
  
  Serial.println("Multiplication of value 1 and value 2 (float): " + (String)floatValue1 + " * " + (String)floatValue2 + " = " + (String)(floatValue1 * floatValue2));
  

  delay(loopEndDelay);
}
