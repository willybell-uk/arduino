#define ESP32_RTOS  // Uncomment this line if you want to use the code with freertos only on the ESP32
                    // Has to be done before including "OTA.h"
#define ONBOARD_LED 2
#include "OTA.h"
#include <credentials.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  setupOTA("TemplateSketch", ssid, password);

  // Your setup code
  pinMode(ONBOARD_LED,OUTPUT);
}

void loop() {
#ifdef defined(ESP32_RTOS) && defined(ESP32)
#else // If you do not use FreeRTOS, you have to regulary call the handle method.
  ArduinoOTA.handle();
#endif

  // Your code here
  delay(200);
  digitalWrite(ONBOARD_LED,HIGH);
  delay(200);
  digitalWrite(ONBOARD_LED,LOW);
}
