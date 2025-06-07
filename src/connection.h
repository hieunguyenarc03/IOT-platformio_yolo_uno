#ifndef SRC_CONNECTION_H_
#define SRC_CONNECTION_H_

#include <WiFi.h>
#include <string>
#include "global.h"

class ConnectionWifi
{
private:
    WiFiClass WiFi;

    const std::string SSID;
    const std::string PASSWORD;

public:
    ConnectionWifi(const char *WIFI_SSID, const char *WIFI_PASSWORD) : SSID(WIFI_SSID), PASSWORD(WIFI_PASSWORD) {};
    ~ConnectionWifi(void) = default;

    enum StatusCode initialize(void);
    const WiFiClass *getWiFiInstance(void) const;
};

#endif /* SRC_CONNECTION_H_ */