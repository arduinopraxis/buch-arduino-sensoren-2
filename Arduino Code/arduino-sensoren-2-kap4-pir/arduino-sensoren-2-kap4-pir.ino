// PIR-Bewegungsmelder
// Datei: arduino-sensoren-2-kap4-pir.ino

// LED
int ledPin = 13;
// PIR-Sensor
int pirPin = 3;

int pirStatus;


void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);

  // Serielle Schnittstelle
  Serial.begin(9600);
  Serial.print("PIR-Sensor...");
  // Ausgang Aus
  digitalWrite(ledPin, LOW);
}

void loop() 
{
  // PIR-Sensor einlesen
  pirStatus = digitalRead(pirPin);
  digitalWrite(ledPin, pirStatus);
  // warten
  delay(500);
}
