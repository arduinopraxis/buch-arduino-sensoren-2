// NTC
// Datei: arduino-sensoren-2_kap2-ntc.ino

    
#include <math.h>

// Widerstandswert bei 25 Grad C
int Wid25Grad= 10000;
// analoger Messwert
int valTemp;
// analoger Eingang
int TempPin = 0;
// Wert Temp in Celsius
float tempC;


void setup()
{
  // Start serielle Ausgabe
  Serial.begin(115200);
}


void loop() 
{
  valTemp = analogRead(TempPin);
  tempC = ThermistorC(valTemp);
  Serial.print("Temperatur: ");
  Serial.print(tempC);
  Serial.println(" C");
  // Warten 1 Sekunde
  delay(1000);
}

double ThermistorC(int RawADC)
{
 double Temp;
 Temp = log(((10240000/RawADC) - Wid25Grad));
 Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
 // Umrechnung Kelvin / Grad Celsius
 Temp = Temp - 273.15;
 return Temp;
}

