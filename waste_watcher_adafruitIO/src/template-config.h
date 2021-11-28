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

// ultrasonic sensor pins
const int ultrasonicTrigPin = 13;
const int ultrasonicEchoPin = 12;

// deep sleep
#define uS_TO_S_FACTOR 1000000 //conversion factor for usec to sec
#define TIME_TO_SLEEP 1800   // TIME ESP32 will sleep for 1800 sec

// system variables
const int binHeight = 50; // units: cm, used to calculate fullness
const int retries = 5; // # of retries for collecting fullness

// camera 
// === camera pin definitions ===
const int flashLED = 4;

//CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22


#endif
