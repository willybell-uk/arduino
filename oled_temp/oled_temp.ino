#include <Wire.h>
#include <dht_nonblocking.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
static const int DHT_SENSOR_PIN = 4;
static const int ledPin = 13;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

void setup( )
{
  pinMode(ledPin, OUTPUT);
  Serial.begin( 9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(WHITE);
  display.setTextSize(4); 
  display.println("ARTI");
  display.setTextSize(2);
  display.println("is alive!");
  display.display();
  delay(2000); // Pause for 2 seconds
}

void DisplayLargeTemp(float temp)
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(WHITE);
  display.setTextSize(6); 
  display.print(int(temp));
  display.setCursor(80,20);
  display.setTextSize(3); 
  display.println(" C");
  display.display();
}

void SendDataToTerminal(float temp, float hum)
{
  Serial.print( "T = " );
  Serial.print( temp, 1 );
  Serial.print( " deg. C, H = " );
  Serial.print( hum, 1 );
  Serial.println( "%" );
}

void loop( )
{
  float temperature;
  float humidity;

  if(dht_sensor.measure(&temperature, &humidity)){
    SendDataToTerminal(temperature, humidity);
    DisplayLargeTemp(temperature);
  }
}
