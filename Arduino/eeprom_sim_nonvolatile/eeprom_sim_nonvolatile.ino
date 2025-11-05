/*
*    Example-Code that emulates a DS2431 1024 bits EEPROM
*
*   Tested with
*    - DS9490R-Master, atmega328@16MHz and teensy3.2@96MHz as Slave
*    - tested on buspirate and two different real 1-wire masters (DS9490 and a PIC18-Device)
*/


#include "OneWireHub.h"
#include <EEPROM.h>
#include "OneWireItem.h"

class DS2433 : public OneWireItem
{

  public:

    static constexpr uint16_t MEM_SIZE          { 512 };
    static constexpr uint16_t MEM_MASK          { 0x01FF };

    static constexpr uint8_t  PAGE_SIZE         { 32 };
    static constexpr uint16_t PAGE_COUNT        { MEM_SIZE / PAGE_SIZE };
    static constexpr uint8_t  PAGE_MASK         { 0b00011111 };

    static constexpr uint8_t  REG_ES_PF_MASK    { 0b00100000 }; // partial byte flag
    static constexpr uint8_t  REG_ES_ZERO_MASK  { 0b01000000 }; // reads always zero
    static constexpr uint8_t  REG_ES_AA_MASK    { 0b10000000 }; // authorization accepted (data copied to target memory)

    uint8_t memory[MEM_SIZE]; // 4kbit max storage
    uint8_t scratchpad[PAGE_SIZE];

DS2433(uint8_t ID1, uint8_t ID2, uint8_t ID3, uint8_t ID4, uint8_t ID5, uint8_t ID6, uint8_t ID7) : OneWireItem(ID1, ID2, ID3, ID4, ID5, ID6, ID7)
{
    static_assert(sizeof(memory) < 65535,  "Implementation does not cover the whole address-space");
    clearScratchpad();
}

void duty(OneWireHub * const hub)
{
    constexpr uint8_t ALTERNATE_01 { 0b10101010 };

    static uint16_t reg_TA { 0 }; // contains TA1, TA2 (Target Address)
    static uint8_t  reg_ES { 31 };  // E/S register

    uint8_t  data, cmd;
    uint16_t crc { 0 };

    if (hub->recv(&cmd,1,crc))  return;

    switch (cmd)
    {
        case 0x0F:      // WRITE SCRATCHPAD COMMAND

            if (hub->recv(reinterpret_cast<uint8_t *>(&reg_TA),2,crc)) return;
            reg_TA &= MEM_MASK; // make sure to stay in boundary
            reg_ES = uint8_t(reg_TA) & PAGE_MASK; // register-offset

            // receive up to 8 bytes of data
            for (; reg_ES < PAGE_SIZE; ++reg_ES)
            {
                if (hub->recv(&scratchpad[reg_ES], 1, crc))
                {
                    if (hub->getError() == Error::AWAIT_TIMESLOT_TIMEOUT_HIGH) reg_ES |= REG_ES_PF_MASK;
                    break;
                }
            }
            reg_ES--;
            reg_ES &= PAGE_MASK;

            if (hub->getError() == Error::NO_ERROR)  // try to send crc if wanted
            {
                crc = ~crc; // normally crc16 is sent ~inverted
                hub->send(reinterpret_cast<uint8_t *>(&crc), 2);
            }
            break;

        case 0x55:      // COPY SCRATCHPAD

            if (hub->recv(&data)) return; // TA1
            if (data != reinterpret_cast<uint8_t *>(&reg_TA)[0]) return;
            if (hub->recv(&data)) return;  // TA2
            if (data != reinterpret_cast<uint8_t *>(&reg_TA)[1]) return;
            if (hub->recv(&data)) return;  // ES
            if (data != reg_ES) return;

            if ((reg_ES & REG_ES_PF_MASK) != 0)                  break; // stop if error occurred earlier

            reg_ES |= REG_ES_AA_MASK; // compare was successful

            {    // Write Scratchpad to memory, writing takes about 5ms
                const uint8_t start  = uint8_t(reg_TA) & PAGE_MASK;
                const uint8_t length = (reg_ES & PAGE_MASK)+ uint8_t(1) - start;
                writeMemory(&scratchpad[start], length, reg_TA);
            }

            noInterrupts();

            do
            {
                hub->clearError();
                hub->sendBit(true); // send passive 1s
            }
            while   (hub->getError() == Error::AWAIT_TIMESLOT_TIMEOUT_HIGH); // wait for timeslots

            interrupts();

            while (!hub->send(&ALTERNATE_01)); // send alternating 1 & 0 after copy is complete
            break;

        case 0xAA:      // READ SCRATCHPAD COMMAND

            if (hub->send(reinterpret_cast<uint8_t *>(&reg_TA),2))  return;
            if (hub->send(&reg_ES,1)) return;

            {   // send Scratchpad content
                const uint8_t start  = uint8_t(reg_TA) & PAGE_MASK;
                const uint8_t length = PAGE_SIZE - start;
                if (hub->send(&scratchpad[start],length))   return;
            }
            return; // datasheed says we should send all 1s, till reset (1s are passive... so nothing to do here)

        case 0xF0:      // READ MEMORY

            if (hub->recv(reinterpret_cast<uint8_t *>(&reg_TA),2)) return;

            for (uint16_t i = reg_TA; i < MEM_SIZE; i+=PAGE_SIZE) // model of the 32byte scratchpad
            {
                if (hub->send(&memory[i],PAGE_SIZE)) return;
            }
            return; // datasheed says we should send all 1s, till reset (1s are passive... so nothing to do here)

        default:

            hub->raiseSlaveError(cmd);
    }
}

void clearMemory(void)
{
//stop this, you could have had non volitile memory, why did you think there was ever a need for this function????
}

void clearScratchpad(void)
{
memset(scratchpad, static_cast<uint8_t>(0x00), PAGE_SIZE);
}

bool writeMemory(const uint8_t* const source, const uint16_t length, const uint16_t position1)
{
    if (position1 >= MEM_SIZE) return false;
    const uint16_t _length = (position1 + length >= MEM_SIZE) ? (MEM_SIZE - position1) : length;
    EEPROM.put(memory[position1],source);
    return true;
}

bool readMemory(const uint8_t* const destination, const uint16_t length, uint16_t position1)
{
    if (position1 >= MEM_SIZE) return false;
    const uint16_t _length = (position1 + length >= MEM_SIZE) ? (MEM_SIZE - position1) : length;
    EEPROM.get(memory[position1], destination);
    return (_length==length);
}
};


constexpr uint8_t pin_onewire   { 8 };

//EEPROMStorage<OneWireHub> hub(0, OneWireHub(pin_onewire));       // This variable is stored in EEPROM at positions 0
auto hub = OneWireHub(pin_onewire);

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
