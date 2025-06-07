#include <string>
#include <Arduino.h>
#include <Wire.h>

// private libraries
#include "global.h"
#include "system_manager.h"
#include "comm.h"
#include "connection.h"
#include "core_iot.h"
#include "sensor.h"
#include "input.h"
#include "actuator.h"
#include "heater.h"
#include "display.h"
#include "utils.h"

#define LED_NEO_PIN 45

#define I2C_SPEED 400000U
#define I2C_SDA_PIN 11
#define I2C_SCL_PIN 12

#define SPI_MISO_PIN 10
#define SPI_MOSI_PIN 21
#define SPI_CLK_PIN 18
#define SPI_SS_PIN 8

#define RFID_RST_PIN 9

#define FAN_PIN 6
#define FAN_PWM_CHANNEL 0
#define HEATER_PIN 8
#define HEATER_PWM_CHANNEL 1

constexpr char WIFI_SSID[] = "BKIT_CS3";
constexpr char WIFI_PASSWORD[] = "cselabc5c6";

constexpr char TOKEN_DRYER_309[] = "dryer309";

ConnectionWifi office_wifi(WIFI_SSID, WIFI_PASSWORD);
CoreIoT core_iot_dryer_309(TOKEN_DRYER_309);
CommI2C comm_i2c(I2C_SPEED);
CommSPI comm_spi(SPI_MISO_PIN, SPI_MOSI_PIN, SPI_CLK_PIN, SPI_SS_PIN);
SensorDHT20 sensor_dht20;
InputRFID input_rfid(RFID_RST_PIN, SPI_SS_PIN);
ActuatorFan actuator_fan(FAN_PIN, FAN_PWM_CHANNEL);
Heater heater(HEATER_PIN, HEATER_PWM_CHANNEL);
DisplayLCD display_lcd;
DisplayLedNeo display_led_neo(LED_NEO_PIN);

SystemTelemetry system_telemetry;
SystemAttributes system_attributes;
SystemFixedAttributes system_fixed_attributes;

