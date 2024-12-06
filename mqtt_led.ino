#include <WiFi.h>
#include <PubSubClient.h>

// Wi-Fi credentials
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

// MQTT broker details
const char* mqtt_broker = "192.168.0.141"; // Replace with your MQTT broker's IP
const int mqtt_port = 1883;
const char* commandTopic = "esp32/commands"; // Topic for receiving commands

// LED pin
const int ledPin = 2;

// WiFi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");

  // Connect to MQTT broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("ESP32Receiver")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed, state: ");
      Serial.println(client.state());
      delay(2000);
    }
  }

  // Subscribe to command topic
  client.subscribe(commandTopic);
  Serial.println("Subscribed to command topic");
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(message);

  // Handle commands
  if (message == "1") {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED ON");
  } else if (message == "0") {
    digitalWrite(ledPin, LOW);
    Serial.println("LED OFF");
  } else {
    Serial.println("Unknown command received");
  }
}

void loop() {
  client.loop();
}
