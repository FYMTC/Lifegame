#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "arial_ttf.h"
using namespace std;
using namespace sf;

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int neighbors[3] = {0, 1, -1};

        int rows = board.size();
        int cols = board[0].size();

        // Create copyBoard
        vector<vector<int>> copyBoard(rows, vector<int>(cols, 0));

        // Copy from original board to copyBoard
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                copyBoard[row][col] = board[row][col];
            }
        }

        // Iterate through board
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                int liveNeighbors = 0;

                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (!(neighbors[i] == 0 && neighbors[j] == 0)) {
                            int r = (row + neighbors[i]);
                            int c = (col + neighbors[j]);

                            if ((r < rows && r >= 0) && (c < cols && c >= 0) && (copyBoard[r][c] == 1)) {
                                liveNeighbors += 1;
                            }
                        }
                    }
                }

                // Rule 1 or 3
                if ((copyBoard[row][col] == 1) && (liveNeighbors < 2 || liveNeighbors > 3)) {
                    board[row][col] = 0;
                }
                // Rule 4
                if (copyBoard[row][col] == 0 && liveNeighbors == 3) {
                    board[row][col] = 1;
                }
            }
        }
    }
};

void drawBoard(RenderWindow& window, const vector<vector<int>>& board, int cellSize, bool isRunning, int speed) {
    window.clear(Color::White);

    Font font;
    if (font.openFromMemory(arial_ttf, arial_ttf_len)) {
        // Draw the game board
        for (size_t i = 0; i < board.size(); ++i) {
            for (size_t j = 0; j < board[i].size(); ++j) {
                RectangleShape cell(Vector2f(cellSize - 1, cellSize - 1));
                cell.setPosition(Vector2f(static_cast<float>(j * cellSize), static_cast<float>(i * cellSize)));
                cell.setFillColor(board[i][j] ? Color::Black : Color::White);
                cell.setOutlineThickness(1);
                cell.setOutlineColor(Color(200, 200, 200));
                window.draw(cell);
            }
        }

        // Draw control buttons
        // Run/Stop button
        RectangleShape runButton(Vector2f(80, 30));
        runButton.setPosition(Vector2f(10, 10));
        runButton.setFillColor(isRunning ? Color::Red : Color::Green);
        window.draw(runButton);

        Text runText(font, "", 14);;
        runText.setFont(font);
        runText.setString(isRunning ? "Stop" : "Run");
        runText.setCharacterSize(20);
        runText.setFillColor(Color::White);
        runText.setPosition(Vector2f(30, 10));
        window.draw(runText);

        // Speed up button
        RectangleShape speedUpButton(Vector2f(80, 30));
        speedUpButton.setPosition(Vector2f(100, 10));
        speedUpButton.setFillColor(Color(100, 100, 255));
        window.draw(speedUpButton);

        Text speedUpText(font, "", 14);;
        speedUpText.setFont(font);
        speedUpText.setString("Faster");
        speedUpText.setCharacterSize(20);
        speedUpText.setFillColor(Color::White);
        speedUpText.setPosition(Vector2f(110, 10));
        window.draw(speedUpText);

        // Slow down button
        RectangleShape slowDownButton(Vector2f(80, 30));
        slowDownButton.setPosition(Vector2f(190, 10));
        slowDownButton.setFillColor(Color(255, 100, 100));
        window.draw(slowDownButton);

        Text slowDownText(font, "", 14);;
        slowDownText.setFont(font);
        slowDownText.setString("Slower");
        slowDownText.setCharacterSize(20);
        slowDownText.setFillColor(Color::White);
        slowDownText.setPosition(Vector2f(200, 10));
        window.draw(slowDownText);

        // Speed indicator
        Text speedText(font, "", 14);
        speedText.setFont(font);
        speedText.setString("Speed: " + to_string(speed) + "ms");
        speedText.setCharacterSize(20);
        speedText.setFillColor(Color::Black);
        speedText.setPosition(Vector2f(280, 10));
        window.draw(speedText);
    }

    window.display();
}

