#include <Arduino.h>
#include "display.h"
#include "TM1637Display.h"

DisplayTM1637::DisplayTM1637(const uint8_t CLK_PIN, const uint8_t DIO_PIN)
    : display(CLK_PIN, DIO_PIN)
{
    display.setBrightness(0x0f);
    display.clear();
}

void DisplayTM1637::clear()
{
    display.clear();
}

void DisplayTM1637::showTempAndHumid(float temperature, float humidity)
{
    display.clear();
    display.showNumberDecEx(round(temperature), 0b01000000, true, 2, 0);
    display.showNumberDecEx(round(humidity), 0b01000000, true, 2, 2);
}