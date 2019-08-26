
#include <iostream>

#include "controller.h"
#include "game.h"
#include "playfield.h"
#include "tetromino.h"


game::game()
    : pf(playfield(10, 20)),
      x(0),
      y(0),
      engine(dev()),
      random_tetromino(0, 7)
{

}


void game::run(const controller &cntrllr, renderer &rndrr)
{
    bool gameover = false;

    while (!gameover)
    {
        const input inpt = cntrllr.get_input();
        gameover = update(inpt);
        /* render */
    }
}


void game::create_tetromino(tetromino &t)
{
    const int type = random_tetromino(engine);
    switch (type)
    {
    case 0:
        break;
    
    default:
        break;
    }
}


bool game::update(input inpt)
{
    bool quit = false;

    switch (inpt)
    {
    case input::move_down:
        std::cout << "Moving down...\n";
        break;
    
    case input::move_right:
        std::cout << "Moving right...\n";
        break;

    case input::move_left:
        std::cout << "Moving left...\n";
        break;

    case input::rotate_clockwise:
        std::cout << "Quiting...\n";
        quit = true;
        break;

    default:
        break;
    }

    return quit;
}
