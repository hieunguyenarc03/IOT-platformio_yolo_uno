#include "dht11.h"
#include "DHT.h"

#define DHT_TYPE DHT11
#define DHT11_PIN 47

struct DHT11Data data;

DHT dht(DHT11_PIN, DHT_TYPE);

void initDHT11()
{
    dht.begin();
}

void readDHT11()
{
    data.temperature = dht.readTemperature();
    data.humidity = dht.readHumidity();
    if (isnan(data.temperature) || isnan(data.humidity))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }
}