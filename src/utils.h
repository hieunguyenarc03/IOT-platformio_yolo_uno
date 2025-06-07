#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include "global.h"
#include "system_manager.h"

void createTelemetryJson(const struct SystemTelemetry *system_telemetry,
                         char *buffer_out, size_t const buffer_size);

void createAttributesJson(const struct SystemAttributes *system_attributes,
                          const struct SystemFixedAttributes *system_fixed_attributes,
                          char *buffer_out, size_t const buffer_size);

#endif /* SRC_UTILS_H_ */