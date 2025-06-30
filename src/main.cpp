#include <EEPROM.h>
#include <Arduino.h>
#include "gravity_tds.h"
#include "ldr.h"
#include "ph_meter.h"
#include "temperature.h"
#include "turbidity.h"
#include "config.h"

GravityTDS gravityTds;
LDR ldr(LDR_PIN, LDR_THRESHOLD, LDR_REFERENCE);
PHMeter phSensor(PH_SENSOR_PIN);
TemperatureSensor tempSensor(TEMP_SENSOR_PIN);
TurbiditySensor turbSensor(TURBIDITY_PIN);

float temperature = 25, tdsValue = 0;
int ldrValue = 0;
int ldrVoltage = 0;
bool isLdrBright = false;
float phValue = 0;
float tempC = 0;
float ntu = 0;

void setup()
{
    Serial.begin(115200);

    gravityTds.setPin(TDS_SENSOR_PIN);
    gravityTds.setAref(3.3);
    gravityTds.setAdcRange(4096);
    gravityTds.begin();

    phSensor.begin();
    tempSensor.begin();
    turbSensor.begin();
}

void loop()
{
    tempC = tempSensor.readTemperature();
    temperature = tempC;

    gravityTds.setTemperature(temperature);
    gravityTds.update();
    tdsValue = gravityTds.getTdsValue();

    ldrValue = ldr.readRaw();
    ldrVoltage = ldr.readVoltage();
    isLdrBright = ldr.isBright();

    phValue = phSensor.readPH();
    ntu = turbSensor.readNTU();

    Serial.print("Temperature (C): "); Serial.println(tempC);
    Serial.print("TDS (ppm): "); Serial.println(tdsValue, 0);
    Serial.print("LDR: "); Serial.print(ldrValue);
    Serial.print(" | V: "); Serial.print(ldrVoltage, 2);
    Serial.print(" | Bright: "); Serial.println(isLdrBright ? "Yes" : "No");
    Serial.print("pH: "); Serial.println(phValue);
    Serial.print("Turbidity (NTU): "); Serial.println(ntu);
    Serial.println("------------------------");

    delay(1000);
}
