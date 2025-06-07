#include "system_manager.h"

void SystemTelemetry::update(const float measured_temperature,
                             const float measured_humidity,
                             const uint8_t measured_fan_power,
                             const uint8_t measured_heater_power,
                             const unsigned long measured_uptime)
{
    this->temperature = measured_temperature;
    this->humidity = measured_humidity;
    this->fan_power = measured_fan_power;
    this->heater_power = measured_heater_power;
    this->uptime_s = measured_uptime;
}

void SystemAttributes::update(const SystemMode set_system_mode,
                              const SystemState set_system_state,
                              const FilamentType set_filament_type,
                              const TargetProfile set_target_profile)
{
    this->system_mode = set_system_mode;
    this->system_state = set_system_state;
    this->filament_type = set_filament_type;

    if (this->system_mode == SystemMode::MANUAL)
    {
        this->target_profile = set_target_profile;
    }
    else
    {
        auto it = this->filament_profiles_map.find(this->filament_type);
        if (it != this->filament_profiles_map.end())
        {
            this->target_profile = it->second;
        }
        else
        {
            target_profile = {0.0f, 0.0f, 0};
        }
    }
}

SystemAttributes::SystemMode SystemAttributes::getSystemMode() const
{
    return this->system_mode;
}
SystemAttributes::SystemState SystemAttributes::getSystemState() const
{
    return this->system_state;
}
SystemAttributes::FilamentType SystemAttributes::getFilamentType() const
{
    return this->filament_type;
}

const SystemAttributes::TargetProfile *SystemAttributes::getTargetProfile() const
{
    return &this->target_profile;
}