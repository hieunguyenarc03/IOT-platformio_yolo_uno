#ifndef SRC_GLOBAL_H_
#define SRC_GLOBAL_H_

#include "Arduino.h"

enum StatusCode
{
    STATUS_OK = 0,
    STATUS_ERROR = -1,
    STATUS_TIMEOUT = -2,
};

#endif /* SRC_GLOBAL_H_ */