void updateSystemTelemetry(void *pvParameters)
{
  while (1)
  {
    sensor_dht20.readData();

    if (system_attributes.getSystemState() == SystemAttributes::SystemState::IDLE)
    {
      system_telemetry.uptime_s = 0;
    }
    else
    {
      ++system_telemetry.uptime_s;
    }

    if (system_telemetry.uptime_s >= system_attributes.getTargetProfile()->drying_time_s &&
        system_attributes.getTargetProfile()->drying_time_s != 0)
    {
      system_attributes.update(system_attributes.getSystemMode(), SystemAttributes::SystemState::IDLE,
                               SystemAttributes::FilamentType::UNKNOWN, {0.0, 0.0, 0});
    }

    system_telemetry.update(sensor_dht20.getDHT20Data()->temperature, sensor_dht20.getDHT20Data()->humidity, actuator_fan.getPower(), heater.getPower(), system_telemetry.uptime_s);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void updateDisplay(void *pvParameters)
{
  enum class DisplayMode
  {
    INFORMATION,
    CONDITION,
    TARGET_CONDITION,
    CONTROLLER,
    TIME
  };

  enum DisplayMode display_mode = DisplayMode::INFORMATION;
  uint8_t counter = 0;

  while (1)
  {
    display_lcd.clear();

    char display_buffer[16];

    switch (display_mode)
    {
    case DisplayMode::INFORMATION:
    {
      snprintf(display_buffer, sizeof(display_buffer), "FW Ver: %s", system_fixed_attributes.FIRMWARE_VERSION);
      display_lcd.displayString(0, 0, display_buffer);

      snprintf(display_buffer, sizeof(display_buffer), "Sys Mode: %s",
               ((system_attributes.getSystemMode() == SystemAttributes::SystemMode::AUTOMATIC) ? "AUT" : "MAN"));
      display_lcd.displayString(1, 0, display_buffer);

      break;
    }
    case DisplayMode::CONDITION:
    {
      snprintf(display_buffer, sizeof(display_buffer), "Temp: %.2f", sensor_dht20.getDHT20Data()->temperature);
      display_lcd.displayString(0, 0, display_buffer);

      snprintf(display_buffer, sizeof(display_buffer), "Humidity: %.2f", sensor_dht20.getDHT20Data()->humidity);
      display_lcd.displayString(1, 0, display_buffer);

      break;
    }
    case DisplayMode::CONTROLLER:
    {
      snprintf(display_buffer, sizeof(display_buffer), "Fan Pwr: %d", actuator_fan.getPower());
      display_lcd.displayString(0, 0, display_buffer);

      switch (system_attributes.getFilamentType())
      {
      case SystemAttributes::FilamentType::PLA:
      {
        snprintf(display_buffer, sizeof(display_buffer), "PLA");
        break;
      }
      case SystemAttributes::FilamentType::ABS:
      {
        snprintf(display_buffer, sizeof(display_buffer), "ABS");
        break;
      }
      case SystemAttributes::FilamentType::PETG:
      {
        snprintf(display_buffer, sizeof(display_buffer), "PET");
        break;
      }
      default:
      {
        snprintf(display_buffer, sizeof(display_buffer), "UNK");
      }
      }
      display_lcd.displayString(13, 0, display_buffer);

      snprintf(display_buffer, sizeof(display_buffer), "Heater Pwr: %d", heater.getPower());
      display_lcd.displayString(1, 0, display_buffer);

      break;
    }
    case DisplayMode::TARGET_CONDITION:
    {
      snprintf(display_buffer, sizeof(display_buffer), "Target Temp: %.2f", system_attributes.getTargetProfile()->target_temperature);
      display_lcd.displayString(0, 0, display_buffer);

      snprintf(display_buffer, sizeof(display_buffer), "Target Humi: %.2f", system_attributes.getTargetProfile()->target_humidity);
      display_lcd.displayString(1, 0, display_buffer);

      break;
    }
    case DisplayMode::TIME:
    {
      if (system_attributes.getSystemState() == SystemAttributes::SystemState::HEATING)
      {
        snprintf(display_buffer, sizeof(display_buffer), "Uptime: %u", system_telemetry.uptime_s);
        display_lcd.displayString(0, 0, display_buffer);

        snprintf(display_buffer, sizeof(display_buffer), "Target Time: %u", system_attributes.getTargetProfile()->drying_time_s);
        display_lcd.displayString(1, 0, display_buffer);
      }

      snprintf(display_buffer, sizeof(display_buffer), (system_attributes.getSystemState() == SystemAttributes::SystemState::HEATING) ? "ON" : "OFF");
      display_lcd.displayString(0, 13, display_buffer);

      break;
    }
    }

    counter = (counter + 1) % 5;
    if (counter == 0)
    {
      switch (display_mode)
      {
      case DisplayMode::INFORMATION:
      {
        display_mode = DisplayMode::CONDITION;
        break;
      }
      case DisplayMode::CONDITION:
      {
        if (system_attributes.getSystemState() == SystemAttributes::SystemState::IDLE)
        {
          display_mode = DisplayMode::TIME;
          break;
        }
        display_mode = DisplayMode::TARGET_CONDITION;
        break;
      }
      case DisplayMode::CONTROLLER:
      {
        display_mode = DisplayMode::TIME;
        break;
      }
      case DisplayMode::TARGET_CONDITION:
      {
        display_mode = DisplayMode::CONTROLLER;
        break;
      }
      case DisplayMode::TIME:
      {
        display_mode = DisplayMode::INFORMATION;
        break;
      }
      }
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void updateSystemAttributes(void *pvParameters)
{
  const uint16_t json_max_size = 256;
  char json_payload[json_max_size] = "";

  while (1)
  {
    if (input_rfid.isRFIDDetected())
    {
      switch (input_rfid.checkAuthorizedKey())
      {
      case InputRFID::AuthorizedKey::KEY_1:
      {
        system_attributes.update(SystemAttributes::SystemMode::AUTOMATIC,
                                 SystemAttributes::SystemState::HEATING,
                                 SystemAttributes::FilamentType::ABS, {0.0f, 0.0f, 0});

        system_telemetry.uptime_s = 0;

        break;
      }
      case InputRFID::AuthorizedKey::KEY_2:
      {
        system_attributes.update(SystemAttributes::SystemMode::AUTOMATIC,
                                 SystemAttributes::SystemState::HEATING,
                                 SystemAttributes::FilamentType::PETG, {0.0f, 0.0f, 0});

        system_telemetry.uptime_s = 0;

        break;
      }
      case InputRFID::AuthorizedKey::KEY_3:
      {
        system_attributes.update(SystemAttributes::SystemMode::AUTOMATIC,
                                 SystemAttributes::SystemState::HEATING,
                                 SystemAttributes::FilamentType::PLA, {0.0f, 0.0f, 0});

        system_telemetry.uptime_s = 0;

        break;
      }

      default:
        break;
      }
    }

    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void publishSystemTelemetry(void *pvParameters)
{
  const uint16_t json_max_size = 256;
  char json_payload[json_max_size] = "";

  while (1)
  {
    createTelemetryJson(&system_telemetry, json_payload, json_max_size);

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
  (void)comm_spi.initialize();
  (void)sensor_dht20.initialize();
  (void)input_rfid.initialize();
  (void)display_lcd.initialize();
  (void)display_led_neo.initialize();
  (void)actuator_fan.initialize();

  xTaskCreate(
      updateSystemTelemetry,   // Function to execute
      "updateSystemTelemetry", // Task name (for debugging)
      2048,                    // Stack size in bytes (adjust if needed)
      nullptr,                 // Task parameters (none in this case)
      1,                       // Task priority (1 is low, higher numbers are higher priority)
      nullptr                  // Task handle (not used here)
  );

  xTaskCreate(
      updateDisplay,   // Function to execute
      "updateDisplay", // Task name (for debugging)
      2048,            // Stack size in bytes (adjust if needed)
      nullptr,         // Task parameters (none in this case)
      2,               // Task priority (1 is low, higher numbers are higher priority)
      nullptr          // Task handle (not used here)
  );

  xTaskCreate(
      updateSystemAttributes,   // Function to execute
      "updateSystemAttributes", // Task name (for debugging)
      2048,                     // Stack size in bytes (adjust if needed)
      nullptr,                  // Task parameters (none in this case)
      3,                        // Task priority (1 is low, higher numbers are higher priority)
      nullptr                   // Task handle (not used here)
  );

  xTaskCreate(
      publishSystemTelemetry, // Function to execute
      "updateTelemetryData",  // Task name (for debugging)
      2048,                   // Stack size in bytes (adjust if needed)
      nullptr,                // Task parameters (none in this case)
      4,                      // Task priority (1 is low, higher numbers are higher priority)
      nullptr                 // Task handle (not used here)
  );
}

void loop()
{
}