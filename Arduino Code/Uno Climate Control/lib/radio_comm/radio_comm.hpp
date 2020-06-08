#ifndef RADIO_COMM_H
#define RAFIO_COMM_H

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define ESP8266_WRITE_PIPE "00002"
#define ESP8266_READ_PIPE "00001"


enum rfStatus {
    RF_SUCCESS,
    RF_FAIL
};

void init_radio_communication(void);
enum rfStatus receive_from_rf(char* recBuff);
enum rfStatus send_to_rf(char* sendBuff);

#endif