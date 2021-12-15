#include "Image.h"

#include "esp_camera.h"
#include "driver/rtc_io.h"
#include <base64.h>

// configure the ESP32 cam. A lot of these parameters are hard-coded
// you can change these configurations as you see fit to your specifications.
void configInitCamera(){
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_SVGA; //800 x 600 necessary for Adafruit IO
  config.jpeg_quality = 30;
  config.fb_count = 1;

  // Initialize the Camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    #ifndef NDEBUG
    Serial.printf("Camera init failed with error 0x%x", err);
    #endif
    return;
  }
}

// Use the ESP32 Cam to take a photo. The output will be a base64 
// string that can be sent to AdafruitIO using MQTT.
String takePhoto() {
  // function parameters
  String getAll;
  String getBody;

  // turn on flash
  rtc_gpio_hold_dis(GPIO_NUM_4);
  digitalWrite(FLASH,HIGH);

  // take the photo and store in frame buffer (fb)
  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();

  // start if camera capture fails 
  if(!fb) {
    #ifndef NDEBUG
    Serial.println("Camera capture failed");
    #endif
    delay(1000);
    ESP.restart();
  }

  // turn off flash
  digitalWrite(FLASH,LOW);
  rtc_gpio_hold_en(GPIO_NUM_4);

  String encodedBuffer = base64::encode((uint8_t *)fb->buf, fb->len);
  
  return encodedBuffer;
}