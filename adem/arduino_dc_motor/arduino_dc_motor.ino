//JDN & JDB NOV 2023
// rettet 2 DEC 2024
// adv udgave mht qudraturencoder

/*******
*  MOTOR
*  https://www.pololu.com/product/4691
* 1:19 gearing (som reelt er 1:18.75)
* 24 V udgave
* 2 kvad encoder hver med 16 pulser pr 360 gr 
* Her benyttes både positive og negative flanker på begge to
* Det giver ialt 64 pulser pr 360 gr
*
* HBRO tb67h420ftg
https://core-electronics.com.au/dual-single-motor-driver-carrier-tb67h420ftg.html
*
* PINNUMRE ER TIL EN ARDUINO UNO
*
* H-bro https://www.pololu.com/product/2999  TB67H420FTG Dual/Single Motor Driver Carrier
* 
* ------------------------
* motor <-> arduino
* Encoder signaler
* encoder A(yellow) => intr pin 2  (INT0)
* encoder B(white)  => intr pin 3  (INT1)
*
* Power til encoder fra Ardino
* 5V:   5V Arduino => blå 
* GND:  GND Arduino => grøn
*
*
* HBRO <-> Arduino  vi bruger kanal A på HBRO
* Arduino PWM ud(6) => HBRO()PWMA)
* omdretning Ar duino A(8), B(9) => INA1, INA2
*
* HBRO <=> motor  
* HBRO A+- => rød ledning på motor Der er er loddet rød ledn på hbro
* HBTO A-  => sort ledning   ............. sort ...........
*
* HBRO 24V power fra strømforsyning
* Strømforsyning (24V 1A min) => VIN pin på hbro  => GND pin på hbro
*
* HUSK AT FORBINDE GND på 24V forsyning med GND på Arduino
*/

// Tælletal  på 1 rotation af oder
#define TICK_PR_ROUND 64

// ISR pin nr fra encoder
#define ENCA 2
#define ENCB 3

#define A1 8
#define A2 9
#define APWM 6

#define ENGVOLT 24.0
#define GEAR_RATIO 18.75




/***** 
* Vores realtidsloop - som kører hver SAMPL_TIME
* 
* SAMPLE_TIME periodetid i [msec]
****/
#define SAMPLE_TIME 100
volatile unsigned long tS;  // tæller til at styre samplingstidspunkt - se i loop fkt


/******** 
* Variables for the qudratur encoder
********/

// variables changed by ISRT so not synchronized with sampling time
volatile int count;            // actual count maintained by ISR
volatile boolean dir = false;  // true i count goes up


// Variables updated for every sample period by  main loop
volatile int count0 = 0, count1 = 0, count2 = 0, count3 = 0;
volatile float vel0 = 0, vel1 = 0, vel2 = 0;

// motor Voltage  up to +- ENGVOLT
volatile float engVolt = 0.0;



void encAIntr() {
  static boolean aDir;
  static boolean bDir;

  aDir = digitalRead(ENCA);
  bDir = digitalRead(ENCB);

  if (aDir == HIGH) {  // rising
    if (bDir == HIGH) {
      count--;
      dir = false;
    } else {
      count++;
      dir = true;
    }
  } else {
    if (bDir == HIGH) {
      count++;
      dir = true;
    } else {
      count--;
      dir = false;
    }
  }
}

void encBIntr() {
  static boolean aDir;
  static boolean bDir;

  aDir = digitalRead(ENCA);
  bDir = digitalRead(ENCB);

  if (bDir == HIGH) {  // rising
    if (aDir == HIGH) {
      count++;
      dir = true;
    } else {
      count--;
      dir = false;
    }
  } else {
    if (aDir == HIGH) {
      count--;
      dir = false;
    } else {
      count++;
      dir = true;
    }
  }
}

//--------------

void setupHBRO() {
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
}

void setDir(boolean b) {
  digitalWrite(A1, b);
  digitalWrite(A2, !b);
}

