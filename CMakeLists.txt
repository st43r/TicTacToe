cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(TicTacToe VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable
add_executable(TicTacToe main.cpp)

# Link SFML libraries
target_link_libraries(TicTacToe sfml-graphics sfml-window sfml-system)
