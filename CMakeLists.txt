cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")


project(SDL2PongGame)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(PongGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/vector2d.cpp src/ball.cpp src/paddles.cpp src/player_score.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
string(STRIP ${SDL2_TTF_LIBRARIES} SDL2_TTF_LIBRARIES)
target_link_libraries(PongGame ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})