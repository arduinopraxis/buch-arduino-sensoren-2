// Umweltsensoren ENS160+AHT21 - Daten lesen
// Datei: arduino-sensoren-2-kap7-umwelt-ens160-aht21.ino

#include <DFRobot_ENS160.h>
#include <Wire.h>
#include "AHT20.h"

// AHT21 Sensor
AHT20 AHT;

// ENS160 Sensor
#define I2C_COMMUNICATION
#ifdef  I2C_COMMUNICATION
  // Sensor an I2C Bus, Adresse 0x53
  DFRobot_ENS160_I2C ENS160(&Wire, /*I2CAddr*/ 0x53);
#else
  // Andernfalls SPI mit CS an D3
  uint8_t csPin = D3;
  DFRobot_ENS160_SPI ENS160(&SPI, csPin);
#endif

void setup()
{
  Serial.begin(115200);
  Serial.println("Umweltsensor ENS160+AHT21");
  // Initialisierung AHT
  AHT.begin();
  // Initialisierung ENS160
  while( NO_ERR != ENS160.begin() ){
    Serial.println("ENS160-Verbindungsfehler..");
    delay(3000);
  }
  Serial.println("ENS160-OK");
  Serial.println("-------------------------------");

  // ENS160 Konfiguration
   /**
   * Set power mode
   * mode Configurable power mode:
   *   ENS160_SLEEP_MODE: DEEP SLEEP mode (low power standby)
   *   ENS160_IDLE_MODE: IDLE mode (low-power)
   *   ENS160_STANDARD_MODE: STANDARD Gas Sensing Modes
   */
  ENS160.setPWRMode(ENS160_STANDARD_MODE);

  /**
   * Users write ambient temperature and relative humidity into ENS160 for calibration and compensation of the measured gas data.
   * ambientTemp Compensate the current ambient temperature, float type, unit: C
   * relativeHumidity Compensate the current ambient temperature, float type, unit: %rH
   */
  ENS160.setTempAndHum(/*temperature=*/25.0, /*humidity=*/50.0);
}

void loop()
{
  // Daten AHT21
  float humi, temp;
    
  int ret = AHT.getSensor(&humi, &temp);
    
  // falls Daten empfangen
  if(ret)
  {
      Serial.print("Hum: ");
      Serial.println(humi*100);
      Serial.print("Temperatur: ");
      Serial.println(temp);
  }
  else
  {
    Serial.println("ERROR: Keine Daten von AHT21...");
    }

  // Daten ENS160
  uint8_t Status = ENS160.getENS160Status();
  Serial.print("ENS160 Status: ");
  Serial.println(Status);

  // Air Quality
  // 1-Excellent, 2-Good, 3-Moderate, 4-Poor, 5-Unhealthy
  uint8_t AQI = ENS160.getAQI();
  Serial.print("Air Quality Index : ");
  Serial.println(AQI);

  // TVOC Konzentration
  uint16_t TVOC = ENS160.getTVOC();
  Serial.print("Konzentration TVOC : ");
  Serial.print(TVOC);
  Serial.println(" ppb");

  // CO2 Konzentration
  uint16_t ECO2 = ENS160.getECO2();
  Serial.print("CO2: ");
  Serial.print(ECO2);
  Serial.println(" ppm");
  Serial.println("-------------------------------");

  // warten
  delay(1000);
}
