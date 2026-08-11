#include <cstring>

#include "display.h"

// TODO: Revisar logica de draw - XOR sobre pantalla con wrap around y deteccion de colision
bool Display::draw(uint8_t const x, uint8_t const y, const uint8_t* sprite, uint8_t const height) {
    bool collision = false;

    for (int fila = 0; fila < height; fila++) {
        uint8_t byte = sprite[fila];  // leer fila del sprite

        for (int col = 0; col < 8; col++) {
            bool const pixel = (byte >> (7 - col)) & 1;  // extraer bit

            if (pixel) {
                int px = (x + col) % 64;  // wrap horizontal
                int py = (y + fila) % 32; // wrap vertical

                if (screen[px][py]) {
                    collision = true;  // colision
                }

                screen[px][py] ^= true;  // XOR
            }
        }
    }

    return collision;
}

void Display::clear() {
    memset(screen, false, sizeof(screen));
}

bool Display::getPixel(uint8_t const x, uint8_t const y) const {
    return screen[x][y];
}