// Flex-Sensor
// Datei: arduino-sensoren-2-kap5-candy-waechter.ino

// Eingang Sensor
int flexPin = A0;
// Ausgang LED
int ledPin =  13;

int valFlex = 0;
// Schaltschwelle
int valFlexAlarm = 230;
unsigned long startAlarm=0;
// Zeit für Alarmauslösung
unsigned long AlarmMeldung=5000;
int valState = 0;


void setup() 
{
  // Ausgang LED
  pinMode(ledPin, OUTPUT);
  // Serielle Schnittstelle
  Serial.begin(9600);
  Serial.println("Flex-Sensor...");
}

void loop() 
{
  // Aktuelle Zeit
  unsigned long currentMillis = millis();
  // Wert des Flex-Sensors einlesen
  valFlex = analogRead(flexPin);
  // Ausgabe Sensorwert
  Serial.print("Wert: ");
  Serial.println(valFlex);

  // Wert ist grösser als Alarmschwelle -> Schrank geöffnet
  if (valFlex >= valFlexAlarm) 
  {
    if (valState == 0)
    {
      valState = 1;
      startAlarm = millis();
     Serial.println("Alarm - Schrank offen");
    }
    
    // Alarm auslösen nach 5 Sekunden
    if (currentMillis-startAlarm >= AlarmMeldung)
    {
      // Alarmanzeige einschalten
      digitalWrite(ledPin, HIGH);
      // Alarmmeldung ausgeben
      Serial.println("ALARM-ALARM");
    }

  
  }
  else
  {
    // Zustände zurücksetzen
    valState = 0;
    digitalWrite(ledPin, LOW);
  }
 delay(100);
}

