#include <Arduino.h>

#include <string.h>
#include <radio_comm.hpp>
#include <temperature_sensor.hpp>

// Defines for all states the device can enter
#define STATE_LISTEN      0
#define STATE_READ_SENSOR 1
#define STATE_SEND_PACKET 2
#define STATE_IDLE        3

// Global variable for the state of the machine
int machineState;
// Global variable for ambient temperature
int tempSensorData;

void setup() {
  // Initialises Serial baudrate
  Serial.begin(115200);
  // Turns on on-board LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  // Initialises RF Transceiver
  init_radio_communication();
  // Sets device to listen state
  machineState = STATE_LISTEN;

}
     
void loop() {

  switch(machineState) {
    // Listens for request packet from ESP
    case STATE_LISTEN:

      char recText[32];
      // Recieves packet
      if(receive_from_rf(recText) == RF_SUCCESS) {
        
        Serial.print("Received: ");
        Serial.println(recText);
        // Decodes HCI packet and sets state to read from sensor

        if(strcmp(recText, "\xAA\x01\01") == 0) {

          machineState = STATE_READ_SENSOR;

        }

      }

      break;

    case STATE_READ_SENSOR:
      // Reads temperature sensor data and sets to send state
      tempSensorData = get_temperature();

      machineState = STATE_SEND_PACKET;

      break;

    case STATE_SEND_PACKET:
      // Creates HCI packet with temperature
      // With 0x02 denoting a response packet      
      char sendText[30];
      sprintf(sendText, "\xAA\x02\x01%x", get_temperature());
      // Sends packet to Uno
      Serial.print("SENDING ");  
      Serial.println(sendText);

      send_to_rf(sendText);
      // Enters listening mode again
      machineState = STATE_LISTEN;

      break;

    default:

      machineState = STATE_LISTEN;
      break;

  }
    
}
