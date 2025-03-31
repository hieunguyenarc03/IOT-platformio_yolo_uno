#include "core_iot.h"

CoreIot::CoreIot(const char *DEVICE_TOKEN) : mqttClient(wifiClient),
                                             tb(this->mqttClient, this->MAX_MESSAGE_SIZE)
{
    this->TOKEN = DEVICE_TOKEN;
}

void CoreIot::connectToThingsBoard()
{
    Serial.print("Connecting to: ");
    Serial.print(this->THINGSBOARD_SERVER.c_str());
    Serial.print(" with token ");
    Serial.println(TOKEN.c_str());
    if (tb.connect(this->THINGSBOARD_SERVER.c_str(), this->TOKEN.c_str(), THINGSBOARD_PORT))
    {

        Serial.println("Connected to ThingsBoard");
        return;
    }
    else
    {
        Serial.print("Failed to connect to ThingsBoard");
    }
}