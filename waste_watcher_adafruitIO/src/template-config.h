// Use this as a template to create your own "config.h" file. 
// "config.h" will remain  untracked by the ".gitignore" file to avoid
// accidentally tracking any sensitive information.

#ifndef CONFIG
#define CONFIG

// WiFi
#define WIFI_SSID     "<YOUR_WIFI_ID_HERE>"
#define WIFI_PASS     "<YOUR_WIFI_PASSWORD_HERE>"

// Adafruit MQTT
// ------------
// 1. Create an Adafruit IO account here https://io.adafruit.com/
// 2. Get your account username and key
// 3. Create a feed. Refer to https://learn.adafruit.com/adafruit-io-basics-feeds
#include "AdafruitIO_WiFi.h"
#define IO_USERNAME   "<YOUR_ADAFRUIT_IO_USERNAME_HERE>"
#define IO_KEY        "<YOUR_ADAFRUIT_IO_KEY_HERE>"
#define FEEDNAME      "<YOUR_ADAFRUIT_IO_FEEDNAME>"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);


// ultrasonic sensor pins
const int ultrasonicTrigPin = 13;
const int ultrasonicEchoPin = 12;

// deep sleep
#define uS_TO_S_FACTOR 1000000 //conversion factor for usec to sec
#define TIME_TO_SLEEP 1800   // TIME ESP32 will sleep for 1800 sec

// system variables
bool debug = true; // set false, if not debugging
const int binHeight = 50; // units: cm, used to calculate fullness
const int retries = 5; // # of retries for collecting fullness

#endif
