


#include <dht_nonblocking.h>
#include <LiquidCrystal.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11


static const int DHT_SENSOR_PIN = 9;
static const int ledPin = 13;
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

void setup( )
{
    pinMode(12, INPUT);   //this pin accidentally connects to LCD VSS (gnd)
  pinMode(8, INPUT);
  pinMode(ledPin, OUTPUT);
Serial.begin( 9600);
lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  delay(1000); //leave hello world for 1 second
}
void loop( )
{
  float temperature;
  float humidity;
lcd.setCursor(0, 1);
  //digitalWrite(ledPin, HIGH);
  //delay(500);
  //digitalWrite(ledPin, LOW);
  //delay(500);
  if(dht_sensor.measure(&temperature, &humidity)){
    Serial.print( "T = " );
    Serial.print( temperature, 1 );
    Serial.print( " deg. C, H = " );
    Serial.print( humidity, 1 );
    Serial.println( "%" );
    lcd.print( (int)temperature, DEC);
    lcd.print(" ");
    lcd.print( (int)humidity, DEC);
  }
}
