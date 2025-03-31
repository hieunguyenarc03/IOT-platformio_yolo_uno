#ifndef SRC_CORE_IOT_H_
#define SRC_CORE_IOT_H_

#include <Arduino.h>
#include <WiFi.h>
#include <Arduino_MQTT_Client.h>
#include <ThingsBoard.h>
#include <string>

class CoreIot
{
private:
    WiFiClient wifiClient;
    Arduino_MQTT_Client mqttClient;
    ThingsBoard tb;

    std::string TOKEN;
    const std::string THINGSBOARD_SERVER = "app.coreiot.io";
    const uint16_t THINGSBOARD_PORT = 1883U;
    const uint32_t MAX_MESSAGE_SIZE = 1024U;

public:
    CoreIot(const char *DEVICE_TOKEN);
    void connectToThingsBoard(void);
    void publishTelemetry(const char *topic, float payload)
    {
        tb.sendTelemetryData(topic, payload);
    }
    void publishAttribute(const char *topic, const char *payload)
    {
        tb.sendAttributeData(topic, payload);
    }
};

#endif /* SRC_CORE_IOT_H_ */