#include <Arduino.h>

#include "esp_camera.h"
#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems
#include "driver/rtc_io.h"

#include <WiFi.h>

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include "Fullness.h"

// create a `config.h` file based off of `template-config.h`
#include "config.h"

void setup() {
  if (debug) Serial.begin(115200);

  // ---- Adafruit MQTT ---- 
  AdafruitIO_Feed *fullness_feed = io.feed(FEEDNAME);

  if (debug)  Serial.print("Connecting to Adafruit IO");
  io.connect();

  while(io.status() < AIO_CONNECTED) {
     if (debug) Serial.print(".");
    delay(500);
  }

  if (debug) {
    Serial.println();
    Serial.println(io.statusText());
  }
  
  // ---- ultrasonic -----
  pinMode(ultrasonicTrigPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);

  // ---- telemetry variables ----
  int fullness;

  // ---- Read Fullness ----
  if (debug) Serial.println("\nReading fullness...");
  fullness = calculateFullness(ultrasonicTrigPin, ultrasonicEchoPin, binHeight, 0, binHeight, retries);
  if (debug) Serial.println(fullness);
  
  // TODO: Get Picture

  // ----- Send Telemetry -----
  io.run();
  fullness_feed->save(fullness);
  if (debug) Serial.println("Fullness Telemetry Sent");

  // TODO: Send Picture to MQTT

  // ---- deep sleep ----
  if (debug) Serial.println("Going to sleep now");
  delay(1000);
  if (debug) Serial.flush();
  esp_deep_sleep_start();
}

void loop() {

}