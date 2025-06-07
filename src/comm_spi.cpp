#include "comm.h"

#include <SPI.h>

enum StatusCode CommSPI::initialize()
{
    SPI.begin(this->CLK_PIN, this->MISO_PIN, this->MOSI_PIN);
    
    return STATUS_OK;
}