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
