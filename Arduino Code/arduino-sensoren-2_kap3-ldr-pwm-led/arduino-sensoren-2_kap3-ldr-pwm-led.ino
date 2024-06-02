// Nachtlampe mit LDR
// Datei: arduino-sensoren-2_kap3-ldr-pwm-led.ino

// Analogwert von LDR    
int valLDR = 0;
// Analogeingang A0
int LDRPin = 0;   
// LED Pin (PWM)
int LEDpin = 6; 
// Helligkeit der LED
int LEDHelligkeit;

void setup() 
{
  // Serielle Schnittstelle
  Serial.begin(9600); 
}

void loop() 
{
  // Wert des LDRs einlesen
  valLDR = analogRead(LDRPin);
  // Ausgabe LDR-Helligkeit
  Serial.print("LDR: ");
  Serial.println(valLDR);
  // LED-Ansteuerung
  LEDHelligkeit = map(valLDR, 1023, 0, 0, 255);
  analogWrite(LEDpin, LEDHelligkeit); 
  delay(500);       
}

