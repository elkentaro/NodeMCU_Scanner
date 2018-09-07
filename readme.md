### A NodeMCU based AP scanner.

This code is based off the ESP8266 scanner by @OurCatDoor of WhiskeyTangoHotel.Com.

It scans the 2.4Ghz and logs open SSIDs (ie: not encryption) to a file named "open.txt" on the root of the SD card, however it also writes everything it finds to a text file called "all.txt" on the root of the SD card. It does not check for previously detected or not , it just keeps writing to the SD card whatever it finds. Use "sort -u" or something to 
extract the individual unique findings later in post-capture processing. 

Yes, its very limited but it has a very distinct purpose. 
(see: https://twitter.com/mubix/status/1032657035597426688)

***Data logged:
SSID,MAC Adress,Channel,Encryption Type.

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
