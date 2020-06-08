#include "wifi_comm.hpp"


WiFiServer server(80);
// Variable to store the HTTP request
String header;
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds
const long timeoutTime = 2000;

/*
 * @brief: Initialises WIFI communication on ESP
 * @input: void
 * @return: void
 */
void init_wifi_comm() {

    // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    Serial.print(WIFI_SSID);
    
    // Start Connection
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    // Print local IP address and start web server
    Serial.println("");
    Serial.println("Connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // Starts local server on ESP8266
    server.begin();
}

/*
 * @brief: Allows server to connect to ESP and receives requests
 * @input: int* machineState - Pointer to state of the device
 *         int temperature - ambient temperature
 * @return: void
 */
void get_server_request(int* machineState, int temperature) {

    WiFiClient client = server.available();
    // Checks client connection from ruby server
    if (client) {
        // Reveals new client connection
        Serial.println("New Client.");

        String currentLine = "";               
        currentTime = millis();
        previousTime = currentTime;

        // Loop checks if client is connected and the timout time hasnt expired
        while (client.connected() && currentTime - previousTime <= timeoutTime) { 
        
            currentTime = millis();        
            
            if (client.available()) {      
                // Reads data sent from client and stores in header variable
                char c = client.read();          
                Serial.write(c);                    
                header += c;
                if (c == '\n') {                

                    // Sends client connection info
                    if (currentLine.length() == 0) {

                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/json");
                        client.println("Connection: close");
                        client.println();

                        // Detects Get request for machine data
                        if(header.indexOf("GET /fan/up") >= 0) {

                            // Creates JSON string based on machine state and accelerometer data
                            Serial.println("Sending data");
                            char jsonResponse[100];
                            // Sends JSON data to ruby server
                            pan_motor_right();
                            int fanPos = get_motor_position();
                            sprintf(jsonResponse, "{\"fanPosition\": \"%d\"}", fanPos);
                            Serial.println(jsonResponse);
                            client.print(jsonResponse);

                        } else if(header.indexOf("GET /fan/down") >= 0) {

                            // Creates JSON string based on machine state and accelerometer data
                            Serial.println("Sending data");
                            char jsonResponse[100];
                            // Sends JSON data to ruby server
                            pan_motor_left();
                            int fanPos = get_motor_position();
                            sprintf(jsonResponse, "{\"fanPosition\": \"%d\"}", fanPos);
                            Serial.println(jsonResponse);
                            client.print(jsonResponse);

                        } else if(header.indexOf("GET /get_data") >= 0) {

                            // Creates JSON string based on machine state and accelerometer data
                            Serial.println("Sending data");
                            char jsonResponse[100];
                            int fanPos = get_motor_position();
                            // Sends JSON data to ruby server
                            sprintf(jsonResponse, "{\"lastMeasuredTemperature\": \"%d\", \"fanPosition\": \"%d\"}", temperature, fanPos);
                            Serial.println(jsonResponse);
                            client.print(jsonResponse);

                        } else if(header.indexOf("GET /update") >= 0) {
                            // Creates JSON string based on machine state and accelerometer data
                            Serial.println("Sending data");
                            char jsonResponse[100];
                            // Sends JSON data to ruby server
                            sprintf(jsonResponse, "{\"updateStatus\": \"success\"}");
                            Serial.println(jsonResponse);
                            client.print(jsonResponse);
                            
                            *machineState = STATE_SEND_RESQUEST;
                        } 
                        
                    } else {

                        currentLine = "";
                    }
                } else if (c != '\r') {
                    
                    currentLine += c;    
                }
                
            }  
        }

        header = "";
        // Close the connection
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
    }
}

/*
 * @brief: Sends POST request to ruby server to create log messges
 * @input: String logMessage - Message to be logged
 *         int temperature - Ambient temperature to be logged
 *         int fanPosition - Position of the fan for log message
 * @return: void
 */
void send_climate_data(String logMessage, int temperature, int fanPosition) {

    HTTPClient http;
    
    // Begins HTTP connection to the ruby server
    http.begin(SERVER_IP); 
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Creates POST request string with the custom content attached
    String postData = "climate[log_message]=" + logMessage + "&climate[temperature]=" + temperature +
    "&climate[fan_position]=" + fanPosition;

    // Sends POST request to RUBY server
    int httpCode = http.POST(postData);
    Serial.println(httpCode);
    http.end();

}