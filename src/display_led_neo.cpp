#include "display.h"

void DisplayLedNeo::initialize()
{
    this->led_neo.begin();
    this->led_neo.show();
}

void DisplayLedNeo::clear()
{
    this->led_neo.clear();
    this->led_neo.show();
}

void DisplayLedNeo::setColor(const uint8_t RED, const uint8_t GREEN, const uint8_t BLUE)
{
    this->led_neo.setPixelColor(this->NUM_LEDS - 1, this->led_neo.Color(RED, GREEN, BLUE));
    this->led_neo.show();
}