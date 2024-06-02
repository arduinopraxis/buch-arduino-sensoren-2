// IR-Empfänger mit Fernsteuerung
// arduino-sensoren-2-kap3-ir-receive-fernsteuerung.ino

//#define DECODE_DENON      // Includes Sharp
//#define DECODE_JVC
//#define DECODE_KASEIKYO
//#define DECODE_PANASONIC   // alias for DECODE_KASEIKYO
//#define DECODE_LG
#define DECODE_NEC          // Includes Apple and Onkyo. To enable all protocols , just comment/disable this line.
//#define DECODE_SAMSUNG
//#define DECODE_SONY
//#define DECODE_RC5
//#define DECODE_RC6
//#define DECODE_BOSEWAVE
//#define DECODE_LEGO_PF
//#define DECODE_MAGIQUEST
//#define DECODE_WHYNTER
//#define DECODE_FAST

#include <Arduino.h>
#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>

void setup() 
{
  // Serielle Schnittstelle
  Serial.begin(115200);
  // IR Empfänger
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  
  Serial.print("IR Signals...");
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
}

void loop() 
{
  // IR Empfänger
  if (IrReceiver.decode()) 
  {
    // Empfangene Daten
    // Unbekannte Daten
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      // Daten ausgeben
      IrReceiver.printIRResultRawFormatted(&Serial, true);
      IrReceiver.resume();
      }
      else
      {
        // Zurücksetzen für neuen Empfang
        IrReceiver.resume();
        IrReceiver.printIRResultShort(&Serial);
        IrReceiver.printIRSendUsage(&Serial);
        }
        Serial.println();

        // Daten auswerten und Aktion
        // Taste 5
        if (IrReceiver.decodedIRData.command == 0x1C) {
            Serial.println("TASTE - 5");
        } 
    }
}
