
#include <iostream>

#include "SDL.h"

#include "renderer.h"


renderer::renderer(std::size_t window_width, std::size_t window_height,
                   std::size_t well_width, std::size_t well_height)
    : window_width(window_width), window_height(window_height),
      well_width(well_width), well_height(well_height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << '\n';
    }

    sdl_window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, window_width,
                                  window_height, SDL_WINDOW_SHOWN);
    if (sdl_window == nullptr)
    {
        std::cerr << "Window could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << '\n';
    }

    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (sdl_renderer == nullptr)
    {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << '\n';
    }
}


renderer::~renderer()
{
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}
