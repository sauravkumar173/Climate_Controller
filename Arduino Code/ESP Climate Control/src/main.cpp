#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#include <radio_comm.hpp>
#include <servo_control.hpp>
#include <wifi_comm.hpp>
#include <state_machine.hpp>

// Global variable for ambient temperature
int ambientTemp;
// Global variable for system ticks
int sysTick = 0;
// Global variable for the state of the machine
int machineState;

void setup() {
  // Initialises Serial baudrate
  Serial.begin(115200);
  // Initialises Peripherals and WIFI
  init_servo_motor();
  init_radio_communication();
  init_wifi_comm();
  // Gets time since device was powered
  sysTick = millis();
  // Sets default state for state machine
  // to wait for command from server
  machineState = STATE_RECEIVE_FROM_SERVER;

}


void loop() {

  char recText[32];
  // State machine is used to check device state
  // and to perform appropriate functions
  switch(machineState) {

    case STATE_RECEIVE_FROM_SERVER:
      // Checks if server has connected and waits
      // for request
      get_server_request(&machineState, ambientTemp);
      break;

    case STATE_SEND_RESQUEST:
      // Sends a request packet for temperature
      // to the UNO via RF communication

      // Timeout is used to ensure RF commands are not spammed
      if(millis() - sysTick >= 500) {

        sysTick = millis();
        // Packet is HCI formatted with 0xAA preamble 0x01
        // Denoting request packet and 0x01 denoting that 
        // Senor 1 (temp sensor) must be read
        char string[32] = {0xAA, 0x01, 0x01};
        // Sends read request to UNO for temperature
        if(send_to_rf(string) == RF_SUCCESS) {
          //UNO has received the request 
          Serial.println("SEND SUCCESS");
          
        } 
        else {
          //UNO has not received request
          Serial.println("SEND FAILED");   
        }
        // Machine is set to listening state
        machineState = STATE_LISTENING;

      }
      break;

    case STATE_LISTENING:
      // ESP now listens for response packet from UNO
      if(receive_from_rf(recText) == RF_SUCCESS) {

        sscanf(recText, "\xAA\x02\x01%x", &ambientTemp);
        Serial.println(ambientTemp);
        machineState = STATE_SENSOR_PROCESSING;

      } else {
        // If packet is not received the machine is set
        // to the send state to transmit another packet
        machineState = STATE_SEND_RESQUEST;
      }

      break;

    case STATE_SENSOR_PROCESSING:
      // State processes the sensor data and rotats motor accordingly
      if(ambientTemp > 24) {
        // Fan gets turned up if temperature is too high
        pan_motor_right();

      } else if (ambientTemp < 24) {
        // Fan gets turned down if temperature is too low
        pan_motor_left();
      
      }
      // Machine is set to the log state to send logging message to server
      machineState = STATE_SEND_SERVER_LOG;

      break;

    case STATE_SEND_SERVER_LOG:
      // Log message is sent to server with motor position
      send_climate_data("Successful update", ambientTemp, get_motor_position());
      machineState = STATE_RECEIVE_FROM_SERVER;
      break;

    case STATE_SEND_ERROR_LOG:
      // An error message is logged if rotation was not successful
      send_climate_data("ERROR: Unsuccessful update", ambientTemp, get_motor_position());
      machineState = STATE_RECEIVE_FROM_SERVER;
      break;

    default:
      break;

  }   

  delay(5);
}

