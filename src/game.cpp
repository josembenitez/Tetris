
#include <iostream>
#include <thread>

#include "controller.h"
#include "game.h"
#include "playfield.h"
#include "tetromino.h"


void print_tetromino(const tetromino &t)
{
    std::vector<int> tetrions = t.to_vector();
    for (std::size_t i = 0; i < tetrions.size(); ++i)
    {
        std::cout << tetrions[i] << ", ";
        if ((i + 1) % t.bounding_box_size() == 0)
        {
            std::cout << '\n';
        }
    }
}


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
        std::cout << "New I tetromino...\n";
        break;
    
    case 1:
        current = new j_tetromino;
        std::cout << "New J tetromino...\n";
        break;
    
    case 2:
        current = new l_tetromino;
        std::cout << "New L tetromino...\n";
        break;

    case 3:
        current = new o_tetromino;
        std::cout << "New O tetromino...\n";
        break;

    case 4:
        current = new s_tetromino;
        std::cout << "New S tetromino...\n";
        break;
    
    case 5:
        current = new t_tetromino;
        std::cout << "New T tetromino...\n";
        break;
    
    default:
        current = new z_tetromino;
        std::cout << "New Z tetromino...\n";
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
        std::cout << "Touching ground...\n";
        pf.store_tetromino_into(*current, x, y);
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
        current->rotate_counter_clockwise();
    }
    return success;   
}


bool game::update(input inpt)
{
    bool running = true;

    switch (inpt)
    {
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

    case input::quit:
        running = false;
        break;

    default:
        break;
    }

    return running && !playfield_is_filled_up();
}
