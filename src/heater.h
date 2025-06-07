#ifndef SRC_HEATER_H_
#define SRC_HEATER_H_

#include "global.h"

class Heater
{
private:
    const uint8_t PIN;
    const uint8_t PWM_CHANNEL;
    inline static constexpr uint8_t PWM_RESOLUTION = 8;
    inline static constexpr uint32_t PWM_FREQUENCY = 1000;

    uint8_t power;

public:
    Heater(const uint8_t HEATER_PIN, const uint8_t HEATER_PWM_CHANNEL = 1) : PIN(HEATER_PIN), PWM_CHANNEL(HEATER_PWM_CHANNEL) {};

    void initialize(void);
    void turnOn(void);
    void turnOff(void);
    void setPower(uint8_t heater_power);
    uint8_t getPower(void);
};

#endif /* SRC_HEATER_H_ */