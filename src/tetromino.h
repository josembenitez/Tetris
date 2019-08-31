
#ifndef TETROMINO_H
#define TETROMINO_H


#include <map>
#include <vector>


enum class orientation
{
    flat_down,
    flat_left,
    flat_up,
    flat_right,
};


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


class tetromino
{
public:
    virtual ~tetromino() = default;

public:
    virtual std::size_t bounding_box_size() const = 0;
    virtual tetromino_color color() const = 0;
    virtual std::size_t heigth() const = 0;
    virtual void rotate_clockwise() = 0;
    virtual void rotate_counter_clockwise() = 0;
    virtual std::vector<int> to_vector() const = 0;
    virtual tetromino_type type() const = 0;
    virtual std::size_t width() const = 0;
    virtual std::size_t x_offset() const = 0;
    virtual std::size_t y_offset() const = 0;
};


class base_tetromino : public tetromino
{
protected:
    base_tetromino();
    ~base_tetromino() = default;

    orientation ornt;

public:
    virtual void rotate_clockwise();
    virtual void rotate_counter_clockwise();
};


class i_tetromino : public base_tetromino
{
private:
    static const std::map<orientation, std::vector<int>> rotation_states;

public:
    i_tetromino() = default;
    ~i_tetromino() = default;

    virtual std::size_t bounding_box_size() const;
    virtual tetromino_color color() const;
    virtual std::size_t heigth() const;
    virtual std::vector<int> to_vector() const;
    virtual tetromino_type type() const;
    virtual std::size_t width() const;
    virtual std::size_t x_offset() const;
    virtual std::size_t y_offset() const;
};
    

class j_tetromino : public base_tetromino
{
private:
    static const std::map<orientation, std::vector<int>> rotation_states;
    
public:
    j_tetromino() = default;
    ~j_tetromino() = default;

    virtual std::size_t bounding_box_size() const;
    virtual tetromino_color color() const;
    virtual std::size_t heigth() const;
    virtual std::vector<int> to_vector() const;
    virtual tetromino_type type() const;
    virtual std::size_t width() const;
    virtual std::size_t x_offset() const;
    virtual std::size_t y_offset() const;
};


class l_tetromino : public base_tetromino
{
private:
    static const std::map<orientation, std::vector<int>> rotation_states;
    
public:
    l_tetromino() = default;
    ~l_tetromino() = default;

    virtual std::size_t bounding_box_size() const;
    virtual tetromino_color color() const;
    virtual std::size_t heigth() const;
    virtual std::vector<int> to_vector() const;
    virtual tetromino_type type() const;
    virtual std::size_t width() const;
    virtual std::size_t x_offset() const;
    virtual std::size_t y_offset() const;
};
    

class o_tetromino : public base_tetromino
{
private:
    static const std::map<orientation, std::vector<int>> rotation_states;
    
public:
    o_tetromino() = default;
    ~o_tetromino() = default;
    
    virtual std::size_t bounding_box_size() const;
    virtual tetromino_color color() const;
    virtual std::size_t heigth() const;
    virtual std::vector<int> to_vector() const;
    virtual tetromino_type type() const;
    virtual std::size_t width() const;
    virtual std::size_t x_offset() const;
    virtual std::size_t y_offset() const;
};
    

class s_tetromino : public base_tetromino
{
private:
    static const std::map<orientation, std::vector<int>> rotation_states;
    
public:
    s_tetromino() = default;
    ~s_tetromino() = default;

    virtual std::size_t bounding_box_size() const;
    virtual tetromino_color color() const;
    virtual std::size_t heigth() const;
    virtual std::vector<int> to_vector() const;
    virtual tetromino_type type() const;
    virtual std::size_t width() const;
    virtual std::size_t x_offset() const;
    virtual std::size_t y_offset() const;
};
    

class t_tetromino : public base_tetromino
{
private:
    static const std::map<orientation, std::vector<int>> rotation_states;
    
public:
    t_tetromino() = default;
    ~t_tetromino() = default;

    virtual std::size_t bounding_box_size() const;
    virtual tetromino_color color() const;
    virtual std::size_t heigth() const;
    virtual std::vector<int> to_vector() const;
    virtual tetromino_type type() const;
    virtual std::size_t width() const;
    virtual std::size_t x_offset() const;
    virtual std::size_t y_offset() const;
};
    

class z_tetromino : public base_tetromino
{
private:
    static const std::map<orientation, std::vector<int>> rotation_states;
    
public:
    z_tetromino() = default;
    ~z_tetromino() = default;

    virtual std::size_t bounding_box_size() const;
    virtual tetromino_color color() const;
    virtual std::size_t heigth() const;
    virtual std::vector<int> to_vector() const;
    virtual tetromino_type type() const;
    virtual std::size_t width() const;
    virtual std::size_t x_offset() const;
    virtual std::size_t y_offset() const;
};


#endif  /* TETROMINO_H */
