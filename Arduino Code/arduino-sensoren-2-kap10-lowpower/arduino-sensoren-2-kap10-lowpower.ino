// Sensor-Board im Low-Power-Betrieb
// Datei: arduino-sensoren-2-kap10-lowpower.ino

#include "LowPower.h"

void setup()
{
  // keine Funktionen notwendig
}

void loop()
{
  // Sleep-Modus für 8 Sekunden, ADC aus, BOD aus
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  // Sensorwerte weiterverarbeiten, beispielsweise Daten senden oder speichern
  //..
}