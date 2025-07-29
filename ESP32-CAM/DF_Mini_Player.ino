#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySerial(16, 17); // RX (GPIO 15), TX (GPIO 14)
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);

  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("DFPlayer Mini initialization failed");
    while (true); // Halt the program if initialization fails
  }

  myDFPlayer.volume(20); // Set volume level (0 to 30)
  Serial.println("DFPlayer Mini ready! Type 'play' to play audio.");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();  // Remove any trailing newline characters

    if (command == "play") {
      Serial.println("Playing audio...");
      myDFPlayer.play(1); // Play the first audio file on the SD card (001.mp3)
    } else {
      Serial.println("Unknown command. Type 'play' to play audio.");
    }
  }
}
