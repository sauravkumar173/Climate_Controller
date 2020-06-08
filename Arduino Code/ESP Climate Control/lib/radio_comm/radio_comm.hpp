#ifndef RADIO_COMM_H
#define RAFIO_COMM_H

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// RF read and write pipe addresses for
// Bidirectional communication
#define RF_CE_PIN 2
#define RF_CSN_PIN 15
#define ESP8266_WRITE_PIPE "00001"
#define ESP8266_READ_PIPE "00002"

// Enum denoting if RF transmission was successful or not
enum rfStatus {
    RF_SUCCESS,
    RF_FAIL
};

void init_radio_communication(void);
enum rfStatus receive_from_rf(char* recBuff);
enum rfStatus send_to_rf(char* sendBuff);

#endif