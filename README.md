# CppND-Capstone-Tetris

Capstone project for [Udacity's C++ Nanodegree program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213) consisting on an implementation of the popular Tetris game.

This implementation tries to adhere as much as possible to the current specification of the [Tetris Guideline](https://tetris.fandom.com/wiki/Tetris_Guideline). There may be situations in which the program behavior differs from the specification, which may be due to an unintended misundertanding or to an implementation trade-off. Thus, some missing features may be addressed in a near future.

The standard mapping for computer keyboards is used:

- *Up arrow* and *X* to rotate 90 degrees clockwise.
- *Space* to hard drop.
- *Z* to rotate 90 degrees counterclockwise.
- *Left*, *Right*, and *Down* to shift accordingly.
- *Esc* to quit the game.

Points are awarded both when lines are completed and when pieces are dropped down (hard-drop). As lines are completed, the game level is increased and pieces start falling at a greater rate.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Tetris`.

## Project Description

As it should be obvious by now, the option chosen for the Capstone Project has been creating my own version of the popular Tetris game. The project structure is based on the provided [Snake Game](https://github.com/udacity/CppND-Capstone-Snake-Game) project, which is in turn nothing more than an implementation of the classic [game loop](https://gameprogrammingpatterns.com/game-loop.html) game programming pattern.

At a high level, a game performs the following steps in each loop iteration or *frame*:

1. It processes any inputs.
2. It updates the game world.
3. It generates any outputs.

Each of these steps is performed by objects of the classes `controller`, `game`, and `renderer` respectively. Additionally, two more objects, `tetromino` and `playfield`, are used to help represent the game logic.

Basically, the game flow is the following: once a new tetromino enters the playfield, the program attends any keyboard input from the user. Then, it updates the game state if possible (the game first checks whether the requested movement is allowed), moving or rotating the piece accordingly. When the tetromino cannot go further down, it is stored into the playfield and a new tetromino is created. Score and level are also updated. Lastly, the current game state (namely, playfield, current falling tetromino, score, and level) is rendered on to the screen. The game finishes when the user so requests it or when the tetrominoes are stacked up to the top of the playfield. Please note that one of the inputs is not originated by the user, but from the *gravity*, which makes the tetrominoes fall down by the playfield at a regular rate based on the game level.

### `main.cpp`

[main.cpp](/src/main.cpp) is the entry point for the program. The `main` function in this file sets variables such as the window height and width and the number of frames per second at which the game will be played. The `main` function also creates `renderer`, `controller`, and `game` objects, and calls the `game::run` method to start the game loop.

### `controller.h` and `controller.cpp`

[controller.h](src/controller.h) and [controller.cpp](src/controller.cpp) define the `controller` class. This class handles keyboard input using the [SDL](https://www.libsdl.org/) library.

### `game.h` and `game.cpp`

[game.h](src/game.h) and [game.cpp](src/game.cpp) define the `game` class and the game loop: `game::run`. The `game` class stores the state of the game, including an instance of the current falling `tetromino` and its current location, the game score and level, the `playfield`. Aside from the game loop, the `game` class also contains methods to update the state of the game (`game::update`) and to carry out each of the actions required by the game logic.

### `tetromino.h` and `tetromino.cpp`

[tetromino.h](src/tetromino.h) and [tetromino.cpp](src/tetromino.cpp) define an abstract `tetromino` class, which contains attributes to keep track of the `tetromino` orientation, color, shape, and the like. Also, these files contain the definitions of several derived classes which implement this interface for each of the standard tetrominoes.

### `playfield.h` and `playfield.cpp`

[playfield.h](src/playfield.h) and [playfield.src](src/playfield.src) contains the definition of the `playfield` class, which represents the game playfield. It stores all the tetrominoes that have touched ground or other tetrominoes.

### `renderer.h` and `renderer.cpp`

[renderer.h](src/renderer.h) and [renderer.cpp](src/renderer.cpp) define the `renderer` class, which uses the SDL library to render the game to the screen. The `renderer` class constructor creates the SDL window an SDL renderer object that can draw in to the window. The `renderer::render` method draws the current falling tetromino and the playfield in to the window using the SDL renderer.

## Rubric

Hopefully, the project compiles and runs with no problem whatsoever, so this point can be ticked off from the *required* criteria list. Also, this is all contained within a README file with building instructions and a moderately detailed project overview, so the rest of criteria should be addressed as well.

Please find below the list of optional rubric points which are met by this projet. Those which are not explicitly identified in the source code are features scattered all over the files.

### Loop, Functions, I/O

- The project demonstrates an understanding of C++ functions and control structures.

### Object Oriented Programming

- The project uses Object Oriented Programming techniques.
- Classes use appropriate access specifiers for class members (see, for instance, [controller.h](src/controller.h), line 27 or [game.h](src/game.h), lines 22 and 44).
- Class constructors utilize member initialization lists (see, for instance, [game.cpp](src/game.cpp), line 14 or [renderer.cpp](src/renderer.cpp), line 24).
- Classes abstract implementation details from their interfaces.
- Classes encapsulate behavior.
- Classes follow an appropriate inheritance hierarchy (see the classes defined at [tetromino.h](src/tetromino.h)).
- Overloaded functions allow the same function to operate on different parameters (see, for instance, the declaration of `get_color_coordinates` at [renderer.h](src/renderer.h), lines 76 and 85).
- Derived class functions override virtual base class functions (see the classes defined at [tetromino.h](src/tetromino.h)).

### Memory management

- The project makes use of references in function declarations.
- The project uses destructors appropriately (see [renderer.cpp](src/renderer.cpp), line 57).
- The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate (see, for instance, [renderer.cpp](src/renderer.cpp), lines 26 and 57).
- The project uses smart pointers instead of raw pointers (see [game.h](src/game.h), line 97, for the use of a `unique_pointer`).
