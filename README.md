# ESP32: Receive Data Only (LED Control via MQTT)

This code allows the ESP32 to receive commands from a server through MQTT to control an LED.

---

## Features

1. Subscribes to MQTT topic: `esp32/commands`.
2. Receives:
   - `1`: Turns the LED ON.
   - `0`: Turns the LED OFF.

---

## Setup Instructions

### **Hardware**
1. Connect an LED to GPIO 2 of the ESP32.
2. Use a 220-ohm resistor to limit current.

### **Software**
1. Open the Arduino IDE.
2. Update the following in the code:
   - Wi-Fi credentials (`ssid` and `password`).
   - MQTT broker IP (`mqtt_broker`).
3. Upload the code to the ESP32.

---

## Testing Instructions

1. Start the MQTT broker on your server.
2. Send commands using a tool like Mosquitto or Postman:
   - Turn LED ON:
     ```bash
     mosquitto_pub -h <broker-ip> -t esp32/commands -m "1"
     ```
   - Turn LED OFF:
     ```bash
     mosquitto_pub -h <broker-ip> -t esp32/commands -m "0"
     ```

3. Monitor the Serial Monitor in Arduino IDE to confirm received commands and LED status.

---

## Files
- `esp32_receive_data.ino`: The ESP32 code for receiving data only.

---

## License
This project is licensed under the MIT License.
