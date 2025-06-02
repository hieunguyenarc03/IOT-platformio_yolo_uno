#include "connection.h"

enum StatusCode ConnectionWifi::initialize()
{
    if (this->SSID == "")
    {
        Serial.println("[ERR] SSID or PASSWORD is invalid");
        return STATUS_ERROR;
    }

    Serial.print("Wifi SSID: ");
    Serial.println(this->SSID.c_str());
    Serial.print(" Wifi PASSWORD: ");
    Serial.println(this->PASSWORD.c_str());

    Serial.println("Connecting to AP ...");
    this->WiFi.begin(this->SSID.c_str(), this->PASSWORD.c_str());

    for (uint8_t i = 0; i < 10; i++)
    {
        delay(1000);
        Serial.print(".");
        ++i;
        if (this->WiFi.status() == WL_CONNECTED)
        {
            Serial.print("IP address: ");
            Serial.println(this->WiFi.localIP());

            Serial.println("[OK] Wifi connection succeeded");
            return STATUS_OK;
        }
    }

    Serial.println("[ERR] Wifi connetion failed");
    return STATUS_ERROR;
}

const WiFiClass *ConnectionWifi::getWiFiInstance() const
{
    return &this->WiFi;
}