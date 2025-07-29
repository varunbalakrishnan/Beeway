# **BeeWay: Elephant Detection and Forest Surveillance 🐘🌲**

## **Overview**
BeeWay is a cost-effective, AI-powered solution to mitigate human-elephant conflicts. By combining **ESP32-CAM** modules, motion sensors, and lightweight **AI models trained on Edge Impulse**, the system detects elephants in real time, triggers **bee sound deterrents**, and sends **Telegram alerts** using **ESP-NOW** communication. 

---

## **Features 🎯**
1. **Real-time Detection**: Elephant detection using a lightweight AI model on ESP32-CAM.  
2. **Non-lethal Deterrent**: Plays bee sounds via the DF Mini Player to scare elephants.  
3. **Instant Alerts**: Real-time notifications via Telegram with images and timestamps.  
4. **ESP-NOW Communication**: Low-latency data transfer between ESP32-CAM and ESP32.  
5. **Scalable and Cost-Effective**: Easy deployment in remote areas using low-cost hardware.
6. **Energy Efficient**: Optimized power consumption for long-term deployment.
7. **Weather Resistant**: Designed for outdoor operation in forest environments.

---

## **Workflow 🚀**

1. **Motion Detection**  
   - PIR motion sensor detects movement and triggers the ESP32-CAM.

2. **Elephant Detection**  
   - The ESP32-CAM captures an image and runs a custom **Edge Impulse AI model** to confirm if an elephant is detected.

3. **Communication via ESP-NOW**  
   - Detection data is sent to the ESP32 main board for further actions.

4. **Sound Deterrent**  
   - The **DF Mini Player** plays pre-recorded bee sounds to deter elephants.

5. **Real-time Alerts**  
   - The ESP32 main board triggers the **Telegram Bot**, sending an image and timestamp to authorized users.

---

## **Hardware Requirements 🛠️**

| Component               | Description                                       |
|-------------------------|---------------------------------------------------|
| **ESP32-CAM**           | Captures images and processes AI inference.       |
| **ESP32**               | Acts as the master board for notifications.       |
| **PIR Motion Sensor**   | Detects motion to trigger image capture.          |
| **DF Mini Player**      | Plays bee sounds to deter elephants.              |
| **SD Card**             | Local storage for detected images.                |
| **Power Supply**        | Battery pack or solar power for remote operation. |

---

## **Pin Configuration 🔌**

### **ESP32-CAM Pin Mapping** 🛜
| Component              | Pin Mapping                |
|------------------------|----------------------------|
| **PIR Sensor**         | GPIO 14                    |
| **DF Mini Player**     | RX: GPIO 16, TX: GPIO 17   |
| **SD Card**            | GPIOs 2, 4, 12, 13, 14, 15 |


### **ESP32 Main Board** 🛜
| Component              | Pin Mapping                                                            |
|------------------------|------------------------------------------------------------------------|
| **ESP-NOW**            | WiFi Channels (Auto Set / Individual WIFI network wth WPA 3 Security)  |
| **Telegram Trigger**   | Configurable and Will be Communicated with the ESP-NOW protocol        |

---

## **Software and Tools 🧑‍💻**

1. **Edge Impulse**  
   - Train and optimize AI models for elephant detection.  
   - Export the model as **TFLite for Microcontrollers** for deployment.

2. **Arduino IDE**  
   - Develop and upload code for ESP32 and ESP32-CAM boards.

3. **Telegram Bot API**  
   - Sends real-time notifications with images to authorized users.

4. **ESP-NOW Protocol**  
   - Low-latency wireless communication between ESP32 devices.

---
## **Necessary Arduino Packages 📦**

To ensure the **BeeWay** project works seamlessly on the **ESP32-CAM** and **ESP32**, install the following necessary Arduino packages:

1. **ESP32 Board Support**  
   - **Package**: **ESP32 by Espressif Systems**  
   - **Installation**:  
     - Go to **Arduino IDE** > **File** > **Preferences**.  
     - In the **Additional Boards Manager URLs** field, add:  
       ```
       https://dl.espressif.com/dl/package_esp32_index.json
       ```  
     - Go to **Tools** > **Boards** > **Boards Manager**, search for **ESP32**, and install it.

2. **Edge Impulse SDK for Arduino**  
   - **Package**: **Edge Impulse SDK**  
   - **Installation**:  
     - In the **Arduino IDE**, go to **Sketch** > **Include Library** > **Manage Libraries**.  
     - Search for **Edge Impulse** and install the **Edge Impulse Inference Library**.

3. **DFMiniMp3**  
   - **Package**: **DFMiniMp3**  
   - **Installation**:  
     - In the **Arduino IDE**, go to **Sketch** > **Include Library** > **Manage Libraries**.  
     - Search for **DFMiniMp3** and install it to control the **DF Mini Player**.

4. **UniversalTelegramBot**  
   - **Package**: **UniversalTelegramBot**  
   - **Installation**:  
     - In the **Arduino IDE**, go to **Sketch** > **Include Library** > **Manage Libraries**.  
     - Search for **UniversalTelegramBot** and install it to send Telegram alerts.

5. **WiFi Library**  
   - **Package**: **WiFi by Arduino** (for ESP32)  
   - **Installation**:  
     - This library is typically installed automatically with the ESP32 board package.  
     - If not, go to **Sketch** > **Include Library** > **Manage Libraries**, search for **WiFi**, and install it.

