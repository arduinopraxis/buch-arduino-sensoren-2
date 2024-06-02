// Wägezelle mit HX711 Messverstärker
// Datei: arduino-sensoren-2-kap5-waegezelle.ino

#include "HX711.h"

// HX711 Anschlusspins
const int waagePin_DOUT = 2;
const int wagePin_SCK = 3;

HX711 waage;

void setup() 
{
  Serial.begin(57600);
  waage.begin(waagePin_DOUT, wagePin_SCK);
}

void loop() {

  if (waage.is_ready()) {
    // Kalibierung
    long waagewert = ((waage.read()*(-0.01))+1525)/4.3;
    // Ohne Kalibrierung
    //long waagewert = waage.read();
    Serial.print("Waage: ");
    Serial.println(waagewert);
 
  } else {
    Serial.println("HX711 nicht gefunden");
  }

  delay(1000);
}
