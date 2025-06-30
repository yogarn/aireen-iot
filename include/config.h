#pragma once

// pin map
#define LDR_PIN A0
#define TEMP_SENSOR_PIN 2
#define TURBIDITY_PIN A1
#define PHMETER_PIN A0
#define TDS_PIN A1

// hardware constants
#define TDS_AREF 3.3  // reference voltage on ADC, default 3.3V on ESP32
#define TDS_ADC_RANGE 4096  // 4096 for 12-bit ADC
#define LDR_REFERENCE 5.0

// environmental constants
#define TDS_TEMPERATURE 25  // default temperature for TDS calculations
#define LDR_THRESHOLD 5
