
#include <algorithm>
#include <iostream>

#include "playfield.h"


playfield::playfield(std::size_t width, std::size_t height)
    : well(std::vector<cell_state>(width * height, cell_state::empty)),
      width(width),
      height(height)
{
}


bool playfield::can_tetromino_move_to(const tetromino &t, int x, int y) const
{
    const int x_start = x + t.x_offset();
    const int y_start = y + t.y_offset();

    // Check whether the tetromino fits within the playfield
    if (x_start < 0 || x_start + t.width() > this->width ||
        y_start < 0 || y_start + t.heigth() > this->height)
    {
        return false;
    }

    // Check now whether every cell to be filled in by the tetromino is empty
    const std::vector<int> tetrions = t.to_vector();
    for (std::size_t i = 0; i < tetrions.size(); ++i)
    {
        const std::size_t x_t = i % t.bounding_box_size();
        const std::size_t y_t = i / t.bounding_box_size();
        if (tetrions[i] && well[(y + y_t) * width + x + x_t] != cell_state::empty)
        {
            return false;
        }
    }

    return true;
}


std::size_t playfield::columns() const
{
    return width;
}


std::size_t playfield::rows() const
{
    return height;
}


void playfield::store_tetromino_into(const tetromino &t, int x, int y)
{
    const std::vector<int> tetrions = t.to_vector();
    for (std::size_t i = 0; i < tetrions.size(); ++i)
    {
        if (tetrions[i])
        {
            const std::size_t x_t = i % t.bounding_box_size();
            const std::size_t y_t = i / t.bounding_box_size();
            well[(y + y_t) * width + x + x_t] = get_cell_state_for(t);
        }
    }
}


cell_state playfield::get_cell_state_for(const tetromino &t)
{
    switch (t.type())
    {
    case tetromino_type::i_block:
        return cell_state::filled_with_i;

    case tetromino_type::j_block:
        return cell_state::filled_with_j;
        
    case tetromino_type::l_block:
        return cell_state::filled_with_l;
        
    case tetromino_type::o_block:
        return cell_state::filled_with_o;
        
    case tetromino_type::s_block:
        return cell_state::filled_with_s;
        
    case tetromino_type::t_block:
        return cell_state::filled_with_t;
        
    default: /* tetromino_type::z_block */
        return cell_state::filled_with_z;   
    }
}


std::vector<int> playfield::to_vector() const
{
    std::vector<int> result(well.size());
    std::transform(well.begin(), well.end(), result.begin(), [] (cell_state st) { return (int) st; });
    return result;
}
