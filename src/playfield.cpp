
#include <algorithm>
#include <iostream>
#include <optional>

#include "playfield.h"
#include "tetromino.h"


playfield::playfield(std::size_t width, std::size_t height)
    : well(std::vector<std::optional<tetromino_color>>(width * height)),
      width(width),
      height(height)
{
}


bool playfield::can_tetromino_move_to(const tetromino &t, int x, int y) const
{
    const int x_start = x + t.x_offset();
    const int y_start = y + t.y_offset();

    // Check whether the tetromino fits within the playfield.
    if (x_start < 0 || x_start + t.width() > this->width ||
        y_start < 0 || y_start + t.heigth() > this->height)
    {
        return false;
    }

    // Check now whether every cell to be filled in by the tetromino is empty.
    const std::vector<int> tetrions = t.to_vector();
    for (std::size_t i = 0; i < tetrions.size(); ++i)
    {
        const std::size_t x_t = i % t.bounding_box_size();
        const std::size_t y_t = i / t.bounding_box_size();
        if (tetrions[i] && well[(y + y_t) * width + x + x_t].has_value())
        {
            return false;
        }
    }

    return true;
}


std::size_t playfield::clear_rows()
{
    const auto rows = filled_rows();
    if (rows.size())
    {
        const std::size_t end_row = *(rows.begin()) + 1;
        const std::size_t start_row = *(rows.end() - 1);
        const std::size_t num_deleted_rows = end_row - start_row;
        std::vector<std::optional<tetromino_color>> tmp(well.size());
        std::copy(well.cbegin(), well.cbegin() + start_row * width,
                  tmp.begin() + num_deleted_rows * width);
        std::copy(well.cbegin() + end_row * width, well.cend(),
                  tmp.begin() + end_row * width);
        well = tmp;
    }
    return rows.size();
}


std::size_t playfield::columns() const
{
    return width;
}


std::vector<std::size_t> playfield::filled_rows() const
{
    std::vector<std::size_t> rows;
    for (std::size_t r = height; r > 0;)
    {
        if (is_row_filled(--r))
        {
            rows.push_back(r);
        }
        else if (rows.size() > 0)
        {
            break;
        }
        
    }
    return rows;
}


bool playfield::is_row_filled(std::size_t row) const
{
    auto cell_is_not_empy = [] (std::optional<tetromino_color> c) { return c.has_value(); };
    return std::count_if(well.cbegin() + row * width,
                         well.cbegin() + (row + 1) * width,
                         cell_is_not_empy) == width;
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
            well[(y + y_t) * width + x + x_t] = t.color();
        }
    }
}


std::vector<std::optional<tetromino_color>> playfield::to_vector() const
{
    return std::vector(well);
}
