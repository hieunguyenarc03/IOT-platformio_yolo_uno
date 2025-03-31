#include <Arduino.h>

// private libraries
#include "dht11.h"
#include "display.h"
#include "wifi_connection.h"
#include "core_iot.h"

#define DHT11_PIN 47
#define TM1637_CLK_PIN 21
#define TM1637_DIO_PIN 38

constexpr char WIFI_SSID[] = "BKIT_CS2";
constexpr char WIFI_PASSWORD[] = "cselabc5c6";
constexpr char DEVICE_TOKEN[] = "vnmhnapcpct7lbv6moom";

constexpr char LATITUDE[] = "10.772823501090318";
constexpr char LONGITUDE[] = "106.6551133015508";

DisplayTM1637 display(TM1637_CLK_PIN, TM1637_DIO_PIN);
DHT11Sensor dht11(DHT11_PIN);
WifiConnection wifiWork(WIFI_SSID, WIFI_PASSWORD);
CoreIot coreIot(DEVICE_TOKEN);

void displayDHT11Data(void *pvParameters)
{
  while (true)
  {
    dht11.readDHT11();

    display.showTempAndHumid(dht11.getDHT11Data().temperature, dht11.getDHT11Data().humidity);

    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void publishDHT11Data(void *pvParameters)
{
  while (true)
  {
    dht11.readDHT11();

    coreIot.publishTelemetry("temperature", dht11.getDHT11Data().temperature);
    coreIot.publishTelemetry("humidity", dht11.getDHT11Data().humidity);

    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);

  wifiWork.connectToWifi();
  coreIot.connectToThingsBoard();

  coreIot.publishAttribute("latitude", LATITUDE);
  coreIot.publishAttribute("longitude", LONGITUDE);

  xTaskCreate(
      publishDHT11Data,
      "PublishDHT11Data",
      2048,
      nullptr,
      2,
      nullptr);

  xTaskCreate(
      displayDHT11Data,   // Function to execute
      "DisplayDHT11Data", // Task name (for debugging)
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