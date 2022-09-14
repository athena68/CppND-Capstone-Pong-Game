# CppND-Capstone-Pong-Game

This is the repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://austinmorlan.com/posts/pong_clone/) pong game tutorial.

Basically, the project structure based on [CppND-Capstone-Snake-Game](https://github.com/udacity/CppND-Capstone-Snake-Game), re-utilize the cmake system and stick to Game, Controller, Render flow.

## Game Play
Using arrow key up, down and w, s to control paddles
![PongGame](https://user-images.githubusercontent.com/9254181/190135943-2878a2ac-6d0f-4e73-80de-8ed6144b3091.png)

## The following rubric points are addressed

* Compiling and Testing
The project code compile and run without errors

* Loops, Functions, I/O
The project demonstrates an understanding of C++ functions and control structures: 
file src/main.cpp:14:17; 
file src/controller.cpp:7:44- HandleInput method - use of multiple switch case.
The project accepts user input and processes the input using the SDL library.

* Object Oriented Programming
The project uses Object Oriented Programming techniques. Can be seen in each file except main.cpp
Classes use appropriate access specifiers for class members. Classes encapsulate behavior. Classes abstract implementation details from their interfaces. can be seen in ball.h, paddles.h, player_score.h, controller.h, game.h, renderer.h...
Class constructors utilize member initialization lists: file src/renderer.cpp:8

* Memory Management
The project makes use of references in function declarations: src/controller.h:8, /src/game.h:16, /src/game.h:29, /src/renderer.h:18, ...
The project uses destructors appropriately: src/renderer.cpp:34:38

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./PongGame`.
