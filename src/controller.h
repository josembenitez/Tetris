
#ifndef CONTROLLER_H
#define CONTROLLER_H


enum class input
{
    none,
    move_right,
    move_left,
    rotate_clockwise,
    rotate_counter_clockwise,
    move_down,
};


class controller
{
public:
    input get_input() const;
};


#endif  /* CONTROLLER_H */
