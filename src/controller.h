
#ifndef CONTROLLER_H
#define CONTROLLER_H


/**
 * Each of the user inputs.
 */
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


/**
 * This class handles keyboard inputs using the SDL library.
 */
class controller
{
public:
    /**
     * Returns the current user input as defined by #input.
     */ 
    input get_input() const;
};


#endif  /* CONTROLLER_H */
