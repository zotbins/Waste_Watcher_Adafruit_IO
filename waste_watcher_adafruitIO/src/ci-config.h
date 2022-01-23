// Use this as a template to create your own "config.h" file.
// "config.h" will remain  untracked by the ".gitignore" file to avoid
// accidentally tracking any sensitive information.
#ifndef CONFIG_H
#define CONFIG_H

// ultrasonic sensor pins
const int ultrasonicTrigPin = 13;
const int ultrasonicEchoPin = 12;

// camera settings
bool flashOn = true;

// deep sleep
#define uS_TO_S_FACTOR 1000000 //conversion factor for usec to sec
#define TIME_TO_SLEEP 1800   // TIME ESP32 will sleep for 1800 sec

// system variables
const int binHeight = 50; // units: cm, used to calculate fullness
const int retries = 5; // # of retries for collecting fullness

// Replace the next variables with your SSID/Password combination
const char *ssid = "dummy";
const char *password = "dummy";

// Add your MQTT Broker IP address
// --------------------------------------
// 1. Create an Adafruit IO account here https://io.adafruit.com/
// 2. Create a feed. Refer to https://learn.adafruit.com/adafruit-io-basics-feeds
// 3. Get your account username, key (password), and mqtt topic name
// 4. Create a unique id using a generator such as https://guidgenerator.com/
// 5. Replace the following lines with your information from the previous steps
const char *mqttServer = "io.adafruit.com"; //mqttServer
const char *mqttClientID = "dummy";
const char *mqttUsername = "dummy"; // Adafruit Username
const char *mqttPassword = "dummy"; // Adafruit AIO Key
const char *mqttFullnessTopic = "dummy";
const char *mqttImageTopic = "dummy";

#endif