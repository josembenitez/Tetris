
#include <chrono>
#include <thread>

#include "controller.h"
#include "game.h"
#include "playfield.h"
#include "tetromino.h"


game::game(std::size_t well_width, std::size_t well_height)
    : gameover(false),
      quit(false),
      delay(0),
      score(0),
      cleared_lines(0),
      level(1),
      pf(playfield(well_width, well_height)),
      x(0),
      y(0),
      current(nullptr),
      last_update(std::chrono::system_clock::now()),
      engine(dev()),
      random_tetromino(0, 7)
{
    update_delay();
}


game::~game()
{
    if (current)
    {
        delete current;
    }
}


void game::run(const controller &cntrllr, renderer &rndrr, std::size_t fps)
{
    const std::size_t target_frame_duration = 1000 / fps;
    bool running = true;

    get_next_tetromino();

    while (!gameover && !quit)
    {
        const auto frame_start = std::chrono::system_clock::now();

        const input inpt = cntrllr.get_input();
        update(inpt);
        rndrr.render(pf, *current, x, y, score, level);

        const auto frame_end = std::chrono::system_clock::now();
        const auto frame_duration = std::chrono::duration_cast<std::chrono::milliseconds>(frame_end - frame_start).count();
        if (frame_duration < target_frame_duration)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(target_frame_duration - frame_duration));
        }
    }

    if (!quit)
    {
        while (cntrllr.get_input() != input::quit);
    }
}


std::size_t game::drop_down()
{
    std::size_t count = 0;
    while (move_down())
    {
        ++count;
    }
    update_score(0, count);
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

    x = (pf.columns() - current->bounding_box_size()) / 2;
    y = 0;

    last_update = std::chrono::system_clock::now();
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
        const std::size_t count = pf.clear_rows();
        update_score(count, 0);
        update_level(count);
        get_next_tetromino();
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


void game::update(input inpt)
{
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

    case input::none:
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_update).count() > delay)
        {
            move_down();
            last_update = std::chrono::system_clock::now();
        }
        break;

    case input::quit:
        quit = true;
        break;

    default:
        break;
    }

    gameover = playfield_is_filled_up();
}


void game::update_delay()
{
    delay = ((max_level + 1 - level) * delay_interval);
}


void game::update_level(std::size_t lines)
{
    if (level < max_level)
    {
        cleared_lines += lines;
        if (cleared_lines >= lines_to_change_level)
        {
            ++level;
            cleared_lines -= lines_to_change_level;
        }
        update_delay();
    }
}


void game::update_score(std::size_t cleared_lines, std::size_t dropped_lines)
{
    constexpr uint ppl[] { 0, 40, 100, 300, 1200, };
    score += 2 * dropped_lines;
    score += (ppl[cleared_lines] * (level + 1));
}
