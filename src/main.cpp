#include <Arduino.h>
#include <dht11.h>

void printDHT11Data(void *pvParameters)
{
  while (true)
  {
    readDHT11();

    Serial.print("Temperature: ");
    Serial.print(data.temperature);
    Serial.println(" *C");

    Serial.print("Humidity: ");
    Serial.print(data.humidity);
    Serial.println(" %");
    Serial.println();

    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);
  initDHT11();

  xTaskCreate(
      printDHT11Data,       // Function to execute
      "PrintDHT11DataTask", // Task name (for debugging)
      2048,                 // Stack size in bytes (adjust if needed)
      nullptr,              // Task parameters (none in this case)
      1,                    // Task priority (1 is low, higher numbers are higher priority)
      nullptr               // Task handle (not used here)
  );
}
void loop()
{
  // Empty because we are using FreeRTOS
}