//Please use "homebridge-http-switch" npm module


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/*Put your SSID & Password*/
const char* ssid = "your ssid";  // Enter SSID here
const char* password = "your pd";  //Enter Password here

ESP8266WebServer server(80);

uint8_t LEDpin = LED_BUILTIN;
volatile bool LEDstatus = HIGH; //The buildin led is active low

void setup() {
  Serial.begin(9600);
  delay(100);
  pinMode(LEDpin, OUTPUT);
  digitalWrite(LEDpin, HIGH);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

//  server.on("/", handle_OnConnect);
  server.on("/ledon", handle_ledon);
  server.on("/ledoff", handle_ledoff);
  server.on("/state", handle_state);

  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
}

//void handle_OnConnect() {
////  LEDstatus = LOW;
//  server.send(200, "text/html", "");
//}
void handle_ledon() {
  LEDstatus = LOW;
  digitalWrite(LEDpin, LEDstatus);
  server.send(200, "text/plain", "");
  Serial.println("LED on ");
}

void handle_ledoff() {
  LEDstatus = HIGH;
  digitalWrite(LEDpin, LEDstatus);
  server.send(200, "text/plain", "");
  Serial.println("LED off ");
}

void handle_state(){
  server.send(200, "text/plain", String(LEDstatus == LOW? 1 : 0));
  Serial.print("state=");
  Serial.println(LEDstatus);
}
