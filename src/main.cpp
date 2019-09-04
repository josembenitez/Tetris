
#include "controller.h"
#include "game.h"
#include "renderer.h"


int main()
{
    /**
     * Scale factor to size the window based on playfield dimensions.
     */
    constexpr std::size_t scale = 32;
    /**
     * Playfield width (in cells).
     */
    constexpr std::size_t well_width = 10;
    /**
     * Playfield height (in cells).
     */
    constexpr std::size_t well_height = 20;
    /**
     * Window width (in pixels).
     */
    constexpr std::size_t window_width = scale * well_width;
    /**
     * Window height (in pixels).
     */
    constexpr std::size_t window_height = scale * well_height;
    /**
     * Desired frame rate (in frames per second).
     */
    constexpr std::size_t fps = 60;

    renderer rndrr { window_width, window_height };
    controller cntrllr;
    game g { well_width, well_height };
    g.run(cntrllr, rndrr, fps);
}
