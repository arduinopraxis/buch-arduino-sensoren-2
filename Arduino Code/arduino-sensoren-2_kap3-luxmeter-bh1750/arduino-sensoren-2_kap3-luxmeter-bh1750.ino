// Luxmeter mit BH1750
// Datei: arduino-sensoren-2_kap3-luxmeter-bh1750.ino

#include <BH1750.h>
#include <Wire.h>

// Luxmeter Objekt mit Busadresse 0x23
BH1750 luxmeter(0x23);

void setup() 
{
  // Serielle Schnittstelle
  Serial.begin(9600);
  // I2C Bus starten
  Wire.begin();
  // Luxmeter starten
  luxmeter.begin();

  Serial.println("Luxmeter...");
}

void loop() 
{
  // Sensor abfragen
  float lux = luxmeter.readLightLevel();
  // Ausgabe
  Serial.print("Licht: ");
  Serial.print(lux);
  Serial.println(" lx");
  // warten
  delay(1000);
}
