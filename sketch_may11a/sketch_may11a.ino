/*
 * Test blink LED on pin 13
 * 
 */

const int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
pinMode(ledPin, OUTPUT);
Serial.begin(9600); // Starts the serial communication
Serial.println("Beginning program....");
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(ledPin, HIGH);
delay(1000);
digitalWrite(ledPin, LOW);
delay(100);
}
