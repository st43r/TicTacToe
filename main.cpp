#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

const u_short SIZE = 3;
const u_short TILE_SIZE = 200;
const u_short TEXT_HEIGHT = 80;
const u_short WINDOW_HEIGHT = SIZE * TILE_SIZE + TEXT_HEIGHT + 50;
char board[SIZE][SIZE];
bool isXTurn = true;
bool gameEnded = false;
std::string gameStatus = "Player X's turn";
std::string fontPath = "arial.ttf";

/**
 * @brief Initializes the game board by setting all cells to ' '.
 */
void initializeBoard() {
    for (auto &i: board) {
        for (char &j: i) {
            j = ' ';
        }
    }
    isXTurn = true;
    gameEnded = false;
    gameStatus = "Player X's turn";
}

/**
 * @brief Checks if the specified player has won the game.
 * @param player The player to check for a win ('X' or 'O').
 * @return true if the player has won, false otherwise.
 */
bool checkWin(const char player) {
    // Check rows
    for (auto const &i: board) {
        if (i[0] == player && i[1] == player && i[2] == player) return true;
    }

    // Check columns
    for (u_short i = 0; i < SIZE; ++i) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }

    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;

    return false;
}

/**
 * @brief Checks if the game board is full.
 * @return true if the board is full, false otherwise.
 */
bool isBoardFull() {
    for (auto const &i: board) {
        for (char const j: i) {
            if (j == ' ') return false;
        }
    }
    return true;
}

/**
 * @brief Handles a click event on the game board.
 * @param x The x-coordinate of the click.
 * @param y The y-coordinate of the click.
 */
void handleClick(const u_short x, const u_short y) {
    if (gameEnded) return;

    const u_short row = (y - TEXT_HEIGHT) / TILE_SIZE;
    const u_short col = x / TILE_SIZE;
    if (row < SIZE && col < SIZE && board[row][col] == ' ') {
        board[row][col] = isXTurn ? 'X' : 'O';
        isXTurn = !isXTurn;
        gameStatus = isXTurn ? "Player X's turn" : "Player O's turn";
    }
}

/**
 * @brief Draws the game board and the current state of the game.
 * @param window The window to draw on.
 * @param font The font to use for drawing text.
 */
void drawBoard(sf::RenderWindow &window, sf::Font &font) {
    window.clear(sf::Color::White);

    // Draw the grid lines
    for (u_short i = 0; i <= SIZE; ++i) {
        // Horizontal lines
        sf::RectangleShape horizontalLine(sf::Vector2f(SIZE * TILE_SIZE, 5));
        horizontalLine.setFillColor(sf::Color::Black);
        horizontalLine.setPosition(0, (i * TILE_SIZE) + TEXT_HEIGHT - 2.5);
        window.draw(horizontalLine);

        // Vertical lines
        sf::RectangleShape verticalLine(sf::Vector2f(5, SIZE * TILE_SIZE));
        verticalLine.setFillColor(sf::Color::Black);
        verticalLine.setPosition((i * TILE_SIZE) - 2.5, TEXT_HEIGHT);
        window.draw(verticalLine);
    }

    // Draw the X and O
    for (u_short i = 0; i < SIZE; ++i) {
        for (u_short j = 0; j < SIZE; ++j) {
            if (board[i][j] != ' ') {
                sf::Text text;
                text.setFont(font);
                text.setString(board[i][j]);
                text.setCharacterSize(150);
                text.setFillColor(sf::Color::Black);

                // Center the text in the tile
                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                text.setPosition(j * TILE_SIZE + TILE_SIZE / 2.0f, i * TILE_SIZE + TILE_SIZE / 2.0f + TEXT_HEIGHT);

                window.draw(text);
            }
        }
    }

    if (gameEnded) {
        // Draw a semi-transparent overlay
        sf::RectangleShape overlay(sf::Vector2f(SIZE * TILE_SIZE, SIZE * TILE_SIZE));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        overlay.setPosition(0, TEXT_HEIGHT);
        window.draw(overlay);

        // Display the game status in the center of the board
        sf::Text statusText;
        statusText.setFont(font);
        statusText.setString(gameStatus);
        statusText.setCharacterSize(60);
        statusText.setFillColor(sf::Color::White);

        // Center the status text
        sf::FloatRect textRect = statusText.getLocalBounds();
        statusText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        statusText.setPosition(SIZE * TILE_SIZE / 2.0f, SIZE * TILE_SIZE / 2.0f + TEXT_HEIGHT);

        window.draw(statusText);
    } else {
        // Display the game status above the board
        sf::Text statusText;
        statusText.setFont(font);
        statusText.setString(gameStatus);
        statusText.setCharacterSize(50);
        statusText.setFillColor(sf::Color::Black);

        sf::FloatRect textRect = statusText.getLocalBounds();
        statusText.setPosition(SIZE * TILE_SIZE / 2.0f - textRect.width / 2.0f, 0);

        window.draw(statusText);
    }
}

