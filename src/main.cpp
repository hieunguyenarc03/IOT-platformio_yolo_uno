#include <Arduino.h>

void printHelloWorld(void *pvParameters)
{
  while (true)
  {
    Serial.println("Hello World!");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);

  xTaskCreate(
      printHelloWorld,  // Function to execute
      "HelloWorldTask", // Task name (for debugging)
      10000,            // Stack size in bytes (adjust if needed)
      NULL,             // Task parameters (none in this case)
      1,                // Task priority (1 is low, higher numbers are higher priority)
      NULL              // Task handle (not used here)
  );
}

void loop()
{
  // Empty because we are using FreeRTOS
}