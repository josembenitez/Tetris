
#include "tetromino.h"


base_tetromino::base_tetromino() : ornt(orientation::flat_down)
{
}


void base_tetromino::rotate_clockwise()
{
    switch (ornt)
    {
    case orientation::flat_down:
        ornt = orientation::flat_left;
        break;
    
    case orientation::flat_left:
        ornt = orientation::flat_up;
        break;
    
    case orientation::flat_up:
        ornt = orientation::flat_right;
        break;
    
    case orientation::flat_right:
        ornt = orientation::flat_down;
        break;
    
    default:
        break;
    }
}


void base_tetromino::rotate_counter_clockwise()
{
    switch (ornt)
    {
    case orientation::flat_down:
        ornt = orientation::flat_right;
        break;
    
    case orientation::flat_right:
        ornt = orientation::flat_up;
        break;
    
    case orientation::flat_up:
        ornt = orientation::flat_left;
        break;
    
    case orientation::flat_left:
        ornt = orientation::flat_down;
        break;
    
    default:
        break;
    }
}


const std::map<orientation, std::vector<int>> i_tetromino::rotation_states = {

    { orientation::flat_down,  { 0, 0, 0, 0,
                                 1, 1, 1, 1,
                                 0, 0, 0, 0,
                                 0, 0, 0, 0, },
    },

    { orientation::flat_left,  { 0, 0, 1, 0,
                                 0, 0, 1, 0,
                                 0, 0, 1, 0,
                                 0, 0, 1, 0, },
    },

    { orientation::flat_up,    { 0, 0, 0, 0,
                                 0, 0, 0, 0,
                                 1, 1, 1, 1,
                                 0, 0, 0, 0, },
    },

    { orientation::flat_right, { 0, 1, 0, 0,
                                 0, 1, 0, 0,
                                 0, 1, 0, 0,
                                 0, 1, 0, 0, },
    },
};


std::size_t i_tetromino::bounding_box_size() const
{
    return 4;
}


tetromino_color i_tetromino::color() const
{
    return tetromino_color::cyan;
}


std::size_t i_tetromino::heigth() const
{
    return ornt == orientation::flat_down || ornt == orientation::flat_up ? 1 : 4;
}


std::vector<int> i_tetromino::to_vector() const
{
    return rotation_states.at(ornt);
}


tetromino_type i_tetromino::type() const
{
    return tetromino_type::i_block;
}


std::size_t i_tetromino::width() const
{
    return ornt == orientation::flat_down || ornt == orientation::flat_up ? 4 : 1;
}


std::size_t i_tetromino::x_offset() const
{
    switch (ornt)
    {
    case orientation::flat_left:
        return 2;

    case orientation::flat_right:
        return 1;

    default:
        return 0;
    }
}


std::size_t i_tetromino::y_offset() const
{
    switch (ornt)
    {
    case orientation::flat_down:
        return 1;

    case orientation::flat_up:
        return 2;

    default:
        return 0;
    }
}


const std::map<orientation, std::vector<int>> j_tetromino::rotation_states = {

    { orientation::flat_down,  { 1, 0, 0,
                                 1, 1, 1,
                                 0, 0, 0, },
    },

    { orientation::flat_left,  { 0, 1, 1,
                                 0, 1, 0,
                                 0, 1, 0, },
    },

    { orientation::flat_up,    { 0, 0, 0, 
                                 1, 1, 1, 
                                 0, 0, 1, },
    },

    { orientation::flat_right, { 0, 1, 0,
                                 0, 1, 0,
                                 1, 1, 0, },
    },
};


std::size_t j_tetromino::bounding_box_size() const
{
    return 3;
}


tetromino_color j_tetromino::color() const
{
    return tetromino_color::blue;
}


std::size_t j_tetromino::heigth() const
{
    return ornt == orientation::flat_down || ornt == orientation::flat_up ? 2 : 3;
}


std::vector<int> j_tetromino::to_vector() const
{
    return rotation_states.at(ornt);
}


tetromino_type j_tetromino::type() const
{
    return tetromino_type::j_block;
}


std::size_t j_tetromino::width() const
{
    return ornt == orientation::flat_down || ornt == orientation::flat_up ? 3 : 2;
}


std::size_t j_tetromino::x_offset() const
{
    return ornt == orientation::flat_left ? 1 : 0;
}

std::size_t j_tetromino::y_offset() const
{
    return ornt == orientation::flat_up ? 1 : 0;
}


const std::map<orientation, std::vector<int>> l_tetromino::rotation_states = {
    
    { orientation::flat_down,  { 0, 0, 1,
                                 1, 1, 1,
                                 0, 0, 0, },
    },

    { orientation::flat_left,  { 0, 1, 0,
                                 0, 1, 0,
                                 0, 1, 1, },
    },

    { orientation::flat_up,    { 0, 0, 0, 
                                 1, 1, 1, 
                                 1, 0, 0, },
    },

    { orientation::flat_right, { 1, 1, 0,
                                 0, 1, 0,
                                 0, 1, 0, },
    },
};


std::size_t l_tetromino::bounding_box_size() const
{
    return 3;
}


tetromino_color l_tetromino::color() const
{
    return tetromino_color::orange;
}


std::size_t l_tetromino::heigth() const
{
    return ornt == orientation::flat_down || ornt == orientation::flat_up ? 2 : 3;
}


std::vector<int> l_tetromino::to_vector() const
{
    return rotation_states.at(ornt);
}


tetromino_type l_tetromino::type() const
{
    return tetromino_type::l_block;
}


std::size_t l_tetromino::width() const
{
    return ornt == orientation::flat_down || ornt == orientation::flat_up ? 3 : 2;
}


