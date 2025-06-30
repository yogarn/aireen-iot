#include "Arduino.h"
#include "temperature.h"
#include "config.h"

TemperatureSensor tempSensor(TEMP_SENSOR_PIN); 

void setup() {
    Serial.begin(9600);
    tempSensor.begin();
}

void loop() {
    float tempC = tempSensor.readTemperature();
    Serial.print("Temperature (°C): ");
    Serial.println(tempC);

    delay(1000);
}
