
#include <iostream>
#include <map>

#include "SDL.h"

#include "playfield.h"
#include "renderer.h"
#include "tetromino.h"


const std::map<cell_state, tetromino_color> renderer::colormap = {
    { cell_state::filled_with_i, i_tetromino().color(), },
    { cell_state::filled_with_j, j_tetromino().color(), },
    { cell_state::filled_with_l, l_tetromino().color(), },
    { cell_state::filled_with_o, o_tetromino().color(), },
    { cell_state::filled_with_s, s_tetromino().color(), },
    { cell_state::filled_with_t, t_tetromino().color(), },
    { cell_state::filled_with_z, z_tetromino().color(), },
};


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
        std::cerr << "Hardware Accelearted Renderer could not be created.\n";
        std::cerr << "Using Software renderer.\n";
        sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_SOFTWARE);
        if (sdl_renderer == nullptr)
        {
            std::cerr << "Software Renderer could not be created.\n";
            std::cerr << "SDL_Error: " << SDL_GetError() << '\n';
        }
    }
}


renderer::~renderer()
{
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}


void renderer::render(const playfield &pf, const tetromino &t, int x, int y, uint score, uint level)
{
    const std::size_t cell_width = window_width / pf.columns();
    const std::size_t cell_height = window_height / pf.rows();

    render_background(cell_width, cell_height);
    render_tetromino(t, x, y, cell_width, cell_height);
    render_playfield(pf, cell_width, cell_height);

    // Update window title with the current score
    const std::string title { "Tetris - Score: " + std::to_string(score) + ", Level: " + std::to_string(level) };
    SDL_SetWindowTitle(sdl_window, title.c_str());

    // Update screen
    SDL_RenderPresent(sdl_renderer);
}


void renderer::get_color_coordinates(cell_state st, uint8_t &r, uint8_t &g, uint8_t &b) const
{
    tetromino_color color;

    if (st == cell_state::empty)
    {
        r = 0x1E, g = 0x1E, b = 0x1E;
        return;
    }
    else
    {
        get_color_coordinates(colormap.at(st), r, g, b);
    }
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


void renderer::render_background(std::size_t cell_width, std::size_t cell_height)
{
    uint8_t r = 0x0, g = 0x0, b = 0x0;

    // Clear screen with "empty" color
    get_color_coordinates(cell_state::empty, r, g, b);
    SDL_SetRenderDrawColor(sdl_renderer, r, g, b, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Draw some grid lines to help the player
    SDL_SetRenderDrawColor(sdl_renderer, 0x4E, 0x4E, 0x4E, 0xFF);
    for (std::size_t x = cell_width; x < window_width; x += cell_width)
    {
        SDL_RenderDrawLine(sdl_renderer, x, 0, x, window_height);
    }
    for (std::size_t y = cell_height; y < window_height; y += cell_height)
    {
        SDL_RenderDrawLine(sdl_renderer, 0, y, window_width, y);
    }
}


void renderer::render_playfield(const playfield &pf, std::size_t cell_width, std::size_t cell_height)
{
    uint8_t r = 0x0, g = 0x0, b = 0x0;

    SDL_Rect block;
    block.w = cell_width;
    block.h = cell_height;

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
}


void renderer::render_tetromino(const tetromino &t, int x, int y, std::size_t cell_width, std::size_t cell_height)
{
    uint8_t r = 0x0, g = 0x0, b = 0x0;

    SDL_Rect block;
    block.w = cell_width;
    block.h = cell_height;

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
}
