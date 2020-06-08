#include "radio_comm.hpp"

// CE and CSN pins on RF board
RF24 radio(RF_CE_PIN, RF_CSN_PIN); 
const byte addresses[][6] = {ESP8266_WRITE_PIPE, ESP8266_READ_PIPE};
int sysTickRadio;

/*
 * @brief: Initialises radio communication
 * @input: void
 * @return: void
 */
void init_radio_communication(void) {
    // Begins radio and sets read and write pipes
    radio.begin();
    radio.openWritingPipe(addresses[0]); // 00001
    radio.openReadingPipe(1, addresses[1]); // 00002
    radio.setPALevel(RF24_PA_MIN);
    // Sets milliseconds since start
    sysTickRadio = millis();
}

/*
 * @brief: Waits for RF response from UNO board 
 * @input: char* recBuff - Buffer to store received packet
 * @return: rfStatus Success - RF transmission was successfully received
 *          rfStatus Fail - No Transmission was received   
 */
enum rfStatus receive_from_rf(char* recBuff) {
    char temp[32];

    delay(5);
    radio.startListening();

    sysTickRadio = millis();
    // Timeout throws error if message more received in time
    while(millis() - sysTickRadio < 1000) {

        if(radio.available()) {
            // Reads the received packet and stores in packet
            radio.read(&temp, sizeof(temp));
            Serial.print("RECEIVED ");
            Serial.println(temp);

            delay(5);
            radio.stopListening();
            memcpy(recBuff, temp, 32);
            return RF_SUCCESS;
            

        }
        
    }
    
    Serial.println("TIMEOUT");
    delay(5);
    // Turns of listening and returns a fail
    radio.stopListening();
    return RF_FAIL;

}

/*
 * @brief: Sends packet to UNO
 * @input: char* sendBuff - Buffer being sent
 * @return: rfStatus Success - RF transmission was successfully Sent
 *          rfStatus Fail - Error occured during transmission
 */
enum rfStatus send_to_rf(char* sendBuff) {

    char temp[32];
    memcpy(temp, sendBuff, 32);

    radio.stopListening();
    // Write buffer to RF stream
    if(radio.write(&temp, sizeof(temp))) {

        delay(5);
        return RF_SUCCESS;

    } else {

        delay(5);
        return RF_FAIL;

    }

}