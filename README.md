# Connect 4 Engine
> An engine to help players win in Connect 4

## Using the engine
This is a simple two-player game that operates in the terminal, with a built-in engine that can be utilised on either player's turn.

To run this game, first clone the repository, and ensure that you have the following:
- A machine with either Windows, Linux, or MacOS,
- The gcc compiler.

To compile the game, navigate to the repository's directory, and run `make` if you are on Linux or MacOS, or `mingw32-make` for Windows. Run the "game" executable file and it will begin in the terminal.

Typing `h` during either player's turn turn will use the engine, currently set at a depth of 6, to determine the best move for that player. This value, and how players interact with it, is susceptible to change. A complete list of commands is provided below:
- Any number from `1` to `7`: place your token in the designated column (column number increases from left to right).
- `q`: quits the game early.
- `u`: performs an "undo" on the most recent move.
- `w`: returns the current player.
- `h`: returns the best move for the current player.
