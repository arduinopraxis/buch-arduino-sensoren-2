// Fensterkontakt
// Datei: arduino-sensoren-2-kap7-fensterkontakt.ino

int magnetPin = 2;
int kontaktStatus = 0;
int LEDPin = 4;

void setup() 
{
  // Serielle Schnittstelle starten
  Serial.begin(9600);
  // Ausgang für LED setzen 
  pinMode(LEDPin, OUTPUT);
  Serial.println("Fensterkontakt prüfen...");
}

void loop() 
{
  // Fensterkontakt einlesen
  kontaktStatus = digitalRead(magnetPin);
  // Abfragen ob Wert = HIGH
  if (kontaktStatus == HIGH)
  {
    // Alarm - LED einschalten
    digitalWrite(LEDPin, HIGH);
    // Zustand ausgeben
    Serial.println("Fensterkontakt: AUS - ALARM");
  }
  else
  {
    // LED ausschalten
    digitalWrite(LEDPin, LOW);
    // Zustand ausgeben
    Serial.println("Fensterkontakt: EIN");
  }
  
  // 1 Sekunde warten
  delay(1000);
}
 
