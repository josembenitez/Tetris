
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
    uint8_t r = 0x0, g = 0x0, b = 0x0;

    SDL_Rect block;
    block.w = window_width / pf.columns();
    block.h = window_height / pf.rows();

    // Clear screen
    get_color_coordinates(cell_state::empty, r, g, b);
    SDL_SetRenderDrawColor(sdl_renderer, r, g, b, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Render tetromino
    get_color_coordinates(t.color(), r, g, b);
    SDL_SetRenderDrawColor(sdl_renderer, r, g, b, 0xFF);
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
    const auto cells = pf.to_vector();
    for (std::size_t i = 0; i < cells.size(); ++i)
    {
        if (cells[i] != cell_state::empty)
        {
            const std::size_t x_c = i % pf.columns();
            const std::size_t y_c = i / pf.columns();
            block.x = x_c * block.w;
            block.y = y_c * block.h;
            get_color_coordinates(cells[i], r, g, b);
            SDL_SetRenderDrawColor(sdl_renderer, r, g, b, 0xFF);
            SDL_RenderFillRect(sdl_renderer, &block);
        }
    }

    // Update screen
    SDL_RenderPresent(sdl_renderer);
}


void renderer::get_color_coordinates(cell_state st, uint8_t &r, uint8_t &g, uint8_t &b) const
{
    tetromino_color color;

    switch (st)
    {
    case cell_state::filled_with_i:
        color = i_tetromino().color();
        break;
    
    case cell_state::filled_with_j:
        color = j_tetromino().color();
        break;
    
    case cell_state::filled_with_l:
        color = l_tetromino().color();
        break;
    
    case cell_state::filled_with_o:
        color = o_tetromino().color();
        break;
    
    case cell_state::filled_with_s:
        color = s_tetromino().color();
        break;
    
    case cell_state::filled_with_t:
        color = t_tetromino().color();
        break;
    
    case cell_state::filled_with_z:
        color = z_tetromino().color();
        break;
    
    case cell_state::empty:
        r = 0x1E, g = 0x1E, b = 0x1E;
        return;
    }

    get_color_coordinates(color, r, g, b);
}


void renderer::get_color_coordinates(tetromino_color color, uint8_t &r, uint8_t &g, uint8_t &b) const
{
    switch (color)
    {
    case tetromino_color::cyan:
        r = 0x0, g = 0xFF, b = 0xFF;
        break;
    
    case tetromino_color::blue:
        r = 0x0, g = 0x0, b = 0xFF;
        break;
    
    case tetromino_color::orange:
        r = 0xFF, g = 0x7F, b = 0x0;
        break;
    
    case tetromino_color::yellow:
        r = 0xFF, g = 0xFF, b = 0x0;
        break;
    
    case tetromino_color::green:
        r = 0x0, g = 0xFF, b = 0x0;
        break;
    
    case tetromino_color::purple:
        r = 0x80, g = 0x0, b = 0x80;
        break;
    
    case tetromino_color::red:
        r = 0xFF, g = 0x0, b = 0x0;
        break;
    
    default:
        break;
    }
}
