/*
   exercise4.ino

    Created on: Nov 16, 2022,
    Author: Nikolaj Krebs,
    Lecture 5, Exercise 4 - Moving functions for Zumo, Friday Oct. 28 (moved to Friday Nov. 4)
*/

// These are called headers by the way!
#include <Arduino.h>
#include<Wire.h>
#include<Zumo32U4.h>

// Our motors.
Zumo32U4Motors motors;

// Intertia Management Unit, we acces the gyro through this.
Zumo32U4IMU imu;

// Our Liquid Crystal Display.
Zumo32U4LCD lcd;

// Motors variables
int motorSpeed = 150;

// Gyroscope variables
int16_t gyroOffset = 0;
uint16_t lastGyroUpdate = 0;
int16_t turnRate = 0;
uint32_t turnAngle = 0;
int turnAngleDegrees = 0;

void setup() {
  Serial.begin(9600);
  stop(); // Make it default that the robot does not move from the beginning.
  setupImu();

  // LCD setup.
  lcd.init();
  lcd.clear();
}

void loop() {
  turn(100, 90, 'r');
  delay(3000);
  turn(100, 90, 'l');
  delay(3000);
}

void setupImu() {
  Wire.begin();
  imu.init();
  imu.enableDefault();
  imu.configureForTurnSensing();

  int32_t totalReadings = 0;
  int sampleIterations = 1024;
  for (uint16_t i = 0; i < sampleIterations; i++) 
  {
    // Exit the loop if there is no ready gyroscope data.
    if (!imu.gyroDataReady()) {
      return;
    }

    // Cache gyro data.
    imu.readGyro();
    totalReadings += imu.g.z;
  }
  gyroOffset = totalReadings / sampleIterations;
  imuReset();
  delay(250);

  lcd.clear();
}

void imuReset() {
  lastGyroUpdate = micros();
  turnAngle = 0;
}

void updateGyro() {
  if (!imu.gyroDataReady()) {
    return;
  }

  // Read measurements from the gyro.
  imu.readGyro();
  turnRate = imu.g.z - gyroOffset;

  // Figure out how much time has passed since the last update (deltaTime).
  uint16_t micros_ = micros();
  uint16_t deltaTime = micros_ - lastGyroUpdate;
  lastGyroUpdate = micros_

  // Multiply deltaTime by turnRate in order to get an estimation of how
  // much the robot has turned since the last update.
  // (angular change = angular velocity * time).
  int32_t d = (int32_t)turnRate * deltaTime;

   // The units of d are gyro digits times microseconds.  We need
  // to convert those to the units of turnAngle, where 2^29 units
  // represents 45 degrees.  The conversion from gyro digits to
  // degrees per second (dps) is determined by the sensitivity of
  // the gyro: 0.07 degrees per second per digit.
  //
  // (0.07 dps/digit) * (1/1000000 s/us) * (2^29/45 unit/degree)
  // = 14680064/17578125 unit/(digit*us)  
  turnAngle += (int64_t)d * 14680064 / 17578125;

  // Converts angle interval from [-180;180] to [0;360]
  turnAngleDegrees = ((((int32_t)turnAngle >> 16) * 360) >> 16);
  if (turnAngleDegrees <= 0 && turnAngleDegrees >= -180) {
      directionalAngle = (360 + turnAngleDegrees);
  }
  if (turnAngleDegrees >= 0 && turnAngleDegrees <= 180) {
      directionalAngle = turnAngleDegrees;
  }
}

///////// Operation functions

void stop() 
{
  motors.setSpeeds(0, 0);
}

void moveFoward(int speed, int centimeters)
{
  // TBD
}

void moveBackward(int speed, int centimeters)
{
  // TBD
}

void turn(int speed, int degrees, char direction)
{
  // Indicator for whether the robot has turned
  // to the correct angle in degrees or not.
  bool turnOver = false;

  switch(direction)
  {
    case 'l':
    case 'L':
      while (!turnOver) {
        updateGyro();
        writeOnLCD((String)turnAngleDegrees);
        motors.setSpeeds(-motorSpeed * 1.2, motorSpeed);

        if (directionalAngle >= degrees && (degrees) >= directionalAngle) {
          turnOver = true;
        }
      }
      stop();
    break;

    case 'r':
    case 'R':
      while (!turnOver) {
        updateGyro();
        writeOnLCD((String)turnAngleDegrees);
        motors.setSpeeds(motorSpeed, -motorSpeed * 1.2);

        if (directionalAngle >= degrees && (degrees) >= directionalAngle) {
          turnOver = true;
        }
      }
    break;
  }
}

void writeOnLCD(String text) {
  lcd.clear();
  lcd.println(text);
}