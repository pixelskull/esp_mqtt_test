#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"

// MQTT Server settings
const int mqttPort = 1883;
const char* mqttTopic = "locations";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    // Start serial
    Serial.begin(115200);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    client.setServer(mqttServer, mqttPort);

    while (!client.connected()) {
        Serial.println("Connecting to MQTT...");

        if (client.connect("ESP32Client")) {
            Serial.println("connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
}

void loop() {
    // Create JSON with dummy values
    String jsonData = "{\"imei\":\"123456789\",\"latitude\":\"50.1109\",\"longitude\":\"8.6821\"}";

    // Send data over MQTT
    client.publish(mqttTopic, jsonData.c_str());

    // Wait before sending again
    delay(1000);
}

