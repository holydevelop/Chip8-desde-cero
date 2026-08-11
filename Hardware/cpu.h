#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H
#include <cstdint>

#include "memory.h"
#include "display.h"
#include "keyboard.h"

class Cpu {
public:
    void init(char const* rom);
    void cycle();

    Display display;
    Keyboard keyboard;
private:
    void decodeExecute (uint16_t opcode);
    //VARIABLES
    uint8_t registers[16] = {0};
    uint16_t index = 0; // Limits 0x000 to 0xFFF (12 Bits)
    uint8_t delayTimer = 0;
    uint8_t soundTimer = 0;
    uint16_t programCounter = 0x200; //Instructions
    uint8_t stackPointer = 0;
    uint16_t stack[16] = {0};
    // NOT CPU BUT INTERACT WITH CONSOLE
    Memory memory;
};

#endif //CHIP8_CPU_H