#include "texture.h"

#include <iostream>

bool Texture::init(SDL_Renderer *render , int const width, int const height) {
    this->width = width;
    this->height = height;

    texture = SDL_CreateTexture(
        render,
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STREAMING,
        width,
        height
        );

    if (texture == nullptr) {
        std::cerr << "SDL_CreateTexture error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    return true;
}

void Texture::destroy() const {
    SDL_DestroyTexture(texture);
}

void Texture::lockTexture(void ** pixels, int * pitch) const {
    SDL_LockTexture(texture,NULL, pixels, pitch);
}

void Texture::unlockTexture() const {
    SDL_UnlockTexture(texture);
}

void Texture::update(bool screen[64][32]) const {
    void *pixels;
    int pitch;

    lockTexture(&pixels, &pitch);

    uint8_t *p = static_cast<uint8_t *>(pixels);

    for (int x = 0; x < 64; x++) {
        for (int y = 0; y < 32; y++) {
            const uint8_t color = screen[x][y]? 255 : 0;
            // Jump Y bytes * pitch, then move X * 3 (3 is for RGB24)
            p[y * pitch + x * 3] = color;     //R
            p[y * pitch + x * 3 + 1] = color; //G
            p[y * pitch + x * 3 + 2] = color; //B
        }
    }
    unlockTexture();
}

SDL_Texture * Texture::getTexture() const {
    return texture;
}
