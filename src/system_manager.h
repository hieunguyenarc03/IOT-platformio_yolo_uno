#ifndef SRC_SYSTEM_MANAGER_H_
#define SRC_SYSTEM_MANAGER_H_

#include <string>
#include <unordered_map>
#include "global.h"

struct SystemTelemetry
{
    float temperature;
    float humidity;
    uint8_t fan_power;
    uint8_t heater_power;
    uint16_t uptime_s;

    SystemTelemetry() = default;
    ~SystemTelemetry() = default;

    void update(const float measured_temperature,
                const float measured_humidity,
                const uint8_t measured_fan_power,
                const uint8_t measured_heater_power,
                const unsigned long measured_uptime);
};

class SystemAttributes
{
public:
    // --- Enums ---
    enum class SystemMode
    {
        AUTOMATIC,
        MANUAL
    };

    enum class SystemState
    {
        IDLE,
        HEATING
    };

    enum class FilamentType
    {
        UNKNOWN,
        PLA,
        ABS,
        PETG,
    };

private:
    // --- Target Profile Struct ---
    struct TargetProfile
    {
        float target_temperature;
        float target_humidity;
        uint16_t drying_time_s;
    };

    // --- Members ---
    SystemMode system_mode;
    SystemState system_state;
    FilamentType filament_type;

    TargetProfile target_profile;

    // --- Map for pre-defined filament profiles ---
    const std::unordered_map<FilamentType, TargetProfile> filament_profiles_map = {
        {FilamentType::PLA, {45.0, 15.0, 60}},
        {FilamentType::ABS, {65.0, 10.0, 40}},
        {FilamentType::PETG, {60.0, 15.0, 20}}};

public:
    // --- Methods ---

    SystemAttributes() = default;
    ~SystemAttributes() = default;

    void update(const SystemMode set_system_mode,
                const SystemState set_system_state,
                const FilamentType filament_type,
                const TargetProfile target_profile);

    SystemMode getSystemMode(void) const;
    SystemState getSystemState(void) const;
    FilamentType getFilamentType(void) const;

    const TargetProfile *getTargetProfile(void) const;
};

struct SystemFixedAttributes
{
    inline static constexpr char FIRMWARE_VERSION[] = "1.0.0";
    inline static constexpr char UNIVERSITY[] = "Bach Khoa University";
    inline static constexpr char ADDRESS[] = "268 Ly Thuong Kiet, District 10, Ho Chi Minh City";
    inline static constexpr uint8_t CAMPUS = 1;
    inline static constexpr uint8_t FLOOR = 3;
    inline static constexpr char ROOM[] = "309B8";
};

#endif /* SRC_SYSTEM_MANAGER_H_ */