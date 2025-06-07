#include "display.h"

void DisplayLCD::initialize()
{
    lcd.init();
    lcd.backlight();
}

void DisplayLCD::clear()
{
    lcd.clear();
}

void DisplayLCD::displayString(uint8_t row, uint8_t col, const std::string &str)
{
    row = ((row > 1) ? 1 : row);
    col = ((col > 15) ? 15 : col);

    lcd.setCursor(col, row);
    lcd.print(str.c_str());
}