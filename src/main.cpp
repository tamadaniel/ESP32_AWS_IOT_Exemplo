// https://www.youtube.com/watch?v=idf-gGXvIu4

// Import required libraries
#include <Arduino.h>
#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include <time.h>

// AWS IoT MQTT Topics
#define AWS_IOT_PUBLISH_TOPIC   "Mqtt_exemplo/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "Mqtt_exemplo/sub"

// Initialize WiFi and MQTT for AWS IoT
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

void messageHandler(char* topic, byte* payload, unsigned int length);

// Function to configure and initialize time
void setupTime() {
  // Brazil Time Zone (for Brasilia) is UTC-3
  // Adjust the timezone offset if you are in a different time zone in Brazil
  configTime(-3 * 3600, 0, "br.pool.ntp.org", "south-america.pool.ntp.org");

  Serial.println("Waiting for time");
  while (time(nullptr) < 86400) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Time synchronized");
}

// Function to connect to AWS IoT
void connectAWS() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);

  // Create a message handler
  client.setCallback(messageHandler);

  Serial.println("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }

  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

// Function to publish messages to AWS IoT
void publishMessage() {
  StaticJsonDocument<200> doc;

  // Generate a random number
  int randomNumber = random(0, 100); // This will generate a number between 0 and 99
  doc["aleatorio"] = randomNumber;

  // Add a timestamp to the JSON document
  time_t now;
  time(&now);
  doc["timestamp"] = now;

  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // serialize the JSON object to a buffer

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

// Callback function to handle MQTT messages
void messageHandler(char* topic, byte* payload, unsigned int length) {
  Serial.print("Incoming message on topic: ");
  Serial.println(topic);

  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  Serial.println(message);
}

// Setup function
void setup() {
  Serial.begin(115200);
  connectAWS();
  setupTime(); // Set up the time after connecting to Wi-Fi
}

// Main loop function
void loop() {
  if (!client.connected()) {
    connectAWS();
  }
  publishMessage();
  client.loop();
  delay(1000);
}
