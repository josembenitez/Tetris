
#include "SDL.h"

#include "controller.h"


input controller::get_input() const
{
    SDL_Event e;
    input inpt = input::none;

    if (SDL_PollEvent(&e))
    {
        if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                inpt = input::rotate_clockwise;
                break;
            
            case SDLK_DOWN:
                inpt = input::move_down;
                break;

            case SDLK_RIGHT:
                inpt = input::move_right;
                break;

            case SDLK_LEFT:
                inpt = input::move_left;
                break;

            case SDLK_ESCAPE:
                inpt = input::quit;
                break;

            case SDLK_SPACE:
                inpt = input::drop;
                break;

            default:
                break;
            }
        }
    }

    return inpt;
}