6. **ArduinoJson**  
   - **Package**: **ArduinoJson**  
   - **Installation**:  
     - In the **Arduino IDE**, go to **Sketch** > **Include Library** > **Manage Libraries**.  
     - Search for **ArduinoJson** and install it for JSON parsing in Telegram messages.

7. **HardwareSerial**  
   - **Package**: **HardwareSerial**  
   - **Installation**:  
     - The **HardwareSerial** library is built into the **ESP32** board package and doesn't require separate installation.  
     - You can access it in your code by including the following:
       ```cpp
       HardwareSerial mySerial(1); // Use UART1 for communication
       ```

8. **SoftwareSerial**  
   - **Package**: **SoftwareSerial**  
   - **Installation**:  
     - This library allows serial communication on other pins if needed, but it's typically not required for ESP32 (which has multiple hardware UARTs). However, if used, you can install it via **Sketch** > **Include Library** > **Manage Libraries**.

Make sure to install these packages to ensure that the **BeeWay** system works seamlessly with your ESP32-CAM and ESP32 devices. Also, ensure that you correctly configure the **hardware serial** and **software serial** as needed for the communication between the ESP32-CAM and other components.

---

## **Model Integration with Edge Impulse 🎯**

### Steps to Import and Deploy Edge Impulse Model on ESP32-CAM

1. **Train the Model on Edge Impulse**  
   - Upload elephant image datasets to Edge Impulse.  
   - Train and optimize the model using the **EON Tuner** for microcontrollers.

2. **Download the Model**  
   - Once the training is complete, go to the **Deployment** section in Edge Impulse.  
   - Select **"ESP32 - CAM"** and download the complete **ZIP file** (includes TFLite model, inference library, and necessary headers).

3. **Import the Model to Arduino IDE**  
   - Extract the downloaded ZIP file.  
   - Copy the folder to the **Arduino libraries** directory:
     
     ```cpp
     <Arduino>/libraries/edge_impulse_inferencing
     ```
     
4. **Include the Model in Your Code**  
   - Or Just import from the Examples and then select the board **ESP32 - CAM**
   - In your Arduino code, include the necessary Edge Impulse header files:
     
   ```cpp
   #include "edge-impulse-sdk/classifier/ei_run_classifier.h"
   ```
   
5. **Upload the Code to ESP32-CAM**
   - Open your Arduino IDE and load the code to the ESP32-CAM board.
   - Verify that the TFLite model runs inference locally and detects elephants as expected.

---

## **Setup Instructions 🛠️**

1. **Edge Impulse Model**  
   - **Train and deploy** the model using Edge Impulse.  
   - **Download** the model and import the extracted ZIP file into the Arduino libraries folder:
     
     ```
     <Arduino>/libraries/edge_impulse_inferencing
     ```

2. **Hardware Setup**  
   - **Connect** the ESP32-CAM, PIR sensor, DF Mini Player, and ESP32 boards as per the pin configuration above.

3. **Telegram Bot Setup**  
   - **Create** a bot on Telegram using **BotFather** and get the **Bot Token**.  
   - **Replace** the Bot Token and Chat ID in the ESP32 code.

4. **ESP-NOW Configuration**  
   - Ensure that the ESP32-CAM and ESP32 main board are on the **same WiFi channel** for ESP-NOW communication to work.

5. **Upload Code**  
   - Upload the respective `.ino` files to the **ESP32-CAM** and **ESP32** using the Arduino IDE.
   - Once uploaded, the system will begin detecting elephants, playing deterrent sounds, and sending alerts via Telegram.

---

## **Future Improvements 🌟**

- Extend the detection range using **LoRa** communication for larger areas.     
- Enhance detection accuracy with **multi-sensor fusion** (e.g., combining thermal imaging or sound-based detection).

---

## **License 📜**
This project is open-source and licensed under the **MIT License**.


---

**BeeWay** ensures safer human-wildlife coexistence using cutting-edge technology while promoting conservation. 🌍🐘⚡add  
---

## **Power Management 🔋**

### **Power Consumption**
- ESP32-CAM (Active): ~180mA
- ESP32-CAM (Deep Sleep): ~6mA
- PIR Sensor: ~65μA
- DF Mini Player (Playing): ~20mA
- DF Mini Player (Standby): ~10μA

### **Power Optimization**
1. **Deep Sleep Mode**
   - ESP32-CAM enters deep sleep when no motion is detected
   - Wake-up triggered by PIR sensor interrupt
   
2. **Solar Power Integration**
   - Recommended solar panel: 5V/2A
   - Battery capacity: 3.7V/5000mAh Li-ion
   - Charge controller for battery protection

---

## **Troubleshooting Guide 🔧**

### Common Issues and Solutions

1. **ESP32-CAM Won't Connect**
   - Check WiFi credentials
   - Verify GPIO0 is properly connected for programming
   - Reset board and try again

2. **No Telegram Alerts**
   - Verify bot token and chat ID
   - Check internet connectivity
   - Ensure proper ESP-NOW communication

3. **Poor Detection Accuracy**
   - Clean camera lens
   - Adjust camera position
   - Retrain model with more diverse dataset

---
