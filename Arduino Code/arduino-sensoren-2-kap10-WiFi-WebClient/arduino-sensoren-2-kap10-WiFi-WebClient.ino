// Wifi Webclient mit Arduino UNO R4 Wifi
// Datei: arduino-sensoren-2-kap10-WiFi-WebClient.ino

#include "WiFiS3.h"
#include "arduino_secrets.h" 

// Zugangsdaten zu WLAN
char ssid[] = SECRET_SSID;    // WLAN SSID
char pass[] = SECRET_PASS;    // WLAN Passwort

int status = WL_IDLE_STATUS;

// Initialisierung Webclient
WiFiClient client;

// Webserver Adresse
char server[] = "arduino-praxis.ch";
//IPAddress server(64,131,82,241);

// Zeit der letzten Verbindung
unsigned long lastConnectionTime = 0;
// Verzögerung zwischen Verbindungen in Millisekunden            
const unsigned long postingInterval = 10000; 


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
    //delay(10000);
  }
  // Ausgabe Wifi-Status
  printWifiStatus();
 
}


void read_request() {
  uint32_t received_data_num = 0;

  while (client.available()) {
    // Empfang Request
    char c = client.read();
    // Ausgabe
    Serial.print(c);
    // maximale Datenmenge
    received_data_num++;
    if(received_data_num % 80 == 0) { 
      
    }
    
  }  
}


void loop() {
  // Eingehende Daten lesen
  read_request();
  
  // Request ausführen alle x Sekunden
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }

}


void httpRequest() {
  // Verbindung schliessen vor neuer Anfrage
  client.stop();

  // wenn erfolgreiche Verbindung mit Webserver
  if (client.connect(server, 80)) {
    Serial.println("Verbindung...");
    // Anfrage senden
    client.println("GET / HTTP/1.1");
    client.println("Host: arduino-praxis.ch");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
    // Zeitpunkt des Verbindungsaufbaus
    lastConnectionTime = millis();
  } else {
    // Verbindungsaufbau fehlerhaft
    Serial.println("Error: Verbindung...");
  }
}

void printWifiStatus() {

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
