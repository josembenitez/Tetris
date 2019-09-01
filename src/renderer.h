
#ifndef RENDERER_H
#define RENDERER_H


#include "SDL.h"

#include "playfield.h"
#include "tetromino.h"


class renderer
{
public:
    renderer(std::size_t window_width, std::size_t window_height);
    ~renderer();

    void render(const playfield &pf, const tetromino &t, int x, int y, uint score);

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    std::size_t window_width;
    std::size_t window_height;

    void get_color_coordinates(cell_state st, uint8_t &r, uint8_t &g, uint8_t &b) const;
    void get_color_coordinates(tetromino_color color, uint8_t &r, uint8_t &g, uint8_t &b) const;
};


#endif  /* RENDERER_H */
