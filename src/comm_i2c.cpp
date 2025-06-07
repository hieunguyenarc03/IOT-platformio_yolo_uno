#include "comm.h"

#include <Wire.h>

enum StatusCode CommI2C::initialize()
{
    if (Wire.begin(this->SDA_PIN, this->SCL_PIN, this->FREQUENCY))
    {
        Serial.println("[OK] I2C initialization succeeded");
        return STATUS_OK;
    }
    Serial.println("[ERR] I2C initialization failed");
    return STATUS_ERROR;
}