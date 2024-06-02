// Ansteuerung RGB
// Datei: arduino-sensoren-2-kap9-rgb-ansteuerung.ino

// LED-Pins
int LEDPinR = 2;
int LEDPinG = 3;
int LEDPinB = 4;

void setup() 
{
  // Ausgänge
  pinMode(LEDPinR, OUTPUT);
  pinMode(LEDPinG, OUTPUT);
  pinMode(LEDPinB, OUTPUT);
}


void loop() 
{
  // LED einzeln Ein
  // Common Anode
  // LED rot
  digitalWrite(LEDPinR, LOW);
  digitalWrite(LEDPinG, HIGH);
  digitalWrite(LEDPinB, HIGH);
  delay(500);
  // LED grün
  digitalWrite(LEDPinR, HIGH);
  digitalWrite(LEDPinG, LOW);
  digitalWrite(LEDPinB, HIGH);
  delay(500);
  // LED blau
  digitalWrite(LEDPinR, HIGH);
  digitalWrite(LEDPinG, HIGH);
  digitalWrite(LEDPinB, LOW);
 
  delay(1000);
  
  // alle LED Aus
  // Common Anode
  digitalWrite(LEDPinR, HIGH);
  digitalWrite(LEDPinG, HIGH);
  digitalWrite(LEDPinB, HIGH);
  // warten
  delay(1000);
}
