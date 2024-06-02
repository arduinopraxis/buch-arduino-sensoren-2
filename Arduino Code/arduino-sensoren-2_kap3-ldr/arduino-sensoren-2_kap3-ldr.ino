// LDR
// Datei: arduino-sensoren-2_kap3-ldr.ino


// Analogwert von LDR    
int valLDR = 0;
// Analogeingang A0
int LDRPin = 0;   

void setup() 
{
  // Serielle Schnittstelle
  Serial.begin(9600); 
}

void loop() 
{
  // Wert des LDRs einlesen
  valLDR = analogRead(LDRPin); 
  // Ausgabe des Werts auf der seriellen Schnittstelle 
  Serial.print("LDR: ");
  Serial.println(valLDR);
  delay(1000);       
}

