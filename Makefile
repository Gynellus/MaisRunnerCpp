# Makefile
OUTPUT_DIR = bin
SRC_DIR = src
OBJ = $(OUTPUT_DIR)/main

all: $(OBJ)

$(OBJ): $(SRC_DIR)/main.cpp $(SRC_DIR)/Maze.cpp $(SRC_DIR)/MazeGUI.cpp $(SRC_DIR)/Player.cpp $(SRC_DIR)/MazeGenerator.cpp
	g++ $^ -o $@

run: $(OBJ)
	./$(OBJ) $(ARGS)

clean:
	rm -f $(OUTPUT_DIR)/*
