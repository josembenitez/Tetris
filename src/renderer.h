
#ifndef RENDERER_H
#define RENDERER_H


#include <map>
#include <optional>

#include "SDL.h"


class playfield;
class tetromino;
enum class tetromino_color;


/**
 * Class defining a renderer for the game.
 */
class renderer
{
public:
    /**
     * Builds an instance of this class with the givn parameters.
     * 
     * @param window_width Width (in pixels) of the game window.
     * @param window_height Height (in pixels) of the game window.
     */
    renderer(std::size_t window_width, std::size_t window_height);
    /**
     * Destructor.
     */
    ~renderer();

    /**
     * Renders the given game state on to the screen.
     * 
     * @param pf The given playfield
     * @param t The current falling tetromino.
     * @param x The x-coordinate of the given tetromino.
     * @param y The y-coordinate of the given tetromino.
     * @param score The current user score.
     * @param level The current game level.
     */
    void render(const playfield &pf, const tetromino &t, int x, int y, uint score, uint level);

private:
    /**
     * Handle to an SDL window.
     */
    SDL_Window *sdl_window;
    /**
     * Handle to an SDL renderer.
     */
    SDL_Renderer *sdl_renderer;
    /**
     * Width (in pixels) of the game window.
     */
    std::size_t window_width;
    /**
     * Height (in pixels) of the game window.
     */
    std::size_t window_height;

    /**
     * Retrieves the RGB values for the given tetromino color.
     * 
     * @param color The given tetromino color as defined by #tetromino_color.
     * @param r The desired red component.
     * @param g The desired green component.
     * @param b The desired blue component.
     */
    void get_color_coordinates(std::optional<tetromino_color> color,
                               uint8_t &r, uint8_t &g, uint8_t &b) const;
    /**
     * Renders the window's background.
     * 
     * @param cell_width Width (in pixels) of a playfield cell.
     * @param cell_height Height (in pixels) of a playfield cell.
     */
    void render_background(std::size_t cell_width, std::size_t cell_height);
    /**
     * Renders the given playfield on to the screen.
     * 
     * @param cell_width Width (in pixels) of a playfield cell.
     * @param cell_height Height (in pixels) of a playfield cell.
     */
    void render_playfield(const playfield &pf, std::size_t cell_width, std::size_t cell_height);
    /**
     * Renders the given tetromino on to the screen.
     * 
     * @param cell_width Width (in pixels) of a playfield cell.
     * @param cell_height Height (in pixels) of a playfield cell.
     */
    void render_tetromino(const tetromino &t, int x, int y, std::size_t cell_width, std::size_t cell_height);
};


#endif  /* RENDERER_H */
