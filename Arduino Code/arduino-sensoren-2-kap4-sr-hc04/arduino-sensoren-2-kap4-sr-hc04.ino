// Abstandmessung mit HC-SR04-Ultraschall-Sensor
// Datei: arduino-sensoren-2-kap4-sr-hc04.ino

// Pins
const int TRIG_PIN=9;
const int ECHO_PIN=10;

// Variable für Abstand, Zeit
long abstand=0;
long zeitmessung=0;

void setup() 
{
  // Trigger für den Start der Messung
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(TRIG_PIN, INPUT);

  // Serielle Schnittstelle
  Serial.begin(9600);
}

void loop() 
{
  // Sender kurz aus
  digitalWrite(TRIG_PIN, LOW);
  delay(5);

  // Trigger-Impuls 10 Mikrosekunden
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  // Ende Signal
  digitalWrite(TRIG_PIN, LOW);
  
  // Warten und Zeit messen bis Rücksignal kommt
  zeitmessung = pulseIn(ECHO_PIN, HIGH);

  // Berechnung der Distanz in cm
  abstand=(zeitmessung/2)*0.03432;
  delay(500);
 

  // Ausgabe auf serielle Schnittstelle
  if (abstand < 100) 
  {
    Serial.print("Abstand: ");
    Serial.print(abstand);
    Serial.println(" cm");
  }
    // warten
  delay(60);
}
