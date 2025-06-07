#include "core_iot.h"

enum StatusCode CoreIoT::initialize()
{
    Serial.print("Core IoT server: ");
    Serial.print(this->SERVER);
    Serial.print(" Device token: ");
    Serial.println(this->TOKEN.c_str());

    if (this->tb.connect(this->SERVER, this->TOKEN.c_str(), this->PORT))
    {
        Serial.println("[OK] Core IoT connection succeeded");
        return STATUS_OK;
    }
    else
    {
        Serial.println("[ERR] Core IoT connetion failed");
        return STATUS_ERROR;
    }
}

enum StatusCode CoreIoT::publishTelemetry(const char *json_payload)
{
    if (this->tb.Send_Json_String(this->TELEMETRY_TOPIC, json_payload))
    {
        return STATUS_OK;
    }
    return STATUS_ERROR;
}

enum StatusCode CoreIoT::publishAttribute(const char *json_payload)
{
    if (this->tb.Send_Json_String(this->ATTRIBUTES_PUBLISH_TOPIC, json_payload))
    {
        return STATUS_OK;
    }
    return STATUS_ERROR;
}