std::size_t l_tetromino::x_offset() const
{
    return ornt == orientation::flat_left ? 1 : 0;
}


std::size_t l_tetromino::y_offset() const
{
    return ornt == orientation::flat_up ? 1 : 0;
}


const std::map<orientation, std::vector<int>> o_tetromino::rotation_states = {

    { orientation::flat_down,  { 1, 1,
                                 1, 1, },
    },

    { orientation::flat_left,  { 1, 1,
                                 1, 1, },
    },

    { orientation::flat_up,    { 1, 1,
                                 1, 1, },
    },

    { orientation::flat_right, { 1, 1,
                                 1, 1, },
    },
};


std::size_t o_tetromino::bounding_box_size() const
{
    return 2;
}


tetromino_color o_tetromino::color() const
{
    return tetromino_color::yellow;
}


std::size_t o_tetromino::heigth() const
{
    return 2;
}


std::vector<int> o_tetromino::to_vector() const
{
    return rotation_states.at(ornt);
}


tetromino_type o_tetromino::type() const
{
    return tetromino_type::o_block;
}


std::size_t o_tetromino::width() const
{
    return 2;
}


std::size_t o_tetromino::x_offset() const
{
    return 0;
}


std::size_t o_tetromino::y_offset() const
{
    return 0;
}


const std::map<orientation, std::vector<int>> s_tetromino::rotation_states = {

    { orientation::flat_down,  { 0, 1, 1,
                                 1, 1, 0,
                                 0, 0, 0, },
    },

    { orientation::flat_left,  { 0, 1, 0,
                                 0, 1, 1,
                                 0, 0, 1, },
    },

    { orientation::flat_up,    { 0, 0, 0, 
                                 0, 1, 1, 
                                 1, 1, 0, },
    },

    { orientation::flat_right, { 1, 0, 0,
                                 1, 1, 0,
                                 0, 1, 0, },
    },
};


std::size_t s_tetromino::bounding_box_size() const
{
    return 3;
}


tetromino_color s_tetromino::color() const
{
    return tetromino_color::green;
}


std::size_t s_tetromino::heigth() const
{
    return ornt == orientation::flat_down || ornt == orientation::flat_up ? 2 : 3;
}


std::vector<int> s_tetromino::to_vector() const
{
    return rotation_states.at(ornt);
}


tetromino_type s_tetromino::type() const
{
    return tetromino_type::s_block;
}


std::size_t s_tetromino::width() const
{
    return ornt == orientation::flat_down || ornt == orientation::flat_up ? 3 : 2;
}


std::size_t s_tetromino::x_offset() const
{
    return ornt == orientation::flat_left ? 1 : 0;
}


std::size_t s_tetromino::y_offset() const
{
    return ornt == orientation::flat_up ? 1 : 0;
}


const std::map<orientation, std::vector<int>> t_tetromino::rotation_states = {

    { orientation::flat_down,  { 0, 1, 0,
                                 1, 1, 1,
                                 0, 0, 0, },
    },

    { orientation::flat_left,  { 0, 1, 0,
                                 0, 1, 1,
                                 0, 1, 0, },
    },

    { orientation::flat_up,    { 0, 0, 0, 
                                 1, 1, 1, 
                                 0, 1, 0, },
    },

    { orientation::flat_right, { 0, 1, 0,
                                 1, 1, 0,
                                 0, 1, 0, },
    },
};


std::size_t t_tetromino::bounding_box_size() const
{
    return 3;
}


tetromino_color t_tetromino::color() const
{
    return tetromino_color::purple;
}


std::size_t t_tetromino::heigth() const
{
    return ornt == orientation::flat_down || ornt == orientation::flat_up ? 2 : 3;
}


std::vector<int> t_tetromino::to_vector() const
{
    return rotation_states.at(ornt);
}


tetromino_type t_tetromino::type() const
{
    return tetromino_type::t_block;
}


std::size_t t_tetromino::width() const
{
    return ornt == orientation::flat_down || ornt == orientation::flat_up ? 3 : 2;
}


std::size_t t_tetromino::x_offset() const
{
    return ornt == orientation::flat_left ? 1 : 0;
}


std::size_t t_tetromino::y_offset() const
{
    return ornt == orientation::flat_up ? 1 : 0;
}


const std::map<orientation, std::vector<int>> z_tetromino::rotation_states = {

    { orientation::flat_down,  { 1, 1, 0,
                                 0, 1, 1,
                                 0, 0, 0, },
    },

    { orientation::flat_left,  { 0, 0, 1,
                                 0, 1, 1,
                                 0, 1, 0, },
    },

    { orientation::flat_up,    { 0, 0, 0, 
                                 1, 1, 0, 
                                 0, 1, 1, },
    },

    { orientation::flat_right, { 0, 1, 0,
                                 1, 1, 0,
                                 1, 0, 0, },
    },
};


std::size_t z_tetromino::bounding_box_size() const
{
    return 3;
}


tetromino_color z_tetromino::color() const
{
    return tetromino_color::red;
}


std::size_t z_tetromino::heigth() const
{
    return ornt == orientation::flat_down || ornt == orientation::flat_up ? 2 : 3;
}


std::vector<int> z_tetromino::to_vector() const
{
    return rotation_states.at(ornt);
}


tetromino_type z_tetromino::type() const
{
    return tetromino_type::z_block;
}


std::size_t z_tetromino::width() const
{
    return ornt == orientation::flat_down || ornt == orientation::flat_up ? 3 : 2;
}


std::size_t z_tetromino::x_offset() const
{
    return ornt == orientation::flat_left ? 1 : 0;
}


std::size_t z_tetromino::y_offset() const
{
    return ornt == orientation::flat_up ? 1 : 0;
}
