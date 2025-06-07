# IoT Assignment: AcLAB 3D Printing Filament Dryer
## IoT Solution based on Core IoT platform.

### Devices in the System
#### Devices are included in AIoT kit
- **LCD 16x2 Display**  
  Used to show real-time temperature, humidity, filament information, and system status.

- **DHT20 Sensor**  
  Measures temperature and humidity inside the dryer chamber.

- **Fan** 
  Regulates airflow and assists in controlling the drying temperature. Used to simulate PID control of heater.

#### Thiết bị bên ngoài
- **RFID Reader**  
  Used for user management and to save filament type and color information via RFID cards.

- **Microcontroller (Yolo Uno)**  
  Core controller for all devices and IoT features.

### System Requirements
[x] Remote control.
[x] Access control. User management RFID.
[x] Data Logging.
[x] OTA Firmware Update.
[x] Can Configure Wifi Without Re-Program.
[x] Core IoT Features.

### 	Requirements from Users:
[] Control the temperature to dry the 3d printing filament.
[] Alarm.
[x] Rfid card to save the type, color of 3d filament.

### RFID card data frame
#### MIFARE Ultralight or Ultralight C
1: 04 5A 67 A2 5C 64 80
2: 04 87 10 42 5D 64 80
3: 04 87 10 42 5D 64 80

#### MIFARE 1KB
1: AC C5 5F 9D
2: F3 F5 10 1A
3: 92 85 76 1E