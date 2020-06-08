#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <Arduino.h>

// Definition of all states used in state machine
// Used to allow state modification in peripheral files
#define STATE_RECEIVE_FROM_SERVER 0
#define STATE_SEND_RESQUEST 1
#define STATE_LISTENING 2
#define STATE_SENSOR_PROCESSING 3
#define STATE_SEND_SERVER_LOG 4
#define STATE_SEND_ERROR_LOG 5
#define STATE_SKIP_RF_COMM 30

#endif