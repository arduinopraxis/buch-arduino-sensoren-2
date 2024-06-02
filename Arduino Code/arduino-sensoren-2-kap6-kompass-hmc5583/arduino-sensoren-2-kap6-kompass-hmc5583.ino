// Kompass mit Kompass-Sensor HMC5883
// Datei: arduino-sensoren-2-kap6-kompass-hmc5583.ino

#include <Wire.h>
#include <HMC5883L.h>

float winkel;
int w;

// Kompass Objekt
HMC5883L compass;
// Fehler
int error = 0;

  
void setup()
{
   // Serielle Schnittstellen
  Serial.begin(9600);
  Wire.begin();
  Serial.print("Start Kompass mit HMC5883");

  // Skalierung setzen
  error = compass.setScale(1.3);
  // falls Fehler
  if(error != 0){
    Serial.println(compass.getErrorText(error));    
  }
  // Continuous Mode setzen
  error = compass.setMeasurementMode(MEASUREMENT_CONTINUOUS);
  if(error != 0){
     Serial.println(compass.getErrorText(error));
  }
}


void loop() 
{ 
  // Rohdaten einlesen
  MagnetometerRaw raw = compass.readRawAxis();
  // Skalierte Daten
  MagnetometerScaled scaled = compass.readScaledAxis();
  // Kalkulation
  float heading = atan2(scaled.YAxis, scaled.XAxis);
  
  // Ermittlung Magnetic Declination unter http://www.magnetic-declination.com/
  // Mein Wert: +2° 29' -> 2.48333° -> Rad 0.043342
  float declinationAngle = 0.043342;
  heading += declinationAngle;
  
  // Korrektur wenn invertiert
  if(heading < 0)
    heading += 2*PI;
  // Limitierung Winkel
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Umrechnung Radiant zu Grad
  winkel = heading * 180/M_PI;
  
  // Winkel als Integer
  w = winkel;
    
  // Ausgabe Winkelgrad
  Serial.print("Winkel: ");
  Serial.println(w);

  delay(100);
   
}
