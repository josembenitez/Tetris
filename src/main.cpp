
#include <iostream>

#include "playfield.h"
#include "tetromino.h"


int main()
{
    playfield pf(10, 20);

    z_tetromino t;
    tetromino &current = t;

    for (std::size_t k = 0; k < 4; ++k)
    {
        for (std::size_t j = 0; j < 20; ++j)
        {
            for (std::size_t i = 0; i < 10; ++i)
            {
                std::cout << pf.can_tetromino_move_to(current, i, j) << '\t';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
        current.rotate_clockwise();
    }

/*
    while (!playfield.IsFilledUp())
    {
        Tetromino t = get_new_tetromino();
        while (playfield.MoveTetrominoTo(t, x, y));
    }
*/
}
