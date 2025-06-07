#include "input.h"

constexpr uint8_t InputRFID::authorized_card[InputRFID::NB_OF_CARD][7];
constexpr uint8_t InputRFID::authorized_key[InputRFID::NB_OF_KEY][4];

void InputRFID::endRFIDSession()
{
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
}

void InputRFID::initialize()
{
    mfrc522.PCD_Init(this->SS_PIN, this->RST_PIN);
    mfrc522.PCD_DumpVersionToSerial(); // Print out to serial version of RFID module
}

bool InputRFID::isRFIDDetected()
{
    return (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial());
}

void InputRFID::serialPrintRFIDCode()
{
    Serial.print(F("Card UID:"));

    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
    }

    Serial.println();

    MFRC522::PICC_Type type = mfrc522.PICC_GetType(mfrc522.uid.sak);
    Serial.print(F("PICC Type: "));
    Serial.println(mfrc522.PICC_GetTypeName(type));

    this->endRFIDSession();
}

InputRFID::AuthorizedCard InputRFID::checkAuthorizedCard()
{
    // print to serial
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();

    // check authorized card
    if (mfrc522.uid.size != 7)
    {
        this->endRFIDSession();
        return AuthorizedCard::UNKNOWN;
    }

    for (uint8_t i = 0; i < NB_OF_CARD; ++i)
    {
        if (memcmp(mfrc522.uid.uidByte, this->authorized_card[i], 7) == 0)
        {
            this->endRFIDSession();
            return static_cast<AuthorizedCard>(i);
        }
    }

    this->endRFIDSession();
    return AuthorizedCard::UNKNOWN;
}

InputRFID::AuthorizedKey InputRFID::checkAuthorizedKey()
{
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();

    // check authorized key
    if (mfrc522.uid.size != 4)
    {
        this->endRFIDSession();
        return AuthorizedKey::UNKNOWN;
    }

    for (uint8_t i = 0; i < NB_OF_KEY; ++i)
    {
        if (memcmp(mfrc522.uid.uidByte, this->authorized_key[i], 4) == 0)
        {
            this->endRFIDSession();
            return static_cast<AuthorizedKey>(i + 1);
        }
    }

    this->endRFIDSession();
    return AuthorizedKey::UNKNOWN;
}