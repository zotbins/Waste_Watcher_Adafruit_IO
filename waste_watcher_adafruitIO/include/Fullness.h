#ifndef FULLNESS_H
#define FULLNESS_H

float distanceRead(
  int ultrasonicTrigPin = 13,
  int ultrasonicEchoPin = 12
);

int calculateFullness(
  int ultrasonicTrigPin = 13,
  int ultrasonicEchoPin = 12,
  int binHeight = 50, 
  int minValue = 0,
  int maxValue = 50,
  int retries = 5
);


#endif