// Temperaturmessung mit Temperatursensor LM35
// Datei: arduino-sensoren-2_kap2-lm35.ino

float valTemp;
// Analogeingang A0
int tempPin = 0;   
float tempC;
float tempCmV;


void setup()
{
  // Serielle Schnittstelle initialisieren
  Serial.begin(9600);
}

void loop()
{
  // Analogport einlesen
  valTemp = analogRead(tempPin);
  // Wert umkonvertieren, 
  tempCmV = (5000* valTemp)/1023.0;
  tempC = tempCmV/10;
  delay(500);
  
  // Wert an serielle Schnittstelle senden
  // Ausgabe als Grad Celsius
  Serial.print("Grad C: ");
  Serial.println(tempC);
  // Messwert auf 0 setzen
  tempC=0;
  // warten 1 Sekunde
  delay(1000);
}

