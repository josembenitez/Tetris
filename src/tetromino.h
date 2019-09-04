
#ifndef TETROMINO_H
#define TETROMINO_H


#include <map>
#include <vector>


/**
 * Tetrominoes orientation values.
 */
enum class orientation
{
    flat_down,
    flat_left,
    flat_up,
    flat_right,
};


/**
 * Types of tetrominoes.
 */
enum class tetromino_type
{
    i_block,
    j_block,
    l_block,
    o_block,
    s_block,
    t_block,
    z_block,
};


/**
 * Colors of tetrominoes.
 */
enum class tetromino_color
{
    cyan,
    blue,
    orange,
    yellow,
    green,
    purple,
    red,
};


/**
 * Abstract class defining a tetromino.
 */
class tetromino
{
public:
    /**
     * Destructor.
     */
    virtual ~tetromino() = default;

public:
    /**
     * Returns the size (in blocks) of this tetromino's bounding box;
     * 
     * @return The size (in blocks) of this tetromino's bounding box
     */
    virtual std::size_t bounding_box_size() const = 0;
    /**
     * Returns this tetromino's color as defined by #tetromino_color.
     * 
     * @return This tetromino's color as defined by #tetromino_color.
     */
    virtual tetromino_color color() const = 0;
    /**
     * Returns this tetromino's height (in blocks).
     * 
     * @return This tetromino's height (in blocks).
     */
    virtual std::size_t heigth() const = 0;
    /**
     * Rotates this tetromino 90 degrees clockwise.
     */
    virtual void rotate_clockwise() = 0;
    /**
     * Rotates this tetromino 90 degrees counterclockwise.
     */
    virtual void rotate_counterclockwise() = 0;
    /**
     * Serializes this tetromino's bounding box.
     * 
     * @return A vector representing this tetromino's bounding box, where `1` indicates
     * there is a block and `0` otherwise.
     */
    virtual std::vector<int> to_vector() const = 0;
    /**
     * Returns this tetromino's type as defined by #tetromino_type.
     * 
     * @return This tetromino's width as defined by #tetromino_type.
     */
    virtual tetromino_type type() const = 0;
    /**
     * Returns this tetromino's width (in blocks).
     * 
     * @return This tetromino's width (in blocks).
     */
    virtual std::size_t width() const = 0;
    /**
     * Returns the x-coordinate of this tetromino's left-uppermost block.
     * 
     * @return The x-coordinate of this tetromino's left-uppermost block.
     */
    virtual std::size_t x_offset() const = 0;
    /**
     * Returns the y-coordinate of this tetromino's left-uppermost block.
     * 
     * @return The y-coordinate of this tetromino's left-uppermost block.
     */
    virtual std::size_t y_offset() const = 0;
};


class base_tetromino : public tetromino
{
protected:
    /**
     * Builds an instance of this class.
     */
    base_tetromino();
    /**
     * Destructor.
     */
    ~base_tetromino() = default;

    /**
     * This tetromino's orientation as defined by #orientation.
     */
    orientation ornt;

public:
    void rotate_clockwise() override;
    void rotate_counterclockwise() override;
};


class i_tetromino : public base_tetromino
{
private:
    /**
     * Map associating orientation values and serialized blocks.
     */
    static const std::map<orientation, std::vector<int>> rotation_states;

public:
    /**
     * Builds an instance of this class.
     */
    i_tetromino() = default;
    /**
     * Destructor.
     */
    ~i_tetromino() = default;

    std::size_t bounding_box_size() const override;
    tetromino_color color() const override;
    std::size_t heigth() const override;
    std::vector<int> to_vector() const override;
    tetromino_type type() const override;
    std::size_t width() const override;
    std::size_t x_offset() const override;
    std::size_t y_offset() const override;
};
    

class j_tetromino : public base_tetromino
{
private:
    /**
     * Map associating orientation values and serialized blocks.
     */
    static const std::map<orientation, std::vector<int>> rotation_states;
    
public:
     /**
     * Builds an instance of this class.
     */
   j_tetromino() = default;
    /**
     * Destructor.
     */
    ~j_tetromino() = default;

    std::size_t bounding_box_size() const override;
    tetromino_color color() const override;
    std::size_t heigth() const override;
    std::vector<int> to_vector() const override;
    tetromino_type type() const override;
    std::size_t width() const override;
    std::size_t x_offset() const override;
    std::size_t y_offset() const override;
};


class l_tetromino : public base_tetromino
{
private:
    /**
     * Map associating orientation values and serialized blocks.
     */
    static const std::map<orientation, std::vector<int>> rotation_states;
    
public:
    /**
     * Builds an instance of this class.
     */
    l_tetromino() = default;
    /**
     * Destructor.
     */
    ~l_tetromino() = default;

    std::size_t bounding_box_size() const override;
    tetromino_color color() const override;
    std::size_t heigth() const override;
    std::vector<int> to_vector() const override;
    tetromino_type type() const override;
    std::size_t width() const override;
    std::size_t x_offset() const override;
    std::size_t y_offset() const override;
};
    

class o_tetromino : public base_tetromino
{
private:
    /**
     * Map associating orientation values and serialized blocks.
     */
    static const std::map<orientation, std::vector<int>> rotation_states;
    
public:
    /**
     * Builds an instance of this class.
     */
    o_tetromino() = default;
    /**
     * Destructor.
     */
    ~o_tetromino() = default;
    
    std::size_t bounding_box_size() const override;
    tetromino_color color() const override;
    std::size_t heigth() const override;
    std::vector<int> to_vector() const override;
    tetromino_type type() const override;
    std::size_t width() const override;
    std::size_t x_offset() const override;
    std::size_t y_offset() const override;
};
    

class s_tetromino : public base_tetromino
{
private:
    /**
     * Map associating orientation values and serialized blocks.
     */
    static const std::map<orientation, std::vector<int>> rotation_states;
    
public:
    /**
     * Builds an instance of this class.
     */
    s_tetromino() = default;
    /**
     * Destructor.
     */
    ~s_tetromino() = default;

    std::size_t bounding_box_size() const override;
    tetromino_color color() const override;
    std::size_t heigth() const override;
    std::vector<int> to_vector() const override;
    tetromino_type type() const override;
    std::size_t width() const override;
    std::size_t x_offset() const override;
    std::size_t y_offset() const override;
};
    

class t_tetromino : public base_tetromino
{
private:
    /**
     * Map associating orientation values and serialized blocks.
     */
    static const std::map<orientation, std::vector<int>> rotation_states;
    
public:
    /**
     * Builds an instance of this class.
     */
    t_tetromino() = default;
    /**
     * Destructor.
     */
    ~t_tetromino() = default;

    std::size_t bounding_box_size() const override;
    tetromino_color color() const override;
    std::size_t heigth() const override;
    std::vector<int> to_vector() const override;
    tetromino_type type() const override;
    std::size_t width() const override;
    std::size_t x_offset() const override;
    std::size_t y_offset() const override;
};
    

class z_tetromino : public base_tetromino
{
private:
    /**
     * Map associating orientation values and serialized blocks.
     */
    static const std::map<orientation, std::vector<int>> rotation_states;
    
public:
     /**
     * Builds an instance of this class.
     */
   z_tetromino() = default;
    ~z_tetromino() = default;

    std::size_t bounding_box_size() const override;
    tetromino_color color() const override;
    std::size_t heigth() const override;
    std::vector<int> to_vector() const override;
    tetromino_type type() const override;
    std::size_t width() const override;
    std::size_t x_offset() const override;
    std::size_t y_offset() const override;
};


#endif  /* TETROMINO_H */
