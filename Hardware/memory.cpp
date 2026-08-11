#include <cstdint>
#include <cstring>
#include <fstream>

#include "memory.h"

#define START_ADDRESS 0x200
#define MEMORY_SIZE 4096

void Memory::boot(char const* romDir) {
    reset(); //Always restart the memory
    loadFonts(); //Load fonts
    // Open the file as a stream of binary and move the file pointer to the end
    std::ifstream file(romDir, std::ios::binary | std::ios::ate);
    if (file.is_open()) {
        std::streampos size = file.tellg();
        char* rom = new char[size];

        file.seekg(0, std::ios::beg);
        file.read(rom, size);
        file.close();

        for (int i = 0; i < size; i++) {
            write(rom[i],START_ADDRESS + i);
        }
        delete[] rom;
    }
}

void Memory::reset() {
    memset(buffer, 0, sizeof(buffer));
}

void Memory::write(const uint8_t value, const uint16_t address) {
    buffer[address] = value;
}

uint8_t Memory::read(const uint16_t address) const {
    return buffer[address];
}

const uint8_t *Memory::getPointer(uint16_t address) const {
    return &buffer[address];
}

void Memory::loadFonts() {
    const uint8_t fonts[] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    for (int i = 0; i < sizeof(fonts); i++) {
        buffer[0x000 + i] = fonts[i];
    }
}
