// UV-Sensor MP8511
// Datei: arduino-sensoren-2_kap3-uv-index-monitor.ino


/* 
 MP8511 UV Sensor Read Example
 By: Nathan Seidle
 SparkFun Electronics
 Date: January 15th, 2014
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
*/

// Pins RGB
int redPin = 9;
int greenPin = 10;
int bluePin = 11; 


// Pins
int uvPin = 0;
int refPin = 1;

// UV-Index - Farbwerte
// grün (0, 255, 0)
// gelb (250, 105, 0)
// orange (250, 40, 0)
// rot (255, 0, 0)
// violett (200, 0, 255);

int ledRGB[11][3] = {   
  {0, 255, 0}, 
  {0, 255, 0}, 
  {250, 105, 0},
  {250, 105, 0},
  {250, 105, 0},
  {250, 40, 0},
  {250, 40, 0},
  {255, 0, 0},
  {255, 0, 0},
  {255, 0, 0},
  {200, 0, 255}
  };

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  pinMode(uvPin, INPUT);
  pinMode(refPin, INPUT);
  
  Serial.begin(9600);
  Serial.println("UV Messung...");
}


void loop()
{
  // UV-Wert
  int uvLevel = averageAnalogRead(uvPin);
  // Referenzwert 3,3 V
  int refLevel = averageAnalogRead(refPin);
  
  // UV-Wert als Spannung
  float outputVoltage = 3.3 / refLevel * uvLevel;
  // UV-Wert-Spannung als UV-Index mappen
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.9, 0.0, 15.0);
  // UV-Index als Integer
  int uvInt=int(uvIntensity);
  uvInt=uvInt-1;

  // Ansteuerung RGB
  // LED rot
  int colR=ledRGB[uvInt][0];
  // LED grün
  int colG=ledRGB[uvInt][1];
  // LED blau
  int colB=ledRGB[uvInt][2];
  // Ansteuerung RGB
  setColor(colR, colG, colB);
  
  // Ausgabe-Wert auf serielle Schnittstelle
  Serial.print("UV-Index: ");
  Serial.println(uvIntensity);

  
  // warten 1 Sekunde
  delay(1000);
}

void setColor(int red, int green, int blue)
{
  red=255-red;
  green=255-green;
  blue=255-blue;
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}


// Messung mit Mittelwert mit jeweils 8 Messungen
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue = runningValue+analogRead(pinToRead);
  runningValue = runningValue/numberOfReadings;

  return(runningValue);  
}


//The Arduino Map function but for floats
//From: http://forum.arduino.cc/index.php?topic=3922.0
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

