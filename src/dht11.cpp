#include "dht11.h"

DHT11Sensor::DHT11Sensor(const uint8_t DHT11_PIN)
    : dht11(DHT11_PIN, this->DHT_TYPE)
{
    dht11.begin();
}

void DHT11Sensor::readDHT11()
{
    dht11Data.temperature = dht11.readTemperature();
    dht11Data.humidity = dht11.readHumidity();
    if (isnan(dht11Data.temperature) || isnan(dht11Data.humidity))
    {
        dht11Data.temperature = 0;
        dht11Data.humidity = 0;
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }
}

struct DHT11Data DHT11Sensor::getDHT11Data() const
{
    return this->dht11Data;
}