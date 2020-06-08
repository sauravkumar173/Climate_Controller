#include "radio_comm.hpp"

RF24 radio(9, 10); // CE, CSN
const byte addresses[][6] = {ESP8266_WRITE_PIPE, ESP8266_READ_PIPE};

/*
 * @brief: Initialises radio communication
 * @input: void
 * @return: void
 */
void init_radio_communication(void) {

    radio.begin();
    radio.openWritingPipe(addresses[0]); // 00002
    radio.openReadingPipe(1, addresses[1]); // 00001
    radio.setPALevel(RF24_PA_MIN);
}

/*
 * @brief: Waits for RF request from ESP board 
 * @input: char* recBuff - Buffer to store received packet
 * @return: rfStatus Success - RF transmission was successfully received
 *          rfStatus Fail - No Transmission was received   
 */
enum rfStatus receive_from_rf(char* recBuff) {
    char temp[32];
    radio.startListening();

    if(radio.available()) {
            
        radio.read(&temp, sizeof(temp));
        Serial.print("RECEIVED ");
        Serial.println(temp);

        delay(5);
        radio.stopListening();
        
        memcpy(recBuff, temp, 32);
        
        return RF_SUCCESS;

    }

    delay(5);
    radio.stopListening();
    return RF_FAIL;

}


/*
 * @brief: Sends packet to ESP
 * @input: char* sendBuff - Buffer being sent
 * @return: rfStatus Success - RF transmission was successfully Sent
 *          rfStatus Fail - Error occured during transmission
 */
enum rfStatus send_to_rf(char* sendBuff) {

    char temp[32];
    memcpy(temp, sendBuff, 32);

    if(radio.write(&temp, sizeof(temp))) {

        return RF_SUCCESS;

    } else {

        return RF_FAIL;

    }

}
