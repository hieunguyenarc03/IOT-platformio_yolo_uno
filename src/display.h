#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_

#include <Arduino.h>
#include "TM1637Display.h"

class DisplayTM1637
{
private:
    TM1637Display display;

public:
    DisplayTM1637(const uint8_t CLK_PIN, const uint8_t DIO_PIN);

    void clear(void);
    void showTempAndHumid(float temperature, float humidity);
};

#endif /* SRC_DISPLAY_H_ */