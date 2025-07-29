#include <WiFi.h>
#include <esp_now.h>
#include "esp_camera.h"

// Wi-Fi credentials
const char* ssid = "wifitest";
const char* password = "wifitest";

// Initialize camera
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

// Function to handle received data
void onDataReceive(const uint8_t *mac, const uint8_t *data, int len) {
  Serial.println("Image received");

  // Save or process the received image data here
  // For example, you could store it in a file or process it for further use
}

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to Wi-Fi!");

  // Initialize the camera
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = 15;
  config.pin_d1 = 2;
  config.pin_d2 = 4;
  config.pin_d3 = 0;
  config.pin_d4 = 5;
  config.pin_d5 = 18;
  config.pin_d6 = 19;
  config.pin_d7 = 21;
  config.pin_xclk = 22;
  config.pin_pclk = 23;
  config.pin_vsync = 25;
  config.pin_href = 26;
  config.pin_sccb_sda = 27;
  config.pin_sccb_scl = 32;
  config.pin_reset = -1;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (esp_camera_init(&config) != ESP_OK) {
    Serial.println("Camera init failed");
    return;
  }

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the receive callback
  esp_now_register_recv_cb(onDataReceive);
}

void loop() {
  // Empty loop since we are handling the data reception via callback
  delay(1000);
}