/**
 * @brief Checks if the mouse is over the given text.
 * @param text The text to check.
 * @param mouseX The x-coordinate of the mouse.
 * @param mouseY The y-coordinate of the mouse.
 * @return true if the mouse is over the text, false otherwise.
 */
bool isMouseOverText(const sf::Text &text, int mouseX, int mouseY) {
    sf::FloatRect bounds = text.getGlobalBounds();
    return bounds.contains(mouseX, mouseY);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(SIZE * TILE_SIZE, WINDOW_HEIGHT), "Tic Tac Toe",
                            sf::Style::Titlebar | sf::Style::Close);
    sf::Font font;
    std::filesystem::path path = std::filesystem::exists(fontPath) ? fontPath : "../" + fontPath;
    if (!font.loadFromFile(path)) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    initializeBoard();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
                && event.mouseButton.y >= TEXT_HEIGHT && event.mouseButton.y < SIZE * TILE_SIZE + TEXT_HEIGHT) {
                handleClick(event.mouseButton.x, event.mouseButton.y);
            }
        }

        if (!gameEnded) {
            if (checkWin('X')) {
                gameStatus = "Player X wins!";
                gameEnded = true;
            } else if (checkWin('O')) {
                gameStatus = "Player O wins!";
                gameEnded = true;
            } else if (isBoardFull()) {
                gameStatus = "It's a draw!";
                gameEnded = true;
            }
        }

        drawBoard(window, font);

        // Draw 'End Game' and 'Restart' buttons
        sf::Text endGameText;
        endGameText.setFont(font);
        endGameText.setString("End Game");
        endGameText.setCharacterSize(30);
        endGameText.setFillColor(sf::Color::Black);
        endGameText.setPosition(10, SIZE * TILE_SIZE + TEXT_HEIGHT + 10);

        sf::Text restartText;
        restartText.setFont(font);
        restartText.setString("Restart");
        restartText.setCharacterSize(30);
        restartText.setFillColor(sf::Color::Black);
        restartText.setPosition(SIZE * TILE_SIZE - 110, SIZE * TILE_SIZE + TEXT_HEIGHT + 10);

        // Handle button clicks and hover effects
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (isMouseOverText(endGameText, mousePos.x, mousePos.y)) {
            endGameText.setStyle(sf::Text::Underlined);
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                window.close(); // End game button
            }
        } else {
            endGameText.setStyle(sf::Text::Regular);
        }

        // Button hover effects and interactions
        if (isMouseOverText(restartText, mousePos.x, mousePos.y)) {
            restartText.setStyle(sf::Text::Underlined);
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                initializeBoard(); // Restart button
            }
        } else {
            restartText.setStyle(sf::Text::Regular);
        }

        window.draw(endGameText);
        window.draw(restartText);

        window.display();
    }

    return 0;
}
