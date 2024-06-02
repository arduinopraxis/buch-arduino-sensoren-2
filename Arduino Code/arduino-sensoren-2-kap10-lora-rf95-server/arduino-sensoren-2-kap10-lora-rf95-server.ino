// LoRa Server
// Datei: arduino-sensoren-2-kap10-lora-rf95-server.ino

#include <RHReliableDatagram.h>
#include <RH_RF95.h>
#include <SPI.h>

// Client/Server
#define SERVER_ADDRESS 10

// LoRa Instanz
RH_RF95 driver;
RHReliableDatagram manager(driver, SERVER_ADDRESS);

// Sensor Data
typedef struct {
      int temp;
      int hum;
      int supplyV;
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
      Serial.print("Temp: ");
      Serial.print(rxLoRa.temp);
      Serial.print(", Hum: ");
      Serial.print(rxLoRa.hum);
      Serial.print(", VCC: ");
      Serial.println(rxLoRa.supplyV);

      // Antwort abwarten
      if (!manager.sendtoWait(data, sizeof(data), from))
        Serial.println("sendtoWait failed");
    }
  }
}
