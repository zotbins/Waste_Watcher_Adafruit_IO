#include <Arduino.h>

#include "esp_camera.h"
#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems
#include "driver/rtc_io.h"

// create a `config.h` file based off of `template-config.h`
#include "config.h"

// Read the distance measurement from the ultrasonic sensor.
// This distance is used to calculate the bin fullness w/ the 
// equation "fullness = binHeight - fullness"
float distanceRead(
  int ultrasonicTrigPin = 13,
  int ultrasonicEchoPin = 12
) {
  // === collect ultrasonic readings ===
  long duration; // units: microseconds, for HC-SR04
  float distance; // units:cm, for HC-SR04

  // clear trigger pin
  digitalWrite(ultrasonicTrigPin, LOW);

  // Toggle trigPin HIGH then LOW
  digitalWrite(ultrasonicTrigPin, HIGH);
  delayMicroseconds(10); //units: us
  digitalWrite(ultrasonicTrigPin, LOW);

  // Reads echoPin and returns sound wave travel time
  duration = pulseIn(ultrasonicEchoPin, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}

int calculateFullness(
  int ultrasonicTrigPin = 13,
  int ultrasonicEchoPin = 12,
  int binHeight = 50, 
  int minValue = 0,
  int maxValue = 50,
  int retries = 5
) {
    int distance;

    for (int i=0; i<retries; i++) {
      distance = (int)distanceRead(ultrasonicTrigPin, ultrasonicEchoPin);
      if (debug) {
        Serial.print("Raw Distance: ");
        Serial.println(distance);
      }

      // Filter out of range values
      if (distance<minValue || distance>maxValue) {
        distance = -1;
      }
      else {
        return binHeight - distance;
      }
    }

    return -1;
  
}

void setup() {
  if (debug) Serial.begin(115200);
  
  // ultrasonic
  pinMode(ultrasonicTrigPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);

  // telemetry variables
  int fullness;

  // TODO: Read Fullness
  if (debug) Serial.println("\nReading fullness...");
  fullness = calculateFullness(ultrasonicTrigPin, ultrasonicEchoPin, binHeight, 0, binHeight, retries);
  if (debug) Serial.println(fullness);
  // TODO: Get Picture

  // TODO: Send Fullness Telemetry

  // TODO: Send Picture to MQTT

  // deep sleep
  if (debug) Serial.println("Going to sleep now");
  delay(1000);
  if (debug) Serial.flush();
  esp_deep_sleep_start();
}

void loop() {

}