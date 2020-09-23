
#ifndef PLAYFIELD_H
#define PLAYFIELD_H


#include <vector>


class tetromino;


/**
 * Each of the possible states of a playfield cell.
 */
enum class cell_state
{
    empty,
    busy,
};


/**
 * Class defining the game playfield as a 2-D cell grid.
 */
class playfield
{
public:
    /**
     * Builds an instance of this class with the given dimensions.
     * 
     * @param rows The grid width.
     * @param column The grid height.
     */
    playfield(std::size_t rows, std::size_t height);
    /**
     * Destructor.
     */
    ~playfield() = default;
    
    /**
     * Returns whether the given tetromino can be moved to the given cell.
     * 
     * @param t The tetromino to be moved.
     * @param x The x-coordinate of the starting cell at which the tetromino is to be moved.
     * @param y The y-coordinate of the starting cell at which the tetromino is to be moved.
     *
     * @return `true` if the tetromino can indeed be moved and `false` otherwise.
     */
    bool can_tetromino_move_to(const tetromino &t, int x, int y) const;
    /**
     * Clears any completed rows.
     * 
     * @return The number of completed rows if any.
     */
    std::size_t clear_rows();
    /**
     * Returns the width (in number of cells) of this playfield.
     * 
     * @return The width (in number of cells) of this playfield.
     */
    std::size_t columns() const;
    /**
     * Returns a list with the indexes of all completed lines.
     * 
     * @return A vector containing the indexes of all completed lines.
     */
    std::vector<std::size_t> filled_rows() const;
    /**
     * Returns whether the given row is completed.
     * 
     * @return `true` if the given row is completed and `false` otherwise.ç
     */
    bool is_row_filled(std::size_t row) const;
    /**
     * Returns the height (in number of cells) of this playfield.
     * 
     * @return The height (in number of cells) of this playfield.
     */
    std::size_t rows() const;
    /**
     * Stores the given tetromino into the given location.
     * 
     * @param t The tetromino to be stored.
     * @param x The x-coordinate of the starting cell at which the tetromino is to be stored.
     * @param y The y-coordinate of the starting cell at which the tetromino is to be stored.
     */
    void store_tetromino_into(const tetromino &t, int x, int y);
    /**
     * Serializes this playfield.
     * 
     * @return A vector containing all the cells of this playfield.
     */
    std::vector<cell_state> to_vector() const;

private:
    /**
     * Width of this playfield (in number of cells);
     */
    std::size_t width;
    /**
     * Height of this playfield (in number of cells);
     */
    std::size_t height;
    /**
     * Vector representing the actual playfield.
     */
    std::vector<cell_state> well;
};


#endif  /* PLAYFIELD_H */
