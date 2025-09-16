# Tic-Tac-Toe in C++

A simple **Tic-Tac-Toe game** written in C++ with support for:

- **Player vs Player**
- **Player vs Computer (Easy – Random moves)**
- **Player vs AI (Hard – Minimax AI algorithm)**

This project demonstrates fundamental C++ skills such as arrays, loops, conditionals, functions, and recursion, while also introducing **AI concepts** like the **Minimax adversarial search algorithm**.

---

## Features

- Play Tic-Tac-Toe in the terminal/command prompt.
- Board labeled with rows and columns for intuitive input (1–3).
- Three game modes:
  1. **Player vs Player**
  2. **Player vs Computer (Easy)** – computer makes random moves.
  3. **Player vs AI (Hard)** – computer uses Minimax to play optimally.
- Input validation (prevents overwriting cells or out-of-range input).
- Replay option after each game.

---

## Getting Started

### Prerequisites

- A C++ compiler such as **g++**.
  - On Windows: install via [MSYS2](https://www.msys2.org/) or [MinGW-w64](http://mingw-w64.org/).
  - On Linux/macOS: `g++` is usually available via package manager.

- [Visual Studio Code](https://code.visualstudio.com/) or any C++ IDE (optional but recommended).

---

### Compile and Run

1. Clone the repository or download the source:
   ```bash
   git clone https://github.com/YOUR-USERNAME/tic-tac-toe-cpp.git
   cd tic-tac-toe-cpp
   
2. Compile the program:
     ```bash
     g++ tictactoe.cpp -o tictactoe

3. Run the game:
- **On Linux/macOS**
    ```bash
    ./tictactoe
- **On Windows (PowerShell or CMD)**
    ```bash
    .\tictactoe.exe

---

## Example Gameplay

=== Tic-Tac-Toe ===
Input moves using row and column numbers (1 to 3).
You are 'X', AI is 'O'.

Choose mode:
 1) Player vs Player
 2) Player vs AI (Easy - random)
 3) Player vs AI (Hard - Minimax)
 4) Exit
Enter choice: 3

---

## Technical Details

- **Programming Language:** C++  
- **AI Algorithm:** Minimax with simple tie-breaking and depth scoring  
- **Difficulty Modes:** Random (easy) vs. Minimax (hard)

This project demonstrates:

- Use of arrays for the game board  
- Input validation and error handling  
- Recursive algorithms (Minimax)  
- Clear separation of functions for readability and maintainability  

---

## Future Improvements

- Add Alpha-Beta Pruning for Minimax optimization  
- Implement a GUI version (e.g., with SFML or SDL)  
- Add unit tests for board evaluation and AI functions  

---

## Author

Developed by **Karlie Sikorski**  
Feel free to connect with me on [LinkedIn](https://www.linkedin.com/in/k-sikorski/) and through my [website](https://karliesikorski.wixsite.com/portfolio) or explore my other projects on GitHub!
