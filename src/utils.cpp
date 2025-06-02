#include "utils.h"

#include <ArduinoJson.h>

void createTelemetryJson(float temperature, float humidity, uint8_t fan_speed, uint8_t heater_power, char *buffer_out, size_t const buffer_size)
{
    StaticJsonDocument<256> doc;

    doc["temperature"] = temperature;
    doc["humidity"] = humidity;
    doc["fan_speed"] = fan_speed;
    doc["heater_power"] = heater_power;

    serializeJson(doc, buffer_out, buffer_size);
}