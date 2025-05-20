#include "sensor.h"

enum StatusCode SensorDHT20::initialize()
{
    if (this->dht20.begin())
    {
        Serial.println("[OK] DHT20 initialization succeeded");
        return STATUS_OK;
    }
    else
    {
        Serial.println("[ERR] DHT20 initialization failed");
        return STATUS_ERROR;
    }
}

enum StatusCode SensorDHT20::readData()
{
    if (dht20.read() == DHT20_OK)
    {
        this->dht20_data.temperature = dht20.getTemperature();
        this->dht20_data.humidity = dht20.getHumidity();
        return STATUS_OK;
    }

    return STATUS_ERROR;
}

const struct SensorDHT20::DHT20Data *SensorDHT20::getDHT20Data() const
{
    return &this->dht20_data;
}