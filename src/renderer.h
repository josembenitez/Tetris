
#ifndef RENDERER_H
#define RENDERER_H


#include "SDL.h"


class renderer
{
public:
    renderer();
    ~renderer();

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
};


#endif  /* RENDERER_H */
