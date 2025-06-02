#ifndef SRC_PLATFORM_H_
#define SRC_PLATFORM_H_

#include <WiFi.h>
#include <string>
#include "Arduino_MQTT_Client.h"
#include "ThingsBoard.h"
#include "global.h"

class CoreIoT
{
private:
    WiFiClient wifiClient;
    Arduino_MQTT_Client mqttClient;
    ThingsBoard tb;

    std::string TOKEN;

    inline static constexpr char SERVER[] = "app.coreiot.io";
    inline static constexpr uint16_t PORT = 1883U;
    inline static constexpr uint32_t MAX_MESSAGE_SIZE = 1024U;

    inline static constexpr char TELEMETRY_TOPIC[] = "v1/devices/me/telemetry";
    inline static constexpr char ATTRIBUTES_PUBLISH_TOPIC[] = "v1/devices/me/attributes";
    inline static constexpr char ATTRIBUTES_SUBSCRIBE_TOPIC[] = "v1/devices/me/attributes";

public:
    CoreIoT(const char *DEVICE_TOKEN) : mqttClient(wifiClient),
                                        tb(this->mqttClient, this->MAX_MESSAGE_SIZE) { this->TOKEN = DEVICE_TOKEN; };

    enum StatusCode initialize(void);
    enum StatusCode publishTelemetry(const char *json_payload);
    enum StatusCode publishAttribute(const char *json_payload);
};

#endif /* SRC_PLATFORM_H_ */