//
// OLED I2C - Bargraph (128x64)
// Datei: arduino-sensoren-2-kap9-oled-bargraph.ino


/*********************************************************************
This is based on an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED Display Breite in Pixel
#define SCREEN_HEIGHT 64 // OLED Display Höhe in Pixel

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Messspannung
int voltage=0;

void setup()   
{
  // Initialisierung OLED an I2C Adresse 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);

  // Buffer löschen
  display.clearDisplay();

  // Ausgabe Startbildschirm
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("OLED...");
  display.display();
  delay(2000);
  display.clearDisplay();
}


void loop() 
{
  // Spannung an A0 messen oder Messsignal von externem Sensor
  voltage=analogRead(0);
  voltage=856;
  
  // Ausgabe Text
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(voltage);
  display.display();

  // Bargraph
  // Rechteck zeichnen
  display.drawRect(0,32,1023/10, 4, WHITE);
  // Balken füllen gemäss Messsignal
  display.fillRect(0,32, voltage/10, 4, WHITE);
  // Display aktualisieren
  display.display();
  delay(1000);
  // Display löschen
  display.clearDisplay();
}
