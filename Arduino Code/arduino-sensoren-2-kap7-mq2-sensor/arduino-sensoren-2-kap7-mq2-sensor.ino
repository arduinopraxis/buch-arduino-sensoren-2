// MQ2-Gas-Sensor
// Datei: arduino-sensoren-2-kap7-mq2-sensor.ino

// Variablen
int gasPin = 0;
int valGas= 0;

void setup()
{
  // Serielle Schnittstelle
  Serial.begin(9600);
  Serial.println("Messung Gas...");
}

void loop()
{
  // Messung Gas
  valGas = analogRead(gasPin);
  // Ausgabe auf serielle Schnittstelle
  Serial.print("Gas Wert: ");
  Serial.print(valGas);
  delay(1000);
}

