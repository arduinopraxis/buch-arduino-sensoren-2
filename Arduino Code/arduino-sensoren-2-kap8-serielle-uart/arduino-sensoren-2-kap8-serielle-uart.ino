// Serielle Ausgabe (UART)
// Datei: arduino-sensoren-2-kap8-serielle-uart.ino

int valA0;
int analogPin=0;
int SensorID=55;

void setup()
{
  // Konfiguration serielle Schnittstellen
  // Native
  Serial.begin(9600); 
  Serial.println("Serial Sensor...");
  // UART
  Serial1.begin(115200); 
}

void loop() 
{
  valA0=analogRead(analogPin);
  // Serielle Ausgabe
  Serial.print(SensorID);
  Serial.print(",");
  Serial.print(valA0);
  Serial.println("!");

  // UART
  Serial1.print(SensorID);
  Serial1.print(",");
  Serial1.print(valA0);
  Serial1.println("!");
  delay(1000);
}

