#ifndef SRC_COMM_I2C_H_
#define SRC_COMM_I2C_H_

#include "global.h"

class Comm
{
public:
    virtual ~Comm() = default;

    virtual enum StatusCode initialize() = 0;
};

class CommI2C : public Comm
{
private:
    static constexpr uint32_t I2C_FREQUENCY = 400000U;

    const int I2C_SDA_PIN;
    const int I2C_SCL_PIN;

public:
    CommI2C(const int sda_pin, const int scl_pin) : I2C_SDA_PIN(sda_pin), I2C_SCL_PIN(scl_pin) {};
    ~CommI2C() override = default;

    enum StatusCode initialize() override;
    enum StatusCode initialize(const uint32_t frequency);
};

#endif /* SRC_COMM_I2C_H_ */