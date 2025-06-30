#include <EEPROM.h>
#include <gravity_tds.h>
#include "config.h"

GravityTDS gravityTds;

float temperature = 25,tdsValue = 0;

void setup()
{
    Serial.begin(115200);
    gravityTds.setPin(TDS_SENSOR_PIN);
    gravityTds.setAref(3.3); 
    gravityTds.setAdcRange(4096);  
    gravityTds.begin(); 
}

void loop()
{
    temperature = readTemperature();
    gravityTds.setTemperature(temperature);  
    gravityTds.update(); 
    tdsValue = gravityTds.getTdsValue(); 
    Serial.print(tdsValue,0);
    Serial.println("ppm");
    delay(1000);
}
