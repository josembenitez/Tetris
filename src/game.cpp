
#include <chrono>
#include <memory>
#include <thread>

#include "controller.h"
#include "game.h"
#include "playfield.h"
#include "renderer.h"
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

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms per frame), delay the loop o achieve
        // the correct frame rate.
        const auto frame_end = std::chrono::system_clock::now();
        const auto frame_duration = std::chrono::duration_cast<std::chrono::milliseconds>(frame_end - frame_start).count();
        if (frame_duration < target_frame_duration)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(target_frame_duration - frame_duration));
        }
    }

    if (!quit)
    {
        // Wait until the user quits the game by closing the window.
        while (cntrllr.get_input() != input::quit)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(target_frame_duration));
        }
    }
}


std::size_t game::drop_down()
{
    std::size_t count = 0;
    // Ground is reached when the tetromino cannot go further down.
    while (move_down())
    {
        ++count;
    }
    update_score(0, count);
    return count;
}


void game::get_next_tetromino()
{
    const int type = random_tetromino(engine);
    switch (type)
    {
    case 0:
        current = std::make_unique<i_tetromino>();
        break;
    
    case 1:
        current = std::make_unique<j_tetromino>();
        break;
    
    case 2:
        current = std::make_unique<l_tetromino>();
        break;

    case 3:
        current = std::make_unique<o_tetromino>();
        break;

    case 4:
        current = std::make_unique<s_tetromino>();
       break;
    
    case 5:
        current = std::make_unique<t_tetromino>();
        break;
    
    default:
        current = std::make_unique<z_tetromino>();
        break;
    }

    // Sets the starting point within the playfield (half of the topmost row).
    x = (pf.columns() - current->bounding_box_size()) / 2;
    y = 0;

    // Update the time point to calculate the next falling instant.
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
        // The tetromino has touched ground if it cannot go further down, so store it
        // into the playfield and update game state.
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
        // Is it time to make the current tetromino fall one more cell?
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
