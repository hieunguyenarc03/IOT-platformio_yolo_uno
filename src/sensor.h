#ifndef SRC_SENSOR_DHT20_H_
#define SRC_SENSOR_DHT20_H_

#include "DHT20.h"
#include "global.h"

class Sensor
{
public:
    virtual ~Sensor(void) = default;

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

    inline static constexpr uint16_t I2C_ADDRESS = 0x38;

    DHT20 dht20;
    DHT20Data data;

public:
    SensorDHT20(void) = default;
    ~SensorDHT20(void) override = default;

    enum StatusCode initialize(void) override;
    enum StatusCode readData(void) override;
    const struct DHT20Data *getDHT20Data(void) const;
};

#endif /* SRC_SENSOR_DHT20_H_ */