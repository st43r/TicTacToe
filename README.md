# Tic Tac Toe Game

This is a graphical implementation of the classic Tic Tac Toe game using the SFML library in C++. The game allows two players to play Tic Tac Toe with a user-friendly graphical interface. 

## Features

- **Playable Tic Tac Toe**: Two players can take turns clicking on the grid to place 'X' or 'O'.
- **Game Status**: Displays the current player's turn and the result of the game (win, draw) in the center of the board.
- **Restart and End Game Buttons**: Includes options to restart the game or end it.
- **Hover Effects**: Button styles change when hovered over for a better user experience.
- **Centered Xs and Os**: The 'X' and 'O' are centered within each grid cell.

## Requirements

- SFML (Simple and Fast Multimedia Library) 2.5.1 or higher
- A C++ compiler that supports C++11 or later

## Installation

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/st43r/TicTacToe.git
   cd TicTacToe
   ```

2. **Install SFML**:

   Follow the instructions for your operating system from the [SFML website](https://www.sfml-dev.org/download.php) to install SFML.

3. **Build the Project**:

   You need to link against the SFML libraries. Below are example commands for different build systems:

   **Using `cmake`**:

   - Create a build directory and navigate to it:

     ```bash
     mkdir build
     cd build
     ```

   - Run `cmake` and `make`:

     ```bash
     cmake ..
     make
     ```

   **Using `g++` directly**:

   ```bash
   g++ -o TicTacToe main.cpp -lsfml-graphics -lsfml-window -lsfml-system
   ```

## Usage

1. **Run the Game**:

   After building, you can run the executable:

   ```bash
   ./TicTacToe
   ```

2. **Playing the Game**:

   - Click on any cell to place an 'X' or 'O' depending on whose turn it is.
   - The game status is displayed at the top of the window, showing whose turn it is or the result of the game.
   - Use the "Restart" button to start a new game without closing the application.
   - Use the "End Game" button to close the application.

## Controls

- **Mouse Click**: Select a cell to place 'X' or 'O'.
- **Restart Button**: Start a new game.
- **End Game Button**: Close the application.

## Code Overview

- `main.cpp`: Contains the main game logic, including handling user input, drawing the board, and managing game state.
- **SFML**: Used for creating the graphical user interface and handling events.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Acknowledgments

- [SFML](https://www.sfml-dev.org/) for the multimedia library used to create the graphical interface.
- [Arial Font](https://www.dafont.com/arial.font) for use in displaying text. Ensure `arial.ttf` is available in the project directory.
