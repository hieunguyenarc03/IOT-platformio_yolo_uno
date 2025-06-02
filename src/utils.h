#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include "global.h"

void createTelemetryJson(float temperature, float humidity, uint8_t fan_speed, uint8_t heater_power,
                         char *buffer_out, size_t const buffer_size);

#endif /* SRC_UTILS_H_ */