// Serielle Ausgabe
// Datei: arduino-sensoren-2-kap8-serielle-ausgabe.ino

int valA0;
int analogPin=0;

void setup()
{
  // Konfiguration serielle Schnittstelle
  Serial.begin(9600); 
}

void loop() 
{
  valA0=analogRead(analogPin);
  Serial.print("Wert A0: "); 
  Serial.println(valA0);
  delay(1000);
}

