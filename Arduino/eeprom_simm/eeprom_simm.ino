/*
*    Example-Code that emulates a DS2431 1024 bits EEPROM
*
*   Tested with
*    - DS9490R-Master, atmega328@16MHz and teensy3.2@96MHz as Slave
*    - tested on buspirate and two different real 1-wire masters (DS9490 and a PIC18-Device)
*/

#include <EEPROM-Storage.h>
#include "OneWireHub.h"
#include "DS2433.h"

constexpr uint8_t pin_onewire   { 8 };

//EEPROMStorage<OneWireHub> hub(0, OneWireHub(pin_onewire));       // This variable is stored in EEPROM at positions 0
 OneWireHub hub = OneWireHub(pin_onewire);

auto ds2433 = DS2433(0xB3, 0x85, 0x2F, 0x0F, 0xD0, 0x14, 0x10);
// 0xB3, 0x85, 0x2F, 0x0F, 0xD0, 0x14, 0x10, 0x9B

void setup()
{
    Serial.begin(9600);
    Serial.println("OneWire-Hub DS2433");

    // Setup OneWire
    hub.attach(ds2433);

    Serial.println("config done");
}

void loop()
{
    // following function must be called periodically
    hub.poll();
} 
