#ifndef SRC_ACTUATOR_H_
#define SRC_ACTUATOR_H_

#include "global.h"

class Actuator
{
public:
    virtual ~Actuator() = default;

    virtual enum StatusCode initialize(void) = 0;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};

class ActuatorFan : public Actuator
{
private:
    const uint8_t PIN;
    const uint8_t PWM_CHANNEL;
    inline static constexpr uint8_t PWM_RESOLUTION = 8;
    inline static constexpr uint32_t PWM_FREQUENCY = 25000U;

    uint8_t power;

public:
    ActuatorFan(const uint8_t FAN_PIN, const uint8_t FAN_PWM_CHANNEL = 0) : PIN(FAN_PIN), PWM_CHANNEL(FAN_PWM_CHANNEL) {};
    ~ActuatorFan() override = default;

    enum StatusCode initialize(void) override;
    void turnOn(void) override;
    void turnOff(void) override;
    void setPower(uint8_t fan_power);
    uint8_t getPower(void);
};

#endif /* SRC_ACTUATOR_H_ */