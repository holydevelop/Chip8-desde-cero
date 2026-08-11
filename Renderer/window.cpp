#include <iostream>
#include <ostream>

#include "window.h"

void Window::init(int const width, int const height, const char *title) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title,width,height,0);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
}

void Window::destroy() const {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Window * Window::getWindow() const {
    return window;
}
