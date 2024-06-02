// MQTT Client
// Datei: arduino-sensoren-2-kap11-WiFi-MQTT-Client.ino

#include <WiFiS3.h>
#include <ArduinoMqttClient.h>

#include "arduino_secrets.h" 
// Wifi-Zugang in tab/arduino_secrets.h
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int status = WL_IDLE_STATUS;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "192.168.1.44";
int        port     = 1883;
const char topic[]  = "SensorBoard/Temp";
const char topicSub[]  = "SensorBoard/Sub";

// Interval
const long interval = 20000;
unsigned long previousMillis = 0;

// Sensor
int LDRPin = 0;

void setup() 
{
  // Serielle Schnittstelle
  Serial.begin(9600);
  while (!Serial) {
    ; // warten bis verbunden
  }

  // WLAN Verbindungsaufbau
  Serial.print("Verbinden mit SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(2000);
  }

  // Verbindung erfolgreich
  Serial.print("WLAN verbunden...");
  printCurrentNet();
  printWifiData();

  Serial.print("Verbinden mit MQTT Broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT Verbindung fehlgeschlagen! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("Verbunden mit MQTT broker!");
  Serial.println();

  // Nachrichtempfang
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Abonnieren Topic: ");
  Serial.println(topicSub);
  Serial.println();

  // Topic abonnieren
  mqttClient.subscribe(topicSub);
  // Warten auf Topic
  Serial.print("Warten auf  Topic: ");
  Serial.println(topicSub);
  Serial.println();

}

void loop() 
{
  mqttClient.poll();

  unsigned long currentMillis = millis();
  
  // Ausführen, wenn Intervall erreicht
  if (currentMillis - previousMillis >= interval) {
    // save the last time a message was sent
    previousMillis = currentMillis;

    // Sensor Wert einlesen
    int SensorVal = analogRead(LDRPin);

    // Serielle Ausgabe
    Serial.print("MQTT: ");
    Serial.println(topic);
    Serial.println(SensorVal);

    // MQTT Message publizieren
    mqttClient.beginMessage(topic);
    mqttClient.print(SensorVal);
    mqttClient.endMessage();

    Serial.println();
  }
}

void printWifiData() {
  // IP Adresse
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  
  Serial.println(ip);

  // MAC Adresse
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);
}

void printCurrentNet() {
  // SSID
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // Router
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);

  // Signalstärke
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // Encryption Type
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}


void onMqttMessage(int messageSize) {
  // Empfangene Nachricht ausgeben
  Serial.print("Nachricht erhalten von Topic '");
  Serial.println(mqttClient.messageTopic());

  // Nachricht in String speichern
  String message = mqttClient.readString();

  // Empfangene Nachricht in Kleinbuchstaben
  message.toLowerCase();

  // Falls empfangene Nachricht diesem Wert entspricht
  if(message == "Wert1") {
    onCustom();
    Serial.println("Wert1 Nachricht");
  } else if (message == "Wert2") {
    onCustom2();
    Serial.println("Wert2 Nachricht");
  } else {
    // anderfalls Topic ausgeben
  Serial.print("Topic Sub: ");
  Serial.println(message);
  }
  Serial.println();

}

void onCustom(){
  //Ausführen, wenn Wert1
}

void onCustom2(){
  //Ausführen, wenn Wert2
}