// tictactoe.cpp
// Tic-Tac-Toe with Player vs Player, Player vs AI (random), Player vs AI (minimax).
// Input: row col using 1-based indices (1..3).
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE];

void initializeBoard() {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = ' ';
}

void displayBoard() {
    cout << "\n    1   2   3\n";
    cout << "  -------------\n";
    for (int i = 0; i < SIZE; ++i) {
        cout << i+1 << " |";
        for (int j = 0; j < SIZE; ++j) {
            cout << ' ' << board[i][j] << " |";
        }
        cout << "\n  -------------\n";
    }
    cout << "\n";
}

bool isMovesLeft() {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == ' ') return true;
    return false;
}

bool checkWin(char player) {
    // Rows and columns
    for (int i = 0; i < SIZE; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    // Diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

// Evaluate board: +10 if AI (O) wins, -10 if human (X) wins, 0 otherwise
int evaluate() {
    if (checkWin('O')) return +10;
    if (checkWin('X')) return -10;
    return 0;
}

// Minimax recursive function.
// depth: how deep we are (used to prefer faster wins / slower losses).
// isMax: true when it's AI's (O) turn to maximize score.
int minimax(int depth, bool isMax) {
    int score = evaluate();

    // If terminal state, return score adjusted by depth to prefer faster wins and slower losses
    if (score == 10)  return score - depth;   // AI wins
    if (score == -10) return score + depth;   // Human wins
    if (!isMovesLeft()) return 0;             // Draw

    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int val = minimax(depth + 1, false);
                    board[i][j] = ' ';
                    best = max(best, val);
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int val = minimax(depth + 1, true);
                    board[i][j] = ' ';
                    best = min(best, val);
                }
            }
        }
        return best;
    }
}

// Find best move for AI using minimax; returns pair(row,col) as zero-based indices
pair<int,int> findBestMove() {
    int bestVal = numeric_limits<int>::min();
    vector<pair<int,int>> bestMoves;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveVal = minimax(0, false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    bestMoves.clear();
                    bestMoves.push_back({i, j});
                } else if (moveVal == bestVal) {
                    bestMoves.push_back({i, j});
                }
            }
        }
    }
    // break ties randomly so board isn't deterministic every game
    if (!bestMoves.empty()) {
        int idx = rand() % bestMoves.size();
        return bestMoves[idx];
    }
    return {-1, -1}; // shouldn't happen if called correctly
}

pair<int,int> getRandomMove() {
    vector<pair<int,int>> emptyCells;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == ' ')
                emptyCells.push_back({i, j});
    if (emptyCells.empty()) return {-1, -1};
    int idx = rand() % emptyCells.size();
    return emptyCells[idx];
}

void playerMove(char player) {
    int row, col;
    while (true) {
        cout << "Player " << player << ", enter your move (row and column, e.g., '1 3'): ";
        if (!(cin >> row >> col)) {
            // clear bad input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter two numbers between 1 and 3.\n";
            continue;
        }
        if (row < 1 || row > 3 || col < 1 || col > 3) {
            cout << "Row and column must be between 1 and 3. Try again.\n";
            continue;
        }
        int r = row - 1, c = col - 1;
        if (board[r][c] != ' ') {
            cout << "That cell is already taken. Try again.\n";
            continue;
        }
        board[r][c] = player;
        break;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // seed random once

    cout << "=== Tic-Tac-Toe ===\n";
    cout << "Input moves using row and column numbers (1 to 3).\n";
    cout << "You are 'X', AI is 'O'.\n\n";

    bool running = true;
    while (running) {
        cout << "Choose mode:\n";
        cout << " 1) Player vs Player\n";
        cout << " 2) Player vs Computer (Easy - random)\n";
        cout << " 3) Player vs AI (Hard - Minimax)\n";
        cout << " 4) Exit\n";
        cout << "Enter choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice.\n\n";
            continue;
        }

        if (choice == 4) {
            running = false;
            break;
        }

        initializeBoard();
        bool gameOver = false;
        char currentPlayer = 'X'; // X always begins

        while (!gameOver) {
            displayBoard();

            if (choice == 1) {
                // PvP: both players human
                playerMove(currentPlayer);
            } else if (choice == 2) {
                // PvE Easy: human X, random O
                if (currentPlayer == 'X') {
                    playerMove('X');
                } else {
                    auto m = getRandomMove();
                    if (m.first != -1) {
                        board[m.first][m.second] = 'O';
                        cout << "AI (random) placed 'O' at: " << (m.first + 1) << " " << (m.second + 1) << "\n";
                    }
                }
            } else if (choice == 3) {
                // PvE Hard: human X, Minimax O
                if (currentPlayer == 'X') {
                    playerMove('X');
                } else {
                    auto best = findBestMove();
                    if (best.first != -1) {
                        board[best.first][best.second] = 'O';
                        cout << "AI (minimax) placed 'O' at: " << (best.first + 1) << " " << (best.second + 1) << "\n";
                    }
                }
            } else {
                cout << "Invalid mode choice.\n";
                break;
            }

            // Check for end conditions
            if (checkWin(currentPlayer)) {
                displayBoard();
                if (currentPlayer == 'X') cout << "Player X wins!\n";
                else cout << "Player O (AI) wins!\n";
                gameOver = true;
                break;
            }

            if (!isMovesLeft()) {
                displayBoard();
                cout << "It's a draw!\n";
                gameOver = true;
                break;
            }

            // Switch player
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        cout << "\nPlay again? (y/n): ";
        char again;
        cin >> again;
        if (again == 'n' || again == 'N') running = false;
        cout << "\n";
    }

    cout << "Thanks for playing!\n";
    return 0;
}
