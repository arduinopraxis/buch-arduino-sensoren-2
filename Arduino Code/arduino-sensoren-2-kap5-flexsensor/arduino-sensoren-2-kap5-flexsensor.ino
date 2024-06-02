// Flex-Sensor
// Datei: arduino-sensoren-2-kap5-flexsensor.ino

int flexPin = A0;
int valFlex = 0;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Flex-Sensor...");
}

void loop() 
{
  // Read the ADC, and calculate voltage and resistance from it
  valFlex = analogRead(flexPin);

  // Serielle Ausgabe
  Serial.print("Flex Wert: ");
  Serial.println(valFlex);

  delay(1000);
}

