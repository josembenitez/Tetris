
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
    game();

    void run(const controller &cntrllr, renderer &rndrr);

private:
    playfield pf;
    int x;
    int y;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_tetromino;

    void create_tetromino(tetromino &t);
    bool update(input inpt);
};


#endif  /* GAME_H */
