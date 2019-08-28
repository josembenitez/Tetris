
#include <iostream>

#include "SDL.h"

#include "playfield.h"
#include "renderer.h"


renderer::renderer(std::size_t window_width, std::size_t window_height)
    : window_width(window_width),
      window_height(window_height)
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


void renderer::render(const playfield &pf, const tetromino &t, int x, int y)
{
    SDL_Rect block;
    block.w = window_width / pf.columns();
    block.h = window_height / pf.rows();

    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Render tetromino
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    const std::vector<int> tetrions = t.to_vector();
    for (std::size_t i = 0; i < tetrions.size(); ++i)
    {
        if (tetrions[i])
        {
            const std::size_t x_t = i % t.bounding_box_size();
            const std::size_t y_t = i / t.bounding_box_size();
            block.x = (x + x_t) * block.w;
            block.y = (y + y_t) * block.h;
            SDL_RenderFillRect(sdl_renderer, &block);
        }
    }

    // Render playfield
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    const std::vector<int> cells = pf.to_vector();
    for (std::size_t i = 0; i < cells.size(); ++i)
    {
        if (cells[i])
        {
            const std::size_t x_c = i % pf.columns();
            const std::size_t y_c = i / pf.columns();
            block.x = x_c * block.w;
            block.y = y_c * block.h;
            SDL_RenderFillRect(sdl_renderer, &block);
        }
    }

    // Update screen
    SDL_RenderPresent(sdl_renderer);
}
