#include "heater.h"

void Heater::initialize()
{
    ledcSetup(this->PWM_CHANNEL, this->PWM_FREQUENCY, this->PWM_RESOLUTION);
    ledcAttachPin(this->PIN, this->PWM_CHANNEL);

    this->turnOff();

    return;
}

void Heater::setPower(uint8_t heater_power)
{
    // exeption handling
    heater_power = (heater_power > 100) ? 100 : heater_power;
    heater_power = (heater_power < 0) ? 0 : heater_power;

    this->power = heater_power;
    uint8_t duty_cycle = round(this->power * (255 / 100));

    ledcWrite(this->PWM_CHANNEL, duty_cycle);
}

void Heater::turnOn()
{
    this->setPower(100);
}

void Heater::turnOff()
{
    this->setPower(0);
}

uint8_t Heater::getPower()
{
    return this->power;
}