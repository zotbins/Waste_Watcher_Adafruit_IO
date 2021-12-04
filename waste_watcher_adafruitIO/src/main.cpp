#include <Arduino.h>

#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems

#include <WiFi.h>

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include <base64.h>
#include "Fullness.h"
#include "Image.h"

// create a `config.h` file based off of `template-config.h`
#include "config.h"

// Adafruit IO 
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
bool debug = true;

void setup() {
  if (debug) Serial.begin(115200);

  // ---- Adafruit MQTT ---- 
  AdafruitIO_Feed *fullnessFeed = io.feed(FULLNESS_FEEDNAME);
  AdafruitIO_Feed *imageFeed = io.feed(IMAGE_FEEDNAME);

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
  
  // ---- set pins -----
  pinMode(ultrasonicTrigPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);
  pinMode(flashLED, OUTPUT);

  // ---- telemetry variables ----
  int fullness;
  String base64Image; //base-64 encoded string to represent a JPG image

  // ---- Read Fullness ----
  if (debug) Serial.println("\nReading fullness...");
  fullness = calculateFullness(ultrasonicTrigPin, ultrasonicEchoPin, binHeight, 0, binHeight, retries);
  if (debug) Serial.println(fullness);
  
  // ---- Get Picture ----
  if (debug) Serial.println("\nCapturing image...");
  configInitCamera(debug);
  base64Image = takePhoto(debug);
  if (debug) Serial.println("Image captured.");

  // ----- Send Telemetry -----
  io.run();
  bool isFullnessSaved = fullnessFeed->save(fullness);
  if (debug && isFullnessSaved) Serial.println("Fullness Telemetry Sent");

  // --- Send Picture to MQTT ----
  bool isImageSaved = imageFeed->save(base64Image);

  if (debug && isImageSaved) Serial.println("Image Telemetry Sent");

  // ---- deep sleep ----
  if (debug) Serial.println("Going to sleep now");
  delay(1000);
  if (debug) Serial.flush();
  esp_deep_sleep_start();
}

void loop() {

}