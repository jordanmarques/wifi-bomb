# Wifi-Bomb



The goal of Wifi-Bomb project is to slow down the speed of a router. For this, it performs a DDOS attack by sending a lot of network packets.



Requirement
-------------
 * Wemos D1 Mini V2 (ESP8266)
 * 2*battery AAA LR03
 * ON/OFF Switch 

![enter image description here](http://img4.hostingpics.net/pics/287422final.png)



Problems encountered 
-------------

At the beginning, we wanted the Wifi-Bomb project to disrupt the connection of a connected device to the router. But the application requires to know the MAC address of the connected device. We could'nt change the mac address with the ESP8266 library. Then, we looked the code of the library "Wifi Manager" to see an example of inclusion of libraries.

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


We looked for other type of wifi attack. We found a way to slow down the speed of a wifi connection.

So we developed a code to connect to a router. 
This code contained an interface to connect to a wifi access point via an form.
We encountered a problem with the arduino that connected to the same router than the one which we wanted to "jam".
So we chose to use Wifi Manager library because it was simpler and more convenient to use.
After a few bugs, we finally managed to validate the connection to a wifi network and to inject a large number of packets in order to slow down the speed wifi of this network.

In parallel, we have welded the arduino to an external battery in order to be able to use it from anywhere.
