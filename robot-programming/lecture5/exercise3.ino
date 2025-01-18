/*
   exercise3.ino

    Created on: Nov 11, 2022,
    Author: Nikolaj Krebs,
    Lecture 5, Exercise 3 - Moving functions for Zumo, Friday Oct. 28 (moved to Friday Nov. 4)
*/ 
#include <Zumo32U4.h>

Zumo32U4Motors motors;

// Pause time inbetween each move in milliseconds.
int pauseMS = 3000;

// The speed we turn with.
int moveSpeed = 150, turnTime = 2000;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  stop();
  delay(pauseMS);
  moveForward(moveSpeed, turnTime * 2);
  delay(pauseMS);
  turn('r', moveSpeed, turnTime);
  delay(pauseMS);
  moveForward(moveSpeed, turnTime * 2);
  delay(pauseMS);
  turn('l', moveSpeed, turnTime);
  delay(pauseMS / 2);
  turn('l', moveSpeed, turnTime);
  delay(pauseMS);
  moveForward(moveSpeed, turnTime * 2);
  delay(pauseMS);
  turn('r', moveSpeed, turnTime);
  delay(pauseMS);
  moveBackward(moveSpeed, turnTime * 2);
  delay(pauseMS);
}

void stop() {
  motors.setSpeeds(0, 0);
}

void moveForward(int speed, int milliseconds) {
  motors.setSpeeds(speed, speed);
  delay(milliseconds);
  stop();
}

void moveBackward(int speed, int milliseconds) {
  motors.setSpeeds(-speed, -speed);
  delay(milliseconds);
  stop();
}

void turn(char direction, int speed, int milliseconds) {
  if (direction == 'l') {
    motors.setSpeeds(0, speed);
    delay(milliseconds);
    stop();
  } 
  else if (direction == 'r') {
    motors.setSpeeds(speed, 0);
    delay(milliseconds);
    stop();
  }
}