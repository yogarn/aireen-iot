#include "config.h"

#include <EEPROM.h>
#include <Arduino.h>
#include <gravity_tds.h>
#include <ldr.h>

GravityTDS gravityTds;
LDR ldr(LDR_PIN, LDR_THRESHOLD, LDR_REFERENCE);

float temperature = 25, tdsValue = 0;
int ldrValue = 0;
int ldrVoltage = 0;
bool isLdrBright = false;

void setup() {
    Serial.begin(115200);

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

    Serial.print("TDS (ppm): ");
    Serial.println(tdsValue, 0);
    Serial.print("LDR: ");
    Serial.print(ldrValue);
    Serial.print(" | V: ");
    Serial.print(ldrVoltage, 2);
    Serial.print(" | Bright: ");
    Serial.println(isLdrBright ? "Yes" : "No");
    Serial.println("------------------------");

    delay(1000);
}
