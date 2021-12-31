#include "Fullness.h"
#include <Arduino.h>

// Read the distance measurement from the ultrasonic sensor.
// This distance is used to calculate the bin fullness w/ the 
// equation "fullness = binHeight - fullness"
float distanceRead(int ultrasonicTrigPin, int ultrasonicEchoPin) {
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

// Depends on: "distanceRead" function.
// Gets the distance reading from the ultrasonic sensor 
// and returns the fullness values using the equation
// "fullness = binHeight - fullness"
int calculateFullness(int ultrasonicTrigPin, int ultrasonicEchoPin, int binHeight, int minValue, int maxValue, int retries) {
    int distance;

    for (int i=0; i<retries; i++) {
      distance = (int)distanceRead(ultrasonicTrigPin, ultrasonicEchoPin);

      // Filter out of range values
      if (distance<=minValue || distance>maxValue) {
        distance = -1;
      }
      else {
        return binHeight - distance;
      }
    }

    return -1;
  
}
