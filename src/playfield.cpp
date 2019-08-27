
#include "playfield.h"


playfield::playfield(std::size_t width, std::size_t height)
    : well(std::vector<cell_state>(width * height, cell_state::empty)),
      width(width),
      height(height)
{
}


bool playfield::can_tetromino_move_to(const tetromino &t, int x, int y) const
{
    // Check whether the tetromino fits within the playfield
    if (x + t.x_offset() < 0 ||
        x + t.x_offset() + t.width() > this->width ||
        y + t.y_offset() < 0 ||
        y + t.y_offset() + t.heigth() > this->height)
    {
        return false;
    }

    // Check now whether every cell to be filled in by the tetromino is empty
    const std::vector<int> tetrions = t.to_vector();
    for (std::size_t i = 0; i < t.width(); ++i)
    {
        for (std::size_t j = 0; j < t.heigth(); ++j)
        {
            if (well[(y + j) * width + (x + i)] != cell_state::empty && tetrions[j * t.width() + i])
            {
                return false;
            }
        }
    }

    return true;
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


void playfield::store_tetromino_into(const tetromino &t, int x, int y)
{
    const std::vector<int> tetrions = t.to_vector();
    for (std::size_t i = 0; i < t.width(); ++i)
    {
        for (std::size_t j = 0; j < t.heigth(); ++j)
        {
            if (tetrions[j * t.width() + i])
            {
                well[(y + j) * width + (x + i)] = get_cell_state_for(t);
            }
        }
    }
}
