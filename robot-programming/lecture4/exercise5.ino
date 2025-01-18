/*
   exercise5.ino

    Created on: Nov 11, 2022,
    Author: Nikolaj Krebs,
    Lecture 4, Exercise 5 - Zumo, the new rover, Friday Oct. 14
*/

/* README 
    This exercise can be a little complicated, so feel free to reach out and ask me 
    anything if you find some of this code confusing! :)
*/

#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;

// This array contains char representations of the following commands:
// f = Forward
// b = Backward
// l = Left
// r = Right
// s = Stop
char commands[] = {'f', 'b', 'l', 'r', 's' };

// This 2D int array represents a speed with a hardcoded time added to it.
// Both dimensions in the array is the same size, meaning every speed has a time.
// The structure of the array is as follows:
// velocity[1, 1] = Forward Speed: 100, Time: 2 seconds
// velocity[2, 2] = Backward Speed: 100, Time: 2 seconds
// velocity[3, 3] = Left Speed: 150, Time: 1 second
// velocity[4, 4] = Right Speed: 150, Time: 1 second
// velocity[5, 5] = Stop Speed: 0, Time: N/A
// NOTE: Time is defined in ms.
int velocity[4][4] = { /*Foward: */{150, 5000}, /* Backward: */ {150, 5000}, /* Left: */ {175, 1900}, /* Right: */ {175, 1900} };

// This is used inside our loop to count how many ms the robot has been waiting 
// for a confirmation (waiting for either button A or B to be pressed).
// If no button is pressed within 2 seconds it will auto-cancel!
int counter = 0;

// The time it takes the counter variable to increase by 1.
int timerMS = 500;

// Indicator for whether the rover is stopped or not.
bool stopped = true;

void setup()
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("Rover is ready!");
}

// The loop function will be used to detect button press.
void loop()
{
  // What we type into the serial.
  char input = Serial.read();

  // Used to indicate that the robot is waiting for a button press
  // confirmation for the move.
  bool awaitingConfirm = false;

  // Once we have read the input we check for serial availability.
  // Upon handling the input the user will receive a prompt that requests
  // a confirmation from the user. Pressing the A button on the Zumo will make it move.
  // pressing the B button will cancel the move.
  if (Serial.available() > 0) 
  {
    // Hackish code for checking legal input.
    // I kept having problems with the IDE crashing if any input
    // such as . or other characters was typed into the serial monitor
    // so I added this last minute hackish code.
    switch(input) {
      case 'f':
      case 'b':
      case 'l':
      case 'r':
      case 's':
        stopped = true;
      break;

      default:
        Serial.println("Illegal input detected: " + (String)input);
        return;
    }

    Serial.println("Registered input: " + (String)input + ". Press button A to confirm and move. Press button B to cancel");
    awaitingConfirm = true;
  }

  // We will stay inside this while loop while we are waiting for confirmation.
  while (awaitingConfirm) 
  {
    // If no button is pressed in 6 seconds (24 * 250ms) the
    // rover will auto cancel.
    if (counter >= 24) {
      Serial.println("No button was pressed. Action has been canceled!");
      counter = 0; // Reset the counter.
      awaitingConfirm = false;
    }

    // Here we make a while loop for the button being pressed
    // The '&& awaitingConfirm' is to make sure we only run the while
    // loop once if the button is pressed.
    while (buttonA.isPressed() && awaitingConfirm) {
      Serial.println("Action confirmed!");
      handleInput(input);
      awaitingConfirm = false;
    }

    // A while loop detecting if the B button is pressed.
    // The '&& awaitingConfirm' is to make sure we only run the while
    // loop once if the button is pressed.
    while (buttonB.isPressed() && awaitingConfirm) {
      Serial.println("Action canceled!");
      awaitingConfirm = false;
    }

    delay(timerMS);
    counter++;
  }

  // This does not really do much it just makes sure everything is not
  // executed too fast. Loop do be speedy!
  delay(250);
}

void handleInput(char input)
{
  switch(input)
  {
    // Forward
    case 'f':
      driveForward(velocity[0][0], velocity[0][1]);
    break;

    case 'b':
      driveBackwards(velocity[1][0], velocity[1][1]);
    break;

    case 'l':
      turnLeft(velocity[2][0], velocity[2][1]);
    break;

    case 'r':
      turnRight(velocity[3][0], velocity[3][1]);
    break;

    case 's':
      stop();
    break;

    default:
      Serial.println("Unhandled direction given: " + input);
    break;
  }
}

// Drives the rover forward.
void driveForward(int speed, int timeMS) {
  stopped = false; // Because we start moving.
  Serial.println("Driving forward for " + (String)timeMS + " milliseconds!");
  motors.setSpeeds(speed, speed);
  delay(timeMS);
  stop();
}

// Drives the rover backwards.
void driveBackwards(int speed, int timeMS) {
  stopped = false; // Because we start moving.
  Serial.println("Driving forward for " + (String)timeMS + " milliseconds!");
  // NOTE: We convert the speed to the speed parameter in negative to drive back.
  motors.setSpeeds(-speed, -speed);
  delay(timeMS);
  stop();
}

// Turns the rover left.
void turnLeft(int speed, int timeMS) {
  stopped = false; // Because we start moving.
  Serial.println("Driving forward for " + (String)timeMS + " milliseconds!");
  motors.setSpeeds(0, speed);
  delay(timeMS);
  stop();
}

// Turns the rover right.
void turnRight(int speed, int timeMS) {
  stopped = false; // Because we start moving.
  Serial.println("Driving forward for " + (String)timeMS + " milliseconds!");
  motors.setSpeeds(speed, 0);
  delay(timeMS);
  stop();
}

void stop() {
  Serial.println("Stopped!");
  motors.setSpeeds(0, 0);
  stopped = true;
  delay(1000);
}