
#ifndef GAME_H
#define GAME_H


#include <random>

#include "controller.h"
#include "playfield.h"
#include "renderer.h"
#include "tetromino.h"


class game
{
public:
    game(std::size_t well_width, std::size_t well_height);
    ~game();

    void run(const controller &cntrllr, renderer &rndrr);

private:
    playfield pf;
    int x;
    int y;
    tetromino *current;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_tetromino;

    std::size_t drop_down();
    void get_next_tetromino();
    bool move_down();
    bool move_left();
    bool move_right();
    bool playfield_is_filled_up() const;
    bool rotate_clockwise();
    bool rotate_counterclockwise();
    bool update(input inpt);
};


#endif  /* GAME_H */
