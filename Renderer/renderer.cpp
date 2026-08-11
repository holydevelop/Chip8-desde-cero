#include <iostream>

#include "renderer.h"

bool Renderer::init(SDL_Window *window) {
    render = SDL_CreateRenderer(window,NULL);
    //Error catch - Renderer
    if (render == nullptr) {
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Renderer::destroy() const {
    SDL_DestroyRenderer(render);
}

void Renderer::renderTexture(SDL_Texture *texture) const {
    SDL_RenderTexture(render, texture, NULL, NULL);
}

void Renderer::renderPresent() const {
    SDL_RenderPresent(render);
}

SDL_Renderer * Renderer::getRender() const {
    return render;
}
