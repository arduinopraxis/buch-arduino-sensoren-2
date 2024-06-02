// Wifi Webserver mit Arduino UNO R4 Wifi
// Datei: arduino-sensoren-2-kap11-WiFi-Webserver.ino

#include "WiFiS3.h"
#include "arduino_secrets.h" 

// Zugangsdaten zu WLAN
char ssid[] = SECRET_SSID;    // WLAN SSID
char pass[] = SECRET_PASS;    // WLAN Passwort

int status = WL_IDLE_STATUS;

// Initialisierung Webserver
WiFiServer server(80);

void setup() {
  //Initialisierung
  Serial.begin(9600);
  while (!Serial) {
    ; // warten auf seriellen Post
  }

  // Status Wifi-Modul prüfen
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("ERROR - Verbindung zu WLAN-Modul...");
    // nichts weiter unternehmen
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("INFO: Update Firmware...");
  }

  // Wifi-Verbindung
  while (status != WL_CONNECTED) {
    Serial.print("Verbinden mit SSID: ");
    Serial.println(ssid);
    // WLAN-Verbindung
    status = WiFi.begin(ssid, pass);

    // warten
    delay(10000);
  }

  // Start Webserver
  server.begin();
  // Ausgabe Wifi-Status
  printWifiStatus();
}


void loop() {
  // Warten auf Anfragen von Clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Neue Anfrage");
    // Ein Request endet mit leerer Zeile
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // HTTP-Request am Ende, Antwort senden
        if (c == '\n' && currentLineIsBlank) {
          // HTTP Header, Error Code 200 = OK
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          // Seite neu laden nach 5 Sekunden
          client.println("Refresh: 5");
          client.println();
          // Ausgabe HTML-Dokument
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // Ausgabe von Werten von Analog-Eingängen A0-A5
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("Eingang ");
            client.print(analogChannel);
            client.print(": ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // Neue Zeile
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // aktuelle Zeile
          currentLineIsBlank = false;
        }
      }
    }
    // Verzögerung für Datenempfang
    delay(1);

    // Verbindung schliessen
    client.stop();
    Serial.println("Verbindung schliessen..");
  }
}


void printWifiStatus() 
{
  // Ausgabe SSID
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // Ausgabe IP-Adresse des Boards
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // Signalstärke
  long rssi = WiFi.RSSI();
  Serial.print("RSSI:");
  Serial.print(rssi);
  Serial.println(" dBm");
}
