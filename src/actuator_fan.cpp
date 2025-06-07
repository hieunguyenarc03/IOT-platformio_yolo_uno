#include "actuator.h"

enum StatusCode ActuatorFan::initialize()
{
    ledcSetup(this->PWM_CHANNEL, this->PWM_FREQUENCY, this->PWM_RESOLUTION);
    ledcAttachPin(this->PIN, this->PWM_CHANNEL);

    this->turnOff();

    return STATUS_OK;
}

void ActuatorFan::setPower(uint8_t fan_power)
{
    // exeption handling
    fan_power = (fan_power > 100) ? 100 : fan_power;
    fan_power = (fan_power < 0) ? 0 : fan_power;

    this->power = fan_power;
    uint8_t duty_cycle = round(this->power * (255 / 100));

    ledcWrite(this->PWM_CHANNEL, duty_cycle);
}

void ActuatorFan::turnOn()
{
    this->setPower(100);
}

void ActuatorFan::turnOff()
{
    this->setPower(0);
}

uint8_t ActuatorFan::getPower()
{
    return this->power;
}