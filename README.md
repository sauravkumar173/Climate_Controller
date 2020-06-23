# Climate Controller IOT Project
This repository contains all the files for the Climate Controller project which automatically controls and adjusts the ceiling fan to maintain Room Temperature. 

The specifics of which can
be viewed here: https://medium.com/@sauravkumar173/creating-a-iot-bedroom-climate-controller-with-esp8266-ruby-on-rails-and-arduino-uno-18a6857e2c22


## Installation

This project uses Ruby on Rails and an Wemos D1 Mini board with ESP8266 and an Arduino UNO . This means that a Linux machine of WSL environment will be needed to host the server, and an PlatformIO is necessary to flash the board.

1. Flash PlatformIO project files onto the ESP8266 Board in "Climate_Controller/Arduino Code/ESP Climate Control/"
2. Flash PlatformIO project files onto the Arduino UNO Board in "Climate_Controller/Arduino Code/Uno Climate Control/"
3. Open the Rails project from "Climate\_Controller/Ruby Rails/climate\_logger/"
4. Run the server with "rails -s -b 0.0.0.0"
5. If the ESP8266 cannot connect to the Rails server, ensure the IP address, SSID and Password is correct to your setup
6. Ensure the RF Transceiver and Temperature Sensor are wired correctly
7. 3D print the mounting brackets for the servo motor

## Usage
Attach the ESP8266 board onto the ceiling fan knob with the mounting bracket. The Arduino board can be placed anywhere in the room which represents the average temperature of the room.

On the local host IP, a HTML view will appear. The fan can be turned up and down with the control panel on the website. After 2 mins the fan position will automatically be adjusted based on the temperature of the room to maintain 23 degrees. Anytime the fan changes position a log will be created with a timestamp of the event. Furthermore, the web page will display the latest temperature and fan position.


## Authors
Saurav Kumar

