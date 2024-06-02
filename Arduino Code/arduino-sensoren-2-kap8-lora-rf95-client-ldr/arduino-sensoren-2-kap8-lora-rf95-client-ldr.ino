// LoRa - Client
// Datei: arduino-sensoren-2-kap8-lora-rf95-client-ldr.ino

#include <RHReliableDatagram.h>
#include <RH_RF95.h>
#include <SPI.h>

// Client ID
#define CLIENT_ADDRESS 40
// Server ID
#define SERVER_ADDRESS 10

// LoRa config
RH_RF95 driver;
RHReliableDatagram manager(driver, CLIENT_ADDRESS);

// Sensor
#define sensorPinData1 A0

// Datenstruktur
typedef struct {
      int sensor1;
      int sensor2;
}Playload;

Playload LoRaData;

void setup() 
{
  // Serielle Schnittstelle
  Serial.begin(9600);
  while (!Serial) ; // warten bis Port bereit
  if (!manager.init())
    Serial.println("Initialisierungsfehler...");

  // LoRa Frequenz
  driver.setFrequency(868);

  driver.setTxPower(14, false);

}

// Dont put this on the stack:
uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];

void loop()
{
  // Daten Sensor
  LoRaData.sensor1=analogRead(sensorPinData1);
  LoRaData.sensor2=9999;
    
  // Meldung senden an Message Server
  if (manager.sendtoWait((uint8_t*)&LoRaData, sizeof(LoRaData), SERVER_ADDRESS))
  {
    // Warten auf Antwort
    uint8_t len = sizeof(buf);
    uint8_t from;   
    if (manager.recvfromAckTimeout(buf, &len, 2000, &from))
    {
      Serial.print("got reply from : 0x");
      Serial.print(from, HEX);
      Serial.print(": ");
      Serial.println((char*)buf);
    }
    else
    {
      Serial.println("Keine Antwort vom Server...");
    }
  }
  else
  {
    Serial.println("sendtoWait fehlgeschlagen");
  }
  // Warten 
  delay(30000);
}
