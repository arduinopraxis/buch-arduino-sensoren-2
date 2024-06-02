// Garagentor-Wächter mit Tilt-Sensor - AT407
// Datei: arduino-sensoren-2-kap4-garagentor-waechter.ino


int LEDrot = 12;
int LEDgruen = 13;
int TiltPin = 2;

int wertTilt = 0;


void setup()
{
  // LED
  pinMode (LEDrot,OUTPUT);
  pinMode (LEDgruen,OUTPUT);
  // Eingang Tilt-Sensor
  pinMode (TiltPin,INPUT);
}


void loop()
{
   wertTilt = digitalRead(TiltPin);
   if (wertTilt == HIGH)
   {
      digitalWrite(LEDrot,HIGH);
      digitalWrite(LEDgruen,LOW);
   }
   else 
   {
    digitalWrite(LEDrot,LOW);
    digitalWrite(LEDgruen,HIGH);
   }
   delay(500);
}
