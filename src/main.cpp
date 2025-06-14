#include <Arduino.h>
#include <ldr.h>

#include "config/config.h"

LDR ldr(LDR_PIN, LDR_THRESHOLD, LDR_REFERENCE);

int ldrValue = 0;
int ldrVoltage = 0;
bool isLdrBright = false;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  ldrValue = ldr.readRaw();
  ldrVoltage = ldr.readVoltage();
  isLdrBright = ldr.isBright();

  Serial.print("LDR: ");
  Serial.print(ldrValue);
  Serial.print(" | V: ");
  Serial.print(ldrVoltage, 2);
  Serial.print(" | Bright: ");
  Serial.println(isLdrBright ? "Yes" : "No");

  delay(1000);
}
