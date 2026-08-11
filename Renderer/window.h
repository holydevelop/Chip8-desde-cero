#ifndef CHIP8_WINDOW_H
#define CHIP8_WINDOW_H

#include <SDL3/SDL.h>

class Window {
public:
    void init(int width, int height,const char* title);
    void destroy() const;
    [[nodiscard]] SDL_Window * getWindow() const;
private:
    SDL_Window *window = nullptr;
};

#endif //CHIP8_WINDOW_H