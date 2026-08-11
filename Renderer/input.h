#ifndef CHIP8_INPUT_H
#define CHIP8_INPUT_H

#include <SDL3/SDL_events.h>

#include "../Hardware/keyboard.h"

class Input {
public:
    void handleEvents(SDL_Event &e, Keyboard &keyboard);
};

#endif //CHIP8_INPUT_H