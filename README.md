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

Then, We used a "node MCU" in order to "jam" via a lua code because this system allows to change the MAC address. On the other hand, we could not make an access point via this solution. Moreover, the associated idea is not adapted to our needs, so we have abandoned this solution.

We looked for other type of wifi attack. We found a way to slow down the speed of a wifi connection.

So we developed a code to connect to a router. 
This code contained an interface to connect to a wifi access point via an html form.
We encountered a problem with the arduino that connected to the same router than the one which we wanted to "jam".
So we chose to use the Wifi Manager library because it was simpler and more convenient to use.
After a few bugs, we finally managed to validate the connection to a wifi network and thus inject a large number of packets in order to slow down the speed wifi of this network.

In parallel, we have welded the arduino to an external battery in order to be able to use it from anywhere.
