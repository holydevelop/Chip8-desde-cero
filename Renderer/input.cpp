#include "input.h"

void Input::handleEvents(SDL_Event &e, Keyboard &keyboard) {
    if (e.type == SDL_EVENT_KEY_DOWN) {
        switch (e.key.key) {
            case SDLK_1: keyboard.pressKey(0x1); break;
            case SDLK_2: keyboard.pressKey(0x2); break;
            case SDLK_3: keyboard.pressKey(0x3); break;
            case SDLK_4: keyboard.pressKey(0xC); break;
            case SDLK_Q: keyboard.pressKey(0x4); break;
            case SDLK_W: keyboard.pressKey(0x5); break;
            case SDLK_E: keyboard.pressKey(0x6); break;
            case SDLK_R: keyboard.pressKey(0xD); break;
            case SDLK_A: keyboard.pressKey(0x7); break;
            case SDLK_S: keyboard.pressKey(0x8); break;
            case SDLK_D: keyboard.pressKey(0x9); break;
            case SDLK_F: keyboard.pressKey(0xE); break;
            case SDLK_Z: keyboard.pressKey(0xA); break;
            case SDLK_X: keyboard.pressKey(0x0); break;
            case SDLK_C: keyboard.pressKey(0xB); break;
            case SDLK_V: keyboard.pressKey(0xF); break;
        }
    }
    if (e.type == SDL_EVENT_KEY_UP) {
        switch (e.key.key) {
            case SDLK_1: keyboard.releaseKey(0x1); break;
            case SDLK_2: keyboard.releaseKey(0x2); break;
            case SDLK_3: keyboard.releaseKey(0x3); break;
            case SDLK_4: keyboard.releaseKey(0xC); break;
            case SDLK_Q: keyboard.releaseKey(0x4); break;
            case SDLK_W: keyboard.releaseKey(0x5); break;
            case SDLK_E: keyboard.releaseKey(0x6); break;
            case SDLK_R: keyboard.releaseKey(0xD); break;
            case SDLK_A: keyboard.releaseKey(0x7); break;
            case SDLK_S: keyboard.releaseKey(0x8); break;
            case SDLK_D: keyboard.releaseKey(0x9); break;
            case SDLK_F: keyboard.releaseKey(0xE); break;
            case SDLK_Z: keyboard.releaseKey(0xA); break;
            case SDLK_X: keyboard.releaseKey(0x0); break;
            case SDLK_C: keyboard.releaseKey(0xB); break;
            case SDLK_V: keyboard.releaseKey(0xF); break;
        }
    }
}
