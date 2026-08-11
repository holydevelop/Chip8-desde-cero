#ifndef CHIP8_DISPLAY_H
#define CHIP8_DISPLAY_H
#include <cstdint>

class Display {
public:
    bool draw(uint8_t x, uint8_t y, const uint8_t *sprite, uint8_t height);
    void clear();
    [[nodiscard]] bool getPixel(uint8_t x, uint8_t y) const;

    bool screen[64][32] = {false};
};

#endif //CHIP8_DISPLAY_H