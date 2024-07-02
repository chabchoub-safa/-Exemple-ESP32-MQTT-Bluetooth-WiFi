#include "BluetoothSerial.h"
#include <WiFi.h>
#include <PubSubClient.h>

BluetoothSerial SerialBT; // Créez un objet BluetoothSerial pour gérer la connexion

#define ID 2
// WiFi
const char ssid[] = "safachbchoub089@gmail.com"; // Enter your WiFi name
const char password[] = "!9rh3dr";  // Enter WiFi password

// MQTT Broker
const char mqtt_broker[] = "broker.emqx.io";
const char topic[] = "autoliv";

const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200); // Pour le débogage
  SerialBT.begin("ESP32test"); // Initialisez le service Bluetooth avec un nom pour votre appareil

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  // Connect to MQTT broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    const char client_id[] = "mqttx_8f7efa7c";
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id);
    if (client.connect("jgtf756bcdky58jr")) {
      Serial.println("Public emqx mqtt broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  // Publish and subscribe
  client.publish(topic, "Hi EMQX I'm ESP32 ^^");
  client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}

void loop() {
      client.loop();
   if (SerialBT.available()) { // Vérifiez si des données sont disponibles à lire via Bluetooth
    String data = SerialBT.readStringUntil('\n'); // Lisez les données jusqu'à ce que vous obteniez une nouvelle ligne
    Serial.println(data); // Affichez les données sur le moniteur série pour le débogage
  }
}
