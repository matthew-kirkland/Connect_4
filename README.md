# Connect 4 Engine v2.0.0
> An engine to help players win in Connect 4

This is a simple two-player game that operates via a game window, with a built-in engine that can be utilised on either player's turn.

## Running the game
Before attempting anything, ensure that you have the following:
- CMake
- C++ compiler with C++17 support:
  - On Windows: [MinGW-w64](https://www.mingw-w64.org/) or MSVC (via Visual Studio)
  - On macOS: Xcode Command Line Tools
  - On Linux: `g++` or `clang++`
- Git (to fetch SFML via CMake)

Now, to run the game, navigate to the repository's root directory.
1. Create a `build` directory by typing `mkdir build`
2. Navigate into it  by typing `cd build`
3. Run `cmake ..` and then `cmake --build .`
4. Run the `Connect_4.exe` executable file, and the game window will open up!

Typing `h` during either player's turn will use the engine, currently set at a depth of 8, to determine the best move for that player. A complete list of actions is provided below:
- Any number from `1` to `7`: places your token in the designated column (column number increases from left to right).
- Clicking in any column: places a token in the clicked column.
- `u`: performs an "undo" on the most recent move.
- `h`: highlights the best move for the current player.

# Changelog
## v2.0.0 (22/05/2025)
- Gameplay has moved out of the terminal! A simple game window replaced the terminal UI for a better experience
- Hand-drawn board and token textures
- Some actions like `w` and `q` have been removed

## v1.1.0 (26/04/2025)
- Engine speed has dramatically increased thanks to implementation of alpha-beta pruning
- Increased speed has allowed the search depth to grow to 8 moves ahead

## v1.0.0 (19/04/2025)
- Added friendly colours to the token characters in the terminal

## v0.1.0 (04/02/2025)
- Engine speed has seen a mild improvement. 2D array board representation was scrapped and replaced with bitboards, which improved win-checking speeds and decreased game state evaluation runtime
- Added a helpful `w` action to remind users who should play the next turn
- Faster engine means search depth increased to 7, providing a more accurate "best move"

## v0.0.0 (28/01/2025)
- The game is played in the terminal, with optional "hint" action that calls the engine
- Slight speedup by translating main game logic from Python to C
- Engine uses naive minimax with a depth of 6, ensuring the right balance between accuracy and runtime
