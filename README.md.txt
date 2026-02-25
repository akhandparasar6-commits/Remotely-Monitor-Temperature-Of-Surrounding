# 🌡️ ESP32 IoT Temperature Monitoring System (FreeRTOS + MQTT)

## 📖 Project Overview
This project is an IoT-based temperature monitoring system using:

- ESP32
- DS18B20 Temperature Sensor
- SSD1306 OLED Display
- Buzzer
- WiFi
- Adafruit IO (MQTT)
- FreeRTOS Tasks

The system:
- Reads temperature using DS18B20
- Displays temperature on OLED
- Sends temperature to Adafruit IO cloud
- Activates buzzer if temperature exceeds 20°C
- Uses FreeRTOS for multitasking

---

## 🛠️ Components Used
- ESP32
- DS18B20 Temperature Sensor
- SSD1306 OLED Display (I2C – 0x3C)
- Buzzer
- 4.7kΩ Pull-up Resistor
- WiFi Connection

---

## 📚 Libraries Required
Install from Arduino Library Manager:

- OneWire
- DallasTemperature
- Wire
- Adafruit GFX
- Adafruit SSD1306
- WiFi
- Adafruit MQTT
- FreeRTOS (Built-in with ESP32)

---

## 🔌 Pin Configuration

### DS18B20
- VCC → 3.3V  
- GND → GND  
- DATA → GPIO 5  
- 4.7kΩ resistor between VCC and DATA  

### OLED (I2C)
- VCC → 3.3V  
- GND → GND  
- SDA → GPIO 21  
- SCL → GPIO 22  
- Address → 0x3C  

### Buzzer
- Positive → GPIO 25  
- Negative → GND  

---

## 🌐 Cloud Configuration

- Server: io.adafruit.com  
- Port: 1883  
- Feed Name: temperature  
- Protocol: MQTT  

Temperature data is published to Adafruit IO dashboard.

---

## ⚙️ System Working

1. ESP32 connects to WiFi.
2. ESP32 connects to Adafruit IO MQTT broker.
3. FreeRTOS task continuously:
   - Reads temperature
   - Displays on OLED
   - Prints to Serial Monitor
   - Publishes to MQTT feed
   - Activates buzzer if temperature > 20°C
4. Task runs every 1 second.

---

## 🧠 FreeRTOS Concept Used

- Task creation for sensor & display
- Queue for data sharing
- vTaskDelay() for task timing
- loop() disabled using PortMAX_DELAY

---

## 🖥️ Serial Output Example

temperature 25.60 degree C  
WiFi Is Connected  
ADAFRUIT IO Is Connected  

---

## 🚀 How to Run

1. Install required libraries.
2. Update WiFi credentials.
3. Update Adafruit IO username and key.
4. Upload code to ESP32.
5. Open Serial Monitor (115200 baud).
6. Monitor data on Adafruit IO dashboard.

---

## 🔔 Alert Logic

If temperature exceeds 20°C:
- Buzzer turns ON briefly.
- Temperature is still uploaded to cloud.

---

## 📂 Project Structure

ESP32_IOT_Temperature_Monitor/
│
├── main.ino
└── README.md

---

## 🔮 Future Improvements

- Add humidity sensor
- Add mobile push notifications
- Store historical cloud data
- Adjustable temperature threshold
- Multiple FreeRTOS tasks separation

---

## 👨‍💻 Author
AKHAND PARASAR  
Embedded Systems & IoT Enthusiast