#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_

#include <string>
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
    static constexpr uint16_t LCD_I2C_ADDRESS = 0x21;

    LiquidCrystal_I2C lcd;

public:
    DisplayLCD() : lcd(LCD_I2C_ADDRESS, 16, 2) {};
    ~DisplayLCD() override = default;

    void initialize(void) override;
    void clear(void) override;

    void displayString(uint8_t row, uint8_t col, const std::string &str);
};

#endif /* SRC_DISPLAY_H_ */