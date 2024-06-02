// LoRa Server
// Datei: arduino-sensoren-2-kap8-lora-rf95-server.ino

#include <RHReliableDatagram.h>
#include <RH_RF95.h>
#include <SPI.h>

// Client/Server
#define SERVER_ADDRESS 10

// LoRa Instanz
RH_RF95 driver;
RHReliableDatagram manager(driver, SERVER_ADDRESS);

// Sensor-Daten
typedef struct {
      int sensor1;
      int sensor2;
}Payload;
Payload rxLoRa;

void setup() 
{
  // Serielle Schnittstelle
  Serial.begin(9600);
  while (!Serial) ;
  if (!manager.init())
    Serial.println("Initialisierung fehlgeschlagen...");
    
    // LoRa Frequenz
    driver.setFrequency(868);
    // LoRa
    driver.setTxPower(23, false);
}

uint8_t data[] = "ACKOK";
// Dont put this on the stack:
uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];

void loop()
{
  if (manager.available())
  {
    // Warten auf Nachricht von Client
    uint8_t buf[sizeof(buf)];
    uint8_t from;
    uint8_t len = sizeof(buf);

    if (manager.recvfromAck(buf, &len, &from))
    {
      // Daten empfangen
      memcpy(&rxLoRa, buf, sizeof(rxLoRa));
      Serial.print("Datenempfang von : ");
      Serial.println(from, DEC);
      Serial.print("Data1: ");
      Serial.print(rxLoRa.sensor1);
      Serial.print(", Data2: ");
      Serial.println(rxLoRa.sensor2);

      // Antwort abwarten
      if (!manager.sendtoWait(data, sizeof(data), from))
        Serial.println("sendtoWait failed");
    }
  }
}
