#include "keyboard.h"

void Keyboard::pressKey(uint8_t position) {
    keyboard[position] = true;
    lastKey = position;
    keyWasPressed = true;
}

void Keyboard::releaseKey(uint8_t position) {
    keyboard[position] = false;
}

bool Keyboard::isPressed(uint8_t position) const {
    return keyboard[position];
}

uint8_t Keyboard::getLastKey() const {
    return lastKey;
}

bool Keyboard::getKeyWasPressed() const {
    return keyWasPressed;
}

void Keyboard::clearKeyWasPressed() {
    keyWasPressed = false;
}