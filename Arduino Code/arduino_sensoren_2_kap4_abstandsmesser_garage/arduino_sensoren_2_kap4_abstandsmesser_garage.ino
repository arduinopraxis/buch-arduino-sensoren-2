// Abstandmesser für Garage mit SR-HC04
// Datei: arduino_sensoren_2_kap4_abstandsmesser_garage.ino

// Pins
const int TRIG_PIN=9;
const int ECHO_PIN=10;

// LED-Pins
int PinLED1 = 7;
int PinLED10 = 6;
int PinLED20 = 5;
int PinLED30 = 4;
int PinLED40 = 3;
int PinLED50 = 2;

// Variable für Abstand, Zeit
long abstand=0;
long zeitmessung=0;

void setup() 
{
  // Trigger für den Start der Messung
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(TRIG_PIN, INPUT);

    // LED für Abstandsanzeige
  pinMode(PinLED1, OUTPUT);
  pinMode(PinLED10, OUTPUT);
  pinMode(PinLED20, OUTPUT);
  pinMode(PinLED30, OUTPUT);
  pinMode(PinLED40, OUTPUT);
  pinMode(PinLED50, OUTPUT);

  // Serielle Schnittstelle
  Serial.begin(9600);
}

void loop() 
{
  // Sender kurz aus
  digitalWrite(TRIG_PIN, LOW);
  delay(5);

  // Trigger-Impuls 10 Mikrosekunden
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  // Ende Signal
  digitalWrite(TRIG_PIN, LOW);
  
  // Warten und Zeit messen bis Rücksignal kommt
  zeitmessung = pulseIn(ECHO_PIN, HIGH);

  // Berechnung der Distanz in cm
  abstand=(zeitmessung/2)*0.03432;
  delay(500);
 

  // Ausgabe auf serielle Schnittstelle
  if (abstand < 100) 
  {
    Serial.print("Abstand: ");
    Serial.print(abstand);
    Serial.println(" cm");
  // Ansteuerung der Abstands-LED
    if (abstand >= 1)
    {
       CountOut(128);
      //Ausgabe mit Portmanipulation (ATmega328)
      //PORTD = B10000000;
      }
    if (abstand >= 10)
    {
      CountOut(192);
      }
    if (abstand >= 20)
    {
      CountOut(224);
      }
    if (abstand >= 30)
    {
       CountOut(240);
      }
    if (abstand >= 40)
    {
       CountOut(248);
      }
    if (abstand >= 50)
    {
       CountOut(252);
      }
  }
    // warten bis nächste Messung
  delay(60);
}

void CountOut(byte c)
{
  int valD0 = c % 2;  // LSB
  int valD1 = c / 2 % 2;
  int valD2 = c / 4 % 2;
  int valD3 = c / 8 % 2;
  int valD4 = c / 16 % 2;
  int valD5 = c / 32 % 2;
  int valD6 = c / 64 % 2;
  int valD7 = c / 128 % 2; //MSB

  digitalWrite(7, valD7); // MSB
  digitalWrite(6, valD6);
  digitalWrite(5, valD5);
  digitalWrite(4, valD4);
  digitalWrite(3, valD3);
  digitalWrite(2, valD2);
  digitalWrite(1, valD1);
  digitalWrite(0, valD0); // LSB 
}
