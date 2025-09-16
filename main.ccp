#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// TicTacToe game class
class TicTacToe {
private:
    vector<vector<char>> board;  // 3x3 game board
    char currentPlayer;          // Current player (X or O)

public:
    // Constructor: initialize empty board and set first player
    TicTacToe() {
        board = vector<vector<char>>(3, vector<char>(3, ' '));
        currentPlayer = 'X';
    }

    // Display the board on the console
    void printBoard() {
        cout << "\n";
        for (int i = 0; i < 3; i++) {
            cout << " ";
            for (int j = 0; j < 3; j++) {
                cout << board[i][j];
                if (j < 2) cout << " | ";
            }
            cout << "\n";
            if (i < 2) cout << "---+---+---\n";
        }
        cout << "\n";
    }

    // Attempt to make a move; return false if invalid
    bool makeMove(int row, int col) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ')
            return false;
        board[row][col] = currentPlayer;
        return true;
    }

    // Check if the current player has won
    bool checkWin() {
        // Check rows and columns
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer)
                return true;
            if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)
                return true;
        }
        // Check diagonals
        if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer)
            return true;
        if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)
            return true;

        return false;
    }

    // Check if the board is full (draw)
    bool checkDraw() {
        for (auto &row : board)
            for (auto cell : row)
                if (cell == ' ') return false;
        return true;
    }

    // Switch turns between X and O
    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    // Get the current player (X or O)
    char getCurrentPlayer() {
        return currentPlayer;
    }

    // AI move: choose a random empty cell
    pair<int, int> getRandomMove() {
        vector<pair<int, int>> emptyCells;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') emptyCells.push_back({i, j});
            }
        }
        if (!emptyCells.empty()) {
            int idx = rand() % emptyCells.size();
            return emptyCells[idx];
        }
        return {-1, -1}; // Should never happen if called correctly
    }
};

// Function to play a single game
void playGame(bool vsAI) {
    TicTacToe game;
    bool gameOver = false;

    while (!gameOver) {
        game.printBoard();
        int row, col;

        if (vsAI && game.getCurrentPlayer() == 'O') {
            // If AI's turn
            cout << "AI is making a move...\n";
            pair<int, int> move = game.getRandomMove();
            game.makeMove(move.first, move.second);
        } else {
            // If human player's turn
            cout << "Player " << game.getCurrentPlayer() << ", enter row and column (0-2 0-2): ";
            cin >> row >> col;
            if (!game.makeMove(row, col)) {
                cout << "Invalid move. Try again.\n";
                continue;
            }
        }

        // Check for win/draw after move
        if (game.checkWin()) {
            game.printBoard();
            cout << "Player " << game.getCurrentPlayer() << " wins!\n";
            gameOver = true;
        } else if (game.checkDraw()) {
            game.printBoard();
            cout << "It's a draw!\n";
            gameOver = true;
        } else {
            game.switchPlayer();
        }
    }
}

// Main menu
int main() {
    srand(static_cast<unsigned int>(time(0)));

    bool running = true;
    while (running) {
        cout << "=== Tic-Tac-Toe ===\n";
        cout << "1. Player vs Player\n";
        cout << "2. Player vs AI\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: playGame(false); break;
            case 2: playGame(true); break;
            case 3: running = false; break;
            default: cout << "Invalid choice. Try again.\n"; break;
        }
    }

    cout << "Thanks for playing!\n";
    return 0;
}
