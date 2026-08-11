#include <iostream>
#include <string>

#include <SDL3/SDL.h>

#include "./Hardware/cpu.h"
#include "./Renderer/window.h"
#include "./Renderer/renderer.h"
#include "./Renderer/texture.h"
#include "./Renderer/input.h"

using namespace std;

#define WIDTH 64
#define HEIGHT 32

#define MAX_FPS 144
#define FRAME_TIME (1000/MAX_FPS) //1000ms equivale a 1 segundo , y son 60 fps

int main(int argc, char* argv[]) {
    //Declare console Chip8 emulation
    Cpu chip8; // Call CPU
    string romDir; // Rom direction

    //Window Screen
    Window window;
    Renderer render;
    Texture texture;
    Input input;

    if (argc < 2) {
        std::cerr << "Usage: Chip8.exe <rom_path>" << std::endl;
        return 1;
    }

    chip8.init(argv[1]);

    window.init(800, 600,"Chip 8");
    render.init(window.getWindow());
    texture.init(render.getRender(),WIDTH,HEIGHT);

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            //Quit Event
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            input.handleEvents(e,chip8.keyboard);
        }
        //Cycle of CPU
        chip8.cycle();
        //Renderer cycle
        texture.update(chip8.display.screen);
        render.renderTexture(texture.getTexture());
        render.renderPresent();
        SDL_Delay(FRAME_TIME);
    }
    return 0;
}