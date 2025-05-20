#ifndef SRC_SENSOR_DHT20_H_
#define SRC_SENSOR_DHT20_H_

#include "DHT20.h"

#include "global.h"

class Sensor
{
public:
    virtual ~Sensor() = default;

    virtual enum StatusCode initialize(void) = 0;
    virtual enum StatusCode readData(void) = 0;
};

class SensorDHT20 : public Sensor
{
private:
    struct DHT20Data
    {
        float temperature;
        float humidity;
    };

    static constexpr uint16_t DHT20_I2C_ADDRESS = 0x38;

    DHT20 dht20;
    DHT20Data dht20_data;

public:
    SensorDHT20() = default;
    ~SensorDHT20() override = default;

    enum StatusCode initialize(void) override;
    enum StatusCode readData(void) override;
    const struct DHT20Data *getDHT20Data(void) const;
};

#endif /* SRC_SENSOR_DHT20_H_ */