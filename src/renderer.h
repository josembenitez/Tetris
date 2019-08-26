
#ifndef RENDERER_H
#define RENDERER_H


#include "SDL.h"


class renderer
{
public:
    renderer(std::size_t window_width, std::size_t window_height,
             std::size_t well_width, std::size_t well_height);
    ~renderer();

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    std::size_t window_width;
    std::size_t window_height;
    std::size_t well_width;
    std::size_t well_height;
};


#endif  /* RENDERER_H */
