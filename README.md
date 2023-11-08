# MaisRunnerCpp
In this project I implemented an agent that uses a Depth First Search algorithm to explore a maze where it can find power-ups and power-downs on its way.

This is a standard implementation of DFS with the added considerations: when the player has power-ups within sight it is more likely that the move towards them will be selected; if power-owns are in sight the moves that lead to them will be considered only if there are no alternative paths immediately available (i.e. require no backtracking); if the exit to the maze is in sight, the player will fast-track to it.

A makefile allows to compile and run the project with the "make run" command. Adding 'ARGS="-r"' to the command will run the program on a randomly generated maze.