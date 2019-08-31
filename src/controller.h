
#ifndef CONTROLLER_H
#define CONTROLLER_H


enum class input
{
    none,
    drop,
    move_down,
    move_left,
    move_right,
    rotate_clockwise,
    rotate_counterclockwise,
    quit,
};


class controller
{
public:
    input get_input() const;
};


#endif  /* CONTROLLER_H */
