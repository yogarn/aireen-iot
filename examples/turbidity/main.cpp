#include "Arduino.h"
#include "turbidty.h"
#include "config.h"

TurbiditySensor turbSensor(TURBIDITY_PIN);

void setup() {
    Serial.begin(9600);
    turbSensor.begin();
}

void loop() {
    float ntu = turbSensor.readNTU();
    Serial.print("Turbidity (NTU): ");
    Serial.println(ntu);

    delay(1000);
}
