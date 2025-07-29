#include <WiFi.h>
#include <esp_now.h>
#include "esp_camera.h"

// Wi-Fi credentials
const char* ssid = "wifitest";
const char* password = "wifitest";

// Receiver's MAC address (replace with your receiver ESP32's MAC address)
uint8_t receiverMac[] = {0x24, 0x6F, 0x28, 0xB9, 0x4F, 0x58}; // Replace with the receiver ESP32's MAC address

// PIR sensor pin
#define PIR_PIN 13

// Camera settings (adjust based on your ESP32-CAM model)
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

// Initialize ESP-NOW
void initESPNow() {
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverMac, 6);
  peerInfo.channel = 0;  // Use current channel
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
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

  // Initialize PIR sensor
  pinMode(PIR_PIN, INPUT);

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
  initESPNow();
}

void loop() {
  // Check PIR sensor for motion
  int pirState = digitalRead(PIR_PIN);

  if (pirState == HIGH) {
    Serial.println("Motion detected! Capturing image...");

    // Capture image
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed");
      return;
    }

    // Send image over ESP-NOW
    esp_err_t result = esp_now_send(receiverMac, fb->buf, fb->len);
    if (result == ESP_OK) {
      Serial.println("Image sent successfully");
    } else {
      Serial.println("Error sending image");
    }

    // Release frame buffer
    esp_camera_fb_return(fb);

    delay(5000);  // Delay between sending images
  } else {
    Serial.println("No motion detected.");
  }

  delay(500);  // Small delay to avoid unnecessary polling
}