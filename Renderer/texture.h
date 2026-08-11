#ifndef CHIP8_TEXTURE_H
#define CHIP8_TEXTURE_H

#include <SDL3/SDL.h>

class Texture {
public:
    bool init(SDL_Renderer *render, int width, int height);
    void destroy() const;

    void lockTexture(void ** pixels, int * pitch) const;
    void unlockTexture() const;

    [[nodiscard]] SDL_Texture * getTexture() const;

    void update(bool screen[64][32]) const;
private:
    SDL_Texture* texture = nullptr;
    int width = 0, height = 0;
};


#endif //CHIP8_TEXTURE_H