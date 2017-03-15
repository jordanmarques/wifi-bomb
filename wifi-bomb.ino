#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <user_interface.h>

ESP8266WebServer server(80);

extern "C" void __run_user_rf_pre_init(void) {
  
  WiFi.mode(WIFI_AP_STA);
  uint8_t mac[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
  wifi_set_macaddr(SOFTAP_IF, &mac[0]);
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
  server.arg(1).toCharArray(ssid, 50);

  bomb(ssid, password, "");
}

void bomb(char ssid[], char password[], String amac){
    
  Serial.println(WiFi.macAddress());

  while(true){
    WiFi.begin(ssid, password);
    Serial.println("Wifi: Connected");
    blink();
    
    delay(5000);
    
    WiFi.disconnect();
    Serial.println("Wifi: Disconnected");
    blink();

    delay(2000);
  }
  
}

void blink(){
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
}

void setup() {
  Serial.begin(115200);
	configureAccesPoint();
  configureLED();

  __run_user_rf_pre_init();
  Serial.println(WiFi.macAddress());
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
  Serial.print("Configuring access point...");
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
  Serial.println("Configuring LED");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

