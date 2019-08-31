
#include <thread>

#include "controller.h"
#include "game.h"
#include "playfield.h"
#include "tetromino.h"


game::game(std::size_t well_width, std::size_t well_height)
    : pf(playfield(well_width, well_height)),
      x(0),
      y(0),
      current(nullptr),
      engine(dev()),
      random_tetromino(0, 7)
{
}


game::~game()
{
    if (current)
    {
        delete current;
    }
}


void game::run(const controller &cntrllr, renderer &rndrr)
{
    bool running = true;

    get_next_tetromino();

    while (running)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        const input inpt = cntrllr.get_input();
        running = update(inpt);
        rndrr.render(pf, *current, x, y);
    }
}


std::size_t game::drop_down()
{
    std::size_t count = 0;
    while (move_down())
    {
        ++count;
    }
    return count;
}


void game::get_next_tetromino()
{
    if (current)
    {
        delete current;
    }

    const int type = random_tetromino(engine);
    switch (type)
    {
    case 0:
        current = new i_tetromino;
        break;
    
    case 1:
        current = new j_tetromino;
        break;
    
    case 2:
        current = new l_tetromino;
        break;

    case 3:
        current = new o_tetromino;
        break;

    case 4:
        current = new s_tetromino;
        break;
    
    case 5:
        current = new t_tetromino;
        break;
    
    default:
        current = new z_tetromino;
        break;
    }
}


bool game::move_down()
{
    bool success = false;
    if (pf.can_tetromino_move_to(*current, x, y + 1))
    {
        ++y;
        success = true;
    }
    else
    {
        pf.store_tetromino_into(*current, x, y);
        pf.clear_rows();
        get_next_tetromino();
        x = y = 0;
    }
    return success;
}


bool game::move_left()
{
    bool success = false;
    if (pf.can_tetromino_move_to(*current, x - 1, y))
    {
        --x;
        success = true;
    }
    return success;
}


bool game::move_right()
{
    bool success = false;
    if (pf.can_tetromino_move_to(*current, x + 1, y))
    {
        ++x;
        success = true;
    }
    return success;
}


bool game::playfield_is_filled_up() const
{
    return !pf.can_tetromino_move_to(*current, x, y);
}


bool game::rotate_clockwise()
{
    bool success = false;
    current->rotate_clockwise();
    if (pf.can_tetromino_move_to(*current, x, y))
    {
        success = true;
    }
    else
    {
        current->rotate_counterclockwise();
    }
    return success;   
}


bool game::rotate_counterclockwise()
{
    bool success = false;
    current->rotate_counterclockwise();
    if (pf.can_tetromino_move_to(*current, x, y))
    {
        success = true;
    }
    else
    {
        current->rotate_clockwise();
    }
    return success;   
}


bool game::update(input inpt)
{
    bool running = true;

    switch (inpt)
    {
    case input::drop:
        drop_down();
        break;
        
    case input::move_down:
        move_down();
        break;
    
    case input::move_right:
        move_right();
        break;    

    case input::move_left:
        move_left();
        break;

    case input::rotate_clockwise:
        rotate_clockwise();
        break;

    case input::rotate_counterclockwise:
        rotate_counterclockwise();
        break;

    case input::quit:
        running = false;
        break;

    default:
        break;
    }

    return running && !playfield_is_filled_up();
}
