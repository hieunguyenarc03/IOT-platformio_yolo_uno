#ifndef SRC_DHT11_H_
#define SRC_DHT11_H_

#include <Arduino.h>
#include "DHT.h"
struct DHT11Data
{
    float temperature;
    float humidity;
};

class DHT11Sensor
{
private:
    const uint8_t DHT_TYPE = 11;
    DHT dht11;
    struct DHT11Data dht11Data;

public:
    DHT11Sensor(const uint8_t DHT11_PIN);
    
    void readDHT11(void);
    struct DHT11Data getDHT11Data(void) const;
};

#endif /* SRC_DHT11_H_ */