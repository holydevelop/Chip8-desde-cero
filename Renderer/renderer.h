#ifndef CHIP8_RENDERER_H
#define CHIP8_RENDERER_H

#include <SDL3/SDL_render.h>

class Renderer {
public:
    bool init(SDL_Window* window);
    void destroy() const;
    void renderTexture(SDL_Texture *texture) const;
    void renderPresent() const;

    SDL_Renderer * getRender() const;
private:
    SDL_Renderer *render = nullptr;
};

#endif //CHIP8_RENDERER_H