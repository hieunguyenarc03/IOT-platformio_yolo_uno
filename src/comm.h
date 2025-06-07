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
    CommI2C(const uint32_t I2C_FREQUENCY = 400000U,
            const uint8_t I2C_SDA_PIN = 11,
            const uint8_t I2C_SCL_PIN = 12)
        : SDA_PIN(I2C_SDA_PIN), SCL_PIN(I2C_SCL_PIN), FREQUENCY(I2C_FREQUENCY) {};
    ~CommI2C(void) = default;

    enum StatusCode initialize(void);
};

class CommSPI
{
private:
    const uint32_t FREQUENCY;

    const uint8_t MISO_PIN;
    const uint8_t MOSI_PIN;
    const uint8_t CLK_PIN;

public:
    CommSPI(const uint8_t SPI_MISO_PIN = 7,
            const uint8_t SPI_MOSI_PIN = 8,
            const uint8_t SPI_CLK_PIN = 6,
            const uint32_t SPI_FREQUENCY = 400000U)
        : MISO_PIN(SPI_MISO_PIN),
          MOSI_PIN(SPI_MOSI_PIN),
          CLK_PIN(SPI_CLK_PIN),
          FREQUENCY(SPI_FREQUENCY) {};

    enum StatusCode initialize(void);
};

#endif /* SRC_COMM_I2C_H_ */