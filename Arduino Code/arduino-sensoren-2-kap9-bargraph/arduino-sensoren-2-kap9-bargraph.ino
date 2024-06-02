// 10-Segment-Anzeige - Bargraph
// (Beispiel Bargraph)
// Datei: arduino-sensoren-2-kap9-bargraph.ino

/*
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/BarGraph
 */

// Analoger Eingang
int analogPin = A0;
// Anzahl LEDs
int AnzahlLED = 10;

int valAnalog;

// Array mit der einzelnen LED-Pins
int ledPin[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

void setup() 
{
  // Schleife über alle LEDs
  for (int LEDNummer = 0; LEDNummer < AnzahlLED; LEDNummer++) 
  {
    // Pin als Ausgang setzen
    pinMode(ledPin[LEDNummer], OUTPUT);
  }
}

void loop() 
{
  // analogen Wert einlesen
  valAnalog = analogRead(analogPin);
  // Analogwert auf die Anzahl LEDs mappen
  int LEDLevel = map(valAnalog, 0, 1023, 0, AnzahlLED);

  // Schleife über LED-Array
  for (int LEDNummer = 0; LEDNummer < AnzahlLED; LEDNummer++) {

    // prüfen, ob LED-Nummer kleiner als LED-Level
    if (LEDNummer < LEDLevel) 
    {
      // LED ein
      digitalWrite(ledPin[LEDNummer], HIGH);
    }
    else 
    {
      // LED aus
      digitalWrite(ledPin[LEDNummer], LOW);
    }
  }
}



