
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

    void render(const playfield &pf, const tetromino &t, int x, int y);

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    std::size_t window_width;
    std::size_t window_height;
};


#endif  /* RENDERER_H */
