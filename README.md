# Wifi-Bomb



The Wifi-Bomb project disrupts the connection of connected device to a router. The application requires to know the MAC address of the connected device.



Requirement
-------------
 * Wemos D1 Mini V2 (ESP8266)
 * 2*battery AAA LR03
 * ON/OFF Switch 

-![enter image description here](http://img4.hostingpics.net/pics/287422final.png)



Problems encountered 
-------------

At the beginning, we wanted that the Wifi-Bomb project disrupts the connection of connected device to a router. But the application requires to know the MAC address of the connected device. We could'nt change the mac address with the ESP8266 library. Then we looked at the code of the library "Wifi Manager" to see an example of inclusion of libraries.
