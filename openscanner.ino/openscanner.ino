/* Based on : 
 * 
 * WhiskeyTangoHotel.Com /  NOV2016
 * 'WarDriver' ESP8266 Adafruit HUZZAH w/ WiFi and 32 line OLED
 *   
 *   Scan WiFi networks leverages from:
 *   https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiScan/WiFiScan.ino
 *   
 *   OLED Driver: Thanks, adafruit.com
 *   
 *   Compile for 80MHz with Arduino IDE
 *      Arduino IDE 1.6.8 or greater
 *      http://www.arduino.cc/en/Main/Software
 *      
 *      ESP8266 Board Package
 *      Enter http://arduino.esp8266.com/stable/package_esp8266com_index.json into Additional Board Manage
 *      Restart, select your ESP8266 from the Tools->Board dropdown
 *      
 *      Modified by @elkentaro to write AP with no encryption to a file on the sd card. You need to have
 *      a file named logger.txt on the root of the sd card. This code will continue to append to that file
 *      it does not check for duplicates or previously noted SSIDs, it scans the 2.4Ghz band and just writes
 *      its findings to the file. 
 *      The SD card breakout board used is the Adafruit mini-SD breakout board. 
 *      https://www.adafruit.com/product/254
 *   
 *   The wiring is :
 *   SD card reader  |  nodeMCU
 *   ================|============
 *       3v          |   3v3
 *       GND         |   GND
 *       CLK         |   D5
 *       DO          |   D6
 *       DI          |   D7
 *       CS          |   D8
 *       
 *       
 */
#include "ESP8266WiFi.h"  // API for the ESP8266 WiFi
#include <SPI.h>
#include <SD.h>

// Setup chipSelect for NodeMCU
const int chipSelect = 15;

void setup() {
  
  Serial.begin(9600); // Display to serial monitor 
  Serial.println("Setup begins....");
    if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

}  // end void setup

void loop() {

  Serial.println("Scan starts...");
   // WiFi.scanNetworks will return the number of networks found as variable "n"
  digitalWrite(0, HIGH);  // On board LED ON
  int n = WiFi.scanNetworks();
  Serial.println(" and completes!!!");
  
  if (n == 0) {  // No WiFi found.  Update the Serial Monitor and the OLED
    Serial.println("No WiFi found!!!");

    // update OLED
 
    digitalWrite(0, LOW);  // On board LED OFF
  }      // endif n=0 (no wifi found)
  else  // wifi found
  {
    Serial.print(n);
    Serial.println(" Networks found:");
    Serial.println("----------------");
  
    for (int i = 0; i < n; ++i)
    {
      digitalWrite(0, HIGH);  // On board LED ON
      File openFile = SD.open("open.txt", FILE_WRITE);
      File allFile = SD.open("all.txt", FILE_WRITE);
      String encryptType ="";
      
      // Print SSID and RSSI for each network found to Serial Monitor. Show SSID, Signal strenght, and OPEN or Encrypted
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(": ");
      Serial.print(WiFi.RSSI(i));
      Serial.print("dBm | ");

      switch (WiFi.encryptionType(i)) {

        case 5:
        encryptType = "WEP";
        break;
        case 2:
        encryptType = "WPA/PSK/TKIP";
        break;
        case 4:
        encryptType = "WPA2/PSK/CCMP";
        break;
        case 7:
        encryptType = "Open";
        break;
        case 8:
        encryptType = "WPA/WPA2/PSK";
        break ;
        
      }
      Serial.print(encryptType);
      Serial.print (" |");
    
      Serial.println(WiFi.BSSIDstr(i));

      
// if and SSID without encryption is found write that SSID to the logger.txt on the root of the sd card.
      if (openFile) {
       if (WiFi.encryptionType(i) == ENC_TYPE_NONE)
       {
       openFile.print(WiFi.SSID(i));
       openFile.print(",");
       openFile.print(WiFi.BSSIDstr(i));
       openFile.print(",");
       openFile.print(WiFi.channel(i));
       openFile.print("ch");
       openFile.print(",");
       openFile.print("OPEN");
       openFile.println();
       openFile.close();
        }
      }
      
      if (allFile) {
       allFile.print(WiFi.SSID(i));
       allFile.print(",");
       allFile.print(WiFi.BSSIDstr(i));
       allFile.print(",");
       allFile.print(WiFi.channel(i));
       allFile.print("ch");
       allFile.print(",");
       allFile.print(encryptType);
       allFile.println();
       allFile.close();
       
      }
      
  
    }  // end for/next loop for n# of wifi networks found
  }   // endif wifi found (n was <> 0)
  Serial.println("");
}  // end void loop (endless)
