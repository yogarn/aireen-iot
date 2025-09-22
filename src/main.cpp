#include "config.h"

#include <EEPROM.h>
#include <Arduino.h>
#include <gravity_tds.h>
#include <ldr.h>
#include <mqtt_client.h>
#include <WiFi.h>
#include <ArduinoJson.h>

GravityTDS gravityTds;
LDR ldr(LDR_PIN, LDR_THRESHOLD, LDR_REFERENCE);
MqttClient mqtt(MQTT_HOST, MQTT_PORT, MQTT_CLIENT);

float temperature = 25, tdsValue = 0;
int ldrValue = 0;
int ldrVoltage = 0;
bool isLdrBright = false;

void messageCallback(char *topic, byte *payload, unsigned int length) {
    Serial.print("[MQTT] Message on ");
    Serial.print(topic);
    Serial.print(": ");
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
}

void setup() {
    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("WiFi connected");

    mqtt.begin();
    mqtt.setCallback(messageCallback);
    mqtt.subscribe(MQTT_TOPIC); // adjust topic as needed in future

    gravityTds.setPin(TDS_PIN);
    gravityTds.setAref(3.3);
    gravityTds.setAdcRange(4096);
    gravityTds.begin();
}

void loop() {
    gravityTds.setTemperature(temperature);
    gravityTds.update();
    tdsValue = gravityTds.getTdsValue();

    ldrValue = ldr.readRaw();
    ldrVoltage = ldr.readVoltage();
    isLdrBright = ldr.isBright();

    JsonDocument doc;
    doc["tds"] = tdsValue;
    doc["ldr"] = ldrValue;
    char buffer[128];
    serializeJson(doc, buffer);

    Serial.println(buffer);
    mqtt.publish(MQTT_TOPIC, buffer);

    mqtt.loop();

    delay(5000);
}
