# Puzzle-Game

Creates N * N puzzle to win a game sort numbers 1 to N empty space needs to be in top left corner
Use wasd to move

Game uses /dev/urandom to fill puzzle.

Usage: puzzle -Options -S <size>
    -M manual solve
    -A Random solve
    -R Random solve with check if number is in correct place
    -B best-first search
