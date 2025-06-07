#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_

#include <string>
#include <Adafruit_NeoPixel.h>
#include "global.h"
#include "LiquidCrystal_I2C.h"

class Display
{
public:
    virtual ~Display() = default;

    virtual void initialize(void) = 0;
    virtual void clear(void) = 0;
};

class DisplayLCD : public Display
{
private:
    static constexpr uint16_t I2C_ADDRESS = 0x21;

    LiquidCrystal_I2C lcd;

public:
    DisplayLCD() : lcd(I2C_ADDRESS, 16, 2) {};
    ~DisplayLCD() override = default;

    void initialize(void) override;
    void clear(void) override;

    void displayString(uint8_t row, uint8_t col, const std::string &str);
};

class DisplayLedNeo : public Display
{
private:
    const uint8_t PIN;
    inline static constexpr uint8_t NUM_LEDS = 1;
    Adafruit_NeoPixel led_neo;

public:
    DisplayLedNeo(const uint8_t LED_PIN) : PIN(LED_PIN),
                                           led_neo(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800) {};
    ~DisplayLedNeo() override = default;

    void initialize(void) override;
    void clear(void) override;
    void setColor(const uint8_t RED, const uint8_t GREEN, const uint8_t BLUE);
};

#endif /* SRC_DISPLAY_H_ */