#include "wifi_connection.h"

WifiConnection::WifiConnection(const char *WIFI_SSID, const char *WIFI_PASSWORD)
{
    this->SSID = WIFI_SSID;
    this->PASSWORD = WIFI_PASSWORD;
}

void WifiConnection::connectToWifi(void)
{
    if (SSID == "" || PASSWORD == "")
    {
        Serial.println("SSID or PASSWORD is invalid");
        return;
    }

    Serial.println("Connecting to AP ...");
    WiFi.begin(SSID.c_str(), PASSWORD.c_str());

    for (uint8_t i = 0; i < 10; i++)
    {
        delay(1000);
        Serial.print(".");
        ++i;
        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("Connected to AP");
            return;
        }
    }

    Serial.println("Failed to connect to AP");
}