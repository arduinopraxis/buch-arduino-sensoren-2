// Barometer BME280
// Datei: arduino-sensoren-2-kap7-bme280.ino


/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
  See the LICENSE file for details.
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

// Sensor Objekt
Adafruit_BME280 bme;


void setup() 
{
    Serial.begin(9600);
    while(!Serial);
    Serial.println("BME280...");

    unsigned status;
    
    // I2C Adresse 0x756
    status = bme.begin(0x76);  
    
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); 
        Serial.println(bme.sensorID(),16);
        Serial.print("ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("ID of 0x60 represents a BME 280.\n");
        Serial.print("ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }
    
    Serial.println("---------");
  
}


void loop() 
{
  // Temperatur
  Serial.print("Temperatur: ");
  Serial.print(bme.readTemperature());
  Serial.println(" Grad C");
  // Luftdruck
  Serial.print("Luftdruck: ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");
  // Höhe über Meer
  Serial.print("Höhe über Meer: ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
  // Luftfeuchtigkeit
  Serial.print("Luftfeuchtigkeit = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");
  // Warten
  delay(2000);
}

