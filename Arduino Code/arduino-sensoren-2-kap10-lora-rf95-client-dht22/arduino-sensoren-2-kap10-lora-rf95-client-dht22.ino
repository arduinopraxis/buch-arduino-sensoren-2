// LoRa Client - DHT22
// Datei: arduino-sensoren-2-kap10-lora-rf95-client-dht22.ino

// Status: offen


#include <RHReliableDatagram.h>
#include <RH_RF95.h>
#include <SPI.h>
#include "LowPower.h"
#include "DHT.h"

// Client ID
#define CLIENT_ADDRESS 40
// Server ID
#define SERVER_ADDRESS 10

// LoRa config
RH_RF95 driver;
RHReliableDatagram manager(driver, CLIENT_ADDRESS);

// Sensor
#define sensorPinPower 9
#define sensorPinData1 5

// Auswahl DHT Sensor Typ
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Sensor Objekt erstellen
DHT dht(sensorPinData1, DHTTYPE);

typedef struct {
      int temp;
      int hum;
      int supplyV;
}Playload;

Playload LoRaData;

long readVcc() {
   bitClear(PRR, PRADC); ADCSRA |= bit(ADEN); // Enable the ADC
   long result;
   // Read 1.1V reference against Vcc
   #if defined(__AVR_ATtiny84__) 
    ADMUX = _BV(MUX5) | _BV(MUX0); // For ATtiny84
   #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);  // For ATmega328
   #endif 
   delay(2); // Wait for Vref to settle
   ADCSRA |= _BV(ADSC); // Convert
   while (bit_is_set(ADCSRA,ADSC));
   result = ADCL;
   result |= ADCH<<8;
   result = 1126400L / result; // Back-calculate Vcc in mV
      return result;
} 

void sleepCounter(int sleepcount) 
{
  for(int count=0; count<sleepcount; count = count + 1){
     LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    }
}


void setup() 
{
  Serial.begin(9600);
  if (!manager.init())
    Serial.println("init failed");

    // LoRa Frequenz
    driver.setFrequency(868);

    driver.setTxPower(14, false);

    // Sensor
    pinMode(sensorPinPower, OUTPUT);
    dht.begin();
}

uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];

void loop()
{
  Serial.println("LoRa Client - DHT22");

  // Daten
  digitalWrite(sensorPinPower, HIGH);
  delay(2000);
  // Luftfeuchtigkeit
  float h = dht.readHumidity();
  // Temperatur
  float t = dht.readTemperature();
  // Prüfen ob richtiger Rückgabewert
  if (isnan(t) || isnan(h))
  {
    Serial.println("DHT Fehler bei Initialisierung...");
  }
  else
  {
    LoRaData.temp=t*100;
    LoRaData.hum=h*100;
    LoRaData.supplyV=readVcc();
  if (manager.sendtoWait((uint8_t*)&LoRaData, sizeof(LoRaData), SERVER_ADDRESS))
  {
    // Antwort abwarten
    uint8_t len = sizeof(buf);
    uint8_t from;   
    if (manager.recvfromAckTimeout(buf, &len, 2000, &from))
    {
      Serial.print("got reply from : 0x");
      Serial.print(from, HEX);
      Serial.print(": ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(driver.lastRssi(), DEC);    
    }
    else
    {
      Serial.println("No reply, is rf95_reliable_datagram_server running?");
    }
  }
    
  }

  // Power Aus von Sensor
  digitalWrite(sensorPinPower, LOW); 
   
  // Sleep und Delay
  driver.sleep();
  sleepCounter(20);
}
