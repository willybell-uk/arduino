/*
 
 Use ultrasonic transducer and pan/tilt head to scan room
 Mark Bell 24 January 2020
 
*/

#include <Servo.h>

// pin allocations
const byte hServopin = 4; // pin 4 is horizontal servo
const byte vServopin = 5; // pin 5 is vertical servo
const byte trigPin = 3; // ultrasonic sensor
const byte echoPin = 2; // ultrasonic sensor

// global variables
const byte hAngles [] = {30, 45, 60, 75, 90, 105, 120, 135, 150}; // angles to be ranged (was 30, 60, 90, 120, 150)
const byte vAngles [] = {30, 45, 60, 75, 90, 105, 120, 135, 150};
const byte hNoAngles = 9;
const byte vNoAngles = 9;
int ranges [hNoAngles] [vNoAngles];

Servo hServo;  // create servo objects
Servo vServo;  

void park(int x, int y) {
  hServo.write(x);
  vServo.write(y);
}

bool scanAll (byte command) {
  // command 0 scan and send ranges to serial port
  // command 1 scan and store in ranges array
  // command 2 scan and compare with ranges array, return an error if different
  // command 3 ??
  byte i, j;
  int k, m;
  bool error = false;
  const byte ultraErrorTol = 1;
  for (i = 0; i < vNoAngles; i++){
    vServo.write(vAngles[i]); // move vertical servo
    if (command == 0) {
        Serial.print("Row ");
        Serial.print(i);
        Serial.print(" ");
      }
    for (j = 0; j < hNoAngles; j++){
      hServo.write(hAngles[j]); // move horizontal servo
      delay(50);
      k = getRange();
      if (command == 0) {
        Serial.print(k);
        Serial.print(" ");
      }
      if (command == 1) {
        ranges[hAngles[j]][vAngles[i]] = k;
      }
      if (command == 2) {
        m = ranges[hAngles[j]][vAngles[i]];
        if ((k > (m + ultraErrorTol)) || (m > (k + ultraErrorTol))) {  // check if range has changed by more than ultraErrorTol cm
          error = true;
        }
      }
    }
    if (command == 0) {
        Serial.println(" cm");
      }
  }
  return (error);
}

void sendArray () {  // send ranges array to serial port
  int m;
  byte i, j;
  for (i = 0; i < vNoAngles; i++){
    Serial.print("Line ");
    Serial.print(i);
    Serial.print(" ");
    for (j = 0; j < hNoAngles; j++){
      m = ranges[hAngles[j]][vAngles[i]];
      Serial.print(m);
      Serial.print(" ");
    }
    Serial.println();
  }
}

int getRange() {
  // servos should be positioned so get the range and return (doubled periods)
  long duration;
  int distance;
  const unsigned long ultraTimeOut = 40000;
  digitalWrite(trigPin, LOW); // Clears the trigPin
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH); // Sets the trigPin on HIGH state
  delayMicroseconds(20);       // for 10 uS
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, ultraTimeOut); // Reads the echoPin, returns the sound wave travel time in microseconds
  // use timeout 30000 uS
  distance = duration*0.0171; // Calculating the distance in cm
  delay(50);
  return(distance); // note delay 250 mS afterwards
}

void setupSerial() {
  Serial.begin(9600); // Open serial communications and wait for port to open:
  while (!Serial) {
     // wait for serial port to connect. Needed for native USB port only
     // need a timeout here?
  }
}

void setupServos() {
  hServo.attach(hServopin);  // attach the servos to the servo objects
  vServo.attach(vServopin);
}

void setupUltra() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

int rangeCont() {
  int k;
  park(90, 90);
  k = getRange();
  Serial.print(k);
  Serial.println(" cm");
  return(k);
}

void setup() {
  setupSerial();
  setupServos();
  setupUltra();
  scanAll(byte(0)); 
  park(90, 90);
}



void loop() {
  int junk;
  rangeCont();
  //
}



// LS9 7TF st james
