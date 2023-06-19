# 42_connect4

# ABOUT THE PROJECT:
This is the classic game of *connect 4* coded in C for a challenge at 42 Luiss Firenze.

Put 4 marks in a row (horizontally, vertically or diagonally) to win.

You can play against the CPU or against another player in shared screen.

# HOW TO USE:
| command | description |
| ------- | ----------- |
| `make` | compile *connect4* |
| `make clean` | remove tmp files |
| `make fclean` | remove tmp files and executable |
| `make re` | force recompile |
| `make pvp` | compile *connect4* with default mode PVP (necessary for noob graphics) |
| `make pve` | compile *connect4* with default mode PVE |

# HOW TO LAUNCH:

`./connect4 <n_of_columns> <n_of_rows> <graphics>`

# GRAPHICS:
| name | description |
| ---- | ----------- |
| noob | to play on the command line |
| mlx | to play on a new window with fancy graphics |
