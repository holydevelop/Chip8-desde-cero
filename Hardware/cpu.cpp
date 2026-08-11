#include <cstdint>
#include <cstdlib>
#include "cpu.h"
#include "keyboard.h"

void Cpu::init(char const* rom) {
    memory.boot(rom);
}

void Cpu::cycle() {
    uint16_t const opcode  = (memory.read(programCounter) << 8) | memory.read(programCounter + 1);
    programCounter += 2;
    decodeExecute(opcode);
    if (delayTimer > 0) delayTimer--;
    if (soundTimer > 0) soundTimer--;
}

void Cpu::decodeExecute(uint16_t const opcode) {
    const uint8_t firstNibble = (opcode & 0xF000) >> 12;
    const uint8_t secondNibble = (opcode & 0x0F00) >> 8;
    const uint8_t thirdNibble = (opcode & 0x00F0) >> 4;
    const uint8_t fourthNibble = (opcode & 0x000F);

    switch(firstNibble) {
        case 0x0:
            if (opcode == 0x00E0) {
                display.clear();
            }

            else if (opcode == 0x00EE) {
                programCounter = stack[stackPointer];
                stackPointer -= 1;
            }
            else {
                programCounter = opcode & 0x0FFF;
            }
            break;
        case 0x1:
            programCounter = opcode & 0x0FFF;
            break;

        case 0x2:
            stackPointer += 1;
            stack[stackPointer] = programCounter;
            programCounter = opcode & 0x0FFF;
            break;
        case 0x3: {
            const uint8_t Vx = registers[secondNibble];
            const uint8_t kk = opcode & 0x00FF;
            if (Vx == kk) {
                programCounter += 2;
            }
            break;
        }
        case 0x4: {
            const uint8_t Vx = registers[secondNibble];
            const uint8_t kk = opcode & 0x00FF;
            if (Vx != kk) {
                programCounter += 2;
            }
            break;
        }
        case 0x5: {
            const uint8_t Vx = registers[secondNibble];
            const uint8_t Vy = registers[thirdNibble];
            if (Vx == Vy) {
                programCounter += 2;
            }
            break;
        }
        case 0x6:
            registers[secondNibble] = opcode & 0x00FF;
            break;
        case 0x7:
            registers[secondNibble] += (opcode & 0x00FF);
            break;
        case 0x8: {
            if (fourthNibble == 0x0) {
                registers[secondNibble] = registers[thirdNibble];
            }
            else if (fourthNibble == 0x1) {
                registers[secondNibble] |= registers[thirdNibble];
            }
            else if (fourthNibble == 0x2) {
                registers[secondNibble] &= registers[thirdNibble];
            }
            else if (fourthNibble == 0x3) {
                registers[secondNibble] ^= registers[thirdNibble];
            }
            else if (fourthNibble == 0x4) {
                const uint16_t result = registers[secondNibble] + registers[thirdNibble];
                registers[0xF] = (result > 0xFF) ? 1 : 0;
                registers[secondNibble] = result & 0xFF;
            }
            else if (fourthNibble == 0x5) {
                const uint16_t result = registers[secondNibble] - registers[thirdNibble];
                registers[0xF] = (registers[secondNibble] > registers[thirdNibble]) ? 1 : 0;
                registers[secondNibble] = result & 0xFF;
            }
            else if (fourthNibble == 0x6) {
                registers[0xF] = (registers[secondNibble] & 1) == 1? 1 : 0;
                registers[secondNibble] >>= 1;
            }
            else if (fourthNibble == 0x7) {
                const uint8_t Vx = registers[secondNibble];
                const uint8_t Vy = registers[thirdNibble];
                registers[0xF] = Vy > Vx? 1 : 0;
                registers[secondNibble] = Vy - Vx;
            }
            else if (fourthNibble == 0xE) {
                registers[0xF] = ((registers[secondNibble] >> 7) & 1) == 1? 1 : 0;
                registers[secondNibble] <<= 1;
            }
            break;
        }
        case 0x9:
            if (fourthNibble == 0x0) {
                if (registers[secondNibble] != registers[thirdNibble]) { programCounter += 2; }
            }
            break;
        case 0xA:
            index = opcode & 0x0FFF;
            break;
        case 0xB:
            programCounter = (opcode & 0x0FFF) + registers[0];
            break;
        case 0xC: {
            const uint8_t random = rand() % 256;
            registers[secondNibble] = random & (opcode & 0x00FF);
            break;
        }
        case 0xD: {
            //Dxyn
            uint8_t Vx = registers[secondNibble];
            uint8_t Vy = registers[thirdNibble];
            registers[0xF] = display.draw(Vx,Vy,memory.getPointer(index),fourthNibble) ? 1 : 0;
            break;
        }
        case 0xE:
            if (thirdNibble == 0x9 && fourthNibble == 0xE) {
                if (keyboard.isPressed(registers[secondNibble])) {
                    programCounter += 2;
                }
            }
            else if (thirdNibble == 0xA && fourthNibble == 0x1) {
                if (!keyboard.isPressed(registers[secondNibble])) {
                    programCounter += 2;
                }
            }
            break;
        case 0xF: {
            if (thirdNibble == 0 && fourthNibble == 0x7) {
                registers[secondNibble] = delayTimer;
            }
            else if (thirdNibble == 0x0 && fourthNibble == 0xA) {
                if (!keyboard.getKeyWasPressed()) {
                    programCounter -= 2;  // esperar hasta que se presione una tecla
                } else {
                    registers[secondNibble] = keyboard.getLastKey();
                    keyboard.clearKeyWasPressed();
                }
            }
            else if (thirdNibble == 0x1 && fourthNibble == 0x5) {
                delayTimer = registers[secondNibble];
            }
            else if (thirdNibble == 0x1 && fourthNibble == 0x8) {
                soundTimer = registers[secondNibble];
            }
            else if (thirdNibble == 0x1 && fourthNibble == 0xE) {
                index += registers[secondNibble];
            }
            else if (thirdNibble == 0x2 && fourthNibble == 0x9) {
                index = registers[secondNibble] * 5;
            }
            else if (thirdNibble == 0x3 && fourthNibble == 0x3) {
                memory.write(registers[secondNibble] / 100 , index);
                memory.write((registers[secondNibble] / 10) % 10 , index + 1);
                memory.write(registers[secondNibble] % 10 , index + 2);
            }
            else if (thirdNibble == 0x5 && fourthNibble == 0x5) {
                for (int i = 0; i <= secondNibble; i++) {
                    memory.write(registers[i], index + i);
                }
            }
            else if (thirdNibble == 0x6 && fourthNibble == 0x5) {
                for (int i = 0; i <= secondNibble; i++) {
                    registers[i] = memory.read(index + i);
                }
            }
            break;
        }
    }
}