int main() {
    vector<vector<int>> board(100, vector<int>(150, 0)); // Larger board for better interaction
    Solution game;

    const int cellSize = 10;
    const int width = static_cast<int>(board[0].size()) * cellSize;
    const int height = static_cast<int>(board.size()) * cellSize;

    RenderWindow window;
    window.create(VideoMode(Vector2u(width, height)), sf::String(L"生命游戏"));
    window.setFramerateLimit(120);

    bool isRunning = false;
    bool mouseDown = false;
    int speed = 20; // Initial speed in milliseconds
    int lastRow = -1, lastCol = -1; // 用于插值的上一个格子坐标

    while (window.isOpen()) {
        for (auto event = window.pollEvent(); event.has_value(); event = window.pollEvent()) {
            const auto& e = event.value();

            if (e.is<Event::Closed>()) {
                window.close();
            }

            if (auto mouseButton = e.getIf<Event::MouseButtonPressed>()) {
                if (mouseButton->button == Mouse::Button::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);

                    // Check if run button was clicked
                    if (mousePos.x >= 10 && mousePos.x <= 90 && mousePos.y >= 10 && mousePos.y <= 40) {
                        isRunning = !isRunning;
                    }
                    // Check if speed up button was clicked
                    else if (mousePos.x >= 100 && mousePos.x <= 180 && mousePos.y >= 10 && mousePos.y <= 40) {
                        speed = max(10, speed - 2); // Decrease by 50ms, minimum 50ms
                    }
                    // Check if slow down button was clicked
                    else if (mousePos.x >= 190 && mousePos.x <= 270 && mousePos.y >= 10 && mousePos.y <= 40) {
                        speed = min(50, speed + 2); // Increase by 50ms, maximum 1000ms
                    }
                    else {
                        // Toggle cells
                        int row = mousePos.y / cellSize;
                        int col = mousePos.x / cellSize;
                        if (row >= 0 && row < board.size() && col >= 0 && col < board[0].size()) {
                            board[row][col] = 1 - board[row][col];
                        }
                        mouseDown = true;
                        lastRow = row;
                        lastCol = col;
                    }
                }
            }

            if (auto mouseButton = e.getIf<Event::MouseButtonReleased>()) {
                if (mouseButton->button == Mouse::Button::Left) {
                    mouseDown = false;
                    lastRow = -1;
                    lastCol = -1;
                }
            }

            if (auto mouseMove = e.getIf<Event::MouseMoved>(); mouseMove && mouseDown) {
                Vector2i mousePos = Mouse::getPosition(window);
                int row = mousePos.y / cellSize;
                int col = mousePos.x / cellSize;
                if (row >= 0 && row < board.size() && col >= 0 && col < board[0].size()) {
                    // 插值填充上一个格子和当前格子之间的所有格子
                    if (lastRow != -1 && lastCol != -1) {
                        int dx = abs(col - lastCol), dy = abs(row - lastRow);
                        int sx = lastCol < col ? 1 : -1;
                        int sy = lastRow < row ? 1 : -1;
                        int x = lastCol, y = lastRow;
                        int err = (dx > dy ? dx : -dy) / 2, e2;
                        while (true) {
                            if (y >= 0 && y < board.size() && x >= 0 && x < board[0].size())
                                board[y][x] = 1;
                            if (x == col && y == row) break;
                            e2 = err;
                            if (e2 > -dx) { err -= dy; x += sx; }
                            if (e2 < dy)  { err += dx; y += sy; }
                        }
                    } else {
                        board[row][col] = 1;
                    }
                    lastRow = row;
                    lastCol = col;
                }
            }

            if (auto keyEvent = e.getIf<Event::KeyPressed>()) {
                if (keyEvent->code ==sf::Keyboard::Key::Space) {
                    isRunning = !isRunning;
                } else if (keyEvent->code == sf::Keyboard::Key::Up) {
                    speed = max(10, speed - 2); // Speed up with up arrow
                } else if (keyEvent->code ==sf::Keyboard::Key::Down) {
                    speed = min(50, speed + 2); // Slow down with down arrow
                }
            }
        }

        if (isRunning) {
            game.gameOfLife(board);
            sleep(milliseconds(speed)); // Use the current speed
        }

        drawBoard(window, board, cellSize, isRunning, speed);
    }

    return 0;
}