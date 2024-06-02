// Datenlogger
// Datei: arduino-sensoren-2-kap9-datenlogger.ino

#include <SD.h>
#include <SPI.h>

// Chip Select, Signal SS (Slave Select)
const int chipSelect = 10;

void setup()
{
  Serial.begin(9600);
  Serial.print("Initialisierung SD Card...");
  // SPI Chip Select als Ausgang setzen, auch wenn nicht genutzt
  pinMode(10, OUTPUT);
  
  // Prüfen ob SD-Card bereit für Initialisierung
  if (!SD.begin(chipSelect))
  {
    Serial.println("SD Card ist nicht bereit oder fehlt");
    // nichts weiter zu tun
    return;
  }
  Serial.println("SD Card initialisiert");
}

void loop()
{
  // String für Daten
  String dataString = "";

  // 3 analoge Eingänge lesen und zusammenfügen
  // Trennzeichen ist Komma (,)
  for (int analogPin = 0; analogPin < 3; analogPin++) {
    int sensor = analogRead(analogPin);
    dataString += String(sensor);
    if (analogPin < 2) {
      dataString += ","; 
    }
  }

  // Datendatei öffnen
  // es kann immer nur eine Datei gleichzeitig geöffnet werden
  File dataFile = SD.open("data.txt", FILE_WRITE);

  // falls Datei bereit, Daten schreiben
  if (dataFile) 
  {
    dataFile.println(dataString);
    dataFile.close();
    // Daten auf seriellen Port schreiben
    Serial.println(dataString);
  }  
  // Falls Fehler beim Öffnen der Datei, Meldung ausgeben
  else
  {
    Serial.println("Fehler beim Öffnen der Datendatei data.txt");
  }
  // warten 5 Sekunden
  delay(5000); 
}
