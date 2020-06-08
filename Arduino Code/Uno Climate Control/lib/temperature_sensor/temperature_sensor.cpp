#include "temperature_sensor.hpp"


uint8_t read_temperature(int pin_ADC) {

  double temperature;
  // Obtains temperture from analogue pin
  temperature = log(((10240000/pin_ADC) - 10000));
  temperature = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temperature * temperature ))* temperature );
  // Convert Kelvin to Celcius
  temperature = temperature - 273.15; 
  // Returns temperature as 8 bit number
  return (uint8_t) temperature;

}

uint8_t get_temperature() {
    // Returns temperature after reading analogue pin
    return read_temperature(analogRead(TEMP_SENSOR_PIN));
}