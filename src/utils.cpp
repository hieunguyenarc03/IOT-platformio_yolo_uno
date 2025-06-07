#include "utils.h"

#include <ArduinoJson.h>

void createTelemetryJson(const struct SystemTelemetry *system_telemetry,
                         char *buffer_out, size_t const buffer_size)
{
    StaticJsonDocument<256> doc;

    doc["temperature"] = system_telemetry->temperature;
    doc["humidity"] = system_telemetry->humidity;
    doc["fan_power"] = system_telemetry->fan_power;
    doc["heater_power"] = system_telemetry->heater_power;
    doc["uptime_s"] = system_telemetry->uptime_s;

    serializeJson(doc, buffer_out, buffer_size);
}

void createAttributesJson(const struct SystemAttributes *system_attributes,
                          const struct SystemFixedAttributes *system_fixed_attributes,
                          char *buffer_out, size_t const buffer_size)
{
    StaticJsonDocument<256> doc;

    // doc["system_mode"] = system_attributes->system_mode;
    // doc["system_state"] = system_attributes->system_state;
    // doc["filament_type"] = system_attributes->filament_type;
    // doc["target_profile"] = system_attributes->target_profile;

    doc["FIRMWARE_VERSION"] = system_fixed_attributes->FIRMWARE_VERSION;
    doc["UNIVERSITY"] = system_fixed_attributes->UNIVERSITY;
    doc["ADDRESS"] = system_fixed_attributes->ADDRESS;
    doc["CAMPUS"] = system_fixed_attributes->CAMPUS;
    doc["FLOOR"] = system_fixed_attributes->FLOOR;
    doc["ROOM"] = system_fixed_attributes->ROOM;

    serializeJson(doc, buffer_out, buffer_size);
}