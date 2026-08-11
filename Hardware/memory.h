#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H

class Memory {
public:
    void boot(char const* rom); //Load the ROM
    void reset(); //Reset buffer
    void write(uint8_t value, uint16_t address); //Write in memory
    [[nodiscard]] const uint8_t* getPointer(uint16_t address) const;
    [[nodiscard]] uint8_t read(uint16_t address) const; //Read in memory
    void loadFonts();
private:
    uint8_t buffer[4096] = {0}; //Locations 0 - 4095 (0xFFF)
    //Should start at 512 (0x200) or 1536 (0x600)
};

#endif //CHIP8_MEMORY_H