#ifndef SRC_INPUT_H_
#define SRC_INPUT_H_

#include <MFRC522.h>

class InputRFID
{
public:
    enum class AuthorizedCard
    {
        CARD_1,
        CARD_2,
        CARD_3,
        UNKNOWN
    };

    enum class AuthorizedKey
    {
        KEY_1,
        KEY_2,
        KEY_3,
        UNKNOWN
    };

private:
    MFRC522 mfrc522;

    const uint8_t RST_PIN;
    const uint8_t SS_PIN;

    static constexpr uint8_t NB_OF_CARD = 3;
    static constexpr uint8_t NB_OF_KEY = 3;

    static constexpr uint8_t authorized_card[NB_OF_CARD][7] = {
        {0x04, 0x5A, 0x67, 0xA2, 0x5C, 0x64, 0x80},
        {0x04, 0x87, 0x10, 0x42, 0x5D, 0x64, 0x80},
        {0x04, 0x87, 0x10, 0x42, 0x5D, 0x64, 0x80}};

    static constexpr uint8_t authorized_key[NB_OF_KEY][4] = {
        {0xAC, 0xC5, 0x5F, 0x9D},
        {0xF3, 0xF5, 0x10, 0x1A},
        {0x92, 0x85, 0x76, 0x1E}};

    void endRFIDSession(void);

public:
    InputRFID(uint8_t RFID_RST_PIN, uint8_t SPI_SS_PIN)
        : RST_PIN(RFID_RST_PIN), SS_PIN(SPI_SS_PIN) {};
    ~InputRFID(void) = default;

    void initialize(void);
    bool isRFIDDetected(void);
    void serialPrintRFIDCode(void); // This function used
    AuthorizedCard checkAuthorizedCard(void);
    AuthorizedKey checkAuthorizedKey(void);
};

#endif /* SRC_INPUT_H_ */