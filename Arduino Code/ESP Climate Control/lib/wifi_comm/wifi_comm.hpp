#ifndef WIFI_COMM_H
#define WIFI_COMM_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include "servo_control.hpp"
#include "state_machine.hpp"

// URL, SSID and password for WIFI network and server
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "Password"
#define SERVER_IP "http://192.168.20.21:3000/climates"


void init_wifi_comm(void);
void get_server_request(int* machineState, int temperature);
void send_climate_data(String logMessage, int temperature, int fanPosition);
#endif