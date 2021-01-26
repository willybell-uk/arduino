//#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#define OnboardLED 13
IPAddress ip(192, 168, 1, 60);
byte mac[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x00};
EthernetServer server(80);

void setup() {
  // put your setup code here, to run once:
  pinMode(OnboardLED, OUTPUT);
  Ethernet.init(10);  // Most Arduino shields
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer 2");
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }
  // start the server
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(OnboardLED, HIGH);
  delay(1000);
  digitalWrite(OnboardLED, LOW);
  delay(1000);
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          Serial.print("MAC address is ");
          for (byte i = 0; i < 6; i++){
            Serial.print(mac[i], HEX);
            if (i < 5) {
              Serial.print(":");
              }
            }
          Serial.println();
          Serial.print("IP address is ");
          Serial.println(ip);
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
      // give the web browser time to receive the data
      delay(1);
      // close the connection:
      client.stop();
      Serial.println("client disconnected");
    }
  }
  
}
