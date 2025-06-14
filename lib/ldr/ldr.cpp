#include "ldr.h"

LDR::LDR(uint8_t pin, uint8_t threshold, float reference) {
  _pin = pin;
  _threshold = threshold;
  _reference = reference;
}

int LDR::readRaw() {
  return analogRead(_pin) ;
}

float LDR::readVoltage() {
  return (readRaw() / 1023.0) * _reference;
}

bool LDR::isBright() {
  return readRaw() > _threshold;
}
