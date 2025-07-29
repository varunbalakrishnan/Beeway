#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "esp_camera.h"
#include "camera_pins.h"

// -------- Replace with your credentials --------
#define WIFI_SSID "YOUR_SSID"              // Replace with your WiFi SSID
#define WIFI_PASSWORD "YOUR_PASSWORD"      // Replace with your WiFi Password
#define BOT_TOKEN "XXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" // Telegram BOT Token
#define CHAT_ID "YOUR_CHAT_ID"            // Replace with your chat ID
// -----------------------------------------------

#define FLASH_LED_PIN 4
#define CAMERA_MODEL_AI_THINKER           // Camera model
const unsigned long BOT_MTBS = 1000;      // Mean time between bot scans
unsigned long bot_lasttime = 0;

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

camera_fb_t *fb = NULL;                   // Camera buffer
bool flashState = LOW;                    // Flash state control
bool dataAvailable = false;               // Used for binary transfer of the image

bool isMoreDataAvailable();
byte *getNextBuffer();
int getNextBufferLen();

void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    if (text == "/flash") {
      flashState = !flashState;
      digitalWrite(FLASH_LED_PIN, flashState);
      bot.sendMessage(chat_id, "Flash toggled!", "");
    }

    if (text == "/photo") {
      fb = esp_camera_fb_get();           // Take picture
      if (!fb) {
        bot.sendMessage(chat_id, "Camera capture failed", "");
        return;
      }
      dataAvailable = true;
      bot.sendPhotoByBinary(chat_id, "image/jpeg", fb->len, isMoreDataAvailable, nullptr, getNextBuffer, getNextBufferLen);
      esp_camera_fb_return(fb);
    }

    if (text == "/start") {
      bot.sendMessage(chat_id, "Welcome to ESP32-CAM Bot!\nCommands:\n/photo - Take a photo\n/flash - Toggle Flash LED", "");
    }
  }
}

bool isMoreDataAvailable() {
  if (dataAvailable) {
    dataAvailable = false;
    return true;
  }
  return false;
}

byte *getNextBuffer() {
  return fb ? fb->buf : nullptr;
}

int getNextBufferLen() {
  return fb ? fb->len : 0;
}

void setup() {
  Serial.begin(115200);
  pinMode(FLASH_LED_PIN, OUTPUT);
  digitalWrite(FLASH_LED_PIN, flashState);

  if (!setupCamera()) {
    Serial.println("Camera Setup Failed!");
    while (true) delay(100);
  }

  Serial.print("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi connected. IP Address: " + WiFi.localIP().toString());

  configTime(0, 0, "pool.ntp.org");       // Synchronize time for secure connection
  while (time(nullptr) < 24 * 3600) delay(100);

  bot.sendMessage(CHAT_ID, "ESP32-CAM Telegram Bot started!", "");
}

void loop() {
  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();
  }
}
