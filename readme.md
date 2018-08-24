A NodeMCU based open AP scanner.

This code is based off the ESP8266 scanner by @OurCatDoor of WhiskeyTangoHotel.Com.

It scans the 2.4Ghz band and if it finds a SSID without any encryption logs that SSID to a text file on the sd card. Its meant as a pure SSID collector , it does not check for previous entry or writes any additional information other than the SSID name to the text file.

Yes, its very limited but it has a very destinct purpose. 
(see: https://twitter.com/mubix/status/1032657035597426688)

1. Setup 

- Wire up sd card reader with the nodemcu.
- Create empty text file named logger.txt on the root of the sd card.
- Flash nodemcu with code.

Wiring: 

The SD card breakout board used is the Adafruit mini-SD breakout board. 
 *      https://www.adafruit.com/product/254

   The wiring is :
   
    SD card reader  |  nodeMCU
   	   
   	    3v          |   3v3
        GND         |   GND
        CLK         |   D5
        DO          |   D6
        DI          |   D7
        CS          |   D8

  
3D files on thingiverse : https://www.thingiverse.com/thing:3065468
