#ifndef CHIP8_KEYBOARD_H
#define CHIP8_KEYBOARD_H
#include <cstdint>

class Keyboard {
public:
    void pressKey(uint8_t position);
    void releaseKey(uint8_t position);
    bool isPressed(uint8_t position) const;
    [[nodiscard]] uint8_t getLastKey() const;

    bool getKeyWasPressed() const;
    void clearKeyWasPressed();
private:
    bool keyboard[16] = {false};
    uint8_t lastKey = 0x0;
    bool keyWasPressed = false;
};

#endif //CHIP8_KEYBOARD_H