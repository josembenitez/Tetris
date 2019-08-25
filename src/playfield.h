
#ifndef PLAYFIELD_H
#define PLAYFIELD_H


#include <vector>

#include "tetromino.h"


enum class cell_state
{
    empty,
    filled_with_i,
    filled_with_j,
    filled_with_l,
    filled_with_o,
    filled_with_s,
    filled_with_t,
    filled_with_z,
};


class playfield
{
public:
    playfield(std::size_t width, std::size_t height);
    ~playfield() = default;
    
    bool can_tetromino_move_to(const tetromino &t, int x, int y) const;
    std::size_t clear_rows();
    bool is_filled_up() const;
    std::vector<int> to_vector() const;

private:
    std::size_t width;
    std::size_t height;     
    std::vector<cell_state> well;

    cell_state get_cell_state_for(const tetromino &t);
    void store_tetromino_into(const tetromino &t, int x, int y);
};


#endif  /* PLAYFIELD_H */
