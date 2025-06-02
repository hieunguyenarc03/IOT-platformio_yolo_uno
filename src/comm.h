#ifndef SRC_COMM_H_
#define SRC_COMM_H_

#include "global.h"

class CommI2C
{
private:
    const uint32_t FREQUENCY;

    const uint8_t SDA_PIN;
    const uint8_t SCL_PIN;

public:
    CommI2C(const uint32_t I2C_FREQUENCY = 400000U, const int I2C_SDA_PIN = 11, const int I2C_SCL_PIN = 12) : SDA_PIN(I2C_SDA_PIN), SCL_PIN(I2C_SCL_PIN), FREQUENCY(I2C_FREQUENCY) {};
    ~CommI2C(void) = default;

    enum StatusCode initialize(void);
};

#endif /* SRC_COMM_I2C_H_ */