#ifndef SRC_WIFI_H_
#define SRC_WIFI_H_

#include <Arduino.h>
#include <string>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif /* ESP8266 */

#ifdef ESP32
#include <WiFi.h>
#endif /* ESP32 */

class WifiConnection
{
private:
    std::string SSID;
    std::string PASSWORD;

public:
    WifiConnection(const char *WIFI_SSID, const char *WIFI_PASSWORD);
    void connectToWifi(void);
};

#endif /* SRC_WIFI_H_ */