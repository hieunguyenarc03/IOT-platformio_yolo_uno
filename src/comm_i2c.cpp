#include "comm.h"

#include <Wire.h>

enum StatusCode CommI2C::initialize()
{
    if (Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN, this->I2C_FREQUENCY))
    {
        Serial.println("[OK] I2C initialization succeeded");
        return STATUS_OK;
    }
    Serial.println("[ERR] I2C initialization failed");
    return STATUS_ERROR;
}

enum StatusCode CommI2C::initialize(const uint32_t frequency)
{
    if (Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN, frequency))
    {
        Serial.println("[OK] I2C initialization succeeded");
        return STATUS_OK;
    }
    Serial.println("[ERR] I2C initialization failed");
    return STATUS_ERROR;
}