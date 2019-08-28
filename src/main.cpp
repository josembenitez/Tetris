
#include "controller.h"
#include "game.h"
#include "renderer.h"


int main()
{
    constexpr std::size_t scale = 32;
    constexpr std::size_t well_width = 10;
    constexpr std::size_t well_height = 20;
    constexpr std::size_t window_width = scale * well_width;
    constexpr std::size_t window_height = scale * well_height;

    renderer rndrr { window_width, window_height };
    controller cntrllr;
    game g { well_width, well_height };
    g.run(cntrllr, rndrr);
}
