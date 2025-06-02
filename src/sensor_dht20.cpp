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
        this->data.temperature = dht20.getTemperature();
        this->data.humidity = dht20.getHumidity();

        Serial.println("[OK] DHT20 read succeeded");
        Serial.print("Temperature: ");
        Serial.println(this->data.temperature, 2);
        Serial.print("Humidity: ");
        Serial.println(this->data.humidity, 2);

        return STATUS_OK;
    }

    return STATUS_ERROR;
}

const struct SensorDHT20::DHT20Data *SensorDHT20::getDHT20Data() const
{
    return &this->data;
}