// input up to +- ENGVOLT (24V )as it is a 24 V motor
void setEngSpd(float v)  // 0 -> +- 24 [V]
{
  int dir;

  v = 255.0 * v / ENGVOLT;  // [ 0-..25] for 20 bit dac/PWM

  // change signed control value to positive pålus a sign(direction) indicator
  if (v < 0) {
    v = -v;
    dir = 0;
  } else {
    dir = 1;
  }

  int vv;
  if (255.0 < v)
    v = 255;
  vv = v;

  setDir(dir);
  analogWrite(APWM, vv);
}

void updateCounts() {
  count3 = count2;
  count2 = count1;
  count1 = count0;
  noInterrupts();
  count0 = count;
  interrupts();
}

float getVel() {
  return ((1000.0 / SAMPLE_TIME) * (2.0 * PI / TICK_PR_ROUND) * (count0 - count1));  // [rad/sec]
}

float getVelWGear() {
  return (getVel() / GEAR_RATIO);
}

void resetHBRIDGE() {
  //https://www.pololu.com/product/2999
  // we toogle to and from standby mode
  analogWrite(APWM, 0);
  digitalWrite(A1, 0);
  digitalWrite(A2, 0);
  delay(100);  // to short ??
}

/* FOR TESTING */
#define LONG_SAMPLE_TIME 400  // test for having  some dynamic in test

volatile unsigned long tSlong;  // see in loop for testing


// A LONG DEMO
float demoControl() {
  static int cnt = 0;
  static float vvv = 0;

  // hvis vi går fra max hastghed i en retning til i den anden retning trækker vi
  // for meget strøm og H-BRO lukker ned.
  // Der er et resetHRIDGE kald lige ovenfor

  // Hvis LO1 pin npå HBRo er kanal A(den vi bruger) gået i safemode
  // og du skal resette HRBO:

  // derfor denne switch for at lve lidt stilstand når vi går far max i en retni gtil i en adne retning
  // IKKE ANBEFALELSESVÆRDIIGT at skiftte retning hårdt og brutalt !
  if (tSlong <= millis()) {      // runs every LONG_SAMPLE_TIME
    tSlong += LONG_SAMPLE_TIME;  // pre for next time

    switch (cnt) {
      case 0:
        vvv = 0;
        break;
      case 1:
        vvv = ENGVOLT;
        break;
      case 2:
        vvv = 0;
        break;
      case 3:
        vvv = -ENGVOLT;
        break;
      default:;
    }

    cnt++;
    if (3 < cnt)
      cnt = 0;
  }
  return vvv;
}

void dumpInputOutput() {
  float vel = getVel();
  Serial.print(millis());
  Serial.print(" Encoder[rad/sec]: ");
  Serial.println(vel);
}

void setVel(float omega){
  int dir;
  int vv;

  float v = map(omega,0,1040,0,255);
  // 0 - 1040 -> 0 - 255

  if(v<0){
    v = -v;
    dir = 0;
  } else {
    dir = 1;
  }

  if (255.0 < v){
    v = 255;
  }

  vv = int(v);
  setDir(dir);
  analogWrite(APWM, vv);
}

void regulate_speed(int target_speed){
  float error;
  float proportional_reg;
  if (tS <= millis()) {
    tS += SAMPLE_TIME;
    updateCounts();
    
    // get act velocity
    vel0 = getVel();

    error = target_speed - vel0;
    proportional_reg = vel0 + (1.5 * error);
    setVel(proportional_reg);
  }
}

//---------oOo  loop and setup ----------------

void setup() {
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  tS = millis() + SAMPLE_TIME;
  tSlong = millis() + LONG_SAMPLE_TIME;

  attachInterrupt(digitalPinToInterrupt(ENCA), encAIntr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCB), encBIntr, CHANGE);
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void loop() {
  //engVolt = demoControl();
  regulate_speed(300);
  float vel = getVel();
  Serial.println(vel);
}


/*
* 4 * 16 = 64 pr rotation
 * INTR ON A
 * A intr rising  & B høj left
 * A intr rising  & B lav right
 * A intr falling & B høj right
 * A intr falling & B lav left
 * 
 * INTR ON B
 * B intr rising  & A høj right
 * B intr rising  & A lav left
 * B intr falling & A høj left
 * B intr falling & A lav right
 * 
 */