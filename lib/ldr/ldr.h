#ifndef LDR_H
#define LDR_H

#include <Arduino.h>

class LDR {
  public:
    LDR(uint8_t pin, uint8_t threshold, float reference);
    int readRaw();
    float readVoltage();
    bool isBright();

  private:
    uint8_t _pin;
    uint8_t _threshold;
    uint8_t _reference;
};

#endif
