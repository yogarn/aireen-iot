#include "ph_meter.h"
#include "config.h"

PHMeter phSensor(PHMETER_PIN);

void setup() {
    Serial.begin(9600);
    phSensor.begin();
}

void loop() {
    float phValue = phSensor.readPH();
    Serial.print("pH: ");
    Serial.println(phValue);
    delay(1000);
}
