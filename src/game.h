
#ifndef GAME_H
#define GAME_H


#include <chrono>
#include <memory>
#include <random>

#include "playfield.h"
#include "tetromino.h"

class controller;
class renderer;


/**
 * Game class defining the game state and logic.
 */
class game
{
public:
    /**
     * Builds an instance of this class.
     * 
     * @param well_width (in cells) of the playfield.
     * @param well_height (in cells) of the playfield.
     */
    game(std::size_t well_width, std::size_t well_height);
    /**
     * Destructor.
     */
    ~game() = default;

    /**
     * Runs this game.
     * 
     * @param cntrllr The controller object handling user input.
     * @param rndrr The renderer object in charge to render game state on to the screen.
     * @param fps The desired frames per second at which the game will be played.
     */
    void run(const controller &cntrllr, renderer &rndrr, std::size_t fps);

private:
    /**
     * Number of lines needed to increase game level.
     */
    static constexpr std::size_t lines_to_change_level = 10;
    /**
     * Total number of game levels.
     */
    static constexpr std::size_t max_level = 10;
    /**
     * Time interval (in milliseconds) to be decreased with each level.
     */
    static constexpr std::size_t delay_interval = 50;

    /**
     * Flag indicating whether the game is over.
     */
    bool gameover;
    /**
     * Flag indicating whether the user has requested to quit the game.
     */
    bool quit;
    /**
     * Time rate (in milliseconds) at which tetrominoes fall downwards.
     */
    std::size_t delay;
    /**
     * User score.
     */
    std::size_t score;
    /**
     * Total number of cleared lines.
     */
    std::size_t cleared_lines;
    /**
     * Game level.
     */
    std::size_t level;
    /**
     * Playfield.
     */
    playfield pf;
    /**
     * Current x-coordinate of the falling tetromino.
     */
    int x;
    /**
     * Current y-coordinate of the falling tetromino.
     */
    int y;
    /**
     * Current falling tetromino.
     */
    std::unique_ptr<tetromino> current;
    /**
     * Starting time point to calculate when the current tetromino is to fall one cell down.
     */
    std::chrono::time_point<std::chrono::system_clock> last_update;

    /**
     * Random device.
     */
    std::random_device dev;
    /**
     * Random engine.
     */
    std::mt19937 engine;
    /**
     * Uniform distribution to be used with the random engine.
     */
    std::uniform_int_distribution<int> random_tetromino;

    /**
     * Drops the current tetromino all the way down and updates the user score and level
     * accordingly.
     * 
     * @return The number of cells (lines) traversed.
     */
    std::size_t drop_down();
    /**
     * Creates a new tetromino and sets it as the current falling piece, starting from the
     * topmost line of the playfield.
     */
    void get_next_tetromino();
    /**
     * Tries to move the current tetromino one block down.
     * 
     * Please note this function stores the current tetromino into the playfield if the
     * piece cannot be moved, clearing rows if possible, and introducing a new tetromino
     * into the game.
     * 
     * User score and level are also updated accordingly.
     * 
     * @return `true` if the tetromino has actually been moved and `false` otherwise.
     */
    bool move_down();
    /**
     * Tries to shift the current tetromino one cell to the left.
     * 
     * @return `true` if the tetromino has actually been shifted and `false` otherwise.
     */
    bool move_left();
    /**
     * Tries to shift the current tetromino one cell to the right.
     * 
     * @return `true` if the tetromino has actually been shifted and `false` otherwise.
     */
    bool move_right();
    /**
     * Returns whether the playfiled is filled up and no more tetrominoes can be added to
     * it.
     * 
     * @return `true` if the playfield is filled up and `false` otherwise.
     */
    bool playfield_is_filled_up() const;
    /**
     * Tries to rotate the current tetromino 90 degrees clockwise.
     * 
     * @return `true` if the playfield is filled up and `false` otherwise.
     */
    bool rotate_clockwise();
    /**
     * Tries to rotate the current tetromino 90 degrees counterclockwise.
     * 
     * @return `true` if the playfield is filled up and `false` otherwise.
     */
    bool rotate_counterclockwise();
    /**
     * Updates the game state with the given input.
     * 
     * Please note this method considers also the tetromino gravity as an input.
     * 
     * @param inpt User input as defined by #input.
     */
    void update(input inpt);
    /**
     * Updates the gravity rate based on the current game level.
     */
    void update_delay();
    /**
     * Updates the current number of cleared lines with the given number and updates the
     * game level accordingly.
     */
    void update_level(std::size_t lines);
    /**
     * Updates the user score with the given number of cleared lines and/or dropped lines.
     * 
     * @param cleared_lines The number of cleared lines made by the last movement.
     * @param dropped_lines The number of dropped lines made by the last movement.
     */
    void update_score(std::size_t cleared_lines, std::size_t dropped_lines);
};


#endif  /* GAME_H */
