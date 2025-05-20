#include <string>
#include <Arduino.h>
#include <Wire.h>

// private libraries
#include "global.h"
#include "comm.h"
#include "connection.h"
#include "sensor.h"
#include "display.h"

#define I2C_SDA_PIN 11
#define I2C_SCL_PIN 12
constexpr char WIFI_SSID[] = "BKIT_LUGIA_CS2";
constexpr char WIFI_PASSWORD[] = "cselabc5c6";

CommI2C comm_i2c(I2C_SDA_PIN, I2C_SCL_PIN);
ConnectionWifi office_wifi(WIFI_SSID, WIFI_PASSWORD);
SensorDHT20 sensor_dht20;
DisplayLCD display_lcd;

void displayDHT20Data(void *pvParameters)
{
  while (true)
  {
    display_lcd.clear();
    sensor_dht20.readData();

    char display_buffer[16];

    snprintf(display_buffer, sizeof(display_buffer), "Temp: %.2f", sensor_dht20.getDHT20Data()->temperature);
    display_lcd.displayString(0, 0, display_buffer);

    snprintf(display_buffer, sizeof(display_buffer), "Humidity: %.2f", sensor_dht20.getDHT20Data()->humidity);
    display_lcd.displayString(1, 0, display_buffer);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);

  (void)comm_i2c.initialize();
  (void)office_wifi.initialize();
  (void)sensor_dht20.initialize();
  (void)display_lcd.initialize();

  xTaskCreate(
      displayDHT20Data,   // Function to execute
      "DisplayDHT20Data", // Task name (for debugging)
      2048,               // Stack size in bytes (adjust if needed)
      nullptr,            // Task parameters (none in this case)
      1,                  // Task priority (1 is low, higher numbers are higher priority)
      nullptr             // Task handle (not used here)
  );
}

void loop()
{
  // Empty because we are using FreeRTOS
}