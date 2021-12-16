#include <Arduino.h>

#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems

#include <WiFi.h>
#include <PubSubClient.h>

#include <base64.h>
#include "Fullness.h"
#include "Image.h"

// create a `config.h` file based off of `template-config.h`
#ifdef CI
#include "ci-config.h"
#else
#include "config.h"
#endif

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect();
void setup_wifi();

void setup_wifi()
{
  delay(10);
  // We start by connecting to a WiFi network
  #ifndef NDEBUG
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  #endif

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);

    #ifndef NDEBUG
    Serial.print(".");
    #endif
  }

  #ifndef NDEBUG
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  #endif
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected())
  {
    #ifndef NDEBUG
    Serial.print("Attempting MQTT connection...");
    #endif

    // Attempt to connect
    if (client.connect(mqttClientID, mqttUsername, mqttPassword))
    {
      #ifndef NDEBUG
      Serial.println("connected");
      #endif
    }
    else
    {
      #ifndef NDEBUG
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      #endif
      
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  #ifndef NDEBUG
  Serial.begin(115200);
  #endif

  setup_wifi();
  client.setServer(mqttServer, 1883);
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // ---- set pins -----
  pinMode(ultrasonicTrigPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);
  pinMode(FLASH, OUTPUT);

  // ---- telemetry variables ----
  int fullness;
  String base64Image; //base-64 encoded string to represent a JPG image

  // ---- Read Fullness ----
  fullness = calculateFullness(ultrasonicTrigPin, ultrasonicEchoPin, binHeight, 0, binHeight, retries);
  
  // ---- Get Picture ----
  configInitCamera();
  base64Image = takePhoto();

  #ifndef NDEBUG
  Serial.print("\nFullness: ");
  Serial.println(fullness);
  Serial.println("Image captured.");
  #endif
  
  // ----- Send Fullness Telemetry -----
  char payload[32] = {0};
  snprintf(payload, sizeof(payload), "%d", fullness);
  bool fullnesSent = client.publish(mqttFullnessTopic, payload);

  // --- Send Picture to MQTT ----
  bool imageSent = client.publish(mqttImageTopic, base64Image.c_str());

  // ---- deep sleep ----
  #ifndef NDEBUG
  if (fullnesSent) Serial.println("Fullness Telemetry Sent");
  if (imageSent) Serial.println("Image Telemetry Sent");
  Serial.println("Going to sleep now");
  delay(1000);
  Serial.flush();
  #endif

  esp_deep_sleep_start();
}

void loop() {

}