#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <Arduino.h>
#include <math.h>

// Pin connected to temperature sensor
#define TEMP_SENSOR_PIN 0

uint8_t read_temperature(int RawADC);
uint8_t get_temperature();
#endif