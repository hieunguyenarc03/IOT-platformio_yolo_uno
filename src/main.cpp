#include <string>
#include <Arduino.h>
#include <Wire.h>

// private libraries
#include "global.h"
#include "comm.h"
#include "connection.h"
#include "core_iot.h"
#include "sensor.h"
#include "actuator.h"
#include "heater.h"
#include "display.h"
#include "utils.h"

#define FIRMWARE_VERSION "0.0.0"

#define I2C_SPEED 400000U
#define I2C_SDA_PIN 11
#define I2C_SCL_PIN 12

#define FAN_PIN 6
#define FAN_PWM_CHANNEL 0
#define HEATER_PIN 8
#define HEATER_PWM_CHANNEL 1

constexpr char WIFI_SSID[] = "BKIT_CS3";
constexpr char WIFI_PASSWORD[] = "cselabc5c6";
constexpr char TOKEN_DRYER_309[] = "dryer309";

// ConnectionWifi office_wifi(WIFI_SSID, WIFI_PASSWORD);
ConnectionWifi office_wifi("RD-SEAI_2.4G", "");
CoreIoT core_iot_dryer_309(TOKEN_DRYER_309);
CommI2C comm_i2c(I2C_SPEED);
SensorDHT20 sensor_dht20;
ActuatorFan actuator_fan(FAN_PIN, FAN_PWM_CHANNEL);
Heater heater(HEATER_PIN, HEATER_PWM_CHANNEL);
DisplayLCD display_lcd;

void display(void *pvParameters)
{
  enum DisplayMode
  {
    INFORMATION,
    DHT20_DATA,
    TEMP_CONTROLLER
  };

  enum DisplayMode current_display_mode = INFORMATION;

  while (true)
  {
    display_lcd.clear();

    char display_buffer[16];

    switch (current_display_mode)
    {
    case INFORMATION:
    {
      snprintf(display_buffer, sizeof(display_buffer), "FW Ver: %s", FIRMWARE_VERSION);
      display_lcd.displayString(0, 0, display_buffer);

      // Currently have not implemented get Filament type
      snprintf(display_buffer, sizeof(display_buffer), "Filament: %s", "PLA");
      display_lcd.displayString(1, 0, display_buffer);

      current_display_mode = DHT20_DATA;

      break;
    }
    case DHT20_DATA:
    {
      sensor_dht20.readData();

      snprintf(display_buffer, sizeof(display_buffer), "Temp: %.2f", sensor_dht20.getDHT20Data()->temperature);
      display_lcd.displayString(0, 0, display_buffer);

      snprintf(display_buffer, sizeof(display_buffer), "Humidity: %.2f", sensor_dht20.getDHT20Data()->humidity);
      display_lcd.displayString(1, 0, display_buffer);

      current_display_mode = TEMP_CONTROLLER;

      break;
    }
    case TEMP_CONTROLLER:
    {
      snprintf(display_buffer, sizeof(display_buffer), "Fan Pwr: %d", actuator_fan.getPower());
      display_lcd.displayString(0, 0, display_buffer);

      snprintf(display_buffer, sizeof(display_buffer), "Heater Pwr: %d", heater.getPower());
      display_lcd.displayString(1, 0, display_buffer);

      current_display_mode = INFORMATION;

      break;
    }
    }

    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void publishTelemetry(void *pvParameters)
{
  while (true)
  {
    sensor_dht20.readData();

    const uint16_t json_max_size = 256;
    char json_payload[256] = "";

    createTelemetryJson(sensor_dht20.getDHT20Data()->temperature, sensor_dht20.getDHT20Data()->humidity,
                        actuator_fan.getPower(), heater.getPower(), json_payload, json_max_size);

    core_iot_dryer_309.publishTelemetry(json_payload);

    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);

  (void)office_wifi.initialize();
  (void)core_iot_dryer_309.initialize();
  (void)comm_i2c.initialize();
  (void)sensor_dht20.initialize();
  (void)display_lcd.initialize();
  (void)actuator_fan.initialize();

  actuator_fan.setPower(0);

  xTaskCreate(
      display,   // Function to execute
      "display", // Task name (for debugging)
      2048,      // Stack size in bytes (adjust if needed)
      nullptr,   // Task parameters (none in this case)
      2,         // Task priority (1 is low, higher numbers are higher priority)
      nullptr    // Task handle (not used here)
  );

  xTaskCreate(
      publishTelemetry,   // Function to execute
      "publishTelemetry", // Task name (for debugging)
      2048,               // Stack size in bytes (adjust if needed)
      nullptr,            // Task parameters (none in this case)
      3,                  // Task priority (1 is low, higher numbers are higher priority)
      nullptr             // Task handle (not used here)
  );
}

void loop()
{
  // Empty because we are using FreeRTOS
}