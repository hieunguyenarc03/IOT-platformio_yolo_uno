#ifndef SRC_WIFI_H_
#define SRC_WIFI_H_

#include <WiFi.h>
#include <string>
#include "global.h"

class Connection
{
public:
    virtual ~Connection() = default;

    virtual enum StatusCode initialize(void) = 0;
};

class ConnectionWifi : Connection
{
private:
    WiFiClass WiFi;

    std::string SSID;
    std::string PASSWORD;

public:
    ConnectionWifi(const char *WIFI_SSID, const char *WIFI_PASSWORD);
    ~ConnectionWifi() = default;

    enum StatusCode initialize(void) override;
    const WiFiClass *getWiFiInstance(void) const;
};

#endif /* SRC_WIFI_H_ */